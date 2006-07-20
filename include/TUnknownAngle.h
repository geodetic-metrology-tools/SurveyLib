/** Class for an angle to be evaluated during a calculation*/

#ifndef SU_UNK_ANGLE
#define SU_UNK_ANGLE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
//
/////////////////////////////////////////////////////


#include "UEOIndices.h"
#include "TAngle.h"

// Class Definition
class TUnknownAngle 
{
public :
	
	///Enumaration of the possible status for this object
	typedef TANumericValue::EStatus EUnknownStatus;

	/**@name Constructors / Destructor*/
	//@{
	///Constructor
	TUnknownAngle();
	///Destructor
	virtual ~TUnknownAngle();
	//@}

	/**@name Access methods*/
	//@{
	/**@return the angle's provisional value as a TAngle instance*/
	virtual TAngle				getProvisionalValue() const;
	/**@return the angle's estimated value as a TAngle instance*/
	virtual TAngle				getEstimatedValue() const;
	/**@return the estimated angle's precision as a TAngle instance*/
	virtual TAngle				getEstimatedPrecision() const;
	/**@return the angle's unknown index*/
	virtual MatrixIndex			getIndex() const;
	/**@return the angle's status (unknown, variable or fixed)*/
	virtual EUnknownStatus		getStatus() const;
	//@}


	/**@name Set methods*/
	//@{
	///Sets the angle's provisional value
	virtual void				setProvisionalValue(TAngle);
	///Sets the correction to the angle's provisional value
	virtual void				setCorrection(TAngle);
	///Sets the estimated angle's precision
	virtual void				setEstimatedPrecision(TAngle);
	///Sets the angle's unknown index
	virtual MatrixIndex			setIndex(MatrixIndex);
	///Sets the angle's unknown/variable/fixed status
	virtual void				setStatus(EUnknownStatus);

	/**@return a true boolean if the status is variable or fixed*/
	virtual bool				known() const;
	///Prepares the angle for the next iteration of the calculation
	virtual void				prepareNextIteration();

protected:

	///Sets the angle's estimated value
	virtual void				setEstimatedValue();

private:
	
	EUnknownStatus		fStatus;
	
	MatrixIndex			fIndex;
	TAngle				fProvisionalValue;
	TAngle				fCorrection;
	TAngle				fEstimatedValue;
	TAngle				fEstimatedPrecision;
};

#endif
