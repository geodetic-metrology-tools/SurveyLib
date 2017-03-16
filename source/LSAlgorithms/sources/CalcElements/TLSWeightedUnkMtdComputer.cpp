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
	if(rm->getSolutionVctr()->size() != 0)
	{
		if(nbCnstr == 0)
		{
			result = computeResultsMtrs(im, rm);
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
bool TLSWeightedUnkMtdComputer::computeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	//test if we do not have a 'nullpointer' in a case that the matrices are not initialize
	if (im->getFirstDgnMtrx() == nullptr || im->getSecondDgnMtrx() == nullptr || im->getWeightInvMtrx() == nullptr)
		throw std::runtime_error("Any of the design matrices is not initialized!");

	const TSparseMatrix & A = *im->getFirstDgnMtrx();
	const TSparseMatrix & B = *im->getSecondDgnMtrx();
	const TSparseMatrix & InvPv = *im->getWeightInvMtrx();
	const TSparseMatrix & Px = *im->getWeightUnkMtrx(); 
	const TVector & misclV = im->getMisclosureVctr(); //W

	int nbUnk = im->getNbrUnknowns();
	int nbEq = im->getNbrEquations();

#ifdef _DEBUG
	//std::cout << "TLSCombinedCalculation::computeResultsMtrs, A=\n " << A << std::endl;
	//std::cout << "TLSCombinedCalculation::computeResultsMtrs, B=\n " << B << std::endl;
	//std::cout << "TLSCombinedCalculation::computeResultsMtrs, Pv1=\n " <<InvPv << std::endl;
	//std::cout << "TLSCombinedCalculation::computeResultsMtrs, Px=\n " <<Px << std::endl;
	//std::cout << "TLSCombinedCalculation::computeResultsMtrs, misclosure=\n " <<misclV << std::endl;
#endif

	//calculate N1 = B1*inv(Pv1)*transpose(B1)
	TSparseMatrix Btransposed = B.transpose();
	TSparseMatrix N1 = B * InvPv * Btransposed;

	//inverse N1
	Eigen::SimplicialLDLT<TSparseMatrix> chol( N1 );

	TSparseMatrix N2(nbUnk, nbUnk); //N2 = transpose(A1)*inv(N1)*A1 + Px
	TVector VP(nbUnk); //VPassage = transpose(A1)*inv(N1)*W

#ifdef _DEBUG
	std::cout << "TLSCombinedMtdComputer::computeResultsMtrs, det(N1)=\n " << chol.determinant() << std::endl;
#endif

	if(chol.info() != Eigen::Success)
	{
		// colesky did not work, try fullPiv
		typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMat;
		Eigen::FullPivLU<TMat> lu(N1);

		if (! lu.isInvertible()) {
			std::ostringstream foo;
			foo << "TLSCombinedMtdComputer::computeResultsMtrs:\n\tsolution failed.";
			fError += foo.str();
			return false;
		}

		TSparseMatrix AtInvN1(nbUnk, nbEq);
		TSparseMatrix *pAtInvN1 = &AtInvN1;
		*pAtInvN1 = A.transpose() * (lu.inverse());
		N2 = *pAtInvN1 * A + Px;
		rm->setIntermediateMatrix(N2);

		VP = *pAtInvN1 * misclV;
	}
	else {
		TSparseMatrix InvN1A(nbEq, nbUnk);
		TSparseMatrix *pInvN1A = &InvN1A;
		*pInvN1A = chol.solve(A);
		N2 = A.transpose() * *pInvN1A+ Px;
		rm->setIntermediateMatrix(N2);

		TVector pInvN1W = chol.solve(misclV);
		VP = A.transpose() * pInvN1W;
	}

	//inverse N2
	Eigen::SimplicialLDLT<TSparseMatrix> chol2( N2 );

	#ifdef _DEBUG
			std::cout << "TLSCombinedCalculation::computeResultsMtrs, det(N2)=\n " << chol2.determinant() << std::endl;
	#endif

	if(chol2.info() != Eigen::Success)
	{
		// cholesky did not work, try fullPiv
		typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMat;
		Eigen::FullPivLU<TMat> lu2(N2);

		if (! lu2.isInvertible()) {
			std::ostringstream foo;
			foo << "TLSCombinedCalculation::computeResultsMtrs:\n\tsolution failed.";
			fError += foo.str();
			return false;
		}
	
		*(rm->getSolutionVctr()) = -lu2.solve(  VP );
		return true;
	}
	else {
		*(rm->getSolutionVctr()) = -chol2.solve( VP );
		return true;
	}
}

void	TLSWeightedUnkMtdComputer::calcResiduAndVarCovMatrice(const TLSInputMatrices* inputMtr,
	TLSResultsMatrices* rm)
{
	if (fError == "")
	{
		int nbUnk = inputMtr->getNbrUnknowns();
		int nbObs = inputMtr->getNbrObservations();
		int nbEq = inputMtr->getNbrEquations();
		TReal sigmaZero2Aposteriori = LITERAL(0.0);

		const TSparseMatrix & A = *inputMtr->getFirstDgnMtrx();
		const TSparseMatrix & AT = A.transpose();
		const TSparseMatrix & B = *inputMtr->getSecondDgnMtrx();
		const TSparseMatrix BT = B.transpose();
		const TSparseMatrix & Pv = *inputMtr->getWeightMtrx();
		const TSparseMatrix & InvPv = *inputMtr->getWeightInvMtrx();
		const TVector & misclV = inputMtr->getMisclosureVctr();
		TVector & solution = *rm->getSolutionVctr();
		TVector & residuals = *rm->getResidualsVctr();
		TSparseMatrix & ResCovarMtrx = *rm->getResCovarMtrx();
		TSparseMatrix & Qxx = *rm->getUnkCovarMtrx();
		const TSparseMatrix & N2 = rm->getIntermediateMatrix();
		TSparseMatrix N1 = B * InvPv * BT;

		//Residuals
		typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMat;
		Eigen::FullPivLU<TMat> lu(N1);

		if (!lu.isInvertible()) {
			std::ostringstream foo;
			foo << "TLSCombinedMtdComputer::calcResiduAndVarCovMatrice:\n\tsolution failed.";
			fError += foo.str();
			return;
		}

		TSparseMatrix S(nbObs, nbEq);
		S = InvPv * BT * (lu.inverse());
		residuals = -S * (A * solution + misclV);


		//Sigma 0 a posteriri
		sigmaZero2Aposteriori = residuals.transpose() * Pv * residuals;
		if (nbObs != nbUnk)
			sigmaZero2Aposteriori /= (nbObs - nbUnk);
		else
			fError += "Number of equations equals number of unknowns, causes zero division!";
		rm->setSigmaZero2(sigmaZero2Aposteriori);
		struct limits fisherLim = calcSigmaZeroLimits(nbObs, nbUnk);
		rm->setSigmaZero2Limits(fisherLim.s0PostLoLimit, fisherLim.s0PostUpLimit);

		//Residuals and unknowns covariance matrices
		Eigen::SimplicialLDLT<TSparseMatrix> chol(N1);
		TSparseMatrix AtInvN1(nbUnk, nbEq); // transpose(A1)*inv(N1)
		TSparseMatrix MP2(nbObs, nbEq);
		AtInvN1 = A.transpose() * (lu.inverse());
		MP2 = InvPv*BT*(lu.inverse());
		
		Eigen::SimplicialLDLT<TSparseMatrix> chol2(N2);
		TSparseMatrix InvN2(nbUnk, nbUnk);
		if(chol2.info() != Eigen::Success)
		{
			// cholesky did not work, try fullPiv
			typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMat;
			Eigen::FullPivLU<TMat> lu2(N2);

			if (! lu2.isInvertible()) {
				std::ostringstream foo;
				foo << "TLSCombinedCalculation::calcResiduAndVarCovMatrice:\n\tsolution failed.";
				fError += foo.str();
				return;
			}
			TSparseMatrix InvN2(nbUnk, nbUnk);
			TSparseMatrix Id(nbUnk,nbUnk);
			for (int i = 0; i<nbUnk; i++)
				Id.insert(i,i) = 1;
			InvN2 = Id*lu2.inverse();
		}
		else {
			TSparseMatrix Id(nbUnk,nbUnk);
			for (int i = 0; i<nbUnk; i++)
			Id.insert(i,i) = 1;
			InvN2 = chol2.solve(Id);
		}

		TSparseMatrix invN2ATInvN1(nbEq, nbEq);
		invN2ATInvN1 = InvN2*AtInvN1;
		Qxx = invN2ATInvN1*A*InvN2.transpose();
		rm->setUnkCovarMtrx(&Qxx);

		TSparseMatrix Id(nbEq, nbEq);
		for (int i = 0; i<nbEq; i++)
			Id.insert(i, i) = 1;
		TSparseMatrix MP(nbEq, nbEq);
		MP = -1*A*invN2ATInvN1+Id;


		ResCovarMtrx =MP2* MP * B * InvPv*BT*MP.transpose()*MP2.transpose();
		rm->setResCovarMtrx(&ResCovarMtrx);
	}
}
