#include "TSparseMatrix.h"

TSparseMatrix::TSparseMatrix(int rows, int columns, quad* vals, int* rowInds, int* colPtr)
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

	quad* values = new quad[colptr[cols]];
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
    quad *resultColumn = new quad[rows];
    Vector<quad> results(rows * second.cols / 2);
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
	quad *resultColumn = new quad[rows];
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
    Vector<quad> results(rows * second.cols / 2);
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

quad TSparseMatrix::operator ()(int row, int column) const
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

quad* TSparseMatrix::operator *(const quad* right) const
{
	int i, j;

	quad* result = new quad[rows];

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

quad* TSparseMatrix::operator *(const TColumnVector& right) const
{
	int i, j;

	quad* result = new quad[rows];

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
		quad temp = vals[i] / second.vals[i];
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
	quad* resultColumn = new quad[cols];
	Vector<quad> results(cols * cols / 2);
	Vector<int> rowInds(cols * cols / 2);

	TSparseMatrix *result = new TSparseMatrix(cols, cols);

	result->colptr[0] = 0;

	for (int i = 0; i < cols; i++)
	{
		resultColumn[i] = 0;
	}

	for (int i = 0; i < cols; i++)
	{
		int column = 1;
		int col = result->colptr[column];

		int count = 0;
		while (column <= i) // going through all the computed columns
		{
			// finding the i -th row of the current column
			while (count < col && rowInds[count] < i)
			{
				count++;
			}

			// if this element in the column is not zero
			if (count < col && rowInds[count] == i)
			{
				quad columnMainValue = results[count++];
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

		col = colptr[i];

		resultColumn[i] += vals[col];
		if (resultColumn[i] < 0)
		{
			delete[] resultColumn;
			delete result;
			return NULL;
		}
		resultColumn[i] = __sqrtq(resultColumn[i]);
		rowInds.add(i);
		results.add(resultColumn[i]);
		col++;

		for (int j = i + 1; j < cols; j++)
		{
			quad val = resultColumn[j];
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

quad* TSparseMatrix::solve_eqn(const quad* b) const
{
	quad* result = new quad[rows];

	TSparseMatrix* LT = this->transposed();

	int col;
	quad sum;
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

	Vector<quad> results(colptr[cols] * 4);
	Vector<int> rowInds(colptr[cols] * 4);

	int i, j, k, l;
	quad sum = 0;

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

	Vector<quad> results(colptr[cols] * 4);
	Vector<int> rowInds(colptr[cols] * 4);

	int i, j, k, l;
	quad sum = 0;

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

quad* TSparseMatrix::multiply_returning_diagonal(const TSparseMatrix& second) const
{
	quad* result = new quad[second.cols];
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

quad* TSparseMatrix::multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const
{
	quad* result = new quad[third.cols];
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
	quad *resultColumn = new quad[rows];
	Vector<quad> results(rows * third.cols / 2);
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
	quad *resultColumn = new quad[rows];
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
    quad *resultColumn = new quad[rows];
    Vector<quad> results((rows * third.cols) / 2 + rows);
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
	quad *resultColumn = new quad[rows];
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
    quad *resultColumn = new quad[rows];
    Vector<quad> results((rows * second.cols) / 2 + rows);
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
	quad *resultColumn = new quad[rows];
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
			quad res;
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

void TSparseMatrix::multiply_by_number(quad n)
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


//#include "TSparseMatrix.h"
//
//template <typename T, typename U, typename V>
//class Tuple
//{
//public:
//	T a;
//	U b;
//	V c;
//};
//
//inline int tuple_cmp(const void *a, const void *b)
//{
//	Tuple<int, quad, int> *ai = (Tuple<int, quad, int> *) a;
//	Tuple<int, quad, int> *bi = (Tuple<int, quad, int> *) b;
//
//	if (ai->a > bi->a)
//	{
//		return 1;
//	}
//	else if(ai->a < bi->a)
//	{
//		return -1;
//	}
//	else if(ai->c > bi->c)
//	{
//		return 1;
//	}
//	else if(ai->c < bi->c)
//	{
//		return -1;
//	}
//	return 0;
//}
//
//inline int binary_search(int arr[], int size, int value)
//{
//	int low = 0, high = size - 1, midpoint = (low + high) / 2;
//	while (low <= high)
//	{
//		if (value == arr[midpoint])
//		{
//			if (midpoint != high && arr[midpoint] != arr[midpoint + 1])
//			{
//				return midpoint;
//			}
//			else
//			{
//				low = midpoint + 1;
//			}
//		}
//		else if (value < arr[midpoint])
//		{
//			high = midpoint - 1;
//		}
//		else
//		{
//			low = midpoint + 1;
//		}
//		midpoint = (low + high) / 2;
//	}
//	return low - 1;
//}
//
//TSparseMatrix::TSparseMatrix(int rows, int columns, quad* vals, int* rowInds, int* colPtr)
//{
//	matrix = new Matrix(rows, columns, vals, colPtr, rowInds);
//}
//
//TSparseMatrix::TSparseMatrix(const TSparseMatrix& other)
//{
//	matrix = other.matrix;
//}
//
//TSparseMatrix::~TSparseMatrix()
//{
//	delete matrix;
//}
//
//TSparseMatrix* TSparseMatrix::transposed() const
//{
//	int* temp = new int[matrix->m];
//	int i, j, q;
//
//	quad* values = new quad[matrix->colptr[matrix->n]];
//	int* colptr = new int[matrix->m + 1];
//	int* rowind = new int[matrix->colptr[matrix->n]];
//	for (i = 0; i < matrix->m; i++)
//	{
//		temp[i] = 0;
//	}
//
//	for (i = 0; i < matrix->colptr[matrix->n]; i++)
//	{
//		temp[matrix->rowind[i]]++;
//	}
//
//	int total = 0;
//	for (i = 0; i < matrix->m; i++)
//	{
//		colptr[i] = total;
//		total += temp[i];
//		temp[i] = colptr[i];
//	}
//	colptr[matrix->m] = total;
//
//	for (i = 0; i < matrix->n; i++)
//    {
//        for (j = matrix->colptr[i]; j < matrix->colptr[i + 1]; j++)
//        {
//			q = temp[matrix->rowind[j]]++;
//            rowind[q] = i;
//            values[q] = matrix->values[j];
//        }
//    }
//
//	delete[] temp;
//
//	return new TSparseMatrix(matrix->n, matrix->m, values, rowind, colptr);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_F(const TSparseMatrix& second) const
//{
//    quad *resultColumn = new quad[matrix->m];
//    Vector<quad> results(matrix->m * second.matrix->n / 2);
//    Vector<int> rowInds(matrix->m * second.matrix->n / 2);
//    int i, k, l;
//    Matrix *result = new Matrix(matrix->m, second.matrix->n);
//    result->colptr[0] = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//        resultColumn[i] = 0;
//    }
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k]]; l < matrix->colptr[second.matrix->rowind[k] + 1]; l++)
//            {
//                resultColumn[matrix->rowind[l]] += second.matrix->values[k] * matrix->values[l];
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                results.add(resultColumn[k]);
//                rowInds.add(k);
//                resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = results.size();
//    }
//    result->setNNZ(results.size());
//    for (i = 0; i < results.size(); i++)
//    {
//        result->values[i] = results[i];
//        result->rowind[i] = rowInds[i];
//    }
//
//    delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_LM(const TSparseMatrix& second) const
//{
//	quad *resultColumn = new quad[matrix->m];
//    int i, k, l;
//    Matrix *result;
//    int nnz = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//		resultColumn[i] = 0;
//    }
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k]]; l < matrix->colptr[second.matrix->rowind[k] + 1]; l++)
//            {
//				resultColumn[matrix->rowind[l]] += second.matrix->values[k] * matrix->values[l];
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                nnz++;
//                resultColumn[k] = 0;
//            }
//        }
//    }
//    result = new Matrix(matrix->m, second.matrix->n, nnz);
//    int count = 0;
//    result->colptr[0] = 0;
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k]]; l < matrix->colptr[second.matrix->rowind[k] + 1]; l++)
//            {
//				resultColumn[matrix->rowind[l]] += second.matrix->values[k] * matrix->values[l];
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                result->values[count] = resultColumn[k];
//                result->rowind[count++] = k;
//				resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = count;
//    }
//
//	delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_returning_unordered_F(const TSparseMatrix& second) const
//{
//	int* cache = new int[matrix->m];
//    Vector<quad> results(matrix->m * second.matrix->n / 2);
//    Vector<int> rowInds(matrix->m * second.matrix->n / 2);
//    int i, k, l;
//    Matrix *result = new Matrix(matrix->m, second.matrix->n);
//    result->colptr[0] = 0;
//	for (i = 0; i < matrix->m; i++)
//	{
//		cache[i] = 0;
//	}
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k]]; l < matrix->colptr[second.matrix->rowind[k] + 1]; l++)
//            {
//				if (cache[matrix->rowind[l]] == 0)
//				{
//					cache[matrix->rowind[l]] = results.size() + 1;
//            		results.add(second.matrix->values[k] * matrix->values[l]);
//            		rowInds.add(matrix->rowind[l]);
//				}
//				else
//				{
//					results[cache[matrix->rowind[l]] - 1] += second.matrix->values[k] * matrix->values[l];
//				}
//            }
//        }
//        result->colptr[i + 1] = results.size();
//        for (k = result->colptr[i]; k < result->colptr[i + 1]; k++)
//        {
//			cache[rowInds[k]] = 0;
//        }
//    }
//    result->setNNZ(results.size());
//    for (i = 0; i < results.size(); i++)
//    {
//        result->values[i] = results[i];
//        result->rowind[i] = rowInds[i];
//    }
//
//    delete[] cache;
//
//    return new TSparseMatrix(result);
//}
//
//quad TSparseMatrix::operator ()(int row, int column) const
//{
//	if (column <= matrix->n / 2)
//	{
//		int i = matrix->colptr[column];
//		while (matrix->rowind[i] < row && i < matrix->colptr[column + 1])
//		{
//			i++;
//		}
//		if (matrix->rowind[i] == row && i < matrix->colptr[column + 1])
//		{
//			return matrix->values[i];
//		}
//	}
//	else
//	{
//		int i = matrix->colptr[column + 1] - 1;
//		while (matrix->rowind[i] > row && i >= matrix->colptr[column])
//		{
//			i--;
//		}
//		if (matrix->rowind[i] == row && i >= matrix->colptr[column])
//		{
//			return matrix->values[i];
//		}
//	}
//	return 0;
//}
//
//quad* TSparseMatrix::operator *(const quad* right) const
//{
//	int i, j;
//
//	quad* result = new quad[matrix->m];
//
//	for (i = 0; i < matrix->m; i++)
//	{
//		result[i] = 0;
//	}
//
//    for (i = 0; i < matrix->n; i++)
//	{
//		if (right[i] != 0)
//		{
//			for (j = matrix->colptr[i]; j < matrix->colptr[i + 1]; j++)
//			{
//				result[matrix->rowind[j]] += right[i] * matrix->values[j];
//			}
//		}
//	}
//
//	return result;
//}
//
//quad* TSparseMatrix::operator *(const TColumnVector& right) const
//{
//	int i, j;
//
//	quad* result = new quad[matrix->m];
//
//	for (i = 0; i < matrix->m; i++)
//	{
//		result[i] = 0;
//	}
//
//    for (i = 0; i < matrix->n; i++)
//	{
//		if (right(i) != 0)
//		{
//			for (j = matrix->colptr[i]; j < matrix->colptr[i + 1]; j++)
//			{
//				result[matrix->rowind[j]] += right(i) * matrix->values[j];
//			}
//		}
//	}
//
//	return result;
//}
//
//bool TSparseMatrix::operator ==(const TSparseMatrix& second) const
//{
//	if (matrix->n != second.matrix->n || matrix->m != second.matrix->m ||
//		matrix->colptr[matrix->n] != second.matrix->colptr[second.matrix->n])
//	{
//		return false;
//	}
//	for (int i = 0; i < matrix->n; i++)
//	{
//		if (matrix->colptr[i] != second.matrix->colptr[i])
//		{
//			return false;
//		}
//	}
//
//	for (int i = 0; i < matrix->colptr[matrix->n]; i++)
//	{
//		if (matrix->rowind[i] != second.matrix->rowind[i] ||
//			matrix->values[i] < second.matrix->values[i] - THRESHOLD ||
//			matrix->values[i] > second.matrix->values[i] + THRESHOLD)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}
//
//bool TSparseMatrix::operator !=(const TSparseMatrix& second) const
//{
//	return !(*this == second);
//}
//
//TSparseMatrix* TSparseMatrix::deepCopy(const TSparseMatrix* matrix)
//{
//	Matrix* m = new Matrix(matrix->matrix->m, matrix->matrix->n, matrix->matrix->colptr[matrix->matrix->n]);
//
//	for (int i = 0; i <= matrix->matrix->n; i++)
//	{
//		m->colptr[i] = matrix->matrix->colptr[i];
//	}
//	for (int i = 0; i < matrix->matrix->colptr[matrix->matrix->n]; i++)
//	{
//		m->values[i] = matrix->matrix->values[i];
//		m->rowind[i] = matrix->matrix->rowind[i];
//	}
//
//	return new TSparseMatrix(m);
//}
//
//TSparseMatrix* TSparseMatrix::cholesky_decompose_lower_triangular_returning_lower_triangular() const
//{
//	quad* resultColumn = new quad[matrix->n];
//	Vector<quad> results(matrix->n * matrix->n / 2);
//	Vector<int> rowInds(matrix->n * matrix->n / 2);
//
//	Matrix *result = new Matrix(matrix->n, matrix->n);
//
//	result->colptr[0] = 0;
//
//	for (int i = 0; i < matrix->n; i++)
//	{
//		resultColumn[i] = 0;
//	}
//
//	for (int i = 0; i < matrix->n; i++)
//	{
//		int column = 1;
//		int col = result->colptr[column];
//
//		int count = 0;
//		while (column <= i) // going through all the computed columns
//		{
//			// finding the i -th row of the current column
//			while (count < col && rowInds[count] < i)
//			{
//				count++;
//			}
//
//			// if this element in the column is not zero
//			if (count < col && rowInds[count] == i)
//			{
//				quad columnMainValue = results[count++];
//				resultColumn[i] -= columnMainValue * columnMainValue;
//
//				// we multiply each element of the rest of the column with the "main value" which is
//				// on the i -th row and then subtract that from the current row's sum
//				while (count < col)
//				{
//					resultColumn[rowInds[count]] -= results[count] * columnMainValue;
//					count++;
//				}
//			}
//			else
//			{
//				count = col;
//			}
//			col = result->colptr[++column];
//		}
//
//		col = matrix->colptr[i];
//
//		resultColumn[i] += matrix->values[col];
//		if (resultColumn[i] < 0)
//		{
//			delete[] resultColumn;
//			delete result;
//			return NULL;
//		}
//		resultColumn[i] = __sqrtq(resultColumn[i]);
//		rowInds.add(i);
//		results.add(resultColumn[i]);
//		col++;
//
//		for (int j = i + 1; j < matrix->n; j++)
//		{
//			quad val = resultColumn[j];
//			if (j == matrix->rowind[col] && col < matrix->colptr[i + 1])
//			{
//				val += matrix->values[col++];
//			}
//			if (val < -THRESHOLD || val > THRESHOLD)
//			{
//				rowInds.add(j);
//				results.add(val / resultColumn[i]);
//			}
//			resultColumn[j] = 0;
//		}
//		resultColumn[i] = 0;
//
//        result->colptr[i + 1] = results.size();
//	}
//
//	delete[] resultColumn;
//
//	result->setNNZ(results.size());
//
//	for (int i = 0; i < results.size(); i++)
//	{
//        result->values[i] = results[i];
//        result->rowind[i] = rowInds[i];
//	}
//
//	return new TSparseMatrix(result);
//}
//
//quad* TSparseMatrix::solve_eqn(const quad* b) const
//{
//	quad* result = new quad[matrix->m];
//
//	TSparseMatrix* LT = this->transposed(); // TODO: isn't there another way?
//
//	int col;
//	quad sum;
//	for (int i = 0; i < matrix->n; i++)
//	{
//		sum = b[i];
//		for (col = LT->matrix->colptr[i]; col < LT->matrix->colptr[i + 1] && LT->matrix->rowind[col] < i; col++)
//		{
//			sum -= LT->matrix->values[col] * result[LT->matrix->rowind[col]];
//		}
//		result[i] = sum / LT->matrix->values[col];
//	}
//	for (int i = matrix->n - 1; i >= 0; i--)
//	{
//		sum = result[i];
//		for (col = matrix->colptr[i + 1] - 1; col >= matrix->colptr[i] && matrix->rowind[col] > i; col--)
//		{
//			sum -= matrix->values[col] * result[matrix->rowind[col]];
//		}
//		result[i] = sum / matrix->values[col];
//	}
//
//	return result;
//}
//
//TSparseMatrix* TSparseMatrix::invert_diagonal_matrix() const
//{
//	Matrix* inverse = new Matrix(matrix->m, matrix->n, matrix->colptr[matrix->n]);
//	for (int i = 0; i < matrix->colptr[matrix->n]; i++)
//	{
//		inverse->values[i] = 1 / matrix->values[i];
//		inverse->rowind[i] = matrix->rowind[i];
//	}
//	for (int i = 0; i <= matrix->n; i++)
//	{
//		inverse->colptr[i] = matrix->colptr[i];
//	}
//	return new TSparseMatrix(inverse);
//}
//
//TSparseMatrix* TSparseMatrix::invert_lower_triangular_cholesky_decomposed() const
//{
//	TSparseMatrix* transposed = this->transposed();
//
//	Vector<quad> results(matrix->colptr[matrix->n] * 4); // TODO: perhaps 4 times is too much?
//	Vector<int> rowInds(matrix->colptr[matrix->n] * 4);
//
//	int i, j, k, l;
//	quad sum = 0;
//
//	Matrix *result = new Matrix(matrix->n, matrix->n);
//	result->colptr[0] = 0;
//
//    for (i = 0; i < matrix->n; i++)
//    {
//        for (j = 0; j < i; j++)
//        {
//			k = result->colptr[j];
//			while (rowInds[k] < j && k < result->colptr[j + 1])
//			{
//				k++;
//			}
//            for (l = transposed->matrix->colptr[i];
//                rowInds[k] < i &&
//				k < result->colptr[j + 1] &&
//                l < transposed->matrix->colptr[i + 1] &&
//                transposed->matrix->rowind[l] < i; )
//            {
//                if (transposed->matrix->rowind[l] < rowInds[k])
//                {
//                    l++;
//                }
//                else if (rowInds[k] == transposed->matrix->rowind[l])
//                {
//                    sum -= results[k] * transposed->matrix->values[l];
//                    k++;
//                    l++;
//                }
//                else
//                {
//                    k++;
//                }
//            }
//
//            if (sum != 0)
//            {
//                rowInds.add(j);
//                results.add(sum / matrix->values[matrix->colptr[i]]);
//                sum = 0;
//            }
//        }
//
//        results.add(1 / matrix->values[matrix->colptr[i]]);
//        rowInds.add(i);
//
//        for (j = i + 1; j < matrix->n; j++)
//        {
//			int size = results.size();
//			k = result->colptr[i];
//			while (rowInds[k] < i && k < size)
//			{
//				k++;
//			}
//            for (l = transposed->matrix->colptr[j];
//                k < size &&
//                rowInds[k] < j &&
//                l < transposed->matrix->colptr[j + 1] &&
//                transposed->matrix->rowind[l] < j; )
//            {
//                if (transposed->matrix->rowind[l] < rowInds[k])
//                {
//                    l++;
//                }
//                else if (rowInds[k] == transposed->matrix->rowind[l])
//                {
//                    sum -= results[k] * transposed->matrix->values[l];
//                    k++;
//                    l++;
//                }
//                else
//                {
//                    k++;
//                }
//            }
//
//            if (sum != 0)
//            {
//                rowInds.add(j);
//                results.add(sum / matrix->values[matrix->colptr[j]]);
//                sum = 0;
//            }
//        }
//        result->colptr[i + 1] = results.size();
//	}
//
//	result->setNNZ(results.size());
//
//	delete transposed;
//
//	for (i = 0; i < results.size(); i++)
//	{
//		result->rowind[i] = rowInds[i];
//		result->values[i] = results[i];
//	}
//
//	return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::invert_lower_triangular_cholesky_decomposed_returning_lower_triangular() const
//{
//	TSparseMatrix* transposed = this->transposed(); // TODO: isn't there another way?
//
//	Vector<quad> results(matrix->colptr[matrix->n] * 4); // TODO: perhaps 4 times is too much?
//	Vector<int> rowInds(matrix->colptr[matrix->n] * 4);
//
//	int i, j, k, l;
//	quad sum = 0;
//
//	Matrix *result = new Matrix(matrix->n, matrix->n);
//	result->colptr[0] = 0;
//
//    for (i = 0; i < matrix->n; i++)
//    {
//        results.add(1 / matrix->values[matrix->colptr[i]]);
//        rowInds.add(i);
//
//        for (j = i + 1; j < matrix->n; j++)
//        {
//			int size = results.size();
//            for (k = result->colptr[i], l = transposed->matrix->colptr[j];
//                k < size &&
//                rowInds[k] < j &&
//                l < transposed->matrix->colptr[j + 1] &&
//                transposed->matrix->rowind[l] < j; )
//            {
//                if (transposed->matrix->rowind[l] < rowInds[k])
//                {
//                    l++;
//                }
//                else if (rowInds[k] == transposed->matrix->rowind[l])
//                {
//                    sum -= results[k] * transposed->matrix->values[l];
//                    k++;
//                    l++;
//                }
//                else
//                {
//                    k++;
//                }
//            }
//
//            if (sum != 0)
//            {
//                rowInds.add(j);
//                results.add(sum / matrix->values[matrix->colptr[j]]);
//                sum = 0;
//            }
//        }
//        result->colptr[i + 1] = results.size();
//	}
//
//	result->setNNZ(results.size());
//
//	delete transposed;
//
//	for (i = 0; i < results.size(); i++)
//	{
//		result->rowind[i] = rowInds[i];
//		result->values[i] = results[i];
//	}
//
//	return new TSparseMatrix(result);
//}
//
//quad* TSparseMatrix::multiply_returning_diagonal(const TSparseMatrix& second) const
//{
//	quad* result = new quad[second.matrix->n];
//    int i, k, l, secondN = second.matrix->n / 2;
//    for (i = 0; i < secondN; i++)
//    {
//		result[i] = 0;
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//			l = matrix->colptr[second.matrix->rowind[k]];
//			while (matrix->rowind[l] < i && l < matrix->colptr[second.matrix->rowind[k] + 1])
//			{
//				l++;
//			}
//			if (matrix->rowind[l] == i && l < matrix->colptr[second.matrix->rowind[k] + 1])
//			{
//				result[i] += matrix->values[l] * second.matrix->values[k];
//			}
//        }
//    }
//    for ( ; i < second.matrix->n; i++)
//    {
//		result[i] = 0;
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//			l = matrix->colptr[second.matrix->rowind[k] + 1] - 1;
//			while (matrix->rowind[l] > i && l >= matrix->colptr[second.matrix->rowind[k]])
//			{
//				l--;
//			}
//			if (matrix->rowind[l] == i && l >= matrix->colptr[second.matrix->rowind[k]])
//			{
//				result[i] += matrix->values[l] * second.matrix->values[k];
//			}
//		}
//    }
//
//	return result;
//}
//
//quad* TSparseMatrix::multiply_three_returning_diagonal(const TSparseMatrix& second, const TSparseMatrix& third) const
//{
//	quad* result = new quad[third.matrix->n]; // TODO: is that correct?
//	int i, k, j, l, thirdN = third.matrix->n / 2;
//    for (i = 0; i < thirdN; i++)
//    {
//		result[i] = 0;
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				j = matrix->colptr[second.matrix->rowind[l]];
//				while (matrix->rowind[j] < i && j < matrix->colptr[second.matrix->rowind[l] + 1])
//				{
//					j++;
//				}
//				if (matrix->rowind[j] == i && j < matrix->colptr[second.matrix->rowind[l] + 1])
//				{
//					result[i] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//		}
//	}
//    for ( ; i < third.matrix->n; i++)
//    {
//		result[i] = 0;
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				j = matrix->colptr[second.matrix->rowind[l] + 1] - 1;
//				while (matrix->rowind[j] > i && j >= matrix->colptr[second.matrix->rowind[l]])
//				{
//					j--;
//				}
//				if (matrix->rowind[j] == i && j >= matrix->colptr[second.matrix->rowind[l]])
//				{
//					result[i] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//		}
//	}
//	return result;
//}
//
//TSparseMatrix* TSparseMatrix::multiply_three_F(const TSparseMatrix& second, const TSparseMatrix& third) const
//{
//	quad *resultColumn = new quad[matrix->m];
//	Vector<quad> results(matrix->m * third.matrix->n / 2);
//	Vector<int> rowInds(matrix->m * third.matrix->n / 2);
//    int i, k, l, j;
//    Matrix *result = new Matrix(matrix->m, third.matrix->n);
//    result->colptr[0] = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//		resultColumn[i] = 0;
//    }
//    for (i = 0; i < third.matrix->n; i++)
//    {
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				for (j = matrix->colptr[second.matrix->rowind[l]]; j < matrix->colptr[second.matrix->rowind[l] + 1]; j++)
//				{
//					resultColumn[matrix->rowind[j]] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                results.add(resultColumn[k]);
//                rowInds.add(k);
//				resultColumn[k] = 0;
//            }
//        }
//		result->colptr[i + 1] = results.size();
//    }
//
//    result->setNNZ(results.size());
//	for (i = 0; i < results.size(); i++)
//	{
//        result->values[i] = results[i];
//        result->rowind[i] = rowInds[i];
//	}
//
//	delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_three_LM(const TSparseMatrix& second, const TSparseMatrix& third) const
//{
//	quad *resultColumn = new quad[matrix->m];
//    int i, k, l, j;
//    Matrix *result;
//    int nnz = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//		resultColumn[i] = 0;
//    }
//    for (i = 0; i < third.matrix->n; i++)
//    {
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				for (j = matrix->colptr[second.matrix->rowind[l]]; j < matrix->colptr[second.matrix->rowind[l] + 1]; j++)
//				{
//					resultColumn[matrix->rowind[j]] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                nnz++;
//				resultColumn[k] = 0;
//            }
//        }
//    }
//    result = new Matrix(matrix->m, third.matrix->n, nnz);
//    result->colptr[0] = 0;
//    int count = 0;
//    for (i = 0; i < third.matrix->n; i++)
//    {
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				for (j = matrix->colptr[second.matrix->rowind[l]]; j < matrix->colptr[second.matrix->rowind[l] + 1]; j++)
//				{
//					resultColumn[matrix->rowind[j]] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                result->values[count] = resultColumn[k];
//                result->rowind[count++] = k;
//				resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = count;
//    }
//
//	delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_three_returning_lower_triangular_F(const TSparseMatrix& second, const TSparseMatrix& third) const
//{
//    quad *resultColumn = new quad[matrix->m];
//    Vector<quad> results((matrix->m * third.matrix->n) / 2 + matrix->m);
//    Vector<int> rowInds((matrix->m * third.matrix->n) / 2 + matrix->m);
//    int i, k, l, j;
//    Matrix *result = new Matrix(matrix->m, third.matrix->n);
//    result->colptr[0] = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//        resultColumn[i] = 0;
//    }
//    for (i = 0; i < third.matrix->n; i++)
//    {
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//                for (j = matrix->colptr[second.matrix->rowind[l] + 1] - 1; j >= matrix->colptr[second.matrix->rowind[l]] && matrix->rowind[j] >= i; j--)
//                {
//                    resultColumn[matrix->rowind[j]] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//                }
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                results.add(resultColumn[k]);
//                rowInds.add(k);
//                resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = results.size();
//    }
//
//    result->setNNZ(results.size());
//    for (i = 0; results.size(); i++)
//    {
//        result->values[i] = results[i];
//        result->rowind[i] = rowInds[i];
//    }
//
//    delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_three_returning_lower_triangular_LM(const TSparseMatrix& second, const TSparseMatrix& third) const
//{
//	quad *resultColumn = new quad[matrix->m];
//    int i, k, l, j;
//    Matrix *result;
//    int nnz = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//		resultColumn[i] = 0;
//    }
//    for (i = 0; i < third.matrix->n; i++)
//    {
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				for (j = matrix->colptr[second.matrix->rowind[l] + 1] - 1; j >= matrix->colptr[second.matrix->rowind[l]] && matrix->rowind[j] >= i; j--)
//				{
//					resultColumn[matrix->rowind[j]] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                nnz++;
//				resultColumn[k] = 0;
//            }
//        }
//    }
//    result = new Matrix(matrix->m, third.matrix->n, nnz);
//    result->colptr[0] = 0;
//    int count = 0;
//    for (i = 0; i < third.matrix->n; i++)
//    {
//        for (k = third.matrix->colptr[i]; k < third.matrix->colptr[i + 1]; k++)
//        {
//            for (l = second.matrix->colptr[third.matrix->rowind[k]]; l < second.matrix->colptr[third.matrix->rowind[k] + 1]; l++)
//            {
//				for (j = matrix->colptr[second.matrix->rowind[l] + 1] - 1; j >= matrix->colptr[second.matrix->rowind[l]] && matrix->rowind[j] >= i; j--)
//				{
//					resultColumn[matrix->rowind[j]] += third.matrix->values[k] * second.matrix->values[l] * matrix->values[j];
//				}
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                result->values[count] = resultColumn[k];
//                result->rowind[count++] = k;
//				resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = count;
//    }
//
//	delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_returning_lower_triangular_F(const TSparseMatrix& second) const
//{
//    quad *resultColumn = new quad[matrix->m];
//    Vector<quad> results((matrix->m * second.matrix->n) / 2 + matrix->m);
//    Vector<int> rowInds((matrix->m * second.matrix->n) / 2 + matrix->m);
//    int i, k, l;
//    Matrix *result = new Matrix(matrix->m, second.matrix->n);
//    result->colptr[0] = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//        resultColumn[i] = 0;
//    }
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k] + 1] - 1; l >= matrix->colptr[second.matrix->rowind[k]] && matrix->rowind[l] >= i; l--)
//            {
//                resultColumn[matrix->rowind[l]] += second.matrix->values[k] * matrix->values[l];
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                results.add(resultColumn[k]);
//                rowInds.add(k);
//                resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = results.size();
//    }
//
//    result->setNNZ(results.size());
//    for (i = 0; i < results.size(); i++)
//    {
//        result->values[i] = results[i];
//        result->rowind[i] = rowInds[i];
//    }
//
//    delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::multiply_returning_lower_triangular_LM(const TSparseMatrix& second) const
//{
//	quad *resultColumn = new quad[matrix->m];
//    int i, k, l;
//    Matrix *result;
//    int nnz = 0;
//    for (i = 0; i < matrix->m; i++)
//    {
//		resultColumn[i] = 0;
//    }
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k] + 1] - 1; l >= matrix->colptr[second.matrix->rowind[k]] && matrix->rowind[l] >= i; l--)
//            {
//                resultColumn[matrix->rowind[l]] += second.matrix->values[k] * matrix->values[l];
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                nnz++;
//                resultColumn[k] = 0;
//            }
//        }
//    }
//    result = new Matrix(matrix->m, second.matrix->n, nnz);
//    result->colptr[0] = 0;
//    int count = 0;
//    for (i = 0; i < second.matrix->n; i++)
//    {
//        for (k = second.matrix->colptr[i]; k < second.matrix->colptr[i + 1]; k++)
//        {
//            for (l = matrix->colptr[second.matrix->rowind[k] + 1] - 1; l >= matrix->colptr[second.matrix->rowind[k]] && matrix->rowind[l] >= i; l--)
//            {
//                resultColumn[matrix->rowind[l]] += second.matrix->values[k] * matrix->values[l];
//            }
//        }
//        for (k = 0; k < matrix->m; k++)
//        {
//            if (resultColumn[k] != 0)
//            {
//                result->values[count] = resultColumn[k];
//                result->rowind[count++] = k;
//				resultColumn[k] = 0;
//            }
//        }
//        result->colptr[i + 1] = count;
//    }
//
//	delete[] resultColumn;
//
//    return new TSparseMatrix(result);
//}
//
//TSparseMatrix* TSparseMatrix::add(const TSparseMatrix& second) const
//{
//    int first = 0, col = 1, sec = 0;
//    int total = 0;
//
//    while (col <= matrix->n)
//    {
//        while (first < matrix->colptr[col] && sec < second.matrix->colptr[col])
//        {
//			quad res;
//            if (matrix->rowind[first] == second.matrix->rowind[sec] && matrix->values[first++] + second.matrix->values[sec++] != 0)
//            {
//	            total++;
//            }
//            else if (matrix->rowind[first] < second.matrix->rowind[sec])
//            {
//				first++;
//				total++;
//            }
//            else
//            {
//				sec++;
//				total++;
//            }
//        }
//        total += matrix->colptr[col] - first + second.matrix->colptr[col] - sec;
//        first = matrix->colptr[col];
//        sec = second.matrix->colptr[col++];
//    }
//
//    Matrix* result = new Matrix(matrix->m, matrix->n, total);
//    first = 0;
//    col = 1;
//    sec = 0;
//    total = 0;
//
//	int colp = 1;
//
//	result->colptr[0] = 0;
//    while (col <= matrix->n)
//    {
//        while (first < matrix->colptr[col] && sec < second.matrix->colptr[col])
//        {
//			quad res;
//            if (matrix->rowind[first] == second.matrix->rowind[sec])
//            {
//				res = matrix->values[first] + second.matrix->values[sec++];
//				if (res != 0)
//				{
//	                result->rowind[total] = matrix->rowind[first];
//	                result->values[total++] = res;
//				}
//				first++;
//            }
//            else if (matrix->rowind[first] < second.matrix->rowind[sec])
//            {
//                result->rowind[total] = matrix->rowind[first];
//                result->values[total++] = matrix->values[first++];
//            }
//            else
//            {
//                result->rowind[total] = second.matrix->rowind[sec];
//                result->values[total++] = second.matrix->values[sec++];
//            }
//        }
//		while (first < matrix->colptr[col])
//		{
//            result->rowind[total] = matrix->rowind[first];
//            result->values[total++] = matrix->values[first++];
//		}
//		while (sec < second.matrix->colptr[col])
//		{
//            result->rowind[total] = second.matrix->rowind[sec];
//            result->values[total++] = second.matrix->values[sec++];
//		}
//		col++;
//		result->colptr[colp++] = total;
//    }
//
//    return new TSparseMatrix(result);
//}
//
//void TSparseMatrix::multiply_by_number(quad n)
//{
//	for (int i = 0; i < matrix->colptr[matrix->n]; i++)
//	{
//		matrix->values[i] *= n;
//	}
//}
//
//void TSparseMatrix::writeMatrixFile(const char *filename) const
//{
//	FILE *f = fopen(filename, "wt");
//	fprintf(f, "%d %d %d\n", matrix->m, matrix->n, matrix->colptr[matrix->n]);
//	for (int i = 0; i < matrix->n; i++)
//	{
//		for (int j = matrix->colptr[i]; j < matrix->colptr[i + 1]; j++)
//		{
//			fprintf(f, "%d %d %.20e\n", matrix->rowind[j] + 1, i + 1, matrix->values[j]);
//		}
//	}
//	fclose(f);
//}
//
//TSparseMatrix* TSparseMatrix::readMatrixFile(const char* filename)
//{
//	FILE *f = fopen(filename, "rt");
//
//	int row = 0, column = 0, nnz = 0;
//	fscanf(f, "%d %d %d\n", &row, &column, &nnz);
//	Matrix* matrix = new Matrix(row, column, nnz);
//
//	int count = 0;
//	int colptr = 1;
//	matrix->colptr[0] = 0;
//	int oldcol = 1;
//	while (!feof(f))
//	{
//		double temp;
//		fscanf(f, "%d %d %lf\n", &row, &column, &temp);
//
//		while (oldcol != column)
//		{
//			matrix->colptr[colptr++] = count;
//			oldcol++;
//		}
//
//		matrix->rowind[count] = row - 1;
//		matrix->values[count++] = temp;
//	}
//	matrix->colptr[colptr] = count;
//	fclose(f);
//
//	return new TSparseMatrix(matrix);
//}
//
