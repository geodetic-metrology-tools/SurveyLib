//  TLA2LGTransformation.cpp
//
/** The transformation from a local astronomical reference frame to a
    local geodetic reference frame.
	
    The deflection of the vertical, and the laplace correction at the
	origin of the reference frames define the transformation.


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
#include  "TGeoidValues.h"
#include  "TVVerticalDatum.h"
#include  "TRotation.h"
//#include  "TReflection.h"
#include  "TCompositeAffTransform.h"
#include  "TLG2LATransformation.h"
#include  "TLA2LGTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TLA2LGTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLA2LGTransformation::TLA2LGTransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TLA2LGTransformation::TLA2LGTransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TLA2LGTransformation::TLA2LGTransformation( const  TLA2LGTransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TLA2LGTransformation::~TLA2LGTransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TLA2LGTransformation&  TLA2LGTransformation::operator=(const TLA2LGTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TLA2LGTransformation::clone() const
{
	return new TLA2LGTransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TLA2LGTransformation::inverse() const
{
	return new TLG2LATransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TLA2LGTransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TLA2LGTransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TLA2LGTransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TLA2LGTransformation::initialise()
{
	// establish the transformation from the local geodetic to the local
	// astronomical system
	
	// get the vertical datum used to define the astronomical system
	TVVerticalDatum*  geoid = getSourceFrame()->getVerticalDatum();

	// get the origin in the reference frame of the local astronomical system geoid
	// and the geoid values at the origin
	TSpatialPosition  origin = getSourceFrame()->getOrigin()->getPosition();
	TGeoidValues  geoidVals = geoid->getGeoidValues( origin );

	// establish the components of the transformation
	TXAxisRotation  r1( geoidVals.getEta() );
	TYAxisRotation  r2( -geoidVals.getXi() );
	TZAxisRotation  r3( geoidVals.getDAlpha() );
	TReflection  p( TReflection::kXEqualY );
	
	// establish the rotation
	// the rotation is defined in terms of left handed reference frames
	// so a reflection is needed before and after the rotation
	*fTransform = p * (r3 * r2 * r1) * p;

	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

