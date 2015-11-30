// TLength.cpp
//
// Class for a length 
//
//include math operators +, -, *factor, =.
//
//
// Copyright 1999,2000, Mark Jones, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////

#include	"TLength.h"
#include	"TDouble.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TLength::TLength(): fValue(LITERAL(0.0))
{	// default constructor 
	setStatus( TANumericValue::kNull );
}

TLength::TLength(TReal value, EUnits unit)
{	// constructor taking a given length value in metres
   
   switch(unit)
   {
      case EUnits::kMetres:      setMetresValue(value); break;
      case EUnits::kMillimetres: setMMetresValue(value); break;
      case EUnits::kKilometres:  setKMetresValue(value); break;
   }
   setStatus((value == std::numeric_limits<TReal>::quiet_NaN()) ? EStatus::kNull : EStatus::kKnown);
}

TLength::TLength(const TLength& tl)
{	// copy constructor
	fValue = tl.fValue;
	setStatus( tl.getStatus() );
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
bool TLength::operator==(const TLength& right) const{

	if ( getMetresValue() == right.getMetresValue())
		return true;
	else
		return false;
}

/////////////////////
// less than operator
/////////////////////
bool TLength::operator<(const TLength& right) const
{
	if ( getMetresValue() < right.getMetresValue())
		return true;
	else
		return false;
}


TLength TLength::operator+(const TLength &length1)
{//add two TLength objects
	TLength resultat;
	TANumericValue::EStatus status;
	status=this->testStatus(length1);
	if (status!= kNull)
	{resultat.setMetresValue(this->getMetresValue()+length1.getMetresValue());}
	resultat.setStatus(status);
	return resultat;
}



TLength TLength::operator-(const TLength &length1)
{//substract two TLength objects
	TLength resultat;
	TANumericValue::EStatus status;
	status=this->testStatus(length1);
	if (status!= kNull)
	{resultat.setMetresValue(getMetresValue()-length1.getMetresValue());}
	resultat.setStatus(status);
	return resultat;
}	


TReal TLength::operator/(const TLength& div)
{// Multiplies a TLength by a TDouble scale factor

   return (div.getMetresValue() != 0) ? (this->getMetresValue() / div.getMetresValue()) : 0;
}

TLength	TLength::operator*(const TReal factor)
{//multiply a TLength object by a factor
   return TLength (factor*this->getMetresValue());
}	

TLength	operator*(const TReal factor, const TLength &length )
{//multiply a TLength object by a factor
	TLength resultat;
	if(length.isNull()!=true)
	{resultat.setMetresValue(factor*(length.getMetresValue()));}
	resultat.setStatus(length.getStatus());
	return resultat;
}

TLength& TLength::operator=(const TLength &length)
{//assign a TLength object to an other
	if (this != &length) 
	{
		fValue=(length.getMetresValue());
		setStatus( length.getStatus() );
	}

	return *this;
}


TLength& TLength::operator+=(const TLength &length)
{//add two TLength objects and rewrite this
return *this=*this+length;
}


TLength& TLength::operator-=(const TLength &length)
{//substract two TLength objects and rewrite this
return *this=*this-length;
}


TLength& TLength::operator*=(const TReal factor)
{//multiply a TLength object by a factor and rewrite this
   return *this=(*this)*factor;
}

/*TLength operator*=(const TReal factor, TLength &length )
{//multiply a TLength object by a factor and rewrite it
return length=factor*length;
}
*/

//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

	
TLength::ENumberSign		TLength::sign(TReal	number) const
{	// return the sign of the number entered

	ENumberSign	sign;

	if(number / fabsq(number) < LITERAL(0.0))
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

