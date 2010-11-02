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


#include "TDouble.h"
#include "TMatrix.h"
#include "TColumnVector.h"
#include "TSparseMatrix.h"

#include <TMatrixImpl.h>

#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////


//ClassImp(TMatrix)


//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

TMatrix::TMatrix()
: fImpl(new TMatrixImpl)
{//default constructor
	setStatus( TANumericValue::kNull );
}

// TODO: Check who is using that
TMatrix::TMatrix(const TDouble & value)
: fImpl(new TMatrixImpl(1,1,value.getValue()))
{//Constructor return the matrice (1,1) with (1,1)=value ..... 
	setStatus( TANumericValue::kKnown );
}


TMatrix::TMatrix(int nRows, int nCols)
: fImpl(new TMatrixImpl(nRows, nCols, 0.0))
{//Constructor setting the dimensions of the matrix
    setStatus( TANumericValue::kKnown );	
	//{
	//	fNbRows = 1;
	//	fNbCols = 1;
	//	fMatrix = new double [fNbRows * fNbCols];
	//	(*this) = LITERAL(0.0);
	//	fError = "Invalid dimension" + '\n';
	//	setStatus( TANumericValue::kNull );
	//}
}	
		

TMatrix::TMatrix(const TMatrix & source)
: fImpl(new TMatrixImpl(*(source.fImpl))),
  fError(source.fError)
{//!Copy constructor
	//copy the status
	setStatus( source.getStatus() );
}

void TMatrix::swap(TMatrix & other) throw()
{
    using std::swap;
    swap(fImpl, other.fImpl);
    swap(fError, other.fError);
}

TMatrix::~TMatrix()
{//!Destructor
    delete fImpl;
}

//////////////////////////////////////////////////////////////////////
///operator Functions
//////////////////////////////////////////////////////////////////////

// the copy assignment operator takes its argument by value, 
// eliminating the need to explicitly create a copy of the other object.
TMatrix & TMatrix::operator=(TMatrix other)
{//Copy assignement operator	
	this->swap(other);
    return *this;
}


void TMatrix::operator=(const double& value)
{//inits all the matrix coefficients to a common value
	fImpl->setConstant(value);
}

// TODO: Dimension checks?
TMatrix & TMatrix::operator+=(const TMatrix & right)
{//replaces this matrix by its sum with a second one
    setStatus(this->testStatus(right));
    if(numRows()!=right.numRows() || numCols()!=right.numCols()) {
        setStatus(kNull);
        fError += "Cannot add matrices of a different sizes";
    }
    if(getStatus()!=kNull)
    {
        fImpl->operator+=(*right.fImpl);
    }
    return *this;
}

// TODO: Could be a nonmember function
TMatrix TMatrix::operator+(const TMatrix & right) const
{//returns the sum of this matrix and a second one
	TMatrix result(*this);
    return result += right;
}

// TODO: Dimension checks?
TMatrix & TMatrix::operator-=(const TMatrix& right)
{//replaces this matrix by its difference with a second one
    setStatus(this->testStatus(right));
    if(numRows()!=right.numRows() || numCols()!=right.numCols()) {
        setStatus(kNull);
        fError += "Cannot calculate a difference between the matrices of a different sizes";
    }
    if(getStatus()!=kNull)
    {
        fImpl->operator-=(*right.fImpl);
    }
    return *this;
}


// TODO: Could be a nonmember function
TMatrix TMatrix::operator-(const TMatrix& right) const
{//returns the difference of this matrix and a second one
	TMatrix result(*this);
    return result -= right;
}

TMatrix & TMatrix::operator*=(const TMatrix & right)
{//replaces this matrix by its product with a second one
    setStatus(this->testStatus(right));
    if(getStatus()!=kNull && numCols() == right.numRows())
    {
        fImpl->operator*=(*right.fImpl);
    }
    return *this;
}

TMatrix TMatrix::operator*(const TMatrix & right) const
{//returns the product of this matrix and a second one
	TMatrix result(*this);
    return result *= right;
}

TColumnVector TMatrix::operator*(const TColumnVector& right) const
{//returns the product of this matrix by a column vector
    TColumnVector result(numRows());
	result.setStatus(this->testStatus(right));
    if (result.getStatus()!=kNull && numCols() == right.dimension())
	{
        TMatrixImpl tmp(numCols(),1,0.0);
        for(std::size_t i=0; i!=numCols(); ++i)
            tmp(i,0) = right(i);

        TMatrixImpl res = *this->fImpl * tmp;
        for(std::size_t i=0; i!=numCols(); ++i)
            result(i) = res(i,0);
	}
	return result;
}

TMatrix & TMatrix::operator*=(double value)
{
    if(getStatus()!=kNull)
    {
        fImpl->operator*=(value);
    }
    return *this;
}

TMatrix TMatrix::operator*(double value)
{//multiplies the Matrix by a scalar
    TMatrix result(*this);
    return result *= value;
}


TMatrix & TMatrix::operator*=(const TDouble & right)
{
    setStatus(this->testStatus(right));
    if(getStatus()!=kNull)
    {
        fImpl->operator*=(right.getValue());
    }
    return *this;
}

TMatrix TMatrix::operator*(const TDouble & right)
{//multiplies the Matrix by a TDouble
	TMatrix result(*this);
    return result *= right;
}


////////////////////////////////////
///Member Functions
////////////////////////////////////

TMatrix TMatrix::transposed() const
{//return the tranposed matrix of this one
    TMatrix result(*this);
    result.fImpl->transpose();
    return result;
}


TColumnVector TMatrix::eqnSolve(const TColumnVector& B) 
{//returns the solution of the system this*X = B
    TColumnVector result(numRows());
	result.setStatus(this->testStatus(B));
    if (result.getStatus()!=kNull && numCols() == B.dimension())
	{
        TMatrixImpl tmp(numCols(),1,0.0);
        for(std::size_t i=0; i!=numCols(); ++i)
            tmp(i,0) = B(i);

        TMatrixImpl res = this->fImpl->solve(tmp);
        for(std::size_t i=0; i!=numCols(); ++i)
            result(i) = res(i,0);
    }
    return result;
}


// TODO: Is this used in the intermediate calculations?
// Maybe it would be better to make it a constructor.
bool TMatrix::initDiag(double value)
{//inits all the matrix diagonal coefficients to a common value
    if(fImpl->rows() == fImpl->cols())
	{
        fImpl->initDiag(value);
		return true;
	}
	else
    {
        // TODO: Are we sure that we don't want rectangular matrices as well?
        return false;
    }
}

// TODO: Is this used in the intermediate calculations?
// Maybe it would be better to use only constructors
void TMatrix::setDimensions(int nRows, int nCols)
{//Sets the dimensions of the matrix
    fImpl->resize(nRows, nCols);
	//{
	//	fNbRows = 1;
	//	fNbCols = 1;
	//	fMatrix = new double [fNbRows * fNbCols];
	//	(*this) = LITERAL(0.0);
	//	fError = "Invalid dimension" + '\n';
	//	setStatus( TANumericValue::kNull );
	//}
}


int TMatrix::numRows() const
{//returns the number of rows
	return fImpl->rows();
}


int TMatrix::numCols() const
{//returns the number of Columns
	return fImpl->cols();
}


bool TMatrix::invert()
{//Overwrites this Matrix by its inverse
//checks if the Matrix can be inverted
	if(getStatus() != TVNumericValue::kNull && numRows() == numCols())
	{
	    return fImpl->invert();
	}
	else
	{
		return false;
	}
}


	

TMatrix TMatrix::inverse()
{//Returns the inverse of this matrix (the latter isn't affected)

	TMatrix result(*this);
	bool inverted = result.invert();
    if(!inverted)
        result.setStatus(TANumericValue::kNull);
    return result;
}


void TMatrix::clear()
{//return a matrice (i,j)=0
    fImpl->setConstant(0.0);
}

double & TMatrix::operator()(int row, int col)
{//returns a reference to a matrix coefficient
    return fImpl->operator()(row,col);
}


double TMatrix::operator()(int row, int col) const
{//returns a copy of a matrix coefficient (const version of the previous method
	return fImpl->operator()(row,col);
}


TSparseMatrix* TMatrix::toSparse() const
{
	int nnz = 0;
	int rowStart;

	for (int i = 0; i < numRows(); i++)
	{
		rowStart = i * numCols();
		for (int j = 0; j < numCols(); j++)
		{
			if ( *(fImpl->data() + rowStart + j) != 0)
			{
				nnz++;
			}
		}
	}

	TReal* vs = new TReal[nnz];
	int* rs = new int[nnz];	
	int* cs = new int[numCols() + 1];
	cs[0] = 0;
	nnz = 0;

	for (int i = 0; i < numCols(); i++)
	{
		for (int j = 0; j < numRows(); j++)
		{
			if ( *( fImpl->data() + i + j * numCols() ) != 0)
			{
				vs[nnz] = *( fImpl->data() + i + j * numCols() );
				rs[nnz++] = j;
			}
		}
		cs[i + 1] = nnz;
	}

	return new TSparseMatrix(numRows(), numCols(), vs, rs, cs);
}



////////////////////////////////////////////////
///Private Function
////////////////////////////////////////////////

//double* TMatrix::getFirstEltAdr() const
//{//returns the adress of the matrix's first element
//	return fMatrix;
//}



//TMatrix TMatrix::dfact(int* n_pivot,int* pivot_i,int* pivot_j)
//{	// LU decomposition, returns the decomposition in one matrix and the pivots.
//	// allways comes first, before dfeqn or dfinv.
//	TMatrix res (*this);
//	int n(this->numRows()-1);
//	
//
//	int i(0),j(0),k(0),l(0),jp1(0),jm1(0);
//	double zero(LITERAL(0.0)),one(LITERAL(1.0)),x(LITERAL(0.0)),y(LITERAL(0.0)),tf(LITERAL(0.0)),s11(LITERAL(0.0)),s12(LITERAL(0.0));
//	double g1(1.0e-19),g2(1.0e19),p(LITERAL(0.0)),q(LITERAL(0.0)),t(LITERAL(0.0));
//	
//	int nxch(-1);
//
//	for (j=0;j<=n;j++)
//	{
//		k=j;
//		p= (double) fabsq((res)(j,j));
//		if (j<n)
//		{
//			jp1 = j+1;
//			for (i=jp1;i<=n;i++)
//			{
//				q=(double) fabsq((res)(i,j));
//				if (q>p)
//				{
//					k=i;
//					p=q;
//				}
//			} // label 121
//			if(k==j)
//			{
//				if (p==LITERAL(0.0)) // pivot == 0 ->singularity
//				{
//					return TMatrix(); // error handling
//				}
//				(res)(j,j) = one/(res)(j,j);
//			}
//			else
//			{
//				for (l=0;l<=n;l++)
//				{
//					tf = (res)(j,l);
//					(res)(j,l)=(res)(k,l);
//					(res)(k,l)=tf;
//				} // label 124
//
//				nxch += 1;
//
//				pivot_i[nxch] = j;
//				pivot_j[nxch] = k;
//				
//				(res)(j,j) = one/(res)(j,j);
//
//			}
//		}
//		else //j==n 
//		{
//			if (p==LITERAL(0.0))
//			{
//				return TMatrix();
//			}
//			(res)(j,j) = one/(res)(j,j);
//		}
//		if (j<n)
//		{
//			jm1 = j-1;
//			jp1 = j+1;
//			for (k=jp1;k<=n;k++)
//			{
//				s11 = -(res)(j,k);
//				s12 = -(res)(k,j+1);
//				if (j>0)
//				{
//					for (i=0;i<=jm1;i++)
//					{
//						s11 += (res)(i,k)*(res)(j,i);
//						s12 += (res)(i,j+1)*(res)(k,i);
//					} // label 141
//				}
//				(res)(j,k) = -s11*(res)(j,j);
//				(res)(k,j+1) = -(s12+(res)(j,j+1)*(res)(k,j));
//			} // label 143
//		} // label 144
//	} // label 144
//
//	*n_pivot = nxch;
//
//	return res;
//}
//
//
//TColumnVector TMatrix::dfeqn(TColumnVector* B,int n_pivot,int* pivot_i,int* pivot_j) 
//{// resolution of equations system. It must be applied on the matrix returned by dfact(...)
//
//	int n(this->numRows()-1);
//	int i(0),j(0),m(0),im1(0),nm1(0),nmi(0),nmjp1(0);
//	double x(LITERAL(0.0)),y(LITERAL(0.0)),te(LITERAL(0.0)),s21(LITERAL(0.0)),s22(LITERAL(0.0));
//
//	if (n_pivot>-1)
//	{
//		for (m=0;m<=n_pivot;m++)
//		{
//			i=pivot_i[m];
//			j=pivot_j[m];
//			te=(*B)(i);
//			(*B)(i)=(*B)(j);
//			(*B)(j)=te;
//		}
//	} //label 220
//	
//	(*B)(0)=(*this)(0,0) * (*B)(0);
//
//	if (n>0)
//	{
//		for (i=1;i<=n;i++)
//		{
//			im1=i-1;
//			s21=-(*B)(i);
//			for (j=0;j<=im1;j++)
//			{
//				s21 += (*this)(i,j) * (double) (*B)(j);
//			}
//			(*B)(i) = -(*this)(i,i) * s21;
//		} //label 232
//
//		nm1 = n-1;
//		for (i=0;i<=nm1;i++)
//		{
//			nmi = n-i-1;
//			s22 = -(*B)(nmi);
//			for (j=0;j<=i;j++)
//			{
//				nmjp1 = n-j;
//				s22 += (*this)(nmi,nmjp1) * (double) (*B)(nmjp1);
//			}
//			(*B)(nmi) = -s22;
//		} // label 242 (i-loop)
//	} // label 299 (endif)
//
//	return *B;
//}



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
     
 		// allocate pointers to rows
		(double**) mxr.mat = new double* [fNbRows];

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
	double   sum(LITERAL(0.0)),element(LITERAL(0.0));
	// get matrix and vector boundaries to avoid clutter
	nbRows = this->numRows();
	nbCols = this->numCols();
	n = nbRows - 1;
	
	// vector containing the diagonals of T matrix, and the permutations
	//	valarray<double> diagT(LITERAL(0.0),nbRows),diagTsym(LITERAL(0.0),nbRows),vcswap(LITERAL(0.0),nbRows);
	valarray<double> vcswap(LITERAL(0.0),nbRows);
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
		(*invL)(i,i) = LITERAL(1.0)/(*L)(i,i);

		for (j=i+1;j<=n;j++)
		{
			sum = LITERAL(0.0);
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

	//	 Compute inverse of matrix N by swapping back any rows and columns which 
	//	were changed to compute the L matrix. 
	//	Simultaneously set N back to the original matrix

		for (i=n;i>=0;i--)
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
}

void	TMatrix::aasen_dcmp2(TMatrix* N,TMatrix* L,TMatrix* T, valarray<double> *vcswap ) {
// decomposes the N matrix



	register int i(0),j(0),k(0),qflg(0);
	int nbRows,nbCols,n;
	double element(LITERAL(0.0));
	
	nbRows = N->numRows();
	nbCols = N->numCols();	
	n = nbRows - 1;

	cout << "nbRows " << nbRows << endl;
	cout << "nbCols " << nbCols << endl;
	cout << "n " << n << endl;

	valarray<double> vch(LITERAL(0.0),nbRows),vcv(LITERAL(0.0),nbRows);

	for (k=0;k<=n;k++) {
		// establish lower triangular matrix values for relevant column
		(*L)(k,k) = LITERAL(1.0);
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
					
					if (fabsq(vcv[j]) > fabsq(vcv[qflg]))
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

			if ((fabsq(vcv[k+1])>1.0e-14) && (k<= n-2)) {
				
				for (i=k+2;i<=n;i++)
					(*L)(i,k+1) = vcv[i]/vcv[k+1];
			}
		}
		
	}

	return;
}



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
		double zero(LITERAL(0.0)),x(LITERAL(0.0)),y(LITERAL(0.0)),ti(LITERAL(0.0)),s31(LITERAL(0.0)),s32(LITERAL(0.0)),s33(LITERAL(0.0)),s34(LITERAL(0.0));

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
