// TAngle.h
/*!
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

#if !defined(SU_ANGLE)
#define SU_ANGLE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include    <iostream>
#include	<float.h>
#if __INTEL_COMPILER
#include	<mathimf.h>
#else
#include <math.h>
#endif
#include	<assert.h>
//
#include  "TANumericValue.h"
class TDouble;
using namespace std;
// typedefs
typedef	real	AngleValue;		// the value for the angle
typedef	int		Degrees;		// the degrees of an angle
typedef	int		Minutes;		// the minutes of an angle
typedef	real	Seconds;		// the seconds of an angle
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//!  The TAngle class represents a mathematical angle value.
class	TAngle  : public  TANumericValue //: public TObject
{

public:
	/*!@name Enumerators and Constants */
	//@{
	/*! Enumeration of the possible angular units */
	enum			EUnits {kRadians, kGons, k100MicroGons, kDMS}; 
	//@}
	
	/*!@name constructors and destructors */
	//@{
	/*! Default constructor */
	TAngle();
	/*! Explicit constructor taking an angle value in radians */
	explicit  TAngle(AngleValue);
	//TAngle(AngleValue);
	/*! Destructor */
	virtual	~TAngle();
	/*! Copy contructor */
	TAngle(const TAngle&);
	//@}


	/*!@name static member functions */
	//@{
	/*! Defines the angle Pi */ 
	static const TAngle pi();
	/*! Defines the angle 2xPi */
	static const TAngle twoPi();
	/*! Defines the angle Pi/2 */
	static const TAngle piBy2();
	/*! Defines the angle Pi/4 */
	static const TAngle piBy4();
	/*! Provides a scale factor to convert from angles in radians to angles in gons */
	static const real  radsToGonsFactor();	
	/*! Provides a scale factor to convert from angles in gons to angles in radians */
	static const real  gonsToRadsFactor();
	/*! Provides a scale factor to convert from angles in radians to angles in degres */
	static const real  radsToDecDegsFactor();
	/*! Provides a scale factor to convert from angles in degres to angles in radians */
	static const real  decDegsToRadsFactor();
	//@}
	
	
	/*!@name Setting methods */
	//@{
	/*! Sets the angle value in radians */
	bool setRadiansValue( AngleValue );
	/*! Sets the angle value in gons */
	bool setGonsValue( AngleValue );
	/*! Sets the angle value in degre, minutes, seconds */
	bool setDMSValue( Degrees, Minutes, Seconds );
	//@}

	/*!@name Access methods  */
	//@{
	/*! Gets the angle value in rads */
	AngleValue getRadiansValue() const;
	/*! Gets the angle value in gons */
	AngleValue getGonsValue() const;
	/*! Gets the angle value in CC (100 microgons) */
	AngleValue getSignedCCValue() const;
	/*! Gets part of the angle value in degs */
	Degrees	getDegreesValue() const;
	/*! Gets part of the angle value in min */
	Minutes	getMinutesValue() const;
	/*! Gets part of the angle value in sec */
	Seconds	getSecondsValue() const;
	//@}

	/*!@name Algebraic operators */
	//@{
	/*! Copy assignement operator */
	virtual bool operator==(const TAngle& ) const;
	/*! Less than operator */
	virtual bool operator<(const TAngle& ) const;
	/*! Adds 2 TAngles */
	TAngle operator+(const TAngle &) const;
	/*! Substract 2 TAngles */
	TAngle operator-(const TAngle &) const;
	/*! Multiplies a TAngle by a scale factor */
	TAngle operator*(const real ) const;
	/*! Multiplies a TAngle by a TDouble scale factor */
	TAngle operator*(const TDouble& ) const;
	/*! div. a TAngle by a TAngle*/
	TDouble operator/(const TAngle& ) const;
	/*! Multiplies a TAngle by a scale factor */
	friend  TAngle operator*(const real, const TAngle & );
	/*! Assigns a TAngle to an other */
	TAngle& operator=(const TAngle &);
	/*! Adds a TAngle to the angle */
	TAngle& operator+=(const TAngle &);
	/*! Substracts a TAngle from the angle */
	TAngle& operator-=(const TAngle &);
	/*! Multiplies the angle by a scale factor */
	TAngle& operator*=(const real );
	/*! Multiplies the TAngle by a TDouble scale factor */
	TAngle& operator*=(const TDouble &);

	/*!@name trigonometric functions */
	//@{
	/*! Calculates the cosine of the angle, for example: angle.Cos() = cosq(angle) */
	real cosine() const;
	/*! Calculates the sine of the angle */
	real sine() const;
	/*! Calculates the tangent of the angle */
	real tangent() const;
	/*! Calculates the hyperbolic cosine of the angle */
	real cosineh() const;
	/*! Calculates the hyperbolic sine of the angle */
	real sineh() const;
	/*! Calculates the hyperbolic tangent of the angle */
	real tangenth() const;
	/*! Calculates the arccosine of a real as a TAngle */
	static TAngle aCos(const real);
	/*! Calculates the arcsine of a real as a TAngle */
	static TAngle aSin(const real);
	/*! Calculates the arctan of a real as a TAngle */
	static TAngle aTan(const real);
	/*! Calculates the arctan(x/y) as a TAngle */
	static TAngle aTan2(const real, const real);
	//@}

private:

	/*! Enumeration indicating the sign of an angle value */
	enum			ENumberSign {kNegative=-1, kZero, kPositive}; 

	/*!@name angle conversion multiplication factors */
	//@{
	static const real	kPi; /*!< pi */
	static const real	kRadiansToGons; /*!< convertion rad->gon factor */
	static const real	kGonsToRadians; /*!< convertion gon->rad factor */
	static const real	kRadiansToDecDegs; /*!< convertion rad->deg factor */
	static const real	kDecDegsToRadians; /*!< convertion deg->rad factor */
	static const real	seuil;
	//@}

	/*! normalise the angle value to lie between -2Pi and +2Pi */
	void normaliseAngle();
	
	/*! return the sign of a real number */
	ENumberSign		sign(real	number) const;	

private:	
	AngleValue		fValue;		/*!< Angle value, default = LITERAL(0.0) */
	
	//ClassDef(TAngle, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


inline AngleValue	TAngle::getRadiansValue() const
{	// get the radians angular value for the angle
	return fValue;
}


inline AngleValue	TAngle::getGonsValue() const
{	// get the gons angular value for the angle
	// return the converted angular value
	/*modification du 08/05/2003,
	getRadiansValue() donne les angles entre -pi et pi
	getGonsValue() donne les angles entre 0 et 2pi*/
	AngleValue gValue = fValue;
	while (gValue < 0)
	{
		gValue += LITERAL(2.0) * kPi;
	}
	while (gValue >= LITERAL(2.0) * kPi - seuil)
	{
		gValue -= LITERAL(2.0) * kPi;
	}
	if (gValue < 0)
	{
		gValue = 0;
	}
	return (gValue * kRadiansToGons);
}


inline AngleValue	TAngle::getSignedCCValue() const
{	// get the CC (100 microgons) angular value for the angle
	return fValue * kRadiansToGons * 10000;
}


inline Degrees	TAngle::getDegreesValue() const
{	// get the integer degrees of the angular value 
	return Degrees(fValue * kRadiansToDecDegs);
}


#endif // !defined(SU_ANGLE)

