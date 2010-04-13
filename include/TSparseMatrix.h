#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#define THRESHOLD LITERAL(0.0000000001)

#include "TColumnVector.h"

class TSparseMatrix
{
public:

	TSparseMatrix(int rows, int columns, real* vals, int* rowInds, int* colPtr);
	~TSparseMatrix();
	
	// Sparse matrix transposition.
	TSparseMatrix* transposed() const;
    // Sparse matrix inversion - the matrix should be symmetric, lower triangular, positive definite. Cholesky decomposition is used.
	TSparseMatrix* symmetric_lower_inverse() const;

	real* operator *(const real* right) const;
	real* operator *(const TColumnVector& right) const;
	real operator ()(int row, int column) const;

	bool operator ==(const TSparseMatrix&) const;
	bool operator !=(const TSparseMatrix&) const;
	
	void multiply_by_number(real);

	TSparseMatrix* cholesky_decompose_lower_triangular_returning_lower_triangular() const;
	TSparseMatrix* ldlt_decompose_lower_triangular_returning_lower_triangular(real*& D) const;
	TSparseMatrix* invert_diagonal_matrix() const;
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed() const;
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() const;
	TSparseMatrix* invert_lower_triangular_ldlt_decomposed(const real* D) const;
	TSparseMatrix* invert_lower_triangular_ldlt_decomposed_returning_lower_triangular(const real* D) const;
	real* invert_lower_triangular_ldlt_decomposed_returning_diagonal(const real* D) const;
	real* solve_eqn(const real* b) const;
	real* solve_ldlt(const real* D, const real* b) const;

    TSparseMatrix* add(const TSparseMatrix& second) const;

	// General multiplication of sparse matrices.
	TSparseMatrix* multiply_F(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_LM(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_diagonal(const real* second, int secondCols) const;
	TSparseMatrix* multiply_returning_unordered_F(const TSparseMatrix& second) const;
	real* multiply_returning_diagonal(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_lower_triangular_F(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const;

    TSparseMatrix* multiply_three_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
    TSparseMatrix* multiply_three_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;
	real* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;

	inline int columnsCount() const { return cols; }
	inline int rowsCount() const { return rows; }

	inline const real* values() const { return vals; }
	inline const int* rowIndices() const { return rowind; }
	inline const int* columnPointers() const { return colptr; }

	void write_matrix_file(const char *) const;
	static TSparseMatrix* read_matrix_file(const char *);

	static TSparseMatrix* deep_copy(const TSparseMatrix* matrix);

private:

	TSparseMatrix(int rows, int columns, int nnz)
	{
		this->rows = rows;
		cols = columns;

		vals = new real[nnz];
		colptr = new int[cols + 1];
		rowind = new int[nnz];
	}

    TSparseMatrix(int rows, int columns)
    {
        this->rows = rows;
        cols = columns;

        vals = NULL;
        rowind = NULL;
        colptr = new int[cols + 1];
    }

    inline void setNNZ(int nnz)
    {
        vals = new real[nnz];
        rowind = new int[nnz];
    }

	int cols;
	int rows;

	int* colptr;	// length cols + 1
	int* rowind;	// length colptr[cols]
	real* vals;	// length colptr[cols]

	template <typename T>
	class Vector
	{
	public:
		inline Vector(int initialSize)
		{
			allocated = initialSize;
			count = 0;
			values = new T[allocated];
		}

		inline ~Vector()
		{
			delete[] values;
		}

		void add(const T& elem)
		{
			if (count == allocated)
			{
				T *temp = new T[allocated];
				for (int i = 0; i < allocated; i++)
				{
					temp[i] = values[i];
				}
				delete[] values;
				values = new T[allocated * 2];
				for (int i = 0; i < allocated; i++)
				{
					values[i] = temp[i];
				}
				delete[] temp;
				allocated *= 2;			
			}
			values[count++] = elem;
		}

		inline const T& operator[] (int index) const
		{
			return values[index];
		}

		inline T& operator[] (int index)
		{
			return values[index];
		}

		inline int size() const
		{
			return count;
		}

	private:
		T *values;
		int count;
		int allocated;
	};
};

#endif // SPARSE_MATRIX_H
