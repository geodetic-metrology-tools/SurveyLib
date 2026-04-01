// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

//  TRefSystemFactory.cpp
//
/* Factory for reference surfaces, reference frames et reference frame transformations. 
  
   
*/

#include <array>
#include <iomanip>
#include <limits>

#include "GeodeticConstants.h"

#include <TReferenceEllipsoid.h>
#include <TGeodeticRefFrame.h>
#include <TTerrestrialReferenceFrame.h>
#include <TAModifiedLocalAstronomicalRF.h>
#include <TModifiedLocalAstronomicalRF.h>
#include <TGraphMLARF.h>
#include <TXYHeProjection.h>
#include <TX0Y0HeProjection.h>
#include <TXYHgProjection.h>
#include <TCernGridGeoid.h>
#include <CernGridGeoidData.h>
#include <TCernParabolicGeoid.h>
#include <TCernSphereGeoid.h>
#include <T3DLocalRefFrame.h>
#include <TLV95Projection.h>
#include <TLV03Projection.h>
#include <TRGF93CC46Projection.h>
#include <TLambert93Projection.h>
#include <TTransverseMercatorProjection.h>
#include <TLocalRFWithTransformationMatrix.h>


#include <TMLA2GCTransformation.h>
#include <TGC2MLATransformation.h>
#include <TXYHs2MLATransformation.h>
#include <TMLA2XYHsTransformation.h>
#include <TLA2LGTransformation.h>
#include <TLG2LATransformation.h>
#include <TLG2GCTransformation.h>
#include <TGC2LGTransformation.h>
#include <TGeodetic2Mercator.h>
#include <THelmertTransformation.h>
#include <THelmertRefFrameTransform.h>
#include <TXYHe2MLATransformation.h>
#include <TMLA2XYHeTransformation.h>
#include <TX0Y0He2XYHeTransformation.h>
#include <TXYHe2X0Y0HeTransformation.h>
#include <TXYHg2XYHeTransformation.h>
#include <TXYHe2XYHgTransformation.h>
#ifdef USE_SWISSTOPO
	#include <TLV95Transformation.h>
	#include <TLV03Transformation.h>
#endif
#include <TRGF93CC46Transformation.h>
#include <TLambert93Transformation.h>
#include <TTrf2TrfTransformation.h>


#include "TRefSystemFactory.h"
#include <TLocal2CCSTransformation.h>

//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
// fGraph initialisation to 0
TRefSystemFactory*  TRefSystemFactory::fRefSystemFactory = 0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TRefSystemFactory::TRefSystemFactory()
{// default constructor: build the unique instance of TRefSystemFactory
}



TRefSystemFactory::~TRefSystemFactory()
{// destructor
}


//////////////////////////////////////////////////////////////////////
//INIT FUNCTION
//////////////////////////////////////////////////////////////////////
void TRefSystemFactory::init()
{// Build the unique instance of TRefSystemFactory
	
	// Definition of the ellipsoid list
	initEllipsoidList();

	// Definition of the reference frame list
	addGeodeticRefFrames();
	addGenericETRFandITRF();
	addSpecificETRFandITRF();
	addLocalGeodeticAndLocalAstronomic();
	addLocalCADRefFrames();

	// Definition of the geoid list
	initGeoidList();

	// Definition of the projection (included in the reference frame list)
	addFrenchProjections();
	addSwissProjections();
	addCERNprojections();

	// Definition of the CERN's ref. frames transformations
	addCERNrefFrameTransformation();
	addTerrestrialRefFramesTransformations();
	addSwissTransformations();  
	addFrenchTransformations();
	addCERNprojectionsTransformations();        
	addLocalRefFrameTransformations();
}

void TRefSystemFactory::initEllipsoidList()
{
	///////////////////////////////////////////////////////////////////
	// Definition of the ellipsoid list

	// Sphere SPS
	addObject(fRefEllList, "SphereSPS", LITERAL(6371000.0), LITERAL(0.0), kSphere);

	// GRS80
	addObject(fRefEllList, "GRS80", LITERAL(6378137.0), LITERAL(298.257222101), kGRS80);

	// WGS84
	addObject(fRefEllList, "WGS84 Ellipsoid", LITERAL(6378137.0), LITERAL(298.257223563), kWGSEll);

	// Hayford
	addObject(fRefEllList, "Hayford1903 Ellipsoid", LITERAL(6378388.0), LITERAL(297), kInternationalEll);

	// Bessel 1841
	addObject(fRefEllList, "Bessel Ellipsoid", LITERAL(6377397.155), LITERAL(299.1528128), kBessel1841);
}

void TRefSystemFactory::initGeoidList()
{
	///////////////////////////////////////////////////////////////////////////////
	// Definition of the geoid list

	auto pCCS = getRefFrame(kCCS);
	auto pCGRF = getRefFrame(kCGRF);
	auto pCGRFs = getRefFrame(kCGRFSphere);
	auto pGRS80 = getEllipsoid(kGRS80);
	auto pSphere = getEllipsoid(kSphere);

	std::string cg00("CG2000 h=0"), cg00topo("CG2000 h=surface"), cg00Machine("CG2000 h=Machine"), cg85("CG1985 h=0"), cg85Machine("CG1985 h=Machine"), cgSphere("Sphere");

	TPositionVector dl(-5000, 0, 0, TCoordSysFactory::k3DCartesian), ur(6000, 15000, 0, TCoordSysFactory::k3DCartesian);

	// CG2000 h=0
	TCernGridGeoid *pCG2000 = createCernGridGeoid(cg00, CernGridGeoidData::nCG2000h0, CernGridGeoidData::etaCG2000h0, CernGridGeoidData::xsiCG2000h0, dl, ur, kCG2000);
	fGeoidList.push_back(pCG2000);

	// CG2000 h=topo
	TCernGridGeoid *pCG2000Topo = createCernGridGeoid(
		cg00topo, CernGridGeoidData::nCG2000hTopo, CernGridGeoidData::etaCG2000hTopo, CernGridGeoidData::xsiCG2000hTopo, dl, ur, kCG2000topo);
	fGeoidList.push_back(pCG2000Topo);

	// CG2000 h=Machine
	TCernGridGeoid *pCG2000Machine = createCernGridGeoid(
		cg00Machine, CernGridGeoidData::nCG2000hMachine, CernGridGeoidData::etaCG2000hMachine, CernGridGeoidData::xsiCG2000hMachine, dl, ur, kCG2000Machine);
	fGeoidList.push_back(pCG2000Machine);

	// CGSphere
	TCernSphereGeoid *pCGSphere = new TCernSphereGeoid(cgSphere, kCGSphere, pCGRFs, pSphere, pCCS);
	fGeoidList.push_back(pCGSphere);

	// CG1985 h=0
	TAngle ang;
	ang.setGonsValue(LITERAL(48.772));
	TReal a(LITERAL(0.535)), b(-LITERAL(0.096)), th(ang.getRadiansValue());
	TCernParabolicGeoid *pCG1985 = new TCernParabolicGeoid(cg85, kCG1985, a, b, th, pCGRF, pGRS80, pCCS);
	fGeoidList.push_back(pCG1985);

	// CG1985 h=Machine
	TAngle angLEP;
	angLEP.setGonsValue(LITERAL(48.219));
	TReal aLEP(LITERAL(0.614)), bLEP(-LITERAL(0.106)), thLEP(angLEP.getRadiansValue());
	TCernParabolicGeoid *pCG1985Machine = new TCernParabolicGeoid(cg85Machine, kCG1985Machine, aLEP, bLEP, thLEP, pCGRF, pGRS80, pCCS);
	fGeoidList.push_back(pCG1985Machine);
}

void TRefSystemFactory::addCERNprojections()
{
	auto pCCS = getRefFrame<TAModifiedLocalAstronomicalRF>(kCCS);

	// CERN XYHs projection: XY system = CCS, Hs = height above SPS sphere (projection of the xy point on the sphere)
	createObjectSetIdAndAddToList<TXYHeProjection>(kCERNXYHsSphereSPS, fRefFrameList, "CERN_XYHs", getEllipsoid(TRefSystemFactory::kSphere), pCCS);

	// CERN XYHe projection: XY system = CCS, He = height above ellipsoid (projection of the xy point on the ellipsoid)
	createObjectSetIdAndAddToList<TXYHeProjection>(kCernXYHe, fRefFrameList, "CERN_XYHe", getEllipsoid(TRefSystemFactory::kGRS80), pCCS);
	auto pCernXYHe = getRefFrame<TXYHeProjection>(kCernXYHe);

	// CERN X0Y0He projection: X0Y0 = projection of XY on the ellipsoid's level (h=0)
	createObjectSetIdAndAddToList<TX0Y0HeProjection>(kCernX0Y0He, fRefFrameList, "CERN_X0Y0He", pCernXYHe);

	// CERN XYHg projection CG2000: XY system = CCS, Hg = height above geoid CG2000 (projection of the xy point on the geoid)
	createObjectSetIdAndAddToList<TXYHgProjection>(kCernXYHg00, fRefFrameList, "CERN_XYHg2000", getGeoid(kCG2000), pCernXYHe);

	// CERN XYHg projection CG2000Topo :XY system = CCS, Hg = height above geoid CG2000Topo (projection of the xy point on the geoid)
	createObjectSetIdAndAddToList<TXYHgProjection>(kCernXYHg00Topo, fRefFrameList, "CERN_XYHg2000Topo", getGeoid(kCG2000topo), pCernXYHe);

	// CERN XYHg projection CG2000Machine: XY system = CCS, Hg = height above geoid CG2000Machine (projection of the xy point on the geoid)
	createObjectSetIdAndAddToList<TXYHgProjection>(kCernXYHg00Machine, fRefFrameList, "CERN_XYHg2000Machine", getGeoid(kCG2000Machine), pCernXYHe);

	// CERN XYHg projection CG1985: XY system = CCS, Hg = height above geoid CG1985 (projection of the xy point on the geoid)
	createObjectSetIdAndAddToList<TXYHgProjection>(kCernXYHg85, fRefFrameList, "CERN_XYHg1985", getGeoid(kCG1985), pCernXYHe);

	// CERN XYHg projection CG1985Machine: XY system = CCS, Hg = height above geoid CG1985Machine (projection of the xy point on the geoid)
	createObjectSetIdAndAddToList<TXYHgProjection>(kCernXYHg85Machine, fRefFrameList, "CERN_XYHg1985Machine", getGeoid(kCG1985Machine), pCernXYHe);

	// CGRF Transverse Mercator Projection
	createObjectSetIdAndAddToList<TTransverseMercatorProjection>(kCGRFMercator_eh, fRefFrameList, "CGRFtm_eh");
}

void TRefSystemFactory::addGeodeticRefFrames()
{
	// new CGRF (coordinate of P0 have been changed) (not used)
	createObjectSetIdAndAddToList<TGeodeticRefFrame>(kCGRF_new, fRefFrameList, "new_CGRF", getEllipsoid(TRefSystemFactory::kGRS80));
	fCGRF2 = getRefFrame<TGeodeticRefFrame>(kCGRF_new);

	// CGRF
	createObjectSetIdAndAddToList<TGeodeticRefFrame>(kCGRF, fRefFrameList, "CGRF", getEllipsoid(TRefSystemFactory::kGRS80));
	fCGRF = getRefFrame<TGeodeticRefFrame>(kCGRF);

	// CGRF sphere
	createObjectSetIdAndAddToList<TGeodeticRefFrame>(kCGRFSphere, fRefFrameList, "CGRFSphere", getEllipsoid(TRefSystemFactory::kSphere));
	fCGRFSphere = getRefFrame<TGeodeticRefFrame>(kCGRFSphere);
}

void TRefSystemFactory::addGenericETRFandITRF()
{
	std::string itrfIn("ITRFin"), itrfOut("ITRFout"), etrfIn("ETRFin"), etrfOut("ETRFout");
	TReal initEpoch = NO_VALf;
	std::string initSolution = "noSolution";

	// Generic ITRF solution at specified epoch (input)
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kITRFin, fRefFrameList, itrfIn, getEllipsoid(TRefSystemFactory::kGRS80), initEpoch, initSolution);
	fITRFin = getRefFrame<TTerrestrialReferenceFrame>(kITRFin);

	// Generic ITRF solution at specified epoch (output)
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kITRFout, fRefFrameList, itrfOut, getEllipsoid(TRefSystemFactory::kGRS80), initEpoch, initSolution);
	fITRFout = getRefFrame<TTerrestrialReferenceFrame>(kITRFout);

	// Generic ETRF solution at specified epoch (input)
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kETRFin, fRefFrameList, etrfIn, getEllipsoid(TRefSystemFactory::kGRS80), initEpoch, initSolution);
	fETRFin = getRefFrame<TTerrestrialReferenceFrame>(kETRFin);

	// Generic ETRF solution at specified epoch (output)
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kETRFout, fRefFrameList, etrfOut, getEllipsoid(TRefSystemFactory::kGRS80), initEpoch, initSolution);
	fETRFout = getRefFrame<TTerrestrialReferenceFrame>(kETRFout);
}

void TRefSystemFactory::addSpecificETRFandITRF()
{
	auto grs80 = getEllipsoid(TRefSystemFactory::kGRS80);

	// ITRF97 at epoch 1998.5.Link between global and local frames
	TReal epoch = 1998.5;
	std::string solution = "ITRF 97";
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kITRF97, fRefFrameList, "ITRF97", grs80, epoch, solution);

	// ETRF93
	epoch = 1993;
	solution = "ETRF 93";
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kETRF93, fRefFrameList, "ETRF93", grs80, epoch, solution);

	// RGF93
	epoch = 2019;
	solution = "ETRF 2000";
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kRGF93, fRefFrameList, "RGF93", grs80, epoch, solution);

	// CHTRF95
	epoch = 1993;
	solution = "ETRF 93";
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kCHTRF95, fRefFrameList, "CHTRF95", grs80, epoch, solution);

	// CH1903plus
	createObjectSetIdAndAddToList<TGeodeticRefFrame>(kCH1903plus, fRefFrameList, "CH1903plus", getEllipsoid(TRefSystemFactory::kBessel1841));

	// WGS84 (G2139)
	epoch = 2016;
	solution = "ITRF 2014";
	createObjectSetIdAndAddToList<TTerrestrialReferenceFrame>(kWGS84_G2139, fRefFrameList, "WGS84 (G2139)", getEllipsoid(TRefSystemFactory::kWGSEll), epoch, solution);
}

void TRefSystemFactory::addFrenchProjections()
{
	// FrenchRGF93 zone 5 (CC46)
	createObjectSetIdAndAddToList<TRGF93CC46Projection>(kFrenchRGF93_CC46_eh, fRefFrameList, "FrenchRGF93_CC46_eh");
	createObjectSetIdAndAddToList<TRGF93CC46Projection>(kFrenchRGF93_CC46_ign69, fRefFrameList, "FrenchRGF93_CC46_ign69");

	// Lambert93
	createObjectSetIdAndAddToList<TLambert93Projection>(kLambert93_eh, fRefFrameList, "Lambert93_eh");
	createObjectSetIdAndAddToList<TLambert93Projection>(kLambert93_ign69, fRefFrameList, "Lambert93_ign69");
}

void TRefSystemFactory::addSwissProjections()
{
#ifdef USE_SWISSTOPO
	// Swiss LV95
	createObjectSetIdAndAddToList<TLV95Projection>(kSwissLV95_eh, fRefFrameList, "LV95_eh");
	createObjectSetIdAndAddToList<TLV95Projection>(kSwissLV95_lhn95, fRefFrameList, "LV95_lhn95");
	createObjectSetIdAndAddToList<TLV95Projection>(kSwissLV95_ln02, fRefFrameList, "LV95_ln02");

	// Swiss LV03
	createObjectSetIdAndAddToList<TLV03Projection>(kSwissLV03_eh, fRefFrameList, "LV03_eh");
	createObjectSetIdAndAddToList<TLV03Projection>(kSwissLV03_ln02, fRefFrameList, "LV03_ln02");
	createObjectSetIdAndAddToList<TLV03Projection>(kSwissLV03_lhn95, fRefFrameList, "LV03_lhn95");
#endif
}

void TRefSystemFactory::addLocalGeodeticAndLocalAstronomic()
{
	// Local Geodesique at CERN: origin = principal point of the system = P0
	TAngle phi(LITERAL(PHIP0), TAngle::kGons);
	TAngle lambda(LITERAL(LambdaP0), TAngle::kGons);
	TLength H(LITERAL(HP0));

	TModifiedLocalGeodeticRF *pLGp0 = createModifiedLocalGeodeticRF(fCGRF, "LG PO", phi, lambda, H);
	setIdAndAddToList(pLGp0, kLGp0, fRefFrameList);
	// Local Astronomic at CERN: origin = principal point of the system = P0
	TAngle etaP0(0), xsiP0(0), dAlphaP0(0);
	TGraphLocalAstronomicalRF *pLAp0 = new TGraphLocalAstronomicalRF("LA P0", etaP0, xsiP0, dAlphaP0, pLGp0);
	setIdAndAddToList(pLAp0, kLAp0, fRefFrameList);

	// CCS : CERN Modified Local Astronomical system : principal point = P0 defined as false origin
	TFreeVector falseOrigin(XP0, LITERAL(YP0), LITERAL(ZP0), TCoordSysFactory::k3DCartesian);
	TAngle omega(0), phi2(0), kappa(LITERAL(AzimuthCCSYaxis), TAngle::kGons);

	TAModifiedLocalAstronomicalRF *pCCS = new TGraphMLARF("CCS", falseOrigin, pLAp0, omega, phi2, kappa);
	setIdAndAddToList(pCCS, kCCS, fRefFrameList);

	// new P0 coordinates
	TAngle phi_new(LITERAL(51.36734), TAngle::kGons), lambda_new(LITERAL(6.722515), TAngle::kGons);

	TModifiedLocalGeodeticRF *pLGp0_new = createModifiedLocalGeodeticRF(fCGRF2, "LG P0_new", phi_new, lambda_new, H);
	setIdAndAddToList(pLGp0_new, kLGp0_new, fRefFrameList);

	// Local Astronomic at P0_new
	TGraphLocalAstronomicalRF *pLAp0_new = new TGraphLocalAstronomicalRF("LA P0_new", etaP0, xsiP0, dAlphaP0, pLGp0_new);
	setIdAndAddToList(pLAp0_new, kLAp0_new, fRefFrameList);

	// CCS at P0_new
	TAngle kappa_new(LITERAL(37.779033), TAngle::EUnits::kGons);
	TAModifiedLocalAstronomicalRF *pCCS_new = new TGraphMLARF("CCS_new", falseOrigin, pLAp0_new, omega, phi2, kappa_new);
	setIdAndAddToList(pCCS_new, kCCS_new, fRefFrameList);
}

void TRefSystemFactory::addLocalCADRefFrames()
{
	createObjectSetIdAndAddToList<TLocalRFWithTransformationMatrix>(kLocalRFin, fRefFrameList, "LocalRF_Input", "");
	createObjectSetIdAndAddToList<TLocalRFWithTransformationMatrix>(kLocalRFout, fRefFrameList, "LocalRF_Output", "");
}

void TRefSystemFactory::addCERNrefFrameTransformation()
{
	auto pCernXYHs = getRefFrame<TXYHeProjection>(kCERNXYHsSphereSPS);
	auto pCCS = getRefFrame<TAModifiedLocalAstronomicalRF>(kCCS);
	auto pLAp0 = getRefFrame<TGraphLocalAstronomicalRF>(kLAp0);
	auto pLGp0 = getRefFrame<TModifiedLocalGeodeticRF>(kLGp0);

	// Transformation between CERN projection XYHs and CCS
	addTransformationPair<TXYHs2MLATransformation>(kXYHsSphereSPS2CCS, kCCS2XYHsSphereSPS, pCernXYHs);

	// Transformation between CCS and CGRF
	/*Il est equivalent de mettre CG2000 ou CG1985 car les parametres du geoide au niveau de P0,
	servant a definir la transformation sont equivalent*/
	addTransformationPair<TMLA2GCTransformation>(kCCS2CGRF, kCGRF2CCS, pCCS, getGeoid(kCG1985Machine));

	// Conversion between CGRF (ellipsoid) and CGRF (Transverse Mercator projection)
	addTransformationPair<TGeodetic2Mercator>(kCGRF2CGRFMercator, kCGRFMercator2CGRF, true);

	// Transformation between CCS and CGRFSphere
	// rotation pour diriger les axes du CGRFs parallele a ceux du CGRF
	TAngle rx(-LITERAL(42.726243230216), TAngle::kGons);
	TAngle ry(-LITERAL(25.285434244947), TAngle::kGons);
	TAngle rz(-LITERAL(77.864346765085), TAngle::kGons);
	// translation pour situer le centre de la sphere
	TLength txs(LITERAL(4381882.331989)), tys(LITERAL(461505.530464)), tzs(LITERAL(4598944.364158));
	// facteur d echelle
	TScaleFactor ks(LITERAL(1.0));
	THelmertRefFrameTransform *pCCS2CGRFs = createHelmertRefFrameTransform(pCCS, fCGRFSphere, rx, ry, rz, txs, tys, tzs, ks);
	addTransformationAndInverse(pCCS2CGRFs, kCCS2CGRFSphere, kCGRFSphere2CCS, fTransformList);

	// Transformation between LAp0 and LGp0
	addTransformationPair<TLA2LGTransformation>(kLAp02LGp0, kLGp02LAp0, pLAp0);

	// Transformation between LGp0 and CGRF
	addTransformationPair<TLG2GCTransformation>(kLGp02CGRF, kCGRF2LGp0, pLGp0);

	// Helmert Transformation between LAp0 and CCS
	TAngle omega = pCCS->getOrientation().getElements(TCoordSysFactory::ECoordSys::k3DCartesian).getAngles(TRotationMatrix::kRzyx).omega;
	TAngle phi = pCCS->getOrientation().getElements(TCoordSysFactory::ECoordSys::k3DCartesian).getAngles(TRotationMatrix::kRzyx).phi;
	TAngle kappa = pCCS->getOrientation().getElements(TCoordSysFactory::ECoordSys::k3DCartesian).getAngles(TRotationMatrix::kRzyx).kappa;
	TFreeVector falseOrigin = pCCS->getFalseOrigin();
	TScaleFactor enl(LITERAL(1.0));
	THelmertRefFrameTransform *pLAp02CCS = createHelmertRefFrameTransform(pLAp0, pCCS, omega, phi, -1.0 * kappa, falseOrigin.getX(), falseOrigin.getY(), falseOrigin.getZ(), enl);
	addTransformationAndInverse(pLAp02CCS, kLAp02CCS, kCCS2LAp0, fTransformList);

	// Helmert Transformation between ITRF97 (ep1998.5) and CGRF
	TAngle om3(LITERAL(399.999533213524), TAngle::kGons);
	TAngle p3(LITERAL(0.001825157943), TAngle::kGons);
	TAngle k3(LITERAL(0.000991054274), TAngle::kGons);
	TLength Tx3(LITERAL(76.3768280)), Ty3(LITERAL(131.9389844)), Tz3(-LITERAL(156.1229775));
	TScaleFactor enl3(LITERAL(1.000000000000000));
	THelmertRefFrameTransform *pITRF972CGRF = createHelmertRefFrameTransform(getRefFrame<TTerrestrialReferenceFrame>(kITRF97), fCGRF, om3, p3, k3, Tx3, Ty3, Tz3, enl3);
	addTransformationAndInverse(pITRF972CGRF, kITRF972CGRF, kCGRF2ITRF97, fTransformList);
}

void TRefSystemFactory::addTerrestrialRefFramesTransformations()
{
	auto itrf2020_toPastITRF = makeMatrix(TrfTransformationCoefficients::coeffITRF2020_toPastITRF);
	auto itrfyy_toETRFyy = makeMatrix(TrfTransformationCoefficients::coeffITRFyy_toETRFyy);

	auto pITRFin = getTerrRefFrame(kITRFin);
	auto pITRFout = getTerrRefFrame(kITRFout);
	auto pETRFout = getTerrRefFrame(kETRFout);
	auto pETRFin = getTerrRefFrame(kETRFin);
	auto pITRF97 = getRefFrame<TTerrestrialReferenceFrame>(kITRF97);
	auto pETRF93 = getRefFrame<TTerrestrialReferenceFrame>(kETRF93);
	auto pRGF93 = getRefFrame<TTerrestrialReferenceFrame>(kRGF93);
	auto pCHTRF95 = getRefFrame<TTerrestrialReferenceFrame>(kCHTRF95);
	auto pWGS84_G2139 = getRefFrame<TTerrestrialReferenceFrame>(kWGS84_G2139);

	// Transformation between any ITRF an ITRF97 (ep 1998.5)
	addTrf2TrfTransformationPair(kITRFin2ITRF97, kITRF972ITRFout, pITRFin, pITRF97);

	// Transformation between any ETRF an ITRF97 (ep 1998.5)
	addTrf2TrfTransformationPair(kITRF972ETRFout, kETRFin2ITRF97, pITRF97, pETRFout);

	// Transformation between ITRF97 (ep1998.5) and ETRF93 (ep 1993.0)
	addTrf2TrfTransformationPair(kITRF972ETRF93, kETRF932ITRF97, pITRF97, pETRF93);

	// Transformation between ITRF97 (ep1998.5) and RGF93
	addTrf2TrfTransformationPair(kITRF972RGF93, kRGF932ITRF97, pITRF97, pRGF93);

	// Transformation between ITRF97 (ep1998.5) and CHTRF95
	addTrf2TrfTransformationPair(kITRF972CHTRF95, kCHTRF952ITRF97, pITRF97, pCHTRF95);

	// Transformation between ITRF97 (ep1998.5) and WGS84 (G2139)
	addTrf2TrfTransformationPair(kITRF972WGS84, kWGS842ITRF97, pITRF97, pWGS84_G2139);

	// Transformtion between ITRF and ETRF
	addTrf2TrfTransformationPair(kITRFin2ETRFout, kETRFin2ITRFout, pITRFin, pETRFout);

	// Transformation between 2 ITRF
	TTrf2TrfTransformation *pITRFin2ITRFout = new TTrf2TrfTransformation(pITRFin, pITRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
	setIdAndAddToList(pITRFin2ITRFout, kITRFin2ITRFout, fTransformList);

	// Transformation between 2 ETRF
	TTrf2TrfTransformation *pETRFin2ETRFout = new TTrf2TrfTransformation(pETRFin, pETRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
	setIdAndAddToList(pETRFin2ETRFout, kETRFin2ETRFout, fTransformList);	
}

void TRefSystemFactory::addCERNprojectionsTransformations()
{
	// Transformation between CERN projection XYHe and CCS
	auto pCernXYHe = getRefFrame<TXYHeProjection>(kCernXYHe);
	addTransformationPair<TXYHe2MLATransformation>(kXYHe2CCS, kCCS2XYHe, pCernXYHe);

	// Transformation between CERN projection X0Y0He and CERN projection XYHe
	auto pCernX0Y0He = getRefFrame<TX0Y0HeProjection>(kCernX0Y0He);
	addTransformationPair<TX0Y0He2XYHeTransformation>(kX0Y0He2XYHe, kXYHe2X0Y0He, pCernX0Y0He);

	// Transformation between CERN projection XYHg (Geoid 2000) and XYHe
	auto pCernXYHg00 = getRefFrame<TXYHgProjection>(kCernXYHg00);
	addTransformationPair<TXYHg2XYHeTransformation>(kXYHg2XYHe, kXYHe2XYHg, pCernXYHg00);

	// Transformation between CERN projection XYHg (Geoid 2000Topo) and XYHe
	auto pCernXYHg00Topo = getRefFrame<TXYHgProjection>(kCernXYHg00Topo);
	addTransformationPair<TXYHg2XYHeTransformation>(kXYHg2XYHe00Topo, kXYHe00Topo2XYHg, pCernXYHg00Topo);

	// Transformation between CERN projection XYHg (Geoid 2000Machine) and XYHe
	auto pCernXYHg00Machine = getRefFrame<TXYHgProjection>(kCernXYHg00Machine);
	addTransformationPair<TXYHg2XYHeTransformation>(kXYHg2XYHe00Machine, kXYHe00Machine2XYHg, pCernXYHg00Machine);

	// Transformation between CERN projection XYHg (Geoid 1985) and XYHe
	auto pCernXYHg85 = getRefFrame<TXYHgProjection>(kCernXYHg85);
	addTransformationPair<TXYHg2XYHeTransformation>(kXYHg2XYHe85, kXYHe852XYHg, pCernXYHg85);

	// Transformation between CERN projection XYHg (Geoid 1985Machine) and XYHe
	auto pCernXYHg85Machine = getRefFrame<TXYHgProjection>(kCernXYHg85Machine);
	addTransformationPair<TXYHg2XYHeTransformation>(kXYHg2XYHe85Machine, kXYHe85Machine2XYHg, pCernXYHg85Machine);
}

void TRefSystemFactory::addFrenchTransformations()
{
	// Transformation between projected CC46 and RGF93
	// Ellipsoidal height
	addTransformationPair<TRGF93ZoneTransformation>(kRGF932CC46eh, kCC46eh2RGF93, true, true);

	// Altitude NGF-IGN69
	addTransformationPair<TRGF93ZoneTransformation>(kRGF932CC46ign69, kCC46raf2RGF93, true, false);

	// Transformation between RGF93v2b and Lambert93
	// Ellipsoidal height
	addTransformationPair<TLambert93Transformation>(kRGF932Lambert93eh, kLambert93eh2RGF93, true, true);

	// Altiude NGF-IGN69
	addTransformationPair<TLambert93Transformation>(kRGF932Lambert93ign69, kLambert93ign692RGF93, true, false);
}

void TRefSystemFactory::addSwissTransformations()
{
	////////////////////////////////////////////////////////////////
	// Helmert Transformation between ETRF93 (ep1993) and CH1903plus
	////////////////////////////////////////////////////////////////
	
	// There is no rotation:
	// Total translation resulting from epoch changes and Reference Frame changes:
	TLength Tx3(LITERAL(-674.374)), Ty3(LITERAL(-15.056)), Tz3(LITERAL(-405.346));
	// There is no scaling:
	TScaleFactor enl3(LITERAL(1.000000000000000));
	auto pETRF93 = getRefFrame<TTerrestrialReferenceFrame>(kETRF93);
	auto pCH1903plus = getRefFrame<TGeodeticRefFrame>(kCH1903plus);

	THelmertRefFrameTransform *pETRF932CH1903plus = createHelmertRefFrameTransform(pETRF93, pCH1903plus, TAngle(0), TAngle(0), TAngle(0), Tx3, Ty3, Tz3, enl3);
	addTransformationAndInverse(pETRF932CH1903plus, kETRF932CH1903plus, kCH1903plus2ETRF93, fTransformList);
	
#ifdef USE_SWISSTOPO
	// Transformation between CH1903plus and LV95 (ellipsoidal height)
	addTransformationPair<TLV95Transformation>(kCH1903plus2SwissLV95eh, kSwissLV95eh2CH1903plus, true, "eh");

	// Transformation between CH1903plus and LV95 (orthometric height)
	addTransformationPair<TLV95Transformation>(kCH1903plus2SwissLV95lhn95, kSwissLV95lhn952CH1903plus, true, "lhn95");

	// Transformation between CH1903plus and LV95 (leveled height)
	addTransformationPair<TLV95Transformation>(kCH1903plus2SwissLV95ln02, kSwissLV95ln022CH1903plus, true, "ln02");
	
	// Transformation between LV95 and LV03 (ellipsoidal height)
	addTransformationPair<TLV03Transformation>(kSwissLV95eh2SwissLV03eh, kSwissLV03eh2SwissLV95eh, true, "eh");

	// Transformation between LV95 (ellipsoidal height) and LV03 (leveled height)
	addTransformationPair<TLV03Transformation>(kSwissLV95eh2SwissLV03ln02, kSwissLV03ln022SwissLV95eh, true, "ln02");

	// Transformation between LV95 (ellipsoidal height) and LV03 (orthometric height)
	addTransformationPair<TLV03Transformation>(kSwissLV95eh2SwissLV03lhn95, kSwissLV03lhn952SwissLV95eh, true, "lhn95");
#endif
}

void TRefSystemFactory::addLocalRefFrameTransformations()
{
	// Empty transformation between local RF and CCS (transformation are updated with a transformation file)
	TLocal2CCSTransformation *pLocalRFin2CCS = new TLocal2CCSTransformation(getRefFrame(kLocalRFin), getRefFrame(kCCS), TScaleFactor(), TRotationMatrix(), TTranslation());
	setIdAndAddToList(pLocalRFin2CCS, kLocalRFin2CCS, fTransformList);
	// Inverse
	TLocal2CCSTransformation *pCCS2LocalRFout = new TLocal2CCSTransformation(getRefFrame(kCCS), getRefFrame(kLocalRFout), TScaleFactor(), TRotationMatrix(), TTranslation());
	setIdAndAddToList(pCCS2LocalRFout, kCCS2LocalRFout, fTransformList);
}

void TRefSystemFactory::addTrf2TrfTransformationPair(const ERefFrameTransform &in2out,
	const ERefFrameTransform &out2in, TTerrestrialReferenceFrame *from,
	TTerrestrialReferenceFrame *to)
{
	auto itrf2020_toPastITRF = makeMatrix(TrfTransformationCoefficients::coeffITRF2020_toPastITRF);
	auto itrfyy_toETRFyy = makeMatrix(TrfTransformationCoefficients::coeffITRFyy_toETRFyy);

	// Forward transformation
	TTrf2TrfTransformation *forward = new TTrf2TrfTransformation(from, to, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
	setIdAndAddToList(forward, in2out, fTransformList);
	// Inverse
	TTrf2TrfTransformation *inverse = new TTrf2TrfTransformation(to, from, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
	setIdAndAddToList(inverse, out2in, fTransformList);
}

TModifiedLocalGeodeticRF* TRefSystemFactory::createModifiedLocalGeodeticRF(TGeodeticRefFrame* refFrame,
	const std::string &frameName,
	const TAngle &phi_origine,
	const TAngle &lambda_origin,
	const TLength &h_origin)
{
	TSpatialPosition origin(refFrame);
	TPositionVector pos(TCoordSysFactory::kGeodetic);
	pos.setPhiEllipsoid(phi_origine);
	pos.setLambdaEllipsoid(lambda_origin);
	pos.setH(h_origin);

	origin.setCoordinates(pos);
	origin.setObjectStatus(TSpatialStatus::kCala);

	TModifiedLocalGeodeticRF *pLG = new TModifiedLocalGeodeticRF(frameName, origin, fCGRF);

	return pLG;
}

THelmertRefFrameTransform *TRefSystemFactory::createHelmertRefFrameTransform(TAReferenceFrame *from,
	TAReferenceFrame *to,
	const TAngle &rX,
	const TAngle &rY,
	const TAngle &rZ,
	const TLength &tX,
	const TLength &tY,
	const TLength &tZ,
	const TScaleFactor &scaleFactor)
{
	TRotation rs(TRotationMatrix::kRzyx, rX.getRadiansValue(), rY.getRadiansValue(), rZ.getRadiansValue());
	TTranslation transls(tX, tY, tZ);

	THelmertRefFrameTransform *helmertRFtransform = new THelmertRefFrameTransform(from, to, scaleFactor, rs, transls);
	return helmertRFtransform;
}


//////////////////////////////////////////////////////////////////////
// MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////
TRefSystemFactory* TRefSystemFactory::getRefSystemFactory()
{//returns the unique instance : clients access trought this member function
	if (fRefSystemFactory == 0)
	{
		fRefSystemFactory = new TRefSystemFactory();
		fRefSystemFactory->init();
	}

	return fRefSystemFactory;
}

TAGeoidModel*  TRefSystemFactory::getGeoid(const EGeoid geoidId)
{//return a pointer to the geoid asked for
	return getElementFromList(fGeoidList, geoidId, "GeoidList");
}

TReferenceEllipsoid* TRefSystemFactory::getEllipsoid(const ERefEll ellId)
{//return a pointer to the ellipsoid asked for
	return getElementFromList(fRefEllList, ellId, "RefEllList");
}

TAReferenceFrame* TRefSystemFactory::getRefFrame(const ERefFrame refFrameId)
{//return a pointer to the ref frame askes for
	return getElementFromList(fRefFrameList, refFrameId, "RefFrameList");
}

TGeodeticRefFrame* TRefSystemFactory::getGeoRefFrame(const ERefFrame refFrameId)
{
	if( refFrameId == kCGRFSphere )
		return fCGRFSphere;
	
	if( refFrameId == kCGRF )
		return fCGRF;

	if (refFrameId == kCGRF_new)
		return fCGRF2;

	std::cerr << "Error : Id. not in RefFrameList" << std::endl;
	throw TNotInGraphException("TNotInGraphException");

	//cerr << "Error : Id. not in RefFrameList";
	///
	//TODO@*@
	///
	//exit(EXIT_FAILURE);
}

TTerrestrialReferenceFrame* TRefSystemFactory::getTerrRefFrame(const ERefFrame refFrameId)
{
	if (refFrameId == kITRFin)
		return fITRFin;
	else if (refFrameId == kITRFout)
		return fITRFout;
	else if (refFrameId == kETRFin)
		return fETRFin;
	else if (refFrameId == kETRFout)
		return fETRFout;

	std::cerr << "Error : Id. not in RefFrameList" << std::endl;
	throw TNotInGraphException("TNotInGraphException");

}

TARefFrameTransformation* TRefSystemFactory::getTransformation(const ERefFrameTransform id)
{//return a pointer to the ref frame transformation asked for
	return getElementFromList(fTransformList, id, "TransformationList");
}


bool TRefSystemFactory::isInRFFactory( const TAReferenceFrame* rf ) 
{//test if the reference frame is in the graph or not

	std::vector<TAReferenceFrame*>::iterator iter = fRefFrameList.begin();
	std::vector<TAReferenceFrame*>::iterator iterEnd = fRefFrameList.end();

	while (iter != iterEnd)
	{
		if((*iter) == rf)
			return true;

		iter++;
	}

	return false;
}

void TRefSystemFactory::updateTerrestrialRefFrame(TReal epoch, std::string solution, ERefFrame frame)
{// Update terrestrial reference frame with current epoch and solution

	getTerrRefFrame(frame)->setSolution(solution);
	getTerrRefFrame(frame)->setEpoch(epoch);

}


TAReferenceFrame*	TRefSystemFactory::getNewLocalRefFrame()
{//return a pointer to a new Local ref Frame and put it in a list in order to be deleted
	T3DLocalRefFrame* pLocalRF = new T3DLocalRefFrame("Local Reference Frame");
	fLocalRefFrameList.push_back(pLocalRF);
	return pLocalRF;
}

TAReferenceFrame* TRefSystemFactory::getNewLocalRefFrame(const TLocalSystemOrigin & LSO, EGeoid geoid,  ERefFrame frame) {
	TSpatialPosition lsoCG = LSO.origin();
	TAReferenceFrame *pRF(0);
	TGeodeticRefFrame *pXGRF(fCGRF);
	TFreeVector falseOrigin(0,0,0, TCoordSysFactory::k3DCartesian);
	TAngle gis = LSO.gisement();
	TAngle slope = LSO.slope();

	// transform the origin to the correct CGRF system
	if (frame == kLASphere || frame == kMLASphere || 
		frame == kLGSphere || frame == kMLGSphere)
		lsoCG.transform(getRefFrame(kCGRFSphere));

	else if (frame == kLA1985Machine || frame == kLA2000Machine ||
			frame == kMLA1985Machine || frame == kMLA2000Machine ||
			frame == kLGGRS80 || frame == kMLGGRS80 ||
			frame == kLA2000Topo || frame == kMLA2000Topo ||
			frame == kLA2000H0 || frame == kMLA2000H0 ||
			frame == kLA1985H0 || frame == kMLA1985H0)
		lsoCG.transform(getRefFrame(kCGRF));
		
	//lsoCG.setStatus(TVNumericValue::kKnown);

	switch (frame) {
		case kLASphere:
		case kLA1985Machine:
		case kLA1985H0:
		case kLA2000Machine:
		case kLA2000Topo:
		case kLA2000H0:
			pRF = new TModifiedLocalAstronomicalRF("la", geoid, lsoCG);
			break;
		case kMLASphere:
		case kMLA1985Machine:
		case kMLA1985H0:
		case kMLA2000Machine:
		case kMLA2000Topo:
		case kMLA2000H0:
			pRF = new TModifiedLocalAstronomicalRF("mla", geoid, lsoCG, falseOrigin, gis, slope);
			break;
		case kLGSphere:
			pXGRF = fCGRFSphere;
		case kLGGRS80:
			pRF = new TModifiedLocalGeodeticRF("lg", lsoCG, pXGRF);
			break;
		case kMLGSphere:
			pXGRF = fCGRFSphere;
		case kMLGGRS80:
			pRF = new TModifiedLocalGeodeticRF("mlg", lsoCG, falseOrigin, gis, slope, pXGRF);
			break;
		default:
			throw std::invalid_argument("Desired reference frame is non-local.");
	}
	
	fLocalRefFrameList.push_back(pRF);
	return pRF;
}

TAReferenceFrame *TRefSystemFactory::updatePathTotransformationMatrix(const std::string &pathToTransformationMatrix, ERefFrame frame)
{
	if (frame != TRefSystemFactory::kLocalRFin && frame != TRefSystemFactory::kLocalRFout)
	{
		throw std::invalid_argument("This method is only valid for CAD reference frame!");
	}
	else
	{
		auto *cad = dynamic_cast<TLocalRFWithTransformationMatrix *>(getRefFrame(frame));
		cad->setPathToTransformationMatrix(pathToTransformationMatrix);
	}

	return TRefSystemFactory::getRefSystemFactory()->getRefFrame(frame);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////////////////////////////////




