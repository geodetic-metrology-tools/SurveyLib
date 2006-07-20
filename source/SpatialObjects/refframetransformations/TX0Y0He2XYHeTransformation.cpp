//  TX0Y0He2XYHeTransformation.cpp
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
#include  "TAModifiedLocalAstronomicalRF.h"
#include  "TXYHe2X0Y0HeTransformation.h"
#include  "TX0Y0He2XYHeTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TX0Y0He2XYHeTransformation)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TX0Y0He2XYHeTransformation::TX0Y0He2XYHeTransformation()
	: fFrom(0), fTo(0), fEllipsoid(0)
{	// default constructor
}


TX0Y0He2XYHeTransformation::TX0Y0He2XYHeTransformation( TX0Y0HeProjection* from )
	: fFrom( from )
{	// constructor taking pointers to the source and destination reference frames
	fTo = from->getXYHe();
	fEllipsoid = from->getEllipsoid();
}


TX0Y0He2XYHeTransformation::TX0Y0He2XYHeTransformation( const  TX0Y0He2XYHeTransformation& original )
{	// copy constructor

	setSourceFrame( original.getX0Y0He() );
	setDestinationFrame( original.getXYHe() );
	setEllipsoid( original.getEllipsoid() );
}


TX0Y0He2XYHeTransformation::~TX0Y0He2XYHeTransformation()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TX0Y0He2XYHeTransformation&  TX0Y0He2XYHeTransformation::operator=(const TX0Y0He2XYHeTransformation& right)
{	// Copy Assignment operator

	if (this != &right)
	{
		setSourceFrame( right.getX0Y0He() );
		setDestinationFrame( right.getXYHe() );
		setEllipsoid( right.getEllipsoid() );
	}
	return *this;
}


TARefFrameTransformation*  TX0Y0He2XYHeTransformation::clone() const
{// Return a pointer to a clone of this reference frame
	return new TX0Y0He2XYHeTransformation( *this );
}


TARefFrameTransformation*  TX0Y0He2XYHeTransformation::inverse() const
{// Return a pointer to the inverse of this transformtion
	return new TXYHe2X0Y0HeTransformation( fFrom );
}




void TX0Y0He2XYHeTransformation::setSourceFrame( TX0Y0HeProjection* x0y0he )
{
	fFrom = x0y0he; 
	setDestinationFrame(x0y0he->getXYHe());
	setEllipsoid(x0y0he->getEllipsoid());
	
	return; 
}


void TX0Y0He2XYHeTransformation::setDestinationFrame( TXYHeProjection* xyhe)
{
	fTo = xyhe; 
	return; 
}


void TX0Y0He2XYHeTransformation::setEllipsoid( TReferenceEllipsoid* ellipsoid )
{// Set the ellipsoid
	fEllipsoid = ellipsoid;
	return; 
}


bool  TX0Y0He2XYHeTransformation::transform(TPositionVector& pv) const
{// Transformation of a spatial position using the parameters of the two reference frames
	double Dx, dx, Dy, dy, he, d, falseX, falseY;

	// distance from p0 in X0Y0-plane
	dx = pv.getX().getMetresValue() - fTo->getMLARefFrame()->getFalseOrigin().getX().getMetresValue();
	dy = pv.getY().getMetresValue() - fTo->getMLARefFrame()->getFalseOrigin().getY().getMetresValue();
	he = pv.getH().getMetresValue();
	d = sqrt( (pow(dx,2)) + (pow(dy,2)) );
	
	// bearing from p0 in the X0Y0-plane
	TAngle beta = TAngle::aTan2(dx,dy);
	
	// azimuth from p0
	TAngle alpha = fTo->getMLARefFrame()->getOrientation().getElements(TCoordSysFactory::k3DCartesian).getAngles(TRotationMatrix::kRzyx).kappa;
	TAngle azimuth = alpha + beta;
	
	// radius of the ellipsoid at azimuth and at phiP0
	TSpatialPosition falseOrigin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TLength xp, yp, zp;
	xp.setMetresValue(fTo->getMLARefFrame()->getFalseOrigin().getX().getMetresValue());
	yp.setMetresValue(fTo->getMLARefFrame()->getFalseOrigin().getY().getMetresValue());
	zp.setMetresValue(fTo->getMLARefFrame()->getFalseOrigin().getZ().getMetresValue());
	TPositionVector vector(xp.getMetresValue(),yp.getMetresValue(),zp.getMetresValue(),TCoordSysFactory::k3DCartesian);
	falseOrigin.setCoordinates(vector);
	
	TAngle phiP0;
	phiP0 = fTo->getMLARefFrame()->getOrigin().getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid(/*fEllipsoid, &falseOrigin*/);
	
	double nuP0 = fEllipsoid->getNu(phiP0.getRadiansValue());

	double rhoalpha = nuP0 / (1 + fEllipsoid->getEPrimeSquared()
		*pow( (phiP0.cosine()) * (azimuth.cosine()) ,2 ) );
	
	// scale factor
	double k = (rhoalpha + he) / rhoalpha ;
	
	//Deltas to be added on X0 and Y0 coordinates, using the scale factor
 	Dx = k * dx;
	Dy = k * dy;
	
	falseX = fTo->getMLARefFrame()->getFalseOrigin().getX().getMetresValue();
	falseY = fTo->getMLARefFrame()->getFalseOrigin().getY().getMetresValue();

	// transformation of tposition vector
	TLength newX(falseX + Dx), newY(falseY + Dy);
	pv.setX(newX);
	pv.setY(newY);

	return true;
}


//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////
