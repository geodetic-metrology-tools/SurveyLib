// TAngle.cpp
/*
The TAngle class represents a mathematical angle value.

The angle may be set with a numerical value in radians, gons or 
DMS (sexagesimal), likewise the value may be obtained in any of 
these units.
 
Angular values are normalised to ensure they lie be between
-2Pi and 2Pi radians (or the equivalent for other angular units).

The class also provides access to a number of different constants
through static member functions:

    -Multiples of Pi;
	-Factors for conversion between angle units.

A set of algebraic operators for angles enable angles to be added,
subtracted, and scaled. Trigonometrical operators enable the sine,
cosine and tangent of the angle value to be obtained, and static 
member functions provide ArcSine, ArcCosine, and ArcTangent operators.
 
Patterns:

 
Copyright 1999-2002, Mark Jones, EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////

// other forward declarations
#include "TAngle.h"
#include "TDouble.h"
////////////////////////////////////////////////////////////////

namespace {
// wraps an angle to the range [-pi,pi]
inline TReal wrapAngle( TReal angle )
{
	return (angle - TWOPI * floor( angle / TWOPI ))-PI;
}
}


//ClassImp(TAngle)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TAngle::TAngle() : fValue(LITERAL(0.0))
{	// default constructor
	setStatus( TANumericValue::kNull );
}


TAngle::TAngle(const TReal value, EUnits unit)
{	// constructor taking a given angle value in radians

   switch(unit)
   {
      case EUnits::kRadians:     setRadiansValue(value); break;
      case EUnits::kGons:        setGonsValue(value); break;
      case EUnits::kCCs:         setGonsValue(value*CC2GON); break;
      case EUnits::k100MicroGons:setGonsValue(value*CC2GON); break;
   }
   setStatus((value == std::numeric_limits<TReal>::quiet_NaN()) ? EStatus::kNull : EStatus::kKnown);
}


TAngle::~TAngle()
{
}

TAngle::TAngle(const TAngle& angle)
{
	fValue=angle.fValue;
	setStatus( angle.getStatus() );
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

void TAngle::normaliseAngle()
{
    while (fValue > PI - seuil())
    {
        fValue -= TWOPI;
    }
    while (fValue < -PI + seuil())
    {
        fValue += TWOPI;
    }
}


bool	TAngle::setRadiansValue(const TReal value)
{	// set the angle value to the given radians value
		
	fValue = value;
	
	//normalise the radians value
	normaliseAngle();			

	valueSet();

	return true;
}



bool	TAngle::setGonsValue(const TReal value)
{	// set the angle value to the given gons value
	
	// convert the given value to radians
	fValue = value * GON2RAD;

	//normalise the radians value
	normaliseAngle();
	
	valueSet();

	return true;
}



bool	TAngle::setDMSValue(const	Degrees	degs, 
							const	Minutes	mins, 
							const	Seconds	secs)
{	// set set the angle value to the given degrees, minutes, seconds value
	
	Degrees	absDegs;
	Minutes	absMins; 
	Seconds	absSecs;
	ENumberSign		angleSign;

	absDegs = abs(degs);
	absMins = abs(mins);
	absSecs = fabsq(secs);
	
	// check the sign of the angle entered
	if(degs >= 0  &&  mins >= 0  &&  secs >= 0 ) 
	{	// all three elements are positive
		angleSign = kPositive;
	}
	else if ((degs < 0  &&  (mins >= 0  &&  secs >=0))  // degrees are negative
				||  (mins < 0  &&  (degs == 0  &&  secs >=0))  // degrees are zero, minutes negative
				||  (secs < 0  &&  (degs == 0  &&  mins == 0)))  // degrees and minutes are zero, seconds negative
	{   // one element is negative
		angleSign = kNegative;
	}
	else if (degs == 0  &&  mins == 0  &&  (-DBL_EPSILON < secs  &&  secs < DBL_EPSILON))
	{	// all elements are zero

		angleSign = kZero;
	}
	else
	{	
		return false;
	}


	// convert the given values to radians
    fValue = angleSign * (TReal(absDegs) + ((TReal(absMins))/LITERAL(60.0)) + (absSecs/LITERAL(3600.0))) * DEG2RAD;

	//normalise the radians value
	normaliseAngle();

	valueSet();

	return true;
}



Minutes	TAngle::getMinutesValue() const
{	// get the integer minutes of the angular value
	
	TReal	decDegs;
	TReal	degs;
	TReal	decMins;
	
	// determine the degrees and minutes values
    decDegs = fValue * RAD2DEG; 
	decMins = LITERAL(60.0)*modfq(decDegs, &degs);	// if the decimal degrees are negative
										// BOTH the degrees and minutes will be negative

	// determine the minutes value with the appropriate sign
	if (int(degs) == 0)
	{	// degrees zero, so minutes can have a sign
		return Minutes(decMins);
	}
	else
	{	// degrees non-zero, so minutes must be positive
		return abs(Minutes(decMins));
	}
}



Seconds	TAngle::getSecondsValue() const
{	// get the decimal seconds of the angular value
	
	TReal	decDegs;
	TReal	degs;
	TReal	decMins;
	TReal	mins;
	TReal	seconds;

	// determine the degrees, minutes, and seconds values
    decDegs = fValue * RAD2DEG; 
	decMins = LITERAL(60.0)*modfq(decDegs, &degs);	// if the decimal degrees are negative
										// BOTH the degrees and minutes will be negative
	seconds = LITERAL(60.0)*modfq(decMins, &mins);	// if the decimal minutes are negative
										// BOTH the minutes and seconds will be negative

	// return the seconds value with the appropriate sign
	if (int(degs) == 0  &&  int(mins) == 0)
	{	// degrees and minutes zero, so seconds can have a sign
		return seconds;
	}
	else
	{	// degrees or minutes non-zero, so seconds must be positive
		return fabsq(seconds);
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////
// Operators
/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////
// equality operator
////////////////////
bool TAngle::operator==(const TAngle& right) const{

	if (getRadiansValue() == right.getRadiansValue())
		return true;
	else
		return false;
}

/////////////////////
// less than operator
/////////////////////
bool TAngle::operator<(const TAngle& right) const{

	if (getRadiansValue() < right.getRadiansValue())
		return true;
	else
		return false;
}



TAngle TAngle::operator+(const TAngle &angle) const
{// Adds another angle to the angle and returns the result	
	TAngle resultat;
	TANumericValue::EStatus status;
	status=this->testStatus(angle);
	if (status!= kNull)
	{
		resultat.setRadiansValue(this->getRadiansValue() + angle.getRadiansValue());
		//resultat.setGonsValue(this->getGonsValue() + angle.getGonsValue());
	}
	resultat.setStatus(status);
	return resultat;
}


TAngle TAngle::operator-(const TAngle &angle) const
{// Subtracts another angle from the angle and returns the result
	TAngle resultat;
	TANumericValue::EStatus status;
	status=this->testStatus(angle);
	if (status!= kNull)
	{
/*		TAngle a(angle);
		if (a.getRadiansValue() < LITERAL(0.0)) { a += (2 * pi()); }
		if (this->getRadiansValue() < LITERAL(0.0)) { (*this) += (2 * pi()); }
		if (((a.getRadiansValue()) < pi().getRadiansValue()) && ((this->getRadiansValue()) >= pi().getRadiansValue()))
		{
			resultat.setRadiansValue((this->getRadiansValue() - a.getRadiansValue()) - 2 * pi().getRadiansValue());
		}

		else if (a.getRadiansValue() >= pi().getRadiansValue() && this->getRadiansValue() < pi().getRadiansValue())
		{
			resultat.setRadiansValue((this->getRadiansValue() - a.getRadiansValue()) + 2 * pi().getRadiansValue());
		}
		
		else
		{
			resultat.setRadiansValue(this->getRadiansValue() - a.getRadiansValue());
		}*/

		resultat.setRadiansValue(this->getRadiansValue() - angle.getRadiansValue());
		//resultat.setGonsValue(this->getGonsValue()-angle.getGonsValue());
	}
	resultat.setStatus(status);
	return resultat;
}

	
TAngle TAngle::operator*(const TReal factor) const
{// Multiplies the angle by a scale factor
	TAngle resultat;
	if (isNull()!=true)
	{
		resultat.setRadiansValue(factor*(this->getRadiansValue()));
	}
	resultat.setStatus(getStatus());
	return resultat;
}


TAngle TAngle::operator*(const TDouble &factor) const
{// Multiplies a TAngle by a TDouble scale factor
	TAngle resultat;
	TANumericValue::EStatus status;
	status=this->testStatus(factor);
	if (status!= kNull)
	{	
		resultat.setRadiansValue(this->getRadiansValue()*factor.getValue());
	}
	resultat.setStatus(status);
	return resultat;
}


TDouble TAngle::operator/(const TAngle& div) const
{// Multiplies a TAngle by a TDouble scale factor
	TDouble resultat;
	TANumericValue::EStatus status;
	status=this->testStatus(div);
	if (status!= kNull)
	{	
		if(div.getRadiansValue() != LITERAL(0.0))
		{
			resultat.setValue(this->getRadiansValue()/div.getRadiansValue());
		}
		else
		{
			resultat.setValue(LITERAL(0.0));
			status = kNull;
		}
	}
	resultat.setStatus(status);
	return resultat;
}


TAngle operator*(const TReal factor, const TAngle &angle )
{// Multiplies a TAngle by a scale factor
	TAngle resultat;
	if (angle.isNull()!=true)
	{
		resultat.setRadiansValue(angle.getRadiansValue() * factor);
	}
	resultat.setStatus(angle.getStatus());
	return resultat;
}



TAngle&	TAngle::operator=(const TAngle &angle)
{// assigns a TAngle to the angle
	if (this != &angle) 
	{
		fValue=(angle.getRadiansValue());
		setStatus( angle.getStatus() );
	}
	return *this;
}


TAngle& TAngle::operator+=(const TAngle &angle)
{// adds a TAngle to the angle
return (*this)=(*this)+angle;
}


TAngle& TAngle::operator-=(const TAngle &angle)
{// subtracts a TAngle from the angle
return (*this)=(*this)-angle;
}


TAngle& TAngle::operator*=(const TReal factor)
{// Multiply the angle by a scale factor
return (*this)=(*this)*factor;
}

TAngle& TAngle::operator*=(const TDouble& factor)
{// Multiply this angle by a scale factor
return (*this)=(*this)*factor;
}


//////////////////////////////////////////////////////////////////////
// trigonometric functions
//////////////////////////////////////////////////////////////////////

TReal TAngle::cosine() const
{//cosine of the angle
	return cosq(this->getRadiansValue());
}


TReal TAngle::sine() const
{//sine of the angle
	return sinq(this->getRadiansValue());
}


TReal TAngle::tangent() const
{//tangent of the angle
	return tanq(this->getRadiansValue());
}


TReal TAngle::cosineh() const
{//hyperbolic cosine of the angle
	return coshq(this->getRadiansValue());
}


TReal TAngle::sineh() const
{//hyperbolic sine of the angle
	return sinhq(this->getRadiansValue());
}


TReal TAngle::tangenth() const
{//hyperbolic tangent of the angle
	return tanhq(this->getRadiansValue());
}

TAngle TAngle::aCos(const TReal x)
{//determines the arccosine of a TReal as a TAngle
	if (-LITERAL(1.0)>x  ||  x>LITERAL(1.0)) throw "incorrect value";

	TAngle angle(acosq(x));
	return angle;
}


TAngle TAngle::aSin(const TReal x)
{//determines the arcsine of a TReal as a TAngle
	if (-LITERAL(1.0)>x  ||  x>LITERAL(1.0)) throw "incorrect value";

	TAngle angle(asinq(x));
	return angle;
}


TAngle TAngle::aTan(const TReal x)
{//determines the arctan of a TReal as a TAngle
	TAngle angle(atanq(x));
	return angle;
}


TAngle TAngle::aTan2(const TReal x, const TReal y)
{//determines the arctan(x/y) as a TAngle
	TAngle angle(atan2q(x, y));
	return angle;
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////


	
TAngle::ENumberSign TAngle::sign(TReal	number) const
{	// return the sign of the number entered

	ENumberSign	sign;

	// divide the TReal by its absolute value
	// the result should be -1, or 1, for numbers 
	// not equal to 0
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

TReal	TAngle::getRadiansValue() const
{	// get the radians angular value for the angle
   return fValue;
}

TReal	TAngle::getGonsValue() const
{	// get the gons angular value for the angle
   // return the converted angular value
   /*modification du 08/05/2003,
   getRadiansValue() donne les angles entre -pi et pi
   getGonsValue() donne les angles entre 0 et 2pi*/
   TReal gValue = fValue;
   while(gValue < 0)
   {
      gValue += 2 * M_PI;
   }
   while(gValue >= 2 * M_PI - seuil())
   {
      gValue -= 2 * M_PI;
   }
   if(gValue < 0)
   {
      gValue = 0;
   }
   return (gValue * RAD2GON);
}

TReal	TAngle::getSignedCCValue() const
{	// get the CC (100 microgons) angular value for the angle
	return fValue * RAD2CC;
}

Degrees	TAngle::getDegreesValue() const
{	// get the integer degrees of the angular value 
   return Degrees(fValue * RAD2DEG);
}
