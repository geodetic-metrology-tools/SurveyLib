#include "TLSCnstMtdComputer.h"
#include "TLSResultsMatrices.h"
#include "TLSInputMatrices.h"
#include "TSparseMatrix.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Eigen/LU>
#include <Eigen/SparseQR>
#include <Logger.hpp>


TLSCnstMtdComputer::TLSCnstMtdComputer()
	:count(1)
{//default constructor
}


TLSCnstMtdComputer::~TLSCnstMtdComputer()
{//destructor
}

bool TLSCnstMtdComputer::computeResults(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	bool result = false;
	int nbCnstr = im->getNbrConstraints();
	if (rm->getSolutionVectByConst()->size() != 0)
	{
		if (nbCnstr != 0)
		{
			//result = computeResultsMatrices(im, rm);
			result = computeFreeResultsMtrs(im, rm);
		}
		else
		{
			result = computeResultsMatrices(im, rm);
			fError = "We have not necessary constraints!";
			result = false;
		}
	}

	return result;
}



//!Computes the results matrices
bool TLSCnstMtdComputer::computeResultsMatrices(TLSInputMatrices* im, TLSResultsMatrices* rm)
{ 
	// Test if we do not have a 'nullpointer' in a case that the matrices are not initialize
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix& A = *im->getFirstDgnMtrx();
	const TSparseMatrix& B = *im->getSecondDgnMtrx();
	const TSparseMatrix& InvPv = *im->getWeightInvMtrx();
	const TVector & W = im->getMisclosureVctr();          // W : Misclosure vector ("fermetures")
	const TSparseMatrix& A2 = *im->getCnstrFirstDgnMtrx();     // A2 : First design matrix related to constraints 
	const TVector & W2 = im->getCnstrMisclosureVctr();         // W2 : Misclosures vector related to constraints 

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();

	// Calculate invN1 = inv( B*inv(Pv)*transpose(B) ),  matrix dimensions (nbEq,nbEq)
	TSparseMatrix invN1(nbEq, nbEq);
	if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1))
		return false;

	// Calculate Normal matrix N2 = At * inv( B * inv(P) * Bt ) * A
	TSparseMatrix N2(nbUnk, nbUnk);
	N2 = A.transpose() * invN1 * A;

	// Corresponding vector VP = At * inv( B * inv(P) * Bt ) * W
	TVector VP(nbUnk);
	VP = A.transpose() * invN1  * W;  

	// Inverse invN2 = inv( N2 ) = inv( At * inv( B * inv(P) * Bt ) * A )
	TSparseMatrix invN2(nbUnk, nbUnk);
	if (!TSparseUtils::inverse(N2, invN2))
		return false;

	//VP2 = W2 - transpose(A2)*inv(N2)*VP  
	TVector VP2(nbCnstr);
	VP2 = W2 - A2 * invN2 * VP;

	//Intermediate matrix N3 = A2 * inv(N2) * transpose(A2)
	TSparseMatrix N3(nbCnstr, nbCnstr); 
	N3 = A2 * invN2 * A2.transpose();

	// Intermediate matrix InvN3VP2 = inv(N3)*VP2
	TVector InvN3VP2(nbCnstr);
	if (!TSparseUtils::solveUnique(N3, VP2, InvN3VP2))
		return false;

	// rightPart = A2.transpose()*inv(N3)*VP2 + VP
	TVector rightPart = A2.transpose() * InvN3VP2 + VP;

	// Solution vector: solution = - inv(N2) * rightPart
	TVector solution(nbUnk);
	solution = -invN2 * rightPart;

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix( N2 );
	rm->setSolutionVect( solution );
	return true;
}



bool TLSCnstMtdComputer::computeFreeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	//test if we do not have a 'nullpointer' in a case that the matrices are not initialize
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
 		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix& A = *im->getFirstDgnMtrx();
	const TSparseMatrix& B = *im->getSecondDgnMtrx();
	const TSparseMatrix& InvPv = *im->getWeightInvMtrx();
	const TVector&       W = im->getMisclosureVctr();           // W : Misclosures vector ("fermetures")
	const TSparseMatrix& A2 = *im->getCnstrFirstDgnMtrx(); // A2 : First design matrix part related to constraints only
	const TVector&       W2 = im->getCnstrMisclosureVctr();     // W2 : Misclosures vector part related to constraints only

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();
	int nbCnstr = im->getNbrConstraints();
	
	// Calculate invN1 = inv( B*inv(Pv)*transpose(B) ),  matrix dimensions (nEq,nEq)
	TSparseMatrix invN1(nbEq, nbEq);
	if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1,false,false))
	{ 
		logCritical() << "Matrix B*inv(Pv)*transpose(B) could not be inverted!";
		return false;
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
	for (int k = 0; k<N2.outerSize(); ++k)
		for (TSparseMatrix::InnerIterator it(N2, k); it; ++it)
			coeffs.push_back(TTriplet(it.row(), it.col(), it.value()));

	// Fill the A2 and A2T
	for (int k = 0; k<A2.outerSize(); ++k)
		for (TSparseMatrix::InnerIterator it(A2, k); it; ++it)
		{
			coeffs.push_back(TTriplet(it.row() + N2.rows(), it.col(), it.value())); //A2
			coeffs.push_back(TTriplet(it.col(), it.row() + N2.cols(), it.value())); // A2T
		}
	NBig.setFromTriplets(coeffs.begin(), coeffs.end());

	// Extended vector: appends W2 (constraints misclosures) to the calculated At*inv(N1)*W  vector 
	TVector VBig(nbUnk + nbCnstr);
	VBig << A.transpose()*invN1* W, W2;  

	// Calculates solution NBig * X = -VBig and keeps only the part corresponding to adjusted parameters
	TVector solutionExt(nbUnk + nbCnstr);

	//	if (!TSparseUtils::solveUnique(NBig, -VBig, solutionExt))
	if (!TSparseUtils::solveUnique(NBig, -VBig, solutionExt, false, false))
	{
		logCritical() << "No solution could be found when solving equation system: Nbig * dX = -VBig (extended matrices with conditions)";
		return false;
	}
	

	TVector solution(nbUnk);
	solution = solutionExt.head(nbUnk);

	// Copies the matrices into the members of the TResultsMatrices object
	rm->setNormalMatrix( N2 );
	rm->setSolutionVect( solution );

	return true;
}

//
// for LIBR constraint, same equations as TCombinedMtdComputer
//
bool TLSCnstMtdComputer::calcResidusAndVarCovMatrix(const TLSInputMatrices* inputMtr, TLSResultsMatrices* rm)
{
	if (!fError.empty())
		return false;

	int nbUnk = inputMtr->getNbrUnknowns();
	int nbObs = inputMtr->getNbrObservations();
	int nbEq = inputMtr->getNbrEquations();
	int nbCnstr = inputMtr->getNbrConstraints();
	TReal sigmaZero2Aposteriori = LITERAL(0.0);

	if (inputMtr->getFirstDgnMtrx() == nullptr || inputMtr->getSecondDgnMtrx() == nullptr || inputMtr->getWeightMtrx() == nullptr || inputMtr->getWeightInvMtrx() == nullptr ||
		rm->getSolutionVectByConst() == nullptr || rm->getResidualsVectByConst() == nullptr || rm->getResCovarMtrxByConst() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix& A = *inputMtr->getFirstDgnMtrx();
	const TSparseMatrix& B = *inputMtr->getSecondDgnMtrx();
	const TSparseMatrix& Pv = *inputMtr->getWeightMtrx();
	const TSparseMatrix& InvPv = *inputMtr->getWeightInvMtrx();
	const TVector&       W = inputMtr->getMisclosureVctr();
	const TSparseMatrix& A2 = *inputMtr->getCnstrFirstDgnMtrx();

	const TVector&       solution = *rm->getSolutionVectByConst();  // NB: Solution vector will NOT be recalculated here (just taken from previous results!)
	const TSparseMatrix& N2 = *rm->getNormalMatrixByConst();        // NB: Normal matrix will NOT be recalculated here (just taken from previous results!)

	//--------------- Residuals ---------------//
	// Calculate intermediate matrix
	// S = - inv(P) * Bt *inv( B * inv(P) * Bt )

	TSparseMatrix invN1(nbObs, nbObs);
	if (!TSparseUtils::inverse(B * InvPv * B.transpose(), invN1, false, false))
	{
		logCritical() << "Could not invert intermediate matrix N1 = B * InvPv * B.transpose()";
		return false;
	}
	TSparseMatrix S(nbObs, nbEq);
	S = -InvPv * B.transpose() * invN1;

	// Residuals vector V
	TVector V(nbObs);
	V = S * (A * solution + W);

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
	TSparseMatrix Qxx(nbUnk + nbCnstr, nbUnk + nbCnstr);

	// ----------Normal method-----------
	
	if (!TSparseUtils::inverse(NBig, Qxx, false, false))
	{
		logCritical() << "In LIBR calculation, the extended normal matrix NBig could not be inverted!";
		return false;
	}
	
	//--------------- Residual covariance matrix ---------------//
	// Intermediate matrix
	TSparseMatrix invN2(nbUnk, nbUnk);

	if (!TSparseUtils::inverse(N2, invN2, false, false))
	{
		// FRK (09/01/18): This matrix is theoretically NEVER invertible!!! => We should use the extended NBig matrix for that and define other formulas
		// GKA (26/09/2019) : Use of a LU decomposition to inverse the matrix, no need from the matrix to be invertible.
		logWarning() << "Could not invert normal matrix N2";
	}
	else
	{
		// FRK (09/01/18): needs STILL TO BE STUDIED for calculating variances on residual errors and related statistics !!!
		// See above remark!!!
		// GKA (26/09/2019) : Qvv is changed from Qvv = S * B * InvPv - S * A * invN2 * A.transpose() * S.transpose() to the actual solution: see "a synthesis of recent advances in the method of least squares" from Krakiwsky
		// according to literature: Qvv = InvPv * B.transpose() * invN1 * B * InvPv - InvPv * B.transpose() * invN1 * A * invN2 * A.transpose() * invN1 * B * InvPv;

		TSparseMatrix Qvv(nbObs, nbObs);
		Qvv = - S * B * InvPv - S * A * invN2 * A.transpose() * S.transpose();
		rm->setResCovarMtrx(Qvv);
	}
	
	// Copies the matrices into the members of the TResultsMatrices object
	rm->setUnkCovarMtrx(Qxx); // IMPORTANT NOTE: this variance-covariance matrix has a dimension of ( u + c, u + c ), where c = number of constraints, u = number of unknowns.
	rm->setResidualsVect(V);
	
	return true;
}
