#include "TSparseMatrix.h"

template <typename T, typename U, typename V>
class Tuple
{
public:
	T a;
	U b;
	V c;
};

int tuple_cmp(const void *a, const void *b);
int binary_search(int arr[], int size, int value);

TSparseMatrix::TSparseMatrix(int columns, int rows, int nnz, list<double>* vals, list<int>* rowInds, list<int>* colPtr)
{
	matrix = taucs_ccs_create(rows, columns, nnz, TAUCS_DOUBLE);
	list<double>::const_iterator iter = vals->begin();
	list<int>::const_iterator iterR = rowInds->begin();
	list<int>::const_iterator iterC = colPtr->begin();
	for (int i = 0; i < nnz; i++)
	{
		matrix->taucs_values[i] = *iter;
		matrix->rowind[i] = *iterR;
		iter++;
		iterR++;
	}
	for (int i = 0; i <= columns; i++)
	{
		matrix->colptr[i] = *iterC;
		iterC++;
	}
}

TSparseMatrix::TSparseMatrix(const TSparseMatrix& other)
{
	matrix = other.matrix;
	lowerTriangular = other.lowerTriangular;
}

TSparseMatrix::TSparseMatrix(taucs_ccs_matrix* m)
{
	matrix = m;
	if (m->flags & TAUCS_LOWER)
	{
		lowerTriangular = true;
	}
}

TSparseMatrix::~TSparseMatrix()
{
	taucs_ccs_free(matrix);
}

TSparseMatrix* TSparseMatrix::transposed() const
{
	int nnz = matrix->colptr[matrix->n];
	taucs_ccs_matrix *result = taucs_ccs_create(matrix->n, matrix->m, nnz, TAUCS_DOUBLE);

	int i;
	Tuple<int, double, int> *t = new Tuple<int, double, int>[nnz];
	for (i = 0; i < nnz; i++)
	{
		t[i].a = matrix->rowind[i];
		t[i].b = matrix->taucs_values[i];
		t[i].c = i;
	}
	qsort(t, nnz, sizeof(Tuple<int, double, int>), tuple_cmp);

	int last = t[0].a;
	int used = 1;
	result->colptr[0] = 0;
	for (i = 0; i < nnz; i++)
	{
		while (t[i].a != last)
		{
			result->colptr[used++] = i;
			last++;
		}
		result->taucs_values[i] = t[i].b;
		result->rowind[i] = binary_search(matrix->colptr, matrix->n + 1, t[i].c);
	}
	result->colptr[used] = nnz;

	delete[] t;

	return new TSparseMatrix(result);
}

TSparseMatrix::operator taucs_ccs_matrix*()
{
	return matrix;
}

TSparseMatrix* TSparseMatrix::multiply(const TSparseMatrix& second) const
{
	int secondColumns = second.columnsCount();
	int *colptr = new int[secondColumns + 1];
	double *resultColumn = new double[matrix->m];
	List<double> results;
	List<int> rowInds;
    int i, k, l;
    taucs_ccs_matrix *result;
    colptr[0] = 0;
    for (i = 0; i < matrix->m; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < secondColumns; i++)
    {
        for (k = second.colPointers()[i]; k < second.colPointers()[i + 1]; k++)
        {
            for (l = matrix->colptr[second.rowIndices()[k]]; l < matrix->colptr[second.rowIndices()[k] + 1]; l++)
            {
				resultColumn[matrix->rowind[l]] += second.values()[k] * matrix->taucs_values[l];
            }
        }
        for (k = 0; k < matrix->m; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
				resultColumn[k] = 0;
            }
        }
        colptr[i + 1] = results.size();
    }
    result = taucs_ccs_create(matrix->m, secondColumns, results.size(), TAUCS_DOUBLE);
    for (i = 0; i <= secondColumns; i++)
    {
        result->colptr[i] = colptr[i];
    }
	results.initIterator();
	rowInds.initIterator();
	for (i = 0; results.hasMore(); i++)
	{
        result->taucs_values[i] = results.nextElement();
        result->rowind[i] = rowInds.nextElement();
	}

	delete[] colptr;
	delete[] resultColumn;

    return new TSparseMatrix(result);
}

double TSparseMatrix::operator ()(int row, int column)
{
	int i = matrix->colptr[column];
	while (matrix->rowind[i] < row && i < matrix->colptr[column + 1])
	{
		i++;
	}
	if (matrix->rowind[i] == row && i < matrix->colptr[column + 1])
	{
		return matrix->taucs_values[i];
	}
	return 0;
}

double* TSparseMatrix::operator *(const TColumnVector& right) const
{
	int i, j;

	double* result = new double[matrix->m];
	
	for (i = 0; i < matrix->m; i++)
	{
		result[i] = 0;
	}

    for (i = 0; i < matrix->n; i++)
	{
		if (right(i) != 0)
		{
			for (j = matrix->colptr[i]; j < matrix->colptr[i + 1]; j++)
			{
				result[matrix->rowind[j]] += right(i) * matrix->taucs_values[j];
			}
		}
	}

	return result;
}

TSparseMatrix* TSparseMatrix::getCholeskyFactor(void* symbolic)
{
	TSparseMatrix *L = new TSparseMatrix(taucs_supernodal_factor_to_ccs(symbolic));
	taucs_supernodal_factor_free(symbolic);

	return L;
}

TSparseMatrix* TSparseMatrix::invert_lower_triangular() const
{
	if (!(this->isLowerTriangular()))
	{
		return NULL;
	}
	
	TSparseMatrix* transposed = this->transposed(); // TODO: isn't there another way?
	
	Vector<double> results(matrix->colptr[matrix->n] * 4); // TODO: perhaps 4 times is too much?
	Vector<int> rowInds(matrix->colptr[matrix->n] * 4);
	int *colptr = new int[matrix->n + 1];

	int i, j, k, l;
	double sum = 0;

	colptr[0] = 0;

    for (i = 0; i < matrix->n; i++)
    {
        results.add(1.0 / matrix->taucs_values[matrix->colptr[i]]);
        rowInds.add(i);

        for (j = i + 1; j < matrix->n; j++)
        {
			int size = results.size();
            for (k = colptr[i], l = transposed->colPointers()[j];
                k < size &&
                rowInds[k] < j &&
                l < transposed->colPointers()[j + 1] &&
                transposed->rowIndices()[l] < j; )
            {
                if (rowInds[k] == transposed->rowIndices()[l])
                {
                    sum -= results[k] * transposed->values()[l];
                    k++;
                    l++;
                }
                else if (transposed->rowIndices()[l] < rowInds[k])
                {
                    l++;
                }
                else
                {
                    k++;
                }
            }

            if (sum != 0)
            {
                rowInds.add(j);
                results.add(sum / matrix->taucs_values[matrix->colptr[j]]);
                sum = 0;
            }
        }
        colptr[i + 1] = results.size();
	}
	
	delete transposed;

	taucs_ccs_matrix *result = taucs_ccs_create(matrix->n, matrix->n, results.size(), TAUCS_DOUBLE | TAUCS_SYMMETRIC | TAUCS_LOWER);

	for (i = 0; i <= matrix->n; i++)
	{
		result->colptr[i] = colptr[i];
	}
	for (i = 0; i < results.size(); i++)
	{
		result->rowind[i] = rowInds[i];
		result->taucs_values[i] = results[i];
	}

	delete[] colptr;

	return new TSparseMatrix(result);
}

double* TSparseMatrix::multiply_returning_diagonal(const TSparseMatrix& second) const
{
	double* result = new double[second.columnsCount()];
    int i, k, l, secondN = second.columnsCount() / 2;
    for (i = 0; i < secondN; i++)
    {
		result[i] = 0;
        for (k = second.colPointers()[i]; k < second.colPointers()[i + 1]; k++)
        {
			l = matrix->colptr[second.rowIndices()[k]];
			while (matrix->rowind[l] < i && l < matrix->colptr[second.rowIndices()[k] + 1])
			{
				l++;
			}
			if (matrix->rowind[l] == i && l < matrix->colptr[second.rowIndices()[k] + 1])
			{
				result[i] += matrix->taucs_values[l] * second.values()[k];
			}
        }
    }
    for ( ; i < second.columnsCount(); i++)
    {
		result[i] = 0;
        for (k = second.colPointers()[i]; k < second.colPointers()[i + 1]; k++)
        {
			l = matrix->colptr[second.rowIndices()[k] + 1] - 1;
			while (matrix->rowind[l] > i && l >= matrix->colptr[second.rowIndices()[k]])
			{
				l--;
			}
			if (matrix->rowind[l] == i && l >= matrix->colptr[second.rowIndices()[k]])
			{
				result[i] += matrix->taucs_values[l] * second.values()[k];
			}
		}
    }

	return result;
}

double* TSparseMatrix::multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	double* result = new double[third.columnsCount()]; // TODO: is that correct?
	int i, k, j, l, thirdN = third.columnsCount() / 2;
    for (i = 0; i < thirdN; i++)
    {
		result[i] = 0;
        for (k = third.colPointers()[i]; k < third.colPointers()[i + 1]; k++)
        {
            for (l = second.colPointers()[third.rowIndices()[k]]; l < second.colPointers()[third.rowIndices()[k] + 1]; l++)
            {
				j = matrix->colptr[second.rowIndices()[l]];
				while (matrix->rowind[j] < i && j < matrix->colptr[second.rowIndices()[l] + 1])
				{
					j++;
				}
				if (matrix->rowind[j] == i && j < matrix->colptr[second.rowIndices()[l] + 1])
				{
					result[i] += third.values()[k] * second.values()[l] * matrix->taucs_values[j];
				}
            }
		}
	}
    for ( ; i < third.columnsCount(); i++)
    {
		result[i] = 0;
        for (k = third.colPointers()[i]; k < third.colPointers()[i + 1]; k++)
        {
            for (l = second.colPointers()[third.rowIndices()[k]]; l < second.colPointers()[third.rowIndices()[k] + 1]; l++)
            {
				j = matrix->colptr[second.rowIndices()[l] + 1] - 1;
				while (matrix->rowind[j] > i && j >= matrix->colptr[second.rowIndices()[l]])
				{
					j--;
				}
				if (matrix->rowind[j] == i && j >= matrix->colptr[second.rowIndices()[l]])
				{
					result[i] += third.values()[k] * second.values()[l] * matrix->taucs_values[j];
				}
            }
		}
	}
	return result;
}

TSparseMatrix* TSparseMatrix::multiply_three_returning_lower_triangular(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	int *colptr = new int[second.columnsCount() + 1];
	double *resultColumn = new double[matrix->m];
	List<double> results;
	List<int> rowInds;
    int i, k, l, j;
    taucs_ccs_matrix *result;
    colptr[0] = 0;
    for (i = 0; i < matrix->m; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < third.columnsCount(); i++)
    {
        for (k = third.colPointers()[i]; k < third.colPointers()[i + 1]; k++)
        {
            for (l = second.colPointers()[third.rowIndices()[k]]; l < second.colPointers()[third.rowIndices()[k] + 1]; l++)
            {
				for (j = matrix->colptr[second.rowIndices()[l] + 1] - 1; j >= matrix->colptr[second.rowIndices()[l]] && matrix->rowind[j] >= i; j--)
				{
					resultColumn[matrix->rowind[j]] += third.values()[k] * second.values()[l] * matrix->taucs_values[j];
				}
            }
        }
        for (k = 0; k < matrix->m; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
				resultColumn[k] = 0;
            }
        }
		colptr[i + 1] = results.size();
    }
    result = taucs_ccs_create(matrix->m, third.columnsCount(), results.size(), TAUCS_DOUBLE | TAUCS_SYMMETRIC | TAUCS_LOWER);
	for (i = 0; i <= third.columnsCount(); i++)
	{
		result->colptr[i] = colptr[i];
	}
	results.initIterator();
	rowInds.initIterator();
	for (i = 0; results.hasMore(); i++)
	{
        result->taucs_values[i] = results.nextElement();
        result->rowind[i] = rowInds.nextElement();
	}

	delete[] colptr;
	delete[] resultColumn;

    return new TSparseMatrix(result);
}

TSparseMatrix* TSparseMatrix::multiply_returning_lower_triangular(const TSparseMatrix& second) const
{
	int secondCols = second.columnsCount();
	int *colptr = new int[secondCols + 1];
	double *resultColumn = new double[matrix->m];
	List<double> results;
	List<int> rowInds;
    int i, k, l;
    taucs_ccs_matrix *result;
    colptr[0] = 0;
    for (i = 0; i < matrix->m; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < secondCols; i++)
    {
        for (k = second.colPointers()[i]; k < second.colPointers()[i + 1]; k++)
        {
            for (l = matrix->colptr[second.rowIndices()[k] + 1] - 1; l >= matrix->colptr[second.rowIndices()[k]] && matrix->rowind[l] >= i; l--)
            {
				resultColumn[matrix->rowind[l]] += second.values()[k] * matrix->taucs_values[l];
            }
        }
        for (k = 0; k < matrix->m; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
				resultColumn[k] = 0;
            }
        }
        colptr[i + 1] = results.size();
    }
    result = taucs_ccs_create(matrix->m, secondCols, results.size(), TAUCS_DOUBLE | TAUCS_SYMMETRIC | TAUCS_LOWER);
    for (i = 0; i <= secondCols; i++)
    {
        result->colptr[i] = colptr[i];
    }
	results.initIterator();
	rowInds.initIterator();
	for (i = 0; results.hasMore(); i++)
	{
        result->taucs_values[i] = results.nextElement();
        result->rowind[i] = rowInds.nextElement();
	}

	delete[] colptr;
	delete[] resultColumn;

    return new TSparseMatrix(result);
}

void TSparseMatrix::multiply_by_number(double n)
{
	for (int i = 0; i < matrix->colptr[matrix->n]; i++)
	{
		matrix->taucs_values[i] *= n;
	}
}

void TSparseMatrix::writeMatrixFile(char *filename) const
{
	FILE *f = fopen(filename, "wt");
	for (int i = 0; i < matrix->n; i++)
	{
		for (int j = matrix->colptr[i]; j < matrix->colptr[i + 1]; j++)
		{
			fprintf(f, "%d %d %.20e\n", matrix->rowind[j] + 1, i + 1, matrix->taucs_values[j]);
		}
	}
	fclose(f);
}

inline int tuple_cmp(const void *a, const void *b)
{
	Tuple<int, double, int> *ai = (Tuple<int, double, int> *) a;
	Tuple<int, double, int> *bi = (Tuple<int, double, int> *) b;

	if (ai->a > bi->a)
	{
		return 1;
	}
	else if(ai->a < bi->a)
	{
		return -1;
	}
	else if(ai->c > bi->c)
	{
		return 1;
	}
	else if(ai->c < bi->c)
	{
		return -1;
	}
	return 0;
}

inline int binary_search(int arr[], int size, int value)
{
	int low = 0, high = size - 1, midpoint = (low + high) / 2;
	while (low <= high)
	{
		if (value == arr[midpoint])
		{
			if (midpoint != high && arr[midpoint] != arr[midpoint + 1])
			{
				return midpoint;
			}
			else
			{
				low = midpoint + 1;
			}
		}
		else if (value < arr[midpoint])
		{
			high = midpoint - 1;
		}
		else
		{
			low = midpoint + 1;
		}
		midpoint = (low + high) / 2;
	}
	return low - 1;
}
