#include "TLSCombinedMtdComputer.h"
#include "TLSResultsMatrices.h"
#include "TLSInputMatrices.h"
#include "TSparseMatrix.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Eigen/LU>


TLSCombinedMtdComputer::TLSCombinedMtdComputer()
	:count(1)
{//default constructor
}


TLSCombinedMtdComputer::~TLSCombinedMtdComputer()
{//destructor
}

bool TLSCombinedMtdComputer::computeResults(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	bool result = false;
	int nbCnstr = im->getNbrConstraints();
	if(rm->getSolutionVectByConst()->size() != 0)
	{
		if(nbCnstr == 0)
		{
			result = computeResultsMatrices(im, rm);
		}
		else
		{
			//result = computeFreeResultsMtrs(im, rm);
			fError = "Free network calculation not yet implemented!";
			result = false;
		}
	}
	else
	{//pas d'inconnue
		result = true;
	}
	return result;
}


//!Computes the results matrices
bool TLSCombinedMtdComputer::computeResultsMatrices(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	//test if we do not have a 'nullpointer' in a case that the matrices are not initialize
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");
	
	const TSparseMatrix& A = *im->getFirstDgnMtrx();	
	const TSparseMatrix& B = *im->getSecondDgnMtrx();
	const TSparseMatrix& InvPv = *im->getWeightInvMtrx();
	const TVector & W = im->getMisclosureVctr(); // W : vector of misclosures

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();

	//calculate intermediate matrix invN1 = inv ( B * inv(P) * Bt )
	TSparseMatrix invN1(nbEq, nbEq);
	if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1, true))
		return false;

	//Normal matrix N2 = At * inv(N1) * A
	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = A.transpose() * invN1 * A;

	// VP = At * inv(N1) * W
	TVector VP(nbUnk);
	VP = A.transpose() * invN1 * W;

	TVector solution(nbUnk);
	if (!TSparseUtils::solveUnique(N2, -VP, solution))
		return false;

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(N2);
	rm->setSolutionVect(solution);

	return true;
}


bool TLSCombinedMtdComputer::calcResidusAndVarCovMatrix(const TLSInputMatrices* inputMtr, TLSResultsMatrices* rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = inputMtr->getNbrUnknowns();
	int nbObs = inputMtr->getNbrObservations();
	int nbEq = inputMtr->getNbrEquations();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	if (inputMtr->getFirstDgnMtrx() == nullptr || inputMtr->getSecondDgnMtrx() == nullptr || inputMtr->getWeightMtrx() == nullptr || inputMtr->getWeightInvMtrx() == nullptr ||
		rm->getSolutionVectByConst() == nullptr || rm->getResidualsVectByConst() == nullptr || rm->getResCovarMtrxByConst() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix &A = *inputMtr->getFirstDgnMtrx();
	const TSparseMatrix &B = *inputMtr->getSecondDgnMtrx();
	const TSparseMatrix &Pv = *inputMtr->getWeightMtrx();
	const TSparseMatrix &InvPv = *inputMtr->getWeightInvMtrx();
	const TVector & W = inputMtr->getMisclosureVctr();

	const TVector & solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix & N2 = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	// Calculate invN1 = inv( B * inv(Pv) * Bt ),  matrix dimensions (nEq,nEq)
	TSparseMatrix invN1(nbEq, nbEq);
	if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1))
		return false;

	//Calculate S = Inv(P) * Bt * inv(N1)
	TSparseMatrix S(nbObs, nbEq);
	S = -InvPv * B.transpose() * invN1;

	//--------------- Residuals ---------------//
	TVector V(nbObs);
	V = S * (A * solution + W);  // vector dimension = nbObs

	//--------------- Sigma 0 a posteriri ---------------//
	sigmaZero2Aposteriori = V.transpose() * Pv * V;
	if (nbObs != nbUnk)
		sigmaZero2Aposteriori /= (nbObs - nbUnk);
	else
		fError += "Number of equations equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk);
	rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	//--------------- Variance-Covariance matrices ---------------//
	// Variance-covariance matrix of the unknowns Qxx = inv( N2 );
	TSparseMatrix Qxx(nbUnk, nbUnk);
	if (!TSparseUtils::inverse(N2, Qxx))
		return false;

	// Variance-covariance matrix of the observation residues ( dimension nObs * nObs )
	// GKA (26/09/2019) : Qvv is changed from Qvv = S * B * InvPv - S * A * Qxx * A.transpose() * S.transpose() to the actual solution: see "a synthesis of recent advances in the method of least squares" from Krakiwsky

	TSparseMatrix Qvv(nbObs, nbObs);
	Qvv = InvPv * B.transpose() * invN1 * B * InvPv - InvPv * B.transpose() * invN1 * A * Qxx * A.transpose() * invN1 * B * InvPv;

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setResCovarMtrx(Qvv);
	rm->setUnkCovarMtrx(Qxx);
	rm->setResidualsVect(V);

	return true;
}
