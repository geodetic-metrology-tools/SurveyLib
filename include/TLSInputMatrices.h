/*SURVEYLIB VERSION!!!!!
// TLSInputMatrices.h

//////////////////////////////////////////////////////////////////////

 Class for input matrices of a least squares calculation

  Pattern:

  Copyright 2000 CERN EST/SU. All rights reserved.
*/


//////////////////////////////////////////////////////////////////////


#ifndef SU_TLSINPUTMATRICES
#define SU_TLSINPUTMATRICES


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include "TMatrix.h"
#include "TSparseMatrix.h"
#include "TColumnVector.h"
#include <fstream>
#include <sstream>
//#include <iostream>
#include "UEOIndices.h"
using namespace std;


//! class for input matrices used in the ls-calculation
class TLSInputMatrices{

public:

	/*!@name Constructors / Destructor*/
	//@{
		//!Constructor
		TLSInputMatrices();
		//!Destructor
		~TLSInputMatrices();
	//@}


	/*!@name Set methods*/
	//@{
		//!Sets the dimensions of the matrices
		/*!@param nbUnknowns the survey network's number of unknowns
		@param nbEquations the survey network's number of equations
		@param nbObservations the survey network's number of observations*/
		virtual void				setDimensions(int nbUnknowns, int nbEquations, int nbObservations, int nbCnstrObs);
	
		//!Sets the dimensions of the matrices
		/*! \param nbUnknowns the survey network's number of unknowns
			\param nbEquations the survey network's number of equations
			\param nbObservations the survey network's number of observations
			\param nbConstraints the free survey network's number of constraint*/
		virtual void				setDimensions(int nbUnknowns, int nbEquations, int nbCnstrObs, int nbObservations, int nbConstraints);
	
		//!Sets the scale factor for the sigma zero a priori
//		virtual void				setS0APrioriScaleFactor(real scalefac);
	
		//!Sets a coefficient of the first design matrix
		virtual bool				setFirstDgnMtrxElement(MatrixIndex column, real coefficient);
		//!Sets a coefficient of the second design matrix
		virtual bool				setSecondDgnMtrxElement(MatrixIndex column, real coefficient);
		//!Sets a coefficient of the misclosure vector
		virtual bool				setMisclosureVectorElement(MatrixIndex row, real coeff);
		//!Sets a coefficient of the weight matrix
		virtual bool				setWeightMtrxElement(real coefficient);
		//!Sets a coefficient of the constraint first design matrix
		virtual bool				setCnstrFirstDgnMtrxElement(MatrixIndex column, real coefficient);
		//!Sets a coefficient of the constraint misclosure vector
		virtual bool				setCnstrMisclosureVectorElement(MatrixIndex row, real coeff);
	//@}

	 virtual int		getNbrUnknowns() const;
	 virtual int		getNbrObservations() const;
	 virtual int		getNbrEquations()const;
	 virtual int		getNbrConstraintObs()const;
	 virtual int		getNbrConstraints()const;


	/*!@name Acess methods*/
	//@{
		/*!@return the sigma zero a priori scale factor*/
//		virtual real					getS0APrioriScaleFactor() const;

		/*!@return a const reference to the first design matrix*/
		const TSparseMatrix* getFirstDgnMtrxTransposed() const;
		/*!@return a const reference to the second design matrix*/
		const TSparseMatrix* getSecondDgnMtrxTransposed() const;
		/*!@return a const reference to the weight design matrix*/
		const TSparseMatrix* getWeightMtrx() const;
		/*!@return a const reference to the misclosure vector*/
		const TColumnVector&	getMisclosureVctr() const;
		/*!@return a const reference to the constraint first design matrix*/
		const TSparseMatrix*	getCnstrFirstDgnMtrx() const;
		/*!@return a const reference to the constraint misclosure vector*/
		const TColumnVector&	getCnstrMisclosureVctr() const;
	//@}


	//!Debug method
	void						saveMatricesToFile(int nbIter) const;

	void setNewRow();
	void setConstraintNewColumn();
	void finishedFillingMatrices();

	void setFirstDesignMatrix(TSparseMatrix* f) { firstDesignMatrix = f; };
	TSparseMatrix* getFirstDesignMatrix() const { return firstDesignMatrix; };
	void setWeightMatrixInverted(TSparseMatrix* f) { weightMatrixInverted = f; };
	TSparseMatrix* getWeightMatrixInverted() const { return weightMatrixInverted; };
	void setBTimesWInvTimesBTransInverted(TSparseMatrix* f) { bTimesWInvTimesBTransInverted = f; };
	TSparseMatrix* getBTimesWInvTimesBTransInverted() const { return bTimesWInvTimesBTransInverted; };

	void clearMatrices();


private:

	MatrixIndex		fNbUnk; /*!< number of unknowns: u */
	MatrixIndex		fNbObs; /*!< number of observations: o */
	MatrixIndex		fNbEqn; /*!< number of equations: e */
	int				fNbCnstrObs; /*!< number of constraint observations */
	MatrixIndex		fNbCnstr;/*!<number of constraint: c */

	list<real>*	firstDesignMatrixTransposedValues; /*!< matrix (u x e) for the parametric part of the model */
	list<int>*		firstDesignMatrixTransposedColPtr;
	list<int>*		firstDesignMatrixTransposedRowInd;

	list<real>*	secondDesignMatrixTransposedValues; /*!< matrix (o x e) for the conditional part of the model  */
	list<int>*		secondDesignMatrixTransposedColPtr;
	list<int>*		secondDesignMatrixTransposedRowInd;

	list<real>*	    constraintFirstDesignMatrixValues; /*!< matrix (u x c) for the parametric part of the model  */
	list<int>*		constraintFirstDesignMatrixColPtr;
	list<int>*		constraintFirstDesignMatrixRowInd;

	list<real>*	weightMatrixValues; /*!< matrix (o x o) for observations weights */

	TColumnVector*	fMisclosureVector; /*!< vector (u) for misclosure errors */
//	real			fS0APrioriScaleFactor; /*!< indicates if there is a priori scale factor or not */

	TSparseMatrix*	fCnstrFirstDesignMtrx; /*!< matrix (u x c) for the parametric part of the model */
	TColumnVector*	fCnstrMisclosureVector; /*!< vector for misclosure errors */

	TSparseMatrix*	firstDesignMatrix;
	TSparseMatrix*	firstDesignMatrixTransposed;
	TSparseMatrix*	secondDesignMatrixTransposed;
	TSparseMatrix*	weightMatrix;
	TSparseMatrix*	weightMatrixInverted;
	TSparseMatrix*	bTimesWInvTimesBTransInverted;

};


#endif
