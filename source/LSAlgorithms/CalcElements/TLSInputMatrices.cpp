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
	firstDesignMatrixTransposedValues = new list<double>();
	firstDesignMatrixTransposedColPtr = new list<int>();
	firstDesignMatrixTransposedRowInd = new list<int>();

	secondDesignMatrixTransposedValues = new list<double>();
	secondDesignMatrixTransposedColPtr = new list<int>();
	secondDesignMatrixTransposedRowInd = new list<int>();

	weightMatrixValues = new list<double>();

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

	constraintFirstDesignMatrixValues = new list<double>();
	constraintFirstDesignMatrixColPtr = new list<int>();
	constraintFirstDesignMatrixRowInd = new list<int>();
}



/*
void TLSInputMatrices::setS0APrioriScaleFactor(double scalefac)
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


bool TLSInputMatrices::setFirstDgnMtrxElement(MatrixIndex column, double coeff)
{//sets an element of the first design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		firstDesignMatrixTransposedValues->push_back(coeff);
		firstDesignMatrixTransposedRowInd->push_back(column);
	}

	return successfullySet;
}


bool TLSInputMatrices::setSecondDgnMtrxElement(MatrixIndex column, double coeff)
{//sets an element of the second design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		secondDesignMatrixTransposedValues->push_back(coeff);
		secondDesignMatrixTransposedRowInd->push_back(column);
	}

	return successfullySet;
}


bool TLSInputMatrices::setMisclosureVectorElement(MatrixIndex row, double coeff)
{//sets an element of the misclosure vector
	bool successfullySet = true;
	if (row <= fNbEqn)
		(*fMisclosureVector)(row) = (*fMisclosureVector)(row) + coeff;
	else
		successfullySet = false;

	return successfullySet;
}


bool TLSInputMatrices::setWeightMtrxElement(double coeff)
{//sets en element of the weight matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		weightMatrixValues->push_back(coeff);
	}

	return successfullySet;
}


bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, double coeff)
{//sets an element of the constraint first design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		constraintFirstDesignMatrixValues->push_back(coeff);
		constraintFirstDesignMatrixRowInd->push_back(row);
	}
	return successfullySet;
}


bool TLSInputMatrices::setCnstrMisclosureVectorElement(MatrixIndex row, double coeff)
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
	firstDesignMatrixTransposed = new TSparseMatrix(fNbEqn, fNbUnk,
		firstDesignMatrixTransposedValues->size(), firstDesignMatrixTransposedValues, 
		firstDesignMatrixTransposedRowInd, firstDesignMatrixTransposedColPtr);
	
	firstDesignMatrixTransposedValues->clear();
	firstDesignMatrixTransposedRowInd->clear();
	firstDesignMatrixTransposedColPtr->clear();

	secondDesignMatrixTransposed = new TSparseMatrix(fNbObs, fNbUnk,
		secondDesignMatrixTransposedValues->size(), secondDesignMatrixTransposedValues, 
		secondDesignMatrixTransposedRowInd, secondDesignMatrixTransposedColPtr);	
	
	secondDesignMatrixTransposedValues->clear();
	secondDesignMatrixTransposedRowInd->clear();
	secondDesignMatrixTransposedColPtr->clear();

	list<int>* rowinds = new list<int>();
	for (int i = 0; i <= fNbObs; i++)
	{
		rowinds->push_back(i);
	}
	weightMatrix = new TSparseMatrix(fNbObs, fNbObs,
		weightMatrixValues->size(), weightMatrixValues, 
		rowinds, rowinds);

	weightMatrixValues->clear();

	if (fNbCnstr != 0)
	{
		while (constraintFirstDesignMatrixColPtr->size() <= fNbUnk)
		{
			setConstraintNewColumn();
		}

		fCnstrFirstDesignMtrx = new TSparseMatrix(fNbUnk, fNbCnstr,
			constraintFirstDesignMatrixValues->size(), constraintFirstDesignMatrixValues,
			constraintFirstDesignMatrixRowInd, constraintFirstDesignMatrixColPtr);

		constraintFirstDesignMatrixValues->clear();
		constraintFirstDesignMatrixRowInd->clear();
		constraintFirstDesignMatrixColPtr->clear();
	}

	delete rowinds;
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


///////////////////////////////////////////////////////////////////////////////
//DEBUG METHOD : saves the content of the matrices to a text file
///////////////////////////////////////////////////////////////////////////////
void TLSInputMatrices::saveMatricesToFile(int nbIter) const{

	// TODO: fix
	/*ostringstream oss;
	oss << "C:\\temp\\inputMatrices" << nbIter << ".txt";
	string fileName = oss.str();

	ofstream of(fileName.c_str(), ios::out);
	if (!of){
		cerr << "Impossible d'ouvrir le fichier C:\\temp\\inputMatrices.txt" << '\n';
		exit (1);
	}

	of << setprecision(9);

	of << "Number of Unknowns : " << fNbUnk << endl;
	of << "Number of Observations : " << fNbObs << endl;
	of << "Number of Equations : " << fNbEqn << endl << endl;

	of << "***********************" << endl;
	of << "* FIRST DESIGN MATRIX *" << endl;
	of << "***********************" << endl << endl;
	
	int i;
	for (i=0; i<fNbEqn ; i++){

		for (int j=0; j<fNbUnk ; j++)
			of << (*fFirstDesignMtrx)(i,j) << '\t';
		of << endl;
	}
	of << endl << endl;


	of << "*********************" << endl;
	of << "* MISCLOSURE VECTOR *" << endl;
	of << "*********************" << endl << endl;
	
	for (i=0; i<fNbObs ; i++)
		of << (*fMisclosureVector)(i) << endl;
	of << endl << endl;


	if (fCnstrFirstDesignMtrx != 0)
	{
		of << "**********************************" << endl;
		of << "* CONSTRAINT FIRST DESIGN MATRIX *" << endl;
		of << "**********************************" << endl << endl;
		
		for (i=0; i<fNbCnstr ; i++){

			for (int j=0; j<fNbUnk ; j++)
				of << (*fCnstrFirstDesignMtrx)(i,j) << '\t';
			of << endl;
		}
		of << endl << endl;
	}


	if (fCnstrMisclosureVector != 0)
	{
		of << "********************************" << endl;
		of << "* CONSTRAINT MISCLOSURE VECTOR *" << endl;
		of << "********************************" << endl << endl;
		
		for (i=0; i<fNbCnstr ; i++)
			of << (*fCnstrMisclosureVector)(i) << endl;
		of << endl << endl;
	}


	of << "*****************" << endl;
	of << "* WEIGHT MATRIX *" << endl;
	of << "*****************" << endl << endl;
	
	for (i=0; i<fNbObs ; i++){

		for (int j=0; j<fNbObs ; j++)
			of << (*fWeightMtrx)(i,j) << '\t';
		of << endl;
	}
	of << endl << endl;



	of << "************************" << endl;
	of << "* SECOND DESIGN MATRIX *" << endl;
	of << "************************" << endl << endl;
	
	for (i=0; i<fNbEqn ; i++){

		for (int j=0; j<fNbObs ; j++)
			of << (*fSecondDesignMtrx)(i,j) << '\t';
		of << endl;
	}
	of << endl << endl;

	of.close();*/
}


/////////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////////