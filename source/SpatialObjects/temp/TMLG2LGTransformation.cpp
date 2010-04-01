//  TMLG2LGTransformation.cpp
//
/** The transformation from a modified local geodetic reference frame to a
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


//ClassImp(TMLG2LGTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMLG2LGTransformation::TMLG2LGTransformation()
	: TARefFrameTransformation(), fTransform(0)
{	// default constructor
}


TMLG2LGTransformation::TMLG2LGTransformation( TVReferenceFrame* from, TVReferenceFrame* to )
	: TARefFrameTransformation( from, to )
{	// constructor taking pointers to the source and destination reference frames
}


TMLG2LGTransformation::TMLG2LGTransformation( const  TMLG2LGTransformation& original )
{	// copy constructor

	setSourceFrame( original.getSourceFrame() );
	setDestinationFrame( original.getDestinationFrame() );
}


TMLG2LGTransformation::~TMLG2LGTransformation()
{
	if( 0 != fTransform )  delete fTransform;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


TMLG2LGTransformation&  TMLG2LGTransformation::operator=(const TMLG2LGTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getSourceFrame() );
		setDestinationFrame( right.getDestinationFrame() );
	}
	return *this;
}


// Return a pointer to a clone of this reference frame
TVRefFrameTransformation*  TMLG2LGTransformation::clone() const
{
	return new TMLG2LGTransformation( *this );
}


// Return a pointer to the inverse of this transformtion
TVRefFrameTransformation*  TMLG2LGTransformation::inverse() const
{
	return new TLG2MLGTransformation( getDestinationFrame(), getSourceFrame() );
}




// Return a transformed position vector
TPositionVector  TMLG2LGTransformation::transform( const TPositionVector& pv ) const
{
	TPositionVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(pv);

	return result;
}


// Return a transformed free vector
TFreeVector  TMLG2LGTransformation::transform( const TFreeVector& fv ) const
{
	TFreeVector result;
	  
	if( isInitialised() )
		  result = fTransform->transform(fv);

	return result;
}


// Return a transformed Rotation Matrix
TRotationMatrix  TMLG2LGTransformation::transform( const TRotationMatrix& rmx ) const
{
	TRotationMatrix result;
	  
	if( isInitialised() )
		  result = fTransform->transform(rmx);

	return result;
}


// Initialise the transformation using the parameters of the two reference frames
void  TMLG2LGTransformation::initialise()
{
	// establish the transformation from the modified local geodetic system to the 
	// local geodetic system

	// get the orientation vector and FalseOrigin
	TSpatialOrientation  orient = getSourceFrame()->getOrientation();
	TTranslation  translation = getSourceFrame()->getFalseOrigin();

	// change the orientation to the Local Geodetic reference frame
	orient.transform( getDestinationFrame() );

	// set the rotation
	TAngle defaut(0);
	TZAxisRotation  rotn(defaut -orient.bearing() );

	// set the Helmert Transformation
	fTransform = new THelmertTransformation( rotn, translation );
	fTransform->invert();
	
	return;
}




//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

