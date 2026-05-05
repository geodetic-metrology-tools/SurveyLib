#include "TRegionalGeoid.h"

#include <TNotInGeoidGridException.h>

#include "TReferenceEllipsoid.h"

TRegionalGeoid::TRegionalGeoid(const std::string &name, const TRefSystemFactory::EGeoid &geoidId, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc, const std::string &pathToFile, const int &epsgCode) :
	TAGeoidModel(name, geoidId, def, ell, calc), fPathToFile(pathToFile), fEPSGCode(epsgCode)
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
	
	if (geoidSRS->IsGeographic())
	{
		x = spos.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDeciDegsValue();
		y = spos.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDeciDegsValue();
	}
	else if (geoidSRS->IsGeocentric())
	{
		x = spos.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue();
		y = spos.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue();
	}
	else if (geoidSRS->IsProjected())
	{
		x = spos.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
		y = spos.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
	}
	else if (geoidSRS->IsLocal())
	{
		x = spos.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue();
		y = spos.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue();
	}
	else
	{
		throw std::invalid_argument("Impossible to extract geoid height: Inconsistent coordinate systems");
	}

	// The axis order of the geoid grid is determined by the axis mapping strategy of the geoid SRS.
	// If it is OAMS_TRADITIONAL_GIS_ORDER, the order is (longitude, latitude) or (x, y).
	// If it is OAMS_AUTHORITY_COMPLIANT, the order is determined by the authority and can be (latitude, longitude) or (y, x)
	if (geoidSRS->GetAxisMappingStrategy() == OAMS_TRADITIONAL_GIS_ORDER)
	{
		y -= 360.0;
		dataset->GetRasterBand(1)->InterpolateAtGeolocation(x, y, geoidSRS, GRIORA_Bilinear, &geoidHeight);
	}
	else
	{
		dataset->GetRasterBand(1)->InterpolateAtGeolocation(y, x, geoidSRS, GRIORA_Bilinear, &geoidHeight);
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

bool TRegionalGeoid::prepareXiAndEtaComputation(const TSpatialPosition &sp, TReal &deltaN, TAngle &lambdaOrPhi, TAngle &gridSpacing, const std::string &xiOrEta) const
{
	// deep copy of TSpatialPosition transformed in same reference frame as the geoid CalculationRF
	TSpatialPosition spos = getSpatialPositionInRefFrame(sp, fCalcRFPtr);

	const TAngle lambda(spos.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid());
	const TAngle phi(spos.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid());

	GDALDataset *dataset = openGDALDataset();
	const OGRSpatialReference *geoidSRS = dataset->GetSpatialRef();
	
	double gt[6];
	dataset->GetGeoTransform(gt);

	TReal n_XBefore_Y, n_XAfter_Y, n_X_YBefore, n_X_YAfter = 0.0;
	getNatCornerAroundPoint(lambda.getDeciDegsValue(), phi.getDeciDegsValue(), dataset, abs(gt[1]), abs(gt[5]), n_XBefore_Y, n_XAfter_Y, n_X_YBefore, n_X_YAfter);

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
	TReal xBefore = std::floor((xPoint / gridSpacingX)) * gridSpacingX + gridSpacingX / 2;
	TReal xAfter = std::ceil((xPoint / gridSpacingX)) * gridSpacingX + gridSpacingX / 2;
	TReal yBefore = std::floor((yPoint / gridSpacingY)) * gridSpacingY + gridSpacingY / 2;
	TReal yAfter = std::ceil((yPoint / gridSpacingY)) * gridSpacingY + gridSpacingY / 2;

	CPLErr err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xBefore, yPoint, dataset->GetSpatialRef(), GRIORA_Bilinear, &n_XBefore_Y);
	if (err != CE_None)
	{
		return false;
	}

	err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xAfter, yPoint, dataset->GetSpatialRef(), GRIORA_Bilinear, &n_XAfter_Y);
	if (err != CE_None)
	{
		return false;
	}

	err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xPoint, yBefore, dataset->GetSpatialRef(), GRIORA_Bilinear, &n_X_YBefore);
	if (err != CE_None)
	{
		return false;
	}

	err = dataset->GetRasterBand(1)->InterpolateAtGeolocation(xPoint, yAfter, dataset->GetSpatialRef(), GRIORA_Bilinear, &n_X_YAfter);
	if (err != CE_None)
	{
		return false;
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
