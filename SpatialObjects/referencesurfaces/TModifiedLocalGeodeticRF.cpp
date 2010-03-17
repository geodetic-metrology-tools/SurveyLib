// TModifiedLocalGeodeticRF.cpp
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



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TModifiedLocalGeodeticRF.h"
#include  "TGraph.h"
#include  "TReferenceEllipsoid.h"
#include  "TGeodeticRefFrame.h"
#include  "TRotation.h"
#include  "TSpatialPositionError.h"
#include  "TGC2LGTransformation.h"
#include  "TLG2GCTransformation.h"
////////////////////////////////////////////////////////////////


//ClassImp(TModifiedLocalGeodeticRF)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
const real TModifiedLocalGeodeticRF::precisionH = 0.0000001; //precision calcul h
const real TModifiedLocalGeodeticRF::precisionPhi = 0.00000000000001; //precision calcul phi



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TModifiedLocalGeodeticRF::TModifiedLocalGeodeticRF( const string& name ) 
	: TA3DEuclideanRefFrame( name ), fOrientationMatrix(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLGp0)),
	fOrigin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF)), fFalseOrigin(TCoordSysFactory::k3DCartesian)
{	//default constructor
}


TModifiedLocalGeodeticRF::TModifiedLocalGeodeticRF( const string& name,
											   const TSpatialPosition spos,
											   TGeodeticRefFrame* GRF) 
	: TA3DEuclideanRefFrame( name ), /*fEllipsoid( ellipsoid ),*/ fOrigin( spos ),
	fGeodeticSys( GRF ),fFalseOrigin(0,0,0, TCoordSysFactory::k3DCartesian),
	fOrientationMatrix(GRF)
{	
	TRotationMatrix id;
	id.identity();
	fOrientationMatrix.setElements(id);
}


TModifiedLocalGeodeticRF::TModifiedLocalGeodeticRF( const string& name,
											   const TSpatialPosition spos,
											   const TFreeVector falseOrigin,
											   const TSpatialOrientation orientation,
											   TGeodeticRefFrame* GRF) 
	: TA3DEuclideanRefFrame( name ), /*fEllipsoid( ellipsoid ),*/ fOrigin( spos ),
	fFalseOrigin( falseOrigin ), fOrientationMatrix( orientation ), fGeodeticSys( GRF )
{	// constructor taking the name of the reference frame
}


TModifiedLocalGeodeticRF::TModifiedLocalGeodeticRF( const string& name,
								   TSpatialPosition origin, TFreeVector falseOrigin, 
								   const TAngle gis, const TAngle slope)
	: TA3DEuclideanRefFrame(name), fOrigin(origin), fFalseOrigin(falseOrigin), fOrientationMatrix(0)

{
	// geodetic reference frame
	fGeodeticSys = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF();
	
	// ellipsoid
//	fEllipsoid = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getLocalGeodeticRF()->getReferenceEllipsoid();

	// origin
	origin.transform(fGeodeticSys);
	//fOrigin = origin;


	// orientation angles
	// orientation in CCS as a spatial vector
	//TSpatialVector unitVector(TGraph::getGraph()->getRefFrame(TGraph::kCCS));
	TAngle alpha(slope), beta(gis);
	TFreeVector vector(alpha.cosine()*beta.sine(), alpha.cosine()*beta.cosine(),
		alpha.sine(), TCoordSysFactory::k3DCartesian);
	//unitVector.setElements(vector);

	TAngle azcern(37.77864 * TAngle::gonsToRadsFactor());
	TAngle phiP0, lambdaP0;
	TVReferenceFrame* rf = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS);
	phiP0 = rf->getOrigin().getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid();
	lambdaP0 = rf->getOrigin().getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid();
	TZAxisRotation r1( ( (azcern + TAngle::piBy2()).getRadiansValue() ) );
	TRotation r2( TRotationMatrix::kRzyx, 0, (TAngle::piBy2().getRadiansValue() - phiP0.getRadiansValue()),
		(TAngle::pi().getRadiansValue() - lambdaP0.getRadiansValue()) );
	r1.transform( vector );
	r2.transform( vector );

	TRotation r3( TRotationMatrix::kRzyx, 0, 
		TAngle::piBy2().getRadiansValue() - origin.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid(/*fEllipsoid*/).getRadiansValue(),
		TAngle::pi().getRadiansValue() - origin.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid(/*fEllipsoid*/).getRadiansValue() );
	r3.invert();
	r3.transform( vector );
	TLength ycomp( - (vector.getY().getMetresValue()) );
	vector.setY( ycomp );


	TAngle bearing(TAngle::aTan2( vector.getY().getMetresValue(),
		vector.getX().getMetresValue() ));
	TRotationMatrix orientation(TRotationMatrix::kRzyx, 0,0,bearing.getRadiansValue());
	fOrientationMatrix.setElements(orientation);
	
}



//TModifiedLocalGeodeticRF::TModifiedLocalGeodeticRF( const  TModifiedLocalGeodeticRF& original )
//{// **Deliberately not implemented**
	// copy constructor
//}


TModifiedLocalGeodeticRF::~TModifiedLocalGeodeticRF()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
//TModifiedLocalGeodeticRF&  TModifiedLocalGeodeticRF::operator=(const TModifiedLocalGeodeticRF& right)
//{	
// **Deliberately not implemented**
// Copy Assignment operator
//
//	if (this != &right)
//	{
//	}
//	return *this;
//}


//////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////

