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

	/*! \brief Returns an element of the residuals covariance matrix
		\param[in] row the desired element's row index
		\param[in] column the desired element's column index*/
	TReal getResCovarMtrxElmt(MatrixIndex row, MatrixIndex column) const { return (*fResCovarianceMtrx).coeff(row, column); }

	/*! \brief Returns an element of the observations covariance matrix
		\param[in] row the desired element's row index
		\param[in] column the desired element's column index*/
	TReal getUnkCovarMtrxElmt(MatrixIndex row, MatrixIndex column) const { return (*fUnkCovarianceMtrx).coeff(row, column); }

	/*! \brief Returns a pointer to the Solution Vector	(vector content cannot be changed when receiving this pointer) */
	const TVector *getSolutionVectByConst() const noexcept { return fSolutionVctr.get(); }

	/*! \brief Returns a pointer to the Residuals Vector (vector content cannot be changed when receiving this pointer) */
	const TVector *getResidualsVectByConst() const noexcept { return fResidualsVctr.get(); }

	/*! \brief Returns a pointer to the residuals covariance matrix	(matrix content cannot be changed when receiving this pointer) */
	const TSparseMatrix *getResCovarMtrxByConst() const noexcept { return fResCovarianceMtrx.get(); }

	/*! \brief Returns a pointer to the unknowns covariance matrix	(matrix content cannot be changed when receiving this pointer)*/
	const TSparseMatrix *getUnkCovarMtrxByConst() const noexcept { return fUnkCovarianceMtrx.get(); }
	/*! \brief Returns a pointer to the unknowns covariance matrix	(matrix content can be changed)*/
	TSparseMatrix *getUnkCovarMtrx() const noexcept { return fUnkCovarianceMtrx.get(); }

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

	/*! \brief Sets (by matrix copy, i.e. operator =) the residuals covariance matrix  	*/
	void setResCovarMtrx(TSparseMatrix &matrix) { *fResCovarianceMtrx = matrix; }

	/*! \brief Sets (by matrix copy, i.e. operator =) the unknowns covariance matrix */
	void setUnkCovarMtrx(TSparseMatrix &matrix) { *fUnkCovarianceMtrx = matrix; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the solution vector 	*/
	void setSolutionVect(TVector &vect) { *fSolutionVctr = vect; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the residues vector 	*/
	void setResidualsVect(TVector &vect) { *fResidualsVctr = vect; }

	/*!	\brief Sets the sigma zero statistical upper and lower limits 	*/
	void setSigmaZeroLimits(TReal loLimit, TReal upLimit)
	{
		fSigmaZeroLowLimit = loLimit;
		fSigmaZeroUpLimit = upLimit;
	}
	//@}

	// for creating the full covar matrix from the reduced one that only contains information on active indices
	TSparseMatrix blowUpParCovarianceMatrix(const TSparseMatrix& reducedCovar, std::vector<int> activeIndices);
	TSparseMatrix blowUpObsCovarianceMatrix(const TSparseMatrix& reducedCovar, std::vector<int> activeIndices);


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
	std::unique_ptr<TSparseMatrix> fResCovarianceMtrx; /*!< Qvv matrix (o x o) containing the variances and covariances for residuals */
	std::unique_ptr<TSparseMatrix> fUnkCovarianceMtrx; /*!< Qxx matrix (u x u) containing the variances and covariances for unknowns */

	TReal fSigmaZero2; /*!< calculated "average variance" on residues */
	TReal fSigmaZeroLowLimit;
	TReal fSigmaZeroUpLimit;
	UEOIndices fUeoi;
};

#endif
