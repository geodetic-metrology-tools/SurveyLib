// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLSUniversalMtdComputer.h"

#include <vector>
#include <iostream>

#include <Logger.hpp>

#include "TLSInputMatrices.h"
#include "TLSResultsMatrices.h"
#include "TSparseMatrix.h"

TLSUniversalMtdComputer::TLSUniversalMtdComputer() : count(1)
{ // default constructor
}

TLSUniversalMtdComputer::~TLSUniversalMtdComputer()
{ // destructor
}

bool TLSUniversalMtdComputer::computeResults(TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	bool result = true;
	if (rm->getSolutionVectByConst()->size() != 0)
	{
		result = computeResultsMatrices(im, rm);
	}
	else
	{
		logWarning() << "Number of unknowns = 0.";
	}
	return result;
}

bool TLSUniversalMtdComputer::computeResultsMatrices(TLSInputMatrices *im, TLSResultsMatrices *rm)
{
//	// test if we do not have a 'nullpointer' in a case that the matrices are not initialized
//	if (!(im->getFirstDgnMtrx()) || !(im->getCnstrFirstDgnMtrx()) || !(rm->getSolutionVectByConst()))
//	{
//		logCritical() << "Some of the design matrices are not initialized!";
//		return false;
//	}

	// Discard any normal-equations intermediate from a previous solve; this pass repopulates it.
	fNormalMatrix.reset();
	fInvN1Matrix.reset();

	// When nothing is deactivated the getters return the full matrices by reference exactly as on
	// master; with a mask present they return the reduced (active-only) views. All masking now lives
	// inside TLSInputMatrices, so the algebra below stays identical to the unmasked master version.
	const bool masked = im->hasMask();

	const TSparseMatrix &A = im->getFirstDgnMtrx(masked);
	const TVector &W = im->getMisclosureVctr(masked); // W : Misclosures vector ("fermetures")
	const TSparseMatrix &A2 = im->getCnstrFirstDgnMtrx(masked); // A2 : First design matrix part related to constraints only
	const TVector &W2 = im->getCnstrMisclosureVctr(); // W2 : Misclosures vector part related to constraints only

	int nbUnk = im->getNbrUnknowns(masked);
	int nbEq = im->getNbrEquations(masked);
	int nbCnstr = im->getNbrConstraints();

	// set invN1
	TSparseMatrix invN1(nbEq, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		const TSparseMatrix &Pv = im->getWeightMtrx(masked);
		const TSparseMatrix &invB = im->getSecondDgnBlockDiagInvMtrx(masked);
		invN1 = invB.transpose() * Pv * invB;
	}
	else
	{ // if B is not block diagonal, invN1 needs to be computed via an explicit inversion
	  // B*invPv*BT is symmetric and positive definite so LDLT can be used
		const TSparseMatrix &B = im->getSecondDgnMtrx(masked);
		const TSparseMatrix &InvPv = im->getWeightInvMtrx(masked);
		if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1, true))
		{
			logCritical() << "Matrix B*inv(Pv)*transpose(B) could not be inverted!";
			return false;
		}
		// keep invN1 for the residual pass only if B is not block diagonal, otherwise it is not needed there
		fInvN1Matrix = invN1;
	}

	// Calculate Normal matrix N2 = At * inv( B * inv(P) * Bt ) * A , matrix dimensions (u,u)
	// and re-sets this new matrix to the main TLSResultsMatrices object.
	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = A.transpose() * invN1 * A;

	// construct NBig = (N2, A2t
	//                   A2, 0  )
	TSparseMatrix NBig(nbUnk + nbCnstr, nbUnk + nbCnstr);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(N2.nonZeros() + 2 * A2.nonZeros());

	// Fill in the N2 part
	for (int k = 0; k < N2.outerSize(); ++k)
	{
		for (TSparseMatrix::InnerIterator it(N2, k); it; ++it)
			coeffs.push_back(TTriplet(it.row(), it.col(), it.value()));
	}

	// Fill the A2 and A2T
	for (int k = 0; k < A2.outerSize(); ++k)
	{
		for (TSparseMatrix::InnerIterator it(A2, k); it; ++it)
		{
			coeffs.push_back(TTriplet(it.row() + N2.rows(), it.col(), it.value())); // A2
			coeffs.push_back(TTriplet(it.col(), it.row() + N2.cols(), it.value())); // A2T
		}
	}
	NBig.setFromTriplets(coeffs.begin(), coeffs.end());

	// Extended vector: appends W2 (constraints misclosures) to the calculated At*inv(N1)*W  vector
	TVector VBig(nbUnk + nbCnstr);
	VBig << A.transpose() * invN1 * W, W2;

	// Calculates solution NBig * X = -VBig and keeps only the part corresponding to adjusted parameters
	TVector solutionExt(nbUnk + nbCnstr);

	// use Cholesky decomposition if nbCnstr=0, otherwise SparseLU as positive definiteness of NBig may be violated
	if (!TSparseUtils::solveUnique(NBig, -VBig, solutionExt, (nbCnstr == 0)))
	{
		logCritical() << "No solution could be found when solving equation system: Nbig * dX = -VBig (extended matrices with conditions)";
		return false;
	}

	TVector solution(nbUnk);
	// we do not need the Lagrange multipliers
	solution = solutionExt.head(nbUnk);

	// Keep the reduced normal matrix for the residual/var-covar pass (computer-internal handoff).
	fNormalMatrix = NBig;

	// blow the solution back up to the full parameter set (inserts zeros at masked parameters;
	// a no-op when nothing is masked)
	rm->setSolutionVect(im->blowUpParameters(solution));

	return true;
}

bool TLSUniversalMtdComputer::calcResidusAndVarCovMatrix(TLSInputMatrices *im, TLSResultsMatrices *rm, bool computeObsCovar)
{
	if (!fError.empty())
		return false;

	// With no unknowns there is nothing to estimate: computeResults skips computeResultsMatrices in
	// that case (no normal matrix is produced) and still reports success. Mirror that here.
	const TVector *solutionVct = rm->getSolutionVectByConst();
	if (solutionVct == nullptr || solutionVct->size() == 0)
		return true;

	// Precondition: for a non-trivial system computeResultsMatrices must have run first - it produces
	// the reduced normal-equations system (fNormalMatrix, and fInvN1Matrix in the non-block-diagonal
	// case) that this pass consumes.
	if (!fNormalMatrix)
	{
		logCritical() << "calcResidusAndVarCovMatrix called before computeResultsMatrices: normal matrix not available.";
		return false;
	}

	// With a mask present the getters/dimensions return the reduced (active-only) system; without a
	// mask they behave exactly as on master. Masking lives entirely in TLSInputMatrices.
	const bool masked = im->hasMask();

	int nbUnk = im->getNbrUnknowns(masked);
	int nbObs = im->getNbrObservations(masked);
	int nbEq = im->getNbrEquations(masked);
	int nbCnstr = im->getNbrConstraints();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	// NB: the residual covariance matrix is optional (computeObsCovar), so it may legitimately be
	// uninitialised in the monitoring path - do not assert on it here.

	const TSparseMatrix &A = im->getFirstDgnMtrx(masked);
	const TSparseMatrix &B = im->getSecondDgnMtrx(masked);
	const TSparseMatrix &InvPv = im->getWeightInvMtrx(masked);

	TSparseMatrix S(nbObs, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		// if B is block-diagonal, the S formula simplifies to -invB
		S = -(im->getSecondDgnBlockDiagInvMtrx(masked));
	}
	else
	{
		if (!fInvN1Matrix)
		{
			throw std::runtime_error("The matrix invN1 is not initialized!");
		}
		const TSparseMatrix &invN1 = *fInvN1Matrix; // NB: invN1 will NOT be recalculated here (just taken from the previous pass!)
		S = -InvPv * B.transpose() * invN1;
	}
	const TSparseMatrix &Pv = im->getWeightMtrx(masked);
	const TVector &W = im->getMisclosureVctr(masked); // W : Misclosures vector ("fermetures")
	// the stored solution is blown up to the full parameter set; reduce it back to the active
	// parameters so it matches the (masked) design matrix A
	TVector solution = (*rm->getSolutionVectByConst())(im->getActiveParIndices()); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix &NBig = *fNormalMatrix; // NB: Normal matrix will NOT be recalculated here (just taken from the previous pass!)

	//--------------- Residuals ---------------//
	// Calculate intermediate matrix
	// S = - inv(P) * Bt *inv( B * inv(P) * Bt )
	// Residuals vector V
	TVector V(nbObs);
	V = S * (A * solution + W);

	//--------------- Sigma 0 a posteriri ---------------//
	sigmaZero2Aposteriori = V.transpose() * Pv * V;
	if (nbEq + nbCnstr != nbUnk)
		sigmaZero2Aposteriori /= (nbEq - nbUnk + nbCnstr); // NB Redundancy: Takes into account the number of constraints!
	else
		fError += "Number of equations + constraints equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk, nbCnstr);
	rm->setSigmaZeroLimits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	// ----------Covariance Matrices-----------//

	TSparseMatrix Qxx_big(nbUnk + nbCnstr, nbUnk + nbCnstr);
	TSparseMatrix Qxx(nbUnk, nbUnk);

	// use Cholesky decomposition if nbCnstr=0, otherwise use LU as positive definiteness may be violated
	if (!TSparseUtils::inverse(NBig, Qxx_big, (nbCnstr == 0)))
	{
		logCritical() << "The normal matrix NBig could not be inverted!";
		return false;
	}
	Qxx = Qxx_big.topLeftCorner(nbUnk, nbUnk);

	// the full parameter covariance matrix, blown up to the full parameter set (always needed)
	rm->setUnkCovarMtrx(rm->blowUpParCovarianceMatrix(Qxx, im->getActiveParIndices()));

	//--------------- Residual covariance matrix (optional) ---------------//
	// Qvv and its blow-up are the dominant cost of this routine and are only needed for the
	// reliability statistics. Callers that only require parameter precisions (e.g. the monitoring
	// API) pass computeObsCovar = false to skip it.
	if (computeObsCovar)
	{
		TSparseMatrix Qvv(nbObs, nbObs);
		if (im->getSecondDgnBlockDiagStatus())
		{ // formula with simplifications if B is invertible Qvv = inv(P) - invB*A*Qxx*At*invBT
			TDenseMatrix QxxATinvBT(nbUnk, nbObs);
			TSparseMatrix invBA(nbObs, nbUnk);
			const TSparseMatrix &invB = im->getSecondDgnBlockDiagInvMtrx(masked);
			invBA = invB * A;
			QxxATinvBT = Qxx * invBA.transpose();
			Qvv = InvPv - invBA * QxxATinvBT;
		}
		else
		{
			// general formula
			Qvv = -S * B * InvPv - S * A * Qxx * A.transpose() * S.transpose();
		}
		// the full residual covar matrix
		rm->setResCovarMtrx(rm->blowUpObsCovarianceMatrix(Qvv, im->getActiveObsIndices()));
	}

	// full residuals, masked obs will have residual 0 per definition (always needed)
	rm->setResidualsVect(im->blowUpResiduals(V));
	return true;
}
