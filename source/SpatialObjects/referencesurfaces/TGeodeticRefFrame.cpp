// TGeodeticRefFrame.cpp
//
/** A Geodetic Ellisoidal Reference Frame. 
    Deals with requests for Spatial Position coordinates
    appropriate to a Geodetic reference frame.

  
    Patterns:
    A concrete STATE of a Spatial Position
   
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//forward declarations
#include	"TReferenceEllipsoid.h"

#include	"TSpatialPosition.h"
#include	"TPositionStatus.h"
#include	"TSpatialPositionError.h"

#include	"TSpatialVector.h"
#include	"TSpatialVectorStatus.h"
#include	"TSpatialVectorError.h"

#include  "TGeodeticRefFrame.h"
////////////////////////////////////////////////////////////////


//ClassImp(TGeodeticRefFrame)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
const quad TGeodeticRefFrame::precisionH = 0.0000001; //precision calcul h
const quad TGeodeticRefFrame::precisionPhi = 0.00000000000001; //precision calcul phi



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TGeodeticRefFrame::TGeodeticRefFrame( const string& name ) 
	: TA3DEuclideanRefFrame( name )
{	// constructor taking the name of the reference frame
}



TGeodeticRefFrame::TGeodeticRefFrame( const string& name, TReferenceEllipsoid* ell ) 
	: TA3DEuclideanRefFrame( name )
{	// constructor taking the name of the reference frame
	fEllipsoid = ell;
}

// **Deliberately not implemented**
//TGeodeticRefFrame::TGeodeticRefFrame( const  TGeodeticRefFrame& original )
//{	// copy constructor
//}


TGeodeticRefFrame::~TGeodeticRefFrame()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TPositionVector TGeodeticRefFrame::getCoordinates(const TSpatialPosition* sp, TCoordSysFactory::ECoordSys coordsys) const
{
	if(coordsys == TCoordSysFactory::k3DCartesian) {
		return getPositionVector(sp);
	}
	else if(coordsys == TCoordSysFactory::kGeodetic) 
	{
		//fEllipsoid = ;
		return getGeodeticCoords(getPositionVector(sp),
			fEllipsoid/*TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80)*/); //compiles but doesn't work
	}
	else if(coordsys == TCoordSysFactory::kGeodeticSphere)
	{
		
		return getGeodeticCoords(getPositionVector(sp),
			fEllipsoid/*TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kSphere)*/);
	}
	else
	{
		TPositionVector pv(TCoordSysFactory::k3DCartesian);
		return pv;
	}
}



bool TGeodeticRefFrame::setCoordinates(TSpatialPosition* sp, const TPositionVector& pv)
{
	if(pv.getCoordSys() == TCoordSysFactory::k3DCartesian)
	{
		return setPositionVector(sp,pv);
	}
	else if (pv.getCoordSys() == TCoordSysFactory::kGeodetic)
	{
		return setPositionVector(sp, getCartesianCoords(pv, fEllipsoid));
	}
	else
	{
		return false;
	}
}


TPositionVector   TGeodeticRefFrame::getGeodeticCoords( const TSpatialPosition* pos, const TReferenceEllipsoid* ellipsoid )  const
{
	return getGeodeticCoords( getPositionVector(pos), ellipsoid );
}

/////////////////////////////////////////////////////////////////////////////////////////
//private fonctions
/////////////////////////////////////////////////////////////////////////////////////////

TPositionVector   TGeodeticRefFrame::getGeodeticCoords( const TPositionVector pv, const TReferenceEllipsoid* ellipsoid )  const
{
	// get the Cartesian coordinates of the position
	quad  x = pv.getX().getMetresValue();
	quad  y = pv.getY().getMetresValue();
	quad  z = pv.getZ().getMetresValue();
	//quad  x = getX1( posn );
	//quad  y = getX2( posn );
	//quad  z = getX3( posn );

	//get a copy of the parameters of the ellipsoid
	quad  a = ellipsoid->getA();
	quad  b = ellipsoid->getB();
	quad  eSquared = ellipsoid->getESquared();

	quad p;
	quad nu;
	AngleValue phi, tempphi, lambda;
	LengthValue h, temph;
	TPositionVector  geodpv(TCoordSysFactory::kGeodetic);
//	TPositionVector*  pgeodpv;
//	pgeodpv=&geodpv;

	if( x==0 && y==0)
	{
		TAngle phirad, lrad;
		TLength hm;
		phirad = TAngle::piBy2();;
		lrad.setRadiansValue(0.0);
		hm.setMetresValue(z-a);
		geodpv.setPhiEllipsoid(phirad);
		geodpv.setLambdaEllipsoid(lrad);
		geodpv.setH(hm);
		geodpv.setStatus(pv.getStatus());
	}
	else
	{	
		p = __sqrtq(x*x + y*y);

		//calcul lambda
		lambda = 2 * __atanq ( y / (x + p) );
		
		//calcul iteratif phi et h
		//initialisation
		h = 0;
		temph = 1;
		phi = __atanq ( z / (p * ( 1.0 - eSquared )) );
		tempphi = phi+1;

		//boucle
		while ( ( __fabsq( phi-tempphi ) > TGeodeticRefFrame::precisionPhi ) ||  ( __fabsq( temph-h ) > TGeodeticRefFrame::precisionH ))
		{
			nu = ellipsoid->getNu( phi );
			temph = h;
			h = ( p / __cosq(phi) ) - nu;
			tempphi = phi;
			phi = __atanq ( z / (p * ( 1.0 - (eSquared * nu / (nu+h)) )) );
		}
		
		TAngle phirad, lrad;
		TLength hm;
		phirad.setRadiansValue(phi);
		lrad.setRadiansValue(lambda);
		hm.setMetresValue(h);
		geodpv.setPhiEllipsoid(phirad);
		geodpv.setLambdaEllipsoid(lrad);
		geodpv.setH(hm);
		geodpv.setStatus(pv.getStatus());
	}
//	pv.setCoordSys(TGraph::kGeodetic); //to be implemented in TGraph and in TACoordSysVector
	return geodpv;
}


TPositionVector  TGeodeticRefFrame::getCartesianCoords( TPositionVector posvec, const TReferenceEllipsoid* ellipsoid )
{
	// get coordinates of posvec as quad
	quad phi = posvec.getPhiEllipsoid().getRadiansValue();
	quad lambda = posvec.getLambdaEllipsoid().getRadiansValue();
	quad he = posvec.getH().getMetresValue();

	//get a copy of the parameters of the ellipsoid
	quad a = ellipsoid->getA();
	quad b = ellipsoid->getB();
	quad nu = ellipsoid->getNu( phi );

	//retablissement XYZ
	quad x((nu+he)*__cosq(phi)*__cosq(lambda)),
		y((nu+he)*__cosq(phi)*__sinq(lambda)),
		z( (nu*b*b/(a*a) + he)*__sinq(phi));
	TPositionVector pv(x,y,z,TCoordSysFactory::k3DCartesian);

	return pv;
}


// **Deliberately not implemented**
//TGeodeticRefFrame&  TGeodeticRefFrame::operator=(const TGeodeticRefFrame& right)
//{	// Copy Assignment operator
//
//	if (this != &right)
//	{
//	}
//	return *this;
//}


//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////

