/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SU_TLSResultsMatrices
#define SU_TLSResultsMatrices

#include <memory>

#include <UEOIndices.h>

#include "Quad.h"
#include "TSparseMatrix.h"

#if USE_SERIALIZER
#	include <Serializer.hpp>
#endif // USE_SERIALIZER

/*!
	\ingroup CalcElements
	\brief Class for result matrices of a least squares calculation.
*/
#if USE_SERIALIZER
class TLSResultsMatrices : public Serializable
#else
class TLSResultsMatrices
#endif // USE_SERIALIZER
{
public:
	/*!@name Constructors / Destructor*/
	//@{

	/*! \brief Constructor
		\param[in] ueoi an object holding the number of unknowns, equations and observations,
	thus enabling the dimensioning of the matrices (set to zero)
	*/
	TLSResultsMatrices(UEOIndices ueoi);

	//! Destructor
	virtual ~TLSResultsMatrices() = default;
	//@}

	/*!@name Getting methods*/
	//@{
	/*!	\brief Returns an element of the solution vector
		\param[in] row the desired element's index
	*/
	TReal getSolutionVctrElmt(MatrixIndex row) const { return (*fSolutionVctr)(row); }

	/*!	\brief Returns an element of the residuals vector
		\param[in] row the desired element's index*/
	TReal getResidualsVctrElmt(MatrixIndex row) const { return (*fResidualsVctr)(row); }

	/*! \brief Returns an element of the observations covariance matrix
		\param[in] row the desired element's row index
		\param[in] column the desired element's column index*/
	TReal getUnkCovarMtrxElmt(MatrixIndex row, MatrixIndex column) const { return (*fUnkCovarianceMtrx).coeff(row, column); }

	/*! \brief Returns a pointer to the Solution Vector	(vector content cannot be changed when receiving this pointer) */
	const TVector *getSolutionVectByConst() const noexcept { return fSolutionVctr.get(); }

	/*! \brief Returns a pointer to the Residuals Vector (vector content cannot be changed when receiving this pointer) */
	const TVector *getResidualsVectByConst() const noexcept { return fResidualsVctr.get(); }

	/*! \brief Returns a pointer to the Residuals covariance diagonal Vector (vector content cannot be changed when receiving this pointer) */
	const TVector *getResCovarDiagByConst() const noexcept { return fResCovarDiag.get(); }

	/*! \brief Returns a pointer to the Z reliability vector (vector content cannot be changed when receiving this pointer) */
	const TVector *getZReliabilityVectByConst() const noexcept { return fZReliability.get(); }

	/*! \brief Returns a pointer to the unknowns covariance matrix	(matrix content cannot be changed when receiving this pointer)*/
	const TSparseMatrix *getUnkCovarMtrxByConst() const noexcept { return fUnkCovarianceMtrx.get(); }
	/*! \brief Returns a pointer to the unknowns covariance matrix	(matrix content can be changed)*/
	TSparseMatrix *getUnkCovarMtrx() const noexcept { return fUnkCovarianceMtrx.get(); }

	/*! \brief Returns a pointer to the inverse of N1 (matrix content cannot be changed when receiving this pointer) */
	const TSparseMatrix *getInvN1MatrixByConst() const noexcept { return fInvN1Matrix.get(); }

	/*! \brief Returns a pointer to the normal matrix (matrix content cannot be changed when receiving this pointer) */
	const TSparseMatrix *getNormalMatrixByConst() const noexcept { return fNormalMatrix.get(); }

	/*! \brief Returns the squared sigma zero 	*/
	TReal getSigmaZero2() const { return fSigmaZero2; }

	/*! \brief Returns the sigma zero statistical lower limit	*/
	TReal getSigmaZeroLowLimit() const { return fSigmaZeroLowLimit; }

	/*! \brief Returns the sigma zero statistical upper limit	*/
	TReal getSigmaZeroUpLimit() const { return fSigmaZeroUpLimit; }

	//@}

	/*!@name Setting methods*/
	//@{
	/*! \brief Sets the sigma zero 	*/
	void setSigmaZero2(TReal s) { fSigmaZero2 = s; }

	/*! \brief Sets (by matrix copy, i.e. operator =) the unknowns covariance matrix */
	void setUnkCovarMtrx(TSparseMatrix &matrix) { *fUnkCovarianceMtrx = matrix; }

	/*!	\brief Sets (by matrix copy, i.e. operator =) the normal matrix, which is used to calculate the covariance matrices */
	void setInvN1Matrix(TSparseMatrix &matrix) { *fInvN1Matrix = matrix; }

	/*!	\brief Sets (by matrix copy, i.e. operator =) the normal matrix, which is used to calculate the covariance matrices */
	void setNormalMatrix(TSparseMatrix &matrix) { *fNormalMatrix = matrix; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the solution vector 	*/
	void setSolutionVect(TVector &vect) { *fSolutionVctr = vect; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the residues vector 	*/
	void setResidualsVect(TVector &vect) { *fResidualsVctr = vect; }

		/*!	\brief Sets (by vector copy, i.e. operator =) the Z reliability vector 	*/
	void setZReliabilityVect(TVector &vect) { *fZReliability = vect; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the residues coavr diag vector 	*/
	void setResCovarDiag(TVector &vect) { *fResCovarDiag = vect; }

	/*!	\brief Sets the sigma zero statistical upper and lower limits 	*/
	void setSigmaZeroLimits(TReal loLimit, TReal upLimit)
	{
		fSigmaZeroLowLimit = loLimit;
		fSigmaZeroUpLimit = upLimit;
	}
	//@}

	/*!@name Other methods*/
	//@{
	/*!	\brief Saves all the matrices elements in a file 	*/
	void saveMatricesToFile(int nbIter) const;

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const override;
#endif // USE_SERIALIZER
	//@}

private:
	std::unique_ptr<TVector> fSolutionVctr; /*!< vector (u x 1) containing the calculated parameters */
	std::unique_ptr<TVector> fResidualsVctr; /*!< vector (o x 1) containing the calculated residues on observations */
	std::unique_ptr<TVector> fResCovarDiag;
	std::unique_ptr<TVector> fZReliability;

	std::unique_ptr<TSparseMatrix> fUnkCovarianceMtrx; /*!< Qxx matrix (u x u) containing the variances and covariances for unknowns */
	std::unique_ptr<TSparseMatrix> fInvN1Matrix; /*!< invN1 matrix (eq x eq) is the inverse of the matrix N1 = B*Pv^-1*BT */
	std::unique_ptr<TSparseMatrix> fNormalMatrix; /*!< N matrix (u+nConstr x u+nConstr) is the normal matrix (extended with the constraints if there are some) */

	TReal fSigmaZero2; /*!< calculated "average variance" on residues */
	TReal fSigmaZeroLowLimit;
	TReal fSigmaZeroUpLimit;
};

#endif
