/*
© Copyright CERN 2000-2024. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLSINPUTMATRICES
#define SU_TLSINPUTMATRICES

#include <memory>

#include "Quad.h"
#include "TSparseMatrix.h"
#include "UEOIndices.h"

/*!
	\ingroup CalcElements

	\brief Class for the input matrices used in the LS-calculation.
*/
class TLSInputMatrices
{
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
	bool addFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

	/*!	\brief Set a block in the second design matrix. Each block corresponds to one mathematical observation equation. Also sets the inverse block.
	 */
	bool addSecondDgnMtrxBlock(MatrixIndex firstIndex, MatrixIndex secondIndex, const Eigen::MatrixXd &block);

	/*!	\brief Set the second design matrix to minus Identity for parametric case
	 */
	bool setSecondDgnMtrxToMinusIdentity();

	/*! \brief Reset the first design matrix if it must be filled at each iteration.
	 */
	bool resetFirstDgnMtrx();

	/*! \brief Reset the second design matrix if it must be filled at each iteration.
	 */
	bool resetSecondDgnMtrx();

	/*! \brief Reset the constraint design matrix if it must be filled at each iteration.
	 */
	bool resetCnstrFirstDgnMtrx();

	/*! \brief Reset the constraint vector if it must be filled at each iteration.
	 */
	bool resetCnstrMisclosureVector();

	/*!	\brief Set a misclosure vector element.
	 */
	bool setMisclosureVectorElement(MatrixIndex row, TReal coeff);

	/*!	\brief Set a block on the diagonal of the weight matrix. Also sets the inverse block.
	 */
	bool addWeightMtrxBlock(MatrixIndex index, const Eigen::MatrixXd &block);

	/*!	\brief Set the value of an element of the observations weight matrix in the adjustment (P-matrix)
		\param[in] row of the desired element
		\param[in] coefficient: value of the desired element
	*/
	bool addWeightMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

	/*!	\brief Set the value of an element of the inverted osbservations weight matrix in the adjustment (invP-matrix)
		\param[in] row of the desired element
		\param[in] column of the desired element
		\param[in] coefficient: value of the desired element
	*/
	bool addWeightInvMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

	/*!	\brief Set the value of an element of the parameters (i.e. unknowns) weight matrix in the adjustment (Pxx-matrix)
		\param[in] row of the desired element
		\param[in] column of the desired element
		\param[in] coefficient: value of the desired element
	*/
	bool addWeightUnkMtrxElement(MatrixIndex row, MatrixIndex column, TReal coefficient);

	/*!	\brief Set the value of an element of the constraints first design matrix (A2-submatrix)
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
	int getNbrUnknowns() const;

	/*!	\brief Returns the number of observations */
	int getNbrObservations() const;

	/*!	\brief Returns the number of equations */
	int getNbrEquations() const;

	/*!	\brief Returns the number of parameters constraints */
	int getNbrConstraints() const;

	/*!	\brief Returns a const reference to the first design matrix allocated here*/
	const TSparseMatrix &getFirstDgnMtrx() const;

	/*!	\brief Returns a const reference to the second design matrix allocated here*/
	const TSparseMatrix &getSecondDgnMtrx() const;

	/*!	\brief Returns the private member secondDesignMatrixIsBlockDiag which indicates that B is block diagonal*/
	bool getSecondDgnBlockDiagStatus() const;

	/*!	\brief Returns a const reference to the inverse second design matrix allocated here, if B is block diagonal*/
	const TSparseMatrix &getSecondDgnBlockDiagInvMtrx() const;

	/*!	\brief Returns a const reference to the weight matrix allocated here*/
	const TSparseMatrix &getWeightMtrx() const;

	/*!	\brief Returns a const reference to the inverted weight matrix allocated here*/
	const TSparseMatrix &getWeightInvMtrx() const;

	/*!	\brief Returns a const reference to the parameters-weight matrix allocated here*/
	const TSparseMatrix &getWeightUnkMtrx() const;

	/*!	\brief Returns a const reference to the misclosure vector allocated here*/
	const TVector &getMisclosureVctr() const noexcept;

	/*!	\brief Returns a const reference to the constraints first design submatrix allocated here*/
	const TSparseMatrix &getCnstrFirstDgnMtrx() const;

	/*!	\brief Returns a const reference to the constraints misclosure subvector allocated here*/
	const TVector &getCnstrMisclosureVctr() const noexcept;
	//@}
	// check if there are constraints that do not depend on any variable
	bool hasDegenerateConstraints() const;

	// finalize the matrices
	void finalizeMatrices();

	/// Debug method
	void saveMatricesToFile(int nbIter) const;
	bool isInitialized = false;

private:
	UEOIndices fUEOIndices; /*!< number of unknowns, equations, observations and constraints */
	std::unique_ptr<TSparseMatrixWithTriplets> fCnstrFirstDesignMtrx; /*!< matrix A2 (c x u) for constraints first design submatrix*/
	std::unique_ptr<TSparseMatrixWithTriplets> firstDesignMatrix;
	std::unique_ptr<TSparseMatrixWithTriplets> secondDesignMatrix; /*!< matrix B (e x o) */

	bool secondDesignMatrixIsBlockDiag = true; /*!< flag indicating whether B is block diagonal */
	std::unique_ptr<TSparseMatrixWithTriplets> secondDesignBlockDiagInvMatrix; /*!< matrix B^-1 (e x o) */
	std::unique_ptr<TSparseMatrixWithTriplets> weightMatrix; /*!< matrix P (o x o) for observations weights */
	std::unique_ptr<TSparseMatrixWithTriplets> weightInvMatrix; /*!< matrix invP (o x o) for observations weights */
	std::unique_ptr<TSparseMatrixWithTriplets> weightUnkMatrix; /*!< matrix Pxx (u x u) for unknowns weights */

	std::unique_ptr<TVector> fMisclosureVector; /*!< vector (o x 1) for misclosure errors */
	std::unique_ptr<TVector> fCnstrMisclosureVector; /*!< vector W2 (c x 1) for constraints misclosure subvector */
};

#endif
