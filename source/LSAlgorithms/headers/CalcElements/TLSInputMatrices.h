/*
© Copyright CERN 2000-2024. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLSINPUTMATRICES
#define SU_TLSINPUTMATRICES

#include "TSparseMatrix.h"
#include "UEOIndices.h"
#include "Quad.h"
#include <memory>


/*!
	\ingroup CalcElements

	\brief Class for the input matrices used in the LS-calculation.
*/
class TLSInputMatrices{

public:

	/*!@name Constructors / Destructor*/
	//@{
	//! Constructor
	TLSInputMatrices() = default;
	//! Destructor
	~TLSInputMatrices() = default;
	//@}


	/*!@name Setting methods*/
	//@{
		/*! \brief Sets the dimensions of the matrices
			\param[in] ueoindices struct with number of unknowns, equations, observations and constraints
		*/
		void initMatrices(UEOIndices ueoindices);

		/*!	\brief Set the value of an element of the first design matrix in the adjustment (A-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Add the value of an element to an entry of the first design matrix in the adjustment (A-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool addFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

		/*!	\brief Set a block in the second design matrix. Each block corresponds to one mathematical observation equation. Also sets the inverse block.
		*/
		bool setSecondDgnMtrxBlock(MatrixIndex firstIndex, MatrixIndex secondIndex, const Eigen::MatrixXd &block);

		/*!	\brief Set the second design matrix to minus Identity for parametric case
		*/
		bool setSecondDgnMtrxToMinusIdentity();

		/*! \brief Reset the second design matrix. It must be filled at each iteration.
		*/
		bool resetSecondDgnMtrx(UEOIndices ueoi);

		/*! \brief Reset the constraint design matrix. It must be filled at each iteration.
		 */
		bool resetCnstrFirstDgnMtrx(UEOIndices ueoi);

		/*! \brief Reset the constraint vector. It must be filled at each iteration.
		 */
		bool resetCnstrMisclosureVector(UEOIndices ueoi);

		/*!	\brief Set a misclosure vector element.
		*/
		bool setMisclosureVectorElement(MatrixIndex row, TReal coeff);

		/*!	\brief Set a block in the weight matrix. Also sets the inverse block.
		*/
		bool setWeightMtrxBlock(MatrixIndex firstIndex, MatrixIndex secondIndex, const Eigen::MatrixXd &block);

		/*!	\brief Set the value of an element of the observations weight matrix in the adjustment (P-matrix)
			\param[in] row of the desired element
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

		/*!	\brief Add the value of an element to an entry of the constraints first design matrix in the adjustment (A2-matrix)
			\param[in] row of the desired element
			\param[in] column of the desired element
			\param[in] coefficient: value of the desired element
		*/
		bool addCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

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

		/*!	\brief Returns the number of parameters constraints */
		int	getNbrConstraints()const;
		
		/*!	\brief Returns a const reference (pointer) to the first design matrix allocated here*/
		const TSparseMatrix* getFirstDgnMtrx() const noexcept;

		/*!	\brief Returns a const reference (pointer) to the second design matrix allocated here*/
		const TSparseMatrix* getSecondDgnMtrx() const noexcept;

		/*!	\brief Returns the private member secondDesignMatrixIsBlockDiag which indicates that B is block diagonal*/
		bool getSecondDgnBlockDiagStatus() const;

		/*!	\brief Returns a const reference (pointer) to the inverse second design matrix allocated here, if B is block diagonal*/
		const TSparseMatrix* getSecondDgnBlockDiagInvMtrx() const noexcept;

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

	UEOIndices fUEOIndices; /*!< number of unknowns, equations, observations and constraints */
	std::unique_ptr<TSparseMatrix> fCnstrFirstDesignMtrx; /*!< matrix A2 (c x u) for constraints first design submatrix*/
	std::unique_ptr<TSparseMatrix> firstDesignMatrix; /*!< matrix A (e x u) */
	std::unique_ptr<TSparseMatrix> secondDesignMatrix; /*!< matrix B (e x o) */
	bool secondDesignMatrixIsBlockDiag = true; /*!< flag indicating whether B is block diagonal */
	std::unique_ptr<TSparseMatrix> secondDesignBlockDiagInvMatrix; /*!< matrix B^-1 (e x o) */
	std::unique_ptr<TSparseMatrix> weightMatrix; /*!< matrix P (o x o) for observations weights */
	std::unique_ptr<TSparseMatrix> weightInvMatrix; /*!< matrix invP (o x o) for observations weights */
	std::unique_ptr<TSparseMatrix> weightUnkMatrix; /*!< matrix Pxx (u x u) for unknowns weights */

	std::unique_ptr<TVector> fMisclosureVector; /*!< vector (o x 1) for misclosure errors */
	std::unique_ptr<TVector> fCnstrMisclosureVector; /*!< vector W2 (c x 1) for constraints misclosure subvector */
};


#endif
