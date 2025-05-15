// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <TGeodetic2Mercator.h>
#include <TRefFrameInfo.h>
#include <GeodeticConstants.h>
#include <math.h>
#include <complex>

using namespace std::complex_literals;

/////////////////////////////////////////////////////////

// Anonymous namespace for local constants
namespace
{
	// CONSTANTS

//scale on the central meridian
const double k0 = 1.00006;

// Central meridian (center of the FCC)
const double lam0_rad = 6.14 * PI / 180;

// Latitude of origin
const double phi0_rad = 0;

//False easting, false northing
const double e0 = 0;
const double n0 = 0;

// GRS 80 ellipsoid constant
const double a = SemiMajorAxisGRS80;
const double b = SemiMinorAxisGRS80;
const double e2 = eccentrGRS80;
const double e = sqrt(e2);

}


TGeodetic2Mercator::TGeodetic2Mercator(bool fromGeodetic) : fFromGeodetic(fromGeodetic)
{
}

TGeodetic2Mercator *TGeodetic2Mercator::clone() const
{
	return new TGeodetic2Mercator(*this);
}

TGeodetic2Mercator *TGeodetic2Mercator::inverse() const
{
	return new TGeodetic2Mercator(!fFromGeodetic);
}

TAReferenceFrame *TGeodetic2Mercator::getSourceFrame() const
{
	if (fFromGeodetic)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRF);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRFMercator_eh);
	}
}

TAReferenceFrame *TGeodetic2Mercator::getDestinationFrame() const
{
	if (!fFromGeodetic)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRF);
	}
	else 
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRFMercator_eh);
	}
}

bool TGeodetic2Mercator::transform(TPositionVector &pv) const
{
	if (fFromGeodetic)
		return transformFromGeodetic(pv);
	return transformToGeodetic(pv);
}

//////////////////////////////////////////////////////


bool TGeodetic2Mercator::transformToGeodetic(TPositionVector &pv) const
{
	// Inverse Transvers Mercator projection
	// Fomulas given in PROJECTION CARTOGRAPHIQUE MERCATOR TRANSVERSE Algorithmes, IGN 1995
	
	// transform x y h
	TSpatialPosition position(getSourceFrame());
	if (!position.setCoordinates(pv))
		return false;

	const double X = position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
	const double Y = position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
	const double h = position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue();

	// ALG 0052
	const double n = k0 * a;
	const double xS = e0;
	const double yS = n0 - n * devMeridianArc(e, phi0_rad);

	// ALG0029
	const double c1 = 1.0 - 1.0 / 4.0 * pow(e, 2) - 3.0 / 64.0 * pow(e, 4) - 5.0 / 256.0 * pow(e, 6) - 175.0 / 16384.0 * pow(e, 8);
	const double c2 = 1.0 / 8.0 * pow(e, 2) + 1.0 / 48.0 * pow(e, 4) + 7.0 / 2048.0 * pow(e, 6) + 4.0 / 61440.0 * pow(e, 8);
	const double c3 = 1.0 / 768.0 * pow(e, 4) + 3.0 / 1280.0 * pow(e, 6) + 559.0 / 368640.0 * pow(e, 8);
	const double c4 = 17.0 / 30720.0 * pow(e, 6) + 283.0 / 430080.0 * pow(e, 8);
	const double c5 = 4397.0 / 41287680.0 * pow(e, 8); 

	// ALG0031
	std::complex<double> zP((Y - yS) / (n * c1), (X - xS) / (n * c1));
	std::complex<double> z = zP - (c2 * sin(2.0 * 1.0 * zP) + c3 * sin(2.0 * 2.0 * zP) + c4 * sin(2.0 * 3.0 * zP) + c5 * sin(2.0 * 4.0 * zP));

	double latIso_rad = real(z);
	const double latIsoS_rad = imag(z);

	const double lam_rad = lam0_rad + atan(sinh(latIsoS_rad) / cos(latIso_rad));
	const double phiP_rad = asin(sin(latIso_rad) / cosh(latIsoS_rad));

	latIso_rad = latTolatIso(0, phiP_rad);
	const double phi_rad = latIsoTolat(e, latIso_rad);
		
	// We can't leave it in the Geodetic form. Other code expects to get Cartesian
	TPositionVector tmp = TPositionVector(phi_rad, lam_rad, h, TCoordSysFactory::kGeodetic);
	TSpatialPosition outpos(getDestinationFrame());
	if (!outpos.setCoordinates(tmp))
		return false;
	// Project to Carthesian
	pv = outpos.getCoordinates(TCoordSysFactory::k3DCartesian);

	return true;
	
}


bool TGeodetic2Mercator::transformFromGeodetic(TPositionVector &pv) const
{
	// Transverse Mercator projection.
	// Fomulas given in PROJECTION CARTOGRAPHIQUE MERCATOR TRANSVERSE Algorithmes, IGN 1995

	
	// transform phi lambda h into east, north, h
	TSpatialPosition position(getSourceFrame());
	if (!position.setCoordinates(pv))
		return false;

	const double phi_rad = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue();
	const double lam_rad = position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue();
	const double h_m = position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue();
	
	// ALG 0052
	const double n = k0 * a;
	const double xS = e0;
	const double yS = n0 - n * devMeridianArc(e, phi0_rad);
	
	// ALG 0028
	const double c1 = 1.0 - 1.0 / 4.0 * pow(e, 2) - 3.0 / 64.0 * pow(e, 4) - 5.0 / 256.0 * pow(e, 6) - 175.0 / 16384.0 * pow(e, 8);
	const double c2 = 1.0 / 8.0 * pow(e, 2) - 1.0 / 96.0 * pow(e, 4) - 9.0 / 1024.0 * pow(e, 6) - 901.0 / 184320.0 * pow(e, 8);
	const double c3 = 13.0 / 768.0 * pow(e, 4) + 17.0 / 5120.0 * pow(e, 6) - 311.0 / 737280.0 * pow(e, 8);
	const double c4 = 61.0 / 15360.0 * pow(e, 6) + 899.0 / 430080.0 * pow(e, 8);
	const double c5 = 49561.0 / 41287680.0 * pow(e, 8); 

	// ALG 0030
	const double latIso_rad = latTolatIso(e, phi_rad);
	const double phiP_rad = asin(sin(lam_rad - lam0_rad) / cosh(latIso_rad));
	const double latIsoS_rad = latTolatIso(0, phiP_rad);
	const double lambdaP_rad = atan(sinh(latIso_rad) / cos(lam_rad - lam0_rad));

	std::complex<double> z(lambdaP_rad, latIsoS_rad);
	std::complex<double> zTotal = n * c1 * z + n * (c2 * sin(2.0 * z) + c3 * sin(2.0 * 2.0 * z) + c4 * sin(2.0 * 3.0 * z) + c5 * sin(2.0 * 4.0 * z));

	const double east_m = imag(zTotal) + xS;
	const double north_m = real(zTotal) + yS;

	TPositionVector tmp = TPositionVector(east_m, north_m, h_m, TCoordSysFactory::k2DPlusH);
	TSpatialPosition outpos(getDestinationFrame());
	if (!outpos.setCoordinates(tmp))
	{
		return false;
	}
	else
	{
		pv = TPositionVector(east_m, north_m, h_m, TCoordSysFactory::k2DPlusH);

		return true;
	}
	
}

double TGeodetic2Mercator::latTolatIso(double first_e, double phi_rad) const
{
	// ALG0001 
	double latIso_rad = log(tan(PI_4 + phi_rad / 2.0) * pow((1.0 - first_e * sin(phi_rad)) / (1.0 + first_e * sin(phi_rad)), first_e / 2.0));
	return latIso_rad;
}

double TGeodetic2Mercator::latIsoTolat(double first_e, double latIso_rad) const
{
	// ALG0002
	double phi_rad_i1 = 2.0 * atan(exp(latIso_rad)) - PI_2;

	double phi_rad_i = 2.0 * atan(pow((1.0 + first_e * sin(phi_rad_i1)) / (1.0 - first_e * sin(phi_rad_i1)), first_e / 2.0) * exp(latIso_rad)) - PI_2;

	while (abs(phi_rad_i - phi_rad_i1) > 1.0 * pow(10, -11))
	{
		phi_rad_i1 = phi_rad_i;
		phi_rad_i = 2.0 * atan(pow((1.0 + first_e * sin(phi_rad_i1)) / (1.0 - first_e * sin(phi_rad_i1)), first_e / 2.0) * exp(latIso_rad)) - PI_2;
	}

	return phi_rad_i;
}

double TGeodetic2Mercator::devMeridianArc(double first_e, double phi_rad) const
{
	// Test values
	//e = 0.08199188998;

	// ALG0025
	const double c1 = 1.0 - 1.0 / 4.0 * pow(first_e, 2) - 3.0 / 64.0 * pow(first_e, 4) - 5.0 / 256.0 * pow(first_e, 6) - 175.0 / 16384.0 * pow(first_e, 8);
	const double c2 = -3.0 / 8.0 * pow(first_e, 2) - 3.0 / 32.0 * pow(first_e, 4) - 45.0 / 1024.0 * pow(first_e, 6) - 105.0 / 4096.0 * pow(first_e, 8);
	const double c3 = 15.0 / 256.0 * pow(first_e, 4) + 45.0 / 1024.0 * pow(first_e, 6) + 525.0 / 16384.0 * pow(first_e, 8);
	const double c4 = - 35.0 / 3072.0 * pow(first_e, 6) - 175.0 / 12288.0 * pow(first_e, 8);
	const double c5 = 315.0 / 131072.0 * pow(first_e, 8);

	// Test values
	//phi_rad = 0.78539816340;
	// ALG0026
	double betaS = c1 * phi_rad + c2 * sin(2 * phi_rad) + c3 * sin(2.0 * 2.0 * phi_rad) + c4 * sin(2.0 * 3.0 * phi_rad) + c5 * sin(2.0 * 4.0 * phi_rad);

	return betaS;
}

double TGeodetic2Mercator::factorial(int nb) const
{
	double factor = 1;
	for (int i=1; i<=nb; i++)
	{
		factor = factor * i;
	}
	return factor;
}
