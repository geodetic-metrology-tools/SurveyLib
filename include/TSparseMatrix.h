#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include "TColumnVector.h"

#define THRESHOLD 0.0000000001

class TSparseMatrix
{
public:

	TSparseMatrix(int rows, int columns, real* vals, int* rowInds, int* colPtr);
	// this does a shallow copy on purpose! The result matrix should not be changed!
	TSparseMatrix(const TSparseMatrix&);
	~TSparseMatrix();
	
	// Sparse matrix transposition.
	TSparseMatrix* transposed() const;

	real* operator *(const real* right) const;
	real* operator *(const TColumnVector& right) const;
	real operator ()(int row, int column) const;

	bool operator ==(const TSparseMatrix&) const;
	bool operator !=(const TSparseMatrix&) const;
	
	void multiply_by_number(real);

	TSparseMatrix* cholesky_decompose_lower_triangular_returning_lower_triangular() const;
	TSparseMatrix* invert_diagonal_matrix() const;
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed() const;
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() const;
	real* solve_eqn(const real* b) const;

    TSparseMatrix* add(const TSparseMatrix& second) const;

	// General multiplication of sparse matrices.
	TSparseMatrix* multiply_F(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_LM(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_unordered_F(const TSparseMatrix& second) const;
	real* multiply_returning_diagonal(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_lower_triangular_F(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const;

    TSparseMatrix* multiply_three_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
    TSparseMatrix* multiply_three_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;
	real* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;

	inline int columnsCount() const { return matrix->n; }
	inline int rowsCount() const { return matrix->m; }

	inline const real* values() const { return matrix->values; }
	inline const int* rowIndices() const { return matrix->rowind; }
	inline const int* colPointers() const { return matrix->colptr; }

	void writeMatrixFile(const char *) const;
	static TSparseMatrix* readMatrixFile(const char *);

	static TSparseMatrix* deepCopy(const TSparseMatrix* matrix);


private:

	struct Matrix
	{
		Matrix(int rows, int columns, int nnz)
		{
			m = rows;
			n = columns;

			values = new real[nnz];
			colptr = new int[n + 1];
			rowind = new int[nnz];
		}

		Matrix(int rows, int columns, real* vs, int* cs, int* rs)
		{
			m = rows;
			n = columns;

			values = vs;
			colptr = cs;
			rowind = rs;
		}

        Matrix(int rows, int columns)
        {
            m = rows;
            n = columns;

            values = NULL;
            colptr = new int[n + 1];
        }

        inline void setNNZ(int nnz)
        {
            values = new real[nnz];
            rowind = new int[nnz];
        }

        ~Matrix()
        {
            if (colptr != NULL)
            {
				if (colptr == rowind)
				{
					rowind = NULL;
				}
                delete[] colptr;
            }

            if (values != NULL)
            {
                delete[] values;
            }

            if (rowind != NULL)
            {
                delete[] rowind;
            }
        }

		int n; // columns
		int m; // rows

		int* colptr;
		int* rowind;
		real* values;
	};

	inline TSparseMatrix(Matrix* m)
	{
		matrix = m;
	}

	Matrix* matrix;

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
				//printf("Bad! Try not to get into here!\n"); // TODO: remove that
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
