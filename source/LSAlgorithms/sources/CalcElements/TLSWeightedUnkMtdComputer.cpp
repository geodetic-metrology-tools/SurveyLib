#include "TLSWeightedUnkMtdComputer.h"
#include "TLSResultsMatrices.h"
#include "TLSInputMatrices.h"
#include "TSparseMatrix.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Eigen/LU>


TLSWeightedUnkMtdComputer::TLSWeightedUnkMtdComputer()
	: count(1)
{//default constructor
}


TLSWeightedUnkMtdComputer::~TLSWeightedUnkMtdComputer()
{//destructor
}

bool TLSWeightedUnkMtdComputer::computeResults(TLSInputMatrices* im, TLSResultsMatrices* rm)
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
bool TLSWeightedUnkMtdComputer::computeResultsMatrices(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	//test if we do not have a 'nullpointer' in a case that the matrices are not initialize
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix & A = *im->getFirstDgnMtrx();
	const TSparseMatrix & B = *im->getSecondDgnMtrx();
	const TSparseMatrix & invB = *im->getSecondDgnInvMtrx();
	const TSparseMatrix & InvPv = *im->getWeightInvMtrx();
	const TSparseMatrix & Pv = *im->getWeightMtrx();
	const TSparseMatrix & Px = *im->getWeightUnkMtrx(); 
	const TVector & W = im->getMisclosureVctr(); 

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();

	// Calculates invN1 = inv(B * inv(Pv) * Bt)
	TSparseMatrix invN1(nbEq, nbEq);
	invN1 = invB.transpose() * Pv * invB;

	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = A.transpose() * invN1 * A + Px;

	TVector VP(nbUnk); // V = At * inv(N1) * W
	VP = A.transpose() * invN1 * W;

	TVector solution(nbUnk);
	TSparseUtils::solveUnique(N2, -VP, solution);
	
	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix(N2);
	rm->setSolutionVect(solution);

	return true;
}


bool TLSWeightedUnkMtdComputer::calcResidusAndVarCovMatrix(const TLSInputMatrices* inputMtr,	TLSResultsMatrices* rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = inputMtr->getNbrUnknowns();
	int nbObs = inputMtr->getNbrObservations();
	int nbEq = inputMtr->getNbrEquations();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	const TSparseMatrix & A = *inputMtr->getFirstDgnMtrx();
	const TSparseMatrix & B = *inputMtr->getSecondDgnMtrx();
	const TSparseMatrix & invB = *inputMtr->getSecondDgnInvMtrx();
	const TSparseMatrix & Pv = *inputMtr->getWeightMtrx();
	const TSparseMatrix & InvPv = *inputMtr->getWeightInvMtrx();
	const TVector & W = inputMtr->getMisclosureVctr();

	const TVector & solution = *rm->getSolutionVectByConst(); // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix & N2 = *rm->getNormalMatrixByConst(); // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	TSparseMatrix invN1(nbEq, nbEq);
	invN1 = invB.transpose() * Pv * invB;

	// Residues V on observations
	TVector V(nbObs);
	V = -InvPv * B.transpose() * invN1 * (A * solution + W);

	// Sigma 0 a posteriri
	sigmaZero2Aposteriori = V.transpose() * Pv * V;
	if (nbObs != nbUnk)
		sigmaZero2Aposteriori /= (nbObs - nbUnk);
	else
		fError += "Number of equations equals number of unknowns, causes zero division!";
	rm->setSigmaZero2(sigmaZero2Aposteriori);
	struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk);
	rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

	// Intermediate matrices
	TSparseMatrix Id(nbEq, nbEq);
	Id.setIdentity();

	TSparseMatrix invN2(nbUnk, nbUnk);
	if (!TSparseUtils::inverse(N2, invN2))
		return false;

	TSparseMatrix MP2(nbObs, nbEq);
	MP2 = InvPv * B.transpose() * invN1;

	TSparseMatrix MP(nbEq, nbEq);
	MP = Id - A * invN2 * A.transpose() * invN1;

	// Unknowns variance-covariance matrix
	TSparseMatrix Qxx(nbUnk, nbUnk);
	Qxx = invN2 * A.transpose() * invN1 * A * invN2.transpose();

	// Observation residues variance-covariance matrix
	TSparseMatrix Qvv(nbObs, nbObs);
	Qvv = MP2 * MP * B * InvPv * B.transpose() * MP.transpose() * MP2.transpose();

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setUnkCovarMtrx(Qxx);
	rm->setResCovarMtrx(Qvv);
	rm->setResidualsVect(V);

	return true;
}
