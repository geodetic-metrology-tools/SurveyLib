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
	secondDesignBlockDiagInvMatrix = nullptr;
	weightMatrix = nullptr;
	weightInvMatrix = nullptr;
	weightUnkMatrix = nullptr;
	fCnstrFirstDesignMtrx = nullptr;
	
	fMisclosureVector = nullptr;
	fCnstrMisclosureVector = nullptr;

}


TLSInputMatrices::~TLSInputMatrices()
{//Destructor
	clearMatrices();
}



/////////////////////////////////////////////////////////////////////////////////
//SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TLSInputMatrices::initMatrices(UEOIndices ueoi)
{//sets the dimensions of the matrices

	fUEOIndices = ueoi;

	clearMatrices();
	fMisclosureVector = new TVector(fUEOIndices.EIndex);

	firstDesignMatrix = new TSparseMatrix(fUEOIndices.EIndex, fUEOIndices.UIndex);
	secondDesignMatrix = new TSparseMatrix(fUEOIndices.EIndex, fUEOIndices.OIndex);
	secondDesignBlockDiagInvMatrix = new TSparseMatrix(fUEOIndices.EIndex, fUEOIndices.OIndex);
	weightMatrix = new TSparseMatrix(fUEOIndices.OIndex, fUEOIndices.OIndex);
	weightInvMatrix = new TSparseMatrix(fUEOIndices.OIndex, fUEOIndices.OIndex);
	weightUnkMatrix = new TSparseMatrix(fUEOIndices.UIndex, fUEOIndices.UIndex);

	fCnstrMisclosureVector = new TVector(fUEOIndices.CIndex);
	fCnstrFirstDesignMtrx = new TSparseMatrix(fUEOIndices.CIndex, fUEOIndices.UIndex);

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
	if (secondDesignBlockDiagInvMatrix != nullptr) {
		delete secondDesignBlockDiagInvMatrix;
		secondDesignBlockDiagInvMatrix = nullptr;
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
	if (0 <= row && row < fUEOIndices.EIndex && 0 <= column && column < fUEOIndices.UIndex)
		firstDesignMatrix->coeffRef(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::addFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fUEOIndices.EIndex && 0 <= column && column < fUEOIndices.UIndex)
		firstDesignMatrix->coeffRef(row,column) += coeff;
	} catch(...) {
		return false;
	}
	return true;
}


bool TLSInputMatrices::setSecondDgnMtrxBlock(MatrixIndex firstIndex, MatrixIndex secondIndex, Eigen::MatrixXd block)
{
	try
	{
		// write the block
		for (int row = 0; row < block.rows(); row++)
		{
			for (int col = 0; col < block.cols(); col++)
			{
				secondDesignMatrix->insert(firstIndex + row, secondIndex + col) = block(row, col);
			}
		}
		// check if the block is square and if it is located on the diagonal, and if all previous blocks were also block-diag
		if ((block.cols() == block.rows() && firstIndex == secondIndex && seconDesignMatrixIsBlockDiag))
		{
			// compute the inverse of the block and write it at the corresponding place of the inverse
			int dim = block.cols();
			Eigen::MatrixXd block_inverse = block.lu().solve(Eigen::MatrixXd::Identity(block.rows(), block.cols()));
			for (int row = 0; row < dim; row++)
			{
				for (int col = 0; col < dim; col++)
				{
					secondDesignBlockDiagInvMatrix->insert(firstIndex + row, secondIndex + col) = block_inverse(row, col);
				}
			}
		}
		else
		{
			seconDesignMatrixIsBlockDiag = false;
			delete secondDesignBlockDiagInvMatrix;
			secondDesignBlockDiagInvMatrix = nullptr;
		}
	}
	catch (...)
	{
		// Setting of second design matrix block failed
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
	if (0 <= row && row < fUEOIndices.OIndex && 0 <= column && column < fUEOIndices.OIndex){
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
	if (0 <= row && row < fUEOIndices.OIndex && 0 <= column && column < fUEOIndices.OIndex)
		weightInvMatrix->insert(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightUnkMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fUEOIndices.UIndex && 0 <= column && column < fUEOIndices.UIndex)
		weightUnkMatrix->insert(row,column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
	if (0 <= row && row < fUEOIndices.CIndex && 0 <= column && column < fUEOIndices.UIndex)
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

bool TLSInputMatrices::getSecondDgnBlockDiagStatus() const
{// returns the private member seconDesignMatrixIsBlockDiag which indicates that B is block diagonal
	return seconDesignMatrixIsBlockDiag;
}
const TSparseMatrix* TLSInputMatrices::getSecondDgnBlockDiagInvMtrx() const noexcept
{//returns a reference to the inverse of the second dgn matrix
	return secondDesignBlockDiagInvMatrix;
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
	return fUEOIndices.UIndex;
}

int TLSInputMatrices::getNbrEquations() const
{
	return fUEOIndices.EIndex;
}

int TLSInputMatrices::getNbrObservations() const
{
	return fUEOIndices.OIndex;
}

int TLSInputMatrices::getNbrConstraints() const
{
	return fUEOIndices.CIndex;
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

	of << "Number of Unknowns : " << fUEOIndices.UIndex << std::endl;
	of << "Number of Observations : " << fUEOIndices.OIndex << std::endl;
	of << "Number of Equations : " << fUEOIndices.EIndex << std::endl << std::endl;

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

