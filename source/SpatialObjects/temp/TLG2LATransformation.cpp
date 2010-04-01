//  TLG2LATransformation.cpp
//
/** The transformation from a local geodetic reference frame to a 
    local astronomical reference frame.
	
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
#include  "TLA2LGTransformation.h"
#include  "TLG2LATransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TLG2LATransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLG2LATransformation::TLG2LATransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TLG2LATransformation::TLG2LATransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TLG2LATransformation::TLG2LATransformation( const  TLG2LATransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TLG2LATransformation::~TLG2LATransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TLG2LATransformation&  TLG2LATransformation::operator=(const TLG2LATransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TLG2LATransformation::clone() const
{
	return new TLG2LATransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TLG2LATransformation::inverse() const
{
	return new TLA2LGTransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TLG2LATransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TLG2LATransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TLG2LATransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TLG2LATransformation::initialise()
{
	// establish the transformation from the local geodetic to the local
	// astronomical system
	
	// get the geoid used to define the astronomical system
	TVVerticalDatum*  geoid = getDestinationFrame()->getVerticalDatum();

	// get the origin in the reference frame of the local astronomical system geoid
	// and the geoid values at the origin
	TSpatialPosition  origin = getDestinationFrame()->getOriginPosition();
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
	fTransform->invert();

	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

