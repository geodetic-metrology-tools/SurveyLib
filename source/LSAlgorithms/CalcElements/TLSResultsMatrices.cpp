//TLSResultsMatrices.h : header file
// class for result matrices as defined for survey purposes 
// and for the least squares solving algorithm
#include <iomanip>



#include "TLSResultsMatrices.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////////////////////////////
TLSResultsMatrices::TLSResultsMatrices()
{// no argument constructor

	fSolutionVctr = 0;
	fResidualsVctr = 0;
	fSigmaZero2 = LITERAL(0.0);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
	bigMatrix = NULL;
}


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi)
{// constructor dimensioning the matrices
	fSolutionVctr = new TColumnVector(ueoi.UIndex);
	fResidualsVctr = new TColumnVector(ueoi.OIndex);
	fSigmaZero2 = LITERAL(0.0);
	//fUnknownsCovarianceMtrx = new TMatrix(ueoi.UIndex, ueoi.UIndex);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
	bigMatrix = NULL;
}


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi, int numConstraints)
{// constructor dimensioning the matrices
	fSolutionVctr = new TColumnVector(ueoi.UIndex);
	fResidualsVctr = new TColumnVector(ueoi.OIndex);
	fSigmaZero2 = LITERAL(0.0);
	//fUnknownsCovarianceMtrx = new TMatrix(ueoi.UIndex + numConstraints, ueoi.UIndex + numConstraints);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
	bigMatrix = NULL;
}


TLSResultsMatrices::TLSResultsMatrices(TColumnVector* solut, TColumnVector* resid, 
									   real sigm2, TMatrix* unkcov)
{// constructor setting the results

	cout<<(double) sigm2<<endl<<endl;
	fSolutionVctr = new TColumnVector (*solut);
	fResidualsVctr = new TColumnVector (*resid);
	fSigmaZero2 = sigm2;
	//fUnknownsCovarianceMtrx = new TMatrix(*unkcov);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
	bigMatrix = NULL;
}


TLSResultsMatrices::TLSResultsMatrices(int numUnknowns, int numEquations)
{// constructor creating the results matrices with the input dimensions

	fSolutionVctr = new TColumnVector (numUnknowns);
	fResidualsVctr = new TColumnVector (numEquations);
	fSigmaZero2 = LITERAL(0.0);
	//fUnknownsCovarianceMtrx = new TMatrix(numUnknowns,numUnknowns);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
	bigMatrix = NULL;
}


TLSResultsMatrices::TLSResultsMatrices(int solut, int resid, 
									   int unkcov)
{// constructor setting the results

	fSolutionVctr = new TColumnVector (solut);
	fResidualsVctr = new TColumnVector (resid);
	fSigmaZero2 = LITERAL(0.0);
	//fUnknownsCovarianceMtrx = new TMatrix(unkcov,unkcov);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
	bigMatrix = NULL;
}

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

TColumnVector	TLSResultsMatrices::computeVarObs(const TSparseMatrix& A, const TSparseMatrix& ATransposed) 
{
	int nobs = A.rowsCount(); //number of observations
	int nunk = A.columnsCount(); //number of observations
	real* vals = new real[fUnknownsCovarianceMtrx->columnPointers()[nunk]];
	int* rows = new int[fUnknownsCovarianceMtrx->columnPointers()[nunk]];
	int* cols = new int[nunk + 1];
	cols[0] = 0;
	int count = 0;
	for (int i = 0; i < nunk; i++)
	{
		for (int j = fUnknownsCovarianceMtrx->columnPointers()[i];
			j < fUnknownsCovarianceMtrx->columnPointers()[i + 1] && fUnknownsCovarianceMtrx->rowIndices()[j] < nunk;
			j++)
		{
			vals[count] = fUnknownsCovarianceMtrx->values()[j];
			rows[count++] = fUnknownsCovarianceMtrx->rowIndices()[j];
		}
		cols[i + 1] = count;
	}
	TSparseMatrix* ucm = new TSparseMatrix(nunk, nunk, vals, rows, cols);
	real *result = A.multiply_three_returning_diagonal(*ucm, ATransposed);
	delete ucm;
	TColumnVector var(nobs);
	for (int i = 0; i < nobs; i++)
	{
		var(i) = result[i];
	}

	delete result;

	return var;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//DEBUG METHOD 
////////////////////////////////////////////////////////////////////////////////////////////////////
void TLSResultsMatrices::saveMatricesToFile(int nbIter) const
{//saves the content of the matrices to a text file

	// TODO: fix
//	ostringstream oss;
//
//	oss << "C:\\temp\\resultsMatrices" << nbIter << ".txt";
//	string fileName = oss.str();
//
//	ofstream of(fileName.c_str(), ios::out);
//	if (!of){
//		//cout << "Impossible d'ouvrir le fichier C:\\temp\\resultsMatrices.txt" << '\n';
//		exit (1);
//	}
//
//	of << setprecision(9);
//
//	of << "Number of Unknowns : " << fUnknownsCovarianceMtrx->numRows() << endl;
//	of << "Number of Observations : " << fResidualsVctr->dimension() << endl << endl;
////	of << "Number of Equations : " << fNbEqn << endl << endl;
//
//	of << "****************" << endl;
//	of << "* SIGMA ZERO ^2*" << endl;
//	of << "****************" << endl << endl;
//	of << fSigmaZero2 << endl <<endl << endl;
//
//
//
//	of << "*******************" << endl;
//	of << "* SOLUTION VECTOR *" << endl;
//	of << "*******************" << endl << endl;
//	
//	int i;
//	for (i=0; i<fUnknownsCovarianceMtrx->numRows() ; i++)
//		of << (*fSolutionVctr)(i) <<  endl;
//	of << endl << endl;
//
//	of << "********************" << endl;
//	of << "* RESIDUALS VECTOR *" << endl;
//	of << "********************" << endl << endl;
//	
//	for (i=0; i<fResidualsVctr->dimension() ; i++)
//		of << (*fResidualsVctr)(i) << endl;
//	of << endl << endl;
//
//
//	of << "******************************" << endl;
//	of << "* UNKNOWNS COVARIANCE MATRIX *" << endl;
//	of << "******************************" << endl << endl;
//	
//	for (i=0; i<fUnknownsCovarianceMtrx->numRows() ; i++){
//
//		for (int j=0; j<fUnknownsCovarianceMtrx->numRows() ; j++)
//			of << (*fUnknownsCovarianceMtrx)(i,j) << '\t';
//		of << endl;
//	}
//	of << endl << endl;
//
//	of.close();

	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////////////