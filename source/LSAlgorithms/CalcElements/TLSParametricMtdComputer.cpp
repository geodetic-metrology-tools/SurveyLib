//
// TLSParametricMtdComputer.cpp : implementation file
// class for a least squares computer producing the results matrices 
// using the parametric method (case where 2nd dgn mtrx = -I)
//

#include "TLSInputMatrices.h"
#include "TLSResultsMatrices.h"

#include "TLSParametricMtdComputer.h"

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
		// TODO: fix!
		/*
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

		void* factor = taucs_ccs_factor_llt_mf(*bTimesWInvTimesBTrans);
		delete bTimesWInvTimesBTrans;

		TSparseMatrix* temp = TSparseMatrix::getCholeskyFactor(factor);
		TSparseMatrix* bTimesWInvTimesBTransInverted = temp->invert_lower_triangular_cholesky_decomposed();
		delete temp;
		im->setBTimesWInvTimesBTransInverted(bTimesWInvTimesBTransInverted);

		TSparseMatrix* aTransTimesBTimesWInvTimesBTransInverted = firstDMTransposed->multiply_F(*bTimesWInvTimesBTransInverted);

		TSparseMatrix* solutionMatrixA = aTransTimesBTimesWInvTimesBTransInverted->multiply_returning_lower_triangular_F(*firstDM);

		quad* solutionVectorb = *aTransTimesBTimesWInvTimesBTransInverted * misclV;
		for (int i = 0; i < aTransTimesBTimesWInvTimesBTransInverted->rowsCount(); i++)
		{
			solutionVectorb[i] = -solutionVectorb[i];
		}
		delete aTransTimesBTimesWInvTimesBTransInverted;

		if (rm->getL() != NULL)
		{
			delete rm->getL();
		}
		TSparseMatrix* L = solutionMatrixA->decompose_Cholesky();
		delete solutionMatrixA;

		if (L == NULL)
		{
			delete[] solutionVectorb;
			// TODO: set some error
			return false; // Matrix is not positive definite
		}

		rm->setL(L);

		quad* solution = L->solve_eqn(solutionVectorb);

		delete[] solutionVectorb;

		TColumnVector* solutionVector = rm->getSolutionVctr();
		*solutionVector = TColumnVector(im->getNbrUnknowns());
		for (int i = 0; i < im->getNbrUnknowns(); i++)
		{
			(*solutionVector)(i) = solution[i];
		}

		delete[] solution;*/
	}
	else
	{
		const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
		const TSparseMatrix* weightM = im->getWeightMtrx();
		const TColumnVector& misclV = im->getMisclosureVctr();
		
		TSparseMatrix* firstDM = firstDMTransposed->transposed();
		im->setFirstDesignMatrix(firstDM);
		TSparseMatrix* aTransTimesW = firstDMTransposed->multiply_F(*weightM);

		TSparseMatrix* fAtPA = aTransTimesW->multiply_returning_lower_triangular_F(*firstDM);
		quad* solutionVectorb = *aTransTimesW * misclV;
		for (int i = 0; i < aTransTimesW->rowsCount(); i++)
		{
			solutionVectorb[i] = -solutionVectorb[i];
		}
		delete aTransTimesW;

		if (rm->getL() != NULL)
		{
			delete rm->getL();
		}
		TSparseMatrix* L = fAtPA->decompose_Cholesky();
		delete fAtPA;

		if (L == NULL)
		{
			delete[] solutionVectorb;
			// TODO: set some error
			return false; // Matrix is not positive definite
		}

		rm->setL(L);

		quad* solution = L->solve_eqn(solutionVectorb);

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
bool TLSParametricMtdComputer::computeFreeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm, bool isCombinedCase){

	// TODO: fix!
	/*if (isCombinedCase)
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
			secondDM->multiply_three_returning_lower_triangular(*weightMInversed, *secondDMTransposed);
        delete secondDM;

		void* factor = taucs_ccs_factor_llt_mf(*bTimesWInvTimesBTrans);
		delete bTimesWInvTimesBTrans;

		TSparseMatrix* temp = TSparseMatrix::getCholeskyFactor(factor);
		TSparseMatrix* bTimesWInvTimesBTransInverted = temp->invert_lower_triangular_cholesky_decomposed();
		delete temp;
		im->setBTimesWInvTimesBTransInverted(bTimesWInvTimesBTransInverted);

		TSparseMatrix* aTransTimesBTimesWInvTimesBTransInverted = firstDMTransposed->multiply(*bTimesWInvTimesBTransInverted);

		temp = aTransTimesBTimesWInvTimesBTransInverted->multiply_returning_lower_triangular(*firstDM);
		factor = taucs_ccs_factor_llt_mf(*temp);
		delete temp;
		
		temp = TSparseMatrix::getCholeskyFactor(factor);
		TSparseMatrix* aTransTimesBTimesWInvTimesBTransInvertedTimesAInverted = temp->invert_lower_triangular_cholesky_decomposed();
		delete temp;

		TSparseMatrix* cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted =
			constraintFirstDM->multiply(*aTransTimesBTimesWInvTimesBTransInvertedTimesAInverted);
		delete constraintFirstDM;

		TSparseMatrix* solutionMatrixA = cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted->
				multiply_returning_lower_triangular(*constraintFirstDMTransposed);
		factor = taucs_ccs_factor_llt_mf(*solutionMatrixA);
		delete solutionMatrixA;

		quad* aTransTimesBTimesWInvTimesBTransInvertedTimesMiscVec =
			*aTransTimesBTimesWInvTimesBTransInverted * misclV;
		delete aTransTimesBTimesWInvTimesBTransInverted;

		quad* solutionVectorb = *cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted *
			aTransTimesBTimesWInvTimesBTransInvertedTimesMiscVec;
		delete cstrATimesATransTimesBTimesWInvTimesBTransInvertedTimesAInverted;

		for (int i = 0; i < misclV.dimension(); i++)
		{
			solutionVectorb[i] = constraintMisclV(i) - solutionVectorb[i];
		}

		quad* solution = new quad[misclV.dimension()];
		taucs_supernodal_solve_llt(factor, solution, solutionVectorb);
		delete[] solutionVectorb;
		taucs_supernodal_factor_free(factor);

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

		TSparseMatrix* aTransW = firstDMTransposed->multiply(*weightM);

		TSparseMatrix* temp = aTransW->multiply_returning_lower_triangular(*firstDM);
		void* factor = taucs_ccs_factor_llt_mf(*temp);
		delete temp;
		
		temp = TSparseMatrix::getCholeskyFactor(factor);
		TSparseMatrix* aTransTimesWTimesAInverted = temp->invert_lower_triangular_cholesky_decomposed();
		delete temp;

		TSparseMatrix* cstrATimesATransTimesWTimesAInverted =
			constraintFirstDM->multiply(*aTransTimesWTimesAInverted);
		delete constraintFirstDM;

		TSparseMatrix* solutionMatrixA = cstrATimesATransTimesWTimesAInverted->
				multiply_returning_lower_triangular(*constraintFirstDMTransposed);
		factor = taucs_ccs_factor_llt_mf(*solutionMatrixA);
		delete solutionMatrixA;

		quad* aTransTimesWTimesATimesMiscVec = *aTransW * misclV;
		delete aTransW;

		quad* solutionVectorb = *cstrATimesATransTimesWTimesAInverted * aTransTimesWTimesATimesMiscVec;
		delete cstrATimesATransTimesWTimesAInverted;

		for (int i = 0; i < misclV.dimension(); i++)
		{
			solutionVectorb[i] = constraintMisclV(i) - solutionVectorb[i];
		}

		quad* solution = new quad[misclV.dimension()];
		taucs_supernodal_solve_llt(factor, solution, solutionVectorb);
		delete[] solutionVectorb;
		taucs_supernodal_factor_free(factor);

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
	}*/

	return true;
}



////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////
