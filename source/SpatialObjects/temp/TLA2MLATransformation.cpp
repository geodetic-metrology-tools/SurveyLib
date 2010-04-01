//  TLA2MLATransformation.cpp
//
/** The transformation from a local astronomical reference frame to a modified
    local astronomical reference frame.
	
	The modified local astronomical system is a local astronomical system that 
	is subject to a rotation around the z-axis (local vertical) 
	and a translation of the origin.

    The orientation vector, and the false origin of the modified local astronomical 
	system define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TVReferenceFrame.h"
#include  "TSpatialOrientation.h"
#include  "TRotation.h"
#include  "THelmertTransformation.h"
#include  "TMLA2LATransformation.h"
#include  "TLA2MLATransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TLA2MLATransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLA2MLATransformation::TLA2MLATransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TLA2MLATransformation::TLA2MLATransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TLA2MLATransformation::TLA2MLATransformation( const  TLA2MLATransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TLA2MLATransformation::~TLA2MLATransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TLA2MLATransformation&  TLA2MLATransformation::operator=(const TLA2MLATransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TLA2MLATransformation::clone() const
{
	return new TLA2MLATransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TLA2MLATransformation::inverse() const
{
	return new TMLA2LATransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TLA2MLATransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TLA2MLATransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TLA2MLATransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TLA2MLATransformation::initialise()
{
	// establish the transformation from the local astronomical system to the 
	// modified local astronomical system

	// get the orientation vector and FalseOrigin
	TSpatialOrientation  orient( getDestinationFrame()->getOrientation() );
	TTranslation  translation( getDestinationFrame()->getFalseOrigin()->getXCoord(),getDestinationFrame()->getFalseOrigin()->getYCoord(),getDestinationFrame()->getFalseOrigin()->getZCoord() );

	// change the orientation to the Local Astronomical reference frame
	orient.transform( getSourceFrame() );

	// set the rotation
	TAngle defaut(0);
	TZAxisRotation  rotn( defaut - orient.bearing() );

	// set the Helmert Transformation
	fTransform = new THelmertTransformation( rotn, translation );
	
	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

