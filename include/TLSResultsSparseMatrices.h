

#ifndef SU_TLSResultsSparseMatrices
#define SU_TLSResultsSparseMatrices


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include "TDouble.h"
#include "TMatrix.h"
#include "TSparseMatrix.h"
#include "TColumnVector.h"
#include <fstream>
#include <sstream>
//#include <iostream.h>
#include "UEOIndices.h"


//using namespace std;


//!Class for result matrices of a least squares calculation
class TLSResultsSparseMatrices{

public:

	/*!@name Constructors / Destructor*/
	//@{
	TLSResultsSparseMatrices(int numUnknowns, int numEquations);

	//!Constructor
	/*!@param ueoi an object holding the number of unknowns, equations and observations,
	thus enabling the dimensioning of the matrices (set to zero)*/
	TLSResultsSparseMatrices(UEOIndices ueoi);


	//!Destructor
	virtual ~TLSResultsSparseMatrices();
	//@}

	/*!@name Access nethods*/
	//@{
	/*!@return an element of the solution vector
	@param row the desired element's index*/
	virtual MatrixElmt	getSolutionVctrElmt(MatrixIndex row) const {return (*fSolutionVctr)(row);}

	/*!@return an element of the residuals vector
	@param row the desired element's index*/
	virtual MatrixElmt	getResidualsVctrElmt(MatrixIndex row) const {return (*fResidualsVctr)(row);}

	/*!@return an element of the unknowns covariance matrix
	@param row the desired element's row index
	@param column the desired element's column index*/
	virtual MatrixElmt	getUnknownsCovarMtrxElmt(MatrixIndex row, MatrixIndex column) const {return (*fUnknownsCovarianceMtrx)(row, column);}

	/*!@return a pointer to the Solution Vector*/
	virtual TColumnVector*		getSolutionVctr() const {return fSolutionVctr;}

	/*!@return a pointer to the Residuals Vector*/
	virtual TColumnVector*		getResidualsVctr() const {return fResidualsVctr;}

	/*!@return a pointer to the unknowns covariance matrix*/
	virtual TSparseMatrix*		getUnkCovarMtrx() const {return fUnknownsCovarianceMtrx;}
	virtual void				setUnkCovarMtrx(TSparseMatrix* m) { fUnknownsCovarianceMtrx = m; }

	/*!@return the boolean indicating if sigma zero should be applied or not */
	virtual bool				S0APosterioriVariances() const {return fS0APosterioriVariances;}
	/*!@return  the squared sigma zero */
	virtual TReal				getSigmaZero2() const { return fSigmaZero2; }
	//@}

	/*! sets the sigma zero */
	virtual void			setSigmaZero2(TReal s);

	/*! sets the boolean */
	virtual void			setS0APosterioriVariances(bool s0) {fS0APosterioriVariances = s0; return;}

	/*! compute and return a vector of observations variances */
	TColumnVector	computeVarObs(const TSparseMatrix& A, const TSparseMatrix& ATransposed);

	TSparseMatrix*  getL() const { return L; }
	void			setL(TSparseMatrix* l) { L = l; }
	TSparseMatrix* getBigMatrix() const { return bigMatrix; }
	void setBigMatrix(TSparseMatrix* l) { bigMatrix = l; }

private:
	//mj2008
	//!Default constructor
	TLSResultsSparseMatrices();
	//!Constructor
	/*!The passed pointers are stored. The pointed to matrices musn't be deleted
	@param solut a pointer to the solution vector
	@param solut a pointer to the residuals vector
	@param sigm2 the estimated square of the sigma zero
	@param unkcov a pointer to the unknowns covariance matrix */
	TLSResultsSparseMatrices(TColumnVector* solut, TColumnVector* resid, TReal sigm2);
	//mj
	


	TColumnVector*	fSolutionVctr; /*!< vector (u x 1) containing the calculated parameters */
	TColumnVector*	fResidualsVctr; /*!< vector (o x 1) containing the calculated residues on observations */
	TSparseMatrix*	fUnknownsCovarianceMtrx; /*!< matrix (u x u) containing the variances and covariances for parameters */
	TReal			fSigmaZero2; /*!< calculated "average variance" on residues */
	bool			fS0APosterioriVariances; /*!< indicates if the s0 a posteriori should be applied */
	TSparseMatrix*  L;
	TSparseMatrix* bigMatrix;
};

/////////////////////
// Inline Definitions
/////////////////////
inline void TLSResultsSparseMatrices::setSigmaZero2(TReal s){ fSigmaZero2 = s;}

//inline void TLSResultsSparseMatrices::setResVariance(TReal rv) {fResidualVariance = new TDouble(rv);}

#endif
