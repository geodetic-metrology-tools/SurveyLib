// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*SURVEYLIB VERSION !!!!!!!!!!!!!!!!!!!!!!!*/

// TLSInputMatrices.h : implementation file
//  class for input matrices as defined for survey purposes
//  and for the least squares solving algorithm
#include "TLSInputMatrices.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <Eigen/Dense>

#include "Logger.hpp"

/////////////////////////////////////////////////////////////////////////////////
// SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TLSInputMatrices::initMatrices(UEOIndices ueoi)
{ // sets the dimensions of the matrices

	fUEOIndices = ueoi;

	firstDesignMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.EIndex, fUEOIndices.UIndex);
	secondDesignMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.EIndex, fUEOIndices.OIndex);
	secondDesignBlockDiagInvMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.OIndex, fUEOIndices.EIndex);
	fCnstrFirstDesignMtrx = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.CIndex, fUEOIndices.UIndex);
	weightMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.OIndex, fUEOIndices.OIndex);
	weightInvMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.OIndex, fUEOIndices.OIndex);
	weightUnkMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.UIndex, fUEOIndices.UIndex);

	fMisclosureVector = std::make_unique<TVector>(fUEOIndices.EIndex);
	fCnstrMisclosureVector = std::make_unique<TVector>(fUEOIndices.CIndex);

	isInitialized = true;
}

bool TLSInputMatrices::addFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		firstDesignMatrix->addTriplet(row, column, coeff);
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting first design matrix: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::addSecondDgnMtrxBlock(MatrixIndex firstIndex, MatrixIndex secondIndex, const Eigen::MatrixXd &block)
{
	try
	{
		// write the block
		for (int row = 0; row < block.rows(); row++)
		{
			for (int col = 0; col < block.cols(); col++)
			{
				secondDesignMatrix->addTriplet(firstIndex + row, secondIndex + col, block(row, col));
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
					secondDesignBlockDiagInvMatrix->addTriplet(firstIndex + row, secondIndex + col, block_inverse(row, col));
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
		secondDesignMatrix->clearTriplets();
		secondDesignBlockDiagInvMatrix->clearTriplets();
		for (int row = 0; row < fUEOIndices.EIndex; row++)
		{
			secondDesignMatrix->addTriplet(row, row, -1.0);
			secondDesignBlockDiagInvMatrix->addTriplet(row, row, -1.0);
		}
		secondDesignMatrixIsBlockDiag = true;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::resetFirstDgnMtrx()
{
	try
	{
		firstDesignMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.EIndex, fUEOIndices.UIndex);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::resetSecondDgnMtrx()
{
	try
	{
		secondDesignMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.EIndex, fUEOIndices.OIndex);
		secondDesignBlockDiagInvMatrix = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.OIndex, fUEOIndices.EIndex);
		secondDesignMatrixIsBlockDiag = true;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TLSInputMatrices::resetCnstrFirstDgnMtrx()
{
	try
	{
		fCnstrFirstDesignMtrx = std::make_unique<TSparseMatrixWithTriplets>(fUEOIndices.CIndex, fUEOIndices.UIndex);
	}
	catch (const std::overflow_error &err)
	{
		logFatal() << "Failed to reset the constraint for the first design matrix, error message: " << err.what() << std::endl;
		return false;
	}
	return true;
}

bool TLSInputMatrices::resetCnstrMisclosureVector()
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
	try
	{
		TSparseUtils::checkedCoeffRef(*fMisclosureVector, row) = coeff;
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting misclosure vector: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::addWeightMtrxBlock(MatrixIndex index, const Eigen::MatrixXd &block)
{
	try
	{
		// check if the block is square
		if (block.cols() != block.rows())
		{
			throw std::runtime_error("To use the setWeightMtrxBlock method, the block needs to be square.");
		}
		int dimBlock = block.cols();
		// check if the block fits in the weight matrix
		if (dimBlock + index > fUEOIndices.OIndex)
		{
			throw std::runtime_error("The setWeightMtrxBlock attempts to set a block in the weight matrix that is too big.");
		}
		// write the block, avoid explicit zeros
		for (int row = 0; row < dimBlock; row++)
		{
			for (int col = 0; col < dimBlock; col++)
			{
				double value = block(row, col);
				if (notZero(value))
				{
					weightMatrix->addTriplet(index + row, index + col, value);
				}
			}
		}
		// compute the inverse of the block and write it at the corresponding place of the inverse
		Eigen::MatrixXd blockInverse = block.inverse();
		for (int row = 0; row < dimBlock; row++)
		{
			for (int col = 0; col < dimBlock; col++)
			{
				double value = blockInverse(row, col);
				if (notZero(value))
				{
					weightInvMatrix->addTriplet(index + row, index + col, value);
				}
			}
		}
	}
	catch (const std::exception &e)
	{
		// Setting of weight matrix block failed
		logFatal() << "Error occurred while setting weight matrix block: " << e.what();
		return false;
	}

	return true;
}

bool TLSInputMatrices::addWeightMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		weightMatrix->addTriplet(row, column, coeff);
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting weight matrix: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::addWeightInvMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		weightInvMatrix->addTriplet(row, column, coeff);
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting weight inverse matrix: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::addWeightUnkMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		weightUnkMatrix->addTriplet(row, column, coeff);
	}
	catch (const std::exception &e)
	{
		logFatal() << "Error occurred while setting unknown weight matrix: " << e.what();
		return false;
	}
	return true;
}

bool TLSInputMatrices::addCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		fCnstrFirstDesignMtrx->addTriplet(row, column, coeff);
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
// ACCESS METHOD FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
const TSparseMatrix &TLSInputMatrices::getFirstDgnMtrx() const
{ // returns a reference to the first dgn matrix
	return firstDesignMatrix->getMatrix();
}

const TSparseMatrix &TLSInputMatrices::getSecondDgnMtrx() const
{ // returns a reference to the first dgn matrix
	return secondDesignMatrix->getMatrix();
}

bool TLSInputMatrices::getSecondDgnBlockDiagStatus() const
{ // returns the private member secondDesignMatrixIsBlockDiag which indicates that B is block diagonal
	return secondDesignMatrixIsBlockDiag;
}
const TSparseMatrix &TLSInputMatrices::getSecondDgnBlockDiagInvMtrx() const
{ // returns a reference to the inverse of the second dgn matrix
	return secondDesignBlockDiagInvMatrix->getMatrix();
}

const TSparseMatrix &TLSInputMatrices::getWeightMtrx() const
{
	return weightMatrix->getMatrix();
}

const TSparseMatrix &TLSInputMatrices::getWeightInvMtrx() const
{
	return weightInvMatrix->getMatrix();
}

const TSparseMatrix &TLSInputMatrices::getWeightUnkMtrx() const
{
	return weightUnkMatrix->getMatrix();
}

const TVector &TLSInputMatrices::getMisclosureVctr() const noexcept
{ // returns a reference to the misclosure vector
	return *fMisclosureVector.get();
}

const TSparseMatrix &TLSInputMatrices::getCnstrFirstDgnMtrx() const
{ // returns a reference to the constraint first dgn matrix
	return fCnstrFirstDesignMtrx->getMatrix();
}

const TVector &TLSInputMatrices::getCnstrMisclosureVctr() const noexcept
{ // returns a reference to the constraint misclosure vector
	return *fCnstrMisclosureVector.get();
}

bool TLSInputMatrices::hasDegenerateConstraints() const
{
	return fCnstrFirstDesignMtrx->hasEmptyRows();
}

void TLSInputMatrices::finalizeMatrices()
{
	fCnstrFirstDesignMtrx->finalize();
	firstDesignMatrix->finalize();
	secondDesignMatrix->finalize();
	secondDesignBlockDiagInvMatrix->finalize();
	weightInvMatrix->finalize();
	weightMatrix->finalize();
	weightUnkMatrix->finalize();
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
// DEBUG METHOD : saves the content of the matrices to a text file
///////////////////////////////////////////////////////////////////////////////
void TLSInputMatrices::saveMatricesToFile(int nbIter) const
{
	// TODO: fix
	std::ostringstream oss;
	oss << "C:\\temp\\inputMatrices" << nbIter << ".txt";
	std::string fileName = oss.str();

	std::ofstream of(fileName.c_str(), std::ios::out);
	if (!of)
	{
		std::cerr << "Impossible d'ouvrir le fichier C:\\temp\\inputMatrices.txt" << '\n';
		std::exit(1);
	}

	of << std::setprecision(9);

	of << "Number of Unknowns : " << fUEOIndices.UIndex << std::endl;
	of << "Number of Observations : " << fUEOIndices.OIndex << std::endl;
	of << "Number of Equations : " << fUEOIndices.EIndex << std::endl << std::endl;

	of << "***********************" << std::endl;
	of << "* FIRST DESIGN MATRIX *" << std::endl;
	of << "***********************" << std::endl << std::endl;

	of << firstDesignMatrix->getMatrix();
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

		of << fCnstrFirstDesignMtrx->getMatrix();
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

	of << weightMatrix->getMatrix();
	of << std::endl << std::endl;

	of << "************************" << std::endl;
	of << "* SECOND DESIGN MATRIX *" << std::endl;
	of << "************************" << std::endl << std::endl;

	of << secondDesignMatrix->getMatrix();
	of << std::endl << std::endl;

	of.close();
}

/////////////////////////////////////////////////////////////////////////////////
// END
/////////////////////////////////////////////////////////////////////////////////
