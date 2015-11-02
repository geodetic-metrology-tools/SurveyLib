// TLength.h
//
// Class for a length 
//
// include math operators +, -, *factor, =.
//
// Copyright 1999,2000, CERN, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////


#ifndef SU_LENGTH
#define SU_LENGTH

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////

//!Includes Files
#include <iostream>
#include	<float.h>
#include <math.h>
#include	<assert.h>
//

#include  "TANumericValue.h"

//!Class Definition
/// \ingroup MathematicalConcepts
class	TLength  : public  TANumericValue //: public TObject
{

public:

	/*!\name Constants*/
	//@{
	//!what type of value the coordinate holding
	enum ENumberSign {kNegative=-1, kZero, kPositive};
	//! possible length units
	enum EUnits {kKilometres, kMetres, kMillimetres}; 
	//@}
	
	/*!\name Constructors and Destructors*/
	//@{
	//! Default Constructor
	TLength();

   //! constructor taking a given length value in metres
   explicit  TLength(TReal, EUnits = kMetres);

	//! copy constructor
	TLength(const TLength&);
	//! Destructor
	virtual	~TLength();
	//@}

	/*!\name Public Methods*/
	//@{
	
	/*!set a value in metres
	\param TReal, value of Tlength in metres 
	*/
	void setMetresValue(TReal);

	/*!set a value in kilometres
	\param TReal, value of Tlength in kilometres 
	*/
	void setKMetresValue(TReal);

	/*!set a value in millimetres
	\param TReal, value of Tlength in millimetres 
	*/
	void setMMetresValue(TReal);
	
	//!give the value in metres
	TReal	getMetresValue() const;

	//!give the value in kilometres
	TReal	getKMetresValue() const;

	//!give the value in millimetres
	TReal	getMMetresValue() const;
	
	/*!Equality operator, comparaison between two TLength objects
	\param Tlength&, TLength object
	\return true if the two TLength objects are egals, else return False
	*/
	virtual bool operator==(const TLength&) const;

	/*!Less than operator, comparaison between two TLength objects
	\param Tlength&, TLength object
	\return true if the value of the first object is less than the value of
	the second object, else return false
	*/
	virtual bool operator<(const TLength&) const;

	//!add two TLength objects
	TLength operator+(const TLength &);
	
	//!substract two TLength objects
	TLength operator-(const TLength &);

	/*! div. a TLength by a TLength*/
	TReal operator/(const TLength& );
	
	//!multiply a TLength object by a factor
	TLength operator*(const TReal );
	
	//!idem *
	friend  TLength operator*(const TReal, const TLength & );

	//!assign a TLength object to an other
	TLength& operator=(const TLength &);
	
	//!add two TLength objects and rewrite this
	TLength& operator+=(const TLength &);
	
	//!substract two TLength objects and rewrite this
	TLength& operator-=(const TLength &);
	
	//!multiply a TLength object by a factor and rewrite this
   TLength& operator*=(const TReal);

   //!cast operator return the value as a TReal and expressed in Meters
   operator TReal() const { return fValue; }

private:

	/*!\name Protected Methods*/
	//@{
	//!return the sign of a TReal number
	ENumberSign	sign(TReal	number) const;
	//@}


private:

	/*!\name Protected Attributes*/
	//@{
	//! default = LITERAL(0.0)
	TReal			fValue;
	//@}


	//ClassDef(TLength, 1)
};



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



inline void TLength::setMetresValue(const TReal value)
{	// set as a length measure of the given metres value
	fValue = value;
	valueSet();
	return;
}


inline void TLength::setKMetresValue(const TReal value)
{	// set as a length measure of the given kilometres value
	// scale the value input
	fValue = value * 1000;
	valueSet();
	return;
}


inline void TLength::setMMetresValue(const TReal value)
{	// set as a length measure of the given millimetres value
	// scale the value input
	fValue = value * 0.001;
	valueSet();
	return;
}


inline TReal TLength::getMetresValue() const
{	// get the metres length value
	return fValue;
}


inline TReal	TLength::getKMetresValue() const
{	// get the km length value
	// return the converted length value
	return fValue * 0.001;
}


inline TReal	TLength::getMMetresValue() const
{	// get the mm length value
	// return the converted length value
	return fValue * 1000;
}

#endif // SU_LENGTH
