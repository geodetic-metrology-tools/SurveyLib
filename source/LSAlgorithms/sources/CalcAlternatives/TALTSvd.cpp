// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TALTSvd.h : implementation file
// class making an approximative best fit between points
// the class is the minimal required for chaba

#include "TALTSvd.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <Eigen/Dense>
#include <Eigen/SVD>

#include "Logger.hpp"

/////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////
TALTSvd::TALTSvd()
{ // Constructor
}

/////////////////////////////////////////////////////////////////////////////////
// MEMBER FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TALTSvd::initMatrices(int equations, int dimension)
{ // sets the dimensions of the matrices

	fNbDim = dimension;
	fNbEqn = equations;

	clearMatrices();
	
	ActiveMatrix = std::make_unique<TSparseMatrix>(equations, dimension);
	PassiveMatrix = std::make_unique<TSparseMatrix>(equations, dimension);
	ResultRotMatrix = std::make_unique<TRotationMatrix>();
}

void TALTSvd::clearMatrices()
{
	ActiveMatrix.reset();
	PassiveMatrix.reset();
	ResultRotMatrix.reset();
}

bool TALTSvd::setActiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
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

bool TALTSvd::setPassiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
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

bool TALTSvd::setRotationMtrxElement(TDenseMatrix RotationMatrix)
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

bool TALTSvd::computeRotMatrx()
{
	try
	{
		// Make a SVD decomposition and extract the U and V matrices
		Eigen::JacobiSVD<TDenseMatrix> svd(PassiveMatrix->toDense().transpose() * ActiveMatrix->toDense(), Eigen::ComputeFullU | Eigen::ComputeFullV);

		TDenseMatrix u = svd.matrixU();
		TDenseMatrix v = svd.matrixV();

		// Compute R = V * U'

		// if det(U) * det(V) <0 the third column should be *-1
		if (u.determinant() * v.determinant() < 0)
		{
			for (int row = 0; row < 3; row++)
			{
				v(row, 2) *= -1;
			}
		}
		setRotationMtrxElement(v * u.transpose());
	}
	catch (...)
	{
		return false;
	}
	return true;
}

Angles TALTSvd::getAngles(TRotationMatrix::ERotationType kR)
{ // calculate the angles from the matrix with the specified rotation order

	Angles xyz;
	xyz = ResultRotMatrix->getAngles(kR);

	return xyz;
}

/////////////////////////////////////////////////////////////////////////////////
// END
/////////////////////////////////////////////////////////////////////////////////
