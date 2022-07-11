/*SURVEYLIB VERSION !!!!!!!!!!!!!!!!!!!!!!!*/

//TLSInputMatrices.h : implementation file
// class for input matrices as defined for survey purposes
// and for the least squares solving algorithm
/***DEBUG*///
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Logger.hpp"
#include "TLSInputMatrices.h"
#include <Eigen/Dense>


/////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////
TLSInputMatrices::TLSInputMatrices()
{//Constructor
	
	firstDesignMatrix = nullptr;
	secondDesignMatrix = nullptr;
	secondDesignInvMatrix = nullptr;
	weightMatrix = nullptr;
	weightInvMatrix = nullptr;
	weightUnkMatrix = nullptr;
	fCnstrFirstDesignMtrx = nullptr;
	
	fMisclosureVector = nullptr;
	fCnstrMisclosureVector = nullptr;

	fNbUnk = 0;
	fNbEqn = 0;
	fNbObs = 0;
	fNbCnstr = 0;
	fNbCnstrObs = 0;
}


TLSInputMatrices::~TLSInputMatrices()
{//Destructor
	clearMatrices();
}



/////////////////////////////////////////////////////////////////////////////////
//SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TLSInputMatrices::initMatrices(int unknowns, int equations, int observations, int nbCnstrObs, int nbCnstrUnk)
{//sets the dimensions of the matrices

	fNbUnk = unknowns;
	fNbObs = observations; // number of observations + constraint observations
	fNbEqn = equations;
	fNbCnstrObs = nbCnstrObs;

	clearMatrices();
	fMisclosureVector = new TVector(fNbEqn);

	firstDesignMatrix = new TSparseMatrix(equations, unknowns);
	secondDesignMatrix = new TSparseMatrix(equations, observations /*+ cnstrObs*/);
	secondDesignInvMatrix = new TSparseMatrix(equations, observations /*+ cnstrObs*/);
	weightMatrix = new TSparseMatrix(observations /*+ cnstrObs*/, observations /*+ cnstrObs*/);
	weightInvMatrix = new TSparseMatrix(observations /*+ cnstrObs*/, observations /*+ cnstrObs*/);
	weightUnkMatrix = new TSparseMatrix(unknowns, unknowns);

	if (nbCnstrUnk != 0)
	{
		fNbCnstr = nbCnstrUnk;
		fCnstrMisclosureVector = new TVector(nbCnstrUnk);
		fCnstrFirstDesignMtrx = new	TSparseMatrix(nbCnstrUnk, unknowns);
	}
}

void TLSInputMatrices::clearMatrices()
{
	// TODO: gets deleted externally, change to internal deletion
	
	if (firstDesignMatrix != nullptr) {
		delete firstDesignMatrix;
		firstDesignMatrix = nullptr;
	}
	if (secondDesignMatrix != nullptr) {
		delete secondDesignMatrix;
		secondDesignMatrix = nullptr;
	}
	if (secondDesignInvMatrix != nullptr) {
		delete secondDesignInvMatrix;
		secondDesignInvMatrix = nullptr;
	}
	if (weightMatrix != nullptr) {
		delete weightMatrix;
		weightMatrix = nullptr;
	}
	if (weightInvMatrix != nullptr) {
		delete weightInvMatrix;
		weightInvMatrix = nullptr;
	}
	if (weightUnkMatrix != nullptr) {
		delete weightUnkMatrix;
		weightUnkMatrix = nullptr;
	}
	if (fMisclosureVector != nullptr) {
		delete fMisclosureVector;
		fMisclosureVector = nullptr;
	}
	if (fCnstrFirstDesignMtrx != nullptr) {
		delete fCnstrFirstDesignMtrx;
		fCnstrFirstDesignMtrx = nullptr;
	}
	if (fCnstrMisclosureVector != nullptr) {
		delete fCnstrMisclosureVector;
		fCnstrMisclosureVector = nullptr;
	}
	
}


bool TLSInputMatrices::setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fNbEqn && 0 <= column && column < fNbUnk)
		firstDesignMatrix->coeffRef(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}


bool TLSInputMatrices::setSecondDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fNbEqn && 0 <= column && column < fNbObs)
		secondDesignMatrix->insert(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setSecondDgnMtrxBlock(MatrixIndex first_index, Eigen::MatrixXd block)
{
	try
	{
		// set the blocks of the second design matrix. immediately also set the inverse blocks
		Eigen::MatrixXd block_inverse = block.lu().solve(Eigen::MatrixXd::Identity(block.rows(), block.rows()));
		int dim = block.rows();
		if (dim != block.cols())
			return false;
		// write the block into the second design matrix
		for (int row = 0; row < dim; row++)
		{
			for (int col = 0; col < dim; col++)
			{
				secondDesignMatrix->insert(first_index + row, first_index + col) = block(row, col);
				secondDesignInvMatrix->insert(first_index + row, first_index + col) = block_inverse(row, col);
			}
		}
	}
	catch (...)
	{
		// block has to be square
		return false;
	}

	return true;
}

bool TLSInputMatrices::setMisclosureVectorElement(MatrixIndex row, TReal coeff)
{
	try {
		(*fMisclosureVector)(row) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}


bool TLSInputMatrices::setWeightMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fNbObs && 0 <= column && column < fNbObs){
		weightMatrix->insert(row,column) = coeff;
	}
	
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightInvMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fNbObs && 0 <= column && column < fNbObs)
		weightInvMatrix->insert(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightUnkMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fNbUnk && 0 <= column && column < fNbUnk)
		weightUnkMatrix->insert(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fNbCnstr && 0 <= column && column < fNbUnk)
		fCnstrFirstDesignMtrx->insert(row,column) = coeff;
	} catch(...) {
		logFatal() << "Setting constraints for LIBR calculations in the first design matrix A:\n"
			<< "Could not insert the element (" << row << "," << column << ") with the value: " << coeff << std::endl;
		return false;
	}
	return true;
}


bool TLSInputMatrices::setCnstrMisclosureVectorElement(MatrixIndex row, TReal coeff)
{
	try {
		(*fCnstrMisclosureVector)(row) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}


////////////////////////////////////////////////////////////////////////////////
//ACCESS METHOD FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
const TSparseMatrix* TLSInputMatrices::getFirstDgnMtrx() const noexcept
{//returns a reference to the first dgn matrix
	return firstDesignMatrix;
}

const TSparseMatrix* TLSInputMatrices::getSecondDgnMtrx() const noexcept
{//returns a reference to the first dgn matrix
	return secondDesignMatrix;
}

const TSparseMatrix* TLSInputMatrices::getSecondDgnInvMtrx() const noexcept
{//returns a reference to the inverse of the second dgn matrix
	return secondDesignInvMatrix;
}

const TSparseMatrix* TLSInputMatrices::getWeightMtrx() const noexcept
{
	return weightMatrix;
}

const TSparseMatrix* TLSInputMatrices::getWeightInvMtrx() const noexcept
{
	return weightInvMatrix;
}

const TSparseMatrix* TLSInputMatrices::getWeightUnkMtrx() const noexcept
{
	return weightUnkMatrix;
}

const TVector& TLSInputMatrices::getMisclosureVctr() const noexcept
{// returns a reference to the misclosure vector
	return *fMisclosureVector;
}


const TSparseMatrix* TLSInputMatrices::getCnstrFirstDgnMtrx() const noexcept
{//returns a reference to the constraint first dgn matrix
	return fCnstrFirstDesignMtrx;
}


const TVector& TLSInputMatrices::getCnstrMisclosureVctr() const noexcept
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
		
		of << *fCnstrFirstDesignMtrx;
		of << std::endl << std::endl;
	}


	if (fCnstrMisclosureVector != 0)
	{
		of << "********************************" << std::endl;
		of << "* CONSTRAINT MISCLOSURE VECTOR *" << std::endl;
		of << "********************************" << std::endl << std::endl;
		
		of << *fCnstrMisclosureVector;
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

