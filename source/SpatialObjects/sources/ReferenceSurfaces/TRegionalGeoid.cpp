#include "TRegionalGeoid.h"

#include <TNotInGeoidGridException.h>

#include "TReferenceEllipsoid.h"

TRegionalGeoid::TRegionalGeoid(const std::string &name,
	const TRefSystemFactory::EGeoid &geoidId,
	TAReferenceFrame *def,
	TReferenceEllipsoid *ell,
	TAReferenceFrame *calc,
	const std::string &pathToFile,
	const int &epsgCode,
	const GDALRIOResampleAlg &interpolationMethod) :
	TAGeoidModel(name, geoidId, def, ell, calc), fPathToFile(pathToFile), fEPSGCode(epsgCode), fInterpolationMethod(interpolationMethod)
{
}

TRegionalGeoid::~TRegionalGeoid()
{
}

TLength TRegionalGeoid::getN(const TSpatialPosition &sp) const
{
	// deep copy of TSpatialPosition transformed in same reference frame as the geoid CalculationRF
	TSpatialPosition spos = getSpatialPositionInRefFrame(sp, fCalcRFPtr);

	GDALDataset *dataset = openGDALDataset();

	double x, y, geoidHeight = 0.0;
	const OGRSpatialReference *geoidSRS = dataset->GetSpatialRef();

	if (!getXAndYFromSpatialPosition(spos, x, y, *geoidSRS))
	{
		throw std::invalid_argument("Impossible to extract geoid height: Be sure to work with geographic coordinates");
	}

	// The axis order of the geoid grid is determined by the axis mapping strategy of the geoid SRS.
	// If it is OAMS_TRADITIONAL_GIS_ORDER, the order is (longitude, latitude) or (x, y).
	// If it is OAMS_AUTHORITY_COMPLIANT, the order is determined by the authority and can be (latitude, longitude) or (y, x)
	if (geoidSRS->GetAxisMappingStrategy() == OAMS_TRADITIONAL_GIS_ORDER)
	{
		dataset->GetRasterBand(1)->InterpolateAtGeolocation(x, y, geoidSRS, fInterpolationMethod, &geoidHeight);
	}
	else
	{
		dataset->GetRasterBand(1)->InterpolateAtGeolocation(y, x, geoidSRS, fInterpolationMethod, &geoidHeight);
	}

	GDALClose(dataset);

	return TLength(geoidHeight);
}

TAngle TRegionalGeoid::getEta(const TSpatialPosition &sp) const
{
	TAngle phiSp = sp.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid();
	TAngle lambdaSp = sp.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid();
	TLength hSp = sp.getCoordinates(TCoordSysFactory::kGeodetic).getH();

	TReal deltaN = 0.0;
	TAngle delta(0.0001, TAngle::kDeciDegs);

	// deep copy of TSpatialPosition transformed in same reference frame as the geoid CalculationRF
	// used to interpolate the slope
	TSpatialPosition sposEast = getSpatialPositionInRefFrame(sp, fCalcRFPtr);
	TSpatialPosition sposWest = getSpatialPositionInRefFrame(sp, fCalcRFPtr);

	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phiSp);
	pv.setLambdaEllipsoid(lambdaSp + delta);
	pv.setH(hSp);
	sposEast.setCoordinates(pv);

	pv.setLambdaEllipsoid(lambdaSp - delta);
	sposWest.setCoordinates(pv);
	try
	{
		TReal nEast = getN(sposEast);
		TReal nWest = getN(sposWest);

		double dLonRad = 2.0 * delta.getRadiansValue();
		double dNdLambda = (nEast - nWest) / dLonRad;

		// Calculate Eta in radians
		// Featherstone, W. E. (1999, November). The use and abuse of vertical deflections. In Sixth South East Asian Surveyors’ Congress Fremantle (Vol. 6, pp. 1-12).
		// equation 4
		double eta_rad = -dNdLambda / (fDefEllPtr->getNu(phiSp) * cos(phiSp.getRadiansValue()));
		return TAngle(eta_rad, TAngle::kRadians);
	}
	catch (const std::exception &)
	{
		std::stringstream ss = generateNotInGeoidGridMessage("getEta", sp);
		throw TNotInGeoidGridException(ss.str());
	}
}

TAngle TRegionalGeoid::getXi(const TSpatialPosition &sp) const
{
	TAngle phiSp = sp.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid();
	TAngle lambdaSp = sp.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid();
	TLength hSp = sp.getCoordinates(TCoordSysFactory::kGeodetic).getH();

	TReal deltaN = 0.0;
	TAngle delta(0.0001, TAngle::kDeciDegs);

	TSpatialPosition sposNorth = getSpatialPositionInRefFrame(sp, fCalcRFPtr);
	TSpatialPosition sposSouth = getSpatialPositionInRefFrame(sp, fCalcRFPtr);

	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phiSp + delta);
	pv.setLambdaEllipsoid(lambdaSp);
	pv.setH(hSp);
	sposNorth.setCoordinates(pv);

	pv.setPhiEllipsoid(phiSp - delta);
	sposSouth.setCoordinates(pv);

	try
	{
		// Central difference for dN/dPhi
		TReal nNorth = getN(sposNorth);
		TReal nSouth = getN(sposSouth);

		double dLatRad = 2.0 * delta.getRadiansValue();
		double dNdPhi = (nNorth - nSouth) / dLatRad;	

		// Calculate Xi in radians
		// Featherstone, W. E. (1999, November). The use and abuse of vertical deflections. In Sixth South East Asian Surveyors’ Congress Fremantle (Vol. 6, pp. 1-12).
		// equation 3
		double xiRad = -dNdPhi / fDefEllPtr->getRho(phiSp);

		// We don't apply the normal curvature of the plumb line because the sign is unclear. No evidence of improvement (using AusGeoid control dataset) when substracting it
		//xiRad -= normalPlumbLineCurvature(phiSp, hSp).getRadiansValue(); // Add the normal curvature of the plumb line) 
		return TAngle(xiRad, TAngle::kRadians);
	}
	catch (const std::exception &)
	{
		std::stringstream ss = generateNotInGeoidGridMessage("getXi", sp);
		throw TNotInGeoidGridException(ss.str());
	}
}

bool TRegionalGeoid::isInGrid(const TSpatialPosition &point) const
{
	return false;
}

GDALDataset *TRegionalGeoid::openGDALDataset() const
{
	GDALAllRegister();
	GDALDataset *dataset = static_cast<GDALDataset *>(GDALOpen(fPathToFile.c_str(), GA_ReadOnly));

	if (!dataset)
	{
		throw std::invalid_argument("GDAL error: Unable to open geoid file : " + fPathToFile);
	}
	else
	{
		OGRSpatialReference *geoidSRS = new OGRSpatialReference();
		geoidSRS->importFromEPSG(fEPSGCode);
		dataset->SetSpatialRef(geoidSRS);
		return dataset;
	}
}

bool TRegionalGeoid::getXAndYFromSpatialPosition(const TSpatialPosition &sp, TReal &x, TReal &y, const OGRSpatialReference &geoidSRS) const
{
	if (geoidSRS.IsGeographic())
	{
		x = sp.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDeciDegsValue();
		if (x > 180.0)
		{
			x -= 360.0;
		}
		y = sp.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDeciDegsValue();
		if (y > 180.0)
		{
			y -= 360.0;
		}
		return true;
	}
	else
	{
		return false;
	}
}

TAngle TRegionalGeoid::normalPlumbLineCurvature(const TAngle &phi, const TLength h) const
{
	// See Heiskanen, W. A., & Moritz, H. (1967). Physical geodesy. Bulletin Géodésique (1946-1975), 86(1), 491-492. equation 5-34
	TReal deltaPhiNormal_arcSeconds = 0.17 * h.getKMetresValue() * sin(2 * phi.getRadiansValue());
	std::cout << "Normal curvature: " << deltaPhiNormal_arcSeconds << std::endl;
	TAngle deltaPhiNormal = TAngle(deltaPhiNormal_arcSeconds / 3600, TAngle::kDeciDegs);
	return deltaPhiNormal;
}

std::stringstream TRegionalGeoid::generateNotInGeoidGridMessage(const std::string &functionCalled, const TSpatialPosition &position) const
{
	std::stringstream ss;
	ss << "TNotInGeoidGridException: " << functionCalled << " function problem with coordinate ";
	ss << "(" << position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << ","
	   << position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << ","
	   << position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << ").";
	return ss;
}
