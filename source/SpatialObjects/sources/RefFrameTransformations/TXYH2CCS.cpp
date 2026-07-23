// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TXYH2CCS.h"

#include "GeodeticConstants.h"
#include "TAGeoidModel.h"
#include "TARefFrameTransformation.h"
#include "TSpatialPosition.h"
#include "TXYHe2MLATransformation.h"

bool TXYH2CCS::XYH2CCS(TPositionVector &pv, const TRefSystemFactory::EGeoid &geoid)
{
	/*Must be in the 2D+H system*/
	if (pv.getCoordSys() != TCoordSysFactory::k2DPlusH)
		return false;

	if (geoid != TRefSystemFactory::EGeoid::kNoGeoid)
	{
		if (geoid == TRefSystemFactory::EGeoid::kCGSphere)
			return XYHs2CCS(pv);
		else
		{
			XYHg2XYHe(pv, geoid);
			return XYHe2CCS(pv, TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid)->getDefRefEll());
		}
	}
	return false;
}

bool TXYH2CCS::CCS2XYH(TPositionVector &pv, const TRefSystemFactory::EGeoid &geoid)
{
	/*Must be in the 3D cartesian coordinate system*/
	if (pv.getCoordSys() != TCoordSysFactory::k3DCartesian)
		return false;

	if (geoid != TRefSystemFactory::EGeoid::kNoGeoid)
	{
		if (geoid == TRefSystemFactory::EGeoid::kCGSphere)
			return CCS2XYHs(pv);
		else
		{
			CCS2XYHe(pv, TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid)->getDefRefEll());
			return XYHe2XYHg(pv, geoid);
		}
	}
	return false;
}

bool TXYH2CCS::XYHs2CCS(TPositionVector &pv)
{ // Transformation of a position vector using the parameters of the two reference frames
	/*Must be in the 2D+H system*/
	if (pv.getCoordSys() != TCoordSysFactory::k2DPlusH)
		return false;

	// radius of the sphere
	TReal R = sphereRadius;

	// transform TPositionVector
	// distance from P0 (CCS false origin) and XY-plane
	TReal dx = pv.getX().getMetresValue() - XP0;
	TReal dy = pv.getY().getMetresValue() - YP0;
	TReal hs = pv.getH().getMetresValue();
	TReal d = sqrtq((powq(dx, 2)) + (powq(dy, 2)));

	TReal d0 = d * R / (R + hs);
	TReal omega = asinq(d0 / R);
	TReal Z = LITERAL(Zoffset) + (hs * cosq(omega)) - (d0 * tanq(omega / LITERAL(2.0)));

	// change the coordinate system of the position vector
	pv.setCoordSys(TCoordSysFactory::k3DCartesian);

	// change the H coordinate of the position vector into the third coordinate Z
	pv.setZ(TLength(Z));
	return true;
}

bool TXYH2CCS::CCS2XYHs(TPositionVector &pv)
{
	TReal dx, dy, dz, d;
	TReal d0, omega;
	// radius of the sphere
	TReal R = sphereRadius;	
	// transform TPositionVector
	TReal H;

	// distance from P0 in XY-plane
	dx = pv.getX().getMetresValue() - XP0;
	dy = pv.getY().getMetresValue() - YP0;
	dz = pv.getZ().getMetresValue() - Zoffset;
	d = sqrtq( (powq(dx, 2)) + (powq(dy, 2)) );

	omega = atanq(d / (R + dz));
	d0 = d * R * cosq(omega) / (R + dz);
	H = (dz + (d0 * tanq(omega / LITERAL(2.0)))) / cosq(omega);

	// Change the coordinate system of the position vector
	pv.setCoordSys(TCoordSysFactory::k2DPlusH);
	// Change the third dimension Z of the position vector into H
	pv.setH(TLength(H));

	return true;
}

bool TXYH2CCS::XYHe2CCS(TPositionVector &pv, const TReferenceEllipsoid* refEllipsoid)
{
	TReal dx, dy, he, d, d0, Dzh;

	// distance from P0 in XY-plane
	dx = pv.getX().getMetresValue() - XP0;
	dy = pv.getY().getMetresValue() - YP0;
	he = pv.getH().getMetresValue();
	d = sqrtq((powq(dx, 2)) + (powq(dy, 2)));

	// radius of the ellipsoid at azimuth and at phiP0
	TReal rhoalpha = calculateRhoAlpha(dx, dy, refEllipsoid);

	// angle between point and z-axis
	TReal omega = asinq(d / (rhoalpha + he));
	// scale factor
	TReal k = rhoalpha / (rhoalpha + he);
	d0 = k * d;

	// transform TPositionVector
	Dzh = ZP0 - HP0;
	TReal omegaBy2 = omega * LITERAL(0.5);
	TReal newZ(Dzh + he * cosq(omega) - d0 * (tanq(omegaBy2)));

	// change the coordinate system of the position vector
	pv.setCoordSys(TCoordSysFactory::k3DCartesian);
	pv.setZ(TLength(newZ));
	return true;
}

bool TXYH2CCS::CCS2XYHe(TPositionVector &pv, const TReferenceEllipsoid* refEllipsoid)
{
	TReal dx, dy, dz, d, d0;

	// distance from P0 in XY-plane
	dx = pv.getX().getMetresValue() - XP0;
	dy = pv.getY().getMetresValue() - YP0;
	dz = pv.getZ().getMetresValue() - ZP0 + HP0;
	d = sqrtq((powq(dx, 2)) + (powq(dy, 2)));

	//radius of the ellipsoid at azimuth and at phiP0
	TReal rhoalpha = calculateRhoAlpha(dx, dy, refEllipsoid);

	// angle between point and z-axis
	TReal omega = atanq(d / (rhoalpha + dz));
	// scale factor
	TReal k = (rhoalpha * cosq(omega)) / (rhoalpha + dz);
	d0 = k * d;

	// transform TPositionVector
	TReal omegaBy2 = omega * LITERAL(0.5);
	TReal newH((dz + d0 * tanq(omegaBy2)) / cosq(omega));

	// Change the coordinate system of the position vector
	pv.setCoordSys(TCoordSysFactory::k2DPlusH);
	pv.setH(TLength(newH));
	return true;
}

bool TXYH2CCS::XYHg2XYHe(TPositionVector &pv, TRefSystemFactory::EGeoid geoid)
{ // Transformation of a position vector using N (height above geoid)
	TLength h = pv.getH();

	pv.setH(h + getN(pv, geoid));
	return true;
}

bool TXYH2CCS::XYHe2XYHg(TPositionVector &pv, TRefSystemFactory::EGeoid geoid)
{
	TLength h = pv.getH();

	pv.setH(h - getN(pv, geoid));
	return true;
}

TReal TXYH2CCS::calculateRhoAlpha(const	TReal &dx, const TReal &dy, const TReferenceEllipsoid* refEllipsoid)
{
	// bearing from P0 in the XY-plane
	TReal beta = atan2q(dx, dy);
	// Azimuth from P0
	TReal AzimuthRAD = AzimuthCCSYaxis * M_PI / LITERAL(200);
	TReal azimuth = beta + AzimuthRAD;

	// radius of the ellipsoid at azimuth and at phiP0
	TReal PhiP0RAD = PHIP0 * M_PI / LITERAL(200);
	return refEllipsoid->getEuler(PhiP0RAD, azimuth);
}

TLength TXYH2CCS::getN(TPositionVector &pv, const TRefSystemFactory::EGeoid &geoid)
{
	// extraction of N using a tspatialposition of coordinates = pv, and reference frame = CCS
	TSpatialPosition spaPos(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS), pv);
	TAGeoidModel *geoidModel = TRefSystemFactory::getRefSystemFactory()->getGeoid(geoid);

	return geoidModel->getN(spaPos);
}
