//  TXYHe2XYHgTransformation.cpp
//
/** The direct transformation from a modified local geodetic reference frame to a
    geodetic reference frame.
	
    The coordinates of the origin, and the laplace correction at the
	origin of the reference frames define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//
//#include  "TVReferenceFrame.h"
#include  "TRotation.h"
#include  "TReferenceEllipsoid.h"
#include  "TAGeoidModel.h"
#include  "TAModifiedLocalAstronomicalRF.h"
#include  "TXYHe2XYHgTransformation.h"
#include  "TXYHg2XYHeTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TX0Y0He2XYHeTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TXYHe2XYHgTransformation::TXYHe2XYHgTransformation()
	: fFrom(0), fTo(0), fEllipsoid(0), fGeoid(0)
{	// default constructor
}


TXYHe2XYHgTransformation::TXYHe2XYHgTransformation( TXYHgProjection* to )
	: fTo( to )
{	// constructor taking pointers to the source and destination reference frames
	fFrom = to->getXYHe();
	fGeoid = to->getGeoid();
	fEllipsoid = fFrom->getEllipsoid();
}


TXYHe2XYHgTransformation::TXYHe2XYHgTransformation( const  TXYHe2XYHgTransformation& original )
{	// copy constructor

	setSourceFrame( original.getXYHe() );
	setDestinationFrame( original.getXYHg() );
	setEllipsoid( original.getEllipsoid() );
	setGeoid( original.getGeoid() );
}


TXYHe2XYHgTransformation::~TXYHe2XYHgTransformation()
{
}



//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TXYHe2XYHgTransformation&  TXYHe2XYHgTransformation::operator=(const TXYHe2XYHgTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getXYHe() );
		setDestinationFrame( right.getXYHg() );
		setEllipsoid( right.getEllipsoid() );
		setGeoid( right.getGeoid() );
	}
	return *this;
}


TARefFrameTransformation*  TXYHe2XYHgTransformation::clone() const
{// Return a pointer to a clone of this reference frame
		return new TXYHe2XYHgTransformation( *this );
}


TARefFrameTransformation*  TXYHe2XYHgTransformation::inverse() const
{// Return a pointer to the inverse of this transformtion
	return new TXYHg2XYHeTransformation( fTo );
} 


bool  TXYHe2XYHgTransformation::transform( TPositionVector& pv ) const
{// Transformation of a position vector using N (height above geoid)

	TLength he(pv.getH());
	quad x, y, h;
	x = pv.getX().getMetresValue();
	y = pv.getY().getMetresValue();
	h = he.getMetresValue();

	// extraction of N using a tspatialposition of coordinates = pv, and reference frame = CCS
	TSpatialPosition trick(fFrom->getMLARefFrame(), x, y, h, pv.getCoordSys()); 
	TLength N = fGeoid->getN(trick);

	pv.setH(he-N);
	return true;
}


//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
