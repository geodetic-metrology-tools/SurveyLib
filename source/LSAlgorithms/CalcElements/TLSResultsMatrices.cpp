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
}


TLSResultsMatrices::TLSResultsMatrices(TColumnVector* solut, TColumnVector* resid, 
									   real sigm2)
{// constructor setting the results

	cout<<(double) sigm2<<endl<<endl;
	fSolutionVctr = new TColumnVector (*solut);
	fResidualsVctr = new TColumnVector (*resid);
	fSigmaZero2 = sigm2;
	//fUnknownsCovarianceMtrx = new TMatrix(*unkcov);
	fUnknownsCovarianceMtrx = NULL;
	fS0APosterioriVariances = false;
	L = NULL;
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
	real *result = A.multiply_three_returning_diagonal(*fUnknownsCovarianceMtrx, ATransposed);
	TColumnVector var(nobs);
	for (int i = 0; i < nobs; i++)
	{
		var(i) = result[i];
	}

	delete result;

	return var;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////////////
