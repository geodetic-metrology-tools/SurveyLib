//
// TLSParametricMtdComputer.cpp : implementation file
// class for a least squares computer producing the results matrices
// using the parametric method (case where 2nd dgn mtrx = -I)
//


#include "TLSParametricMtdComputer.h"
#include "TLSResultsMatrices.h"
#include "TLSInputMatrices.h"
#include "TSparseMatrix.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <Eigen/LU>

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
	if(rm->getSolutionVctr()->size() != 0)
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
	/*
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

	TReal* solutionVectorb = *aTransTimesW * misclV;
	for (int i = 0; i < aTransTimesW->rowsCount(); i++)
	{
		solutionVectorb[i] = -solutionVectorb[i];
#if _DEBUG
		printf("%.20e\n", (double) solutionVectorb[i]);
#endif
	}
	delete aTransTimesW;

	TReal* solution = L->solve_eqn(solutionVectorb);

	delete[] solutionVectorb;

	TColumnVector* solutionVector = rm->getSolutionVctr();
	*solutionVector = TColumnVector(im->getNbrUnknowns());
	for (int i = 0; i < im->getNbrUnknowns(); i++)
	{
		(*solutionVector)(i) = solution[i];
	}

	return true;
	*/
	
	const TSparseMatrix * A = im->getFirstDesignMatrix();
	const TSparseMatrix * W = im->getWeightMtrx();
#ifdef _DEBUG
	//std::cout << "TLSParametricMtdComputer::computeResultsMtrs, A=\n " << *A << std::endl;
	//std::cout << "TLSParametricMtdComputer::computeResultsMtrs, W=\n " <<*W << std::endl;
#endif
	const TVector & misclV = im->getMisclosureVctr();
	TSparseMatrix N = A->transpose() * (*W) * (*A);
	Eigen::SimplicialLDLT<TSparseMatrix> chol( N );
#ifdef _DEBUG
	std::cout << "TLSParametricMtdComputer::computeResultsMtrs, det(N)=\n " << chol.determinant() << std::endl;
#endif
	if(chol.info() != Eigen::Success)
	{
		// colesky did not work, try fullPiv
		typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> TMat;
		Eigen::FullPivLU<TMat> lu(N);

		if (! lu.isInvertible()) {
			std::ostringstream foo;
			foo << "TLSParametricMtdComputer::computeResultsMtrs:\n\tsolution failed.";
			fError += foo.str();
			return false;
		}
				
		rm->setIntermediateMatrix(N);
		

		*(rm->getSolutionVctr()) = lu.solve( -A->transpose() * (*W) * misclV );
		return true;

	} 
	else {
		rm->setIntermediateMatrix(N);

		*(rm->getSolutionVctr()) = chol.solve( -A->transpose() * (*W) * misclV );
		return true;
	}
}


////////////////////////////////////////////////////////////////
//COMPUTES THE RESULTS MATRICES FOR FREE CALCULATION
////////////////////////////////////////////////////////////////
bool TLSParametricMtdComputer::computeFreeResultsMtrs(TLSInputMatrices* im, TLSResultsMatrices* rm){
	/*
	const TSparseMatrix* firstDMTransposed = im->getFirstDgnMtrxTransposed();
	const TSparseMatrix* constraintFirstDM = im->getCnstrFirstDgnMtrx();
	const TSparseMatrix* weightM = im->getWeightMtrx();
	const TColumnVector& misclV = im->getMisclosureVctr();
	const TColumnVector& constraintMisclV = im->getCnstrMisclosureVctr();

	TSparseMatrix* firstDM = firstDMTransposed->transposed();
	im->setFirstDesignMatrix(firstDM);

	TSparseMatrix* aTransTimesW = firstDMTransposed->multiply_F(*weightM);

	TSparseMatrix* temp = aTransTimesW->multiply_returning_lower_triangular_F(*firstDM);
	TReal* aTransTimesWTimesMiscVec = *aTransTimesW * misclV;
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
    TReal* bigValues = new TReal[nnz];
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

	TReal* bigSolutionVector = new TReal[cols];
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
	TReal* D;
	TSparseMatrix* ldlt = bigMatrix->ldlt_decompose_lower_triangular_returning_lower_triangular(D);
	if (ldlt == NULL)
	{
		delete bigMatrix;
		delete[] bigSolutionVector;
		return false;
	}
	rm->setBigMatrix(bigMatrix);

	TReal* solution = ldlt->solve_ldlt(D, bigSolutionVector);
	delete[] bigSolutionVector;

	TColumnVector* s = rm->getSolutionVctr();
	for (int i = 0; i < s->dimension(); i++)
	{
		(*s)(i) = solution[i];
	}

	delete[] solution;

	return true;
	*/
	int nbUnk = im->getNbrUnknowns();
	int nbCnstr = im->getNbrConstraints();

	const TSparseMatrix * A1 = im->getFirstDesignMatrix();
	const TSparseMatrix * W  = im->getWeightMtrx();
	const TVector & misclV = im->getMisclosureVctr();

	TSparseMatrix N = A1->transpose() * (*W) * (*A1);
	TVector B1 = - A1->transpose() * (*W) * misclV;

	const TSparseMatrix * A2 = im->getCnstrFirstDgnMtrx();
	const TVector & cMisclV = im->getCnstrMisclosureVctr();

	TSparseMatrix NBig(nbUnk + nbCnstr, nbUnk + nbCnstr);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(N.nonZeros() + 2*A2->nonZeros());
	// Fill in the N part
	for(int k=0; k<N.outerSize(); ++k)
	{
		for(TSparseMatrix::InnerIterator it(N,k); it; ++it)
		{
			coeffs.push_back(TTriplet(it.row(), it.col(), it.value()));
		}
	}
	// Fill the A2 and A2T
	for(int k=0; k<A2->outerSize(); ++k)
	{
		for(TSparseMatrix::InnerIterator it(*A2,k); it; ++it)
		{
			coeffs.push_back(TTriplet(it.row() + N.rows(), it.col(), it.value())); //A2
			coeffs.push_back(TTriplet(it.col(), it.row() + N.cols(), it.value())); // A2T
		}
	}
	NBig.setFromTriplets(coeffs.begin(), coeffs.end());
	Eigen::SimplicialLDLT<TSparseMatrix> chol( NBig );
	if(chol.info() != Eigen::Success)
	{
		fError += "Eigen Cholesky decomposition failed";
		return false;
	}
	rm->setIntermediateMatrix(NBig);

	TVector b(A1->cols() + cMisclV.rows());
	b << -A1->transpose() * (*W) * misclV , cMisclV;
	TVector xBig = chol.solve(b);

	*(rm->getSolutionVctr()) = xBig.head(nbUnk);
	return true;
}



////////////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////////////
