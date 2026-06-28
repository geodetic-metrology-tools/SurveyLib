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
		// write the block
		for (int row = 0; row < dimBlock; row++)
		{
			for (int col = 0; col < dimBlock; col++)
			{
				weightMatrix->addTriplet(index + row, index + col, block(row, col));
			}
		}
		// compute the inverse of the block and write it at the corresponding place of the inverse
		Eigen::MatrixXd blockInverse = block.inverse();
		for (int row = 0; row < dimBlock; row++)
		{
			for (int col = 0; col < dimBlock; col++)
			{
				weightInvMatrix->addTriplet(index + row, index + col, blockInverse(row, col));
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
const TSparseMatrix &TLSInputMatrices::getFirstDgnMtrx(bool masked) const
{ // first design matrix A (e x u): mask equation rows and parameter columns
	if (!masked)
		return firstDesignMatrix->getMatrix();
	fMaskedFirstDgn = maskParCols(maskEqnRows(firstDesignMatrix->getMatrix()));
	return fMaskedFirstDgn;
}

const TSparseMatrix &TLSInputMatrices::getSecondDgnMtrx(bool masked) const
{ // second design matrix B (e x o): mask equation rows and observation columns
	if (!masked)
		return secondDesignMatrix->getMatrix();
	fMaskedSecondDgn = maskObsCols(maskEqnRows(secondDesignMatrix->getMatrix()));
	return fMaskedSecondDgn;
}

bool TLSInputMatrices::getSecondDgnBlockDiagStatus() const
{ // returns the private member secondDesignMatrixIsBlockDiag which indicates that B is block diagonal
	return secondDesignMatrixIsBlockDiag;
}
const TSparseMatrix &TLSInputMatrices::getSecondDgnBlockDiagInvMtrx(bool masked) const
{ // inverse second design matrix invB: mask observation rows and columns
	if (!masked)
		return secondDesignBlockDiagInvMatrix->getMatrix();
	fMaskedSecondDgnInv = maskObsColsAndRows(secondDesignBlockDiagInvMatrix->getMatrix());
	return fMaskedSecondDgnInv;
}

const TSparseMatrix &TLSInputMatrices::getWeightMtrx(bool masked) const
{ // observation weight matrix P (o x o): mask observation rows and columns
	if (!masked)
		return weightMatrix->getMatrix();
	fMaskedWeight = maskObsColsAndRows(weightMatrix->getMatrix());
	return fMaskedWeight;
}

const TSparseMatrix &TLSInputMatrices::getWeightInvMtrx(bool masked) const
{ // inverse observation weight matrix invP (o x o): mask observation rows and columns
	if (!masked)
		return weightInvMatrix->getMatrix();
	fMaskedWeightInv = maskObsColsAndRows(weightInvMatrix->getMatrix());
	return fMaskedWeightInv;
}

const TSparseMatrix &TLSInputMatrices::getWeightUnkMtrx() const
{
	return weightUnkMatrix->getMatrix();
}

const TVector &TLSInputMatrices::getMisclosureVctr(bool masked) const
{ // misclosure vector W (e): mask equation rows
	if (!masked)
		return *fMisclosureVector.get();
	fMaskedMisclosure = getEqnMask() * (*fMisclosureVector.get());
	return fMaskedMisclosure;
}

const TSparseMatrix &TLSInputMatrices::getCnstrFirstDgnMtrx(bool masked) const
{ // constraint first design matrix A2 (c x u): mask parameter columns
	if (!masked)
		return fCnstrFirstDesignMtrx->getMatrix();
	fMaskedCnstrFirstDgn = maskParCols(fCnstrFirstDesignMtrx->getMatrix());
	return fMaskedCnstrFirstDgn;
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

int TLSInputMatrices::getNbrUnknowns(bool masked) const
{
	return fUEOIndices.UIndex - (masked ? static_cast<int>(fMaskData.PIndices.size()) : 0);
}

int TLSInputMatrices::getNbrEquations(bool masked) const
{
	return fUEOIndices.EIndex - (masked ? static_cast<int>(fMaskData.EIndices.size()) : 0);
}

int TLSInputMatrices::getNbrObservations(bool masked) const
{
	return fUEOIndices.OIndex - (masked ? static_cast<int>(fMaskData.OIndices.size()) : 0);
}

int TLSInputMatrices::getNbrConstraints() const
{
	return fUEOIndices.CIndex;
}

bool TLSInputMatrices::hasMask() const
{
	return !fMaskData.EIndices.empty() || !fMaskData.OIndices.empty() || !fMaskData.PIndices.empty();
}

TSparseMatrix TLSInputMatrices::getObsMask() const
{
	std::vector<int> actInd = getActiveObsIndices();
	int nActive = actInd.size();
	TSparseMatrix rightFactor(fUEOIndices.OIndex, nActive);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(nActive);

	for (int colIdx = 0; colIdx < nActive; colIdx++)
	{
		coeffs.push_back(TTriplet(actInd.at(colIdx), colIdx, 1));
	}
	rightFactor.setFromTriplets(coeffs.begin(), coeffs.end());
	return rightFactor;
}

TSparseMatrix TLSInputMatrices::getParMask() const
{
	std::vector<int> actInd = getActiveParIndices();
	int nActive = actInd.size();
	TSparseMatrix rightFactor(fUEOIndices.UIndex, nActive);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(nActive);

	for (int colIdx = 0; colIdx < nActive; colIdx++)
	{
		coeffs.push_back(TTriplet(actInd.at(colIdx), colIdx, 1));
	}
	rightFactor.setFromTriplets(coeffs.begin(), coeffs.end());
	return rightFactor;
}

TSparseMatrix TLSInputMatrices::getEqnMask() const
{
	std::vector<int> actInd = getActiveEqnIndices();
	int nActive = actInd.size();
	TSparseMatrix leftFactor(nActive, fUEOIndices.EIndex);
	std::vector<TTriplet> coeffs;
	coeffs.reserve(nActive);

	for (int rowIdx = 0; rowIdx < nActive; rowIdx++)
	{
		coeffs.push_back(TTriplet(rowIdx, actInd.at(rowIdx), 1));
	}
	leftFactor.setFromTriplets(coeffs.begin(), coeffs.end());

	return leftFactor;
}

TSparseMatrix TLSInputMatrices::maskEqnRows(const TSparseMatrix &mat) const
{
	// Nothing masked: the equation mask is the identity, so skip building it and the product.
	if (fMaskData.EIndices.empty())
		return mat;
	return getEqnMask() * (mat);
}

TSparseMatrix TLSInputMatrices::maskObsCols(const TSparseMatrix &mat) const
{
	if (fMaskData.OIndices.empty())
		return mat;
	return (mat) * getObsMask();
}

TSparseMatrix TLSInputMatrices::maskParCols(const TSparseMatrix &mat) const
{
	if (fMaskData.PIndices.empty())
		return mat;
	return (mat) * getParMask();
}

TSparseMatrix TLSInputMatrices::maskObsColsAndRows(const TSparseMatrix &mat) const
{
	if (fMaskData.OIndices.empty())
		return mat;
	return getObsMask().transpose() * (mat) * getObsMask();
}

std::vector<int> TLSInputMatrices::getActiveEqnIndices() const
{
	std::vector<int> ind;
	for (int j = 0; j < fUEOIndices.EIndex; j++)
	{
		if (fMaskData.EIndices.find(j) != fMaskData.EIndices.end())
		{
			// index is masked
		}
		else
		{
			// its active
			ind.push_back(j);
		}
	}

	return ind;
}
std::vector<int> TLSInputMatrices::getActiveObsIndices() const
{
	std::vector<int> ind;
	for (int j = 0; j < fUEOIndices.OIndex; j++)
	{
		if (fMaskData.OIndices.find(j) != fMaskData.OIndices.end())
		{
			// index is masked
		}
		else
		{
			// its active
			ind.push_back(j);
		}
	}

	return ind;
}

std::vector<int> TLSInputMatrices::getActiveParIndices() const
{
	std::vector<int> ind;
	for (int j = 0; j < fUEOIndices.UIndex; j++)
	{
		if (fMaskData.PIndices.find(j) != fMaskData.PIndices.end())
		{
			// index is masked
		}
		else
		{
			// its active
			ind.push_back(j);
		}
	}

	return ind;
}

TVector TLSInputMatrices::blowUpParameters(const TVector &reduced) const
{
	if (fMaskData.PIndices.empty())
		return reduced;
	// reduced is defined on the active parameters; scatter it back to the full size,
	// leaving zeros at the masked parameters.
	TVector full(fUEOIndices.UIndex);
	full.setZero();
	full(getActiveParIndices()) = reduced;
	return full;
}

TVector TLSInputMatrices::blowUpResiduals(const TVector &reduced) const
{
	if (fMaskData.OIndices.empty())
		return reduced;
	// reduced is defined on the active observations; masked observations get residual 0.
	TVector full(fUEOIndices.OIndex);
	full.setZero();
	full(getActiveObsIndices()) = reduced;
	return full;
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
