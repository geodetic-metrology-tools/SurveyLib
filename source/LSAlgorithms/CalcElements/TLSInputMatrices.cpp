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
	fFirstDesignMtrx = 0;
	fSecondDesignMtrx = 0;
	fWeightMtrx = 0;
	fMisclosureVector = 0;
	
	fCnstrFirstDesignMtrx = 0;
	fCnstrMisclosureVector = 0;

	fNbUnk = 0;
	fNbEqn = 0;
	fNbObs = 0;
	fNbCnstr = 0;
	fNbCnstrObs = 0;

//	fS0APrioriScaleFactor = 1;
}


TLSInputMatrices::~TLSInputMatrices()
{//Destructor
	delete fFirstDesignMtrx;
	delete fSecondDesignMtrx;
	delete fWeightMtrx;
	delete fMisclosureVector;

	delete fCnstrFirstDesignMtrx;
	delete fCnstrMisclosureVector;


}



/////////////////////////////////////////////////////////////////////////////////
//SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////
void TLSInputMatrices::setDimensions(int unknowns, int equations, int observations,  int cnstrObs)
{//sets the dimensions of the matrices

	if ((fNbUnk == unknowns) && (fNbObs == observations) && (fNbEqn == equations)){

		*fFirstDesignMtrx = 0.0;	
		*fSecondDesignMtrx = 0.0;
		*fMisclosureVector = 0.0;
		*fWeightMtrx = 0.0;
	}
	else{

		fNbUnk = unknowns;
		fNbObs = observations;
		fNbEqn = equations;
		fNbCnstrObs = cnstrObs; 
	
		delete fFirstDesignMtrx;
		delete fSecondDesignMtrx;
		delete fWeightMtrx;
		delete fMisclosureVector;
	
		//debug
		fFirstDesignMtrx = new TMatrix(equations, unknowns);
		*fFirstDesignMtrx = 0.0;

	
		fSecondDesignMtrx = new TMatrix(equations, observations /*+ cnstrObs*/);
		*fSecondDesignMtrx = 0.0;
	
		fMisclosureVector = new TColumnVector(equations);
		*fMisclosureVector = 0.0;
	
		fWeightMtrx = new TMatrix(observations /*+ cnstrObs*/, observations /*+ cnstrObs*/);
		*fWeightMtrx = 0.0;
	}
	return;
}


void TLSInputMatrices::setDimensions(int unknowns, int equations, int observations, int nbCnstrObs, int constraints)
{//sets the dimensions of the matrices

	if ((fNbUnk == unknowns) && (fNbObs == observations) &&
		(fNbEqn == equations) && (fNbCnstr == constraints))
	{

		*fFirstDesignMtrx = 0.0;	
		*fSecondDesignMtrx = 0.0;
		*fMisclosureVector = 0.0;
		*fWeightMtrx = 0.0;

		*fCnstrFirstDesignMtrx = 0.0;	
		*fCnstrMisclosureVector = 0.0;
	}
	else
	{

		fNbUnk = unknowns;
		fNbObs = observations;
		fNbEqn = equations;
		fNbCnstr = constraints;
		fNbCnstrObs = nbCnstrObs;

		delete fFirstDesignMtrx;
		delete fSecondDesignMtrx;
		delete fWeightMtrx;
		delete fMisclosureVector;
		delete fCnstrFirstDesignMtrx;	
		delete fCnstrMisclosureVector;

	
		fFirstDesignMtrx = new TMatrix(equations, unknowns);
		*fFirstDesignMtrx = 0.0;
	
		fSecondDesignMtrx = new TMatrix(equations, observations /*+ nbCnstrObs*/);
		*fSecondDesignMtrx = 0.0;
	
		fMisclosureVector = new TColumnVector(equations);
		*fMisclosureVector = 0.0;
	
		fWeightMtrx = new TMatrix(observations /*+ nbCnstrObs*/, observations /*+ nbCnstrObs*/);
		*fWeightMtrx = 0.0;

		fCnstrFirstDesignMtrx = new TMatrix(constraints, unknowns);
		*fFirstDesignMtrx = 0.0;

		fCnstrMisclosureVector = new TColumnVector(constraints);
		*fMisclosureVector = 0.0;

	}

	return;
}



/*
void TLSInputMatrices::setS0APrioriScaleFactor(double scalefac)
{//sets the scale factor for the S0 a priori
	fS0APrioriScaleFactor = scalefac;
}*/


bool TLSInputMatrices::setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, double coeff)
{//sets an element of the first design matrix
	bool successfullySet = true;
	if (row<=fNbEqn && column <=fNbUnk)
		(*fFirstDesignMtrx)(row, column) = (*fFirstDesignMtrx)(row, column) + coeff;
	else
		successfullySet = false;

	return successfullySet;
}


bool TLSInputMatrices::setSecondDgnMtrxElement(MatrixIndex row, MatrixIndex column, double coeff)
{//sets an element of the second design matrix
	bool successfullySet = true;
	if (row<=fNbEqn && column <=fNbObs)
		(*fSecondDesignMtrx)(row, column) = (*fSecondDesignMtrx)(row, column) + coeff;
	else
		successfullySet = false;

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


bool TLSInputMatrices::setWeightMtrxElement(MatrixIndex row, MatrixIndex column, double coeff)
{//sets en element of the weight matrix
	bool successfullySet = true;
	if (row<=fNbObs && column <=fNbObs)
		(*fWeightMtrx)(row, column) = (*fWeightMtrx)(row, column) + coeff;
	else
		successfullySet = false;

	return successfullySet;
}


bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, double coeff)
{//sets an element of the constraint first design matrix
	bool successfullySet = true;
	if (row<=fNbCnstr && column <=fNbUnk)
	{
		(*fCnstrFirstDesignMtrx)(row, column) = (*fCnstrFirstDesignMtrx)(row, column) + coeff;
	}
	else
	{
		successfullySet = false;
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


////////////////////////////////////////////////////////////////////////////////
//ACCESS METHOD FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
const TMatrix& TLSInputMatrices::getFirstDgnMtrx() const
{//returns a reference to the first dgn matrix
	return *fFirstDesignMtrx;
}


const TMatrix& TLSInputMatrices::getSecondDgnMtrx() const
{//returns a reference to the second dgn matrix
	return *fSecondDesignMtrx;
}


const TMatrix& TLSInputMatrices::getWeightMtrx() const
{//returns a reference to the first dgn matrix
	return *fWeightMtrx;
}


const TColumnVector& TLSInputMatrices::getMisclosureVctr() const
{// returns a reference to the misclosure vector
	return *fMisclosureVector;
}


const TMatrix& TLSInputMatrices::getCnstrFirstDgnMtrx() const
{//returns a reference to the constraint first dgn matrix
	return *fCnstrFirstDesignMtrx;
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

	ostringstream oss;
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
	
	for (int i=0; i<fNbEqn ; i++){

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

	of.close();
}


/////////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////////