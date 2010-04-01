//  TMLA2LATransformation.cpp
//
/** The transformation from a modified local astronomical reference frame to a 
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
#include  "TLA2MLATransformation.h"
#include  "TMLA2LATransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TMLA2LATransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMLA2LATransformation::TMLA2LATransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TMLA2LATransformation::TMLA2LATransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TMLA2LATransformation::TMLA2LATransformation( const  TMLA2LATransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TMLA2LATransformation::~TMLA2LATransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TMLA2LATransformation&  TMLA2LATransformation::operator=(const TMLA2LATransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TMLA2LATransformation::clone() const
{
	return new TMLA2LATransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TMLA2LATransformation::inverse() const
{
	return new TLA2MLATransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TMLA2LATransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TMLA2LATransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TMLA2LATransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TMLA2LATransformation::initialise()
{
	// establish the transformation from the local astronomical system to the 
	// modified local astronomical system

	// get the orientation vector and FalseOrigin
	TSpatialOrientation  orient = getSourceFrame()->getOrientation();
	TTranslation  translation = getSourceFrame()->getFalseOrigin();

	// change the orientation to the Local Astronomical reference frame
	orient.transform( getDestinationFrame() );

	// set the rotation
	TAngle defaut(0);
	TZAxisRotation  rotn(defaut - orient.bearing() );

	// set the Helmert Transformation
	fTransform = new THelmertTransformation( rotn, translation );
	fTransform->invert();
	
	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

