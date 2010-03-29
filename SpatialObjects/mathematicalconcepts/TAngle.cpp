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

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include	"TAngle.h"
#include	"TDouble.h"
////////////////////////////////////////////////////////////////



//ClassImp(TAngle)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////

const real	TAngle::kPi = acosq(-LITERAL(LITERAL(1.0)));  // Pi = LITERAL(LITERAL(3.14159265358979323844));
const real	TAngle::kRadiansToGons = LITERAL(LITERAL(200.0))/kPi;
const real	TAngle::kGonsToRadians = kPi/LITERAL(LITERAL(200.0));
const real	TAngle::kRadiansToDecDegs = LITERAL(LITERAL(180.0))/kPi;
const real	TAngle::kDecDegsToRadians = kPi/LITERAL(LITERAL(180.0));
const real	TAngle::seuil = LITERAL(LITERAL(0.00000000001));


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TAngle::TAngle() : fValue(LITERAL(LITERAL(0.0)))
{	// default constructor
	setStatus( TANumericValue::kNull );
}


TAngle::TAngle(const AngleValue value)
{	// constructor taking a given angle value in radians
	this->setRadiansValue(value);
	setStatus( TANumericValue::kKnown );
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
// Static Member Functions (multiples de pi comme TAngle)
//////////////////////////////////////////////////////////////////////

 
const TAngle TAngle::pi()
{	// Defines the angle Pi
	TAngle pi(kPi);
	return pi;
}


const TAngle TAngle::twoPi()
{   // Defines the angle 2*Pi 
	TAngle twoPi(LITERAL(LITERAL(2.0))*kPi);
	return twoPi;
}


const TAngle TAngle::piBy2()
{   // Defines the angle Pi/2
	TAngle piBy2(kPi/LITERAL(LITERAL(2.0)));
	return piBy2;
}


const TAngle TAngle::piBy4()
{   // Defines the angle Pi/4
	TAngle piBy4(kPi/LITERAL(LITERAL(4.0)));
	return piBy4;
}


const real  TAngle::radsToGonsFactor()
{   // Provides a scale factor to convert from angles 
	//in radians to angles in gons
	return  kRadiansToGons;
}


const real  TAngle::gonsToRadsFactor()
{   // Provides a scale factor to convert from angles 
	// in gons to angles in radians
	return  kGonsToRadians;
}


const real  TAngle::radsToDecDegsFactor()
{   // Provides a scale factor to convert from angles 
	// in radians to angles in decimal degrees
	return  kRadiansToDecDegs;
}


const real  TAngle::decDegsToRadsFactor()
{   // Provides a scale factor to convert from angles 
	// in decimal degrees to angles in radians
	return  kDecDegsToRadians;
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

void TAngle::normaliseAngle()
{
	//modification du 08/05/2003 pour le calcul les angles seront exprimes entre -pi et pi

	while (fValue > kPi - seuil)
	{
		fValue -= LITERAL(LITERAL(2.0)) * kPi;
	}
	while (fValue < -kPi + seuil)
	{
		fValue += LITERAL(LITERAL(2.0)) * kPi;
	}
}


bool	TAngle::setRadiansValue(const AngleValue value)
{	// set the angle value to the given radians value
		
	fValue = value;
	
	//normalise the radians value
	normaliseAngle();			

	valueSet();

	return true;
}



bool	TAngle::setGonsValue(const AngleValue value)
{	// set the angle value to the given gons value
	
	// convert the given value to radians
	fValue = value * kGonsToRadians;

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
	fValue = angleSign * (real(absDegs) + ((real(absMins))/LITERAL(LITERAL(60.0))) + (absSecs/LITERAL(LITERAL(3600.0)))) * kDecDegsToRadians;

	//normalise the radians value
	normaliseAngle();

	valueSet();

	return true;
}



Minutes	TAngle::getMinutesValue() const
{	// get the integer minutes of the angular value
	
	real	decDegs;
	real	degs;
	real	decMins;
	
	// determine the degrees and minutes values
	decDegs = fValue * kRadiansToDecDegs; 
#if _DEBUG && __INTEL_COMPILER
	decMins = LITERAL(LITERAL(60.0))*modfq(decDegs, degs);	// if the decimal degrees are negative
										// BOTH the degrees and minutes will be negative
#else
	decMins = LITERAL(LITERAL(60.0))*modfq(decDegs, &degs);	// if the decimal degrees are negative
										// BOTH the degrees and minutes will be negative
#endif

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
	
	real	decDegs;
	real	degs;
	real	decMins;
	real	mins;
	real	seconds;

	// determine the degrees, minutes, and seconds values
	decDegs = fValue * kRadiansToDecDegs; 
#if _DEBUG && __INTEL_COMPILER
	decMins = LITERAL(LITERAL(60.0))*modfq(decDegs, degs);	// if the decimal degrees are negative
										// BOTH the degrees and minutes will be negative
	seconds = LITERAL(LITERAL(60.0))*modfq(decMins, mins);	// if the decimal minutes are negative
										// BOTH the minutes and seconds will be negative
#else
	decMins = LITERAL(LITERAL(60.0))*modfq(decDegs, &degs);	// if the decimal degrees are negative
										// BOTH the degrees and minutes will be negative
	seconds = LITERAL(LITERAL(60.0))*modfq(decMins, &mins);	// if the decimal minutes are negative
										// BOTH the minutes and seconds will be negative
#endif

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
		if (a.getRadiansValue() < LITERAL(LITERAL(0.0))) { a += (2 * pi()); }
		if (this->getRadiansValue() < LITERAL(LITERAL(0.0))) { (*this) += (2 * pi()); }
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

	
TAngle TAngle::operator*(const real factor) const
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
		if(div.getRadiansValue() != LITERAL(LITERAL(0.0)))
		{
			resultat.setValue(this->getRadiansValue()/div.getRadiansValue());
		}
		else
		{
			resultat.setValue(LITERAL(LITERAL(0.0)));
			status = kNull;
		}
	}
	resultat.setStatus(status);
	return resultat;
}


TAngle	operator*(const real factor, const TAngle &angle )
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


TAngle& TAngle::operator*=(const real factor)
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

real TAngle::cosine() const
{//cosine of the angle
	return cosq(this->getRadiansValue());
}


real TAngle::sine() const
{//sine of the angle
	return sinq(this->getRadiansValue());
}


real TAngle::tangent() const
{//tangent of the angle
	return tanq(this->getRadiansValue());
}


real TAngle::cosineh() const
{//hyperbolic cosine of the angle
	return coshq(this->getRadiansValue());
}


real TAngle::sineh() const
{//hyperbolic sine of the angle
	return sinhq(this->getRadiansValue());
}


real TAngle::tangenth() const
{//hyperbolic tangent of the angle
	return tanhq(this->getRadiansValue());
}

TAngle TAngle::aCos(const real x)
{//determines the arccosine of a real as a TAngle
	if (-LITERAL(LITERAL(1.0))>x  ||  x>LITERAL(LITERAL(1.0))) throw "incorrect value";

	TAngle angle(acosq(x));
	return angle;
}


TAngle TAngle::aSin(const real x)
{//determines the arcsine of a real as a TAngle
	if (-LITERAL(LITERAL(1.0))>x  ||  x>LITERAL(LITERAL(1.0))) throw "incorrect value";

	TAngle angle(asinq(x));
	return angle;
}


TAngle TAngle::aTan(const real x)
{//determines the arctan of a real as a TAngle
	TAngle angle(atanq(x));
	return angle;
}


TAngle TAngle::aTan2(const real x, const real y)
{//determines the arctan(x/y) as a TAngle
	TAngle angle(atan2q(x, y));
	return angle;
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////


	
TAngle::ENumberSign		TAngle::sign(real	number) const
{	// return the sign of the number entered

	ENumberSign	sign;

	// divide the real by its absolute value
	// the result should be -1, or 1, for numbers 
	// not equal to 0
	if(number / fabsq(number) < LITERAL(LITERAL(0.0)))
	{
		sign = kNegative;
	}
	else if (number / fabsq(number) > LITERAL(LITERAL(0.0)))
	{
		sign = kPositive;
	}
	else
	{
		sign = kZero;
	}

	return sign;
}

