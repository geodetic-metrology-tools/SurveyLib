//
// TLSParametricMtdComputer.cpp : implementation file
// class for a least squares computer producing the results matrices
// using the parametric method (case where 2nd dgn mtrx = -I)
//


#include "TLSParametricMtdComputer.h"
#include "TLSResultsMatrices.h"
#include "TLSInputMatrices.h"
#include "TSparseMatrix.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Eigen/LU>
//#include <Eigen/Cholesky>

//////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////
TLSParametricMtdComputer::TLSParametricMtdComputer()
	:count(1)
{//default constructor
}


TLSParametricMtdComputer::~TLSParametricMtdComputer()
{//destructor
}



bool TLSParametricMtdComputer::computeResults(TLSInputMatrices* im , TLSResultsMatrices* rm)
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


////////////////////////////////////////////////////////////////
//COMPUTES THE RESULTS MATRICES
////////////////////////////////////////////////////////////////
bool TLSParametricMtdComputer::computeResultsMatrices(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	//test if we do not have a 'nullpointer' in a case that the matrices are not initialize
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	int nbUnk = im->getNbrUnknowns();

	const TSparseMatrix & A = *im->getFirstDgnMtrx();
	const TSparseMatrix & Pv = *im->getWeightMtrx();
	const TVector & W = im->getMisclosureVctr(); // "Fermetures"
	
	// Calculates the normal matrix and re-sets it to the main TLSResultsMatrices object
	TSparseMatrix N(nbUnk, nbUnk);
	N = A.transpose() * Pv * A;

	TVector solution(nbUnk);
	if (!TSparseUtils::solveUnique(N, -A.transpose() * Pv * W, solution))  // solution: X = - (At*P*A)-1 * (At*P*F) where P = weights, F = misclosures ("fermetures")
		return false;
	
	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(N);
	rm->setSolutionVect(solution);
	
	return true;
}



bool TLSParametricMtdComputer::calcResidusAndVarCovMatrix(const TLSInputMatrices* inputMtr, TLSResultsMatrices* rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = inputMtr->getNbrUnknowns();
	int nbObs = inputMtr->getNbrObservations();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	const TSparseMatrix& A = *inputMtr->getFirstDgnMtrx();
	const TSparseMatrix& Pv = *inputMtr->getWeightMtrx();
	const TSparseMatrix& InvPv = *inputMtr->getWeightInvMtrx();
	const TVector&       W = inputMtr->getMisclosureVctr();  // "Fermetures"

	const TVector& solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix& N = *rm->getNormalMatrixByConst();  // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	//--------------- Residuals ---------------//
	// V = A * X + W, where W = misclosures ("fermetures")
	TVector V(nbObs);
	V = (A * solution + W);

	//--------------- Sigma 0 a posteriri ---------------//
	// s0 = (Vt*P*V)/r   where r = redundancy = n - u 
	sigmaZero2Aposteriori = V.transpose() * Pv * V;
	if (nbObs != nbUnk)
		sigmaZero2Aposteriori /= (nbObs - nbUnk);
	else
		fError += "Number of equations equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk);
	rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	//--------------- Unknowns covariance matrix : Qxx = inv(N) ---------------//
	TSparseMatrix Qxx(nbUnk, nbUnk);
	if (!TSparseUtils::inverse(N, Qxx, true))
		return false;

	//--------------- Residual covariance matrix: Qvv = inv(P) - A*Qxx*At ---------------//
	TSparseMatrix Qvv(nbObs, nbObs);
	TDenseMatrix QxxAT(nbUnk, nbObs);
	QxxAT = Qxx * A.transpose();
	Qvv = InvPv - A * QxxAT;

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setUnkCovarMtrx(Qxx);
	rm->setResCovarMtrx(Qvv);
	rm->setResidualsVect(V);

	return true;
}

////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////
