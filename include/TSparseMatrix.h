#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#pragma once

#include <list>

#include "TColumnVector.h"

using namespace std;

class TSparseMatrix
{
public:

	TSparseMatrix(int rows, int columns, int nnz, list<quad>* vals, list<int>* rowInds, list<int>* colPtr);
	// this does a shallow copy on purpose! The result matrix should not be changed!
	TSparseMatrix(const TSparseMatrix&);
	~TSparseMatrix();
	
	// Sparse matrix transposition.
	TSparseMatrix* transposed() const;

	quad* operator *(const quad* right) const;
	quad* operator *(const TColumnVector& right) const;
	quad operator ()(int row, int column) const;
	
	void multiply_by_number(quad);

	TSparseMatrix* decompose_Cholesky() const;
	TSparseMatrix* invert_diagonal_matrix() const;
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed() const;
	TSparseMatrix* invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() const;
	quad* solve_eqn(const quad* b) const;

    TSparseMatrix* add(const TSparseMatrix& second) const;

	// General multiplication of sparse matrices.
	TSparseMatrix* multiply_F(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_LM(const TSparseMatrix& second) const;
	quad* multiply_returning_diagonal(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_lower_triangular_F(const TSparseMatrix& second) const;
	TSparseMatrix* multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const;

    TSparseMatrix* multiply_three_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
    TSparseMatrix* multiply_three_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;
	quad* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const;

	inline int columnsCount() const { return matrix->n; }
	inline int rowsCount() const { return matrix->m; }

	inline const quad* values() const { return matrix->values; }
	inline const int* rowIndices() const { return matrix->rowind; }
	inline const int* colPointers() const { return matrix->colptr; }

	void writeMatrixFile(char *) const;
	static TSparseMatrix* readMatrixFile(char *);

	static TSparseMatrix* deepCopy(TSparseMatrix* matrix);


private:

	struct Matrix
	{
		Matrix(int rows, int columns, int nnz)
		{
			m = rows;
			n = columns;

			values = new quad[nnz];
			colptr = new int[n + 1];
			rowind = new int[nnz];
		}

        Matrix(int m, int n)
        {
            this->m = m;
            this->n = n;

            values = NULL;
            colptr = new int[n + 1];
        }

        inline void setNNZ(int nnz)
        {
            values = new quad[nnz];
            rowind = new int[nnz];
        }

        ~Matrix()
        {
            if (colptr != NULL)
            {
                delete[] colptr;
            }

            if (values != NULL)
            {
                delete[] values;
                delete[] rowind;
            }
        }

		int n; // columns
		int m; // rows

		int* colptr;
		int* rowind;
		quad* values;
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
		Vector(int initialSize)
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

		inline int size() const
		{
			return count;
		}

	private:
		T *values;
		int count;
		int allocated;
	};

	// This should only be used by primitive types (int, float, quad...)!
	template <typename T>
	class List
	{
	public:
		inline List()
		{
			head = tail = NULL;
			count = 0;
		}

		~List()
		{
			while (head != tail)
			{
				Node* old = head;
				head = head->next;
				delete old;
			}
			if (head != NULL)
			{
				delete head;
			}
		}

		void add(const T value)
		{
			if (head == NULL)
			{
				head = new Node();
				head->elem = value;
				tail = head;
			}
			else
			{
				tail->next = new Node();
				tail->next->elem = value;
				tail = tail->next;
			}
			count++;
		}

		inline int size() const
		{
			return count;
		}

		inline void initIterator()
		{
			iter = head;
			iterHasMore = count != 0;
		}

		inline bool hasMore() const
		{
			return iterHasMore;
		}

		inline const T nextElement()
		{
			if (iter == tail)
			{
				iterHasMore = false;
			}
			T e = iter->elem;
			iter = iter->next;
			return e;
		}

	private:
		struct Node
		{
			T elem;
			Node *next;
		};
		Node* head;
		Node* tail;
		int count;

		Node* iter;
		bool iterHasMore;
	};
};

#endif // SPARSE_MATRIX_H
