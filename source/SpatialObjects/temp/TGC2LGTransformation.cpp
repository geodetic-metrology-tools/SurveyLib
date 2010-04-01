//  TGC2LGTransformation.cpp
//
/** The transformation from a Geodetic reference frame to a 
    local geodetic reference frame.
	
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
#include  "TLG2GCTransformation.h"
#include  "TGC2LGTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TGC2LGTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TGC2LGTransformation::TGC2LGTransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TGC2LGTransformation::TGC2LGTransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TGC2LGTransformation::TGC2LGTransformation( const  TGC2LGTransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TGC2LGTransformation::~TGC2LGTransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TGC2LGTransformation&  TGC2LGTransformation::operator=(const TGC2LGTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TGC2LGTransformation::clone() const
{
	return new TGC2LGTransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TGC2LGTransformation::inverse() const
{
	return new TLG2GCTransformation( getDestinationFrame(), getSourceFrame() );
}


// Return a transformed position vector
TPositionVector  TGC2LGTransformation::transform( const TPositionVector& pv ) const
{
	  TPositionVector  result;
	  
	  if( isInitialised() )
		  result = fTransform->transform(pv);

	  return result;
}


// Return a transformed free vector
TFreeVector  TGC2LGTransformation::transform( const TFreeVector& fv ) const
{
	  TFreeVector  result;
	  
	  if( isInitialised() )
		  result = fTransform->transform(fv);

	  return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TGC2LGTransformation::transform( const TRotationMatrix& rmx ) const
{
	  TRotationMatrix  result;
	  
	  if( isInitialised() )
		  result = fTransform->transform(rmx);

	  return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TGC2LGTransformation::initialise()
{
	// establish the transformation from the geodetic to the local geodetic system

	// get the origin of the Local Geodetic system
	TSpatialPosition  origin( getDestinationFrame()->getOrigin()->getPosition() );

	TRotation     rotn;
	TTranslation  translation( origin.getXCoord(), origin.getYCoord(), origin.getZCoord() );

	// Transform the origin to the Geodetic Cartesian reference frame
	origin.transform( getSourceFrame() );

	{
		// set the rotation matrix
		TZAxisRotation  r1( TAngle::piBy2() );
		TYAxisRotation  r2( TAngle::piBy2() - origin.getPhiEllipsoid() );
		TZAxisRotation  r3( TAngle::pi() - origin.getLambdaEllipsoid() );
		
		rotn = r3 * r2 * r1;
	}

	
	// set the Helmert Transformation
	fTransform = new THelmertTransformation( rotn, translation );
	fTransform->invert();

	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

