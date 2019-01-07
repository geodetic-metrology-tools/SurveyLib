#include <Eigen/LU>

#include "TSparseMatrix.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <Logger.hpp>

namespace TSparseUtils {


/*!
		\brief Main method for inverting sparse matrices
		\param[in]  sparseMat The sparse matrix to be inverted
		\param[out] invMat    The resulting inverted matrix.
*/
bool inverse(const TSparseMatrix& sparseMat, TSparseMatrix& invMat, bool bTryCholeskyFirst)
{
	invMat.setZero();
	
	int nRows = sparseMat.rows();
	int nCols = sparseMat.cols();

	if (nRows == nCols)
	{
		if (bTryCholeskyFirst)  // By default, does not try this method
		{
			// LDL^T Cholesky factorizations without square root of sparse matrices that are selfadjoint and positive definite
			Eigen::SimplicialLDLT<TSparseMatrix> cholMat(sparseMat);
			if (cholMat.info() == Eigen::Success)
			{
				// Cholesky method is used to invert the matrix. solving the equation: N * X = Id => X = inv(N) 
				TSparseMatrix IdMat(nRows, nRows);
				IdMat.setIdentity();
				invMat = cholMat.solve(IdMat);
				return true;
			}
		}

		// LU decomposition of any matrix, with complete pivoting : the matrix A is decomposed as  
		// A = P ^ { -1 } L U Q^{ -1 },  where L is unit -lower-triangular, U is upper-triangular, and P and Q are permutation matrices.
		Eigen::FullPivLU<TMatrixDouble> luMat(sparseMat);
		if (!luMat.isInvertible())
		{
			// Add some log with the new LOG static library
			// error = "Matrix not inverted (neither Cholesky nor FullPivLU Methods worked!)";
			return false;
		}
		invMat = luMat.inverse().sparseView();
		return true;
	}
	else
	{
		// Add some log with the new LOG static library
		// error = "The given matrix is not a square matrix and cannot be inverted!";
		return false;
	}
}


/*!
		\brief Solves the matricial equation A * X = B, where A is a squared sparse matrix, X and B are vectors
		\param[in]  matA is a square matrix
		\param[in]  vectB is a vector having the same dimension as the square matrix
		\param[out] vectX The resulting solution vector.
*/

bool solveUnique(const TSparseMatrix& matA, const TVector& vectB, TVector& vectX, bool bTryCholeskyFirst)
{
	vectX.setZero();

	if (matA.rows() == matA.cols() && vectB.rows() == matA.rows())  // A must be a square matrix in our case, and the number of B vector elements must be the same!
	{
		if (bTryCholeskyFirst)  // By default, tries this method first
		{
			Eigen::SimplicialLDLT<TSparseMatrix> cholMat(matA);
			if (cholMat.info() == Eigen::Success)
			{
				// Uses Cholesky method
				vectX = cholMat.solve(vectB);
				return true;
			}
			else
				logDebug() << "Cholesky method failed for solving the equations system!";
		}

		// Cholesky method does not work, try FullPiv
		Eigen::FullPivLU<TMatrixDouble> luMat(matA);
		if (!luMat.isInvertible())
		{
			logDebug() << "FullPivLU method failed for solving the equations system!";
			return false;
		}
		vectX = luMat.solve(vectB);
		return true;
	}
	else
	{
		// Add some log with the new LOG static library
		logDebug() << "The given matrix A is not a square matrix, or the number of vector B elements does not correspond to A dimensions!";
		return false;
	}

}


inline double ABij(const TSparseMatrix& A, const TSparseMatrix& B, int i, int j)
{
	const int u(A.cols());
	double sum(0.0);

#pragma omp parallel for reduction(+ : sum)
	for (int r = 0; r < u; r++) {
		sum += A.coeff(i, r)*B.coeff(r, j);
	}

	return sum;
}

/*!
		\brief Optimized multiplication routine that returns the main diagonal of A*B*A'
		\param[in]  A sparse matrix
		\param[in]  B sparse matrix
		\param[out] res The resulting diagonal vector.
*/

TVector& multABATasDiag(TVector& res, const TSparseMatrix& A, const TSparseMatrix& B)
{
	const int obs(A.rows());
	const int ukn(A.cols());

	res.resize(obs);
	res.setZero();

	//TSparseMatrix AB(A*B);
#pragma omp parallel for
	for (int n = 0; n < obs; n++) {
		for (int u = 0; u < ukn; u++) {
			// for unknowns (u= num unknowns)
			//double abij = AB.coeff(n,u) ;
			double abij = ABij(A, B, n, u);
			res(n) += abij * A.coeff(n, u);
		}
	}
	return res;
}


} // namespace


