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
	TReal deltaN = 0.0;
	TAngle phi;
	TAngle gridSpacingY;
	if (prepareXiAndEtaComputation(sp, deltaN, phi, gridSpacingY, "Eta"))
	{
		TReal eta_rad = deltaN / (fDefEllPtr->getNu(phi) * gridSpacingY.getRadiansValue() * cos(phi.getRadiansValue()));
		return TAngle(eta_rad, TAngle::kRadians);
	}
	else
	{
		std::stringstream ss = generateNotInGeoidGridMessage("getEta", sp);
		throw TNotInGeoidGridException(ss.str());
	}
}

TAngle TRegionalGeoid::getXi(const TSpatialPosition &sp) const
{
	TReal deltaN = 0.0;
	TAngle lambda;
	TAngle gridSpacingX;
	if (prepareXiAndEtaComputation(sp, deltaN, lambda, gridSpacingX, "Xi"))
	{
		TReal xiRad = deltaN / (fDefEllPtr->getRho(lambda) * gridSpacingX.getRadiansValue());
		return TAngle(xiRad, TAngle::kRadians);
	}
	else
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

bool TRegionalGeoid::prepareXiAndEtaComputation(const TSpatialPosition &sp, TReal &deltaN, TAngle &lambdaOrPhi, TAngle &gridSpacing, const std::string &xiOrEta) const
{
	// deep copy of TSpatialPosition transformed in same reference frame as the geoid CalculationRF
	TSpatialPosition spos = getSpatialPositionInRefFrame(sp, fCalcRFPtr);

	const TAngle lambda(spos.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid());
	const TAngle phi(spos.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid());

	GDALDataset *dataset = openGDALDataset();
	const OGRSpatialReference *geoidSRS = dataset->GetSpatialRef();

	double x = 0, y = 0;
	if (!getXAndYFromSpatialPosition(spos, x, y, *geoidSRS))
	{
		throw std::invalid_argument("Impossible to extract deflection of the vertical: Be sure to work with geographic coordinates");
	}

	double gt[6];
	dataset->GetGeoTransform(gt);

	TReal n_XBefore_Y, n_XAfter_Y, n_X_YBefore, n_X_YAfter = 0.0;
	getNatCornerAroundPoint(x, y, dataset, abs(gt[1]), abs(gt[5]), n_XBefore_Y, n_XAfter_Y, n_X_YBefore, n_X_YAfter);

	GDALClose(dataset);

	if (xiOrEta == "Xi")
	{
		deltaN = n_X_YBefore - n_X_YAfter;
		lambdaOrPhi = lambda;
		gridSpacing = TAngle(abs(gt[1]), TAngle::kDeciDegs); // gt[1] is the x grid spacing
		return true;
	}
	else if (xiOrEta == "Eta")
	{
		deltaN = n_XBefore_Y - n_XAfter_Y;
		lambdaOrPhi = phi;
		gridSpacing = TAngle(abs(gt[5]), TAngle::kDeciDegs); // gt[5] is the y grid spacing (often negative)
		return true;
	}
	else
	{
		return false;
	}
}

bool TRegionalGeoid::getNatCornerAroundPoint(const TReal &xPoint,
	const TReal &yPoint,
	const GDALDataset *dataset,
	const TReal &gridSpacingX,
	const TReal &gridSpacingY,
	TReal &n_XBefore_Y,
	TReal &n_XAfter_Y,
	TReal &n_X_YBefore,
	TReal &n_X_YAfter) const
{
	TReal xBefore =0.0, xAfter =0.0 , yBefore = 0.0, yAfter = 0.0;
	if (xPoint >= 0)
	{
		xBefore = std::floor((xPoint / gridSpacingX)) * gridSpacingX + gridSpacingX / 2;
		xAfter = std::ceil((xPoint / gridSpacingX)) * gridSpacingX + gridSpacingX / 2;
	}
	else
	{
		xAfter = std::floor((xPoint / gridSpacingX)) * gridSpacingX - gridSpacingX / 2;
		xBefore = std::ceil((xPoint / gridSpacingX)) * gridSpacingX - gridSpacingX / 2;
	}

	if (yPoint >= 0)
	{
		yBefore = std::floor((yPoint / gridSpacingY)) * gridSpacingY + gridSpacingY / 2;
		yAfter = std::ceil((yPoint / gridSpacingY)) * gridSpacingY + gridSpacingY / 2;
	}
	else
	{
		yAfter = std::floor((yPoint / gridSpacingY)) * gridSpacingY - gridSpacingY / 2;
		yBefore = std::ceil((yPoint / gridSpacingY)) * gridSpacingY - gridSpacingY / 2;
	}

	CPLErr err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xBefore, yPoint, dataset->GetSpatialRef(), fInterpolationMethod, &n_XBefore_Y);
	if (err != CE_None)
	{
		return false;
	}

	err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xAfter, yPoint, dataset->GetSpatialRef(), fInterpolationMethod, &n_XAfter_Y);
	if (err != CE_None)
	{
		return false;
	}
	if (xPoint<0)
	{
		TReal temp = n_XAfter_Y;
		n_XAfter_Y = n_XBefore_Y;
		n_XBefore_Y = temp;
	}

	err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xPoint, yBefore, dataset->GetSpatialRef(), fInterpolationMethod, &n_X_YBefore);
	if (err != CE_None)
	{
		return false;
	}

	err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xPoint, yAfter, dataset->GetSpatialRef(), fInterpolationMethod, &n_X_YAfter);
	if (err != CE_None)
	{
		return false;
	}
	if (yPoint < 0)
	{
		TReal temp = n_X_YAfter;
		n_X_YAfter = n_X_YBefore;
		n_X_YBefore = temp;
	}
	return true;
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
