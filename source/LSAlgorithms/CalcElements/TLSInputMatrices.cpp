/*SURVEYLIB VERSION !!!!!!!!!!!!!!!!!!!!!!!*/

//TLSInputMatrices.h : implementation file
// class for input matrices as defined for survey purposes
// and for the least squares solving algorithm
/***DEBUG*///
#include <iostream>
#include <iomanip>
using namespace std;

#include "TLSInputMatrices.h"


/////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////
TLSInputMatrices::TLSInputMatrices()
{//Constructor
	firstDesignMatrixTransposedValues = new list<real>();
	firstDesignMatrixTransposedColPtr = new list<int>();
	firstDesignMatrixTransposedRowInd = new list<int>();

	secondDesignMatrixTransposedValues = new list<real>();
	secondDesignMatrixTransposedColPtr = new list<int>();
	secondDesignMatrixTransposedRowInd = new list<int>();

	weightMatrixValues = new list<real>();

	firstDesignMatrixTransposed = NULL;
	secondDesignMatrixTransposed = NULL;
	weightMatrix = NULL;
	bTimesWInvTimesBTransInverted = NULL;
	weightMatrixInverted = NULL;

	fCnstrFirstDesignMtrx = NULL;

	fMisclosureVector = NULL;

	fCnstrMisclosureVector = 0;

	constraintFirstDesignMatrixValues = NULL;
	constraintFirstDesignMatrixColPtr = NULL;
	constraintFirstDesignMatrixRowInd = NULL;

	fNbUnk = 0;
	fNbEqn = 0;
	fNbObs = 0;
	fNbCnstr = 0;
	fNbCnstrObs = 0;

//	fS0APrioriScaleFactor = 1;
}


TLSInputMatrices::~TLSInputMatrices()
{//Destructor
	delete firstDesignMatrixTransposedValues;
	delete firstDesignMatrixTransposedColPtr;
	delete firstDesignMatrixTransposedRowInd;
	delete secondDesignMatrixTransposedValues;
	delete secondDesignMatrixTransposedColPtr;
	delete secondDesignMatrixTransposedRowInd;
	delete weightMatrixValues;
	delete fMisclosureVector;

	if (constraintFirstDesignMatrixValues != NULL)
	{
		delete constraintFirstDesignMatrixValues;
		delete constraintFirstDesignMatrixColPtr;
		delete constraintFirstDesignMatrixRowInd;
		delete fCnstrFirstDesignMtrx;
		delete fCnstrMisclosureVector;
	}
}



/////////////////////////////////////////////////////////////////////////////////
//SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////
void TLSInputMatrices::setDimensions(int unknowns, int equations, int observations,  int cnstrObs)
{//sets the dimensions of the matrices

	fNbUnk = unknowns;
	fNbObs = observations; // number of observations + constraint observations
	fNbEqn = equations;
	fNbCnstrObs = cnstrObs;

	clearMatrices();
	fMisclosureVector = new TColumnVector(fNbObs);
}


void TLSInputMatrices::setDimensions(int unknowns, int equations, int observations, int nbCnstrObs, int constraints)
{//sets the dimensions of the matrices

	fNbUnk = unknowns;
	fNbObs = observations; // number of observations + constraint observations
	fNbEqn = equations;
	fNbCnstr = constraints;
	fNbCnstrObs = nbCnstrObs;

	clearMatrices();
	fMisclosureVector = new TColumnVector(fNbObs);
	fCnstrMisclosureVector = new TColumnVector(fNbCnstr);

	constraintFirstDesignMatrixValues = new list<real>();
	constraintFirstDesignMatrixColPtr = new list<int>();
	constraintFirstDesignMatrixRowInd = new list<int>();
}



/*
void TLSInputMatrices::setS0APrioriScaleFactor(real scalefac)
{//sets the scale factor for the S0 a priori
	fS0APrioriScaleFactor = scalefac;
}*/

void TLSInputMatrices::clearMatrices()
{
	if (firstDesignMatrixTransposed != NULL)
	{
		delete secondDesignMatrixTransposed;
		delete firstDesignMatrixTransposed;
		delete weightMatrix;

		firstDesignMatrixTransposed = NULL;
		secondDesignMatrixTransposed = NULL;
		weightMatrix = NULL;
	}

	if (fCnstrFirstDesignMtrx != NULL)
	{
		delete fCnstrFirstDesignMtrx;
		fCnstrFirstDesignMtrx = NULL;
	}

	if (weightMatrixInverted != NULL)
	{
		delete weightMatrixInverted;
		weightMatrixInverted = NULL;
	}

	if (bTimesWInvTimesBTransInverted != NULL)
	{
		delete bTimesWInvTimesBTransInverted;
		bTimesWInvTimesBTransInverted = NULL;
	}

	if (constraintFirstDesignMatrixValues != NULL)
	{
		delete constraintFirstDesignMatrixValues;
		delete constraintFirstDesignMatrixColPtr;
		delete constraintFirstDesignMatrixRowInd;

		constraintFirstDesignMatrixValues = NULL;
		constraintFirstDesignMatrixColPtr = NULL;
		constraintFirstDesignMatrixRowInd = NULL;
	}

	if (fMisclosureVector != NULL)
	{
		delete fMisclosureVector;
	}
	if (fCnstrMisclosureVector != NULL)
	{
		delete fCnstrMisclosureVector;
	}
}


bool TLSInputMatrices::setFirstDgnMtrxElement(MatrixIndex column, real coeff)
{//sets an element of the first design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		firstDesignMatrixTransposedValues->push_back(coeff);
		firstDesignMatrixTransposedRowInd->push_back(column);
	}

	return successfullySet;
}


bool TLSInputMatrices::setSecondDgnMtrxElement(MatrixIndex column, real coeff)
{//sets an element of the second design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		secondDesignMatrixTransposedValues->push_back(coeff);
		secondDesignMatrixTransposedRowInd->push_back(column);
	}

	return successfullySet;
}


bool TLSInputMatrices::setMisclosureVectorElement(MatrixIndex row, real coeff)
{//sets an element of the misclosure vector
	bool successfullySet = true;
	if (row <= fNbEqn)
		(*fMisclosureVector)(row) = (*fMisclosureVector)(row) + coeff;
	else
		successfullySet = false;

	return successfullySet;
}


bool TLSInputMatrices::setWeightMtrxElement(real coeff)
{//sets en element of the weight matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		weightMatrixValues->push_back(coeff);
	}

	return successfullySet;
}


bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, real coeff)
{//sets an element of the constraint first design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		constraintFirstDesignMatrixValues->push_back(coeff);
		constraintFirstDesignMatrixRowInd->push_back(row);
	}
	return successfullySet;
}


bool TLSInputMatrices::setCnstrMisclosureVectorElement(MatrixIndex row, real coeff)
{//sets an element of the constraint misclosure vector
	bool successfullySet = true;
	if (row <= fNbCnstr)
	{
		(*fCnstrMisclosureVector)(row) = (*fCnstrMisclosureVector)(row) + coeff;
	}
	else
	{
		successfullySet = false;
	}
	return successfullySet;
}

void TLSInputMatrices::setNewRow()
{
	firstDesignMatrixTransposedColPtr->push_back(firstDesignMatrixTransposedValues->size());
	secondDesignMatrixTransposedColPtr->push_back(secondDesignMatrixTransposedValues->size());
}

void TLSInputMatrices::setConstraintNewColumn()
{
	constraintFirstDesignMatrixColPtr->push_back(constraintFirstDesignMatrixValues->size());
}

void TLSInputMatrices::finishedFillingMatrices()
{
	real* vals = new real[firstDesignMatrixTransposedValues->size()];
	int* cols = new int[firstDesignMatrixTransposedColPtr->size()];
	int* rows = new int[firstDesignMatrixTransposedRowInd->size()];
	list<real>::const_iterator iter = firstDesignMatrixTransposedValues->begin();
	list<int>::const_iterator iterRows = firstDesignMatrixTransposedRowInd->begin();
	int i = 0;
	while (iter != firstDesignMatrixTransposedValues->end())
	{
		rows[i] = *iterRows;
		vals[i++] = *iter;

		iter++;
		iterRows++;
	}
	firstDesignMatrixTransposedValues->clear();
	firstDesignMatrixTransposedRowInd->clear();

	i = 0;
	list<int>::const_iterator iterCols = firstDesignMatrixTransposedColPtr->begin();
	while (iterCols != firstDesignMatrixTransposedColPtr->end())
	{
		cols[i++] = *iterCols;

		iterCols++;
	}
	firstDesignMatrixTransposedColPtr->clear();

	real* vals2 = new real[secondDesignMatrixTransposedValues->size()];
	int* cols2 = new int[secondDesignMatrixTransposedColPtr->size()];
	int* rows2 = new int[secondDesignMatrixTransposedRowInd->size()];

	list<real>::const_iterator iter2 = secondDesignMatrixTransposedValues->begin();
	list<int>::const_iterator iterRows2 = secondDesignMatrixTransposedRowInd->begin();
	i = 0;
	while (iter2 != secondDesignMatrixTransposedValues->end())
	{
		rows2[i] = *iterRows2;
		vals2[i++] = *iter2;

		iter2++;
		iterRows2++;
	}
	secondDesignMatrixTransposedValues->clear();
	secondDesignMatrixTransposedRowInd->clear();

	i = 0;
	list<int>::const_iterator iterCols2 = secondDesignMatrixTransposedColPtr->begin();
	while (iterCols2 != secondDesignMatrixTransposedColPtr->end())
	{
		cols2[i++] = *iterCols2;

		iterCols2++;
	}
	secondDesignMatrixTransposedColPtr->clear();

	firstDesignMatrixTransposed = new TSparseMatrix(fNbUnk, fNbEqn,
		vals, rows, cols);
	secondDesignMatrixTransposed = new TSparseMatrix(fNbUnk, fNbObs,
		vals2, rows2, cols2);
	int* rowinds = new int[fNbObs + 1];
	for (i = 0; i <= fNbObs; i++)
	{
		rowinds[i] = i;
	}

	real* vals3 = new real[weightMatrixValues->size()];
	list<real>::const_iterator iter3 = weightMatrixValues->begin();
	i = 0;
	while (iter3 != weightMatrixValues->end())
	{
		vals3[i++] = *iter3;

		iter3++;
	}
	weightMatrixValues->clear();

	weightMatrix = new TSparseMatrix(fNbObs, fNbObs,
		vals3, rowinds, rowinds);

	if (fNbCnstr != 0)
	{
		while (constraintFirstDesignMatrixColPtr->size() <= fNbUnk)
		{
			setConstraintNewColumn();
		}

        real* vals4 = new real[constraintFirstDesignMatrixValues->size()];
        int* cols4 = new int[constraintFirstDesignMatrixColPtr->size()];
        int* rows4 = new int[constraintFirstDesignMatrixRowInd->size()];
        list<real>::const_iterator iter4 = constraintFirstDesignMatrixValues->begin();
        list<int>::const_iterator iterRows4 = constraintFirstDesignMatrixRowInd->begin();
        i = 0;
        while (iter4 != constraintFirstDesignMatrixValues->end())
        {
            rows4[i] = *iterRows4;
            vals4[i++] = *iter4;

            iter4++;
            iterRows4++;
        }
        constraintFirstDesignMatrixValues->clear();
        constraintFirstDesignMatrixRowInd->clear();

        i = 0;
        list<int>::const_iterator iterCols4 = constraintFirstDesignMatrixColPtr->begin();
        while (iterCols4 != constraintFirstDesignMatrixColPtr->end())
        {
            cols4[i++] = *iterCols4;

            iterCols4++;
        }
        constraintFirstDesignMatrixColPtr->clear();

		fCnstrFirstDesignMtrx = new TSparseMatrix(fNbCnstr, fNbUnk,
			vals4, rows4, cols4);
	}
}

////////////////////////////////////////////////////////////////////////////////
//ACCESS METHOD FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
const TSparseMatrix* TLSInputMatrices::getFirstDgnMtrxTransposed() const
{//returns a reference to the first dgn matrix
	return firstDesignMatrixTransposed;
}

const TSparseMatrix* TLSInputMatrices::getSecondDgnMtrxTransposed() const
{//returns a reference to the first dgn matrix
	return secondDesignMatrixTransposed;
}

const TSparseMatrix* TLSInputMatrices::getWeightMtrx() const
{
	return weightMatrix;
}

const TColumnVector& TLSInputMatrices::getMisclosureVctr() const
{// returns a reference to the misclosure vector
	return *fMisclosureVector;
}


const TSparseMatrix* TLSInputMatrices::getCnstrFirstDgnMtrx() const
{//returns a reference to the constraint first dgn matrix
	return fCnstrFirstDesignMtrx;
}


const TColumnVector& TLSInputMatrices::getCnstrMisclosureVctr() const
{// returns a reference to the constraint misclosure vector
	return *fCnstrMisclosureVector;
}

int TLSInputMatrices::getNbrUnknowns() const
{
	return fNbUnk;
}

int TLSInputMatrices::getNbrEquations() const
{
	return fNbEqn;
}

int TLSInputMatrices::getNbrObservations() const
{
	return fNbObs;
}

//zero or 1
int TLSInputMatrices::getNbrConstraintObs() const
{
	return fNbCnstrObs;
}

//zero or 1
int TLSInputMatrices::getNbrConstraints() const
{
	return fNbCnstr;
}



/////////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////////
