// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TModifiedLocalAstronomicalRF.cpp
//
/**
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
TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const std::string& name, TRefSystemFactory::EGeoid geoid,
								   TSpatialPosition origin, TFreeVector falseOrigin, 
								   const TAngle gis, const TAngle slope) :
	TAModifiedLocalAstronomicalRF(name), fOrientationMatrix(fGeoidRefFrame), 
	fGis(gis), fSlope(slope), fGeoid(geoid)
{
	// get geoid model and the associated reference frame
	TAGeoidModel *geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);
	fGeoidRefFrame = static_cast<TGeodeticRefFrame*>(geoidModel->getDefRefFrame());
	if (!fGeoidRefFrame)
	{
		throw std::runtime_error("TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF: Geoid model must be referenced in a geodetic reference frame");
	}

	//Transformation of the origin (principal point) to a Geodetic Cartesian Reference frame
	if (origin.getRefFrame() != fGeoidRefFrame)
	{
		origin.transform(fGeoidRefFrame);
		origin.changeRefFrameTo(fGeoidRefFrame);
	}
	fOrigin = origin;
	fOriginDefined = true;

	// false origin
	setFalseOrigin(falseOrigin);

	//get deviation of vertical values at principal point
	setEta( geoidModel->getEta(origin) );
	setXsi( geoidModel->getXi(origin) );
	setDAlpha( geoidModel->getDAlpha(origin) );

	//set reference Ellipsoid
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
	unitVector.transform(fGeoidRefFrame);

	//set rotation matrix for GC to LG system
	TRotation r(TRotationMatrix::kRzyx,LITERAL(0.0),
		TAngle::piBy2().getRadiansValue() - fGeoidRefFrame->getGeodeticCoords( &origin, ell).getPhiEllipsoid().getRadiansValue(),
		TAngle::pi().getRadiansValue() - fGeoidRefFrame->getGeodeticCoords(&origin, ell).getLambdaEllipsoid().getRadiansValue());
	r.invert();

	// between local geodetic and local astronomical systems
	TRotation r2(TRotationMatrix::kRzyx, getEta().getRadiansValue(),
		-(getXsi().getRadiansValue()),
		getDAlpha().getRadiansValue());
	r2.invert();

	// reflections
	TReflection  p( TReflection::kYEqual0 );


	TCompositeAffTransform* comp = new TCompositeAffTransform( r2( p( r ) ) );

	//transform orientation vector to LA
	vector = unitVector.getElements(TCoordSysFactory::k3DCartesian);
	comp->transform(vector);

	delete comp;

	//set spatial orientation
	// azimut of the vector projection on the xy-plane
	TReal x(vector.getX().getMetresValue()), y(vector.getY().getMetresValue());
	TAngle az, zero(LITERAL(0.0));
	az.setRadiansValue((TAngle::aTan2(y,x).getRadiansValue()));
	// construction of the orientation matrix
	TSpatialOrientation spatialOrientation(TRotationMatrix::kRzyx, zero, zero, az,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = spatialOrientation;

	fTransformation = 0;
}


TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const std::string& name, TRefSystemFactory::EGeoid geoid)
    : TAModifiedLocalAstronomicalRF(name),
	fOrigin (TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS), 0, 0, 0, TCoordSysFactory::k3DCartesian),
	fOrientationMatrix(fGeoidRefFrame), fGis(0), fSlope(0), fGeoid(geoid)
{	
	// get geoid model and the associated reference frame
	TAGeoidModel *geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);
	fGeoidRefFrame = static_cast<TGeodeticRefFrame *>(geoidModel->getDefRefFrame());
	if (!fGeoidRefFrame)
	{
		throw std::runtime_error("TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF: Geoid model must be referenced in a geodetic reference frame");
	}
	fOriginDefined = false;

	//false origin
	TFreeVector vector(0,0,0,TCoordSysFactory::k3DCartesian);
	setFalseOrigin( vector );

	// geoid parameters
	setEta( geoidModel->getEta(fOrigin) );
	setXsi( geoidModel->getXi(fOrigin) );
	setDAlpha( geoidModel->getDAlpha(fOrigin) );

	fTransformation = 0;
}


TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const std::string& name, TRefSystemFactory::EGeoid geoid,
								   TSpatialPosition origin)
    : TAModifiedLocalAstronomicalRF(name), fOrigin(origin), fOrientationMatrix(fGeoidRefFrame), fGis(0), fSlope(0), fGeoid(geoid)
{	
	// get geoid model and the associated reference frame
	TAGeoidModel *geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);
	fGeoidRefFrame = static_cast<TGeodeticRefFrame *>(geoidModel->getDefRefFrame());
	if (!fGeoidRefFrame)
	{
		throw std::runtime_error("TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF: Geoid model must be referenced in a geodetic reference frame");
	}

	// origin
	fOriginDefined = true;

	// false origin
	TFreeVector vector(0,0,0,TCoordSysFactory::k3DCartesian);
	setFalseOrigin( vector );

	// orientation matrix
	TReal zero(0);
	TSpatialOrientation orientation(TRotationMatrix::kRzyx,zero,zero,zero,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = orientation;

	setEta( geoidModel->getEta(origin) );
	setXsi( geoidModel->getXi(origin) );
	setDAlpha( geoidModel->getDAlpha(origin) );

	fTransformation = 0;
}


TModifiedLocalAstronomicalRF::TModifiedLocalAstronomicalRF( const std::string& name, TRefSystemFactory::ERefEll ell,
								   TSpatialPosition origin)
    : TAModifiedLocalAstronomicalRF(name),
	fOrigin(origin), 
	fOrientationMatrix(fGeoidRefFrame),
	fGis(0), fSlope(0)
{
	ignoring(ell);
	// origin
	fOriginDefined = true;

	// false origin
	TFreeVector vector(0,0,0,TCoordSysFactory::k3DCartesian);
	setFalseOrigin( vector );

	// orientation matrix
	TReal zero(0);
	TSpatialOrientation orientation(TRotationMatrix::kRzyx,zero,zero,zero,
		TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0),
		TCoordSysFactory::k3DCartesian);
	fOrientationMatrix = orientation;

	// geoid parameters
	fGeoid = TRefSystemFactory::kNoGeoid;
	TAngle ang(LITERAL(0.0));
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
TPositionVector TModifiedLocalAstronomicalRF::getCoordinates(const TSpatialPosition * sp, TCoordSysFactory::ECoordSys coordsys) const
{
	if (coordsys == TCoordSysFactory::k3DCartesian)
		return getPositionVector(sp);
	if (coordsys == TCoordSysFactory::kGeodetic || coordsys == TCoordSysFactory::kGeodeticSphere)
		return fGeoidRefFrame->getCoordinates(sp, coordsys);

	return TPositionVector(TCoordSysFactory::k3DCartesian);
}

TGeodeticRefFrame* TModifiedLocalAstronomicalRF::getGeodeticRF() const 
{ 
	return fGeoidRefFrame; 
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
