// TDeciDegsFilter.cpp
//
// Concrete Class of the TAngleFilter PABC.
// Handles the IO of an TAngle object angles in a text stream with
// decimal degrees units.
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TTStreamFormatter object.
//
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

#include "TAngle.h"
#include "TDeciDegsFilter.h"
#include "TObservationFormat.h"
#include "TPointFormat.h"

//////////////////////////////////////////////////////////////////////

// ClassImp(TDeciDegsFilter)

//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
TDeciDegsFilter *TDeciDegsFilter::fFilter = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TDeciDegsFilter::TDeciDegsFilter()
{
}

TDeciDegsFilter::~TDeciDegsFilter()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TDeciDegsFilter *TDeciDegsFilter::instance()
{
	if (fFilter == nullptr)
	{
		fFilter = new TDeciDegsFilter;
	}

	return fFilter;
}

void TDeciDegsFilter::input(TAStreamFormatter &iStream, TAngle &angle) const
{ // function to get a decimal degrees angle from a QTextStream object
	// and set the value in a TAngle object
	TReal deciDegs;

	iStream.skipWhiteSpace();
	if (iStream.peek() == '\n')
	{ // check if there's coordinate to read
		angle.setDeciDegsValue(NO_VALf);
		iStream.setError("No angle value to read");
	}

	else
	{
		iStream >> deciDegs;
		if (!(iStream.fail()))
			angle.setDeciDegsValue(deciDegs);
		else
		{
			angle.setDeciDegsValue(NO_VALf);
			// make iStream's flags to "goodbit"
			iStream.clear();
			// read the wrong decimal degrees value
			while (iStream.peek() != ' ' && iStream.peek() != '\n')
			{
				iStream.readChar();
			}
			iStream.setError("Invalid angle value");
		}
	}

	return;
}

/////////////////////////////////////////////////////////
// outputs an angle formatted in decimal degrees units to the stream
/////////////////////////////////////////////////////////
void TDeciDegsFilter::output(TAStreamFormatter &oStream, const TAngle &angle) const
{ // function to put a decimal degree angle to a QTextStream object.
	// Gets the value from a TAngle object

	oStream.setf(std::ios::fixed, std::ios::floatfield);
	oStream.width(oStream.getWidthFormat());
	oStream.precision(oStream.getPrecisionFormat());

	// provisoire
	TAngle a(angle);
	if (a.getRadiansValue() < LITERAL(0.0))
		a += (2.0 * TAngle::pi());

	oStream << a.getDeciDegsValue();

	return;
}

//////////////////////////////////////////////////////////////////////
// End
//////////////////////////////////////////////////////////////////////
