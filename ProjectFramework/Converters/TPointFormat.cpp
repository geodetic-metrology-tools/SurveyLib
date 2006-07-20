// TPointFormat.cpp
//
/** Class used by a text stream to store and get all necessary formatting information*/
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TPointFormat.h"

////////////////////////////////////////////////////////////////


//ClassImp(TPointFormat)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TPointFormat::TPointFormat()
{//default constructor

	fNameWidth = 10;
	fCoordWidth = 12;
	fCoordPrecision = k100Micrometres;
	fCoordErrorWidth = 6;
	fCoordErrorPrecision =  k100Micrometres;
	fShowSign = false;
	fStatus = TSpatialStatus::kCala;
}


TPointFormat::TPointFormat(int nameWidth, int coordWidth, ECoordPrecision coordPrecision, 
						   int coordErrorWidth, ECoordPrecision coordErrorPrecision,
						   bool showSign, TSpatialStatus::ESpatialStatus status):
fNameWidth(nameWidth), fCoordWidth(coordWidth), fCoordPrecision(coordPrecision),
fCoordErrorWidth(coordErrorWidth), fCoordErrorPrecision(coordErrorPrecision),
fShowSign(showSign), fStatus(status)
{//constructor	

}


TPointFormat::TPointFormat( const  TPointFormat& source )
{//copy constructor	
	(*this) = source;
}


TPointFormat::~TPointFormat()
{//destructor
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TPointFormat&  TPointFormat::operator=(const TPointFormat& source)
{// copy assignement operator	

	if (this != &source)
	{
		fNameWidth = source.fNameWidth;
		fCoordWidth = source.fCoordWidth;
		fCoordPrecision = source.fCoordPrecision;
		fCoordErrorWidth = source.fCoordErrorWidth;
		fCoordErrorPrecision = source.fCoordErrorPrecision;
		fShowSign = source.fShowSign;
		fStatus = source.fStatus;
	}
	return *this;
}

void  TPointFormat::setSpatialStatus(const TSpatialStatus::ESpatialStatus status)
{// copy assignement operator	

	fStatus = status;

	return;
}

///////////////////////////////////
// returns the coordinate precision
///////////////////////////////////
TPointFormat::ECoordPrecision TPointFormat::getCoordPrecision() const{

	return fCoordPrecision;
}

/////////////////////////////////////////
// returns the coordinate error precision
/////////////////////////////////////////
TPointFormat::ECoordPrecision TPointFormat::getCoordErrorPrecision() const{

	return fCoordErrorPrecision;
}




