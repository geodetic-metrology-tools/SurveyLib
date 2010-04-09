#include "TSparseMatrix.h"

TSparseMatrix::TSparseMatrix(int rows, int columns, real* vals, int* rowInds, int* colPtr)
{
	this->rows = rows;
	cols = columns;

	this->vals = vals;
	colptr = colPtr;
	rowind = rowInds;
}

TSparseMatrix::~TSparseMatrix()
{
    if (colptr != NULL)
    {
		if (colptr == rowind)
		{
			rowind = NULL;
		}
        delete[] colptr;
    }

    if (vals != NULL)
    {
        delete[] vals;
    }

    if (rowind != NULL)
    {
        delete[] rowind;
    }
}

TSparseMatrix* TSparseMatrix::transposed() const
{
	int* temp = new int[rows];
	int i, j, q;

	real* values = new real[colptr[cols]];
	int* newColptr = new int[rows + 1];
	int* newRowind = new int[colptr[cols]];
	for (i = 0; i < rows; i++)
	{
		temp[i] = 0;
	}

	for (i = 0; i < colptr[cols]; i++)
	{
		temp[rowind[i]]++;
	}

	int total = 0;
	for (i = 0; i < rows; i++)
	{
		newColptr[i] = total;
		total += temp[i];
		temp[i] = newColptr[i];
	}
	newColptr[rows] = total;

	for (i = 0; i < cols; i++)
    {
        for (j = colptr[i]; j < colptr[i + 1]; j++)
        {
			q = temp[rowind[j]]++;
            newRowind[q] = i;
            values[q] = vals[j];
        }
    }

	delete[] temp;

	return new TSparseMatrix(cols, rows, values, newRowind, newColptr);
}

TSparseMatrix* TSparseMatrix::symmetric_lower_inverse() const
{
	TSparseMatrix* decomposed = this->cholesky_decompose_lower_triangular_returning_lower_triangular();
    if (decomposed != NULL)
    {
        TSparseMatrix* inverse = decomposed->invert_lower_triangular_cholesky_decomposed_returning_lower_triangular();
        delete decomposed;
        TSparseMatrix* inverseTrans = inverse->transposed();
        TSparseMatrix* result = inverseTrans->multiply_F(*inverse);
        delete inverse;
        delete inverseTrans;
        return result;
    }
    else
    {
        return NULL;
    }
}

TSparseMatrix* TSparseMatrix::multiply_F(const TSparseMatrix& second) const
{
    real *resultColumn = new real[rows];
    Vector<real> results(rows * second.cols / 2);
    Vector<int> rowInds(rows * second.cols / 2);
    int i, k, l;
    TSparseMatrix *result = new TSparseMatrix(rows, second.cols);
    result->colptr[0] = 0;
    for (i = 0; i < rows; i++)
    {
        resultColumn[i] = 0;
    }
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k]]; l < colptr[second.rowind[k] + 1]; l++)
            {
                resultColumn[rowind[l]] += second.vals[k] * vals[l];
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
                resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = results.size();
    }
    result->setNNZ(results.size());
    for (i = 0; i < results.size(); i++)
    {
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
    }

    delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_LM(const TSparseMatrix& second) const
{
	real *resultColumn = new real[rows];
    int i, k, l;
    TSparseMatrix *result;
    int nnz = 0;
    for (i = 0; i < rows; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k]]; l < colptr[second.rowind[k] + 1]; l++)
            {
				resultColumn[rowind[l]] += second.vals[k] * vals[l];
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                nnz++;
                resultColumn[k] = 0;
            }
        }
    }
    result = new TSparseMatrix(rows, second.cols, nnz);
    int count = 0;
    result->colptr[0] = 0;
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k]]; l < colptr[second.rowind[k] + 1]; l++)
            {
				resultColumn[rowind[l]] += second.vals[k] * vals[l];
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                result->vals[count] = resultColumn[k];
                result->rowind[count++] = k;
				resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = count;
    }

	delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_returning_unordered_F(const TSparseMatrix& second) const
{
	int* cache = new int[rows];
    Vector<real> results(rows * second.cols / 2);
    Vector<int> rowInds(rows * second.cols / 2);
    int i, k, l;
    TSparseMatrix *result = new TSparseMatrix(rows, second.cols);
    result->colptr[0] = 0;
	for (i = 0; i < rows; i++)
	{
		cache[i] = 0;
	}
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k]]; l < colptr[second.rowind[k] + 1]; l++)
            {
				if (cache[rowind[l]] == 0)
				{
					cache[rowind[l]] = results.size() + 1;
            		results.add(second.vals[k] * vals[l]);
            		rowInds.add(rowind[l]);
				}
				else
				{
					results[cache[rowind[l]] - 1] += second.vals[k] * vals[l];
				}
            }
        }
        result->colptr[i + 1] = results.size();
        for (k = result->colptr[i]; k < result->colptr[i + 1]; k++)
        {
			cache[rowInds[k]] = 0;
        }
    }
    result->setNNZ(results.size());
    for (i = 0; i < results.size(); i++)
    {
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
    }

    delete[] cache;

    return result;
}

real TSparseMatrix::operator ()(int row, int column) const
{
	if (column <= cols / 2)
	{
		int i = colptr[column];
		while (rowind[i] < row && i < colptr[column + 1])
		{
			i++;
		}
		if (rowind[i] == row && i < colptr[column + 1])
		{
			return vals[i];
		}
	}
	else
	{
		int i = colptr[column + 1] - 1;
		while (rowind[i] > row && i >= colptr[column])
		{
			i--;
		}
		if (rowind[i] == row && i >= colptr[column])
		{
			return vals[i];
		}
	}
	return 0;
}

real* TSparseMatrix::operator *(const real* right) const
{
	int i, j;

	real* result = new real[rows];

	for (i = 0; i < rows; i++)
	{
		result[i] = 0;
	}

    for (i = 0; i < cols; i++)
	{
		if (right[i] != 0)
		{
			for (j = colptr[i]; j < colptr[i + 1]; j++)
			{
				result[rowind[j]] += right[i] * vals[j];
			}
		}
	}

	return result;
}

real* TSparseMatrix::operator *(const TColumnVector& right) const
{
	int i, j;

	real* result = new real[rows];

	for (i = 0; i < rows; i++)
	{
		result[i] = 0;
	}

    for (i = 0; i < cols; i++)
	{
		if (right(i) != 0)
		{
			for (j = colptr[i]; j < colptr[i + 1]; j++)
			{
				result[rowind[j]] += right(i) * vals[j];
			}
		}
	}

	return result;
}

bool TSparseMatrix::operator ==(const TSparseMatrix& second) const
{
	if (cols != second.cols || rows != second.rows ||
		colptr[cols] != second.colptr[second.cols])
	{
		return false;
	}
	for (int i = 0; i < cols; i++)
	{
		if (colptr[i] != second.colptr[i])
		{
			return false;
		}
	}

	for (int i = 0; i < colptr[cols]; i++)
	{
		real temp = vals[i] / second.vals[i];
		if (rowind[i] != second.rowind[i] ||
			temp < 1 - THRESHOLD || temp > 1 + THRESHOLD)
		{
			return false;
		}
	}

	return true;
}

bool TSparseMatrix::operator !=(const TSparseMatrix& second) const
{
	return !(*this == second);
}

TSparseMatrix* TSparseMatrix::deep_copy(const TSparseMatrix* matrix)
{
	TSparseMatrix* m = new TSparseMatrix(matrix->rows, matrix->cols, matrix->colptr[matrix->cols]);

	for (int i = 0; i <= matrix->cols; i++)
	{
		m->colptr[i] = matrix->colptr[i];
	}
	for (int i = 0; i < matrix->colptr[matrix->cols]; i++)
	{
		m->vals[i] = matrix->vals[i];
		m->rowind[i] = matrix->rowind[i];
	}

	return m;
}

TSparseMatrix* TSparseMatrix::cholesky_decompose_lower_triangular_returning_lower_triangular() const
{
	real* resultColumn = new real[cols];
	Vector<real> results(cols * cols / 2);
	Vector<int> rowInds(cols * cols / 2);

	TSparseMatrix *result = new TSparseMatrix(cols, cols);

	result->colptr[0] = 0;
	int colDiv2 = cols / 2;

	for (int i = 0; i < cols; i++)
	{
		resultColumn[i] = 0;
	}

	for (int i = 0; i < cols; i++)
	{
		int column = 1;
		int col = result->colptr[column];

		int count = 0;
		int minim = i < colDiv2 ? i : colDiv2;
		while (column <= minim)
		{
			// finding the i -th row of the current column
			while (count < col - 1 && rowInds[count] < i)
			{
				count++;
			}

			// if this element in the column is not zero
			if (rowInds[count] == i)
			{
				real columnMainValue = results[count++];
				resultColumn[i] -= columnMainValue * columnMainValue;

				// we multiply each element of the rest of the column with the "main value" which is
				// on the i -th row and then subtract that from the current row's sum
				while (count < col)
				{
					resultColumn[rowInds[count]] -= results[count] * columnMainValue;
					count++;
				}
			}
			else
			{
				count = col;
			}
			col = result->colptr[++column];
		}

		while (column <= i) // going through all the computed columns
		{
			// finding the i -th row of the current column
			count = col - 1;
			while (count > result->colptr[column - 1] && rowInds[count] > i)
			{
				count--;
			}

			// if this element in the column is not zero
			if (rowInds[count] == i)
			{
				real columnMainValue = results[count++];
				resultColumn[i] -= columnMainValue * columnMainValue;

				// we multiply each element of the rest of the column with the "main value" which is
				// on the i -th row and then subtract that from the current row's sum
				while (count < col)
				{
					resultColumn[rowInds[count]] -= results[count] * columnMainValue;
					count++;
				}
			}
			col = result->colptr[++column];
		}

		col = colptr[i];

		resultColumn[i] += vals[col];
		if (resultColumn[i] <= 0)
		{
			delete[] resultColumn;
			delete result;
			return NULL;
		}
		resultColumn[i] = sqrtq(resultColumn[i]);
		rowInds.add(i);
		results.add(resultColumn[i]);
		col++;

		for (int j = i + 1; j < cols; j++)
		{
			real val = resultColumn[j];
			if (j == rowind[col] && col < colptr[i + 1])
			{
				val += vals[col++];
			}
			if (val < -THRESHOLD || val > THRESHOLD)
			{
				rowInds.add(j);
				results.add(val / resultColumn[i]);
			}
			resultColumn[j] = 0;
		}
		resultColumn[i] = 0;

        result->colptr[i + 1] = results.size();
	}

	delete[] resultColumn;

	result->setNNZ(results.size());

	for (int i = 0; i < results.size(); i++)
	{
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
	}

	return result;
}

TSparseMatrix* TSparseMatrix::ldlt_decompose_lower_triangular_returning_lower_triangular() const
{
	real* resultColumn = new real[cols];
	Vector<real> results(cols * cols / 4);
	Vector<int> rowInds(cols * cols / 4);

	int* colWhereTo = new int[cols];

	TSparseMatrix *result = new TSparseMatrix(cols, cols);
	result->colptr[0] = 0;

	for (int i = 0; i < cols; i++)
	{
		resultColumn[i] = 0;
	}

	for (int i = 0; i < cols; i++)
	{
		colWhereTo[i] = results.size() + 1;

		// computing the diagonal element
		real diag = vals[colptr[i]];
		for (int j = 0; j < i; j++)
		{
			if (colWhereTo[j] != -1 && rowInds[colWhereTo[j]] == i)
			{
				diag -= results[result->colptr[j]] * results[colWhereTo[j]] * results[colWhereTo[j]];
			}
		}
		if (diag == 0)
		{
			delete[] resultColumn;
			delete[] colWhereTo;
			delete result;
			return NULL;
		}
		rowInds.add(i);
		results.add(diag);

		// computing the rest of the column...

		// for each of the computed columns up to this one
		for (int j = 0; j < i; j++)
		{
			if (colWhereTo[j] != -1 && rowInds[colWhereTo[j]] == i)
			{
				real multiplier = results[result->colptr[j]] * results[colWhereTo[j]];
				for (int k = colWhereTo[j]; k < result->colptr[j + 1]; k++)
				{
					resultColumn[rowInds[k]] += multiplier * results[k];
				}

				if (++colWhereTo[j] >= result->colptr[j + 1])
				{
					colWhereTo[j] = -1;
				}
			}
		}

		diag = 1 / diag;
		// fill the elements
		for (int j = i + 1, k = colptr[i] + 1; j < cols; j++)
		{
			real element = diag * ((rowind[k] == j ? vals[k++] : 0) - resultColumn[j]);
			if (element != 0)
			{
				rowInds.add(j);
				results.add(element);
			}
			resultColumn[j] = 0;
		}

		result->colptr[i + 1] = results.size();
	}

	delete[] colWhereTo;

	result->setNNZ(results.size());

	for (int i = 0; i < results.size(); i++)
	{
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
	}

	delete[] resultColumn;

	return result;
}

real* TSparseMatrix::solve_eqn(const real* b) const
{
	real* result = new real[rows];

	TSparseMatrix* LT = this->transposed();

	int col;
	real sum;
	for (int i = 0; i < cols; i++)
	{
		sum = b[i];
		for (col = LT->colptr[i]; col < LT->colptr[i + 1] && LT->rowind[col] < i; col++)
		{
			sum -= LT->vals[col] * result[LT->rowind[col]];
		}
		result[i] = sum / LT->vals[col];
	}
	for (int i = cols - 1; i >= 0; i--)
	{
		sum = result[i];
		for (col = colptr[i + 1] - 1; col >= colptr[i] && rowind[col] > i; col--)
		{
			sum -= vals[col] * result[rowind[col]];
		}
		result[i] = sum / vals[col];
	}

	return result;
}

TSparseMatrix* TSparseMatrix::invert_diagonal_matrix() const
{
	TSparseMatrix* inverse = new TSparseMatrix(rows, cols, colptr[cols]);
	for (int i = 0; i < colptr[cols]; i++)
	{
		inverse->vals[i] = 1 / vals[i];
		inverse->rowind[i] = rowind[i];
	}
	for (int i = 0; i <= cols; i++)
	{
		inverse->colptr[i] = colptr[i];
	}
	return inverse;
}

TSparseMatrix* TSparseMatrix::invert_lower_triangular_cholesky_decomposed() const
{
	TSparseMatrix* transposed = this->transposed();

	Vector<real> results(colptr[cols] * 4);
	Vector<int> rowInds(colptr[cols] * 4);

	int i, j, k, l;
	real sum = 0;

	TSparseMatrix *result = new TSparseMatrix(cols, cols);
	result->colptr[0] = 0;

    for (i = 0; i < cols; i++)
    {
        for (j = 0; j < i; j++)
        {
			k = result->colptr[j];
			while (rowInds[k] < j && k < result->colptr[j + 1])
			{
				k++;
			}
            for (l = transposed->colptr[i];
                rowInds[k] < i &&
				k < result->colptr[j + 1] &&
                l < transposed->colptr[i + 1] &&
                transposed->rowind[l] < i; )
            {
                if (transposed->rowind[l] < rowInds[k])
                {
                    l++;
                }
                else if (rowInds[k] == transposed->rowind[l])
                {
                    sum -= results[k] * transposed->vals[l];
                    k++;
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
                results.add(sum / vals[colptr[i]]);
                sum = 0;
            }
        }

        results.add(1 / vals[colptr[i]]);
        rowInds.add(i);

        for (j = i + 1; j < cols; j++)
        {
			int size = results.size();
			k = result->colptr[i];
			while (rowInds[k] < i && k < size)
			{
				k++;
			}
            for (l = transposed->colptr[j];
                k < size &&
                rowInds[k] < j &&
                l < transposed->colptr[j + 1] &&
                transposed->rowind[l] < j; )
            {
                if (transposed->rowind[l] < rowInds[k])
                {
                    l++;
                }
                else if (rowInds[k] == transposed->rowind[l])
                {
                    sum -= results[k] * transposed->vals[l];
                    k++;
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
                results.add(sum / vals[colptr[j]]);
                sum = 0;
            }
        }
        result->colptr[i + 1] = results.size();
	}

	result->setNNZ(results.size());

	delete transposed;

	for (i = 0; i < results.size(); i++)
	{
		result->rowind[i] = rowInds[i];
		result->vals[i] = results[i];
	}

	return result;
}

TSparseMatrix* TSparseMatrix::invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() const
{
	TSparseMatrix* transposed = this->transposed();

	Vector<real> results(colptr[cols] * 4);
	Vector<int> rowInds(colptr[cols] * 4);

	int i, j, k, l;
	real sum = 0;

	TSparseMatrix *result = new TSparseMatrix(cols, cols);
	result->colptr[0] = 0;

    for (i = 0; i < cols; i++)
    {
        results.add(1 / vals[colptr[i]]);
        rowInds.add(i);

        for (j = i + 1; j < cols; j++)
        {
			int size = results.size();
            for (k = result->colptr[i], l = transposed->colptr[j];
                k < size &&
                rowInds[k] < j &&
                l < transposed->colptr[j + 1] &&
                transposed->rowind[l] < j; )
            {
                if (transposed->rowind[l] < rowInds[k])
                {
                    l++;
                }
                else if (rowInds[k] == transposed->rowind[l])
                {
                    sum -= results[k] * transposed->vals[l];
                    k++;
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
                results.add(sum / vals[colptr[j]]);
                sum = 0;
            }
        }
        result->colptr[i + 1] = results.size();
	}

	result->setNNZ(results.size());

	delete transposed;

	for (i = 0; i < results.size(); i++)
	{
		result->rowind[i] = rowInds[i];
		result->vals[i] = results[i];
	}

	return result;
}

real* TSparseMatrix::multiply_returning_diagonal(const TSparseMatrix& second) const
{
	real* result = new real[second.cols];
    int i, k, l, secondN = second.cols / 2;
    for (i = 0; i < secondN; i++)
    {
		result[i] = 0;
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
			l = colptr[second.rowind[k]];
			while (rowind[l] < i && l < colptr[second.rowind[k] + 1])
			{
				l++;
			}
			if (rowind[l] == i && l < colptr[second.rowind[k] + 1])
			{
				result[i] += vals[l] * second.vals[k];
			}
        }
    }
    for ( ; i < second.cols; i++)
    {
		result[i] = 0;
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
			l = colptr[second.rowind[k] + 1] - 1;
			while (rowind[l] > i && l >= colptr[second.rowind[k]])
			{
				l--;
			}
			if (rowind[l] == i && l >= colptr[second.rowind[k]])
			{
				result[i] += vals[l] * second.vals[k];
			}
		}
    }

	return result;
}

real* TSparseMatrix::multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	real* result = new real[third.cols];
	int i, k, j, l, thirdN = third.cols / 2;
    for (i = 0; i < thirdN; i++)
    {
		result[i] = 0;
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				j = colptr[second.rowind[l]];
				while (rowind[j] < i && j < colptr[second.rowind[l] + 1])
				{
					j++;
				}
				if (rowind[j] == i && j < colptr[second.rowind[l] + 1])
				{
					result[i] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
		}
	}
    for ( ; i < third.cols; i++)
    {
		result[i] = 0;
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				j = colptr[second.rowind[l] + 1] - 1;
				while (rowind[j] > i && j >= colptr[second.rowind[l]])
				{
					j--;
				}
				if (rowind[j] == i && j >= colptr[second.rowind[l]])
				{
					result[i] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
		}
	}
	return result;
}

TSparseMatrix* TSparseMatrix::multiply_three_F(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	real *resultColumn = new real[rows];
	Vector<real> results(rows * third.cols / 2);
	Vector<int> rowInds(rows * third.cols / 2);
    int i, k, l, j;
    TSparseMatrix *result = new TSparseMatrix(rows, third.cols);
    result->colptr[0] = 0;
    for (i = 0; i < rows; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < third.cols; i++)
    {
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				for (j = colptr[second.rowind[l]]; j < colptr[second.rowind[l] + 1]; j++)
				{
					resultColumn[rowind[j]] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
				resultColumn[k] = 0;
            }
        }
		result->colptr[i + 1] = results.size();
    }

    result->setNNZ(results.size());
	for (i = 0; i < results.size(); i++)
	{
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
	}

	delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_three_LM(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	real *resultColumn = new real[rows];
    int i, k, l, j;
    TSparseMatrix *result;
    int nnz = 0;
    for (i = 0; i < rows; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < third.cols; i++)
    {
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				for (j = colptr[second.rowind[l]]; j < colptr[second.rowind[l] + 1]; j++)
				{
					resultColumn[rowind[j]] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                nnz++;
				resultColumn[k] = 0;
            }
        }
    }
    result = new TSparseMatrix(rows, third.cols, nnz);
    result->colptr[0] = 0;
    int count = 0;
    for (i = 0; i < third.cols; i++)
    {
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				for (j = colptr[second.rowind[l]]; j < colptr[second.rowind[l] + 1]; j++)
				{
					resultColumn[rowind[j]] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                result->vals[count] = resultColumn[k];
                result->rowind[count++] = k;
				resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = count;
    }

	delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const
{
    real *resultColumn = new real[rows];
    Vector<real> results((rows * third.cols) / 2 + rows);
    Vector<int> rowInds((rows * third.cols) / 2 + rows);
    int i, k, l, j;
    TSparseMatrix *result = new TSparseMatrix(rows, third.cols);
    result->colptr[0] = 0;
    for (i = 0; i < rows; i++)
    {
        resultColumn[i] = 0;
    }
    for (i = 0; i < third.cols; i++)
    {
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
                for (j = colptr[second.rowind[l] + 1] - 1; j >= colptr[second.rowind[l]] && rowind[j] >= i; j--)
                {
                    resultColumn[rowind[j]] += third.vals[k] * second.vals[l] * vals[j];
                }
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
                resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = results.size();
    }

    result->setNNZ(results.size());
    for (i = 0; results.size(); i++)
    {
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
    }

    delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	real *resultColumn = new real[rows];
    int i, k, l, j;
    TSparseMatrix *result;
    int nnz = 0;
    for (i = 0; i < rows; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < third.cols; i++)
    {
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				for (j = colptr[second.rowind[l] + 1] - 1; j >= colptr[second.rowind[l]] && rowind[j] >= i; j--)
				{
					resultColumn[rowind[j]] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                nnz++;
				resultColumn[k] = 0;
            }
        }
    }
    result = new TSparseMatrix(rows, third.cols, nnz);
    result->colptr[0] = 0;
    int count = 0;
    for (i = 0; i < third.cols; i++)
    {
        for (k = third.colptr[i]; k < third.colptr[i + 1]; k++)
        {
            for (l = second.colptr[third.rowind[k]]; l < second.colptr[third.rowind[k] + 1]; l++)
            {
				for (j = colptr[second.rowind[l] + 1] - 1; j >= colptr[second.rowind[l]] && rowind[j] >= i; j--)
				{
					resultColumn[rowind[j]] += third.vals[k] * second.vals[l] * vals[j];
				}
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                result->vals[count] = resultColumn[k];
                result->rowind[count++] = k;
				resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = count;
    }

	delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_returning_lower_triangular_F(const TSparseMatrix& second) const
{
    real *resultColumn = new real[rows];
    Vector<real> results((rows * second.cols) / 2 + rows);
    Vector<int> rowInds((rows * second.cols) / 2 + rows);
    int i, k, l;
    TSparseMatrix *result = new TSparseMatrix(rows, second.cols);
    result->colptr[0] = 0;
    for (i = 0; i < rows; i++)
    {
        resultColumn[i] = 0;
    }
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k] + 1] - 1; l >= colptr[second.rowind[k]] && rowind[l] >= i; l--)
            {
                resultColumn[rowind[l]] += second.vals[k] * vals[l];
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                results.add(resultColumn[k]);
                rowInds.add(k);
                resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = results.size();
    }

    result->setNNZ(results.size());
    for (i = 0; i < results.size(); i++)
    {
        result->vals[i] = results[i];
        result->rowind[i] = rowInds[i];
    }

    delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const
{
	real *resultColumn = new real[rows];
    int i, k, l;
    TSparseMatrix *result;
    int nnz = 0;
    for (i = 0; i < rows; i++)
    {
		resultColumn[i] = 0;
    }
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k] + 1] - 1; l >= colptr[second.rowind[k]] && rowind[l] >= i; l--)
            {
                resultColumn[rowind[l]] += second.vals[k] * vals[l];
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                nnz++;
                resultColumn[k] = 0;
            }
        }
    }
    result = new TSparseMatrix(rows, second.cols, nnz);
    result->colptr[0] = 0;
    int count = 0;
    for (i = 0; i < second.cols; i++)
    {
        for (k = second.colptr[i]; k < second.colptr[i + 1]; k++)
        {
            for (l = colptr[second.rowind[k] + 1] - 1; l >= colptr[second.rowind[k]] && rowind[l] >= i; l--)
            {
                resultColumn[rowind[l]] += second.vals[k] * vals[l];
            }
        }
        for (k = 0; k < rows; k++)
        {
            if (resultColumn[k] != 0)
            {
                result->vals[count] = resultColumn[k];
                result->rowind[count++] = k;
				resultColumn[k] = 0;
            }
        }
        result->colptr[i + 1] = count;
    }

	delete[] resultColumn;

    return result;
}

TSparseMatrix* TSparseMatrix::add(const TSparseMatrix& second) const
{
    int first = 0, col = 1, sec = 0;
    int total = 0;

    while (col <= cols)
    {
        while (first < colptr[col] && sec < second.colptr[col])
        {
            if (rowind[first] == second.rowind[sec] && vals[first++] + second.vals[sec++] != 0)
            {
	            total++;
            }
            else if (rowind[first] < second.rowind[sec])
            {
				first++;
				total++;
            }
            else
            {
				sec++;
				total++;
            }
        }
        total += colptr[col] - first + second.colptr[col] - sec;
        first = colptr[col];
        sec = second.colptr[col++];
    }

    TSparseMatrix* result = new TSparseMatrix(rows, cols, total);
    first = 0;
    col = 1;
    sec = 0;
    total = 0;

	int colp = 1;

	result->colptr[0] = 0;
    while (col <= cols)
    {
        while (first < colptr[col] && sec < second.colptr[col])
        {
			real res;
            if (rowind[first] == second.rowind[sec])
            {
				res = vals[first] + second.vals[sec++];
				if (res != 0)
				{
	                result->rowind[total] = rowind[first];
	                result->vals[total++] = res;
				}
				first++;
            }
            else if (rowind[first] < second.rowind[sec])
            {
                result->rowind[total] = rowind[first];
                result->vals[total++] = vals[first++];
            }
            else
            {
                result->rowind[total] = second.rowind[sec];
                result->vals[total++] = second.vals[sec++];
            }
        }
		while (first < colptr[col])
		{
            result->rowind[total] = rowind[first];
            result->vals[total++] = vals[first++];
		}
		while (sec < second.colptr[col])
		{
            result->rowind[total] = second.rowind[sec];
            result->vals[total++] = second.vals[sec++];
		}
		col++;
		result->colptr[colp++] = total;
    }

    return result;
}

void TSparseMatrix::multiply_by_number(real n)
{
	for (int i = 0; i < colptr[cols]; i++)
	{
		vals[i] *= n;
	}
}

void TSparseMatrix::write_matrix_file(const char *filename) const
{
	FILE *f = fopen(filename, "wt");
	fprintf(f, "%d %d %d\n", rows, cols, colptr[cols]);
	for (int i = 0; i < cols; i++)
	{
		for (int j = colptr[i]; j < colptr[i + 1]; j++)
		{
			fprintf(f, "%d %d %.20e\n", rowind[j] + 1, i + 1, (double) vals[j]);
		}
	}
	fclose(f);
}

TSparseMatrix* TSparseMatrix::read_matrix_file(const char* filename)
{
	FILE *f = fopen(filename, "rt");

	int row = 0, column = 0, nnz = 0;
	fscanf(f, "%d %d %d\n", &row, &column, &nnz);
	TSparseMatrix* matrix = new TSparseMatrix(row, column, nnz);

	int count = 0;
	int colptr = 1;
	matrix->colptr[0] = 0;
	int oldcol = 1;
	while (!feof(f))
	{
		double temp;
		fscanf(f, "%d %d %lf\n", &row, &column, &temp);

		while (oldcol != column)
		{
			matrix->colptr[colptr++] = count;
			oldcol++;
		}

		matrix->rowind[count] = row - 1;
		matrix->vals[count++] = temp;
	}
	matrix->colptr[colptr] = count;
	fclose(f);

	return matrix;
}
