// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TSparseMatrix.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include <Eigen/Dense>


#include <Logger.hpp>

namespace TSparseUtils
{
// for a given square matrix, apply a simple, symmetry preserving diagonal scaling, return the scaled matrix and also the diagonal scaling vector
TSparseMatrix createSymmetricScaling(const TSparseMatrix &inputMat, TVector &scalingVector)
{
	if (inputMat.rows() != inputMat.cols())
	{
		throw std::runtime_error("Symmetric Scaling: Matrix must be square");
	}
	// symmetry preserving diagonal matrix scaling (suitable for cholesky)
	scalingVector = inputMat.diagonal().cwiseAbs().cwiseMax(1e-12).cwiseSqrt().cwiseInverse();
	const Eigen::DiagonalMatrix<double, Eigen::Dynamic> D(scalingVector);
	return D * inputMat * D;
}

// preparing the decomposition (and the scaling is desired)
template<class Decomposition>
bool scaleAndDecompose(const TSparseMatrix &A, bool useScaling, TSparseMatrix &AScaled, TVector &scalingVector, Decomposition &solver)
{
	if (A.rows() == 0)
	{
		return true;
	}
	if (useScaling)
	{
		AScaled = createSymmetricScaling(A, scalingVector); // computes scalingVector and AScaled = D*A*D
		solver.compute(AScaled);
	}
	else
	{
		scalingVector = TVector::Ones(A.rows());
		solver.compute(A);
	}
	return solver.info() == Eigen::Success;
}

// utility template to solve with a given decomposition. Only used in TSparseMatrix.cpp
template<typename Decomposition>
bool solveUniqueWithDecomposition(const TSparseMatrix &A, const TVector &b, TVector &sol, bool useScaling = true)
{
	const int nRows = A.rows();
	if (nRows == 0)
	{
		sol.resize(0);
		return true;
	}

	TSparseMatrix AScaled;
	TVector d;
	Decomposition solver;

	if (!scaleAndDecompose(A, useScaling, AScaled, d, solver))
	{
		return false;
	}
	const TVector bScaled = useScaling ? d.asDiagonal() * b : b;
	const TVector y = solver.solve(bScaled);
	sol = useScaling ? d.asDiagonal() * y : y; // scaling case: A' y = b' => A (D y) = b, i.e. D y is the solution of the original system

	const double bNorm = b.norm();
	if (bNorm > 0.0)
	{
		logDebug() << "solve operation relative accuracy |A*x-b|/|b|= " << (A * sol - b).norm() / bNorm;
	}

	return solver.info() == Eigen::Success;
}

// utility template to invert with a given decomposition. Only used in TSparseMatrix.cpp
template<typename Decomposition>
bool invertWithDecomposition(const TSparseMatrix &A, TSparseMatrix &invMat, bool useScaling = true)
{
	const int nRows = A.rows();
	if (nRows == 0)
	{
		invMat.resize(0, 0);
		return true;
	}

	TSparseMatrix AScaled;
	TVector d;
	Decomposition solver;

	if (!scaleAndDecompose(A, useScaling, AScaled, d, solver))
	{
		return false;
	}

	const Eigen::DiagonalMatrix<double, Eigen::Dynamic> D(d);
	Eigen::MatrixXd inverse = Eigen::MatrixXd::Zero(nRows, nRows);
	// variable to estimate the condition number
	double maxRatio = 0;
#pragma omp parallel for
	for (int i = 0; i < nRows; ++i)
	{
		TVector bScaled = TVector::Unit(nRows, i);
		if (useScaling)
			bScaled = D * bScaled;

		TVector y = solver.solve(bScaled);
		maxRatio = std::max(maxRatio, y.norm());
		TVector sol = useScaling ? D * y : y; // scaling case: A' y = b' => A (D y) = b, i.e. D y is the solution of the original system
		inverse.col(i) = sol;
	}
	if (maxRatio > 1e+12)
	{
		std::stringstream msg;
		msg << std::scientific << std::setprecision(3) << "Condition number estimate = " << maxRatio << " indicating ill-conditioned matrix, possibly singular.";
		logWarning() << msg.str();
	}

	invMat = inverse.sparseView();
	return true;
}

/*!
		\brief Main method for inverting sparse matrices
		\param[in]  sparseMat The sparse matrix to be inverted
		\param[out] invMat    The resulting inverted matrix.
*/
bool inverse(const TSparseMatrix &sparseMat, TSparseMatrix &invMat, bool isSPD)
{
	auto nRows = sparseMat.rows();
	auto nCols = sparseMat.cols();

	if (!sparseMat.isCompressed())
		throw std::runtime_error("inverse() method requires a sparse matrix in compressed mode. Call .makeCompressed() before passing.");
	if (nRows != nCols)
	{
		logDebug() << "The given matrix A is not a square matrix to inverse!";
		return false;
	}
	bool invertSuccess;
	if (isSPD)
	{
		invertSuccess = invertWithDecomposition<Eigen::SimplicialLDLT<TSparseMatrix>>(sparseMat, invMat);
	}
	else
	{
		invertSuccess = invertWithDecomposition<Eigen::SparseLU<TSparseMatrix>>(sparseMat, invMat);
	}

	return invertSuccess;
}

/*!
		\brief Solves the matricial equation A * X = B, where A is a squared sparse matrix, X and B are vectors
		\param[in]  matA is a square matrix
		\param[in]  vectB is a vector having the same dimension as the square matrix
		\param[out] vectX The resulting solution vector.
*/

bool solveUnique(const TSparseMatrix &matA, const TVector &vectB, TVector &vectX, bool isSPD)
{
	vectX.setZero();

	if (!matA.isCompressed())
		throw std::runtime_error("solveUnique() method requires a sparse matrix in compressed mode. Call .makeCompressed() before passing.");
	// A must be a square matrix in our case, and the number of B vector elements must be the same!
	if (matA.rows() != matA.cols() || vectB.rows() != matA.rows())
	{
		logDebug() << "The given matrix A is not a square matrix, or the number of vector B elements does not correspond to A dimensions!";
		return false;
	}
	bool solveSuccess = false;
	if (isSPD)
	{
		solveSuccess = solveUniqueWithDecomposition<Eigen::SimplicialLDLT<TSparseMatrix>>(matA, vectB, vectX);
		if (solveSuccess)
		{
			logDebug() << "Cholesky method is used for solving the equations system!";
		}
		else
		{
			logDebug() << "Cholesky method failed for solving the equations system! Check if matrix is symmetric and positive definite. ";
		}
	}
	else
	{
		solveSuccess = solveUniqueWithDecomposition<Eigen::SparseLU<TSparseMatrix>>(matA, vectB, vectX);
		if (solveSuccess)
		{
			logDebug() << "SparseLU method is used for solving the equations system!";
		}
		else
		{
			logDebug() << "SparseLU method failed for solving the equations system!";
		}
	}
	return solveSuccess;
}

inline double ABij(const TSparseMatrix &A, const TSparseMatrix &B, int i, int j)
{
	const Eigen::Index u(A.cols());
	double sum(0.0);

#pragma omp parallel for reduction(+ : sum)
	for (Eigen::Index r = 0; r < u; r++)
	{
		sum += A.coeff(i, r) * B.coeff(r, j);
	}

	return sum;
}

/*!
		\brief Optimized multiplication routine that returns the main diagonal of A*B*A'
		\param[in]  A sparse matrix
		\param[in]  B sparse matrix
		\param[out] res The resulting diagonal vector.
*/

TVector &multABATasDiag(TVector &res, const TSparseMatrix &A, const TSparseMatrix &B)
{
	const auto obs(A.rows());
	const auto ukn(A.cols());

	res.resize(obs);
	res.setZero();

	// TSparseMatrix AB(A*B);
#pragma omp parallel for
	for (Eigen::Index n = 0; n < obs; n++)
	{
		for (Eigen::Index u = 0; u < ukn; u++)
		{
			// for unknowns (u= num unknowns)
			// double abij = AB.coeff(n,u) ;
			double abij = ABij(A, B, (int)n, (int)u);
			res(n) += abij * A.coeff(n, u);
		}
	}
	return res;
}

double &checkedCoeffRef(TSparseMatrix &mat, int row, int col)
{
	bool isOutOfBound = !(row >= 0 && row < mat.rows() && col >= 0 && col < mat.cols());
	if (isOutOfBound)
	{
		throw std::runtime_error("Attempting to get reference of matrix entry at index (" + std::to_string(row) + " , " + std::to_string(col) + ") of ("
			+ std::to_string(mat.rows()) + " , " + std::to_string(mat.cols()) + ") dimensional matrix.");
	}
	return mat.coeffRef(row, col);
}

double &checkedCoeffRef(TVector &vec, int row)
{
	bool isOutOfBound = !(row >= 0 && row < vec.rows());
	if (isOutOfBound)
	{
		throw std::runtime_error("Attempting to get reference of vector entry at index " + std::to_string(row) + " of " + std::to_string(vec.rows()) + " dimensional vector.");
	}
	return vec.coeffRef(row);
}

bool isPositiveDefinite(const Eigen::MatrixXd &mat)
{
	if (mat.cols() != mat.rows())
	{
		throw std::runtime_error("test for positive definiteness only possible for square matrices");
	}
	// Compute the eigenvalues of the matrix
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(mat);
	if (solver.info() != Eigen::Success)
	{
		throw std::runtime_error("Eigenvalue computation failed!");
	}
	// test pos definiteness
	Eigen::Vector3d eigenvalues = solver.eigenvalues();
	bool isPositiveDefinite = (eigenvalues.array() > 0).all();
	return isPositiveDefinite;
}

} // namespace TSparseUtils
