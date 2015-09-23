//TLSResultsMatrices.h : header file
// class for result matrices as defined for survey purposes 
// and for the least squares solving algorithm
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


#include "lsalgo/TLSResultsMatrices.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////
//TLSResultsMatrices::TLSResultsMatrices()
//{// no argument constructor
//
//	fSolutionVctr = 0;
//	fResidualsVctr = 0;
//	fSigmaZero2 = LITERAL(0.0);
//	fUnknownsCovarianceMtrx = NULL;
//	fS0APosterioriVariances = false;
//	L = NULL;
//	bigMatrix = NULL;
//}


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi)
{// constructor dimensioning the matrices
	fSolutionVctr = new TVector(ueoi.UIndex);
	fResidualsVctr = new TVector(ueoi.OIndex);
	fSigmaZero2 = LITERAL(0.0);
	fUnknownsCovarianceMtrx = new TSparseMatrix(ueoi.UIndex, ueoi.UIndex);
	//fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	//L = NULL;
	//bigMatrix = NULL;
}


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi, int numConstraints)
{// constructor dimensioning the matrices
	fSolutionVctr = new TVector(ueoi.UIndex);
	fResidualsVctr = new TVector(ueoi.OIndex);
	fSigmaZero2 = LITERAL(0.0);
	fUnknownsCovarianceMtrx = new TSparseMatrix(ueoi.UIndex + numConstraints, ueoi.UIndex + numConstraints);
	//fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	//L = NULL;
	//bigMatrix = NULL;
}


//TLSResultsMatrices::TLSResultsMatrices(TVector* solut, TVector* resid, 
//									   TReal sigm2, TMatrix* unkcov)
//{// constructor setting the results
//
//	cout<<(double) sigm2<<std::endl<<std::endl;
//	fSolutionVctr = new TVector (*solut);
//	fResidualsVctr = new TVector (*resid);
//	fSigmaZero2 = sigm2;
//	//fUnknownsCovarianceMtrx = new TMatrix(*unkcov);
//	fUnknownsCovarianceMtrx = NULL;
//	fS0APosterioriVariances = false;
//	L = NULL;
//	bigMatrix = NULL;
//}
//
//
TLSResultsMatrices::TLSResultsMatrices(int numUnknowns, int numEquations)
{// constructor creating the results matrices with the input dimensions

	fSolutionVctr = new TVector (numUnknowns);
	fResidualsVctr = new TVector (numEquations);
	fSigmaZero2 = LITERAL(0.0);
	fUnknownsCovarianceMtrx = new TSparseMatrix(numUnknowns,numUnknowns);
	//fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	//L = NULL;
	//bigMatrix = NULL;
}
//
//
//TLSResultsMatrices::TLSResultsMatrices(int solut, int resid, 
//									   int unkcov)
//{// constructor setting the results
//
//	fSolutionVctr = new TVector (solut);
//	fResidualsVctr = new TVector (resid);
//	fSigmaZero2 = LITERAL(0.0);
//	//fUnknownsCovarianceMtrx = new TMatrix(unkcov,unkcov);
//	fUnknownsCovarianceMtrx = NULL;
//	fS0APosterioriVariances = false;
//	L = NULL;
//	bigMatrix = NULL;
//}

TLSResultsMatrices::~TLSResultsMatrices()
{// destructor
	if(fSolutionVctr != 0)
	{
		delete fSolutionVctr;
	}

	if(fResidualsVctr != 0)
	{
		delete fResidualsVctr;
	}

	if(fUnknownsCovarianceMtrx != 0)
	{
		delete fUnknownsCovarianceMtrx;
	}

}


//////////////////////////////////////////////////////////////////////////////////////////
//MEMBER FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////

TVector	TLSResultsMatrices::computeVarObs(const TSparseMatrix* A) 
{
	TVector res;
	return TSparseUtils::multABATasDiag(res, *A, *fUnknownsCovarianceMtrx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//DEBUG METHOD 
////////////////////////////////////////////////////////////////////////////////////////////////////
void TLSResultsMatrices::saveMatricesToFile(int nbIter) const
{//saves the content of the matrices to a text file

	// TODO: fix
	std::ostringstream oss;

	oss << "C:\\temp\\resultsMatrices" << nbIter << ".txt";
	std::string fileName = oss.str();

	std::ofstream of(fileName.c_str(), std::ios::out);
	if (!of){
		std::cout << "Impossible d'ouvrir le fichier C:\\temp\\resultsMatrices.txt" << '\n';
		std::exit (1);
	}

	of << std::setprecision(9);

	of << "Number of Unknowns : " << fUnknownsCovarianceMtrx->rows() << std::endl;
	of << "Number of Observations : " << fResidualsVctr->size() << std::endl << std::endl;
//	of << "Number of Equations : " << fNbEqn << std::endl << std::endl;

	of << "****************" << std::endl;
	of << "* SIGMA ZERO ^2*" << std::endl;
	of << "****************" << std::endl << std::endl;
	of << fSigmaZero2 << std::endl <<std::endl << std::endl;



	of << "*******************" << std::endl;
	of << "* SOLUTION VECTOR *" << std::endl;
	of << "*******************" << std::endl << std::endl;
	
	of << *fSolutionVctr << std::endl;
	of << std::endl << std::endl;

	of << "********************" << std::endl;
	of << "* RESIDUALS VECTOR *" << std::endl;
	of << "********************" << std::endl << std::endl;

	of << *fResidualsVctr << std::endl;
	of << std::endl << std::endl;


	of << "******************************" << std::endl;
	of << "* UNKNOWNS COVARIANCE MATRIX *" << std::endl;
	of << "******************************" << std::endl << std::endl;

	of << *fUnknownsCovarianceMtrx << std::endl;
	of << std::endl << std::endl;

	of << "******************************" << std::endl;
	of << "* INTERMEDIATE MATRIX *" << std::endl;
	of << "******************************" << std::endl << std::endl;

	of << fIntermediateMatrix << std::endl;
	of << std::endl << std::endl;

	of.close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////////////