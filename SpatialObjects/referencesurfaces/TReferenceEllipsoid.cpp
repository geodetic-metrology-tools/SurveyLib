// 
// TReferenceEllipsoid
//
// Class for an ellipsoid of reference as defined for survey purposes
//

////////////////////////////////////////////////////////////////
//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
// other forward declarations
////////////////////////////////////////////////////////////////


#include	"TAngle.h"
#include	"TReferenceEllipsoid.h"

#include    "TGraph.h"

//ClassImp(TReferenceEllipsoid)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// Constructor taking the name of the reference ellipsoid
TReferenceEllipsoid::TReferenceEllipsoid( const  string& name ) : fName( name )
{	 
}



TReferenceEllipsoid::~TReferenceEllipsoid()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

void	TReferenceEllipsoid::setAAndESquared( const EllipseParameter a, const EllipseParameter eSquared ) 
{	// set all parameters when the values of semi-major axis and eccentricity squared are given

	fA = a;
	fESquared = eSquared;
	fF = 1.0 - sqrtq(1.0 - eSquared);

	setDerivedParameters();
	
}


void	TReferenceEllipsoid::setAAndReciprocalF( const EllipseParameter a, const EllipseParameter reciprocalF ) 
{	// set all parameters when the values of semi-major axis and reciprocal of the flattening are given

	fA = a;
	fF = 1.0 / reciprocalF;
	fESquared = fF * (2.0 - fF);

	setDerivedParameters();

		
}


void TReferenceEllipsoid::setDerivedParameters() 
{ //set remaining parameters of the ellipsoid
	
	fB = fA * (1.0 - fF);
	fEPrimeSquared = fESquared / (1.0 - fESquared);

}


// Get the Radius of Curvature of the Ellipsoid in the Prime Vertical
// at a given latitude.
EllipseParameter  TReferenceEllipsoid::getNu( const TAngle& phi )  const
{
	real sinP = sinq( phi.getRadiansValue() );
	
	real nu = fA / sqrtq( 1.0 - (fESquared * sinP * sinP) );
	return nu;
}


// Get the Radius of Curvature of the Ellipsoid in the Prime Vertical
// at a given latitude given in radians.
EllipseParameter  TReferenceEllipsoid::getNu( const real phi )  const
{
	real sinP = sinq( phi );
	
	real nu = fA / sqrtq( 1.0 - (fESquared * sinP * sinP) );
	return nu;
}


// Get the Radius of Curvature of the Ellipsoid in the Meridian
//	at a given latitude.
EllipseParameter  TReferenceEllipsoid::getRho( const TAngle& phi )  const
{
	real sinP = sinq( phi.getRadiansValue() );
	
	real rho = fA * (1.0 - fESquared) / powq(( 1.0 - (fESquared * sinP * sinP) ), 3.0/2.0);
	return rho;
}


// Get the Radius of Curvature of the Ellipsoid in the Meridian
//	at a given latitude given in radians.
EllipseParameter  TReferenceEllipsoid::getRho( const real phi )  const
{
	real sinP = sinq( phi );
	
	real rho = fA * (1.0 - fESquared) / powq(( 1.0 - (fESquared * sinP * sinP) ), 3.0/2.0);
	return rho;
}


// Get the Euler's Radius of Curvature of the Ellipsoid
//	at a given latitude, and azimuth.
EllipseParameter  TReferenceEllipsoid::getEuler( const TAngle& phi, const TAngle& alpha )  const
{
	real cosP = cosq( phi.getRadiansValue() );
	real cosA = cosq( alpha.getRadiansValue() );
	real nu = getNu( phi );
	
	real euler = nu / ( 1.0 + ( fEPrimeSquared * cosP * cosP * cosA * cosA ) );
	return euler;
}


// Get the Euler's Radius of Curvature of the Ellipsoid
//	at a given latitude, and azimuth given in radians.
EllipseParameter  TReferenceEllipsoid::getEuler( const real phi, const real alpha )  const
{
	real cosP = cosq( phi );
	real cosA = cosq( alpha );
	real nu = getNu( phi );
	
	real euler = nu / ( 1.0 + ( fEPrimeSquared * cosP * cosP * cosA * cosA ) );
	return euler;
}



void TReferenceEllipsoid::setEllId(const TRefSystemFactory::ERefEll ellId)
{ 
	fEllId = ellId;
	return; 
}


TRefSystemFactory::ERefEll TReferenceEllipsoid::getEllId() const
{
	return fEllId; 
}


//////////////////////////////////////////////////////////////////////
// Utility Member Functions
//////////////////////////////////////////////////////////////////////


bool TReferenceEllipsoid::operator==(const TReferenceEllipsoid &right) const{
//Compare 2 ellipsoid names
	return ( fName==right.getName() );
}



