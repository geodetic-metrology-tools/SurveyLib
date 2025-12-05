// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLSUniversalMtdComputer.h"

#include <vector>

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
	if (!(rm->getSolutionVectByConst()) || !(im->isInitialized))
	{
		logCritical() << "Some of the design matrices are not initialized!";
		return false;
	}

	const TSparseMatrix &A = im->getFirstDgnMtrx();
	const TVector &W = im->getMisclosureVctr(); // W : Misclosures vector ("fermetures")
	const TSparseMatrix &A2 = im->getCnstrFirstDgnMtrx(); // A2 : First design matrix part related to constraints only
	const TVector &W2 = im->getCnstrMisclosureVctr(); // W2 : Misclosures vector part related to constraints only

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();

	// set invN1
	TSparseMatrix invN1(nbEq, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		const TSparseMatrix &Pv = im->getWeightMtrx();
		const TSparseMatrix &invB = im->getSecondDgnBlockDiagInvMtrx();
		invN1 = invB.transpose() * Pv * invB;
	}
	else
	{ // if B is not block diagonal, invN1 needs to be computed via an explicit inversion
	  // B*invPv*BT is symmetric and positive definite so LDLT can be used
		const TSparseMatrix &B = im->getSecondDgnMtrx();
		const TSparseMatrix &InvPv = im->getWeightInvMtrx();
		if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1, true))
		{
			logCritical() << "Matrix B*inv(Pv)*transpose(B) could not be inverted!";
			return false;
		}
		// copy invN1 to resultmatrices only if B is not block diagonal, otherwise it is not needed in the calcRes method
		rm->setInvN1Matrix(invN1);
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
	// regularize the primal part only
	double regTerm = 1e-6;
	for (int k = 0; k < N2.outerSize(); ++k)
	{
		for (TSparseMatrix::InnerIterator it(N2, k); it; ++it)
		{
			if (it.row() == it.col())
			{
				coeffs.push_back(TTriplet(it.row(), it.col(), it.value() + regTerm));
			}
			else
				coeffs.push_back(TTriplet(it.row(), it.col(), it.value()));
		}
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

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(NBig);
	rm->setSolutionVect(solution);

	return true;
}

bool TLSUniversalMtdComputer::calcResidusAndVarCovMatrix(const TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = im->getNbrUnknowns();
	int nbObs = im->getNbrObservations();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	if (!(rm->getSolutionVectByConst()) || !(rm->getResidualsVectByConst()) || !(rm->getZReliabilityVectByConst()) || !(rm->getResCovarDiagByConst()))
		throw std::runtime_error("Some of the result matrices are not initialized!");

	const TSparseMatrix &A = im->getFirstDgnMtrx();
	const TSparseMatrix &B = im->getSecondDgnMtrx();
	const TSparseMatrix &InvPv = im->getWeightInvMtrx();

	TSparseMatrix S(nbObs, nbEq);
	if (im->getSecondDgnBlockDiagStatus())
	{
		// if B is block-diagonal, the S formula simplifies to -invB
		S = -(im->getSecondDgnBlockDiagInvMtrx());
	}
	else
	{
		if (!(rm->getInvN1MatrixByConst()))
		{
			throw std::runtime_error("The matrix invN1 is not initialized!");
		}
		const TSparseMatrix &invN1 = *rm->getInvN1MatrixByConst(); // NB: invN1 will NOT be recalculated here (just taken from previous results!)
		S = -InvPv * B.transpose() * invN1;
	}
	const TSparseMatrix &Pv = im->getWeightMtrx();
	const TVector &W = im->getMisclosureVctr();
	const TVector &solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix &NBig = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

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
	// test if Pv is diagonal. Exploiting that we know it is already block diagonal and invertible.
	bool PvIsDiag = (Pv.nonZeros() == Pv.rows());
	TSparseMatrix Qxx(nbUnk, nbUnk);
	TVector QvvDiag(nbObs);
	TVector ZReliability(nbObs);

	// prepare the extra infos for the inversion
	TSparseUtils::InverseExtras inversionExtras;
	// in any case we only need the Qxx part
	inversionExtras.topLeftSize = nbUnk;
	// only store a band around the diagonal in the big File version
	inversionExtras.bandWidth = 7;

	if (PvIsDiag)
	{
		// during the Qxx computation we want also the diagonal of M Qxx MT
		TSparseMatrix M = S * A;
		inversionExtras.M = &M;
		// prepare the resulting diagonal
		TVector diagMQxxMT = TVector::Zero(nbObs);
		inversionExtras.diag_MinvMT = &diagMQxxMT;
		// do the inversion
		if (!TSparseUtils::inverse(NBig, Qxx, (nbCnstr == 0), inversionExtras))
		{
			logCritical() << "The normal matrix NBig could not be inverted!";
			return false;
		}
		// set the diagonal of Qvv
		if (im->getSecondDgnBlockDiagStatus())
		{
			QvvDiag = InvPv.diagonal() - diagMQxxMT;
		}
		else
		{
			TSparseMatrix SBInvPv = (S * B * InvPv);
			QvvDiag = (SBInvPv).diagonal() - diagMQxxMT;
		}
		// we can set the ZReliability cheaply here because Pv is diagonbal and Z=diag(Qvv * Pv)=diag(Qvv)*diag(Pv) holds
		ZReliability = QvvDiag.cwiseProduct(Pv.diagonal());
	}
	else
	{
		// compute Qxx without extra requests beside the topleft dimension
		if (!TSparseUtils::inverse(NBig, Qxx, (nbCnstr == 0), inversionExtras))
		{
			logCritical() << "The normal matrix NBig could not be inverted!";
			return false;
		}
		if (im->getSecondDgnBlockDiagStatus())
		{
			// general formula, because we need the full Qvv for the ZReliability vector computation (expensive because of big matrix multiplication with dense Qxx)
			TSparseMatrix Qvv = -S * B * InvPv - S * A * Qxx * A.transpose() * S.transpose();
			QvvDiag = Qvv.diagonal();
			// because Pv is not diagonal, we have to do the full matrix multiplication here to get the the ZReliability vector
			TSparseMatrix QvvPv = Qvv * Pv;
			ZReliability = QvvPv.diagonal();
		}
	}

	// Copies the data into the members of the TResultsMatrices object
	rm->setResCovarDiag(QvvDiag);
	rm->setZReliabilityVect(ZReliability);
	rm->setUnkCovarMtrx(Qxx);
	rm->setResidualsVect(V);
	return true;
}
