

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <string>

#include <Eigen/Sparse>

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

bool inverse(const TSparseMatrix &sparseMat, TSparseMatrix &invMat, bool bTryCholeskyFirst = false, bool bTryFullPivotSecond = true);

bool solveUnique(const TSparseMatrix &matA, const TVector &vectB, TVector &vectX, bool bTryCholeskyFirst = true, bool bTryFullPivotSecond = true);

// optimized multiplication routine that returns the main diagonal of A*B*A'
TVector &multABATasDiag(TVector &res, const TSparseMatrix &A, const TSparseMatrix &B);
double &checkedCoeffRef(TSparseMatrix &mat, int row, int col);
double &checkedCoeffRef(TVector &mat, int row);
bool isPositiveDefinite(const Eigen::MatrixXd &mat);

} // namespace TSparseUtils

#endif
