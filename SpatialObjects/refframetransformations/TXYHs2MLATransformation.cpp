//  TXYHs2MLATransformation.cpp
//
/** The direct transformation from a modified local astronomical reference frame to a
    geodetic reference frame.
	
    The coordinates of the origin, and the laplace correction at the
	origin of the reference frames define the transformation.


    Patterns:
  
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////


//For ROOT//////////////////////////////////////////////////////
//
//#include  "TVReferenceFrame.h"
#include  "TRotation.h"
#include  "TReferenceEllipsoid.h"
#include  "TMLA2XYHsTransformation.h"
#include  "TXYHs2MLATransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TXYHs2MLATransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TXYHs2MLATransformation::TXYHs2MLATransformation()
	: fFrom(0), fTo(0), fEllipsoid(0)
{	// default constructor
}


TXYHs2MLATransformation::TXYHs2MLATransformation( TXYHeProjection* from )
	: fFrom( from )
{	// constructor taking pointers to the source and destination reference frames
	fTo = from->getMLARefFrame();
	fEllipsoid = from->getEllipsoid();
}


TXYHs2MLATransformation::TXYHs2MLATransformation( const  TXYHs2MLATransformation& original )
{	// copy constructor

	setSourceFrame( original.getXYHs() );
	setDestinationFrame( original.getMLARF() );
	setEllipsoid( original.getEllipsoid() );
}


TXYHs2MLATransformation::~TXYHs2MLATransformation()
{
}



//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TXYHs2MLATransformation&  TXYHs2MLATransformation::operator=(const TXYHs2MLATransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getXYHs() );
		setDestinationFrame( right.getMLARF() );
		setEllipsoid( right.getEllipsoid() );
	}
	return *this;
}


TARefFrameTransformation*  TXYHs2MLATransformation::clone() const
{// Return a pointer to a clone of this reference frame
		return new TXYHs2MLATransformation( *this );
}


TARefFrameTransformation*  TXYHs2MLATransformation::inverse() const
{// Return a pointer to the inverse of this transformtion
	return new TMLA2XYHsTransformation( fFrom );
}


void TXYHs2MLATransformation::setSourceFrame( TXYHeProjection* XYHs )
{
	fFrom = XYHs; 
	setDestinationFrame(XYHs->getMLARefFrame());
	setEllipsoid(XYHs->getEllipsoid());
	
	return; 
}



bool  TXYHs2MLATransformation::transform(TPositionVector& pv) const
{// Transformation of a position vector using the parameters of the two reference frames
	quad dx, dy, hs, d;
	quad d0, omega;
	// radius of the sphere
	quad R = 6371000.0;
	// transform TPositionVector
	quad Z;

	// distance from P0 in XY-plane
	dx = pv.getX().getMetresValue() - fTo->getFalseOrigin().getX().getMetresValue();
	dy = pv.getY().getMetresValue() - fTo->getFalseOrigin().getY().getMetresValue();
	hs = pv.getH().getMetresValue();
	d=__sqrtq( (__powq(dx,2)) + (__powq(dy,2)) );

	//Z = __sqrtq( (__powq((R+hs),2) - (__powq(d,2))) )-  R + 2000.00079;
	d0 = d * R / (R + hs);
	omega = __asinq(d0 / R);
	Z = 2000.00079 + (hs * __cosq(omega)) - (d0 * __tanq(omega/2.0));

	TLength newZ (Z);

	// change the coordinate system of the position vector
	pv.setCoordSys(TCoordSysFactory::k3DCartesian);

	// change the H coordinate of the position vector into the third coordinate Z
	pv.setZ( newZ ); 

	return true;
}


//////////////////////////////////////////////////////////////////////
//End
//////////////////////////////////////////////////////////////////////
