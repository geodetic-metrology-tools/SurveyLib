#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <Eigen/Sparse>
#include <string>

typedef Eigen::SparseMatrix<double> TSparseMatrix;
typedef Eigen::VectorXd TVector;
typedef Eigen::Triplet<double> TTriplet;

namespace TSparseUtils {
TSparseMatrix inverse(const TSparseMatrix & matrix, std::string & error);
}

#endif
