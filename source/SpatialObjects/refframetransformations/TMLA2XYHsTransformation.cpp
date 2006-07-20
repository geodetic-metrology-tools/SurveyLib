//  TMLA2XYHsTransformation.h
//
/** The direct transformation from a modified local astronomical reference frame to a
    geodetic reference frame.
	
    The cooerdinates of the origin, and the laplace correction at the
	origin of the reference frames define the transformation.


    Patterns:
  
   
    Copyright 2002 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//
#include  "TRotation.h"
#include  "TReferenceEllipsoid.h"
#include  "TMLA2XYHsTransformation.h"
#include  "TXYHs2MLATransformation.h"
#include  "TCoordSysFactory.h"
////////////////////////////////////////////////////////////////


//ClassImp(TMLA2XYHsTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMLA2XYHsTransformation::TMLA2XYHsTransformation()
	: fFrom(0), fTo(0)
{	// default constructor
}


TMLA2XYHsTransformation::TMLA2XYHsTransformation( TXYHeProjection* to )
	: fTo( to )
{	// constructor taking pointers to the source and destination reference frames
	fFrom = to->getMLARefFrame();
	fEllipsoid = to->getEllipsoid();
}


TMLA2XYHsTransformation::TMLA2XYHsTransformation( const  TMLA2XYHsTransformation& original )
{	// copy constructor

	setSourceFrame( original.getMLARF() );
	setDestinationFrame( original.getXYHs() );
	setEllipsoid( original.getEllipsoid() );
}


TMLA2XYHsTransformation::~TMLA2XYHsTransformation()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TMLA2XYHsTransformation&  TMLA2XYHsTransformation::operator=(const TMLA2XYHsTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getMLARF() );
		setDestinationFrame( right.getXYHs() );
		setEllipsoid( right.getEllipsoid() );
	}
	return *this;
}


TARefFrameTransformation*  TMLA2XYHsTransformation::clone() const
{// Return a pointer to a clone of this reference frame
	return new TMLA2XYHsTransformation( *this );
}


TARefFrameTransformation*  TMLA2XYHsTransformation::inverse() const
{// Return a pointer to the inverse of this transformtion
	return new TXYHs2MLATransformation( fTo );
}


bool  TMLA2XYHsTransformation::transform(TPositionVector& pv) const
{// Transformation of a position vector using the parameters of the two reference frames
	
	double dx, dy, dz, d;
	double d0, omega;
	// radius of the sphere
	double R = 6371000;	
	// transform TPositionVector
	double H;

	//distance from P0 in XY-plane
	dx = pv.getX().getMetresValue() - fFrom->getFalseOrigin().getX().getMetresValue();
	dy = pv.getY().getMetresValue() - fFrom->getFalseOrigin().getY().getMetresValue();
	dz = pv.getZ().getMetresValue() - fFrom->getFalseOrigin().getZ().getMetresValue()
		+ fTo->getMLARefFrame()->getOrigin().getCoordinates(TCoordSysFactory::kGeodetic).getH(/*TGraph::getGraph()->getEllipsoid(TGraph::kGRS80)*/).getMetresValue();
	d=sqrt( (pow(dx,2)) + (pow(dy,2)) );

	//H = sqrt( (pow((R+dz),2) + (pow(d,2))) )-  R;
	omega = atan(d / (R+dz));
	d0 = d * R * cos(omega) / (R + dz);
	H = ( dz + (d0 * tan(omega/2.0)) ) / cos(omega);

	TLength newH (H);
	
	// Change the coordinate system of the position vector
	pv.setCoordSys(TCoordSysFactory::k2DPlusH);   
	
	// Change the third dimension Z of the position vector into H
	pv.setH(newH);
	
	return true;
}


//////////////////////////////////////////////////////////////////////
//End
//////////////////////////////////////////////////////////////////////
