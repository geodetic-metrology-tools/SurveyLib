/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLSINPUTMATRICES
#define SU_TLSINPUTMATRICES

#include "TSparseMatrix.h"
#include <UEOIndices.h>
#include "Quad.h"


/*!
	\ingroup CalcElements

	\brief Class for the input matrices used in the LS-calculation.
*/
class TLSInputMatrices{

public:

	/*!@name Constructors / Destructor*/
	//@{
		//!Constructor
		TLSInputMatrices();
		//!Destructor
		~TLSInputMatrices();
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
		void initMatrices(int unknowns, int equations, int observations, int nbCnstrObs, int nbCnstrUnk = 0);
	

		/*!	\brief Set the value of an element of the first design matrix in the adjustment (A-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of an element of the second design matrix in the adjustment (B-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setSecondDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of a misclosure vector (W or "Fermetures" vector)
			\param[in] row of the desired element
			\param[in] coeff: value of the desired misclosure
		*/
		bool setSecondDgnMtrxBlock(MatrixIndex first_index, Eigen::MatrixXd block);

		/*!	\brief Set a block in the second design matrix. Each block corresponds to one mathematical observation equation. Also sets the inverse block.
		*/
		bool setMisclosureVectorElement(MatrixIndex row, TReal coeff);

		/*!	\brief Set the value of an element of the observations weight matrix in the adjustment (P-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setWeightMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of an element of the inverted osbservations weight matrix in the adjustment (invP-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setWeightInvMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of an element of the parameters (i.e. unknowns) weight matrix in the adjustment (Pxx-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setWeightUnkMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of an element of the constraints first design matrix (A2-submatrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set the value of an element of the constraints misclosure vector (W2-submatrix)
			\param[in] row of the desired element
			\param[in] coeff: value of the desired element
		*/
		bool setCnstrMisclosureVectorElement(MatrixIndex row, TReal coeff);
	//@}


	/*!@name Getting methods*/
	//@{
		/*!	\brief Returns the number of unknowns */
		int	getNbrUnknowns() const;

		/*!	\brief Returns the number of observations */
		int	getNbrObservations() const;

		/*!	\brief Returns the number of equations */
		int	getNbrEquations()const;

		/*!	\brief Returns the number of observations constraints */
		int	getNbrConstraintObs()const;

		/*!	\brief Returns the number of parameters constraints */
		int	getNbrConstraints()const;
		
		/*!	\brief Returns a const reference (pointer) to the first design matrix allocated here*/
		const TSparseMatrix* getFirstDgnMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the second design matrix allocated here*/
		const TSparseMatrix* getSecondDgnMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the inverse second design matrix allocated here*/
		const TSparseMatrix* getSecondDgnInvMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the weight matrix allocated here*/
		const TSparseMatrix* getWeightMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the inverted weight matrix allocated here*/
		const TSparseMatrix* getWeightInvMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the parameters-weight matrix allocated here*/
		const TSparseMatrix* getWeightUnkMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the misclosure vector allocated here*/
		const TVector&	getMisclosureVctr() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the constraints first design submatrix allocated here*/
		const TSparseMatrix* getCnstrFirstDgnMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the constraints misclosure subvector allocated here*/
		const TVector&	getCnstrMisclosureVctr() const noexcept;
	//@}


	/// Debug method
	void saveMatricesToFile(int nbIter) const;

private:

	MatrixIndex		fNbUnk;      /*!< u : number of unknowns */
	MatrixIndex		fNbObs;      /*!< o : number of observations */
	MatrixIndex		fNbEqn;      /*!< e : number of equations */
	int				fNbCnstrObs; /*!< number of constraint observations */
	MatrixIndex		fNbCnstr;    /*!< c : number of constraints on parameters */

	TVector*		fMisclosureVector;  /*!< vector (o x 1) for misclosure errors */

	TSparseMatrix*	fCnstrFirstDesignMtrx;  /*!< matrix A2 (c x u) for constraints first design submatrix*/
	TVector*		fCnstrMisclosureVector; /*!< vector W2 (c x 1) for constraints misclosure subvector */

	TSparseMatrix*	firstDesignMatrix;  /*!< matrix A (e x u) */
	TSparseMatrix*	secondDesignMatrix; /*!< matrix B (e x o) */
	TSparseMatrix*	secondDesignInvMatrix; /*!< matrix B^-1 (e x o) */
	TSparseMatrix*	weightMatrix;       /*!< matrix P (o x o) for observations weights */
	TSparseMatrix*	weightInvMatrix;    /*!< matrix invP (o x o) for observations weights */
	TSparseMatrix*	weightUnkMatrix;    /*!< matrix Pxx (u x u) for unknowns weights */

	void clearMatrices();
};


#endif
