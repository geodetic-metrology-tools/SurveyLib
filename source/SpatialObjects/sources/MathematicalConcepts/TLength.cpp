// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TLength.cpp
//
// Class for a length
//
// include math operators +, -, *factor, =.
//
//
////////////////////////////////////////////////////////////////

#include "TLength.h"

#include "TDouble.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLength::TLength() : fValue(NO_VALf)
{ // default constructor
}

TLength::TLength(TReal value, EUnits unit)
{ // constructor taking a given length value in metres

	switch (unit)
	{
	case EUnits::kMetres:
		setMetresValue(value);
		break;
	case EUnits::kMillimetres:
		setMMetresValue(value);
		break;
	case EUnits::kKilometres:
		setKMetresValue(value);
		break;
	}
}

TLength::TLength(const TLength &tl)
{ // copy constructor
	fValue = tl.fValue;
}

TLength::~TLength()
{
}

//////////////////////////////////////////////////////////////////////
// operators definitions
//////////////////////////////////////////////////////////////////////
////////////////////
// equality operator
////////////////////
bool TLength::operator==(const TLength &right) const
{
	if (getMetresValue() == right.getMetresValue())
		return true;
	else
		return false;
}

/////////////////////
// less than operator
/////////////////////
bool TLength::operator<(const TLength &right) const
{
	if (getMetresValue() < right.getMetresValue())
		return true;
	else
		return false;
}

TLength TLength::operator+(const TLength &length1)
{ // add two TLength objects
	TLength resultat;

	if (length1 != NO_VALf && *this != NO_VALf)
		resultat.setMetresValue(this->getMetresValue() + length1.getMetresValue());

	return resultat;
}

TLength TLength::operator-(const TLength &length1)
{ // substract two TLength objects
	TLength resultat;

	if (length1 != NO_VALf && *this != NO_VALf)
		resultat.setMetresValue(getMetresValue() - length1.getMetresValue());

	return resultat;
}

TReal TLength::operator/(const TLength &div)
{ // Multiplies a TLength by a TDouble scale factor

	return (div.getMetresValue() != 0) ? (this->getMetresValue() / div.getMetresValue()) : NO_VALf;
}

TLength TLength::operator*(const TReal factor)
{ // multiply a TLength object by a factor
	TLength resultat;

	if (factor != NO_VALf && *this != NO_VALf)
		resultat.setMetresValue(factor * this->getMetresValue());

	return resultat;
}

TLength operator*(const TReal factor, const TLength &length)
{ // multiply a TLength object by a factor
	TLength resultat;

	if (length != NO_VALf && factor != NO_VALf)
		resultat.setMetresValue(factor * (length.getMetresValue()));

	return resultat;
}

TLength TLength::operator*(const int factor)
{ // multiply a TLength object by an int factor
	return TLength(TReal(factor) * this->getMetresValue());
}

TLength operator*(const int factor, const TLength &length)
{ // multiply a TLength object by an int factor
	return TReal(factor) * length;
}

TLength &TLength::operator=(const TLength &length)
{ // assign a TLength object to an other
	if (this != &length)
		fValue = (length.getMetresValue());

	return *this;
}

TLength &TLength::operator+=(const TLength &length)
{ // add two TLength objects and rewrite this
	return *this = *this + length;
}

TLength &TLength::operator-=(const TLength &length)
{ // substract two TLength objects and rewrite this
	return *this = *this - length;
}

TLength &TLength::operator*=(const TReal factor)
{ // multiply a TLength object by a factor and rewrite this
	return *this = (*this) * factor;
}

/*TLength operator*=(const TReal factor, TLength &length )
{//multiply a TLength object by a factor and rewrite it
return length=factor*length;
}
*/

//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

TLength::ENumberSign TLength::sign(TReal number) const
{ // return the sign of the number entered

	ENumberSign sign;

	if (number / fabsq(number) < LITERAL(0.0))
	{
		sign = kNegative;
	}
	else if (number / fabsq(number) > LITERAL(0.0))
	{
		sign = kPositive;
	}
	else
	{
		sign = kZero;
	}

	return sign;
}
