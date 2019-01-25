//TLSResultsMatrices.h : header file
// class for result matrices as defined for survey purposes 
// and for the least squares solving algorithm
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TConstants.h"
#include "TLSResultsMatrices.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////

TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi)
{
	// constructor dimensioning the matrices
	fSolutionVctr = new TVector(ueoi.UIndex);   // dX solution vector (corrections to unknowns approximate values)
	fResidualsVctr = new TVector(ueoi.OIndex);  // V residues vector (corrections to raw observations)
	fResCovarianceMtrx = new TSparseMatrix(ueoi.OIndex, ueoi.OIndex);  // Qvv variance-covariance matrix of the observation residues V
	fUnkCovarianceMtrx = new TSparseMatrix(ueoi.UIndex, ueoi.UIndex);  // Qxx variance-covariance matrix of the unjnowns
	fNormalMatrix = new TSparseMatrix(ueoi.UIndex, ueoi.UIndex);  // N normal matrix of the adjustment

	fSigmaZero2 = NO_VALf;
}


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi, int numConstraints)
{
	// constructor dimensioning the matrices
	fSolutionVctr = new TVector(ueoi.UIndex);
	fResidualsVctr = new TVector(ueoi.OIndex);
	fResCovarianceMtrx = new TSparseMatrix(ueoi.OIndex, ueoi.OIndex);
	fUnkCovarianceMtrx = new TSparseMatrix(ueoi.UIndex + numConstraints, ueoi.UIndex + numConstraints);
	fNormalMatrix = new TSparseMatrix(ueoi.UIndex, ueoi.UIndex);

	fSigmaZero2 = NO_VALf;
}


TLSResultsMatrices::TLSResultsMatrices(int numUnknowns,int numObs)
{
	// constructor creating the results matrices with the input dimensions
	fSolutionVctr = new TVector (numUnknowns);
	fResidualsVctr = new TVector (numObs);
	fResCovarianceMtrx = new TSparseMatrix(numObs,numObs);
	fUnkCovarianceMtrx = new TSparseMatrix(numUnknowns,numUnknowns);
	fNormalMatrix = new TSparseMatrix(numUnknowns, numUnknowns);

	fSigmaZero2 = NO_VALf;
}


TLSResultsMatrices::~TLSResultsMatrices()
{
	// destructor
	if(fSolutionVctr != 0)
		delete fSolutionVctr;

	if(fResidualsVctr != 0)
		delete fResidualsVctr;

	if(fResCovarianceMtrx != 0)
		delete fResCovarianceMtrx;

	if(fUnkCovarianceMtrx != 0)
		delete fUnkCovarianceMtrx;

	if (fNormalMatrix != 0)
		delete fNormalMatrix;
}


//////////////////////////////////////////////////////////////////////////////////////////
//MEMBER FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////

//TSparseMatrix TLSResultsMatrices::computeCovarObs(const TSparseMatrix& A)
//{
//	return  (A - *fResCovarianceMtrx);
//}

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

	of << "Number of Unknowns : " << fUnkCovarianceMtrx->rows() << std::endl;
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

	of << "******************************" << std::endl;
	of << "* UNKNOWNS COVARIANCE MATRIX *" << std::endl;
	of << "******************************" << std::endl << std::endl;

	of<< *fUnkCovarianceMtrx << std::endl;
	of << std::endl << std::endl;


	of << "********************" << std::endl;
	of << "* RESIDUALS VECTOR *" << std::endl;
	of << "********************" << std::endl << std::endl;

	of << *fResidualsVctr << std::endl;
	of << std::endl << std::endl;


	of << "******************************" << std::endl;
	of << "* RESIDUALS COVARIANCE MATRIX *" << std::endl;
	of << "******************************" << std::endl << std::endl;

	of<< *fResCovarianceMtrx << std::endl;
	of << std::endl << std::endl;

	of.close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////////////