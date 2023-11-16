//TLSResultsMatrices.h : header file
// class for result matrices as defined for survey purposes 
// and for the least squares solving algorithm
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TConstants.h"
#include "TLSResultsMatrices.h"
#include "ProjectPath.h"

#if USE_SERIALIZER
#	include <Serializer_json.hpp>
#endif // USE_SERIALIZER

////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi)
{
	// constructor dimensioning the matrices
	fSolutionVctr = new TVector(ueoi.UIndex);
	fResidualsVctr = new TVector(ueoi.OIndex);
	fResCovarianceMtrx = new TSparseMatrix(ueoi.OIndex, ueoi.OIndex);
	fUnkCovarianceMtrx = new TSparseMatrix(ueoi.UIndex, ueoi.UIndex);
	fNormalMatrix = new TSparseMatrix(ueoi.UIndex + ueoi.CIndex, ueoi.UIndex + ueoi.CIndex);
	fInvN1Matrix = new TSparseMatrix(ueoi.EIndex, ueoi.EIndex);
	fUeoi = ueoi;

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

	if (fInvN1Matrix != 0)
		delete fInvN1Matrix;
}


//////////////////////////////////////////////////////////////////////////////////////////
//MEMBER FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////

//TSparseMatrix TLSResultsMatrices::computeCovarObs(const TSparseMatrix& A)
//{
//	return  (A - *fResCovarianceMtrx);
//}

TSparseMatrix TLSResultsMatrices::blowUpParCovarianceMatrix(TSparseMatrix reducedCovar, std::vector<int> activeIndices)
{
	int nbUnk = fUeoi.UIndex;
	TSparseMatrix result(nbUnk, nbUnk);
	int nActIndices = activeIndices.size();
	for (int row = 0; row < nActIndices; row++)
	{
		for (int col = 0; col < nActIndices; col++)
		{
			result.coeffRef(activeIndices[row], activeIndices[col]) = reducedCovar.coeff(row, col);
		}
	}

	return result;
}

TSparseMatrix TLSResultsMatrices::blowUpObsCovarianceMatrix(TSparseMatrix reducedCovar, std::vector<int> activeIndices)
{
	int nbObs = fUeoi.OIndex;
	TSparseMatrix result(nbObs, nbObs);
	int nActIndices = activeIndices.size();
	for (int row = 0; row < nActIndices; row++)
	{
		for (int col = 0; col < nActIndices; col++)
		{
			result.coeffRef(activeIndices[row], activeIndices[col]) = reducedCovar.coeff(row, col);
		}
	}

	return result;

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

#if USE_SERIALIZER
void TLSResultsMatrices::serialize(SerializerObject::SerializationHelper &obj) const
{
	// Save covariance specifically into some other file, and keep the path in the main object
	// Create a JSON COVAR object
	jsonSerializerObject ser;
	SerializerObject::SerializationHelper objMatrix = ser.getSerializationHelper();
	objMatrix.addProperty("fUnkCovarianceMtrx", fUnkCovarianceMtrx);

	// Save the object to an external JSON file
	const std::string covarOutputFileLocation = ProjectPath::getPath().getExtensionlessInputPath() + "_ucovar.json";
	std::ofstream fout(covarOutputFileLocation);
	fout << ser.getStringRepresentation();

	// Save path in the main JSON object
	obj.addProperty("fUnkCovarianceMtrx", covarOutputFileLocation);
}
#endif // USE_SERIALIZER


////////////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////////////
