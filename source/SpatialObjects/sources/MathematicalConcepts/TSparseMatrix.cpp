// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TSparseMatrix.h"

#include <mutex>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

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

	// use slight regularization
	TSparseMatrix id(A.rows(), A.cols());
	id.setIdentity();
	double reg = 0;
	TSparseMatrix AReg = A + reg * id;

	if (!scaleAndDecompose(AReg, useScaling, AScaled, d, solver))
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

static void printProgress(int current, int total, bool clear = false)
{
	if (total == 0)
		return;
	static std::mutex printMutex; // Thread-safety
	std::lock_guard<std::mutex> lock(printMutex);
	const int barWidth = 50;
	const int clearWidth = 200; // Fixed generous width to clear the line fully
	float progress = static_cast<float>(current) / total;
	// Higher resolution: total "sub-steps" = barWidth * 8
	float finePos = barWidth * progress * 8.0f;
	int fullBlocks = static_cast<int>(finePos / 8);
	int fracBlock = static_cast<int>(finePos) % 8;
	// Spinning animation (fancy!)
	static const char spinner[] = {'|', '/', '-', '\\'};
	static int spinIdx = 0;
	char spinChar = spinner[spinIdx % 4];
	spinIdx++;
	// Compute color for spinner based on overall progress (red to green)
	int spinR = static_cast<int>(255 * (1 - progress));
	int spinG = static_cast<int>(255 * progress);
	int spinB = 0;
	std::string spinColor = "\033[38;2;" + std::to_string(spinR) + ";" + std::to_string(spinG) + ";" + std::to_string(spinB) + "m";
	// Reset color
	const std::string reset = "\033[0m";
	// Unicode fractional blocks (from 0/8 to 8/8)
	static const std::string blocks[9] = {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"};
	std::ostringstream oss;
	oss << "Inversion progress " << spinColor << spinChar << reset << " [";
	// Filled part with gradient from red to green based on position
	for (int k = 0; k < fullBlocks; ++k)
	{
		float frac = static_cast<float>(k) / (barWidth - 1);
		int R = static_cast<int>(255 * (1 - frac));
		int G = static_cast<int>(255 * frac);
		int B = 0;
		std::string color = "\033[38;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m";
		oss << color << blocks[8];
	}
	if (fullBlocks < barWidth)
	{
		float frac = static_cast<float>(fullBlocks) / (barWidth - 1);
		int R = static_cast<int>(255 * (1 - frac));
		int G = static_cast<int>(255 * frac);
		int B = 0;
		std::string color = "\033[38;2;" + std::to_string(R) + ";" + std::to_string(G) + ";" + std::to_string(B) + "m";
		oss << color << blocks[fracBlock];
	}
	oss << reset;
	for (int k = fullBlocks + 1; k < barWidth; ++k)
	{
		oss << " ";
	}
	oss << "] " << std::fixed << std::setprecision(0) << progress * 100.0 << "% " << current << "/" << total;
	std::string line = oss.str();
	std::cout << "\r" << std::string(clearWidth, ' ') << "\r" << line;
	if (clear)
	{
		std::cout << "\r" << std::string(clearWidth, ' ') << "\r";
	}
	std::cout.flush();
}

template<typename Decomposition>
bool invertWithDecomposition(const TSparseMatrix &A, TSparseMatrix &invMat, bool useScaling, const InverseExtras &extras)
{
	const int nRows = A.rows();
	if (nRows == 0)
	{
		invMat.resize(0, 0);
		return true;
	}
	// determine the size of the top left block of the inverse to compute
	const int m = (extras.topLeftSize > 0) ? std::min(extras.topLeftSize, nRows) : nRows;
	TSparseMatrix AScaled;
	TVector d;
	// use slight regularization
	TSparseMatrix id(A.rows(), A.cols());
	id.setIdentity();
	double reg = 0;
	//1e-6;
	TSparseMatrix AReg = A + reg * id;
	Decomposition solver;
	if (!scaleAndDecompose(AReg, useScaling, AScaled, d, solver))
	{
		return false;
	}
	const Eigen::DiagonalMatrix<double, Eigen::Dynamic> D(d);
	// Optional diagonal request?
	const bool wantDiagonal = (extras.M != nullptr) && (extras.diag_MinvMT != nullptr);
	if (wantDiagonal)
	{
		if (extras.M->cols() != m)
		{
			// columns of M must match m (top-left size)
			return false;
		}
		extras.diag_MinvMT->setZero(extras.M->rows()); // will be filled after the parallel section
	}
	int bandWidth = extras.bandWidth;
	// Effective bandwidth; if <=0, treat as full (bandWidth = m-1)
	const int bw = (bandWidth <= 0) ? (m - 1) : bandWidth;
	// variable to estimate the condition number
	double maxRatio = 0;
	// Vector to store norms for maxRatio calculation
	TVector norms(m);
	norms.setZero();
	// Per-thread partial diagonals for diag(M * Qxx * M^T) (empty if not needed)
	int max_threads = 1;
#ifdef _OPENMP
	max_threads = omp_get_max_threads();
#endif
	std::vector<TVector> partialDiags(max_threads);
	int num_threads_used = 1;
	// Band storage for the inverse elements
	const int band_rows = 2 * bw + 1;
	Eigen::MatrixXd band(band_rows, m);
	// Progress tracking
	std::atomic<int> completed(0);
	// Single parallel loop for both cases: normal and diagonal requested
#pragma omp parallel
	{
#ifdef _OPENMP
		int tid = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
#	pragma omp master
		{
			num_threads_used = num_threads;
		}
#else
		int tid = 0;
		int num_threads = 1;
#endif
		TVector localDiag;
		if (wantDiagonal)
		{
			localDiag = TVector::Zero(extras.M->rows());
		}
#pragma omp for nowait
		for (int i = 0; i < m; ++i)
		{
			TVector bScaled = TVector::Zero(nRows);
			bScaled[i] = 1.0;
			if (useScaling)
			{
				bScaled = D * bScaled;
			}
			TVector y = solver.solve(bScaled);
			norms[i] = y.norm();
			TVector sol = useScaling ? D * y : y; // scaling case: A' y = b' => A (D y) = b, i.e. D y is the solution of the original system
			TVector x_i = sol.head(m);
			// Store only the band around the diagonal
			const int lower = std::max(0, i - bw);
			const int upper = std::min(m - 1, i + bw);
			for (int j = lower; j <= upper; ++j)
			{
				int r = j - i + bw;
				band(r, i) = x_i[j];
			}
			// accumulate diag(M * Qxx * M^T) if requested (using full x_i for accuracy)
			if (wantDiagonal)
			{
				const TVector t = (*extras.M) * x_i; // size p (sparse*dense)
				// iterate non-zeros of column i of M (column-major assumed)
				for (TSparseMatrix::InnerIterator it(*extras.M, i); it; ++it)
				{
					const int row = it.row();
					localDiag[row] += it.value() * t[row];
				}
			}
			// Update progress
			++completed;
			if (completed % 100 == 0)
			{
				printProgress(completed.load(), m);
			}
		}
		if (wantDiagonal)
		{
			partialDiags[tid] = std::move(localDiag);
		}
	}
	// Finish progress bar
	printProgress(m, m);
	std::cout << std::endl;
	maxRatio = norms.maxCoeff();
	if (maxRatio > 1e+12)
	{
		std::stringstream msg;
		msg << std::scientific << std::setprecision(3) << "Condition number estimate = " << maxRatio << " indicating ill-conditioned matrix, possibly singular.";
		logWarning() << msg.str();
	}
	// Adding up all diagonals from different threads to compute diag(M * Qxx * M^T)
	if (wantDiagonal)
	{
		for (int t = 0; t < num_threads_used; ++t)
		{
			(*extras.diag_MinvMT) += partialDiags[t];
		}
	}
	// Combine band storage into triplet list
	std::vector<Eigen::Triplet<double>> triplets;
	size_t est_nnz = static_cast<size_t>(m) * (2LL * bw + 1);
	if (est_nnz > static_cast<size_t>(m) * m)
		est_nnz = static_cast<size_t>(m) * m; // cap for large bw
	triplets.reserve(est_nnz);
	for (int i = 0; i < m; ++i)
	{
		const int lower = std::max(0, i - bw);
		const int upper = std::min(m - 1, i + bw);
		for (int j = lower; j <= upper; ++j)
		{
			int r = j - i + bw;
			triplets.push_back(Eigen::Triplet<double>(j, i, band(r, i)));
		}
	}
	// Set the sparse inverse matrix from triplets
	invMat.resize(m, m);
	invMat.setFromTriplets(triplets.begin(), triplets.end());
	invMat.makeCompressed();
	return true;
}




/*!
		\brief Main method for inverting sparse matrices
		\param[in]  sparseMat The sparse matrix to be inverted
		\param[out] invMat    The resulting inverted matrix.
*/
bool inverse(const TSparseMatrix &sparseMat, TSparseMatrix &invMat, bool isSPD, const InverseExtras& extras)
{
	auto nRows = sparseMat.rows();
	auto nCols = sparseMat.cols();

	//std::cout << "inversion and res covar starts" << std::endl;
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
		invertSuccess = invertWithDecomposition<Eigen::SimplicialLDLT<TSparseMatrix>>(sparseMat, invMat, true, extras);
	}
	else
	{
		invertSuccess = invertWithDecomposition<Eigen::SparseLU<TSparseMatrix>>(sparseMat, invMat, true, extras);
	}
	//std::cout << "inversion and res covar finished" << std::endl;
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

void saveToMatrixMarket(const std::string &filename, const Eigen::SparseMatrix<double> &matrix)
{
	
		std::ofstream out(filename);
		if (!out.is_open())
		{
			throw std::runtime_error("Cannot open file: " + filename);
		}
		out << std::setprecision(17);
		// Header
		out << "%%MatrixMarket matrix format: row, column, value, indices 1-based \n";
		out << matrix.rows() << " " << matrix.cols() << " " << matrix.nonZeros() << "\n";

		// Write non-zeros (1-based indices; loop handles ColMajor/RowMajor via InnerIterator)
		for (int k = 0; k < matrix.outerSize(); ++k)
		{
			for (Eigen::SparseMatrix<double>::InnerIterator it(matrix, k); it; ++it)
			{
				out << (it.row() + 1) << " " << (it.col() + 1) << " " << it.value() << "\n";
			}
		}

		out.close();
	
}

bool isPositiveDefinite(const TDenseMatrix &mat)
{
	if (mat.cols() != mat.rows())
	{
		throw std::runtime_error("test for positive definiteness only possible for square matrices");
	}
	// Compute the eigenvalues of the matrix
	Eigen::SelfAdjointEigenSolver<TDenseMatrix> solver(mat);
	if (solver.info() != Eigen::Success)
	{
		throw std::runtime_error("Eigenvalue computation failed!");
	}
	// test pos definiteness
	Eigen::Vector3d eigenvalues = solver.eigenvalues();
	bool isPositiveDefinite = (eigenvalues.array() > 0).all();
	return isPositiveDefinite;
}

TSparseMatrix symbolicMtM(const TSparseMatrix &M)
{
	// Compute the sparsity pattern of M^T * M without numeric values.
	// For each column j of M^T (= row j of M), find all nonzero column indices.
	// The pattern of M^T * M has entry (j,k) if columns j and k of M^T share a nonzero row,
	// i.e., if there exists some row i where both M(i,j) != 0 and M(i,k) != 0.
	const int n = static_cast<int>(M.cols());
	std::vector<TTriplet> triplets;

	// M is column-major. Build a row-to-columns map.
	std::vector<std::vector<int>> rowCols(M.rows());
	for (int col = 0; col < M.outerSize(); ++col)
	{
		for (TSparseMatrix::InnerIterator it(M, col); it; ++it)
		{
			rowCols[it.row()].push_back(col);
		}
	}

	// For each row, all pairs of column indices contribute to the pattern
	std::vector<std::set<int>> colSets(n);
	for (int i = 0; i < static_cast<int>(rowCols.size()); ++i)
	{
		const auto &cols = rowCols[i];
		for (size_t a = 0; a < cols.size(); ++a)
		{
			for (size_t b = a; b < cols.size(); ++b)
			{
				colSets[cols[a]].insert(cols[b]);
				colSets[cols[b]].insert(cols[a]);
			}
		}
	}

	for (int j = 0; j < n; ++j)
	{
		for (int k : colSets[j])
		{
			triplets.emplace_back(j, k, 1.0); // value doesn't matter, just structure
		}
	}

	TSparseMatrix result(n, n);
	result.setFromTriplets(triplets.begin(), triplets.end());
	result.makeCompressed();
	return result;
}

TVector diagMQMt(const TSparseMatrix &M, const TSparseMatrix &Q)
{
	// Compute diag(M * Q * M^T) using sparse Q.
	// Element i = sum_{j,k} M_{ij} * Q_{jk} * M_{ik}
	// We iterate over nonzero pairs (i,j) in M, and for each such j,
	// iterate over nonzero entries Q_{j,k}, and accumulate M_{ik} * Q_{jk} * M_{ij}.
	const int nRows = static_cast<int>(M.rows());
	TVector result = TVector::Zero(nRows);

	// Build row-wise access to M (M is column-major)
	// For each row i: list of (col, value) pairs
	std::vector<std::vector<std::pair<int, double>>> Mrows(nRows);
	for (int col = 0; col < M.outerSize(); ++col)
	{
		for (TSparseMatrix::InnerIterator it(M, col); it; ++it)
		{
			Mrows[it.row()].emplace_back(col, it.value());
		}
	}

	// For each row i of M
	for (int i = 0; i < nRows; ++i)
	{
		const auto &row = Mrows[i];
		double sum = 0.0;
		for (size_t a = 0; a < row.size(); ++a)
		{
			int j = row[a].first;
			double Mij = row[a].second;
			for (size_t b = 0; b < row.size(); ++b)
			{
				int k = row[b].first;
				double Mik = row[b].second;
				// Q is symmetric, so Q(j,k) == Q(k,j). Look up whichever is stored.
				double Qjk = Q.coeff(j, k);
				sum += Mij * Qjk * Mik;
			}
		}
		result[i] = sum;
	}
	return result;
}

TSparseMatrix takahashiSelectedInverse(
	const Eigen::SimplicialLDLT<TSparseMatrix> &ldlt,
	const TVector &scalingVector,
	const TSparseMatrix *augmentedPattern)
{
	// LDLT gives P * A_scaled * P^T = L * D * L^T
	// => Q_original = D_s * P^T * (LDL^T)^{-1} * P * D_s
	const TVector D = ldlt.vectorD();
	const auto &Pinv = ldlt.permutationPinv();
	const int n = static_cast<int>(D.size());

	TSparseMatrix Lmat = ldlt.matrixL(); // unit lower triangular in permuted space

	// Build working pattern: L merged with optional augmented pattern (permuted into factorization ordering)
	TSparseMatrix Laug;
	if (augmentedPattern != nullptr)
	{
		TSparseMatrix augPerm;
		augPerm = augmentedPattern->twistedBy(ldlt.permutationP());
		std::vector<TTriplet> triplets;
		triplets.reserve(Lmat.nonZeros() + augPerm.nonZeros());
		for (int col = 0; col < Lmat.outerSize(); ++col)
			for (TSparseMatrix::InnerIterator it(Lmat, col); it; ++it)
				triplets.emplace_back(it.row(), it.col(), it.value());
		for (int col = 0; col < augPerm.outerSize(); ++col)
			for (TSparseMatrix::InnerIterator it(augPerm, col); it; ++it)
				if (it.row() > it.col())
					triplets.emplace_back(it.row(), it.col(), 0.0);
		Laug.resize(n, n);
		Laug.setFromTriplets(triplets.begin(), triplets.end());
		Laug.makeCompressed();
	}
	else
	{
		Laug = Lmat;
	}

	// Allocate Q with same structure as Laug (lower triangle), values zeroed.
	// Must NOT use Eigen's setZero() which destroys the structural pattern.
	TSparseMatrix Qperm = Laug;
	for (int col = 0; col < Qperm.outerSize(); ++col)
		for (TSparseMatrix::InnerIterator it(Qperm, col); it; ++it)
			it.valueRef() = 0.0;

	// Symmetric access helpers (we store lower triangle only)
	auto getQ = [&](int i, int j) -> double
	{
		return (i >= j) ? Qperm.coeff(i, j) : Qperm.coeff(j, i);
	};
	auto setQ = [&](int i, int j, double val)
	{
		if (i >= j) Qperm.coeffRef(i, j) = val;
		else        Qperm.coeffRef(j, i) = val;
	};

	// Takahashi recursion (Erisman-Tinney), columns right to left.
	// S_j = {k > j : L_{kj} != 0}
	// Off-diagonal (i > j): Q_{ij} = -sum_{k in S_j} L_{kj} * Q_{ik}
	// Diagonal:              Q_{jj} = 1/D_j - sum_{k in S_j} L_{kj} * Q_{kj}
	// Off-diagonals must be computed before diagonal (diagonal uses Q_{kj} from same column).
	for (int j = n - 1; j >= 0; --j)
	{
		// Collect S_j from original L (not augmented — augmented entries have L_{kj}=0)
		std::vector<std::pair<int, double>> Sj;
		for (TSparseMatrix::InnerIterator it(Lmat, j); it; ++it)
			if (it.row() > j)
				Sj.emplace_back(it.row(), it.value());

		// Off-diagonal entries first
		for (TSparseMatrix::InnerIterator it(Laug, j); it; ++it)
		{
			int i = static_cast<int>(it.row());
			if (i <= j) continue;
			double qij = 0.0;
			for (const auto &[k, Lkj] : Sj)
				qij -= Lkj * getQ(i, k);
			setQ(i, j, qij);
		}

		// Diagonal
		double qjj = 1.0 / D[j];
		for (const auto &[k, Lkj] : Sj)
			qjj -= Lkj * getQ(k, j);
		setQ(j, j, qjj);
	}

	// Symmetrize: Q_full = lower + upper - diagonal
	TSparseMatrix QpermFull = Qperm + TSparseMatrix(Qperm.transpose());
	for (int i = 0; i < n; ++i)
		QpermFull.coeffRef(i, i) = Qperm.coeff(i, i);

	// Un-permute and un-scale: Q = D_s * P^T * Q_perm * P * D_s
	const Eigen::DiagonalMatrix<double, Eigen::Dynamic> Ds(scalingVector);
	TSparseMatrix Qscaled;
	Qscaled = QpermFull.twistedBy(Pinv);
	TSparseMatrix Q = Ds * Qscaled * Ds;
	Q.makeCompressed();
	return Q;
}

} // namespace TSparseUtils
