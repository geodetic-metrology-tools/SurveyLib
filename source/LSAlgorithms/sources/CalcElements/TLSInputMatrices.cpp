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
//SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TLSInputMatrices::initMatrices(UEOIndices ueoi)
{//sets the dimensions of the matrices

	fUEOIndices = ueoi;

	fGlobalMisclosureVector = std::make_unique<TVector>(fUEOIndices.EIndex + fUEOIndices.WIndex);

	globalFirstDesignMatrix = std::make_unique<TSparseMatrix>(fUEOIndices.EIndex + fUEOIndices.WIndex, fUEOIndices.UIndex);
	globalSecondDesignMatrix = std::make_unique<TSparseMatrix>(fUEOIndices.EIndex + fUEOIndices.WIndex, fUEOIndices.OIndex + fUEOIndices.WIndex);
	globalSecondDesignBlockDiagInvMatrix = std::make_unique<TSparseMatrix>(fUEOIndices.EIndex + fUEOIndices.WIndex, fUEOIndices.OIndex + fUEOIndices.WIndex);
	globalWeightMatrix = std::make_unique<TSparseMatrix>(fUEOIndices.OIndex + fUEOIndices.WIndex, fUEOIndices.OIndex + fUEOIndices.WIndex);
	globalWeightInvMatrix = std::make_unique<TSparseMatrix>(fUEOIndices.OIndex + fUEOIndices.WIndex, fUEOIndices.OIndex + fUEOIndices.WIndex);

	fCnstrMisclosureVector = std::make_unique<TVector>(fUEOIndices.CIndex);
	fCnstrFirstDesignMtrx = std::make_unique<TSparseMatrix>(fUEOIndices.CIndex, fUEOIndices.UIndex);

}



bool TLSInputMatrices::setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
		TSparseUtils::checkedCoeffRef(*globalFirstDesignMatrix, row, column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}
bool TLSInputMatrices::setWeightUnkMtrxBlock(MatrixIndex startRow, TDenseMatrix block)
{
	if (block.cols() != block.rows())
	{
		throw std::runtime_error("Cannot insert block in weight first design matrix - Block is too big.");
	}
	if ((fUEOIndices.WIndex < startRow + block.rows())||(fUEOIndices.WIndex < startRow + block.cols()))
	{
		throw std::runtime_error("Cannot insert block in weight first design matrix - Block is too big.");
	}

	// set its inverse
	if (!block.fullPivHouseholderQr().isInvertible())
	{
		throw std::runtime_error("Block of weight matrix has to be invertible");
	}
	TDenseMatrix blockInverse = block.fullPivHouseholderQr().inverse();
	for (int row = 0; row < block.rows(); row++)
	{
		for (int col = 0; col < block.cols(); col++)
		{
			setWeightUnkMtrxElement(startRow + row, startRow + col, block(row, col));
			setWeightUnkInvMtrxElement(startRow + row, startRow + col, blockInverse(row, col));
		}
	}



	return true;
}
bool TLSInputMatrices::setWeightsFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
		TSparseUtils::checkedCoeffRef(*globalFirstDesignMatrix, row + fUEOIndices.EIndex, column) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::addFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
		TSparseUtils::checkedCoeffRef(*globalFirstDesignMatrix, row, column) += coeff;
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
				TSparseUtils::checkedCoeffRef(*globalSecondDesignMatrix, firstIndex + row, secondIndex + col) = block(row, col);
			}
		}
		// check if the block is square and if it is located on the diagonal, and if all previous blocks were also block-diag
		if ((block.cols() == block.rows() && firstIndex == secondIndex && secondDesignMatrixIsBlockDiag))
		{
			// compute the inverse of the block and write it at the corresponding place of the inverse
			int dim = block.cols();
			Eigen::MatrixXd block_inverse = block.lu().solve(Eigen::MatrixXd::Identity(block.rows(), block.cols()));
			for (int row = 0; row < dim; row++)
			{
				for (int col = 0; col < dim; col++)
				{
					TSparseUtils::checkedCoeffRef(*globalSecondDesignBlockDiagInvMatrix, firstIndex + row, secondIndex + col) = block_inverse(row, col);
				}
			}
		}
		else
		{
			secondDesignMatrixIsBlockDiag = false;
		}
	}
	catch (const std::exception &e)
	{
		// Setting of second design matrix block failed
		logFatal() << "Error occurred while setting second design matrix: " << e.what();
		return false;
	}

	return true;
}

bool TLSInputMatrices::setSecondDgnMtrxToMinusIdentity()
{
	// set the second design matrix and its inverse to minus identity
	try
	{
		globalSecondDesignMatrix->setIdentity();
		*globalSecondDesignMatrix *= -1.0;
		globalSecondDesignBlockDiagInvMatrix->setIdentity();
		*globalSecondDesignBlockDiagInvMatrix *= -1.0;
		secondDesignMatrixIsBlockDiag = true;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::resetCnstrFirstDgnMtrx(UEOIndices ueoi)
{
	try
	{
		fCnstrFirstDesignMtrx = std::make_unique<TSparseMatrix>(fUEOIndices.CIndex, fUEOIndices.UIndex);
	}
	catch (const std::overflow_error &err)
	{
		logFatal() << "Failed to reset the constraint for the first design matrix, error message: " << err.what() << std::endl;
		return false;
	}
	return true;
}

bool TLSInputMatrices::resetCnstrMisclosureVector(UEOIndices ueoi)
{
	try
	{
		fCnstrMisclosureVector = std::make_unique<TVector>(fUEOIndices.CIndex);
	}
	catch (const std::overflow_error &err)
	{
		logFatal() << "Failed to reset the constraint misclosure vector, error message: " << err.what() << std::endl;
		return false;
	}
	return true;
}

bool TLSInputMatrices::setMisclosureVectorElement(MatrixIndex row, TReal coeff)
{
	try {
		TSparseUtils::checkedCoeffRef(*fGlobalMisclosureVector, row) = coeff;
	} catch(...) {
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightMisclosureVectorElement(MatrixIndex row, TReal coeff)
{
	try {
		TSparseUtils::checkedCoeffRef(*fGlobalMisclosureVector, row + fUEOIndices.EIndex) = coeff;
	} catch(...) {
		return false;
	}
	return true;

}

bool TLSInputMatrices::setWeightMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*globalWeightMatrix, row, column) = coeff;
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting weight matrix: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightInvMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*globalWeightInvMatrix, row, column) = coeff;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightUnkMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*globalWeightMatrix, row + fUEOIndices.OIndex, column + fUEOIndices.OIndex) = coeff;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::setWeightUnkInvMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*globalWeightInvMatrix, row + fUEOIndices.OIndex, column + fUEOIndices.OIndex) = coeff;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*fCnstrFirstDesignMtrx, row, column) = coeff;
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting constraint first design matrix: " << e.what();
		return false;
	}
	return true;
}


bool TLSInputMatrices::addCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*fCnstrFirstDesignMtrx, row, column) += coefficient;
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting constraint first design matrix: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::setCnstrMisclosureVectorElement(MatrixIndex row, TReal coeff)
{
	try
	{
		TSparseUtils::checkedCoeffRef(*fCnstrMisclosureVector, row) = coeff;
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting constraint misclosure: " << e.what();
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//ACCESS METHOD FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

const TSparseMatrix TLSInputMatrices::getSecondDgnMtrx() const noexcept
{//returns a reference to the first dgn matrix
	return globalSecondDesignMatrix.get()->topLeftCorner(fUEOIndices.EIndex, fUEOIndices.OIndex);
}

const TSparseMatrix *TLSInputMatrices::getGlobalSecondDgnMtrx() const noexcept
{
	return globalSecondDesignMatrix.get();
}

bool TLSInputMatrices::getSecondDgnBlockDiagStatus() const
{// returns the private member seconDesignMatrixIsBlockDiag which indicates that B is block diagonal
	return secondDesignMatrixIsBlockDiag;
}
//const TSparseMatrix* TLSInputMatrices::getSecondDgnBlockDiagInvMtrx() const noexcept
//{//returns a reference to the inverse of the second dgn matrix
//	return globalSecondDesignBlockDiagInvMatrix;
//}

const TSparseMatrix *TLSInputMatrices::getGlobalSecondDgnBlockDiagInvMtrx() const noexcept
{
	return globalSecondDesignBlockDiagInvMatrix.get();
}

const TSparseMatrix *TLSInputMatrices::getGlobalWeightMtrx() const noexcept
{
	return globalWeightMatrix.get();
}

const TSparseMatrix *TLSInputMatrices::getGlobalWeightInvMtrx() const noexcept
{
	return globalWeightInvMatrix.get();
}

const TSparseMatrix TLSInputMatrices::getObsWeightMtrx() const noexcept
{
	return (globalWeightMatrix->topLeftCorner(fUEOIndices.OIndex, fUEOIndices.OIndex));
}

const TSparseMatrix TLSInputMatrices::getObsWeightInvMtrx() const noexcept
{
	return (globalWeightInvMatrix->topLeftCorner(fUEOIndices.OIndex, fUEOIndices.OIndex));
}

const TSparseMatrix TLSInputMatrices::getWeightUnkMtrx() const noexcept
{
	return (globalWeightMatrix->bottomRightCorner(fUEOIndices.WIndex, fUEOIndices.WIndex));
}

const TVector TLSInputMatrices::getObsMisclosureVctr() const noexcept
{// returns a copy of the misclosure vector
	return (fGlobalMisclosureVector->topRows(fUEOIndices.EIndex));
}
const TVector TLSInputMatrices::getWeightMisclosureVctr() const noexcept
{// returns a copy of the misclosure vector
	return (fGlobalMisclosureVector->bottomRows(fUEOIndices.WIndex));
}


const TVector &TLSInputMatrices::getGlobalMisclosureVctr() const noexcept
{
	return *fGlobalMisclosureVector;
}


const TSparseMatrix* TLSInputMatrices::getCnstrFirstDgnMtrx() const noexcept
{//returns a reference to the constraint first dgn matrix
	return fCnstrFirstDesignMtrx.get();
}


const TVector& TLSInputMatrices::getCnstrMisclosureVctr() const noexcept
{// returns a reference to the constraint misclosure vector
	return *fCnstrMisclosureVector.get();
}

int TLSInputMatrices::getNbrUnknowns() const
{
	return fUEOIndices.UIndex;
}

int TLSInputMatrices::getNbrEquations() const
{
	return fUEOIndices.EIndex;
}

int TLSInputMatrices::getNbrWeights() const
{
	return fUEOIndices.WIndex;
}

int TLSInputMatrices::getNbrObservations() const
{
	return fUEOIndices.OIndex;
}

int TLSInputMatrices::getNbrConstraints() const
{
	return fUEOIndices.CIndex;
}

const TSparseMatrix *TLSInputMatrices::getGlobalFirstDgnMtrx() const noexcept
{
	return globalFirstDesignMatrix.get();
}

const TSparseMatrix TLSInputMatrices::getObsFirstDgnMtrx() const noexcept
{
	return globalFirstDesignMatrix->topRows(fUEOIndices.EIndex);
}

const TSparseMatrix TLSInputMatrices::getWeightsFirstDgnMtrx() const noexcept
{
	return globalFirstDesignMatrix->bottomRows(fUEOIndices.WIndex);
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
	
	of << getObsFirstDgnMtrx();
	of << std::endl << std::endl;


	of << "*********************" << std::endl;
	of << "* MISCLOSURE VECTOR *" << std::endl;
	of << "*********************" << std::endl << std::endl;

	of << *fGlobalMisclosureVector;
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
	
	of << *globalWeightMatrix;
	of << std::endl << std::endl;



	of << "************************" << std::endl;
	of << "* SECOND DESIGN MATRIX *" << std::endl;
	of << "************************" << std::endl << std::endl;

	of << getSecondDgnMtrx();
	of << std::endl << std::endl;

	of.close();
}


/////////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////////

