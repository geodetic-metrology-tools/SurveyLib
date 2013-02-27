/*SURVEYLIB VERSION !!!!!!!!!!!!!!!!!!!!!!!*/

//TLSInputMatrices.h : implementation file
// class for input matrices as defined for survey purposes
// and for the least squares solving algorithm
/***DEBUG*///
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "TLSInputMatrices.h"


/////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////
TLSInputMatrices::TLSInputMatrices()
{//Constructor
	
	firstDesignMatrix = nullptr;
	secondDesignMatrix = nullptr;
	weightMatrix = nullptr;
	fCnstrFirstDesignMtrx = nullptr;
	
	fMisclosureVector = nullptr;
	fCnstrMisclosureVector = nullptr;

	fNbUnk = 0;
	fNbEqn = 0;
	fNbObs = 0;
	fNbCnstr = 0;
	fNbCnstrObs = 0;


//	fS0APrioriScaleFactor = 1;
}


TLSInputMatrices::~TLSInputMatrices()
{//Destructor
	clearMatrices();
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
	fMisclosureVector = new TVector(fNbObs);

	// TODO: Reserve space in sparse matrices - after discussing fill factors
	firstDesignMatrix = new TSparseMatrix(equations, unknowns);
	secondDesignMatrix = new TSparseMatrix(equations, observations /*+ cnstrObs*/);
	weightMatrix = new TSparseMatrix(observations /*+ cnstrObs*/, observations /*+ cnstrObs*/);
}


void TLSInputMatrices::setDimensions(int unknowns, int equations, int observations, int nbCnstrObs, int constraints)
{//sets the dimensions of the matrices

	fNbUnk = unknowns;
	fNbObs = observations; // number of observations + constraint observations
	fNbEqn = equations;
	fNbCnstr = constraints;
	fNbCnstrObs = nbCnstrObs;

	clearMatrices();
	fMisclosureVector = new TVector(fNbObs);
	fCnstrMisclosureVector = new TVector(constraints);

	// TODO: Reserve space in sparse matrices - after discussing fill factors
	firstDesignMatrix = new TSparseMatrix(equations, unknowns);
	secondDesignMatrix = new TSparseMatrix(equations, observations /*+ cnstrObs*/);
	weightMatrix = new TSparseMatrix(observations /*+ cnstrObs*/, observations /*+ cnstrObs*/);
	fCnstrFirstDesignMtrx = new	TSparseMatrix(constraints, unknowns);
}



/*
void TLSInputMatrices::setS0APrioriScaleFactor(TReal scalefac)
{//sets the scale factor for the S0 a priori
	fS0APrioriScaleFactor = scalefac;
}*/

void TLSInputMatrices::clearMatrices()
{
	//delete firstDesignMatrix;
	//delete secondDesignMatrix;
	//delete weightMatrix;
	//delete fMisclosureVector;
	//delete fCnstrFirstDesignMtrx;
	//delete fCnstrMisclosureVector;
}


bool TLSInputMatrices::setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{//sets an element of the first design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		firstDesignMatrix->insert(row,column) = coeff;
#ifdef _DEBUG
		//std::cout << "TLSInputMatrices::setFirstDgnMtrxElement " << row << " " << column << " " << firstDesignMatrix->coeff(row,column) << std::endl;
#endif
	}
	return successfullySet;
}


bool TLSInputMatrices::setSecondDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{//sets an element of the second design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		secondDesignMatrix->insert(row,column) = coeff;
#ifdef _DEBUG
		//std::cout << "TLSInputMatrices::setSecondDgnMtrxElement " << row << " " << column << " " << secondDesignMatrix->coeff(row,column) << std::endl;
#endif
	}

	return successfullySet;
}


bool TLSInputMatrices::setMisclosureVectorElement(MatrixIndex row, TReal coeff)
{//sets an element of the misclosure vector
	bool successfullySet = true;
	if (row <= fNbEqn)
		(*fMisclosureVector)(row) = coeff;
	else
		successfullySet = false;

	return successfullySet;
}


bool TLSInputMatrices::setWeightMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{//sets en element of the weight matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		weightMatrix->insert(row,column) = coeff;
#ifdef _DEBUG
		//std::cout << "TLSInputMatrices::setWeightMtrxElement " << row << " " << column << " " << weightMatrix->coeff(row,column) << std::endl;
#endif

	}

	return successfullySet;
}


bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{//sets an element of the constraint first design matrix
	bool successfullySet = true;
	if (coeff != 0)
	{
		fCnstrFirstDesignMtrx->insert(row,column) = coeff;
	}
	return successfullySet;
}


bool TLSInputMatrices::setCnstrMisclosureVectorElement(MatrixIndex row, TReal coeff)
{//sets an element of the constraint misclosure vector
	bool successfullySet = true;
	if (row <= fNbCnstr)
	{
		(*fCnstrMisclosureVector)(row) = coeff;
	}
	else
	{
		successfullySet = false;
	}
	return successfullySet;
}

//void TLSInputMatrices::setNewRow()
//{
//	firstDesignMatrixTransposedColPtr->push_back(firstDesignMatrixTransposedValues->size());
//	secondDesignMatrixTransposedColPtr->push_back(secondDesignMatrixTransposedValues->size());
//}
//
//void TLSInputMatrices::setConstraintNewColumn()
//{
//	constraintFirstDesignMatrixColPtr->push_back(constraintFirstDesignMatrixValues->size());
//}
//
//void TLSInputMatrices::finishedFillingMatrices()
//{
//	TReal* vals = new TReal[firstDesignMatrixTransposedValues->size()];
//	int* cols = new int[firstDesignMatrixTransposedColPtr->size()];
//	int* rows = new int[firstDesignMatrixTransposedRowInd->size()];
//	list<TReal>::const_iterator iter = firstDesignMatrixTransposedValues->begin();
//	list<int>::const_iterator iterRows = firstDesignMatrixTransposedRowInd->begin();
//	int i = 0;
//	while (iter != firstDesignMatrixTransposedValues->end())
//	{
//		rows[i] = *iterRows;
//		vals[i++] = *iter;
//
//		iter++;
//		iterRows++;
//	}
//	firstDesignMatrixTransposedValues->clear();
//	firstDesignMatrixTransposedRowInd->clear();
//
//	i = 0;
//	list<int>::const_iterator iterCols = firstDesignMatrixTransposedColPtr->begin();
//	while (iterCols != firstDesignMatrixTransposedColPtr->end())
//	{
//		cols[i++] = *iterCols;
//
//		iterCols++;
//	}
//	firstDesignMatrixTransposedColPtr->clear();
//
//	TReal* vals2 = new TReal[secondDesignMatrixTransposedValues->size()];
//	int* cols2 = new int[secondDesignMatrixTransposedColPtr->size()];
//	int* rows2 = new int[secondDesignMatrixTransposedRowInd->size()];
//
//	list<TReal>::const_iterator iter2 = secondDesignMatrixTransposedValues->begin();
//	list<int>::const_iterator iterRows2 = secondDesignMatrixTransposedRowInd->begin();
//	i = 0;
//	while (iter2 != secondDesignMatrixTransposedValues->end())
//	{
//		rows2[i] = *iterRows2;
//		vals2[i++] = *iter2;
//
//		iter2++;
//		iterRows2++;
//	}
//	secondDesignMatrixTransposedValues->clear();
//	secondDesignMatrixTransposedRowInd->clear();
//
//	i = 0;
//	list<int>::const_iterator iterCols2 = secondDesignMatrixTransposedColPtr->begin();
//	while (iterCols2 != secondDesignMatrixTransposedColPtr->end())
//	{
//		cols2[i++] = *iterCols2;
//
//		iterCols2++;
//	}
//	secondDesignMatrixTransposedColPtr->clear();
//
//	firstDesignMatrixTransposed = new TSparseMatrix(fNbUnk, fNbEqn,
//		vals, rows, cols);
//	secondDesignMatrixTransposed = new TSparseMatrix(fNbUnk, fNbObs,
//		vals2, rows2, cols2);
//	int* rowinds = new int[fNbObs + 1];
//	for (i = 0; i <= fNbObs; i++)
//	{
//		rowinds[i] = i;
//	}
//
//	TReal* vals3 = new TReal[weightMatrixValues->size()];
//	list<TReal>::const_iterator iter3 = weightMatrixValues->begin();
//	i = 0;
//	while (iter3 != weightMatrixValues->end())
//	{
//		vals3[i++] = *iter3;
//
//		iter3++;
//	}
//	weightMatrixValues->clear();
//
//	weightMatrix = new TSparseMatrix(fNbObs, fNbObs,
//		vals3, rowinds, rowinds);
//
//	if (fNbCnstr != 0)
//	{
//		while (constraintFirstDesignMatrixColPtr->size() <= fNbUnk)
//		{
//			setConstraintNewColumn();
//		}
//
//        TReal* vals4 = new TReal[constraintFirstDesignMatrixValues->size()];
//        int* cols4 = new int[constraintFirstDesignMatrixColPtr->size()];
//        int* rows4 = new int[constraintFirstDesignMatrixRowInd->size()];
//        list<TReal>::const_iterator iter4 = constraintFirstDesignMatrixValues->begin();
//        list<int>::const_iterator iterRows4 = constraintFirstDesignMatrixRowInd->begin();
//        i = 0;
//        while (iter4 != constraintFirstDesignMatrixValues->end())
//        {
//            rows4[i] = *iterRows4;
//            vals4[i++] = *iter4;
//
//            iter4++;
//            iterRows4++;
//        }
//        constraintFirstDesignMatrixValues->clear();
//        constraintFirstDesignMatrixRowInd->clear();
//
//        i = 0;
//        list<int>::const_iterator iterCols4 = constraintFirstDesignMatrixColPtr->begin();
//        while (iterCols4 != constraintFirstDesignMatrixColPtr->end())
//        {
//            cols4[i++] = *iterCols4;
//
//            iterCols4++;
//        }
//        constraintFirstDesignMatrixColPtr->clear();
//
//		fCnstrFirstDesignMtrx = new TSparseMatrix(fNbCnstr, fNbUnk,
//			vals4, rows4, cols4);
//	}
//}

////////////////////////////////////////////////////////////////////////////////
//ACCESS METHOD FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
const TSparseMatrix* TLSInputMatrices::getFirstDgnMtrx() const
{//returns a reference to the first dgn matrix
	return firstDesignMatrix;
}

const TSparseMatrix* TLSInputMatrices::getSecondDgnMtrx() const
{//returns a reference to the first dgn matrix
	return secondDesignMatrix;
}

const TSparseMatrix* TLSInputMatrices::getWeightMtrx() const
{
	return weightMatrix;
}

const TVector& TLSInputMatrices::getMisclosureVctr() const
{// returns a reference to the misclosure vector
	return *fMisclosureVector;
}


const TSparseMatrix* TLSInputMatrices::getCnstrFirstDgnMtrx() const
{//returns a reference to the constraint first dgn matrix
	return fCnstrFirstDesignMtrx;
}


const TVector& TLSInputMatrices::getCnstrMisclosureVctr() const
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
	std::ostringstream oss;
	oss << "C:\\temp\\inputMatrices" << nbIter << ".txt";
	std::string fileName = oss.str();

	std::ofstream of(fileName.c_str(), std::ios::out);
	if (!of){
		std::cerr << "Impossible d'ouvrir le fichier C:\\temp\\inputMatrices.txt" << '\n';
		std::exit (1);
	}

	of << std::setprecision(9);

	of << "Number of Unknowns : " << fNbUnk << std::endl;
	of << "Number of Observations : " << fNbObs << std::endl;
	of << "Number of Equations : " << fNbEqn << std::endl << std::endl;

	of << "***********************" << std::endl;
	of << "* FIRST DESIGN MATRIX *" << std::endl;
	of << "***********************" << std::endl << std::endl;
	
	of << *firstDesignMatrix;
	of << std::endl << std::endl;


	of << "*********************" << std::endl;
	of << "* MISCLOSURE VECTOR *" << std::endl;
	of << "*********************" << std::endl << std::endl;

	of << *fMisclosureVector;
	of << std::endl << std::endl;


	if (fCnstrFirstDesignMtrx != 0)
	{
		of << "**********************************" << std::endl;
		of << "* CONSTRAINT FIRST DESIGN MATRIX *" << std::endl;
		of << "**********************************" << std::endl << std::endl;
		
		of << fCnstrFirstDesignMtrx;
		of << std::endl << std::endl;
	}


	if (fCnstrMisclosureVector != 0)
	{
		of << "********************************" << std::endl;
		of << "* CONSTRAINT MISCLOSURE VECTOR *" << std::endl;
		of << "********************************" << std::endl << std::endl;
		
		of << fCnstrMisclosureVector;
		of << std::endl << std::endl;
	}


	of << "*****************" << std::endl;
	of << "* WEIGHT MATRIX *" << std::endl;
	of << "*****************" << std::endl << std::endl;
	
	of << *weightMatrix;
	of << std::endl << std::endl;



	of << "************************" << std::endl;
	of << "* SECOND DESIGN MATRIX *" << std::endl;
	of << "************************" << std::endl << std::endl;

	of << *secondDesignMatrix;
	of << std::endl << std::endl;

	of.close();
}


/////////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////////