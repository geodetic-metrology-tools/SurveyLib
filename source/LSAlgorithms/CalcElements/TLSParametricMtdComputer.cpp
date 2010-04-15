//
// TLSParametricMtdComputer.cpp : implementation file
// class for a least squares computer producing the results matrices
// using the parametric method (case where 2nd dgn mtrx = -I)
//


#include "TLSParametricMtdComputer.h"
#include "TLSResultsMatrices.h"
#include "TLSInputMatrices.h"

#include	<nag.h>
#include	<nagg01.h>
//////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////
TLSParametricMtdComputer::TLSParametricMtdComputer():
fError("")/*, fS0PostUpLimit(LITERAL(0.0)), fS0PostLoLimit(LITERAL(0.0)), fSigmaZero2(LITERAL(0.0))*/
{//default constructor
	count = 1;
}


TLSParametricMtdComputer::~TLSParametricMtdComputer()
{//destructor
}



bool TLSParametricMtdComputer::computeResults(TLSInputMatrices* im , TLSResultsMatrices* rm)
{
	bool result;
	int nbCnstr = im->getNbrConstraints();
	if(rm->getSolutionVctr()->dimension() != 0)
	{
		if(nbCnstr == 0)
		{
			result = computeResultsMtrs(im, rm);
		}
		else
		{
			result = computeFreeResultsMtrs( im, rm);
		}
	}
	else
	{//pas d'inconnue
		result = true;
	}
	return result;
}





////////////////////////////////////////////////////////////////
//COMPUTES THE RESULTS MATRICES
////////////////////////////////////////////////////////////////
bool TLSParametricMtdComputer::computeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm)
{
	/* in this method, the solution is computed with a numeric equations solver method (nagc lib).
	   The unknown variance-covariance matrix is thus not computed here.
	   The fAtPAInv attribute contains the AtPA product, and is updated during each iteration.
	   It is finally inverted outside the method, when there are no iterations left to
	   be performed (in TLSCalculation). */

	const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
	const TSparseMatrix* weightM = im->getWeightMtrx();
	const TColumnVector& misclV = im->getMisclosureVctr();

    TSparseMatrix* firstDM = firstDMTransposed->transposed();
	im->setFirstDesignMatrix(firstDM);
	TSparseMatrix* aTransTimesW = firstDMTransposed->multiply_F(*weightM);

	TSparseMatrix* fAtPA = aTransTimesW->multiply_returning_lower_triangular_F(*firstDM);
#if _DEBUG
	firstDM->write_matrix_file("C:\\AOld.txt");
	aTransTimesW->write_matrix_file("C:\\AtPOld.txt");
	fAtPA->write_matrix_file("C:\\AtPAOld.txt");
	for (int i = 0; i < misclV.dimension(); i++)
	{
		printf("%.20e\n", (double) misclV(i));
	}
#endif

	int success = 0;

	if (rm->getL() != NULL)
	{
		delete rm->getL();
	}
	TSparseMatrix* L = fAtPA->cholesky_decompose_lower_triangular_returning_lower_triangular();
	//L->write_matrix_file("C:\\LOld.txt");

	delete fAtPA;

	if (L == NULL)
	{
		return false; // Matrix is not positive definite
	}

	rm->setL(L);

	real* solutionVectorb = *aTransTimesW * misclV;
	for (int i = 0; i < aTransTimesW->rowsCount(); i++)
	{
		solutionVectorb[i] = -solutionVectorb[i];
#if _DEBUG
		printf("%.20e\n", (double) solutionVectorb[i]);
#endif
	}
	delete aTransTimesW;

	real* solution = L->solve_eqn(solutionVectorb);

	delete[] solutionVectorb;

	TColumnVector* solutionVector = rm->getSolutionVctr();
	*solutionVector = TColumnVector(im->getNbrUnknowns());
	for (int i = 0; i < im->getNbrUnknowns(); i++)
	{
		(*solutionVector)(i) = solution[i];
	}

	return true;
}


////////////////////////////////////////////////////////////////
//COMPUTES THE RESULTS MATRICES FOR FREE CALCULATION
////////////////////////////////////////////////////////////////
bool TLSParametricMtdComputer::computeFreeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm){

	const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
	const TSparseMatrix* constraintFirstDM = im->getCnstrFirstDgnMtrx();
	const TSparseMatrix* weightM = im->getWeightMtrx();
	const TColumnVector& misclV = im->getMisclosureVctr();
	const TColumnVector& constraintMisclV = im->getCnstrMisclosureVctr();

	TSparseMatrix* firstDM = firstDMTransposed->transposed();
	im->setFirstDesignMatrix(firstDM);

	TSparseMatrix* aTransTimesW = firstDMTransposed->multiply_F(*weightM);

	TSparseMatrix* temp = aTransTimesW->multiply_returning_lower_triangular_F(*firstDM);
	real* aTransTimesWTimesMiscVec = *aTransTimesW * misclV;
	int solVecRows = aTransTimesW->rowsCount();

#if _DEBUG
	firstDM->write_matrix_file("C:\\AOld.txt");
	aTransTimesW->write_matrix_file("C:\\AtPOld.txt");
	temp->write_matrix_file("C:\\AtPAOld.txt");
	constraintFirstDM->write_matrix_file("C:\\COld.txt");

	for (int i = 0; i < misclV.dimension(); i++)
	{
		printf("%.20e\n", (double) misclV(i));
	}
#endif
	delete aTransTimesW;

    int nnz = temp->columnPointers()[temp->columnsCount()] + constraintFirstDM->columnPointers()[constraintFirstDM->columnsCount()];
    int cols = temp->columnsCount() + constraintFirstDM->rowsCount();
    real* bigValues = new real[nnz];
    int* bigRowind = new int[nnz];
    int* bigColptr = new int[cols + 1];
    bigColptr[0] = 0;

    int count = 0;
    for (int i = 0; i < temp->columnsCount(); i++)
    {
        for (int j = temp->columnPointers()[i]; j < temp->columnPointers()[i + 1]; j++)
        {
            bigValues[count] = temp->values()[j];
            bigRowind[count++] = temp->rowIndices()[j];
        }
        for (int j = constraintFirstDM->columnPointers()[i]; j < constraintFirstDM->columnPointers()[i + 1]; j++)
        {
            bigValues[count] = constraintFirstDM->values()[j];
            bigRowind[count++] = constraintFirstDM->rowIndices()[j] + temp->rowsCount();
        }
        bigColptr[i + 1] = count;
    }
	for (int i = temp->columnsCount() + 1; i <= cols; i++)
	{
        bigColptr[i] = count;
	}
	delete temp;

    TSparseMatrix* bigMatrix = new TSparseMatrix(cols, cols,
		bigValues, bigRowind, bigColptr);
#if _DEBUG
	bigMatrix->write_matrix_file("C:\\bigOld.txt");
#endif

	real* bigSolutionVector = new real[cols];
	for (int i = 0; i < solVecRows; i++)
	{
		bigSolutionVector[i] = -aTransTimesWTimesMiscVec[i];
	}
	for (int i = solVecRows, j = 0; j < constraintMisclV.dimension(); i++, j++)
	{
		bigSolutionVector[i] = -constraintMisclV(j);
	}
	delete[] aTransTimesWTimesMiscVec;

	if (rm->getBigMatrix() != NULL)
	{
		delete rm->getBigMatrix();
	}
	real* D;
	TSparseMatrix* ldlt = bigMatrix->ldlt_decompose_lower_triangular_returning_lower_triangular(D);
	if (ldlt == NULL)
	{
		delete bigMatrix;
		delete[] bigSolutionVector;
		return false;
	}
	rm->setBigMatrix(bigMatrix);

	real* solution = ldlt->solve_ldlt(D, bigSolutionVector);
	delete[] bigSolutionVector;

	TColumnVector* s = rm->getSolutionVctr();
	for (int i = 0; i < s->dimension(); i++)
	{
		(*s)(i) = solution[i];
	}

	delete[] solution;

	return true;
}



////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////
