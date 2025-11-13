// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TRadiansFilter.cpp
//
// Concrete Class of the TAngleFilter PABC.
// Handles the IO of an TAngle object angles in a text stream with 
// radian units. 
// 
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TTStreamFormatter object. 
//
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// Other forward declarations
#include "TAngle.h"
#include "TPointFormat.h"
#include "TObservationFormat.h"
#include "TRadiansFilter.h"
//////////////////////////////////////////////////////////////////////


//ClassImp(TRadiansFilter)



//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
TRadiansFilter *TRadiansFilter::fFilter = 0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TRadiansFilter::TRadiansFilter()
{}

TRadiansFilter::~TRadiansFilter()
{}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TRadiansFilter *TRadiansFilter::instance()
{
	if( fFilter == nullptr )
	{
		fFilter = new TRadiansFilter;
	}

	return fFilter;
}


void	TRadiansFilter::input(TAStreamFormatter& iStream, TAngle& angle)const
{	// function to get a radians angle from a QTextStream object
	// and set the value in a TAngle object
	TReal	rads;

	iStream.skipWhiteSpace();
	if(iStream.peek()=='\n')
	{//check if there's coordinate to read
		angle.setRadiansValue(NO_VALf);
		iStream.setError("No angle value to read");
	}

	else
	{
		iStream >> rads;
		if(!(iStream.fail()))
			angle.setRadiansValue(rads);
		else
		{
			angle.setRadiansValue(NO_VALf);
			//make iStream's flags to "goodbit"
			iStream.clear();
			//read the "wrong" gons
			while(iStream.peek()!=' ' && iStream.peek()!='\n')
			{
				iStream.readChar();
			}
			iStream.setError("Invalid angle value");
		}
	}

	return;
}

////////////////////////////////////////////////////////////
// outputs an angle formatted in radians units to the stream
////////////////////////////////////////////////////////////
void	TRadiansFilter::output(TAStreamFormatter& oStream,const TAngle& angle)const
{	// function to put a radians angle to a QTextStream object.
	// Gets the value from a TAngle object

	int width, precision;
	width = oStream.getPointFormat()->getCoordWidth();
	precision = oStream.getPointFormat()->getCoordPrecision();

	oStream.setf(std::ios::fixed, std::ios::floatfield);
	oStream.width(width);
	oStream.precision(precision);
	oStream<< angle.getRadiansValue();
	

	return;
}


//////////////////////////////////////////////////////////////////////
// End 
//////////////////////////////////////////////////////////////////////

