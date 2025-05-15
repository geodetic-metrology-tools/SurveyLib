/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿// TLength.h


// Class for a length
//
// include math operators +, -, *factor, =.
////////////////////////////////////////////////////////////////

#ifndef SU_LENGTH
#define SU_LENGTH

#if _MSC_VER >= 1000
#	pragma once
#endif // _MSC_VER >= 1000

//! Includes Files
#include <iostream>

#include <assert.h>
#include <math.h>

#include "Quad.h"

#if USE_SERIALIZER
#	include <Serializer.hpp>
#endif // USE_SERIALIZER

//! Class Definition
/// \ingroup MathematicalConcepts
#if USE_SERIALIZER
class TLength : public Serializable
#else
class TLength
#endif // USE_SERIALIZER
{
public:
	/*!\name Constants*/
	//@{
	//! what type of value the coordinate holding
	enum ENumberSign
	{
		kNegative = -1,
		kZero,
		kPositive
	};
	//! possible length units
	enum EUnits
	{
		kKilometres,
		kMetres,
		kMillimetres
	};
	//@}

	/*!\name Constructors and Destructors*/
	//@{
	//! Default Constructor
	TLength();

	//! constructor taking a given length value in metres
	explicit TLength(TReal, EUnits = kMetres);

	//! copy constructor
	TLength(const TLength &);
	//! Destructor
	virtual ~TLength();
	//@}

	/*!\name Public Methods*/
	//@{
#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const override;
#endif // USE_SERIALIZER

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

	//! give the value in metres
	TReal getMetresValue() const;

	//! give the value in kilometres
	TReal getKMetresValue() const;

	//! give the value in millimetres
	TReal getMMetresValue() const;

	/*!Equality operator, comparaison between two TLength objects
	\param Tlength&, TLength object
	\return true if the two TLength objects are egals, else return False
	*/
	virtual bool operator==(const TLength &) const;

	/*!Less than operator, comparaison between two TLength objects
	\param Tlength&, TLength object
	\return true if the value of the first object is less than the value of
	the second object, else return false
	*/
	virtual bool operator<(const TLength &) const;

	//! add two TLength objects
	TLength operator+(const TLength &);

	//! substract two TLength objects
	TLength operator-(const TLength &);

	/*! div. a TLength by a TLength*/
	TReal operator/(const TLength &);

	//! multiply a TLength object by a factor
	TLength operator*(const TReal);

	//! idem *
	friend TLength operator*(const TReal, const TLength &);

	//! multiply a TLength object by an int factor
	TLength operator*(const int);

	//! idem *
	friend TLength operator*(const int, const TLength &);

	//! assign a TLength object to an other
	TLength &operator=(const TLength &);

	//! add two TLength objects and rewrite this
	TLength &operator+=(const TLength &);

	//! substract two TLength objects and rewrite this
	TLength &operator-=(const TLength &);

	//! multiply a TLength object by a factor and rewrite this
	TLength &operator*=(const TReal);

	//! cast operator return the value as a TReal and expressed in Meters
	operator TReal() const { return fValue; }

private:
	/*!\name Protected Methods*/
	//@{
	//! return the sign of a TReal number
	ENumberSign sign(TReal number) const;
	//@}

private:
	/*!\name Protected Attributes*/
	//@{
	//! default = LITERAL(0.0)
	TReal fValue;
	//@}

	// ClassDef(TLength, 1)
};

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline void TLength::setMetresValue(const TReal value)
{ // set as a length measure of the given metres value
	fValue = value;

	return;
}

inline void TLength::setKMetresValue(const TReal value)
{ // set as a length measure of the given kilometres value
	// scale the value input
	fValue = value * 1000;

	return;
}

inline void TLength::setMMetresValue(const TReal value)
{ // set as a length measure of the given millimetres value
	// scale the value input
	fValue = value * 0.001;

	return;
}

inline TReal TLength::getMetresValue() const
{ // get the metres length value
	return fValue;
}

inline TReal TLength::getKMetresValue() const
{ // get the km length value
	// return the converted length value
	return fValue * 0.001;
}

inline TReal TLength::getMMetresValue() const
{ // get the mm length value
	// return the converted length value
	return fValue * 1000;
}

#if USE_SERIALIZER
inline void TLength::serialize(ObjectSerializer &obj) const
{
	obj.addProperty("fValue", fValue);
}
#endif // USE_SERIALIZER

#endif // SU_LENGTH
