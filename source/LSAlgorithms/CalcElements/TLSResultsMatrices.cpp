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
	fSigmaZero2 = 0.0;
	fUnknownsCovarianceMtrx = 0;
	fS0APosterioriVariances = false;
}


TLSResultsMatrices::TLSResultsMatrices(UEOIndices ueoi)
{// constructor dimensioning the matrices
	fSolutionVctr = new TColumnVector(ueoi.UIndex);
	fResidualsVctr = new TColumnVector(ueoi.OIndex);
	fSigmaZero2 = 0.0;
	fUnknownsCovarianceMtrx = new TMatrix(ueoi.UIndex, ueoi.UIndex);
	fS0APosterioriVariances = false;
}


TLSResultsMatrices::TLSResultsMatrices(TColumnVector* solut, TColumnVector* resid, 
									   double sigm2, TMatrix* unkcov)
{// constructor setting the results

	cout<<sigm2<<endl<<endl;
	fSolutionVctr = new TColumnVector (*solut);
	fResidualsVctr = new TColumnVector (*resid);
	fSigmaZero2 = sigm2;
	fUnknownsCovarianceMtrx = new TMatrix(*unkcov);
	fS0APosterioriVariances = false;
}



TLSResultsMatrices::TLSResultsMatrices(int solut, int resid, 
									   int unkcov)
{// constructor setting the results

	fSolutionVctr = new TColumnVector (solut);
	fResidualsVctr = new TColumnVector (resid);
	fSigmaZero2 = 0.0;
	fUnknownsCovarianceMtrx = new TMatrix(unkcov,unkcov);
	fS0APosterioriVariances = false;
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
double TLSResultsMatrices::computeS2APosteriori(const TMatrix& A, int i) const
{// returns the variance a posteriori of the ith observation
	
	double var(0.0);

	int n = A.numCols();
	// computation of var = variance on the ith observation
	for (int j=0;j<n;j++) {
		double vari(0.0);
		// product of A ith row and one column of unknown covar. matrix
		for (int k=0;k<n;k++) 
			vari += A(i,k) * getUnknownsCovarMtrxElmt(k,j);
		// product of (A ith row * one unk.covar.mat. column) and transposed A ith row
		var += vari * A(i,j);
	}
	
	return var;

}

TColumnVector	TLSResultsMatrices::computeVarObs(const TMatrix& A) 
{
	int nobs = A.numRows(); //number of observations
	int nunk = A.numCols(); //number of unknowns
	int nel = fUnknownsCovarianceMtrx->numRows(); //number of unknowns + constraints (if any)
	TMatrix* Nbis = new TMatrix(nunk,nunk); //for local copy of Unknowns Covariance Mtrx
	TMatrix* Kll = new TMatrix(nobs,nobs);
	// if free calculation, attribute Unknowns Covariance Mtrx bigger than real unknowns covariance mtrx
	// -> extraction of real unknowns covariance mtrx
	if (nunk <= nel)
	{
		for (int i=0; i<nunk; i++)
		{
			for (int j=0; j<nunk; j++)
			{
				(const_cast<TMatrix*>(Nbis))->operator()(i,j) = (*fUnknownsCovarianceMtrx)(i,j);
			}
		}
	}
	
	// computation of var = diag of observations covariance mtrx
	TColumnVector	var(nobs);
	(*Kll) = A * (*Nbis) * A.transposed();
	for (int i=0;i<nobs;i++)
		var(i) = (*Kll)(i,i);

	delete Kll;
	delete Nbis;

	return var;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//DEBUG METHOD 
////////////////////////////////////////////////////////////////////////////////////////////////////
void TLSResultsMatrices::saveMatricesToFile(int nbIter) const
{//saves the content of the matrices to a text file

	ostringstream oss;

	oss << "C:\\temp\\resultsMatrices" << nbIter << ".txt";
	string fileName = oss.str();

	ofstream of(fileName.c_str(), ios::out);
	if (!of){
		//cout << "Impossible d'ouvrir le fichier C:\\temp\\resultsMatrices.txt" << '\n';
		exit (1);
	}

	of << setprecision(9);

	of << "Number of Unknowns : " << fUnknownsCovarianceMtrx->numRows() << endl;
	of << "Number of Observations : " << fResidualsVctr->dimension() << endl << endl;
//	of << "Number of Equations : " << fNbEqn << endl << endl;

	of << "****************" << endl;
	of << "* SIGMA ZERO ^2*" << endl;
	of << "****************" << endl << endl;
	of << fSigmaZero2 << endl <<endl << endl;



	of << "*******************" << endl;
	of << "* SOLUTION VECTOR *" << endl;
	of << "*******************" << endl << endl;
	
	for (int i=0; i<fUnknownsCovarianceMtrx->numRows() ; i++)
		of << (*fSolutionVctr)(i) <<  endl;
	of << endl << endl;

	of << "********************" << endl;
	of << "* RESIDUALS VECTOR *" << endl;
	of << "********************" << endl << endl;
	
	for (i=0; i<fResidualsVctr->dimension() ; i++)
		of << (*fResidualsVctr)(i) << endl;
	of << endl << endl;


	of << "******************************" << endl;
	of << "* UNKNOWNS COVARIANCE MATRIX *" << endl;
	of << "******************************" << endl << endl;
	
	for (i=0; i<fUnknownsCovarianceMtrx->numRows() ; i++){

		for (int j=0; j<fUnknownsCovarianceMtrx->numRows() ; j++)
			of << (*fUnknownsCovarianceMtrx)(i,j) << '\t';
		of << endl;
	}
	of << endl << endl;

	of.close();

	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////////////////////////////////////////