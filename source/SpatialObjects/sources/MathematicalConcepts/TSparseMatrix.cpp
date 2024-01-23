#include <Eigen/LU>
#include <Eigen/SparseQR>
#include <Eigen/Dense>

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
bool inverse(const TSparseMatrix &sparseMat, TSparseMatrix &invMat, bool bTryCholeskyFirst, bool bTryFullPivotSecond)
{

	auto nRows = sparseMat.rows();
	auto nCols = sparseMat.cols();

	if (nRows != nCols)
	{
		logDebug() << "The given matrix A is not a square matrix to inverse!";
		return false;
	}

	// Setting the identity matrix

	TSparseMatrix IdMat(nRows, nRows);
	IdMat.setIdentity();

	// By default, tries Cholesky method first (it's the fastest method)
	// Cholesky is valid only for selfadjoint (symmetric) and positive definite matrices.
	if (bTryCholeskyFirst)
	{
		// LDL^T Cholesky factorizations without square root of sparse matrices that are selfadjoint and positive definite
		Eigen::SimplicialLDLT<TSparseMatrix> cholMat(sparseMat);
		if (cholMat.info() == Eigen::Success)
		{
			TDenseMatrix idMat_dense(nRows, nRows);
			idMat_dense.setIdentity();
			TVector aux(nRows, 1);
			TDenseMatrix inverse(nRows, nRows);
			inverse = TDenseMatrix::Zero(nRows, nRows);
#pragma omp parallel for
			for (int i = 0; i < nRows; i++)
			{
				inverse.col(i) = cholMat.solve(idMat_dense.col(i));
			}
			invMat = inverse.sparseView();

			logDebug() << "Cholesky method is used to invert the matrix!";
			return true;


		}
		else
			logDebug() << "Cholesky method failed to invert the matrix!";
	}

	// Cholesky method does not work (if the matrix is not symmetric), try FullPiv
	// LU decomposition of any matrix, with complete pivoting : the matrix A is decomposed as
	// A = P ^ { -1 } L U Q^{ -1 },  where L is unit -lower-triangular, U is upper-triangular, and P and Q are permutation matrices.
	if (bTryFullPivotSecond)
	{
		Eigen::FullPivLU<TMatrixDouble> luMat(sparseMat.toDense());
		if (luMat.isInvertible())
		{
			invMat = luMat.inverse().sparseView();
			logDebug() << "FullPivLU method is used to invert the matrix!";
			return true;
	}
	else
		logDebug() << "FullPivLU method failed to invert the matrix!";
	}

	// If both are not working, use Sparse LU
	Eigen::SparseLU<Eigen::SparseMatrix<double>, Eigen::NaturalOrdering<int>> LuMat;
	LuMat.compute(sparseMat);
	if (LuMat.info() != Eigen::Success) 
	{
		logDebug() << "Decomposition with the SparseLU method failed to invert the matrix!!";
		return false;
	}
	invMat = LuMat.solve(IdMat);
	if (LuMat.info() == Eigen::Success) 
	{
		logDebug() << "SparseLU method method is used to invert the matrix!";
		return true;
	}
	else
	{
		logDebug() << "SparseLU method failed to invert the matrix!!";
		return false;
	}
	
}

/*!
		\brief Solves the matricial equation A * X = B, where A is a squared sparse matrix, X and B are vectors
		\param[in]  matA is a square matrix
		\param[in]  vectB is a vector having the same dimension as the square matrix
		\param[out] vectX The resulting solution vector.
*/

bool solveUnique(const TSparseMatrix &matA, const TVector &vectB, TVector &vectX, bool bTryCholeskyFirst, bool bTryFullPivotSecond, bool useStrictThreshold)
{
	vectX.setZero();

	 // A must be a square matrix in our case, and the number of B vector elements must be the same!
	if (matA.rows() != matA.cols() || vectB.rows() != matA.rows())
	{
		logDebug() << "The given matrix A is not a square matrix, or the number of vector B elements does not correspond to A dimensions!";
		return false;
	}

	// By default, tries Cholesky method first
	if (bTryCholeskyFirst) 
	{
		Eigen::SimplicialLDLT<TSparseMatrix> cholMat(matA);
		if (cholMat.info() == Eigen::Success)
		{
			// Uses Cholesky method
			vectX = cholMat.solve(vectB);
			logDebug() << "Cholesky method is used for solving the equations system!";
			return true;
		}
		else
			logDebug() << "Cholesky method failed for solving the equations system!";
	}

	// Cholesky method does not work, try FullPiv
	if (bTryFullPivotSecond)
	{
		Eigen::FullPivLU<TMatrixDouble> luMat(matA.toDense());
		if (luMat.isInvertible())
		{
			vectX = luMat.solve(vectB);
			logDebug() << "FullPivLU method is used for solving the equations system!";
			return true;
		}
		else
			logDebug() << "FullPivLU method failed for solving the equations system!";
	}
	
	// If both are not working, use Sparse QR
	Eigen::SparseQR<Eigen::SparseMatrix<double>, Eigen::NaturalOrdering<int>> QrMat;
	// pivotThreshold important for solving the system accurately
	// https://eigen.tuxfamily.org/dox/classEigen_1_1SparseQR.html
	// necessary for Slave feature, otherwise let Eigen choose
	if (useStrictThreshold)
	{
		QrMat.setPivotThreshold(1e-12);
	}
	QrMat.compute(matA);
	if (QrMat.info() != Eigen::Success) 
	{
		logDebug() << "Decomposition with the SparseQR method failed!";
		return false;
	}
	vectX = QrMat.solve(vectB);
	if (QrMat.info() != Eigen::Success) 
	{
		logDebug() << "SparseQR method failed for solving the equations system!";
		return false;
	}
	else
	{
		logDebug() << "SparseQR method is used for solving the equations system!";
		return true;
	}
}


inline double ABij(const TSparseMatrix& A, const TSparseMatrix& B, int i, int j)
{
	const Eigen::Index u(A.cols());
	double sum(0.0);

#pragma omp parallel for reduction(+ : sum)
	for (Eigen::Index r = 0; r < u; r++)
	{
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
	const auto obs(A.rows());
	const auto ukn(A.cols());

	res.resize(obs);
	res.setZero();

	//TSparseMatrix AB(A*B);
#pragma omp parallel for
	for (Eigen::Index n = 0; n < obs; n++)
	{
		for (Eigen::Index u = 0; u < ukn; u++)
		{
			// for unknowns (u= num unknowns)
			//double abij = AB.coeff(n,u) ;
			double abij = ABij(A, B, (int)n, (int)u);
			res(n) += abij * A.coeff(n, u);
		}
	}
	return res;
}


} // namespace


