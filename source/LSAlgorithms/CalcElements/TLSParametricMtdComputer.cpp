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
fError("")/*, fS0PostUpLimit(0.0), fS0PostLoLimit(0.0), fSigmaZero2(0.0)*/
{//default constructor
	count = 1;
}


TLSParametricMtdComputer::~TLSParametricMtdComputer()
{//destructor
}



bool TLSParametricMtdComputer::computeResults(TLSInputMatrices* im , TLSResultsMatrices* rm, bool isCombinedCase)
{
	bool result;
	int nbCnstr = im->getNbrConstraints();
	if(rm->getSolutionVctr()->dimension() != 0)
	{
		if(nbCnstr == 0)
		{
			result = computeResultsMtrs(im, rm, isCombinedCase);
		}
		else
		{
			result = computeFreeResultsMtrs( im, rm, isCombinedCase);
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
bool TLSParametricMtdComputer::computeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm, bool isCombinedCase)
{
	/* in this method, the solution is computed with a numeric equations solver method (nagc lib).
	   The unknown variance-covariance matrix is thus not computed here. 
	   The fAtPAInv attribute contains the AtPA product, and is updated during each iteration. 
	   It is finally inverted outside the method, when there are no iterations left to 
	   be performed (in TLSCalculation). */

	if (isCombinedCase)
	{		
		const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
		const TSparseMatrix* secondDMTransposed = im->getSecondDgnMtrxTransposed();
		TSparseMatrix* weightMInversed = im->getWeightMtrx()->invert_diagonal_matrix();
		im->setWeightMatrixInverted(weightMInversed);
		const TColumnVector& misclV = im->getMisclosureVctr();
		
		TSparseMatrix* firstDM = firstDMTransposed->transposed();
		im->setFirstDesignMatrix(firstDM);
		TSparseMatrix* secondDM = secondDMTransposed->transposed();
		TSparseMatrix* bTimesWInvTimesBTrans = secondDM->multiply_three_returning_lower_triangular_F(*weightMInversed, *secondDMTransposed);
        delete secondDM;

		TSparseMatrix* temp = bTimesWInvTimesBTrans->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete bTimesWInvTimesBTrans;
		TSparseMatrix* bTimesWInvTimesBTransInverted = temp->invert_lower_triangular_cholesky_decomposed();
		delete temp;
		im->setBTimesWInvTimesBTransInverted(bTimesWInvTimesBTransInverted);

		TSparseMatrix* aTransTimesBTimesWInvTimesBTransInverted = firstDMTransposed->multiply_F(*bTimesWInvTimesBTransInverted);

		TSparseMatrix* solutionMatrixA = aTransTimesBTimesWInvTimesBTransInverted->multiply_returning_lower_triangular_F(*firstDM);

		real* solutionVectorb = *aTransTimesBTimesWInvTimesBTransInverted * misclV;
		for (int i = 0; i < aTransTimesBTimesWInvTimesBTransInverted->rowsCount(); i++)
		{
			solutionVectorb[i] = -solutionVectorb[i];
		}
		delete aTransTimesBTimesWInvTimesBTransInverted;

		if (rm->getL() != NULL)
		{
			delete rm->getL();
		}
		TSparseMatrix* L = solutionMatrixA->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete solutionMatrixA;

		if (L == NULL)
		{
			delete[] solutionVectorb;
			// TODO: set some error
			return false; // Matrix is not positive definite
		}

		rm->setL(L);

		real* solution = L->solve_eqn(solutionVectorb);

		delete[] solutionVectorb;

		TColumnVector* solutionVector = rm->getSolutionVctr();
		*solutionVector = TColumnVector(im->getNbrUnknowns());
		for (int i = 0; i < im->getNbrUnknowns(); i++)
		{
			(*solutionVector)(i) = solution[i];
		}

		delete[] solution;
	}
	else
	{
		const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
		const TSparseMatrix* weightM = im->getWeightMtrx();
		const TColumnVector& misclV = im->getMisclosureVctr();
		
		TSparseMatrix* firstDM = firstDMTransposed->transposed();
		firstDM->writeMatrixFile("C:\\A.txt");
		im->setFirstDesignMatrix(firstDM);
		TSparseMatrix* aTransTimesW = firstDMTransposed->multiply_F(*weightM);
		aTransTimesW->writeMatrixFile("C:\\AtP.txt");

		TSparseMatrix* fAtPA = aTransTimesW->multiply_returning_lower_triangular_F(*firstDM);
		fAtPA->writeMatrixFile("C:\\AtPA.txt");
		real* solutionVectorb = *aTransTimesW * misclV;
		for (int i = 0; i < aTransTimesW->rowsCount(); i++)
		{
			solutionVectorb[i] = -solutionVectorb[i];
			printf("%.20e\n", (double) solutionVectorb[i]);
		}
		delete aTransTimesW;

		if (rm->getL() != NULL)
		{
			delete rm->getL();
		}
		TSparseMatrix* L = fAtPA->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete fAtPA;

		if (L == NULL)
		{
			delete[] solutionVectorb;
			// TODO: set some error
			return false; // Matrix is not positive definite
		}

		rm->setL(L);

		real* solution = L->solve_eqn(solutionVectorb);

		delete[] solutionVectorb;

		TColumnVector* solutionVector = rm->getSolutionVctr();
		*solutionVector = TColumnVector(im->getNbrUnknowns());
		for (int i = 0; i < im->getNbrUnknowns(); i++)
		{
			(*solutionVector)(i) = solution[i];
		}

		delete[] solution;
	}

	return true;
}


////////////////////////////////////////////////////////////////
//COMPUTES THE RESULTS MATRICES FOR FREE CALCULATION
////////////////////////////////////////////////////////////////
bool TLSParametricMtdComputer::computeFreeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm, bool isCombinedCase)
{
	if (isCombinedCase)
	{
		const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
		const TSparseMatrix* secondDMTransposed = im->getSecondDgnMtrxTransposed();
		const TSparseMatrix* constraintFirstDM = im->getCnstrFirstDgnMtrx();
		TSparseMatrix* weightMInversed = im->getWeightMtrx()->invert_diagonal_matrix();
		im->setWeightMatrixInverted(weightMInversed);
		const TColumnVector& misclV = im->getMisclosureVctr();
		const TColumnVector& constraintMisclV = im->getCnstrMisclosureVctr();
		
		TSparseMatrix* firstDM = firstDMTransposed->transposed();
		im->setFirstDesignMatrix(firstDM);
		TSparseMatrix* secondDM = secondDMTransposed->transposed();		
		TSparseMatrix* constraintFirstDMTransposed = constraintFirstDM->transposed();
		TSparseMatrix* bTimesWInvTimesBTrans =
			secondDM->multiply_three_returning_lower_triangular_F(*weightMInversed, *secondDMTransposed);
        delete secondDM;

		TSparseMatrix* temp = bTimesWInvTimesBTrans->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete bTimesWInvTimesBTrans;
		TSparseMatrix* bTimesWInvTimesBTransInverted = temp->invert_lower_triangular_cholesky_decomposed();
		delete temp;
		im->setBTimesWInvTimesBTransInverted(bTimesWInvTimesBTransInverted);

		TSparseMatrix* aTransTimesBTimesWInvTimesBTransInverted = firstDMTransposed->multiply_F(*bTimesWInvTimesBTransInverted);

		temp = aTransTimesBTimesWInvTimesBTransInverted->multiply_returning_lower_triangular_F(*firstDM);
		TSparseMatrix* decomposed = temp->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete temp;
		
		TSparseMatrix* aTransTimesBTimesWInvTimesBTransInvertedTimesAInverted = decomposed->invert_lower_triangular_cholesky_decomposed();
		delete decomposed;

		TSparseMatrix* cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted =
			constraintFirstDM->multiply_F(*aTransTimesBTimesWInvTimesBTransInvertedTimesAInverted);
		delete constraintFirstDM;

		TSparseMatrix* solutionMatrixA = cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted->
				multiply_returning_lower_triangular_F(*constraintFirstDMTransposed);
		decomposed = solutionMatrixA->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete solutionMatrixA;

		real* aTransTimesBTimesWInvTimesBTransInvertedTimesMiscVec =
			*aTransTimesBTimesWInvTimesBTransInverted * misclV;
		delete aTransTimesBTimesWInvTimesBTransInverted;

		real* solutionVectorb = *cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted *
			aTransTimesBTimesWInvTimesBTransInvertedTimesMiscVec;
		delete cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted;

		for (int i = 0; i < misclV.dimension(); i++)
		{
			solutionVectorb[i] = constraintMisclV(i) - solutionVectorb[i];
		}

		real* solution = decomposed->solve_eqn(solutionVectorb);
		delete decomposed;		
		delete[] solutionVectorb;

		solutionVectorb = *constraintFirstDMTransposed * solution;
		delete[] solution;
		
		for (int i = 0; i < misclV.dimension(); i++)
		{
			solutionVectorb[i] = -solutionVectorb[i] - aTransTimesBTimesWInvTimesBTransInvertedTimesMiscVec[i];
		}
		delete[] aTransTimesBTimesWInvTimesBTransInvertedTimesMiscVec;

		solution = *aTransTimesBTimesWInvTimesBTransInvertedTimesAInverted * solutionVectorb;
		delete[] solutionVectorb;
		delete aTransTimesBTimesWInvTimesBTransInvertedTimesAInverted;

		TColumnVector* s = rm->getSolutionVctr();
		for (int i = 0; i < misclV.dimension(); i++)
		{
			(*s)(i) = solution[i];
		}

		delete[] solution;
	}
	else
	{
		const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
		const TSparseMatrix* constraintFirstDM = im->getCnstrFirstDgnMtrx();
		const TSparseMatrix* weightM = im->getWeightMtrx();
		const TColumnVector& misclV = im->getMisclosureVctr();
		const TColumnVector& constraintMisclV = im->getCnstrMisclosureVctr();
		
		TSparseMatrix* firstDM = firstDMTransposed->transposed();
		im->setFirstDesignMatrix(firstDM);
		TSparseMatrix* constraintFirstDMTransposed = constraintFirstDM->transposed();

		TSparseMatrix* aTransW = firstDMTransposed->multiply_F(*weightM);

		TSparseMatrix* temp = aTransW->multiply_returning_lower_triangular_F(*firstDM);
		TSparseMatrix* decomposed = temp->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete temp;
		
		TSparseMatrix* aTransTimesWTimesAInverted = decomposed->invert_lower_triangular_cholesky_decomposed();
		delete decomposed;

		TSparseMatrix* cstrATimesATransTimesWTimesAInverted =
			constraintFirstDM->multiply_F(*aTransTimesWTimesAInverted);
		delete constraintFirstDM;

		TSparseMatrix* solutionMatrixA = cstrATimesATransTimesWTimesAInverted->
				multiply_returning_lower_triangular_F(*constraintFirstDMTransposed);
		decomposed = solutionMatrixA->cholesky_decompose_lower_triangular_returning_lower_triangular();
		delete solutionMatrixA;

		real* aTransTimesWTimesATimesMiscVec = *aTransW * misclV;
		delete aTransW;

		real* solutionVectorb = *cstrATimesATransTimesWTimesAInverted * aTransTimesWTimesATimesMiscVec;
		delete cstrATimesATransTimesWTimesAInverted;

		for (int i = 0; i < misclV.dimension(); i++)
		{
			solutionVectorb[i] = constraintMisclV(i) - solutionVectorb[i];
		}

		real* solution = decomposed->solve_eqn(solutionVectorb);
		delete decomposed;
		delete[] solutionVectorb;

		solutionVectorb = *constraintFirstDMTransposed * solution;
		delete[] solution;
		
		for (int i = 0; i < misclV.dimension(); i++)
		{
			solutionVectorb[i] = -solutionVectorb[i] - aTransTimesWTimesATimesMiscVec[i];
		}
		delete[] aTransTimesWTimesATimesMiscVec;

		solution = *aTransTimesWTimesAInverted * solutionVectorb;
		delete[] solutionVectorb;
		delete aTransTimesWTimesAInverted;

		TColumnVector* s = rm->getSolutionVctr();
		for (int i = 0; i < misclV.dimension(); i++)
		{
			(*s)(i) = solution[i];
		}

		delete[] solution;
	}

	return true;
}



////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////
