// TModifiedLocalAstronomicalRF.cpp
//
/**
    Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// other forward declarations
#include  "TModifiedLocalAstronomicalRF.h"
#include  "TRotation.h"
#include  "TReflection.h"
#include  "TMLA2GCTransformation.h"
#include  "TGC2MLATransformation.h"
#include  "TRefSystemFactory.h"
////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const string& name, TRefSystemFactory::EGeoid geoid,
								   TSpatialPosition origin, TFreeVector falseOrigin, 
								   const TAngle gis, const TAngle slope)
	: TAModifiedLocalAstronomicalRF(name),fOrigin(fGeodeticSys), fOrientationMatrix(fGeodeticSys), 
	fGeodeticSys(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()),
	fGis(gis), fSlope(slope)
{
	//identify geodetic system 
	if( geoid == TRefSystemFactory::kCGSphere)
	{
		fGeodeticSys = TRefSystemFactory::getRefSystemFactory()->getGeoRefFrame(TRefSystemFactory::kCGRFSphere);
	}
	else
	{
		fGeodeticSys = TRefSystemFactory::getRefSystemFactory()->getGeoRefFrame(TRefSystemFactory::kCGRF);
	}

	//Transformation of the origin (principal point) to a Geodetic Cartesian Reference frame
	if(origin.getRefFrame() != fGeodeticSys)
	{
		origin.transform(fGeodeticSys);
		origin.changeRefFrameTo(fGeodeticSys);
	}
	fOrigin = origin;
	fOriginDefined = true;


	// false origin
	setFalseOrigin(falseOrigin);

	//get geoid model
	fGeoid = geoid;
	TAGeoidModel* geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);

	//create a spatial position for origin
	TSpatialPosition sp(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TPositionVector pos(falseOrigin.getX().getMetresValue(), falseOrigin.getY().getMetresValue(),
		falseOrigin.getZ().getMetresValue(), falseOrigin.getCoordSys());
	sp.setCoordinates(pos);

	//get deviation of vertical values at principal point
	setEta( geoidModel->getEta(origin) );
	setXsi( geoidModel->getXi(origin) );
	setDAlpha( geoidModel->getDAlpha(origin) );

	//set refernec Ellipsoid
	TReferenceEllipsoid* ell = geoidModel->getDefRefEll();


	// orientation angles
	//set orientation vector in CCS
	TSpatialVector unitVector(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TAngle alpha(slope), beta(gis);
	TFreeVector vector( alpha.cosine()*beta.sine(),
						alpha.cosine()*beta.cosine(),
						alpha.sine(),
						TCoordSysFactory::k3DCartesian);
	unitVector.setElements(vector);

	//transform orientation vector into GRF
	unitVector.transform(fGeodeticSys);

	//set rotation matrix for GC to LG system
	TRotation r(TRotationMatrix::kRzyx,0.0,
		//TAngle::piBy2().getRadiansValue() - origin.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue(),
		//TAngle::pi().getRadiansValue() - origin.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue());
		TAngle::piBy2().getRadiansValue() - fGeodeticSys->getGeodeticCoords( &origin, ell).getPhiEllipsoid().getRadiansValue(),
		TAngle::pi().getRadiansValue() - fGeodeticSys->getGeodeticCoords( &origin, ell).getLambdaEllipsoid().getRadiansValue());
	r.invert();

	// between local geodetic and local astronomical systems
	TRotation r2(TRotationMatrix::kRzyx, getEta().getRadiansValue(),
		-(getXsi().getRadiansValue()),
		getDAlpha().getRadiansValue());
	r2.invert();

	// reflections
	TReflection  p( TReflection::kYEqual0 );


	TCompositeAffTransform* comp = new TCompositeAffTransform(r2 * p * r );

	//transform orientation vector to LA
	vector = unitVector.getElements(TCoordSysFactory::k3DCartesian);
	comp->transform(vector);

	delete comp;

	//set spatial orientation
	// azimut of the vector projection on the xy-plane
	quad x(vector.getX().getMetresValue()), y(vector.getY().getMetresValue());
	TAngle az, zero(0.0);
	az.setRadiansValue((TAngle::aTan2(y,x).getRadiansValue()));
	// construction of the orientation matrix
	TSpatialOrientation spatialOrientation(TRotationMatrix::kRzyx, zero, zero, az,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = spatialOrientation;

	fTransformation = 0;
}


TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const string& name, TRefSystemFactory::EGeoid geoid)
    : TAModifiedLocalAstronomicalRF(name),
	fOrigin (TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS), 0, 0, 0, TCoordSysFactory::k3DCartesian), fGeodeticSys(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()),
	fOrientationMatrix(fGeodeticSys), fGis(0), fSlope(0)
{
	fOriginDefined = false;

	//false origin
	TFreeVector vector(0,0,0,TCoordSysFactory::k3DCartesian);
	setFalseOrigin( vector );

	// geoid parameters
	TAGeoidModel* geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);
	setEta( geoidModel->getEta(fOrigin) );
	setXsi( geoidModel->getXi(fOrigin) );
	setDAlpha( geoidModel->getDAlpha(fOrigin) );

	fTransformation = 0;
}


TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const string& name, TRefSystemFactory::EGeoid geoid,
								   TSpatialPosition origin)
    : TAModifiedLocalAstronomicalRF(name),
	fGeodeticSys(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()),
	fOrigin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()), 
	fOrientationMatrix(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()),
	fGis(0), fSlope(0)
{
	// origin
	fOrigin = origin;
	fOriginDefined = true;

	// false origin
	TFreeVector vector(0,0,0,TCoordSysFactory::k3DCartesian);
	setFalseOrigin( vector );

	// orientation matrix
	quad zero(0);
	TSpatialOrientation orientation(TRotationMatrix::kRzyx,zero,zero,zero,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = orientation;

	// geodetic reference frame
	//fGeodeticSys = TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF();

	// geoid parameters
	fGeoid = geoid;
	TAGeoidModel* geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);
	setEta( geoidModel->getEta(origin) );
	setXsi( geoidModel->getXi(origin) );
	setDAlpha( geoidModel->getDAlpha(origin) );

	fTransformation = 0;
}


TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const string& name, TRefSystemFactory::ERefEll ell,
								   TSpatialPosition origin)
    : TAModifiedLocalAstronomicalRF(name),
	fGeodeticSys(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()),
	fOrigin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()), 
	fOrientationMatrix(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getGeodeticRF()),
	fGis(0), fSlope(0)
{
	// origin
	fOrigin = origin;
	fOriginDefined = true;

	// false origin
	TFreeVector vector(0,0,0,TCoordSysFactory::k3DCartesian);
	setFalseOrigin( vector );

	// orientation matrix
	quad zero(0);
	TSpatialOrientation orientation(TRotationMatrix::kRzyx,zero,zero,zero,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = orientation;

	// geoid parameters
	fGeoid = TRefSystemFactory::kNoGeoid;
	TAngle ang(0.0);
	setEta( ang );
	setXsi( ang );
	setDAlpha( ang );

	fTransformation = 0;

}


TModifiedLocalAstronomicalRF::~TModifiedLocalAstronomicalRF()
{
	if(	fTransformation != 0)
	{
		delete fTransformation;
	}
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
void	TModifiedLocalAstronomicalRF::initialiseMLA(TSpatialPosition origin)
{
	//Transformation of the origin (principal point) to a Geodetic Cartesian Reference frame
	if(origin.getRefFrame() != fGeodeticSys)
	{
		origin.transform(fGeodeticSys);
		origin.changeRefFrameTo(fGeodeticSys);
	}
	setOrigin(origin);

	// false origin
	TFreeVector falseOrigin = getFalseOrigin();

	//get geoid model
	TAGeoidModel* geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(fGeoid);

	//create a spatial position for origin
	TSpatialPosition sp(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TPositionVector pos(falseOrigin.getX().getMetresValue(), falseOrigin.getY().getMetresValue(),
		falseOrigin.getZ().getMetresValue(), falseOrigin.getCoordSys());
	sp.setCoordinates(pos);

	//get deviation of vertical values at principal point
	setEta( geoidModel->getEta(origin) );
	setXsi( geoidModel->getXi(origin) );
	setDAlpha( geoidModel->getDAlpha(origin) );

	//set refernec Ellipsoid
	TReferenceEllipsoid* ell = geoidModel->getDefRefEll();

	// orientation angles
	//set orientation vector in CCS
	TSpatialVector unitVector(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TAngle alpha(fSlope), beta(fGis);
	TFreeVector vector( alpha.cosine()*beta.sine(),
						alpha.cosine()*beta.cosine(),
						alpha.sine(),
						TCoordSysFactory::k3DCartesian);
	unitVector.setElements(vector);

	//transform orientation vector into GRF
	unitVector.transform(fGeodeticSys);

	//set rotation matrix for GC to LG system
	TRotation r(TRotationMatrix::kRzyx,0.0,
				TAngle::piBy2().getRadiansValue() - fGeodeticSys->getGeodeticCoords( &origin, ell).getPhiEllipsoid().getRadiansValue(),
				TAngle::pi().getRadiansValue() - fGeodeticSys->getGeodeticCoords( &origin, ell).getLambdaEllipsoid().getRadiansValue());
	r.invert();

	// between local geodetic and local astronomical systems
	TRotation r2(TRotationMatrix::kRzyx, getEta().getRadiansValue(),
				-(getXsi().getRadiansValue()),
				getDAlpha().getRadiansValue());
	r2.invert();

	// reflections
	TReflection  p( TReflection::kYEqual0 );


	TCompositeAffTransform* comp = new TCompositeAffTransform(r2 * p * r );

	//transform orientation vector to LA
	vector = unitVector.getElements(TCoordSysFactory::k3DCartesian);
	comp->transform(vector);

	delete comp;

	//set spatial orientation
	// azimut of the vector projection on the xy-plane
	quad x(vector.getX().getMetresValue()), y(vector.getY().getMetresValue());
	TAngle az, zero(0.0);
	az.setRadiansValue((TAngle::aTan2(y,x).getRadiansValue()));
	// construction of the orientation matrix
	TSpatialOrientation spatialOrientation(TRotationMatrix::kRzyx, zero, zero, az,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = spatialOrientation;
}









void	TModifiedLocalAstronomicalRF::initialiseLA(TSpatialPosition origin)
{
	//Transformation of the origin (principal point) to a Geodetic Cartesian Reference frame
/*	if(origin.getRefFrame() != fGeodeticSys)
	{
		origin.transform(fGeodeticSys);
		origin.changeRefFrameTo(fGeodeticSys);
	}*/
	setOrigin(origin);

	// orientation matrix
	quad zero(0);
	TSpatialOrientation orientation(TRotationMatrix::kRzyx,zero,zero,zero,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = orientation;


	// geoid parameters
	TAGeoidModel* geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(fGeoid);
	setEta( geoidModel->getEta(origin) );
	setXsi( geoidModel->getXi(origin) );
	setDAlpha( geoidModel->getDAlpha(origin) );

}











TGeodeticRefFrame* TModifiedLocalAstronomicalRF::getGeodeticRF() const 
{ 
	return fGeodeticSys; 
}



TARefFrameTransformation* TModifiedLocalAstronomicalRF::getRFTransfo2CGRF()
{//transformation from this reference frame to CGRF (in case of a reference frame not included in TGraph)

	if(	fTransformation == 0)
	{
		fTransformation = new TMLA2GCTransformation(this, TRefSystemFactory::getRefSystemFactory()->getGeoid(this->getGeoid()));
	}

	return fTransformation;
}


bool	TModifiedLocalAstronomicalRF::setOrigin(const TSpatialPosition& origin)
{//set the origin of the MLA
	if(origin.getObjectStatus()!=TSpatialStatus::kPosNull)
	{
		fOrigin= origin;
		fOriginDefined = true;
	}
	else
	{
		fOriginDefined = false;
	}

	return fOriginDefined;
}


bool	TModifiedLocalAstronomicalRF::isOriginSet() const
{//!return true if the origin is set
	return fOriginDefined;
}



bool	TModifiedLocalAstronomicalRF::transform(TSpatialPosition* sp, TAReferenceFrame* rf)
{//! transform a position from a reference frame to another

	TPositionVector position(sp->getCoordinates(sp->getCoordSys()));
	TRefFrameWrapper from, to;

	//MLA to CGRF
	getRFTransfo2CGRF()->transform(position);
	sp->changeRefFrameTo(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
	sp->setCoordinates(position);


	if(fGeoid == TRefSystemFactory::kCGSphere)
	{
		from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere));
		to.setFrame(rf);
	}
	else
	{
		from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		to.setFrame(rf);
	}


	if (from.getFrame() != to.getFrame() )
	{
		vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
	
		if (transfo[0] == 0)
		{return false;}

		// reverse the order of the vector to have transformations as applicated to the point
		reverse(transfo.begin(), transfo.end());

		// application of the successive transformations
		vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
		vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

		while (iter != iterEnd )
		{
			(*iter)->transform(position);
			iter++;
		}

		sp->changeRefFrameTo(to.getFrame());
		sp->setCoordinates(position);
	}

	return true;
}


bool	TModifiedLocalAstronomicalRF::transform(TSpatialVector* sv, TAReferenceFrame* rf)
{//! transform a position from a reference frame to another

	TFreeVector vec(sv->getElements(sv->getCoordSys()));
	TRefFrameWrapper from, to;

	//MLA to CGRF
	getRFTransfo2CGRF()->transform(vec);
	sv->changeRefFrameTo(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
	sv->setElements(vec);


	if(fGeoid == TRefSystemFactory::kCGSphere)
	{
		from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere));
		to.setFrame(rf);
	}
	else
	{
		from.setFrame(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		to.setFrame(rf);
	}


	if (from.getFrame() != to.getFrame() )
	{
		vector<TARefFrameTransformation*> transfo = TGraph::getGraph()->getTransform(from, to);
	
		if (transfo[0] == 0)
		{return false;}

		// reverse the order of the vector to have transformations as applicated to the point
		reverse(transfo.begin(), transfo.end());

		// application of the successive transformations
		vector<TARefFrameTransformation*>::iterator iter = transfo.begin();
		vector<TARefFrameTransformation*>::iterator iterEnd = transfo.end();

		while (iter != iterEnd )
		{
			(*iter)->transform(vec);
			iter++;
		}

		sv->changeRefFrameTo(to.getFrame());
		sv->setElements(vec);
	}

	return true;
}



