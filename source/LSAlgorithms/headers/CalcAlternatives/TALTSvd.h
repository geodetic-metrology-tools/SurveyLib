/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TALTSvd
#define SU_TALTSvd

#include "TSparseMatrix.h"
#include <UEOIndices.h>
#include "Quad.h"
#include  "TRotationMatrix.h"



/*!
	\ingroup CalcAlternatives

	\brief Class to solve Svd decomposition, Used to get starting values for a LS equation in point fitting
*/
class TALTSvd {

public:

	/*!@name Constructors / Destructor*/
	//@{
		//!Constructor
	TALTSvd();
	//!Destructor
	~TALTSvd();
	//@}


	/*!@name Setting methods*/
	//@{
		/*! \brief Sets the dimensions of the matrices
			\param[in] nbUnknowns the survey network's number of unknowns
			\param[in] nbEquations the survey network's number of equations
			\param[in] nbObservations the survey network's number of observations
			\param[in] nbConstraints the free survey network's number of observation constraints
			\param[in] constraints the free survey network's number of constraints
		*/
	void initMatrices(int equations, int dimension);

	/*!	\brief Set the value of an element of the first design matrix in the adjustment (A-matrix)
	\param[in] row of the desired element
	\param[in] column of the desired element
	\param[in] coefficient: value of the desired element
*/
	bool setActiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

	/*!	\brief Set the value of an element of the second design matrix in the adjustment (B-matrix)
		\param[in] row of the desired element
		\param[in] column of the desired element
		\param[in] coefficient: value of the desired element
	*/
	bool setPassiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

	///Verify the number of unknowns and run the calculation
	bool computeRotMatrx();

	bool setRotationMtrxElement(TDenseMatrix RotationMatrix);

	struct Angles getAngles(TRotationMatrix::ERotationType kR);


private:
	TSparseMatrix* ActiveMatrix; /*!< matrix A (3 x eq) */
	TSparseMatrix* PassiveMatrix; /*!< matrix B (3 x eq) */

	TRotationMatrix ResultRotMatrix;

	MatrixIndex		fNbDim;      /*!< u : number of unknowns */
	MatrixIndex		fNbEqn;      /*!< e : number of equations */




	//TMatrixDouble* Rot;

	void clearMatrices();
};

#endif
