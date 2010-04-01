/** Class for a length to be evaluated during a calculation*/


#ifndef SU_UNKNOWN_LENGTH
#define SU_UNKNOWN_LENGTH

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
//
/////////////////////////////////////////////////////

#include "TLength.h"
#include "UEOIndices.h"

// Class Definition
class TUnknownLength 
{
public :
	
	///Enumaration of the possible status for this object
	typedef TANumericValue::EStatus EUnknownStatus;

	/**@name Constructors / Destructor*/
	//@{
	///Constructor
	TUnknownLength();
	///Copy constructor
	TUnknownLength(const TUnknownLength& source);
	///Destructor
	virtual ~TUnknownLength();
	//@}

	/**@name Access methods*/
	//@{
	/**@return the length's provisional value as a TLength instance*/
	virtual TLength				getProvisionalValue() const;
	/**@return the length's estimated value as a TLength instance*/
	virtual TLength				getEstimatedValue() const;
	/**@return the estimated length's precision as a TLength instance*/
	virtual TLength				getEstimatedPrecision() const;
	/**@return the length's unknown index*/
	virtual MatrixIndex			getIndex() const;
	/**@return the length's status (unknown, variable or fixed)*/
	virtual EUnknownStatus		getStatus() const;
	//@}

	/**@name Set methods*/
	//@{
	///Sets the length's provisional value
	virtual void				setProvisionalValue(TLength);
	///Sets the correction to the length's provisional value
	virtual void			setCorrection(TLength);
	///Sets the estimated length's precision
	virtual void				setEstimatedPrecision(TLength);
	///Sets the length's unknown index
	virtual MatrixIndex			setIndex(MatrixIndex);
	///Sets the length's unknown/variable/fixed status
	virtual void				setStatus(EUnknownStatus);

	/**@return a true boolean if the status is variable or fixed*/
	virtual bool				known() const;
	///Prepares the length for the next iteration of the calculation
	virtual void				prepareNextIteration();

protected:

	///Sets the length's estimated value
	void				setEstimatedValue();

private:
	
	EUnknownStatus		fStatus;
	
	MatrixIndex			fIndex;
	TLength				fProvisionalValue;
	TLength				fCorrection;
	TLength				fEstimatedValue;
	TLength				fEstimatedPrecision;
};

#endif

