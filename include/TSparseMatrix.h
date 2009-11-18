#ifndef T_SPARSE_MATRIX_H
#define T_SPARSE_MATRIX_H

#pragma once

#include "TColumnVector.h"

#define TAUCS_CORE_DOUBLE

extern "C" {
#include <taucs.h>
}

using namespace std;

class TSparseMatrix
{
public:

	TSparseMatrix(int columns, int rows, int nnz, list<double>* vals, list<int>* rowInds, list<int>* colPtr);
	// this does a shallow copy on purpose! The result matrix should not be changed!
	TSparseMatrix(const TSparseMatrix&);
	~TSparseMatrix();
	
	// Sparse matrix transposition.
	TSparseMatrix* transposed() const;

	// General multiplication of sparse matrices.
	TSparseMatrix* multiply(const TSparseMatrix& second) const;
	double* operator *(const TColumnVector& right) const;
	operator taucs_ccs_matrix*();
	double operator ()(int row, int column);
	
	void multiply_by_number(double);

	TSparseMatrix* invert_lower_triangular() const;
	double* multiply_returning_diagonal(const TSparseMatrix& second) const;
	double* multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_three_returning_lower_triangular(const TSparseMatrix& second, const TSparseMatrix& third) const;
	TSparseMatrix* multiply_returning_lower_triangular(const TSparseMatrix& second) const;

	static TSparseMatrix* getCholeskyFactor(void* symbolic);

	int columnsCount() const { return matrix->n; }
	int rowsCount() const { return matrix->m; }

	const double* values() const { return matrix->taucs_values; }
	const int* rowIndices() const { return matrix->rowind; }
	const int* colPointers() const { return matrix->colptr; }

	bool isLowerTriangular() const { return lowerTriangular; }

	void writeMatrixFile(char *) const;


private:

	TSparseMatrix(taucs_ccs_matrix* m);

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

		~Vector()
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

	// This should only be used by primitive types (int, float, double...)!
	template <typename T>
	class List
	{
	public:
		List()
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

	bool lowerTriangular;
	taucs_ccs_matrix *matrix;
};

#endif // T_SPARSE_MATRIX_H