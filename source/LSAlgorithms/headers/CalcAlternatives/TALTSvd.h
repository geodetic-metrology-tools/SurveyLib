/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TALTSvd
#define SU_TALTSvd

#include <UEOIndices.h>
#include "Quad.h"
#include "TRotationMatrix.h"
#include "TSparseMatrix.h"
#include <memory>

/*!
	\ingroup CalcAlternatives
	\brief Class to solve Svd decomposition, Used to get starting values for a LS equation in point fitting. Minimal implementation of the solution for CHABA Purposes.
*/
class TALTSvd
{
public:
	/*!@name Constructors / Destructor*/
	//@{
		//! Constructor
		TALTSvd();

		//! Destructor --> Default
	//@}

	/**@name Member Functions */
	//@{
		/*! \brief Sets the dimensions of the matrices
			\param[in] nbDim the number of dimension of the points, typically 3
			\param[in] nbEquations the survey network's number of equations
		*/
		void initMatrices(int equations, int dimension);

		/*!	\brief Set the value of an element of the ActivePoint - barrycenter matrix
		\param[in] row of the desired element
		\param[in] column of the desired element
		\param[in] coefficient: value of the desired element
		*/
		bool setActiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of an element of the PassivePoint - barycenter matrix
		\param[in] row of the desired element
		\param[in] column of the desired element
		\param[in] coefficient: value of the desired element
		*/
		bool setPassiveMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the Rotation Matrix elements */
		bool setRotationMtrxElement(TDenseMatrix RotationMatrix);

		/*!	\Verify the number of unknowns and run the calculation */
		bool computeRotMatrx();

		/*!	\ calculate the angles from the matrix with the specified rotation order */
		struct Angles getAngles(TRotationMatrix::ERotationType kR);
	//@}

private:
		std::unique_ptr<TSparseMatrix> ActiveMatrix = nullptr; /*!< matrix A (eq x ndim) */
		std::unique_ptr<TSparseMatrix> PassiveMatrix = nullptr; /*!< matrix B (eq x ndim) */

		std::unique_ptr<TRotationMatrix> ResultRotMatrix = nullptr;
	
		MatrixIndex fNbDim = 0; /*!< d : number of dimensions, usually 3 */
		MatrixIndex fNbEqn = 0; /*!< e : number of equations */

	void clearMatrices();
};

#endif
