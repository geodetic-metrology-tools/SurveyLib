//  TDatumServer.cpp
//
/** A class that instantiates the complete set of available horizontal 
    and vertical datums (coordinate surfaces), and provides access to 
	them.

  
    Patterns:
	A singleton to ensure only one such server exists.
     
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TAngle.h"
#include  "TLength.h"
#include  "TVReferenceEllipsoid.h"
#include  "TReferenceEllipsoid.h"
#include  "TVGeoid.h"
#include  "TCernParabolicGeoid.h"
#include  "TVTopocentricDatumPosition.h"
#include  "TTopocentricDatumPosition.cpp"
#include  "TDatumServer.h"
////////////////////////////////////////////////////////////////


//ClassImp(TDatumServer)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////

TDatumServer*  TDatumServer::fInstance = 0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TDatumServer::TDatumServer()
{	// default constructor
	
	// initialise all the pointers to null
	// the reference ellipsoids
	fGRS80 = 0;
	fWGS84Ell = 0;
	fInternational = 0;
	fCERNSPS = 0;

	// the geoid models
	fCERNSurf = 0;
	fCERNLEP = 0;

	// the datum positions
	fCGRFPosition = 0;
}


// **Deliberately not implemented**
//TDatumServer::TDatumServer( const  TDatumServer& original )
//{	// copy constructor
//}


TDatumServer::~TDatumServer()
{
	// delete all the objects that have been made
	// the reference ellipsoids
	if( fGRS80 != 0)  delete fGRS80;
	if( fWGS84Ell != 0)  delete fWGS84Ell;
	if( fInternational != 0)  delete fInternational;
	if( fCERNSPS != 0)  delete fCERNSPS;

	// the geoid models
	if( fCERNSurf != 0)  delete fCERNSurf;
	if( fCERNLEP != 0)  delete fCERNLEP;

	// the datum positions
	if( fCGRFPosition != 0)  delete fCGRFPosition;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


// **Deliberately not implemented**
//TDatumServer&  TDatumServer::operator=(const TDatumServer& right)
//{	// Copy Assignment operator
//
//	if (this != &right)
//	{
//	}
//	return *this;
//}


TDatumServer*  TDatumServer::instance()
{	// return a pointer to the instance of the TDatumServer
	
	if( fInstance == 0 )
	{
		fInstance = new TDatumServer();
	}

	return fInstance;
}


//
// Return a pointer to the specified reference ellipsoid
//
TVReferenceEllipsoid*  TDatumServer::getRefEllipsoid( TDatumServer::EEllipsoid  nameEnum )
{	// if the ellipsoid instance doesn't yet exist, make it
	
	TVReferenceEllipsoid*  ellipsoid = 0;

	switch( nameEnum )
	{
	case kGRS80:
		ellipsoid = getGRS80();
		break;

	case kWGS84Ell:
		ellipsoid = getWGS84Ell();
		break;

	case kInternational:
		ellipsoid = getInternational();
		break;

	case kCERNSPS:
		ellipsoid = getCERNSPS();
		break;

	default:
		break;
	}

	return ellipsoid;
}


//
// Return a pointer to the instance of the GRS80 reference ellipsoid
//
TVReferenceEllipsoid*  TDatumServer::getGRS80()
{	// if the ellipsoid instance doesn't yet exist, make it
	
	double a = 6378137.0;
	double eSquared = 0.0066943800229;

	if( fGRS80 == 0 )
	{
		fGRS80 = new TReferenceEllipsoid( "GRS80 Reference Ellipsoid" );
		// set the defining parameters of the ellipsoid
		fGRS80->setAAndESquared( a, eSquared );
	}

	return fGRS80;
}


//
// Return a pointer to the instance of the WGS84 reference ellipsoid
//
TVReferenceEllipsoid*  TDatumServer::getWGS84Ell()
{	// if the ellipsoid instance doesn't yet exist, make it
	
	double a = 6378137.0;
	double reciprocalF = 298.257223563;

	if( fWGS84Ell == 0 )
	{
		fWGS84Ell = new TReferenceEllipsoid( "WGS84 Reference Ellipsoid" );
		// set the defining parameters of the ellipsoid
		fWGS84Ell->setAAndReciprocalF( a, reciprocalF );
	}

	return fWGS84Ell;
}


//
// Return a pointer to the instance of the International reference ellipsoid
//
TVReferenceEllipsoid*  TDatumServer::getInternational()
{	// if the ellipsoid instance doesn't yet exist, make it
	
	double a = 6378388.0;
	double eSquared = 0.006722670022;

	if( fInternational == 0 )
	{
		fInternational = new TReferenceEllipsoid( "International Reference Ellipsoid" );
		// set the defining parameters of the ellipsoid
		fInternational->setAAndESquared( a, eSquared );
	}

	return fInternational;
}


//
// Return a pointer to the instance of the CERNSPS reference ellipsoid
//
TVReferenceEllipsoid*  TDatumServer::getCERNSPS()
{	// if the ellipsoid instance doesn't yet exist, make it
	
	double a = 6371000.0;
	double eSquared = 0.0;

	if( fCERNSPS == 0 )
	{
		fCERNSPS = new TReferenceEllipsoid( "CERN (SPS) Spherical Datum Model" );
		// set the defining parameters of the sphere
		fCERNSPS->setAAndESquared( a, eSquared );
	}

	return fCERNSPS;
}


//
// Return a pointer to the specified geoid model
//
TVGeoid*  TDatumServer::getGeoid( TDatumServer::EGeoid  nameEnum )
{	// if the geoid instance doesn't yet exist, make it
	
	TVGeoid*  geoid = 0;

	switch( nameEnum )
	{
	case kCERNSurf:
		geoid = getCERNSurf();
		break;

	case kCERNLEP:
		geoid = getCERNLEP();
		break;

	default:
		break;
	}

	return geoid;
}


//
// Return a pointer to the instance of the CERN Surface Geoid (H=0)
//
TVGeoid*  TDatumServer::getCERNSurf()
{	// if the geoid instance doesn't yet exist, make it
	
	double a0 =  0.535;
	double b0 = -0.096;
	double thetas0 = 48.772 * TAngle::gonsToRadsFactor();

	if( fCERNSurf == 0 )
	{
		fCERNSurf = new TCernParabolicGeoid( "CERN Co-Geoidal Datum Model", a0 , b0, thetas0 );
	}

	return fCERNSurf;
}


//
// Return a pointer to the instance of the CERN LEP Geoid (H=HLep)
//
TVGeoid*  TDatumServer::getCERNLEP()
{	// if the geoid instance doesn't yet exist, make it
	
	double aL =  0.614;
	double bL = -0.106;
	double thetasL = 48.219 * TAngle::gonsToRadsFactor();

	if( fCERNLEP == 0 )
	{
		fCERNLEP = new TCernParabolicGeoid( "CERN (LEP) Orthometric Datum Model", aL , bL, thetasL );
	}

	return fCERNLEP;
}


//
// Return a pointer to the Topocentric datum position parameters of the specified datum
//
TVTopocentricDatumPosition*  TDatumServer::getTopoDatumPosition( TDatumServer::EDatum  nameEnum )
{	// if the datum position instance doesn't yet exist, make it
	
	TVTopocentricDatumPosition*  datumPosition = 0;

	switch( nameEnum )
	{
	case kCERNGRF:
		datumPosition = getCGRFPosition();
		break;

	default:
		break;
	}

	return datumPosition;
}


//
// Return a pointer to the instance of the CERN GRF topocentric datum position parameters
//
TVTopocentricDatumPosition*  TDatumServer::getCGRFPosition()
{	// if the topocentric datum position parameters instance doesn't yet exist, make it
	
	TAngle  phi0;
	TAngle  lambda0;
	TLength he0( 0.0 );
	TAngle  eta0( 0.0 );
	TAngle  xi0( 0.0 );
	TAngle  alpha0;
	TLength x0( 2000.0 );
	TLength y0( 2097.79265 );
	TLength z0( 2000.00079 );

	phi0.setGonsValue( 51.3692 );
	lambda0.setGonsValue( 6.72124 );
	alpha0.setGonsValue( 37.77864 );
	

	if( fCGRFPosition == 0 )
	{
		fCGRFPosition = new TTopocentricDatumPosition( "CGRF Topocentric Datum Position");
		
		// set the datum position parameters
		fCGRFPosition->setPhi0( phi0 );
		fCGRFPosition->setLambda0( lambda0 );
		fCGRFPosition->setHe0( he0 );
		fCGRFPosition->setEta0( eta0 );
		fCGRFPosition->setXi0( xi0 );
		fCGRFPosition->setAlpha0( alpha0 );
		fCGRFPosition->setX0( x0 );
		fCGRFPosition->setY0( y0 );
		fCGRFPosition->setZ0( z0 );

	}

	return fCGRFPosition;
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////

