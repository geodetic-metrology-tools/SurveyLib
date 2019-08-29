/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <Eigen/Sparse>
#include <string>

typedef Eigen::SparseMatrix<double> TSparseMatrix;
typedef Eigen::MatrixXd TDenseMatrix;
typedef Eigen::VectorXd TVector;
typedef Eigen::Triplet<double> TTriplet;

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMatrixDouble;

namespace TSparseUtils {

	bool inverse(const TSparseMatrix &sparseMat, TSparseMatrix &invMat, bool bTryCholeskyFirst = false, bool bTryFullPivotSecond = true);
	
	bool solveUnique(const TSparseMatrix &matA, const TVector &vectB, TVector &vectX, bool bTryCholeskyFirst = true, bool bTryFullPivotSecond = true);
	
	// optimized multiplication routine that returns the main diagonal of A*B*A'
	TVector& multABATasDiag(TVector& res, const TSparseMatrix& A, const TSparseMatrix& B);

}

#endif
