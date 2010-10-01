//  TLG2GCTransformation.cpp
//
/** The transformation from a local geodetic reference frame to a
    geodetic reference frame.
	
    The origin of the local geodetic system defines the transformation.


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
#include  "TSpatialPosition.h"
#include  "TSpatialOrientation.h"
#include  "TRotation.h"
#include  "THelmertTransformation.h"
#include  "TGC2LGTransformation.h"
#include  "TLG2GCTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TLG2GCTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLG2GCTransformation::TLG2GCTransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TLG2GCTransformation::TLG2GCTransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TLG2GCTransformation::TLG2GCTransformation( const  TLG2GCTransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TLG2GCTransformation::~TLG2GCTransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TLG2GCTransformation&  TLG2GCTransformation::operator=(const TLG2GCTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TLG2GCTransformation::clone() const
{
	return new TLG2GCTransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TLG2GCTransformation::inverse() const
{
	return new TGC2LGTransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TLG2GCTransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TLG2GCTransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TLG2GCTransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TLG2GCTransformation::initialise()
{
	// establish the transformation from the local geodetic to the geodetic system

	// get the origin of the Local Geodetic system
	TSpatialPosition  origin( getSourceFrame()->getOriginPosition() );

	TRotation  rotn;

	// set the translation
	TTranslation  translation( origin.getXCoord(), origin.getYCoord(), origin.getZCoord() );;

	// change the origin to the Geodetic Cartesian reference frame
	origin.transform( getDestinationFrame() );

	{
		// set the rotation matrix
		TZAxisRotation  r1( TAngle::piBy2() );
		TYAxisRotation  r2( TAngle::piBy2() - origin.getPhiEllipsoid() );
		TZAxisRotation  r3( TAngle::pi() - origin.getLambdaEllipsoid() );
		
		rotn = r3 * r2 * r1;
	}

	// set the Helmert Transformation
	fTransform = new THelmertTransformation( rotn, translation );

	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

