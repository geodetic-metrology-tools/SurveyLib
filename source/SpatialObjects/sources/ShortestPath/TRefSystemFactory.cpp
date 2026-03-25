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
#include "TNotInGraphException.h"
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
	
	///////////////////////////////////////////////////////////////////
	// Definition of the ellipsoid list

	initEllipsoidList();

	// Definition of the reference frame list
	std::string cgrf("CGRF"), cgrfs("CGRFSphere"), itrf97("ITRF97"), wgs("WGS84 (G2139)");
	std::string ccs("CCS"), etrf93("ETRF93");
	std::string cgrf2("new_CGRF");
	std::string itrfIn("ITRFin");
	std::string itrfOut("ITRFout");
	std::string etrfIn("ETRFin");
	std::string etrfOut("ETRFout");
	
		//new CGRF (coordinate of P0 have been changed)
	TGeodeticRefFrame* pCGRF2 = new TGeodeticRefFrame(cgrf2, getEllipsoid(TRefSystemFactory::kGRS80));
	pCGRF2->setRefFrameId(kCGRF_new);
	fRefFrameList.push_back(pCGRF2);
	fCGRF2 = pCGRF2;

		// CGRF
	TGeodeticRefFrame* pCGRF = new TGeodeticRefFrame(cgrf, getEllipsoid(TRefSystemFactory::kGRS80));
	pCGRF->setRefFrameId(kCGRF);
	fRefFrameList.push_back(pCGRF);
	fCGRF = pCGRF;
	
		// CGRF sphere
	TGeodeticRefFrame* pCGRFs = new TGeodeticRefFrame(cgrfs, getEllipsoid(TRefSystemFactory::kSphere));
	pCGRFs->setRefFrameId(kCGRFSphere);
	fRefFrameList.push_back(pCGRFs);
	fCGRFSphere = pCGRFs;

		// CGRF Transverse Mercator Projection
	TAReferenceFrame *pCGRFtm_eh = new TTransverseMercatorProjection("CGRFtm_eh");
	pCGRFtm_eh->setRefFrameId(kCGRFMercator_eh);
	fRefFrameList.push_back(pCGRFtm_eh);

		// ITRF97 at epoch 1998.5.Link between global and local frames
	TReal epoch = 1998.5;
	std::string solution = "ITRF 97";
	TTerrestrialReferenceFrame* pITRF97 = new TTerrestrialReferenceFrame(itrf97, getEllipsoid(TRefSystemFactory::kGRS80), epoch, solution);
	pITRF97->setRefFrameId(kITRF97);
	fRefFrameList.push_back(pITRF97);

	//Generic ITRF solution at specified epoch (input)
	TReal initEpochITRF = NO_VALf;
	std::string initSolution = "noSolution";
	TTerrestrialReferenceFrame* pITRFin = new TTerrestrialReferenceFrame(itrfIn, getEllipsoid(TRefSystemFactory::kGRS80), initEpochITRF, initSolution);
	pITRFin->setRefFrameId(kITRFin);
	fRefFrameList.push_back(pITRFin);
	fITRFin = pITRFin;

	//Generic ITRF solution at specified epoch (output)
	TTerrestrialReferenceFrame* pITRFout = new TTerrestrialReferenceFrame(itrfOut, getEllipsoid(TRefSystemFactory::kGRS80), initEpochITRF, initSolution);
	pITRFout->setRefFrameId(kITRFout);
	fRefFrameList.push_back(pITRFout);
	fITRFout = pITRFout;

	//Generic ETRF solution at specified epoch (input)
	TReal initEpochETRF = NO_VALf;
	TTerrestrialReferenceFrame* pETRFin = new TTerrestrialReferenceFrame(etrfIn, getEllipsoid(TRefSystemFactory::kGRS80), initEpochETRF, initSolution);
	pETRFin->setRefFrameId(kETRFin);
	fRefFrameList.push_back(pETRFin);
	fETRFin = pETRFin;

	//Generic ETRF solution at specified epoch (output)
	TTerrestrialReferenceFrame* pETRFout = new TTerrestrialReferenceFrame(etrfOut, getEllipsoid(TRefSystemFactory::kGRS80), initEpochETRF, initSolution);
	pETRFout->setRefFrameId(kETRFout);
	fRefFrameList.push_back(pETRFout);
	fETRFout = pETRFout;

		// FrenchRGF93 zone 5 (CC46)
    TAReferenceFrame* pFrenchRGF93_CC46_eh = new TRGF93CC46Projection("FrenchRGF93_CC46_eh");
    pFrenchRGF93_CC46_eh->setRefFrameId(kFrenchRGF93_CC46_eh);
    fRefFrameList.push_back(pFrenchRGF93_CC46_eh);

	TAReferenceFrame *pFrenchRGF93_CC46_raf = new TRGF93CC46Projection("FrenchRGF93_CC46_ign69");
	pFrenchRGF93_CC46_raf->setRefFrameId(kFrenchRGF93_CC46_ign69);
	fRefFrameList.push_back(pFrenchRGF93_CC46_raf);	

	// Lambert93
	TAReferenceFrame* pLambert93_eh = new TLambert93Projection("Lambert93_eh");
	pLambert93_eh->setRefFrameId(kLambert93_eh);
    fRefFrameList.push_back(pLambert93_eh);

	TAReferenceFrame *pLambert93_raf = new TLambert93Projection("Lambert93_ign69");
	pLambert93_raf->setRefFrameId(kLambert93_ign69);
	fRefFrameList.push_back(pLambert93_raf);

    // ETRF93
	epoch = 1993;
	solution = "ETRF 93";
	TTerrestrialReferenceFrame* pETRF93 = new TTerrestrialReferenceFrame(etrf93, getEllipsoid(TRefSystemFactory::kGRS80), epoch, solution);
	pETRF93->setRefFrameId(kETRF93);
	fRefFrameList.push_back(pETRF93);

	// RGF93
	epoch = 2019;
	solution = "ETRF 2000";
	TTerrestrialReferenceFrame* pRGF93 = new TTerrestrialReferenceFrame("RGF93", getEllipsoid(TRefSystemFactory::kGRS80), epoch, solution);
	pRGF93->setRefFrameId(kRGF93);
	fRefFrameList.push_back(pRGF93);

	// CHTRF95
	epoch = 1993;
	solution = "ETRF 93";
	TTerrestrialReferenceFrame* pCHTRF95 = new TTerrestrialReferenceFrame("CHTRF95", getEllipsoid(TRefSystemFactory::kGRS80), epoch, solution);
	pCHTRF95->setRefFrameId(kCHTRF95);
	fRefFrameList.push_back(pCHTRF95);

        // CH1903plus
	TGeodeticRefFrame* pCH1903plus = new TGeodeticRefFrame("CH1903plus", getEllipsoid(TRefSystemFactory::kBessel1841));
	pCH1903plus->setRefFrameId(kCH1903plus);
	fRefFrameList.push_back(pCH1903plus);
#ifdef USE_SWISSTOPO
        // Swiss LV95
    TAReferenceFrame* pLV95_eh = new TLV95Projection("LV95_eh");
    pLV95_eh->setRefFrameId(kSwissLV95_eh);
    fRefFrameList.push_back(pLV95_eh);

	TAReferenceFrame *pLV95_lhn95 = new TLV95Projection("LV95_lhn95");
	pLV95_lhn95->setRefFrameId(kSwissLV95_lhn95);
	fRefFrameList.push_back(pLV95_lhn95);

	TAReferenceFrame *pLV95_ln02 = new TLV95Projection("LV95_ln02");
	pLV95_ln02->setRefFrameId(kSwissLV95_ln02);
	fRefFrameList.push_back(pLV95_ln02);

        // Swiss LV03
    TAReferenceFrame* pLV03_eh = new TLV03Projection("LV03_eh");
    pLV03_eh->setRefFrameId(kSwissLV03_eh);
    fRefFrameList.push_back(pLV03_eh);

	TAReferenceFrame *pLV03_ln02 = new TLV03Projection("LV03_ln02");
	pLV03_ln02->setRefFrameId(kSwissLV03_ln02);
	fRefFrameList.push_back(pLV03_ln02);

	TAReferenceFrame *pLV03_lhn95 = new TLV03Projection("LV03_lhn95");
	pLV03_lhn95->setRefFrameId(kSwissLV03_lhn95);
	fRefFrameList.push_back(pLV03_lhn95);

#endif
		// WGS84 (G2139)
	epoch = 2016;
	solution = "ITRF 2014";
	TTerrestrialReferenceFrame *pWGS84_G2139 = new TTerrestrialReferenceFrame(wgs, getEllipsoid(TRefSystemFactory::kWGSEll), epoch, solution);
	pWGS84_G2139->setRefFrameId(kWGS84_G2139);
	fRefFrameList.push_back(pWGS84_G2139);

		// Local Geodesique at CERN: origin = principal point of the system = P0 
	TSpatialPosition origin(pCGRF);
	TAngle phi, lambda;
	TLength H;
	phi.setGonsValue(LITERAL(51.3692));
	lambda.setGonsValue(LITERAL(6.72124));
	H.setMetresValue(LITERAL(433.65921));
	TPositionVector pos(TCoordSysFactory::kGeodetic);
	pos.setPhiEllipsoid(phi);
	pos.setLambdaEllipsoid(lambda);
	pos.setH(H);

	origin.setCoordinates( pos );
	origin.setObjectStatus( TSpatialStatus::kCala );

	TModifiedLocalGeodeticRF* pLGp0 = new TModifiedLocalGeodeticRF( "LG P0", origin, pCGRF);
	pLGp0->setRefFrameId(kLGp0);
	fRefFrameList.push_back(pLGp0);

		// Local Astronomic at CERN: origin = principal point of the system = P0
	TAngle etaP0(0), xsiP0(0), dAlphaP0(0);
	TGraphLocalAstronomicalRF* pLAp0 = new TGraphLocalAstronomicalRF( "LA P0", etaP0, xsiP0, dAlphaP0, pLGp0 );
	pLAp0->setRefFrameId(kLAp0);
	fRefFrameList.push_back(pLAp0);
	
		// CCS : CERN Modified Local Astronomical system : principal point = P0 defined as false origin
	TFreeVector falseOrigin(2000, LITERAL(2097.79265), LITERAL(2433.66000), TCoordSysFactory::k3DCartesian);
	TAngle omega(0), phi2(0), kappa;
	kappa.setGonsValue(LITERAL(37.77864));

	TAModifiedLocalAstronomicalRF* pCCS = new TGraphMLARF(ccs, falseOrigin,
		pLAp0, omega, phi2, kappa);
	pCCS->setRefFrameId(kCCS);
	fRefFrameList.push_back(pCCS);

	//new P0 coordinates
	TSpatialPosition origin_new(pCGRF2);
	TAngle phi_new, lambda_new;
	phi_new.setGonsValue(LITERAL(51.36734));
	lambda_new.setGonsValue(LITERAL(6.722515));

	TPositionVector pos_new(TCoordSysFactory::kGeodetic);
	pos_new.setPhiEllipsoid(phi_new);
	pos_new.setLambdaEllipsoid(lambda_new);
	pos_new.setH(H);

	origin_new.setCoordinates(pos_new);
	origin_new.setObjectStatus(TSpatialStatus::kCala);

	// Local Geodetic at P0_new
	TModifiedLocalGeodeticRF* pLGp0_new = new TModifiedLocalGeodeticRF("LG P0_new", origin_new, pCGRF2);
	pLGp0_new->setRefFrameId(kLGp0_new);
	fRefFrameList.push_back(pLGp0_new);

	// Local Astronomic at P0_new
	TGraphLocalAstronomicalRF* pLAp0_new = new TGraphLocalAstronomicalRF("LA P0_new", etaP0, xsiP0, dAlphaP0, pLGp0_new);
	pLAp0_new->setRefFrameId(kLAp0_new);
	fRefFrameList.push_back(pLAp0_new);

	// CCS at P0_new
	TAngle kappa_new(LITERAL(37.779033), TAngle::EUnits::kGons);
	TAModifiedLocalAstronomicalRF* pCCS_new = new TGraphMLARF("CCS_new", falseOrigin,
		pLAp0_new, omega, phi2, kappa_new);
	pCCS_new->setRefFrameId(kCCS_new);
	fRefFrameList.push_back(pCCS_new);

	

	///////////////////////////////////////////////////////////////////////////////	
	// Definition of the geoid list
	initGeoidList();
	
	/////////////////////////////////////////////////////////////////////
	// Definition of the CERN projection list (included in ref frame list)

	// CERN XYHs projection: XY system = CCS, Hs = height above SPS sphere (projection of the xy point on the sphere)
	TXYHeProjection* pCernXYHs = new TXYHeProjection( "CERN_XYHs", getEllipsoid(TRefSystemFactory::kSphere), pCCS);
	pCernXYHs->setRefFrameId(kCERNXYHsSphereSPS);
	fRefFrameList.push_back(pCernXYHs);

	// CERN XYHe projection: XY system = CCS, He = height above ellipsoid (projection of the xy point on the ellipsoid)
	TXYHeProjection* pCernXYHe = new TXYHeProjection( "CERN_XYHe", getEllipsoid(TRefSystemFactory::kGRS80), pCCS);
	pCernXYHe->setRefFrameId(kCernXYHe);
	fRefFrameList.push_back(pCernXYHe);

	// CERN X0Y0He projection: X0Y0 = projection of XY on the ellipsoid's level (h=0)
	TX0Y0HeProjection* pCernX0Y0He = new TX0Y0HeProjection( "CERN_X0Y0He", pCernXYHe);
	pCernX0Y0He->setRefFrameId(kCernX0Y0He);
	fRefFrameList.push_back(pCernX0Y0He);

	// CERN XYHg projection CG2000: XY system = CCS, Hg = height above geoid CG2000 (projection of the xy point on the geoid)
	TXYHgProjection *pCernXYHg00 = new TXYHgProjection("CERN_XYHg2000", getGeoid(kCG2000), pCernXYHe);
	pCernXYHg00->setRefFrameId(kCernXYHg00);
	fRefFrameList.push_back(pCernXYHg00);

	// CERN XYHg projection CG2000Topo :XY system = CCS, Hg = height above geoid CG2000Topo (projection of the xy point on the geoid)
	TXYHgProjection *pCernXYHg00Topo = new TXYHgProjection("CERN_XYHg2000Topo", getGeoid(kCG2000topo), pCernXYHe);
	pCernXYHg00Topo->setRefFrameId(kCernXYHg00Topo);
	fRefFrameList.push_back(pCernXYHg00Topo);
	
	// CERN XYHg projection CG2000Machine: XY system = CCS, Hg = height above geoid CG2000Machine (projection of the xy point on the geoid)
	TXYHgProjection *pCernXYHg00Machine = new TXYHgProjection("CERN_XYHg2000Machine", getGeoid(kCG2000Machine), pCernXYHe);
	pCernXYHg00Machine->setRefFrameId(kCernXYHg00Machine);
	fRefFrameList.push_back(pCernXYHg00Machine);

	// CERN XYHg projection CG1985: XY system = CCS, Hg = height above geoid CG1985 (projection of the xy point on the geoid)
	TXYHgProjection *pCernXYHg85 = new TXYHgProjection("CERN_XYHg1985", getGeoid(kCG1985), pCernXYHe);
	pCernXYHg85->setRefFrameId(kCernXYHg85);
	fRefFrameList.push_back(pCernXYHg85);

	// CERN XYHg projection CG1985Machine: XY system = CCS, Hg = height above geoid CG1985Machine (projection of the xy point on the geoid)
	TXYHgProjection *pCernXYHg85Machine = new TXYHgProjection("CERN_XYHg1985Machine", getGeoid(kCG1985Machine), pCernXYHe);
	pCernXYHg85Machine->setRefFrameId(kCernXYHg85Machine);
	fRefFrameList.push_back(pCernXYHg85Machine);

	// CAD Systems
	TLocalRFWithTransformationMatrix *pLocalRFin = new TLocalRFWithTransformationMatrix("LocalRF_Input", "");
	pLocalRFin->setRefFrameId(kLocalRFin);
	fRefFrameList.push_back(pLocalRFin);
	TLocalRFWithTransformationMatrix *pLocalRFout = new TLocalRFWithTransformationMatrix("LocalRF_Output", "");
	pLocalRFout->setRefFrameId(kLocalRFout);
	fRefFrameList.push_back(pLocalRFout);

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Definition of the CERN's ref. frames transformations

		// Transformation between CERN projection XYHs and CCS
	{
		TXYHs2MLATransformation* pXYHs2CCS = new TXYHs2MLATransformation(pCernXYHs);
		pXYHs2CCS->setTransformId(kXYHsSphereSPS2CCS);
		fTransformList.push_back(pXYHs2CCS);
		//Inverse
		TARefFrameTransformation* pCCS2XYHs = pXYHs2CCS->inverse(); //utilise new
		pCCS2XYHs->setTransformId(kCCS2XYHsSphereSPS);
		fTransformList.push_back(pCCS2XYHs);
	}

	// Transformation between CCS and CGRF
	/*Il est equivalent de mettre CG2000 ou CG1985 car les parametres du geoide au niveau de P0,
	servant a definir la transformation sont equivalent*/
	{
		TMLA2GCTransformation *pCCS2CGRF = new TMLA2GCTransformation(pCCS, getGeoid(kCG1985Machine));
		pCCS2CGRF->setTransformId(kCCS2CGRF);
		fTransformList.push_back(pCCS2CGRF);
		//Inverse
		TARefFrameTransformation* pCGRF2CCS = pCCS2CGRF->inverse(); //utilise new
		pCGRF2CCS->setTransformId(kCGRF2CCS);
		fTransformList.push_back(pCGRF2CCS);
	}

	//Conversion between CGRF (ellipsoid) and CGRF (Transverse Mercator projection)
	{
		TGeodetic2Mercator *pCGRF2CGRFMercator = new TGeodetic2Mercator(true);
		pCGRF2CGRFMercator->setTransformId(kCGRF2CGRFMercator);
		fTransformList.push_back(pCGRF2CGRFMercator);
		// Inverse
		TARefFrameTransformation *pCGRFMercator2CGRF = pCGRF2CGRFMercator->inverse(); // utilise new
		pCGRFMercator2CGRF->setTransformId(kCGRFMercator2CGRF);
		fTransformList.push_back(pCGRFMercator2CGRF);
	}

	// Transformation between CCS and CGRFSphere
	//rotation pour diriger les axes du CGRFs parallele a ceux du CGRF
	{
		TAngle rx, ry, rz;
		rx.setGonsValue(-LITERAL(42.726243230216));
		ry.setGonsValue(-LITERAL(25.285434244947));
		rz.setGonsValue(-LITERAL(77.864346765085));
		TRotation rs(TRotationMatrix::kRzyx, rx.getRadiansValue(), ry.getRadiansValue(), rz.getRadiansValue());
		//translation pour situer le centre de la sphere
		TLength txs(LITERAL(4381882.331989)), tys(LITERAL(461505.530464)), tzs(LITERAL(4598944.364158));
		TTranslation transls(txs, tys, tzs);
		//facteur d echelle
		TScaleFactor ks(LITERAL(1.0));
		THelmertRefFrameTransform* pCCS2CGRFs = new THelmertRefFrameTransform(pCCS, pCGRFs, ks, rs, transls);
		pCCS2CGRFs->setTransformId(kCCS2CGRFSphere);
		fTransformList.push_back(pCCS2CGRFs);
		//Inverse
		TARefFrameTransformation* pCGRFs2CCS = pCCS2CGRFs->inverse();//utilise new
		pCGRFs2CCS->setTransformId(kCGRFSphere2CCS);
		fTransformList.push_back(pCGRFs2CCS);
	}

	// Transformation between LAp0 and LGp0
	{
		TLA2LGTransformation* pLAp02LGp0 = new TLA2LGTransformation(pLAp0);
		pLAp02LGp0->setTransformId(kLAp02LGp0);
		fTransformList.push_back(pLAp02LGp0);
		//Inverse
		TARefFrameTransformation* pLGp02LAp0 = pLAp02LGp0->inverse(); //utilise new
		pLGp02LAp0->setTransformId(kLGp02LAp0);
		fTransformList.push_back(pLGp02LAp0);
	}

	//Transformation between LGp0 and CGRF
	{
		TLG2GCTransformation* pLGp02CGRF = new TLG2GCTransformation(pLGp0);
		pLGp02CGRF->setTransformId(kLGp02CGRF);
		fTransformList.push_back(pLGp02CGRF);
		//Inverse
		TARefFrameTransformation* pCGRF2LGp0 = pLGp02CGRF->inverse(); //utilise new
		pCGRF2LGp0->setTransformId(kCGRF2LGp0);
		fTransformList.push_back(pCGRF2LGp0);
	}

	// Helmert Transformation between LAp0 and CCS
	{
		TRotation r(TRotationMatrix::kRzyx, 0, 0, -(kappa.getRadiansValue()));
		TTranslation transl(falseOrigin.getX(), falseOrigin.getY(), (falseOrigin.getZ()));
		TScaleFactor enl(LITERAL(1.0));
		THelmertRefFrameTransform* pLAp02CCS = new THelmertRefFrameTransform(pLAp0, pCCS, enl, r, transl);
		pLAp02CCS->setTransformId(kLAp02CCS);
		fTransformList.push_back(pLAp02CCS);
		//Inverse
		TARefFrameTransformation* pCCS2LAp0 = pLAp02CCS->inverse(); //utilise new
		pCCS2LAp0->setTransformId(kCCS2LAp0);
		fTransformList.push_back(pCCS2LAp0);
	}
	
		// Helmert Transformation between ITRF97 (ep1998.5) and CGRF
	{
		TAngle om3, p3, k3;
		om3.setGonsValue(LITERAL(399.999533213524));
		p3.setGonsValue(LITERAL(0.001825157943));
		k3.setGonsValue(LITERAL(0.000991054274));
		TRotation r3(TRotationMatrix::kRzyx, om3.getRadiansValue(), p3.getRadiansValue(), k3.getRadiansValue());
		TLength Tx3(LITERAL(76.3768280)), Ty3(LITERAL(131.9389844)), Tz3(-LITERAL(156.1229775));
		TTranslation transl3(Tx3, Ty3, Tz3);
		TScaleFactor enl3(LITERAL(1.000000000000000));
		THelmertRefFrameTransform* pITRF972CGRF = new THelmertRefFrameTransform(pITRF97, pCGRF, enl3, r3, transl3);
		pITRF972CGRF->setTransformId(kITRF972CGRF);
		fTransformList.push_back(pITRF972CGRF);
		//Inverse
		TARefFrameTransformation* pCGRF2ITRF97 = pITRF972CGRF->inverse(); //utilise new
		pCGRF2ITRF97->setTransformId(kCGRF2ITRF97);
		fTransformList.push_back(pCGRF2ITRF97);
	}

		////////////////////////////////////////////////////////////////
		// Transformation ITRF-ETRF, ETRF-ITRF
		////////////////////////////////////////////////////////////////
	{
		auto itrf2020_toPastITRF = makeMatrix(TrfTransformationCoefficients::coeffITRF2020_toPastITRF);
		auto itrfyy_toETRFyy = makeMatrix(TrfTransformationCoefficients::coeffITRFyy_toETRFyy);


		// Transformtion between ITRF and ETRF
		TTrf2TrfTransformation *pITRFin2ETRFout = new TTrf2TrfTransformation(pITRFin, pETRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRFin2ETRFout->setTransformId(kITRFin2ETRFout);
		fTransformList.push_back(pITRFin2ETRFout);
		// Inverse
		TTrf2TrfTransformation *pETRFin2ITRFout = new TTrf2TrfTransformation(pETRFin, pITRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pETRFin2ITRFout->setTransformId(kETRFin2ITRFout);
		fTransformList.push_back(pETRFin2ITRFout);

		// Transformation between any ITRF an ITRF97 (ep 1998.5)
		TTrf2TrfTransformation *pITRFin2ITRF97 = new TTrf2TrfTransformation(pITRFin, pITRF97, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRFin2ITRF97->setTransformId(kITRFin2ITRF97);
		fTransformList.push_back(pITRFin2ITRF97);
		// Inverse
		TTrf2TrfTransformation *pITRF972ITRFout = new TTrf2TrfTransformation(pITRF97, pITRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRF972ITRFout->setTransformId(kITRF972ITRFout);
		fTransformList.push_back(pITRF972ITRFout);

		// Transformation between any ETRF an ITRF97 (ep 1998.5)
		TTrf2TrfTransformation *pITRF972ETRFout = new TTrf2TrfTransformation(pITRF97, pETRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRF972ETRFout->setTransformId(kITRF972ETRFout);
		fTransformList.push_back(pITRF972ETRFout);
		// Inverse
		TTrf2TrfTransformation *pETRFin2ITRF97 = new TTrf2TrfTransformation(pETRFin, pITRF97, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pETRFin2ITRF97->setTransformId(kETRFin2ITRF97);
		fTransformList.push_back(pETRFin2ITRF97);

		// Transformation between 2 ITRF
		TTrf2TrfTransformation *pITRFin2ITRFout = new TTrf2TrfTransformation(pITRFin, pITRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRFin2ITRFout->setTransformId(kITRFin2ITRFout);
		fTransformList.push_back(pITRFin2ITRFout);

		// Transformation between 2 ETRF
		TTrf2TrfTransformation *pETRFin2ETRFout = new TTrf2TrfTransformation(pETRFin, pETRFout, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pETRFin2ETRFout->setTransformId(kETRFin2ETRFout);
		fTransformList.push_back(pETRFin2ETRFout);
		
		// Transformation between ITRF97 (ep1998.5) and ETRF93 (ep 1993.0)
		TTrf2TrfTransformation *pITRF972ETRF93 = new TTrf2TrfTransformation(pITRF97, pETRF93, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRF972ETRF93->setTransformId(kITRF972ETRF93);
		fTransformList.push_back(pITRF972ETRF93);
		//Inverse
		TTrf2TrfTransformation *pETRF932ITRF97 = new TTrf2TrfTransformation(pETRF93, pITRF97, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pETRF932ITRF97->setTransformId(kETRF932ITRF97);
		fTransformList.push_back(pETRF932ITRF97);

		// Transformation between ITRF97 (ep1998.5) and RGF93
		TTrf2TrfTransformation *pITRF972RGF93 = new TTrf2TrfTransformation(pITRF97, pRGF93, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRF972RGF93->setTransformId(kITRF972RGF93);
		fTransformList.push_back(pITRF972RGF93);
		// Inverse
		TTrf2TrfTransformation *pRGF932ITRF97 = new TTrf2TrfTransformation(pRGF93, pITRF97, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pRGF932ITRF97->setTransformId(kRGF932ITRF97);
		fTransformList.push_back(pRGF932ITRF97);

		// Transformation between ITRF97 (ep1998.5) and CHTRF95
		TTrf2TrfTransformation *pITRF972CHTRF95 = new TTrf2TrfTransformation(pITRF97, pCHTRF95, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRF972CHTRF95->setTransformId(kITRF972CHTRF95);
		fTransformList.push_back(pITRF972CHTRF95);
		// Inverse
		TTrf2TrfTransformation *pCHTRF952ITRF97 = new TTrf2TrfTransformation(pCHTRF95, pITRF97, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pCHTRF952ITRF97->setTransformId(kCHTRF952ITRF97);
		fTransformList.push_back(pCHTRF952ITRF97);

		// Transformation between ITRF97 (ep1998.5) and WGS84 (G2139)
		TTrf2TrfTransformation *pITRF972WGS84 = new TTrf2TrfTransformation(pITRF97, pWGS84_G2139, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pITRF972WGS84->setTransformId(kITRF972WGS84);
		fTransformList.push_back(pITRF972WGS84);
		// Inverse
		TTrf2TrfTransformation *pWGS842ITRF97 = new TTrf2TrfTransformation(pWGS84_G2139, pITRF97, itrf2020_toPastITRF.get(), itrfyy_toETRFyy.get());
		pWGS842ITRF97->setTransformId(kWGS842ITRF97);
		fTransformList.push_back(pWGS842ITRF97);

	}
    
        ////////////////////////////////////////////////////////////////
		// Helmert Transformation between ETRF93 (ep1993) and CH1903plus
        ////////////////////////////////////////////////////////////////
	{
		// There is no rotation:
		TRotation r3(TRotationMatrix::kRzyx, 0, 0, 0);
		// Total translation resulting from epoch changes and Reference Frame changes:
		TLength Tx3(LITERAL(-674.374)), Ty3(LITERAL(-15.056)), Tz3(LITERAL(-405.346));
		TTranslation transl3(Tx3, Ty3, Tz3);
		// There is no scaling:
		TScaleFactor enl3(LITERAL(1.000000000000000));
		THelmertRefFrameTransform* pETRF932CH1903plus = new THelmertRefFrameTransform(pETRF93, pCH1903plus, enl3, r3, transl3);
		pETRF932CH1903plus->setTransformId(kETRF932CH1903plus);
		fTransformList.push_back(pETRF932CH1903plus);
		//Inverse
		TARefFrameTransformation* pCH1903plus2ETRF93 = pETRF932CH1903plus->inverse(); //utilise new
		pCH1903plus2ETRF93->setTransformId(kCH1903plus2ETRF93);
		fTransformList.push_back(pCH1903plus2ETRF93);
	}
#ifdef USE_SWISSTOPO
    {
        ////////////////////////////////////////////////////////////////
		// Transformation between CH1903plus and LV95 (ellipsoidal height)
        ////////////////////////////////////////////////////////////////
        TLV95Transformation * pTrans = new TLV95Transformation(true, "eh");
        pTrans->setTransformId(kCH1903plus2SwissLV95eh);
		fTransformList.push_back(pTrans);
		//Inverse
		TARefFrameTransformation* pInverse = pTrans->inverse();
        pInverse->setTransformId(kSwissLV95eh2CH1903plus);
        fTransformList.push_back(pInverse);
	}
	{
		////////////////////////////////////////////////////////////////
		// Transformation between CH1903plus and LV95 (orthometric height)
		////////////////////////////////////////////////////////////////
		TLV95Transformation *pTrans = new TLV95Transformation(true, "lhn95");
		pTrans->setTransformId(kCH1903plus2SwissLV95lhn95);
		fTransformList.push_back(pTrans);
		// Inverse
		TARefFrameTransformation *pInverse = pTrans->inverse();
		pInverse->setTransformId(kSwissLV95lhn952CH1903plus);
		fTransformList.push_back(pInverse);
	}
	{
		////////////////////////////////////////////////////////////////
		// Transformation between CH1903plus and LV95 (leveled height)
		////////////////////////////////////////////////////////////////
		TLV95Transformation *pTrans = new TLV95Transformation(true, "ln02");
		pTrans->setTransformId(kCH1903plus2SwissLV95ln02);
		fTransformList.push_back(pTrans);
		// Inverse
		TARefFrameTransformation *pInverse = pTrans->inverse();
		pInverse->setTransformId(kSwissLV95ln022CH1903plus);
		fTransformList.push_back(pInverse);
	}
    {
        ////////////////////////////////////////////////////////////////
		// Transformation between LV95 and LV03 (ellipsoidal height)
        ////////////////////////////////////////////////////////////////
        TLV03Transformation * pTrans = new TLV03Transformation(true, "eh");
        pTrans->setTransformId(kSwissLV95eh2SwissLV03eh);
		fTransformList.push_back(pTrans);
		//Inverse
		TARefFrameTransformation* pInverse = pTrans->inverse();
        pInverse->setTransformId(kSwissLV03eh2SwissLV95eh);
        fTransformList.push_back(pInverse);
	}

	{
		////////////////////////////////////////////////////////////////
		// Transformation between LV95 (ellipsoidal height) and LV03 (leveled height)
		////////////////////////////////////////////////////////////////
		TLV03Transformation *pTrans = new TLV03Transformation(true, "ln02");
		pTrans->setTransformId(kSwissLV95eh2SwissLV03ln02);
		fTransformList.push_back(pTrans);
		// Inverse
		TARefFrameTransformation *pInverse = pTrans->inverse();
		pInverse->setTransformId(kSwissLV03ln022SwissLV95eh);
		fTransformList.push_back(pInverse);
	}

	{
		////////////////////////////////////////////////////////////////
		// Transformation between LV95 (ellipsoidal height) and LV03 (orthometric height)
		////////////////////////////////////////////////////////////////
		TLV03Transformation *pTrans = new TLV03Transformation(true, "lhn95");
		pTrans->setTransformId(kSwissLV95eh2SwissLV03lhn95);
		fTransformList.push_back(pTrans);
		// Inverse
		TARefFrameTransformation *pInverse = pTrans->inverse();
		pInverse->setTransformId(kSwissLV03lhn952SwissLV95eh);
		fTransformList.push_back(pInverse);
	}
#endif
    
        ////////////////////////////////////////////////////////////////
		// Transformation between projected CC46 and RGF93
        ////////////////////////////////////////////////////////////////
	{
		//Ellipsoidal height
		TRGF93ZoneTransformation * pRGF932CC46eh = new TRGF93ZoneTransformation(true, true);
		pRGF932CC46eh->setTransformId(kRGF932CC46eh);
		fTransformList.push_back(pRGF932CC46eh);
		//Inverse
		TARefFrameTransformation *pCC46eh2RGF93 = pRGF932CC46eh->inverse();
		pCC46eh2RGF93->setTransformId(kCC46eh2RGF93);
		fTransformList.push_back(pCC46eh2RGF93);

		//Altitude NGF-IGN69
		TRGF93ZoneTransformation *pRGF932CC46raf = new TRGF93ZoneTransformation(true, false);
		pRGF932CC46raf->setTransformId(kRGF932CC46ign69);
		fTransformList.push_back(pRGF932CC46raf);
		// Inverse
		TARefFrameTransformation *pCC46raf2RGF93 = pRGF932CC46raf->inverse();
		pCC46raf2RGF93->setTransformId(kCC46raf2RGF93);
		fTransformList.push_back(pCC46raf2RGF93);
	}

	
        ////////////////////////////////////////////////////////////////
		// Transformation between RGF93v2b and Lambert93
        ////////////////////////////////////////////////////////////////
	{
		//Ellipsoidal height
		TLambert93Transformation *pRGF932Lambert93eh = new TLambert93Transformation(true, true);
		pRGF932Lambert93eh->setTransformId(kRGF932Lambert93eh);
		fTransformList.push_back(pRGF932Lambert93eh);
		//Inverse
		TARefFrameTransformation *pLambert93eh2RGF93 = pRGF932Lambert93eh->inverse();
		pLambert93eh2RGF93->setTransformId(kLambert93eh2RGF93);
		fTransformList.push_back(pLambert93eh2RGF93);

		//Altiude NGF-IGN69
		TLambert93Transformation *pRGF932Lambert93ign69 = new TLambert93Transformation(true, false);
		pRGF932Lambert93ign69->setTransformId(kRGF932Lambert93ign69);
		fTransformList.push_back(pRGF932Lambert93ign69);
		// Inverse
		TARefFrameTransformation *pLambert93ign692RGF93 = pRGF932Lambert93ign69->inverse();
		pLambert93ign692RGF93->setTransformId(kLambert93ign692RGF93);
		fTransformList.push_back(pLambert93ign692RGF93);
	}
            
	// Transformation between CERN projection XYHe and CCS
	TXYHe2MLATransformation* pXYHe2CCS = new TXYHe2MLATransformation(pCernXYHe);
	pXYHe2CCS->setTransformId(kXYHe2CCS);
	fTransformList.push_back(pXYHe2CCS);
	//Inverse
	TARefFrameTransformation* pCCS2XYHe = pXYHe2CCS->inverse(); //utilise new
	pCCS2XYHe->setTransformId(kCCS2XYHe);
	fTransformList.push_back(pCCS2XYHe);


	// Transformation between CERN projection X0Y0He and CERN projection XYHe
	TX0Y0He2XYHeTransformation* pX0Y0He2XYHe =  new TX0Y0He2XYHeTransformation(pCernX0Y0He) ;
	pX0Y0He2XYHe->setTransformId(kX0Y0He2XYHe);
	fTransformList.push_back(pX0Y0He2XYHe);
	//Inverse
	TARefFrameTransformation* pXYHe2X0Y0He =  pX0Y0He2XYHe->inverse(); //utilise new
	pXYHe2X0Y0He->setTransformId(kXYHe2X0Y0He);
	fTransformList.push_back(pXYHe2X0Y0He);


	// Transformation between CERN projection XYHg (Geoid 2000) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe = new TXYHg2XYHeTransformation(pCernXYHg00) ;
	pXYHg2XYHe->setTransformId(kXYHg2XYHe);
	fTransformList.push_back(pXYHg2XYHe);
	//Inverse
	TARefFrameTransformation* pXYHe2XYHg = pXYHg2XYHe->inverse(); //utilise new
	pXYHe2XYHg->setTransformId(kXYHe2XYHg);
	fTransformList.push_back(pXYHe2XYHg);


	// Transformation between CERN projection XYHg (Geoid 2000Topo) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe00Topo = new TXYHg2XYHeTransformation(pCernXYHg00Topo) ;
	pXYHg2XYHe00Topo->setTransformId(kXYHg2XYHe00Topo);
	fTransformList.push_back(pXYHg2XYHe00Topo);
	//Inverse
	TARefFrameTransformation* pXYHe00Topo2XYHg = pXYHg2XYHe00Topo->inverse(); //utilise new
	pXYHe00Topo2XYHg->setTransformId(kXYHe00Topo2XYHg);
	fTransformList.push_back(pXYHe00Topo2XYHg);


	// Transformation between CERN projection XYHg (Geoid 2000Machine) and XYHe 
	TXYHg2XYHeTransformation* pXYHg2XYHe00Machine = new TXYHg2XYHeTransformation(pCernXYHg00Machine) ;
	pXYHg2XYHe00Machine->setTransformId(kXYHg2XYHe00Machine);
	fTransformList.push_back(pXYHg2XYHe00Machine);
	//Inverse
	TARefFrameTransformation* pXYHe00Machine2XYHg = pXYHg2XYHe00Machine->inverse(); //utilise new
	pXYHe00Machine2XYHg->setTransformId(kXYHe00Machine2XYHg);
	fTransformList.push_back(pXYHe00Machine2XYHg);


	// Transformation between CERN projection XYHg (Geoid 1985) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe85 = new TXYHg2XYHeTransformation(pCernXYHg85) ;
	pXYHg2XYHe85->setTransformId(kXYHg2XYHe85);
	fTransformList.push_back(pXYHg2XYHe85);
		//Inverse
	TARefFrameTransformation* pXYHe852XYHg = pXYHg2XYHe85->inverse(); //utilise new
	pXYHe852XYHg->setTransformId(kXYHe852XYHg);
	fTransformList.push_back(pXYHe852XYHg);


	// Transformation between CERN projection XYHg (Geoid 1985Machine) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe85Machine = new TXYHg2XYHeTransformation(pCernXYHg85Machine) ;
	pXYHg2XYHe85Machine->setTransformId(kXYHg2XYHe85Machine);
	fTransformList.push_back(pXYHg2XYHe85Machine);
	//Inverse
	TARefFrameTransformation* pXYHe85Machine2XYHg = pXYHg2XYHe85Machine->inverse(); //utilise new
	pXYHe85Machine2XYHg->setTransformId(kXYHe85Machine2XYHg);
	fTransformList.push_back(pXYHe85Machine2XYHg);

	// Empty transformation between local RF and CCS (transformation are updated with a transformation file)
	TLocal2CCSTransformation *pLocalRFin2CCS = new TLocal2CCSTransformation(pLocalRFin, pCCS, TScaleFactor(), TRotationMatrix(), TTranslation());
	pLocalRFin2CCS->setTransformId(kLocalRFin2CCS);
	fTransformList.push_back(pLocalRFin2CCS);
	// Inverse
	TLocal2CCSTransformation *pCCS2LocalRFout = new TLocal2CCSTransformation(pCCS, pLocalRFout, TScaleFactor(), TRotationMatrix(), TTranslation());
	pCCS2LocalRFout->setTransformId(kCCS2LocalRFout);
	fTransformList.push_back(pCCS2LocalRFout);

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

	std::vector<TAGeoidModel*>::iterator iter = fGeoidList.begin();
	std::vector<TAGeoidModel*>::iterator iterEnd = fGeoidList.end();

	while (iter != iterEnd)
	{
		if( (*iter)->getGeoidId() == geoidId )
			return *iter;

		iter++;
	}

	std::cerr << "Error : Id. not in GeoidList" << std::endl;
	throw TNotInGraphException("TNotInGraphException");
	///
	//TODO@*@
	///
	//exit(EXIT_FAILURE);

	

}


TReferenceEllipsoid* TRefSystemFactory::getEllipsoid(const ERefEll ellId)
{//return a pointer to the ellipsoid asked for
	std::vector<TReferenceEllipsoid*>::iterator iter, iterEnd;
	iter = fRefEllList.begin();
	iterEnd = fRefEllList.end();

	while (iter != iterEnd)
	{
		if((*iter)->getEllId() == ellId)
			return *iter;

		iter++;
	}

	std::cerr << "Error : Id. not in RefEllList" << std::endl;
	throw TNotInGraphException("TNotInGraphException");

	//cerr << "Error : Id. not in RefEllList";
	///
	//TODO@*@
	///
	//exit(EXIT_FAILURE);
}

TAReferenceFrame* TRefSystemFactory::getRefFrame(const ERefFrame refFrameId)
{//return a pointer to the ref frame askes for
	std::vector<TAReferenceFrame*>::iterator iter = fRefFrameList.begin();
	std::vector<TAReferenceFrame*>::iterator iterEnd = fRefFrameList.end();

	while (iter != iterEnd)
	{
		if((*iter)->getRefFrameId() == refFrameId)
			return *iter;

		iter++;
	}

	std::cerr << "Error : Id. not in RefFrameList" << std::endl;
	throw TNotInGraphException("TNotInGraphException");

	//cerr << "Error : Id. not in RefFrameList";
	///
	//TODO@*@
	///
	//exit(EXIT_FAILURE);
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
	std::vector<TARefFrameTransformation*>::iterator iter = fTransformList.begin();
	std::vector<TARefFrameTransformation*>::iterator iterEnd = fTransformList.end();

	while (iter != iterEnd)
	{
		if((*iter)->getTransformId() == id)
			return *iter;

		iter++;
	}

	std::cerr << "Error : Id. not in TransformationList" << std::endl;
	throw TNotInGraphException("TNotInGraphException");
 

	//cerr << "Error : Id. not in TransformationList";
	///
	//TODO@*@
	///
	//exit(EXIT_FAILURE);
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




