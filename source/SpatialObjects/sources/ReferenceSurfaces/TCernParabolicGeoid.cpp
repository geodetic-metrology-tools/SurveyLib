// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// 
// TCernParabolicGeoid
//
// Paraboloid defined to approximate the geoid in CERN's area, 
// with respect to the swiss mapping plane
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
//forward declarations

#include	"GeodeticConstants.h"
#include	"TGraph.h"
#include	"TSpatialPosition.h"
#include	"TAReferenceFrame.h"
#include	"TCernParabolicGeoid.h"

#include	"TLength.h"
#include	"TAngle.h"


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
const TReal TCernParabolicGeoid::scaleFactor = LITERAL(0.001);
const TReal TCernParabolicGeoid::scaleFactorM = LITERAL(0.01);
const TAngle TCernParabolicGeoid::ang_h0 = TAngle(LITERAL(48.772), TAngle::kGons);
const TReal TCernParabolicGeoid::a_h0 = LITERAL(0.535);
const TReal TCernParabolicGeoid::b_h0 = -LITERAL(0.096);
const TAngle TCernParabolicGeoid::ang_LEP = TAngle(LITERAL(48.219), TAngle::kGons);
const TReal TCernParabolicGeoid::a_LEP = LITERAL(0.614);
const TReal TCernParabolicGeoid::b_LEP = -LITERAL(0.106);


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TCernParabolicGeoid::TCernParabolicGeoid() : TAGeoidModel()
{
	fA = 0;
	fB = 0;
	fThs = 0;
	costhc = 0;
	cosazp = 0;
	sinthc = 0;
	sinazp = 0;

}

/* Constructor taking the geoid model name and the parameters of the 
 *	paraboloid as arguments.
 *	
 *	The paraboloid is of the form:
 *		
 *						a                 b
 *		  z = (xp*xp) * -   +   (yp*yp) * -
 *						2                 2
 */

TCernParabolicGeoid::TCernParabolicGeoid(const std::string &name,
	const TRefSystemFactory::EGeoid &geoidId,
	const TReal a,
	const TReal b,
	const TAngle ths,
	TAReferenceFrame *def,
	TReferenceEllipsoid *ell,
	TAReferenceFrame *calc) :
	TAGeoidModel(name, geoidId, def, ell, calc), fA(a), fB(b), fThs(ths.getRadiansValue())
{
	// set the derived parameters of the paraboloid (see EDMS doc 308419 85_ballPart2.pdf page 99)
	TReal thc, azp;
	TReal azxs = -LITERAL(1.12878) * GON2RAD; // Azimuth of the X axis of the swiss system at P0 (Xswiss), computed as the difference between gsc (38.90742) and AzimuthCCSYaxis (37.77864) 
	TReal gsc = LITERAL(38.90742) * GON2RAD; // Bearing of Yccs with respect to Xswiss 

	thc = fThs - gsc; // Bearing between Xswiss and Yp (Yp = Y axis of the paraboloid)
	azp = fThs + azxs; // Azimuth of Yp with respect to Xswiss
	costhc = cosq(thc);
	sinthc = sinq(thc);
	cosazp = cosq(azp);
	sinazp = sinq(azp);
}


// **Deliberately not implemented**
//TCernParabolicGeoid::TCernParabolicGeoid( const  TCernParabolicGeoid& original )
//{	// copy constructor
//}


TCernParabolicGeoid::~TCernParabolicGeoid()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


// **Deliberately not implemented**
//TCernParabolicGeoid&  TCernParabolicGeoid::operator=(const TCernParabolicGeoid& right)
//{	// Copy Assignment operator
//
//	if (this != &right)
//	{
//	}
//	return *this;
//}


TLength	TCernParabolicGeoid::getN( const TSpatialPosition& position ) const
{//
	TReal xp, yp;
	computeLocalParaboloidCoordinates(position, xp, yp);

	//Calculate N (separation between ellipsoid and geoid) in meters
	TLength fNValue;
	fNValue.setMetresValue( ((fA/2)*xp*xp + (fB/2)*yp*yp)*scaleFactorM );
	return fNValue;
}


TAngle	TCernParabolicGeoid::getXi( const TSpatialPosition& sp ) const
{
	TReal xp, yp;
	computeLocalParaboloidCoordinates(sp, xp, yp);

	// Calculate the vertical deflection in N-S direction  
	TAngle fXiValue;
	fXiValue.setRadiansValue((fA*sinazp*xp -fB*cosazp*yp)/100000 ); //* LITERAL(6.366);
	return fXiValue;

}

TAngle	TCernParabolicGeoid::getEta( const TSpatialPosition& sp ) const
{
	TReal xp, yp;
	computeLocalParaboloidCoordinates(sp, xp, yp);
	
	// Calculate the vertical deflection in E-W direction 
	TAngle fEtaValue;
	fEtaValue.setRadiansValue((-fA*cosazp*xp -fB*sinazp*yp)/100000 ); // * LITERAL(6.366);
	return fEtaValue;

}

bool TCernParabolicGeoid::computeLocalParaboloidCoordinates(const TSpatialPosition &sp, TReal &xp, TReal &yp) const
{
	// deep copy of TSpatialPosition transformed in same reference frame as the geoid CalculationRF
	TSpatialPosition position = getSpatialPositionInRefFrame(sp, fCalcRFPtr);

	TReal x, y;
	TReal dx, dy;
	TReal falseOriginX(XP0), falseOriginY(LITERAL(YP0));

	x = position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue();
	y = position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue();

	dx = (x - falseOriginX) * scaleFactor;
	dy = (y - falseOriginY) * scaleFactor;

	xp = dx * costhc - dy * sinthc;
	yp = dx * sinthc + dy * costhc;

	return true;
}

TAngle TCernParabolicGeoid::getDAlpha(const TSpatialPosition &sp, const TAngle &latitude) const
{
	// deep copy of TSpatialPosition and check the reference frame is the same as the geoid CalculationRF
	TSpatialPosition position = getSpatialPositionInRefFrame(sp, fCalcRFPtr); 

	TReal phi = latitude.getRadiansValue();
	TAngle eta, fDAlphaValue;
	eta = getEta(position);
	fDAlphaValue = eta * tanq(phi);
	return fDAlphaValue;
}


/////////////////////////////////////////////////////////////////////////////////
//END
/////////////////////////////////////////////////////////////////////////////////
