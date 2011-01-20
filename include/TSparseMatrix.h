#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#define THRESHOLD LITERAL(0.0000000001)

#include "TColumnVector.h"
#include "TMatrix.h"

/*

CONTACT

If ANY of this code doesn't work or you have any suggestions for speed and/or space improvements, please write
to boris_petrov@live.com

GENERAL INFORMATION

The sparse matrix structure used is the so called Compressed Column Storage (CCS). Information about 
that can be found on the web. The constructor of the class accepts the number of rows, the number of 
columns, an array of values, an array of row indices (which should be the same length as the values and 
is 0-based) and an array of column pointers (with length columnsCount + 1, 0-based, where colptr[0] == 0 
and colptr[columnsCount] == length(values)). The arrays should be built before being passed to the 
constructor and they should NOT be deallocated after that as the matrix class is not making a copy of them. 
It is going to take care of the memory.

Practically none of the routines check for correct input so you should make sure that you are passing 
the right arguments.

This library can be found at: http://sparsematrix.codeplex.com

*/

class TSparseMatrix
{
public:

	// This sparse matrix uses CCS (Compressed Column Storage)
	// info: http://netlib2.cs.utk.edu/linalg/html_templates/node92.html

	TSparseMatrix(int rows, int columns, real* vals, int* rowInds, int* colPtr);
	~TSparseMatrix();
	
	// this returns a new matrix, which is the transpose of the original. Takes linear time on the number of non-zeros in the matrix.
	TSparseMatrix* transposed() const;
    // returns the inverse of a lower triangular, symmetric, positive-definite matrix. Cholesky decomposition is used. Returns a non-NULL pointer on success.
	TSparseMatrix* symmetric_lower_inverse() const;
	// same as the above, only saves the decomposition
	TSparseMatrix* symmetric_lower_inverse_saving_L(TSparseMatrix*& L) const;

	//****************************************************
	// multiplies the matrix by a column vector - returns another vector.
	real* operator *(const real* right) const;
	real* operator *(const TColumnVector& right) const;
	// returns the element in this row and column.
	real operator ()(int row, int column) const;
	
	// checks for equality and inequality. The THRESHOLD definition from the header is used. It can be changed arbitrarily to suit one's needs.
	bool operator ==(const TSparseMatrix&) const;
	bool operator !=(const TSparseMatrix&) const;
	//*****************************************************
	
	// multiplies the whole matrix by a number. This is done IN PLACE! It is one of only TWO routines which mutate the original matrix.
	void multiply_by_number(real);

	// Numerical Recipies in C++ Second edition
	// page 100, function choldc
	// as the long name says, it accepts a lower triangular symmetric matrix, which is being decomposed into L * LT (the lower part, i.e. L, is being returned on success). If the function fails, because the matrix is not positive-definite, NULL is returned.
	TSparseMatrix* cholesky_decompose_lower_triangular_returning_lower_triangular() const;
	// accepts a lower triangular symmetric matrix, which may or may not be positive-definite, as well as a pointer to a "real", which should NOT be allocated - the routine does that. It returns as result the L * D * LT decomposition of the matrix - L as an output (which is a unit-lower triangular matrix) and D in the argument that is passed. Returns NULL and an unallocated D pointer on failure. No pivoting is done whatsoever so take care, because the result may not be numerically stable.
	//*REAT THE COMMENT
	TSparseMatrix* ldlt_decompose_lower_triangular_returning_lower_triangular(real*& D) const;
	// finds the inverse of a matrix, that has elements only on the diagonal. Result is wrong if there are elements on other positions so make sure there aren't any.
	TSparseMatrix* invert_diagonal_matrix() const;
	// Numerical Recipies in C++ Second edition
	// page 101, code for inversion
	// should be called on the result from cholesky_decompose_lower_triangular_returning_lower_triangular - returns the whole inverse of L - LInv. This is probably slower than using the next function, transposing the result and then adding the two together. In addition to that, it is not a very useful thing to get anyway.
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed() const;
	// Numerical Recipies in C++ Second edition
	// page 101, code for inversion
	// the same as the above, i.e. accepts the Cholesky decomposition of a matrix and returns LInv, but only the lower part of it. This can be used to find the inverse of the original matrix (it is used internally in symmetric_lower_inverse).
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() const;
	// this, as opposed to the above two routines, returns the inverse of A 
	// (i.e. the original matrix, before decomposition), not of L. As the decomposition itself, this 
	// function does not do any kind of pivoting, and that is why I have found it to be not very useful in 
	// many cases, because the result is far from "the truth". 
	//*READ THE COMMENT
	TSparseMatrix* invert_lower_triangular_ldlt_decomposed(const real* D) const;
	// as the above, only returns the lower triangular part of A-inverse.
	TSparseMatrix* invert_lower_triangular_ldlt_decomposed_returning_lower_triangular(const real* D) const;

	// THIS IS NOT WORKING! DO NOT CALL!!!
	real* invert_lower_triangular_ldlt_decomposed_returning_diagonal(const real* D) const;
	// Numerical Recipies in C++ Second edition
	// page 100, function cholsl
	// called on the return from cholesky_decompose_lower_triangular_returning_lower_triangular and passing it a vector, it computes the solution of Ax = b, i.e. x is being returned, A being the original positive-definite matrix before decomposition.
	real* solve_eqn(const real* b) const;
	// called on the return from ldlt_decompose_lower_triangular_returning_lower_triangular and passing it D (again from there) and a vector, it computes the solution Ax = b. I have found that this gives really good results even though no pivoting is done in the decomposition.
	real* solve_ldlt(const real* D, const real* b) const;
	// the same as the above, only the "b" argument is being replaced from the solution. L transposed is required as an argument, too. I suggest you don't use that function, rather use the one above.
	//*READ THE COMMENT
	void solve_ldlt_in_place(const TSparseMatrix* LT, const real* D, real* b, int up_to = 0) const;

	// adds two sparse matrices. Linear in the number of non-zeros in both matrices combined.
    TSparseMatrix* add(const TSparseMatrix& second) const;

	// multiplies a general sparse matrix with another. The F stands for Fast. The routines with LM take Less Memory but are slower.

	TSparseMatrix* multiply_F(const TSparseMatrix& second) const;
	// see above.
	TSparseMatrix* multiply_LM(const TSparseMatrix& second) const;
	// multiplies the matrix by another, diagonal, one which has non-zero values in (at least almost) all diagonal positions. The second matrix is represented only as an array. Note that this is DIFFERENT than the operator *, which multiplies the matrix by a vector, not by a diagonal matrix!
	TSparseMatrix* multiply_diagonal_dense(const real* second, int secondCols) const;
	// same as the above, only that the diagonal matrix may have many zeros.
	TSparseMatrix* multiply_diagonal_sparse(const real* second, int secondCols) const;
	// again multiplies two general sparse matrices but returns an unordered one - i.e. a sparse matrix with row indices within the columns not necessarily being sorted. Such a matrix CANNOT be used in practically any of the other routines, except the multiplication ones, i.e. this should be used only as a middle product. It is probably faster than the other multiplication routines, but you should try it out first.
	//READ THIS COMMENT
	TSparseMatrix* multiply_returning_unordered_F(const TSparseMatrix& second) const;
	// to be used if you know that the result of multiplying two matrices is a diagonal one or you only care about the diagonal elements.
	//READ THIS COMMENT
	real* multiply_returning_diagonal(const TSparseMatrix& second) const;
    // if the result of the multiplication is a symmetric matrix and you want only the lower part (for example to use it for the Cholesky decompostion) - you can use that.
	TSparseMatrix* multiply_returning_lower_triangular_F(const TSparseMatrix& second) const;
    // less temporary memory, but slower than the above.
	TSparseMatrix* multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const;

	// same as the multiply versions, only with three matrices, not two. I have noticed that this is slower than just multiplying twice (i.e. first the first two, then the result with the third one) for some reason, so you might prefer using them.
    TSparseMatrix* multiply_three_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
    TSparseMatrix* multiply_three_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;
	real* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;

	// accessor functions.
	inline int columnsCount() const { return cols; }
	inline int rowsCount() const { return rows; }

	inline real* values() const { return vals; }
	inline int* rowIndices() const { return rowind; }
	inline int* columnPointers() const { return colptr; }

    // writes the matrix to a text file.
	void write_matrix_file(const char *) const;
    // reads a matrix from a text file.
	static TSparseMatrix* read_matrix_file(const char *);

    // makes a copy of a matrix.
	static TSparseMatrix* deep_copy(const TSparseMatrix* matrix);

	TMatrix* to_dense() const;

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
