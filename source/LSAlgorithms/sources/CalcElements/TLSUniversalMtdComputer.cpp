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
	int nbCnstr = im->getNbrConstraints();
	if (rm->getSolutionVectByConst()->size() != 0)
	{
		return computeResultsMatrices(im, rm);
	}

	return false;
}

bool TLSUniversalMtdComputer::computeResultsMatrices(TLSInputMatrices *im, TLSResultsMatrices *rm)
{
	// test if we do not have a 'nullpointer' in a case that the matrices are not initialized
	if (!(im->getFirstDgnMtrx()) || !(im->getSecondDgnMtrx()) || !(im->getSecondDgnInvMtrx()) || !(im->getWeightMtrx()) || !(im->getCnstrFirstDgnMtrx())
		|| !(rm->getSolutionVectByConst()))
	{
		logCritical() << "Some of the design matrices are not initialized!";
		return false;
	}

	const TSparseMatrix &A = *im->getFirstDgnMtrx();
	const TSparseMatrix &invB = *im->getSecondDgnInvMtrx();
	const TSparseMatrix &Pv = *im->getWeightMtrx();
	const TVector &W = im->getMisclosureVctr(); // W : Misclosures vector ("fermetures")
	const TSparseMatrix &A2 = *im->getCnstrFirstDgnMtrx(); // A2 : First design matrix part related to constraints only
	const TVector &W2 = im->getCnstrMisclosureVctr(); // W2 : Misclosures vector part related to constraints only

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();

	// Calculate invN1 = inv( B*inv(Pv)*transpose(B) ),  matrix dimensions (nEq,nEq)
	TSparseMatrix invN1(nbEq, nbEq);
	invN1 = invB.transpose() * Pv * invB;

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

	// use Cholesky decomposition if nbCnstr=0, otherwise LU as positive definiteness may be violated
	if (!TSparseUtils::solveUnique(NBig, -VBig, solutionExt, (nbCnstr == 0), (nbCnstr == 0)))
	{
		logCritical() << "No solution could be found when solving equation system: Nbig * dX = -VBig (extended matrices with conditions)";
		return false;
	}

	TVector solution(nbUnk);
	solution = solutionExt.head(nbUnk);

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(N2);
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

	if (!(im->getFirstDgnMtrx()) || !(im->getSecondDgnInvMtrx()) || !(im->getWeightMtrx()) || !(im->getWeightInvMtrx()) || !(im->getCnstrFirstDgnMtrx())
		|| !(rm->getSolutionVectByConst()) || !(rm->getResidualsVectByConst()) || !(rm->getResCovarMtrxByConst()))
		throw std::runtime_error("Some of the design matrices are not initialized!");

	const TSparseMatrix &A = *im->getFirstDgnMtrx();
	const TSparseMatrix &invB = *im->getSecondDgnInvMtrx();
	const TSparseMatrix &Pv = *im->getWeightMtrx();
	const TSparseMatrix &InvPv = *im->getWeightInvMtrx();
	const TVector &W = im->getMisclosureVctr();
	const TSparseMatrix &A2 = *im->getCnstrFirstDgnMtrx();

	const TVector &solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix &N2 = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	//--------------- Residuals ---------------//
	// Calculate intermediate matrix
	// S = - inv(P) * Bt *inv( B * inv(P) * Bt )
	// can be simplified to S=-invB

	TSparseMatrix invN1(nbObs, nbObs);
	invN1 = invB.transpose() * Pv * invB;

	// Residuals vector V
	TVector V(nbObs);
	V = -invB * (A * solution + W);

	//--------------- Sigma 0 a posteriri ---------------//
	sigmaZero2Aposteriori = V.transpose() * Pv * V;
	if (nbObs + nbCnstr != nbUnk)
		sigmaZero2Aposteriori /= (nbObs - nbUnk + nbCnstr); // NB Redundancy: Takes into account the number of constraints!
	else
		fError += "Number of equations equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk);
	rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	//--------------- unknown covariance matrix ---------------//

	// Builds extended matrix NBig = (N2, A2t
	//                                A2, 0  )
	TSparseMatrix NBig(nbUnk + nbCnstr, nbUnk + nbCnstr);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(N2.nonZeros() + 2 * A2.nonZeros());

	// Fill in the N2 part (normal matrix)
	for (int k = 0; k < N2.outerSize(); ++k)
		for (TSparseMatrix::InnerIterator it(N2, k); it; ++it)
			coeffs.push_back(TTriplet(it.row(), it.col(), it.value()));

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

	// Inverse NBig: Changed the way the extended matrix is inverted (similar method than during the iterative adjustment steps!!!)
	TSparseMatrix Qxx_big(nbUnk + nbCnstr, nbUnk + nbCnstr);

	// ----------Normal method-----------

	TSparseMatrix Qxx(nbUnk, nbUnk);

	// use Cholesky decomposition if nbCnstr=0, otherwise use LU as positive definiteness may be violated
	if (!TSparseUtils::inverse(NBig, Qxx_big, (nbCnstr == 0), (nbCnstr == 0)))
	{
		logCritical() << "The normal matrix NBig could not be inverted!";
		return false;
	}
	Qxx = Qxx_big.topLeftCorner(nbUnk, nbUnk);
	//--------------- Residual covariance matrix: Qvv = inv(P) - invB*A*Qxx*At*invBT ---------------//
	TSparseMatrix Qvv(nbObs, nbObs);
	TDenseMatrix QxxATinvBT(nbUnk, nbObs);
	TSparseMatrix invBA(nbObs, nbUnk);
	invBA = invB * A;
	QxxATinvBT = Qxx * invBA.transpose();
	Qvv = InvPv - invBA * QxxATinvBT;
	// Copies the matrices into the members of the TResultsMatrices object
	rm->setUnkCovarMtrx(Qxx);
	rm->setResCovarMtrx(Qvv);
	rm->setResidualsVect(V);
	return true;
}
