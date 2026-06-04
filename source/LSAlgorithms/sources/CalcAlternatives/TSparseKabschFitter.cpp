// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TSparseKabschFitter.cpp : implementation file
// class making an approximative best fit between points
// the class is the minimal required for chaba

#include "TSparseKabschFitter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <Eigen/Dense>

#include "BestFitRotationFns.h"
#include "Logger.hpp"

/////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////
TSparseKabschFitter::TSparseKabschFitter()
{ // Constructor
}

/////////////////////////////////////////////////////////////////////////////////
// MEMBER FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TSparseKabschFitter::initMatrices(int equations, int dimension)
{ // sets the dimensions of the matrices

	fNbDim = dimension;
	fNbEqn = equations;

	clearMatrices();
	
	ActiveMatrix = std::make_unique<TSparseMatrix>(equations, dimension);
	PassiveMatrix = std::make_unique<TSparseMatrix>(equations, dimension);
	ResultRotMatrix = std::make_unique<TRotationMatrix>();
}

void TSparseKabschFitter::clearMatrices()
{
	ActiveMatrix.reset();
	PassiveMatrix.reset();
	ResultRotMatrix.reset();
}

bool TSparseKabschFitter::setActiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		if (0 <= row && row < fNbEqn && 0 <= column && column < fNbDim)
			ActiveMatrix->insert(row, column) = coeff;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TSparseKabschFitter::setPassiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try
	{
		if (0 <= row && row < fNbEqn && 0 <= column && column < fNbDim)
			PassiveMatrix->insert(row, column) = coeff;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TSparseKabschFitter::setRotationMatrix(TDenseMatrix RotationMatrix)
{
	try
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				ResultRotMatrix->setC(row, col, RotationMatrix(row, col));
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool TSparseKabschFitter::computeRotMatrx()
{
	if (!PassiveMatrix || !ActiveMatrix)
		return false;

	const Eigen::Matrix3d H = PassiveMatrix->toDense().transpose() * ActiveMatrix->toDense();
	bool ok = false;
	const Eigen::Matrix3d R = bestFitRotation(H, ok);
	if (!ok)
		return false;
	return setRotationMatrix(R);
}

Angles TSparseKabschFitter::getAngles(TRotationMatrix::ERotationType kR)
{ // calculate the angles from the matrix with the specified rotation order

	Angles xyz;
	xyz = ResultRotMatrix->getAngles(kR);

	return xyz;
}

/////////////////////////////////////////////////////////////////////////////////
// END
/////////////////////////////////////////////////////////////////////////////////
