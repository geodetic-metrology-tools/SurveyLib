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
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnInvMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");
	
	const TSparseMatrix& A = *im->getFirstDgnMtrx();	
	const TSparseMatrix& invB = *im->getSecondDgnInvMtrx();
	const TSparseMatrix& InvPv = *im->getWeightInvMtrx();
	const TSparseMatrix& Pv = *im->getWeightMtrx();
	const TVector & W = im->getMisclosureVctr(); // W : vector of misclosures

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();

	// calculate intermediate matrix invN1 = inv ( B * inv(P) * Bt )
	TSparseMatrix invN1(nbEq, nbEq);
	invN1 = invB.transpose()*Pv*invB;

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

	if (inputMtr->getFirstDgnMtrx() == nullptr || inputMtr->getSecondDgnMtrx() == nullptr || inputMtr->getSecondDgnInvMtrx() == nullptr || inputMtr->getWeightMtrx() == nullptr || inputMtr->getWeightInvMtrx() == nullptr ||
		rm->getSolutionVectByConst() == nullptr || rm->getResidualsVectByConst() == nullptr || rm->getResCovarMtrxByConst() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix &A = *inputMtr->getFirstDgnMtrx();
	const TSparseMatrix &B = *inputMtr->getSecondDgnMtrx();
	const TSparseMatrix &invB = *inputMtr->getSecondDgnInvMtrx();
	const TSparseMatrix &Pv = *inputMtr->getWeightMtrx();
	const TSparseMatrix &InvPv = *inputMtr->getWeightInvMtrx();
	const TVector & W = inputMtr->getMisclosureVctr();

	const TVector & solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix & N2 = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	// Calculate invN1 = inv( B * inv(Pv) * Bt ),  matrix dimensions (nEq,nEq)
	TSparseMatrix invN1(nbEq, nbEq);
	invN1 = invB.transpose()*Pv*invB;


	//--------------- Residuals ---------------//
	TVector V(nbObs);
	V = -invB * (A * solution + W);  // vector dimension = nbObs

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
	// GKA (28/10/2019): Try Cholesky first enabled for the computation of precisions in Chaba 
	TSparseMatrix Qxx(nbUnk, nbUnk);
	if (!TSparseUtils::inverse(N2, Qxx,true))
		return false;

	// Variance-covariance matrix of the observation residues ( dimension nObs * nObs )

	TSparseMatrix Qvv(nbObs, nbObs);
	TSparseMatrix invBA = invB*A;
	TDenseMatrix QAinvBT = Qxx *invBA.transpose();
	Qvv = InvPv -  invBA*QAinvBT;
	
	// Copies the matrices into the members of the TResultsMatrices object
	rm->setResCovarMtrx(Qvv);
	rm->setUnkCovarMtrx(Qxx);
	rm->setResidualsVect(V);

	return true;
}
