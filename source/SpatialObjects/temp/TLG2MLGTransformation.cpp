//  TLG2MLGTransformation.cpp
//
/** The transformation from a local geodetic reference frame to a modified
    local geodetic reference frame.
	
	The modified local geodetic system is a local geodetic system that 
	is subject to a rotation around the z-axis (ellipsoidal normal) 
	and a translation of the origin.

    The orientation vector, and the false origin of the modified local geodetic 
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
#include  "TMLG2LGTransformation.h"
#include  "TLG2MLGTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TLG2MLGTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLG2MLGTransformation::TLG2MLGTransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TLG2MLGTransformation::TLG2MLGTransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TLG2MLGTransformation::TLG2MLGTransformation( const  TLG2MLGTransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TLG2MLGTransformation::~TLG2MLGTransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TLG2MLGTransformation&  TLG2MLGTransformation::operator=(const TLG2MLGTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TLG2MLGTransformation::clone() const
{
	return new TLG2MLGTransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TLG2MLGTransformation::inverse() const
{
	return new TMLG2LGTransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TLG2MLGTransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TLG2MLGTransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TLG2MLGTransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TLG2MLGTransformation::initialise()
{
	// establish the transformation from the local geodetic system to the 
	// modified local geodetic system

	// get the orientation vector and FalseOrigin
	TSpatialOrientation  orient = getDestinationFrame()->getOrientation();
	TTranslation  translation = getDestinationFrame()->getFalseOrigin();

	// change the orientation to the Local Geodetic reference frame
	orient.transform( getSourceFrame() );

	// set the rotation
	TAngle defaut(0);
	TZAxisRotation  rotn( defaut-orient.bearing() );

	// set the Helmert Transformation
	fTransform = new THelmertTransformation( rotn, translation );
	
	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

