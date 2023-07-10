/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLSResultsMatrices
#define SU_TLSResultsMatrices

#include "TSparseMatrix.h"
#include <UEOIndices.h>
#include "Quad.h"

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


	//!Destructor
	virtual ~TLSResultsMatrices();
	//@}

	/*!@name Getting methods*/
	//@{
	/*!	\brief Returns an element of the solution vector
		\param[in] row the desired element's index
	*/
	TReal getSolutionVctrElmt(MatrixIndex row) const {return (*fSolutionVctr)(row);}

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
	const TVector* getSolutionVectByConst() const noexcept {return fSolutionVctr;}

	/*! \brief Returns a pointer to the Residuals Vector (vector content cannot be changed when receiving this pointer) */
	const TVector* getResidualsVectByConst() const noexcept {return fResidualsVctr;}

	/*! \brief Returns a pointer to the residuals covariance matrix	(matrix content cannot be changed when receiving this pointer) */
	const TSparseMatrix* getResCovarMtrxByConst() const noexcept {return fResCovarianceMtrx;}

	/*! \brief Returns a pointer to the unknowns covariance matrix	(matrix content cannot be changed when receiving this pointer)*/
	const TSparseMatrix* getUnkCovarMtrxByConst() const noexcept {return fUnkCovarianceMtrx;}
	/*! \brief Returns a pointer to the unknowns covariance matrix	(matrix content can be changed)*/
	TSparseMatrix* getUnkCovarMtrx() const noexcept { return fUnkCovarianceMtrx; }

	/*! \brief Returns a pointer to the inverse of N1 (matrix content cannot be changed when receiving this pointer) */
	const TSparseMatrix* getInvN1MatrixByConst() const noexcept {return fInvN1Matrix; }

	/*! \brief Returns a pointer to the normal matrix (matrix content cannot be changed when receiving this pointer) */
	const TSparseMatrix* getNormalMatrixByConst() const noexcept {return fNormalMatrix; }

	/*! \brief Returns the squared sigma zero 	*/
	TReal getSigmaZero2() const { return fSigmaZero2; }

	/*! \brief Returns the squared sigma zero statistical lower limit	*/
	TReal getSigmaZeroLowLimit() const { return fSigmaZero2LowLimit; }

	/*! \brief Returns the squared sigma zero statistical upper limit	*/
	TReal getSigmaZeroUpLimit() const { return fSigmaZero2UpLimit; }

	//@}


	/*!@name Setting methods*/
	//@{
	/*! \brief Sets the sigma zero 	*/
	void setSigmaZero2(TReal s){ fSigmaZero2 = s;}

	/*! \brief Sets (by matrix copy, i.e. operator =) the residuals covariance matrix  	*/
	void setResCovarMtrx(TSparseMatrix& matrix) { *fResCovarianceMtrx = matrix; }

	/*! \brief Sets (by matrix copy, i.e. operator =) the unknowns covariance matrix */
	void setUnkCovarMtrx(TSparseMatrix& matrix) { *fUnkCovarianceMtrx = matrix; }
	
	/*!	\brief Sets (by matrix copy, i.e. operator =) the normal matrix, which is used to calculate the covariance matrices */
	void setInvN1Matrix(TSparseMatrix& matrix) { *fInvN1Matrix = matrix; }

	/*!	\brief Sets (by matrix copy, i.e. operator =) the normal matrix, which is used to calculate the covariance matrices */
	void setNormalMatrix(TSparseMatrix& matrix) { *fNormalMatrix = matrix; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the solution vector 	*/
	void setSolutionVect(TVector& vect) { *fSolutionVctr = vect; }

	/*!	\brief Sets (by vector copy, i.e. operator =) the residues vector 	*/
	void setResidualsVect(TVector& vect) { *fResidualsVctr = vect; }

	/*!	\brief Sets the squared sigma zero statistical upper and lower limits 	*/
	void setSigmaZero2Limits(TReal loLimit, TReal upLimit) {
		fSigmaZero2LowLimit =  loLimit; 
		fSigmaZero2UpLimit = upLimit;
	}
	//@}

	/*!@name Other methods*/
	//@{
	/*!	\brief Saves all the matrices elements in a file 	*/
	void saveMatricesToFile(int nbIter) const;

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(SerializerObject::SerializationHelper &obj) const override;
#endif // USE_SERIALIZER
	//@}


private:

	TVector*		fSolutionVctr; /*!< vector (u x 1) containing the calculated parameters */
	TVector*		fResidualsVctr; /*!< vector (o x 1) containing the calculated residues on observations */
	TSparseMatrix*	fResCovarianceMtrx; /*!< Qvv matrix (o x o) containing the variances and covariances for residuals */
	TSparseMatrix*	fUnkCovarianceMtrx; /*!< Qxx matrix (u x u) containing the variances and covariances for unknowns */
	TSparseMatrix*	fInvN1Matrix;  /*!< invN1 matrix (eq x eq) is the inverse of the matrix N1 = B*Pv^-1*BT */
	TSparseMatrix*	fNormalMatrix;  /*!< N matrix (u+nConstr x u+nConstr) is the normal matrix (extended with the constraints if there are some) */

	TReal fSigmaZero2; /*!< calculated "average variance" on residues */
	TReal fSigmaZero2LowLimit;
	TReal fSigmaZero2UpLimit;

};

#endif
