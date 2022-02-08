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
#include "TALTSvd.h"
#include <Eigen/SVD>
#include <Eigen/Dense>

#include "TRotationMatrix.h"

/////////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////////////
TALTSvd::TALTSvd()
{//Constructor
	ActiveMatrix = nullptr; /*!< matrix A (3 x eq) */
	PassiveMatrix = nullptr; /*!< matrix B (3 x eq) */
	ResultRotMatrix.identity();

	fNbDim = 0;
	fNbEqn = 0;
}


TALTSvd::~TALTSvd()
{//Destructor
	clearMatrices();
}



/////////////////////////////////////////////////////////////////////////////////
//SET FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////

void TALTSvd::initMatrices(int equations, int dimension )
{//sets the dimensions of the matrices

	fNbDim = dimension;
	fNbEqn = equations;

	clearMatrices();

	ActiveMatrix = new TSparseMatrix(equations, dimension);
	PassiveMatrix = new TSparseMatrix(equations, dimension);
	ResultRotMatrix.identity();

}

void TALTSvd::clearMatrices()
{
	if (ActiveMatrix != nullptr) {
		delete ActiveMatrix;
		ActiveMatrix = nullptr;
	}
	if (PassiveMatrix != nullptr) {
		delete PassiveMatrix;
		PassiveMatrix = nullptr;
	}
}


bool TALTSvd::setActiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
		if (0 <= row && row < fNbEqn && 0 <= column && column < fNbDim)
			ActiveMatrix->insert(row, column) = coeff;
	}
	catch (...) {
		return false;
	}
	return true;
}


bool TALTSvd::setPassiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coeff)
{
	try {
		if (0 <= row && row < fNbEqn && 0 <= column && column < fNbDim)
			PassiveMatrix->insert(row, column) = coeff;
	}
	catch (...) {
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
				ResultRotMatrix.setC(row, col, RotationMatrix(row, col));
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
		Eigen::JacobiSVD<TDenseMatrix> svd(PassiveMatrix->toDense().transpose() * ActiveMatrix->toDense(), Eigen::ComputeFullU | Eigen::ComputeFullV);

		TDenseMatrix u = svd.matrixU();
		TDenseMatrix v = svd.matrixV();

		// Compute R = V * U'
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
	xyz = ResultRotMatrix.getAngles(kR);

	return xyz;
}
