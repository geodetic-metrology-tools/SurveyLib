/*SURVEYLIB VERSION!!!!!
// TLSInputMatrices.h

//////////////////////////////////////////////////////////////////////

/*! Class for input matrices of a least squares calculation

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
//		virtual void				setS0APrioriScaleFactor(double scalefac);
	
		//!Sets a coefficient of the first design matrix
		virtual bool				setFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, double coefficient);
		//!Sets a coefficient of the second design matrix
		virtual bool				setSecondDgnMtrxElement(MatrixIndex row, MatrixIndex column, double coefficient);
		//!Sets a coefficient of the misclosure vector
		virtual bool				setMisclosureVectorElement(MatrixIndex row, double coeff);
		//!Sets a coefficient of the weight matrix
		virtual bool				setWeightMtrxElement(MatrixIndex row, MatrixIndex column, double coefficient);
		//!Sets a coefficient of the constraint first design matrix
		virtual bool				setCnstrFirstDgnMtrxElement(MatrixIndex row, MatrixIndex column, double coefficient);
		//!Sets a coefficient of the constraint misclosure vector
		virtual bool				setCnstrMisclosureVectorElement(MatrixIndex row, double coeff);
	//@}

	 virtual int		getNbrUnknowns() const;
	 virtual int		getNbrObservations() const;
	 virtual int		getNbrEquations()const;
	 virtual int		getNbrConstraintObs()const;
	 virtual int		getNbrConstraints()const;


	/*!@name Acess methods*/
	//@{
		/*!@return the sigma zero a priori scale factor*/
//		virtual double					getS0APrioriScaleFactor() const;

		/*!@return a const reference to the first design matrix*/
		virtual const TMatrix&			getFirstDgnMtrx() const;
		/*!@return a const reference to the second design matrix*/
		virtual const TMatrix&			getSecondDgnMtrx() const;
		/*!@return a const reference to the weight design matrix*/
		virtual const TMatrix&			getWeightMtrx() const;
		/*!@return a const reference to the misclosure vector*/
		virtual const TColumnVector&	getMisclosureVctr() const;
		/*!@return a const reference to the constraint first design matrix*/
		virtual const TMatrix&			getCnstrFirstDgnMtrx() const;
		/*!@return a const reference to the constraint misclosure vector*/
		virtual const TColumnVector&	getCnstrMisclosureVctr() const;
	//@}


	//!Debug method
	void						saveMatricesToFile(int nbIter) const;


private:

	MatrixIndex		fNbUnk; /*!< number of unknowns: u */
	MatrixIndex		fNbObs; /*!< number of observations: o */
	MatrixIndex		fNbEqn; /*!< number of equations: e */
	int				fNbCnstrObs; /*!< number of constraint observations */
	MatrixIndex		fNbCnstr;/*!<number of constraint*/

	TMatrix*		fFirstDesignMtrx; /*!< matrix (e x u) for the parametric part of the model */
	TMatrix*		fSecondDesignMtrx; /*!< matrix (e x o) for the conditional part of the model  */
	TMatrix*		fWeightMtrx; /*!< matrix (o x o) for observations weights */
	TColumnVector*	fMisclosureVector; /*!< vector (e x u) for misclosure errors */
//	double			fS0APrioriScaleFactor; /*!< indicates if there is a priori scale factor or not */

	TMatrix*		fCnstrFirstDesignMtrx; /*!< matrix (o x 7 or less) for the parametric part of the model */
	TColumnVector*	fCnstrMisclosureVector; /*!< vector for misclosure errors */


};


#endif