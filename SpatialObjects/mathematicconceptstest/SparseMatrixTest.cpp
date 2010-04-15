// TestProject.cpp : Defines the entry point for the console application.
//

#define APFLOAT
#define real apfloat

#ifdef APFLOAT
#include "apfloat.h"
#else
#include <stdio.h>
#include <math.h>
#endif

#define SU_TCOLUMN_VECTOR

class TColumnVector
{
public:
	double operator ()(int index) const { return 0; }
};

#define sqrtq sqrt
#define LITERAL(x) x
#include "TSparseMatrix.cpp"

#include <list>
#include <ctime>

using namespace std;

TSparseMatrix* generateMatrix(int rows, int cols)
{
	int i;

	int* rowind = new int[rows * cols];
	int* colptr = new int[cols + 1];

	int rowi = 0;
	int colp = 1;
	colptr[0] = 0;
	for (i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
			if (r >= LITERAL(0.7))
			{
				rowind[rowi++] = j;
			}
		}
		colptr[colp++] = rowi;
	}
	colp--;
	int* realRowind = new int[colptr[colp]];

	for (i = 0; i < colptr[colp]; i++)
	{
		realRowind[i] = rowind[i];
	}
	delete[] rowind;

	int XMin = -10;
	int XMax = 10;
	real* values = new real[colptr[colp]];
	rowi = 0;
	for (int i = 0; i < colptr[colp]; i++)
	{
		double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
		double X = XMin + r * (XMax - XMin); // transform to wanted range
		while (X == 0)
		{
			r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
			X = XMin + r * (XMax - XMin);
		}
#ifdef APFLOAT
		values[rowi++] = apfloat(X, 1000);
#else
        values[rowi++] = X;
#endif
	}

	TSparseMatrix* res = new TSparseMatrix(rows, cols, values, realRowind, colptr);
	
	return res;
}

TSparseMatrix* generateLowerTriangularMatrix(int size)
{
	int i;
	
	int* rowind = new int[size * size];
	int* colptr = new int[size + 1];

	int rowi = 0;
	int colp = 1;
	colptr[0] = 0;
	for (i = 0; i < size; i++)
	{
		rowind[rowi++] = i;
		for (int j = i + 1; j < size; j++)
		{
			double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
			if (r >= LITERAL(0.7))
			{
				rowind[rowi++] = j;
			}
		}
		colptr[colp++] = rowi;
	}
	colp--;
	int* realRowind = new int[colptr[colp]];

	for (i = 0; i < colptr[colp]; i++)
	{
		realRowind[i] = rowind[i];
	}
	delete[] rowind;

	int XMin = -10;
	int XMax = 10;
	real* values = new real[colptr[colp]];
	rowi = 0;
	int whichCol = 0;
	for (int i = 0; i < colptr[colp]; i++)
	{
		double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
		double X = XMin + r * (XMax - XMin); // transform to wanted range
		while (X == 0 || (colptr[whichCol] == i && X < 0))
		{
			r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
			X = XMin + r * (XMax - XMin);
		}
		if (colptr[whichCol] == i)
		{
			whichCol++;
		}
#ifdef APFLOAT
		values[rowi++] = apfloat(X, 1000);
#else
        values[rowi++] = X;
#endif
	}
	
	TSparseMatrix* res = new TSparseMatrix(size, size, values, realRowind, colptr);
	
	return res;
}

TSparseMatrix* generateIntegralLowerTriangularMatrix(int size)
{
	int i;
	
	int* rowind = new int[size * size];
	int* colptr = new int[size + 1];

	int rowi = 0;
	int colp = 1;
	colptr[0] = 0;
	for (i = 0; i < size; i++)
	{
		rowind[rowi++] = i;
		for (int j = i + 1; j < size; j++)
		{
			double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
			if (r >= LITERAL(0.7))
			{
				rowind[rowi++] = j;
			}
		}
		colptr[colp++] = rowi;
	}
	colp--;
	int* realRowind = new int[colptr[colp]];

	for (i = 0; i < colptr[colp]; i++)
	{
		realRowind[i] = rowind[i];
	}
	delete[] rowind;

	int XMin = -10;
	int XMax = 10;
	real* values = new real[colptr[colp]];
	rowi = 0;
	int whichCol = 0;
	for (int i = 0; i < colptr[colp]; i++)
	{
		double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
		double X = XMin + r * (XMax - XMin); // transform to wanted range
		while ((int) X == 0 || (colptr[whichCol] == i && X < 0))
		{
			r = rand() % (XMax - XMin);
			X = XMin + r;
		}
		if (colptr[whichCol] == i)
		{
			whichCol++;
		}
#ifdef APFLOAT
		values[rowi++] = apfloat((int) X, 1000);
#else
        values[rowi++] = (int) X;
#endif
	}
	
	TSparseMatrix* res = new TSparseMatrix(size, size, values, realRowind, colptr);
	
	return res;
}

bool MatricesEqual(const TSparseMatrix& first, const TSparseMatrix& second)
{
	if (first.columnsCount() != second.columnsCount() || first.rowsCount() != second.rowsCount() ||
		first.columnPointers()[first.columnsCount()] != second.columnPointers()[second.columnsCount()])
	{
		return false;
	}
	for (int i = 0; i < first.columnsCount(); i++)
	{
		if (first.columnPointers()[i] != second.columnPointers()[i])
		{
			return false;
		}
	}

	for (int i = 0; i < first.columnPointers()[first.columnsCount()]; i++)
	{
		real temp = first.values()[i] / second.values()[i];
		if (first.rowIndices()[i] != second.rowIndices()[i] ||
#ifdef APFLOAT
			temp < apfloat("0.99999999999999999999999999999999999999999999999999999999999999", 1000)
			|| temp > apfloat("1.00000000000000000000000000000000000000000000000000000000000001", 1000))
#else
            temp < 0.99999999999999 || temp > 1.000000000000000001)
#endif
		{
			return false;
		}
	}

	return true;
}

bool MatricesEqualAtLeast(const TSparseMatrix& first, const TSparseMatrix& second)
{
#ifdef APFLOAT
	apfloat atLeast = apfloat("1E-100", 1000);
#else
	double atLeast = 1e-8;
#endif
	int i, j;
	for (i = 0, j = 0; i < first.columnPointers()[first.columnsCount()] && j < second.columnPointers()[second.columnsCount()]; )
	{
		if (first.values()[i] < atLeast)
		{
			i++;
		}
		else if (second.values()[j] < atLeast)
		{
			j++;
		}
		else
		{
			real temp = first.values()[i] / second.values()[j];
			if (first.rowIndices()[i] != second.rowIndices()[j] ||
#ifdef APFLOAT
				temp < apfloat("0.9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", 1000)
				|| temp > apfloat("1.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", 1000))
#else
				temp < 0.99999999999999 || temp > 1.00000000000001)
#endif
			{
				return false;
			}
			i++;
			j++;
		}
	}
	for ( ; i < first.columnPointers()[first.columnsCount()]; i++)
	{
		if (first.values()[i] >= atLeast)
		{
			return false;
		}
	}
	for ( ; j < second.columnPointers()[second.columnsCount()]; j++)
	{
		if (second.values()[j] >= atLeast)
		{
			return false;
		}
	}

	return true;
}

int main()
{
	srand(time(0));

	int minRows = 60, maxRows = 90;

	for (int count = 0; count < 0; count++)
	{
		int a = rand() % (maxRows - minRows) + minRows;
		int b = rand() % (maxRows - minRows) + minRows;

		TSparseMatrix* A = generateMatrix(a, b);
		TSparseMatrix* B = generateMatrix(a, b);

		TSparseMatrix* added = A->add(*B);
		A->multiply_by_number(-1);
		TSparseMatrix* result = added->add(*A);
		A->multiply_by_number(-1);
		B->multiply_by_number(-1);
		TSparseMatrix* result1 = added->add(*B);
		B->multiply_by_number(-1);

		if (*result != *B || *result1 != *A)
		{
			printf("addition doesn't work!\n");
		}
		
		delete A;
		delete B;
		delete added;
		delete result;
		delete result1;
	}

	for (int count = 0; count < 0; count++)
	{
		int a = rand() % (maxRows - minRows) + minRows;
		int b = rand() % (maxRows - minRows) + minRows;
		int c = rand() % (maxRows - minRows) + minRows;
		int d = rand() % (maxRows - minRows) + minRows;

		TSparseMatrix* A = generateMatrix(a, b);
		TSparseMatrix* B = generateMatrix(b, c);
		TSparseMatrix* C = generateMatrix(c, d);

		TSparseMatrix* temp = A->multiply_F(*B);
		TSparseMatrix* temp2 = temp->multiply_LM(*C);
		delete temp;

		TSparseMatrix* temp3 = A->multiply_three_F(*B, *C);
		TSparseMatrix* temp4 = A->multiply_three_LM(*B, *C);

		if (*temp2 != *temp3 || *temp3 != *temp4)
		{
			printf("multiplication doesn't work!\n");
		}

		delete A;
		delete B;
		delete C;
		delete temp2;
		delete temp3;
		delete temp4;
	}

	for (int count = 0; count < 0; count++)
	{
		int a = rand() % (maxRows - minRows) + minRows;
		int b = rand() % (maxRows - minRows) + minRows;

		TSparseMatrix* A = generateMatrix(a, b);

		TSparseMatrix* trans = A->transposed();
		TSparseMatrix* trans2 = trans->transposed();
		delete trans;

		if (*trans2 != *A)
		{
			printf("transposition doesn't work!\n");
		}

		delete A;
		delete trans2;
	}
	
#ifdef APFLOAT
	apfloat from = apfloat("0.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", 1000);
	apfloat to = apfloat("1.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", 1000);
	apfloat atLeast = apfloat("1E-100", 1000);
#else
    double from = 0.9999999999999;
    double to = 1.000000000000001;
    double atLeast = 1e-50;
#endif


	for (int a = 4; a < 50; a++)
	for (int count = 0; count < 10; count++)
	{
		//int a = rand() % (maxRows - minRows) + minRows;
		TSparseMatrix* L = generateLowerTriangularMatrix(a);

		real* idV = new real[a];
		int* idR = new int[a + 1];

		for (int i = 0; i < a; i++)
		{
			idV[i] = 1;
			idR[i] = i;
		}
		idR[a] = a;

		TSparseMatrix* identity = new TSparseMatrix(a, a, idV, idR, idR);

		TSparseMatrix* LT = L->transposed();
		TSparseMatrix* positiveDefinite = L->multiply_returning_lower_triangular_F(*LT);

		TSparseMatrix* decomposed = positiveDefinite->cholesky_decompose_lower_triangular_returning_lower_triangular();
		
		TSparseMatrix* temp = decomposed->transposed();
		TSparseMatrix* temp2 = decomposed->multiply_returning_lower_triangular_LM(*temp);
		delete temp;

		if (!MatricesEqual(*temp2, *positiveDefinite))
		{
			printf("cholesky decomposition doesn't work!\n");
		}

		delete temp2;

		if (decomposed == NULL || !MatricesEqual(*L, *decomposed))
		{
			printf("cholesky decomposition doesn't work!\n");
		}

		TSparseMatrix* cholInv = decomposed->invert_lower_triangular_cholesky_decomposed_returning_lower_triangular();
		TSparseMatrix* cholInvTrans = cholInv->transposed();
		TSparseMatrix* cholInvFull = decomposed->invert_lower_triangular_cholesky_decomposed();
		TSparseMatrix* cholInvFull1 = cholInv->add(*cholInvTrans);

		real* diagg = new real[cholInvFull1->rowsCount()];
		int* diagIndices = new int[cholInvFull1->rowsCount() + 1];
		for (int i = 0; i < cholInvFull1->rowsCount(); i++)
		{
			diagg[i] = -cholInv->values()[cholInv->columnPointers()[i]];
#ifdef APFLOAT
			diagg[i].prec(1000);
#endif
			diagIndices[i] = i;
		}
		diagIndices[cholInvFull1->rowsCount()] = cholInvFull1->rowsCount();
		TSparseMatrix* te = new TSparseMatrix(cholInvFull1->rowsCount(), cholInvFull1->rowsCount(),
			diagg, diagIndices, diagIndices);
		TSparseMatrix* realCholInvFull = cholInvFull1->add(*te);
		delete te;
		delete cholInvFull1;
		if (!MatricesEqual(*cholInvFull, *realCholInvFull))
		{
			printf("full inversion doesn't work!\n");
		}

		delete cholInvFull;
		delete realCholInvFull;

		TSparseMatrix* positiveDefiniteTrans = positiveDefinite->transposed();
		TSparseMatrix* A = positiveDefinite->add(*positiveDefiniteTrans);

		real* diag = new real[L->rowsCount()];
		int* diagonalIndices = new int[L->rowsCount() + 1];
		for (int i = 0; i < L->rowsCount(); i++)
		{
			diag[i] = -positiveDefinite->values()[positiveDefinite->columnPointers()[i]];
#ifdef APFLOAT
			diag[i].prec(1000);
#endif
			diagonalIndices[i] = i;
		}
		diagonalIndices[L->rowsCount()] = L->rowsCount();

		TSparseMatrix* tempAdd = new TSparseMatrix(L->rowsCount(), L->rowsCount(), diag,
			diagonalIndices, diagonalIndices);
		TSparseMatrix* realA = A->add(*tempAdd);
		delete tempAdd;
		delete A;
		A = realA;

		delete positiveDefiniteTrans;
		TSparseMatrix* AInv = cholInvTrans->multiply_F(*cholInv);
		TSparseMatrix* result = AInv->multiply_LM(*A);
		//TSparseMatrix* result = cholInvTrans->multiply_three_LM(*cholInv, *A);

		if (!MatricesEqualAtLeast(*result, *identity))
		{
			printf("inversion doesn't work!\n");
		}

		real* b = new real[a];

		for (int i = 0; i < a; i++)
		{
			double XMin = -10;
			double XMax = 10;
			double r = double (rand()) / (double (RAND_MAX) + LITERAL(1.0));
			double X = XMin + r * (XMax - XMin); // transform to wanted range
#ifdef APFLOAT
			b[i] = apfloat(X, 1000);
#else
            b[i] = X;
#endif
		}

		real* resAxEqb = *AInv * b;
		real* resAxEqb1 = decomposed->solve_eqn(b);
		
		for (int i = 0; i < a; i++)
		{
			real t = resAxEqb1[i] / resAxEqb[i];

			if (t <= 0 || (!(t >= from && t < to) && t > atLeast))
			{
				printf("equation doesn't work!\n");
				break;
			}
		}

		real* resAxEqb2 = *A * resAxEqb;
		
		for (int i = 0; i < a; i++)
		{
			real t = resAxEqb2[i] / b[i];

			if (t <= 0 || (!(t >= from && t < to) && t > atLeast))
			{
				printf("equation doesn't work!\n");
				break;
			}
		}

		real* D;
		TSparseMatrix* ldlt = L->ldlt_decompose_lower_triangular_returning_lower_triangular(D);

		if (ldlt != NULL)
		{
			real* solutionVector = ldlt->solve_ldlt(D, b);
			TSparseMatrix* ldltInverse = ldlt->invert_lower_triangular_ldlt_decomposed(D);

			TSparseMatrix* transd = ldlt->transposed();
			TSparseMatrix* middle = ldlt->multiply_diagonal_dense(D, ldlt->columnsCount());
			delete ldlt;
			TSparseMatrix* original = middle->multiply_returning_lower_triangular_F(*transd);
			TSparseMatrix* originalBig = middle->multiply_F(*transd);
			delete middle;
			delete transd;
			delete[] D;

			if (!MatricesEqualAtLeast(*original, *L))
			{
				printf("LDLT doesn't work!\n");
			}

			TSparseMatrix* shouldBeIdentity = ldltInverse->multiply_F(*originalBig);
			delete ldltInverse;

			if (!MatricesEqualAtLeast(*shouldBeIdentity, *identity))
			{
				printf("LDLT inversion doesn't work!\n");
			}

			real* otherSolutionVector = *originalBig * solutionVector;
		
			for (int i = 0; i < a; i++)
			{
				real t = otherSolutionVector[i] / b[i];

				if (t <= 0 || (!(t >= from && t < to) && t > atLeast))
				{
					printf("LDLt equation doesn't work!\n");
					break;
				}
			}

			delete original;
			delete originalBig;
			delete[] solutionVector;
		}
		else
		{
			int aghahah = 10;
		}
		
		delete identity;
		delete AInv;
		delete[] b;
		delete[] resAxEqb;
		delete[] resAxEqb1;
		delete[] resAxEqb2;

		delete A;
		delete result;
		delete cholInv;
		delete cholInvTrans;

		delete positiveDefinite;
		delete LT;
		delete L;
		delete decomposed;
	}

	return 0;
}

