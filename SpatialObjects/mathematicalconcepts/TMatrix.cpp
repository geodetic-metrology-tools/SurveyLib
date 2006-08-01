// TMatrix.cpp
//
/** Class for a matrix of doubles.
Designed to be easiliy usable with matrix functions of the NagC math library */
//
// Patterns:
//
// 
// Copyright 2002 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include "TColumnVector.h"
#include "TDouble.h"
#include  "TMatrix.h"

//#include	"vecmatdefs.h"
//#include	"errmesg.h"
//#include	"geo_utils.h"
//#include	"vecmat.h"
//#include	"ptcovdefs.h"
//#include	"primtvdefs.h"
//#include	"libgenmat.h"
//#include	"liblsapps.h"
//#include	"libgeofit.h"

#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////


//ClassImp(TMatrix)


//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

TMatrix::TMatrix()
{//default constructor
	fMatrix = 0;
	fNbRows = 0;
	fNbCols = 0;
	fError = "";
	setStatus( TANumericValue::kNull );
}

TMatrix::TMatrix(const TDouble& value)
{//Constructor return the matrice (1,1) with (1,1)=value ..... 
	fNbRows = 1;
	fNbCols = 1;
	fError = "";
	//unsigned int bob = 5; (unsigned int) value.getValue()
	fMatrix = new double [1];
	*fMatrix = value.getValue();
	setStatus( TANumericValue::kKnown );
}


TMatrix::TMatrix(int nRows,int nCols):fNbRows(nRows), fNbCols(nCols)
{//Constructor setting the dimensions of the matrix

	if( (fNbRows > 0) && (fNbCols > 0) )
	{
		fMatrix = new double [fNbRows * fNbCols];
		(*this) = 0.0;
		setStatus( TANumericValue::kKnown );
	}
	else
	{
		fNbRows = 1;
		fNbCols = 1;
		fMatrix = new double [fNbRows * fNbCols];
		(*this) = 0.0;
		fError = "Invalid dimension" + '\n';
		setStatus( TANumericValue::kNull );
	}
}	
		

TMatrix::TMatrix( const  TMatrix& source ):fNbRows(source.fNbRows), fNbCols(source.fNbCols)
{//!Copy constructor

	//dimensioning of the matrix
	fMatrix = new double [fNbRows * fNbCols];

	//copy the matrix coefficients
	for (int i = 0; i<(fNbRows * fNbCols); i++)
		fMatrix[i] = source.fMatrix[i];

	//copy the status
	setStatus( source.getStatus() );

	//copy error message
	fError = source.fError;
}


TMatrix::~TMatrix()
{//!Destructor
	delete[] fMatrix;
}

//////////////////////////////////////////////////////////////////////
///operator Functions
//////////////////////////////////////////////////////////////////////

TMatrix&  TMatrix::operator=(const TMatrix& right)
{//Copy assignement operator	
	if (this != &right)
	{
		if ((numCols() == right.numCols()) && (numRows() == right.numRows()) && numCols()!=0 && numRows()!=0)
		{
			for (int i=0; i<fNbRows; i++)
			{
				for (int j=0; j<fNbCols; j++)
				{(const_cast<TMatrix*>(this))->operator()(i,j) = right(i,j);}
				setStatus(right.getStatus());
				fError = right.fError;
			}
		}
		else
		{
			this->setDimensions(0,0);
			this->setStatus(kNull);
		}
	}
	return *this;
}


void TMatrix::operator=(const double& value)
{//inits all the matrix coefficients to a common value
	for (int i = 0; i<(fNbRows * fNbCols); i++)
	{fMatrix[i] = value;}
}


TMatrix TMatrix::operator +(const TMatrix& right) const
{//returns the sum of this matrix and a second one
	TMatrix resultat (numRows(), numCols());
	resultat.setStatus(TVNumericValue::kNull);
	TANumericValue::EStatus status;
	status=this->testStatus(right);
	if (status!= kNull && (numCols() == right.numCols()) && (numRows() == right.numRows()))
	{
		for (int i=0; i<fNbRows; i++)
		{
			for (int j=0; j<fNbCols; j++)
			{
				resultat(i,j) = (*this)(i,j) + right(i,j);
			}
		}
	resultat.setStatus(status);
	}
return resultat;	
}


TMatrix& TMatrix::operator +=(const TMatrix& right)
{//replaces this matrix by its sum with a second one
*this=(*this)+right;
return *this;
}


TMatrix TMatrix::operator -(const TMatrix& right) const
{//returns the difference of this matrix and a second one
	TMatrix resultat (numRows(), numCols());
	resultat.setStatus(TVNumericValue::kNull);
	TANumericValue::EStatus status;
	status=this->testStatus(right);
	if (status!= kNull && (numCols() == right.numCols()) && (numRows() == right.numRows()))
	{
		for (int i=0; i<fNbRows; i++)
		{
			for (int j=0; j<fNbCols; j++)
			{
				resultat(i,j) = (*this)(i,j) - right(i,j);
			}
		}
	resultat.setStatus(status);
	}
return resultat;	
}


TMatrix& TMatrix::operator -=(const TMatrix& right)
{//replaces this matrix by its difference with a second one
*this=(*this)-right;
return *this;
}


TMatrix TMatrix::operator *(const TMatrix& right) const
{//returns the product of this matrix and a second one
	TMatrix resultat (numRows(), right.numCols());
	resultat.setStatus(TVNumericValue::kNull);
	TANumericValue::EStatus status;
	status=this->testStatus(right);
	if (status!=kNull && numCols() == right.numRows())
	{
			dgemm(NoTranspose, NoTranspose, resultat.numRows(), resultat.numCols(), numCols(), 1.0, getFirstEltAdr(),
			numCols(), right.getFirstEltAdr(), right.numCols(), 0.0, resultat.getFirstEltAdr(), resultat.numCols());
	resultat.setStatus(status);
	}
	return resultat;
}

TMatrix& TMatrix::operator *=(const TMatrix& right)
{//replaces this matrix by its product with a second one
*this=(*this)*right;
return *this;
}


TColumnVector TMatrix::operator*(const TColumnVector& right) const
{//returns the product of this matrix by a column vector
	TColumnVector resultat (numRows());
	resultat.setStatus(TVNumericValue::kNull);
	TANumericValue::EStatus status;
	status=this->testStatus(right);
	if (status!=kNull && numCols() == right.dimension())
	{
		dgemv(NoTranspose, numRows(), numCols(), 1.0, getFirstEltAdr(), numCols(), right.getFirstEltAdr(), 
		1, 0.0, resultat.getFirstEltAdr(), 1);
		resultat.setStatus(status);
	}
	return resultat;	
}


TMatrix TMatrix::operator*( const double& k)
{//multiplies the Matrix by a scalar
	TMatrix result (numRows(), numCols());
	for (int i=0; i<fNbRows; i++)
	{
		for (int j=0; j<fNbCols; j++)
		{
			result(i,j) = (*this)(i,j)*k;
		}
	}
	result.setStatus(getStatus());
	return result;
}


TMatrix TMatrix::operator*( const TDouble& k)
{//multiplies the Matrix by a TDouble
	TMatrix resultat (numRows(), numCols());
	TANumericValue::EStatus status;
	status=this->testStatus(k);
	if (status!=kNull)
	{
		for (int i=0; i<fNbRows; i++)
		{
			for (int j=0; j<fNbCols; j++)
			{
				resultat(i,j) = (*this)(i,j)*k.getValue();
			}
		}
	}
	resultat.setStatus(status);
	return resultat;
}


////////////////////////////////////
///Member Functions
////////////////////////////////////

TMatrix TMatrix::transposed() const
{//return the tranposed matrix of this one
	TMatrix result (numCols(), numRows());
	for (int i=0; i<numRows(); i++)
	{
		for (int j=0; j<numCols(); j++)
		{
			result(j,i) = (*this)(i,j);
		}
	}
	result.setStatus(getStatus());
	return result;
}


TColumnVector TMatrix::eqnSolve(const TColumnVector& B) 
{//returns the solution of the system this*X = B

	//this matrix has to be copied otherwise it is overwritten
	TMatrix* thisCopy = new TMatrix(*this);
	// nagc error message, to be set if there is a problem. 
	// It should not be printed on the screen
	static NagError fail;
	fail.print = false;

	//computation of the solution vector X
	TColumnVector solution (numRows());
	nag_real_lin_eqn(numRows(), thisCopy->getFirstEltAdr(), numCols(), B.getFirstEltAdr(), solution.getFirstEltAdr(), &fail);

	// Possible errors: input unconsistency, matrix singularity, or memory allocation failure
	if ((fail.code == NE_INT_ARG_LT) || (fail.code == NE_2_INT_ARG_LT) || 
		(fail.code == NE_SINGULAR) || (fail.code == NE_ALLOC_FAIL)) {
		fError += fail.message + '\n';
		solution.setStatus(TANumericValue::kNull);
	}

	delete thisCopy;
	return solution;
}


bool TMatrix::initDiag( const double& comVal)
{//inits all the matrix diagonal coefficients to a common value

	if (fNbRows == fNbCols)
	{
		for (int i = 0; i<fNbRows ; i++)
		{
			for (int j=0; j<fNbCols; j++)
			{
				if (i == j)
				{(*this)(i,j) = comVal;}
				else
				{(*this)(i,j) = 0.0;}
			}
		}
	return true;
	}
	else
	{return false;}
}


void TMatrix::setDimensions( const int& nRows,  const int& nCols)
{//Sets the dimensions of the matrix
	
	//destroy the previous values
	if (fMatrix != 0)
	{
		delete[] fMatrix;
	}
	
	
	if( (nRows >= 0) && (nCols >= 0) )
	{
		//creates the new Matrix
		fNbRows = nRows;
		fNbCols = nCols;
		fMatrix = new double [fNbRows * fNbCols];
		(*this) = 0.0;
	}
	else
	{
		fNbRows = 1;
		fNbCols = 1;
		fMatrix = new double [fNbRows * fNbCols];
		(*this) = 0.0;
		fError = "Invalid dimension" + '\n';
		setStatus( TANumericValue::kNull );
	}
}


int TMatrix::numRows() const
{//returns the number of rows
	return fNbRows;
}


int TMatrix::numCols() const
{//returns the number of Columns
	return fNbCols;
}


bool TMatrix::invert()
{//Overwrites this Matrix by its inverse
//checks if the Matrix can be inverted
	if(getStatus() != TVNumericValue::kNull)
	{
		if (fNbCols == fNbRows)
		{
			TMatrix* copyMat = new TMatrix(*this);
			
			long* pivot = new long[fNbCols];
			long dete;
			double detf;
			// nagc error message, to be set if there is a problem. 
			// It should not be printed on the screen
			static NagError fail;
			fail.print = false;

			//LU factorization of the matrix
			nag_real_lu(fNbCols, copyMat->getFirstEltAdr(), fNbCols, pivot, &detf, &dete, &fail);
			
			// Possible errors: matrix singularity, input unconsistency, or memory allocation failure
			if ((fail.code == NE_SINGULAR) || (fail.code == NE_INT_ARG_LT) || 
				(fail.code == NE_2_INT_ARG_LT) || (fail.code == NE_ALLOC_FAIL)) {
				fError += fail.message + '\n';
				return false;
			}

			//right hand side 
			TMatrix rhs (fNbCols, fNbCols);
			rhs.initDiag(1.0);

			//Computation of the inverse
			nag_real_lu_solve_mult_rhs(fNbCols, fNbCols, copyMat->getFirstEltAdr(), fNbCols, pivot, rhs.getFirstEltAdr(),
				fNbCols, &fail);

			// possible errors: input unconsistency
			if ((fail.code == NE_INT_ARG_LT) || (fail.code == NE_2_INT_ARG_LT)) {
				fError += fail.message + '\n';
				return false;
			}

			//copyMat and pivot are no longer needed
			delete copyMat;
			delete[] pivot;
			*this=rhs;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


	

TMatrix TMatrix::inverse()
{//Returns the inverse of this matrix (the latter isn't affected) using nagc lib.

	TMatrix  copy(*this);
	bool inverted = copy.invert();
	if (inverted)
	{
		return copy;
	}
	else
	{
		copy.setStatus(TANumericValue::kNull);
		return copy;
	}
}
	

void TMatrix::clear()
{//return a matrice (i,j)=0, status kNull
	for (int i=0; i< fNbRows; i++)
	{
		for (int j=0; j< fNbCols; j++)
		{(*this)(i,j)=0;}
	}
}

double& TMatrix::operator()(const int&  row, const int& col)
{//returns a reference to a matrix coefficient

	if( (row<0) || (row>=fNbRows) || (col<0) || (col>=fNbCols) )
	{
		double NaN = 0;
		NaN = 1/NaN;
		double* p = &NaN;
		return (*p);
	}
	else
	{
		return fMatrix[(row)*fNbCols + col];
	}
}


double TMatrix::operator()(const int& row, const int& col) const
{//returns a copy of a matrix coefficient (const version of the previous method
	if( (row<0) || (row>=fNbRows) || (col<0) || (col>=fNbCols) )
	{
		double NaN = 0;
		NaN = 1/NaN;
		double* p = &NaN;
		return (*p);
	}
	else
	{
		return fMatrix[(row)*fNbCols + col];
	}
}




////////////////////////////////////////////////
///Private Function
////////////////////////////////////////////////

double* TMatrix::getFirstEltAdr() const
{//returns the adress of the matrix's first element
	return fMatrix;
}



TMatrix TMatrix::dfact(int* n_pivot,int* pivot_i,int* pivot_j)
{	// LU decomposition, returns the decomposition in one matrix and the pivots.
	// allways comes first, before dfeqn or dfinv.
	TMatrix res (*this);
	int n(this->numRows()-1);
	

	int i(0),j(0),k(0),l(0),jp1(0),jm1(0);
	double zero(0.0),one(1.0),x(0.0),y(0.0),tf(0.0),s11(0.0),s12(0.0);
	double g1(1.0e-19),g2(1.0e19),p(0.0),q(0.0),t(0.0);
	
	int nxch(-1);

	for (j=0;j<=n;j++)
	{
		k=j;
		p=fabs((res)(j,j));
		if (j<n)
		{
			jp1 = j+1;
			for (i=jp1;i<=n;i++)
			{
				q=fabs((res)(i,j));
				if (q>p)
				{
					k=i;
					p=q;
				}
			} // label 121
			if(k==j)
			{
				if (p==0.0) // pivot == 0 ->singularity
				{
					return TMatrix(); // error handling
				}
				(res)(j,j) = one/(res)(j,j);
			}
			else
			{
				for (l=0;l<=n;l++)
				{
					tf = (res)(j,l);
					(res)(j,l)=(res)(k,l);
					(res)(k,l)=tf;
				} // label 124

				nxch += 1;

				pivot_i[nxch] = j;
				pivot_j[nxch] = k;
				
				(res)(j,j) = one/(res)(j,j);

			}
		}
		else //j==n 
		{
			if (p==0.0)
			{
				return TMatrix();
			}
			(res)(j,j) = one/(res)(j,j);
		}
		if (j<n)
		{
			jm1 = j-1;
			jp1 = j+1;
			for (k=jp1;k<=n;k++)
			{
				s11 = -(res)(j,k);
				s12 = -(res)(k,j+1);
				if (j>0)
				{
					for (i=0;i<=jm1;i++)
					{
						s11 += (res)(i,k)*(res)(j,i);
						s12 += (res)(i,j+1)*(res)(k,i);
					} // label 141
				}
				(res)(j,k) = -s11*(res)(j,j);
				(res)(k,j+1) = -(s12+(res)(j,j+1)*(res)(k,j));
			} // label 143
		} // label 144
	} // label 144

	*n_pivot = nxch;

	return res;
}


TColumnVector TMatrix::dfeqn(TColumnVector* B,int n_pivot,int* pivot_i,int* pivot_j) 
{// resolution of equations system. It must be applied on the matrix returned by dfact(...)

	int n(this->numRows()-1);
	int i(0),j(0),m(0),im1(0),nm1(0),nmi(0),nmjp1(0);
	double x(0.0),y(0.0),te(0.0),s21(0.0),s22(0.0);

	if (n_pivot>-1)
	{
		for (m=0;m<=n_pivot;m++)
		{
			i=pivot_i[m];
			j=pivot_j[m];
			te=(*B)(i);
			(*B)(i)=(*B)(j);
			(*B)(j)=te;
		}
	} //label 220
	
	(*B)(0)=(*this)(0,0) * (*B)(0);

	if (n>0)
	{
		for (i=1;i<=n;i++)
		{
			im1=i-1;
			s21=-(*B)(i);
			for (j=0;j<=im1;j++)
			{
				s21 += (*this)(i,j) * (*B)(j);
			}
			(*B)(i) = -(*this)(i,i) * s21;
		} //label 232

		nm1 = n-1;
		for (i=0;i<=nm1;i++)
		{
			nmi = n-i-1;
			s22 = -(*B)(nmi);
			for (j=0;j<=i;j++)
			{
				nmjp1 = n-j;
				s22 += (*this)(nmi,nmjp1) * (*B)(nmjp1);
			}
			(*B)(nmi) = -s22;
		} // label 242 (i-loop)
	} // label 299 (endif)

	return *B;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//to be deleted
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
TMatrix TMatrix::inverseSym()
{// Returns the inverse of this matrix (the latter isn't affected). 
 //	Methods using LU decomposition and row interchanges (translated form cernlib / fortran lib)

	TMatrix resultat (this->numRows(),this->numCols());
	TMatrix* invN = &resultat;
	TMatrix* inter = new TMatrix(this->numRows(),this->numCols());

	int n_pivot(this->numRows()-1);
	int* pivot_i;
	int* pivot_j;

	pivot_i = new int [n_pivot+1];
	pivot_j = new int [n_pivot+1];

	*inter = this->dfact(&n_pivot,pivot_i,pivot_j);
	
	*invN = inter->dfinv(&n_pivot,pivot_i,pivot_j);

	delete inter;
	delete[] pivot_i;
	delete[] pivot_j;
	
	return *invN;
}

TMatrix		TMatrix::inverseAasen()
{//Returns the inverse of this matrix (the latter isn't affected), uses C methods
	TMatrix  copy(*this);
	bool inverted = copy.invertSym();
	if (inverted)
	{	
		return copy;
	}
	else
	{
		copy.setStatus(TANumericValue::kNull);
		return copy;
	}	
}

TMatrix		TMatrix::inverseAasen2() 
{// Returns the inverse of this matrix (the latter isn't affected)
	//almost fully translated from C to C++

	TMatrix invN (this->numRows(),this->numCols());
	invN = this->aasen_inv2();
	
	return invN;
}*/

/*
bool TMatrix::invertSym()
{//Overwrites this Matrix by its inverse
//checks if the Matrix can be inverted
	if (fNbCols == fNbRows)
	{
		int istrt = 0;
		int iend = fNbRows-1;
		int jstrt = 0;
		int jend = fNbCols-1;
		unsigned long int errflg = 0;

		Mmn	mxr = matrix(istrt,iend ,jstrt ,jend, &errflg);
     
 		/* allocate pointers to rows */
/*		(double**) mxr.mat = new double* [fNbRows];

		while ( istrt <= iend)
		{
			mxr.mat[istrt]= &fMatrix[istrt * fNbCols];
			istrt ++;
		}


		if(errflg != 0)
		{
			return false;
		}
		else
		{
			Mmn	mxrout = aasen_inv(&mxr, &errflg);

			if(errflg != 0)
			{
				return false;
			}
			else
			{
				for (int i=0; i<fNbRows; i++)
				{
					for (int j=0; j<fNbCols; j++)
					{
						fMatrix[(i)*fNbCols + j] = mxrout.mat[i][j];
					}
				}
			}
			free_matrix(&mxrout);

		}
  
		delete mxr.mat;
		return true;
	}
	else
	{
		return false;
	}
}*/


/*
TMatrix	TMatrix::aasen_inv2()
{
	// inverts this matrix and returns the invert
	int nbRows ,nbCols, n;
	double   sum(0.0),element(0.0);
	// get matrix and vector boundaries to avoid clutter
	nbRows = this->numRows();
	nbCols = this->numCols();
	n = nbRows - 1;
	
	// vector containing the diagonals of T matrix, and the permutations
	//	valarray<double> diagT(0.0,nbRows),diagTsym(0.0,nbRows),vcswap(0.0,nbRows);
	valarray<double> vcswap(0.0,nbRows);
	// T as a matrix
	TMatrix* T = new TMatrix(nbRows,nbCols);
	// unit lower triangular matrix
	TMatrix* L = new TMatrix(nbRows,nbCols);
	// inverse of L
	TMatrix* invL = new TMatrix(nbRows,nbCols);
	// results natrices
	TMatrix resultat (nbRows,nbCols);
	TMatrix* res = &resultat;

	// Aasen decomposition
	aasen_dcmp2(this,L,T,&vcswap);

	register int i(0),j(0),k(0),ki(0),kj(0),ii(0);

	// compute inverse of L
	for (i=0;i<=n;i++)
	{
		(*invL)(i,i) = 1.0/(*L)(i,i);

		for (j=i+1;j<=n;j++)
		{
			sum = 0.0;
			for (k=0;k<=j-1;k++)
				sum -=(*L)(j,k) * (*invL)(k,i);

			(*invL)(j,i) = sum/(*L)(j,j);
		}

	}

	// compute inverse of T
	TMatrix* invT = new TMatrix(nbRows,nbCols);

	unsigned long int errflg = 0;
	int istrt = 0;
	int iend = nbRows-1;
	int jstrt = 0;
	int jend = nbCols-1;	

	Mmn	mxT = matrix(istrt,iend ,jstrt ,jend, &errflg);
	Mmn	invmxT = matrix(istrt,iend ,jstrt ,jend, &errflg);
	clear_matrix(&mxT);
	clear_matrix(&invmxT);

	for (i=0;i<n;i++)
	{
		mxT.mat[i][i] = (*T)(i,i);
		mxT.mat[i][i+1] = (*T)(i,i+1);
		mxT.mat[i+1][i] = (*T)(i+1,i);
	}
  
	mxT.mat[n][n] = (*T)(n,n);

	invmxT = lu_bandpiv_inv(&mxT,1,1,&errflg);
	// converts T from matrix to TMatrix
	for (i=0;i<=n;i++)
	{
		for (j=0;j<=n;j++)
			(*invT)(i,j) = invmxT.mat[i][j];
	}

	if(errflg != 0)
	{
		delete T,L,invL,invT;
		return TMatrix();
	}
	else
	{	// INVERSION DE N
		(*res) = invL->transposed() * (*invT) * (*invL);

		/* Compute inverse of matrix N by swapping back any rows and columns which 
		were changed to compute the L matrix. 
		Simultaneously set N back to the original matrix */

/*		for (i=n;i>=0;i--)
		{
			if ((ii = vcswap[i])!=0)
			{
				// some rows and columns have been swapped so reverse the process
				//swap columns
				for (k=0;k<=n;k++)
				{
					element=(*res)(k,i);
					(*res)(k,i) = (*res)(k,ii);
					(*res)(k,ii) = element;

					element = (*this)(k,i);
					(*this)(k,i) = (*this)(k,ii);
					(*this)(k,ii) = element;
				}

				//swap rows
				for (k=0;k<=n;k++)
				{
					element = (*res)(i,k);
					(*res)(i,k) = (*res)(ii,k);
					(*res)(ii,k) = element;

					element = (*this)(i,k);
					(*this)(i,k) = (*this)(ii,k);
					(*this)(ii,k) = element;
				}
			}
		}
		free_matrix(&invmxT);		
		free_matrix(&mxT);
	}
 
	delete L,invL,T,invT;

	return *res;
}*/
/*
void	TMatrix::aasen_dcmp2(TMatrix* N,TMatrix* L,TMatrix* T, valarray<double> *vcswap ) {
// decomposes the N matrix



	register int i(0),j(0),k(0),qflg(0);
	int nbRows,nbCols,n;
	double element(0.0);
	
	nbRows = N->numRows();
	nbCols = N->numCols();	
	n = nbRows - 1;

	cout << "nbRows " << nbRows << endl;
	cout << "nbCols " << nbCols << endl;
	cout << "n " << n << endl;

	valarray<double> vch(0.0,nbRows),vcv(0.0,nbRows);

	for (k=0;k<=n;k++) {
		// establish lower triangular matrix values for relevant column
		(*L)(k,k) = 1.0;
		// determine relevant column of T*(transpose(L))

		for (i=1;i<=(k-1);i++) {
		
			vch[i] = (*T)(i,i-1) * (*L)(k,i-1) 
				+ (*T)(i,i) * (*L)(k,i) 
				+ (*T)(i,i+1) * (*L)(k,i+1);

		}
		
		vch[k] = (*N)(k,k);

		for (i=1;i<=(k-1);i++)
			vch[k] -= (*L)(k,i) * vch[i];

		if (k == 0)
			(*T)(k,k) = (*N)(k,k);
		else
			(*T)(k,k) = vch[k] - (*T)(k,k-1) * (*L)(k,k-1);

		if (k<n) {
			
			for (i=k+1;i<=n;i++) {
				
				vcv[i] = (*N)(i,k);

				for (j=1;j<=k;j++)
					vcv[i] -= (*L)(i,j) * vch[j];
			}

			// locate largest element in vcv
			qflg = k+1;
			for (j=k+2;j<=n;j++) {
					
					if (fabs(vcv[j]) > fabs(vcv[qflg]))
						qflg = j;
				}

			if (qflg!=k+1) {
					
				// row with larger element value found: swap values
				element = vcv[k+1];
				vcv[k+1] = vcv[qflg];
				vcv[qflg] = element;
				

				// swap rows of N matrix
				for (j=0;j<=n;j++) {
					
					element = (*N)(k+1,j);
					(*N)(k+1,j) = (*N)(qflg,j);
					(*N)(qflg,j) = element;
				}

				// swap columns of N matrix
				for (j=0;j<=n;j++) {
					
					element = (*N)(j,k+1);
					(*N)(j,k+1) = (*N)(j,qflg);
					(*N)(j,qflg) = element;
				}
				
				// swap computed row elements of L
				for (j=0;j<i;j++) {
					
					element = (*L)(k+1,j);
					(*L)(k+1,j) = (*L)(qflg,j);
					(*L)(qflg,j) = element;
				}

				// mark which row was swapped
				(*vcswap)[k+1] = qflg;
			}

			(*T)(k+1,k) = vcv[k+1];
			(*T)(k,k+1) = vcv[k+1];

			if ((fabs(vcv[k+1])>1.0e-14) && (k<= n-2)) {
				
				for (i=k+2;i<=n;i++)
					(*L)(i,k+1) = vcv[i]/vcv[k+1];
			}
		}
		
	}

	return;
}*/


/*
TMatrix TMatrix::dfinv(int* n_pivot,int* pivot_i,int* pivot_j)
{// inversion of this matrix. Returns a matrix containing the invert (latter not affected)
 // It must be applied on the matrix returned by dfact(...)
	if (this->isNull())
	{
		return TMatrix();
	}
	else
	{
		TMatrix res (*this);
		
		int n(this->numRows()-1);
		int i(0),j(0),k(0),im2(0),nm1(0),nmi(0),nxch(0),m(0),ij(0);
		double zero(0.0),x(0.0),y(0.0),ti(0.0),s31(0.0),s32(0.0),s33(0.0),s34(0.0);

		(res)(1,0) = -(res)(1,1)*(res)(0,0)*(res)(1,0);
		(res)(0,1) = -(res)(0,1);

		if (n>1)
		{
			for (i=2;i<=n;i++)
			{
				im2 = i-2;
				for (j=0;j<=im2;j++)
				{
					s31=zero;
					s32=(res)(j,i);
					for (k=j;k<=im2;k++)
					{
						s31 += (res)(k,j)*(res)(i,k);
						s32 += (res)(j,k+1)*(res)(k+1,i);
					}
					(res)(i,j) = -(res)(i,i)*((res)(i-1,j)*(res)(i,i-1)+s31);
					(res)(j,i) = -s32;
				}
				(res)(i,i-1) = -(res)(i,i)*(res)(i-1,i-1)*(res)(i,i-1);
				(res)(i-1,i) = -(res)(i-1,i);
			}
		} // label 330
		nm1=n-1;
		for (i=0;i<=nm1;i++)
		{
			nmi=n-i-1;
			for (j=0;j<=i;j++)
			{
				s33 = (res)(i,j);
				for (k=0;k<=nmi;k++)
				{
					s33 += (res)(i+k+1,j)*(res)(i,i+k+1);
				}
				(res)(i,j) = s33;
			}
			for (j=0;j<=nmi;j++)
			{
				s34 = zero;
				for (k=j;k<=nmi;k++)
				{
					s34 += (res)(i+k+1,i+j+1)*(res)(i,i+k+1);
				}
				(res)(i,i+j+1) = s34;
			} // label 334
		} // label 335
		nxch = (*n_pivot);
		if (nxch != -1)
		{
			for (m=0;m<=nxch;m++)
			{
				k=nxch-m;
				i=pivot_i[k];
				j=pivot_j[k];
				for (k=0;k<=n;k++)
				{
					ti = (res)(k,i);
					(res)(k,i) = (res)(k,j);
					(res)(k,j) = ti;
				}
			}
		}
		
		return res;
	}
}*/
