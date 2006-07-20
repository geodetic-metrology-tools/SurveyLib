// TFixedColFormatTStream.cpp
//
//
// Concrete class defining the normal "fixed column size" format file syntax,
// for example the file as used in Transform.
//
// Patterns:
// A concrete decorator class of a QTextStream.
// 
// Copyright 1999,2000 CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// Other forward declarations
#include  "TAngleFilter.h"
#include  "TLengthFilter.h"
#include  "TSpatialPositionFilter.h"
#include  "TFixedColFormatTStream.h"
#include  "TSpatialPoint.h"
#include  "TSpatialPointName.h"
#include  "TSpatialPosition.h"
///////////////#include  "TEuclideanRefFrame.h"
#include  "TPointFormat.h"
//#include  "QTextStream.h"
//////////////////////////////////////////////////////////////////////


//ClassImp(TFixedColFormatTStream)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TFixedColFormatTStream::TFixedColFormatTStream(TDataParameters& dp) : TAFixedColFormatTStream(dp)
{
/*	TEuclideanRefFrame* erf = new TEuclideanRefFrame("LocalTransform");
	setReferenceFrame(erf);*/
	//fCoordToken;
	//fCoorSys;
}

TFixedColFormatTStream::TFixedColFormatTStream(const string& str, TDataParameters& dp) : TAFixedColFormatTStream(str, dp)
{
/*	TEuclideanRefFrame* erf = new TEuclideanRefFrame("LocalTransform");
	setReferenceFrame(erf);*/
	//fCoordToken;
	//fCoorSys;
}


TFixedColFormatTStream::TFixedColFormatTStream(EIOType io, TADataSet& ds) : TAFixedColFormatTStream( io, ds)
{
/*	TEuclideanRefFrame* erf = new TEuclideanRefFrame("LocalTransform");
	setReferenceFrame(erf);*/
	//fCoordToken;
	//fCoorSys;
}


TFixedColFormatTStream::~TFixedColFormatTStream()
{
//	delete fStream;
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////



TAStreamFormatter  &TFixedColFormatTStream::operator>>( TSpatialPoint &point )
{	
	TSpatialPointName  name;
	TSpatialPosition*	position = new TSpatialPosition(fRefFrame);
	
	this->skipCommentLines();

	// get the point name
	this->TAStreamFormatter::operator >> (name);

	// get the point position
	this->TAStreamFormatter::operator >> (*position);

	position->setObjectStatus(TSpatialStatus::kVxyz);

	point.setName(name);
	point.setPosition( position );

	
	

	return *this;
}



TAStreamFormatter  &TFixedColFormatTStream::operator<<( const TSpatialPoint &point )
{	
// output the point name
	this->TAFixedColFormatTStream::operator<< (point.getName()); 
	(*fIOStream) << separator();

	// output the position
//	if ( (point.getPosition(getReferenceFrame()).getPositionStatus()) != TPositionStatus::kPosNull )
	TPositionVector pv (TCoordSysFactory::k3DCartesian);
	pv=point.getPosition(getReferenceFrame()).getCoordinates(TCoordSysFactory::k3DCartesian);
	
	if (pv.getStatus()!= TANumericValue::kNull)
	{
		this->TAFixedColFormatTStream::operator << (point.getPosition(getReferenceFrame()));
	}
	
	return *this;
}

//////////////////////////////////////////////////////////////////////



