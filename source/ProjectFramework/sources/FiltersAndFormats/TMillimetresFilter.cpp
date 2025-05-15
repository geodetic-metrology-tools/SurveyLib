// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿// TMillimetresFilter.cpp
//
// Concrete Class of the TLengthFilter PABC.
// Handles the IO of an TLength object lengths in a text stream with 
// millimetre units. 
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
#include <iostream>

#include  "TLength.h"
#include "TObservationFormat.h"
#include "TPointFormat.h"
#include  "TMillimetresFilter.h"
//////////////////////////////////////////////////////////////////////


//ClassImp(TMillimetresFilter)



//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
TMillimetresFilter *TMillimetresFilter::fFilter = 0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMillimetresFilter::TMillimetresFilter()
{}

TMillimetresFilter::~TMillimetresFilter()
{}



//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TMillimetresFilter *TMillimetresFilter::instance()
{	// get the instance of a TMillimetresFilter
	if( fFilter == nullptr )
	{
		fFilter = new TMillimetresFilter;
	}

	return fFilter;
}


void	TMillimetresFilter::input(TAStreamFormatter& iStream, TLength& length)const
{	// function to get a millimetre length from a QTextStream object
	// and set the value in a TLength object
	TReal	lenVal;

	iStream >> lenVal;
	if(!(iStream.fail()))
	{
		length.setMMetresValue(lenVal);
	}
	else
	{
		length.setMMetresValue(NO_VALf);
		iStream.clear();
			
		while(iStream.peek()!=' ' && iStream.peek()!='\n')
		{
			iStream.readChar();
		}
	}
	
	return;
}


void	TMillimetresFilter::output(TAStreamFormatter& oStream, const TLength& length)const
{	// function to put a millimetre length to a QTextStream object.
	// Gets the value from a TLength object



	int precision;
	precision = oStream.getPrecisionFormat();

	if (precision <=3)
		{
			precision = 0;
		}
	else
		{
			precision -=3;
		}
	

	oStream.setf(std::ios::fixed, std::ios::floatfield);
	oStream.width(oStream.getWidthFormat());
	oStream.precision(precision);
	oStream<<right;
	oStream <<length.getMMetresValue();
	
	return;
}

//////////////////////////////////////////////////////////////////////
// End 
//////////////////////////////////////////////////////////////////////

