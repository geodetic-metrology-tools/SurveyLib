/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <string>

#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>

#include <Quad.h>

typedef Eigen::SparseMatrix<double> TSparseMatrix;
typedef Eigen::MatrixXd TDenseMatrix;
typedef Eigen::VectorXd TVector;
typedef Eigen::Triplet<double> TTriplet;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMatrixDouble;

class TSparseMatrixWithTriplets
{
public:
	TSparseMatrixWithTriplets(int rows, int cols) : fRows(rows), fCols(cols), fMatrix(rows, cols), isFinalized(false)
	{ // rough estimate of how much matrix entries to avoid frequent reallocation
		// 10 entries per row corresponds to observations that depend on up to 10 parameters
		fTriplets.reserve(10 * rows);
	}
	void addTriplet(int row, int col, double value)
	{
		fTriplets.emplace_back(row, col, value);
		isFinalized = false;
	}
	void clearTriplets()
	{
		fTriplets.clear();
		fMatrix = TSparseMatrix(fRows, fCols);
		isFinalized = false;
	}
	void finalize()
	{
		if (!isFinalized)
		{
			fMatrix.setFromTriplets(fTriplets.begin(), fTriplets.end());
			fMatrix.makeCompressed();
			isFinalized = true;
		}
	}
	const TSparseMatrix &getMatrix() const
	{
		if (!isFinalized)
			throw std::logic_error("Matrix must be finalized before use. Call finalize() before getMatrix().");
		return fMatrix;
	}
	bool hasEmptyRows() const
	{
		// checks if there are empty rows
		for (size_t i = 0; i < fRows; i++)
		{
			bool hasEntries = false;
			for (const auto &triplet : fTriplets)
			{
				if ((triplet.row() == i) && (notZero(triplet.value())))
				{
					hasEntries = true;
					break;
				}
			}
			if (!hasEntries)
			{
				return true;
			}
		}
		return false;
	}

private:
	int fRows, fCols;
	std::vector<Eigen::Triplet<double>> fTriplets;
	TSparseMatrix fMatrix;
	bool isFinalized;
};

namespace TSparseUtils
{
struct InverseExtras
{
	// tell the inverse method to only compute a certain size top left block of the inverse matrix, the default value -1 means the whole inverse is computed
	int topLeftSize = -1;
	int bandWidth = -1;
	// if M and specified diag_MinvMT are specified, this triggers the computation of diag(M invMat M^T) in the inverse method
	const Eigen::SparseMatrix<double> *M = nullptr;
	Eigen::VectorXd *diag_MinvMT = nullptr;
};
// solve and invert using different methods depending wether the matrix is SPD (symmetric positive definite) or not
TSparseMatrix createSymmetricScaling(const TSparseMatrix &inputMat, TVector &scalingVector);
bool inverse(const TSparseMatrix &sparseMat, TSparseMatrix &invMat, bool isSPD, const InverseExtras &extras = {});
bool solveUnique(const TSparseMatrix &matA, const TVector &vectB, TVector &vectX, bool isSPD);

// optimized multiplication routine that returns the main diagonal of A*B*A'
TVector &multABATasDiag(TVector &res, const TSparseMatrix &A, const TSparseMatrix &B);
double &checkedCoeffRef(TSparseMatrix &mat, int row, int col);
double &checkedCoeffRef(TVector &mat, int row);
// test for positive definitness. Only usable for small, dense matrices, expensive
bool isPositiveDefinite(const Eigen::MatrixXd &mat);
void saveToMatrixMarket(const std::string &filename, const Eigen::SparseMatrix<double> &matrix);

struct TakahashiResult
{
	TSparseMatrix Q;  // selected elements of Q = A^{-1}, in the sparsity pattern of L + L^T + diagonal
	TVector diagonal; // diagonal of Q (always computed, also present in Q)
};

// Takahashi (Erisman-Tinney) selected inversion from an existing SimplicialLDLT factorization.
// Computes elements of Q = A^{-1} within the sparsity pattern of the Cholesky factor L.
// scalingVector: the diagonal scaling D_s such that the factorization was performed on D_s * A * D_s.
//                Pass a ones-vector if no scaling was used.
// augmentedPattern: if non-null, its sparsity pattern is merged into L's pattern before the
//                   selected inversion. Use this to ensure that all entries needed for
//                   diag(M * Q * M^T) are computed (pass the symbolic sparsity of M^T * M).
TakahashiResult takahashiSelectedInverse(
	const Eigen::SimplicialLDLT<TSparseMatrix> &ldlt,
	const TVector &scalingVector,
	const TSparseMatrix *augmentedPattern = nullptr);

// Compute the symbolic sparsity pattern of M^T * M (no numeric values, just structure).
// Useful for building the augmented pattern for Takahashi when diag(M * Q * M^T) is needed.
TSparseMatrix symbolicMtM(const TSparseMatrix &M);

// Compute diag(M * Q * M^T) using only the selected elements stored in Q (sparse).
// M must be sparse; Q is a sparse matrix containing the selected inverse elements.
// Precondition: all entries Q_{jk} needed (where M_{ij} != 0 and M_{ik} != 0) must be present in Q.
TVector diagMQMt(const TSparseMatrix &M, const TSparseMatrix &Q);

} // namespace TSparseUtils

#endif
