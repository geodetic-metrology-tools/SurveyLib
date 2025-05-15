// SPDX-FileCopyrightText: 2025 CERN

// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <utils/PositionVectorUtils.h>
#include <TDataParameters.h>
#include <TSpatialPosition.h>
#include <TRefSystemFactory.h>

TPositionVector utils::getPositionVector(
    double x_long, double y_lat, double z_h, 
    const TDataParameters & dp)
{
    TPositionVector pv(TCoordSysFactory::k3DCartesian);
	TCoordSysFactory::ECoordSys coordSys = dp.getCoordinateSystem();
	TAngle::EUnits angleUnit = dp.getAngleUnits();

    if(coordSys==TCoordSysFactory::k3DCartesian)
    {
        pv.setX(TLength(x_long));
        pv.setY(TLength(y_lat));
        pv.setZ(TLength(z_h));
    }
    else if(coordSys==TCoordSysFactory::kGeodetic)
    {
        pv.setCoordSys(TCoordSysFactory::kGeodetic);
        TAngle tmpLong;
        TAngle tmpLat;
		if (angleUnit == TAngle::kGons)
		{
			tmpLong.setGonsValue(x_long);
			tmpLat.setGonsValue(y_lat);
		}
		else if (angleUnit == TAngle::kDeciDegs)
		{
			tmpLong.setDeciDegsValue(x_long);
			tmpLat.setDeciDegsValue(y_lat);
		}
		pv.setPhiEllipsoid(tmpLat);
		pv.setLambdaEllipsoid(tmpLong);
		pv.setH(TLength(z_h));
    }
    else if(coordSys==TCoordSysFactory::k2DPlusH)
    {
		pv.setCoordSys(TCoordSysFactory::k2DPlusH);
		pv.setX(TLength(x_long));
		pv.setY(TLength(y_lat));
		pv.setH(TLength(z_h));
    }
    else
        throw std::invalid_argument("Unsupported input coordinate system");

    return pv;
}


void utils::extractCoordinates(
    const TSpatialPosition & position,
    double * x_long, double * y_lat, double * z_h,
    const TDataParameters & dp)
{
	TCoordSysFactory::ECoordSys coordSys = dp.getCoordinateSystem();
	TAngle::EUnits angleUnit = dp.getAngleUnits();
    if(coordSys==TCoordSysFactory::k3DCartesian)
    {
        *x_long = position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue();
        *y_lat = position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue();
        *z_h = position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue();
    }
    else if(coordSys==TCoordSysFactory::kGeodetic)
    {
		if (angleUnit == TAngle::kGons)
		{
			*x_long = position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getGonsValue();
			*y_lat = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getGonsValue();
		}
		else if (angleUnit == TAngle::kDeciDegs)
		{
			*x_long = position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDeciDegsValue();
			*y_lat = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDeciDegsValue();
		}
		*z_h = position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue();
    }
    else if(coordSys==TCoordSysFactory::k2DPlusH)
    {
		*x_long = position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
		*y_lat = position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
		*z_h = position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue();		
    }
    else
        throw std::invalid_argument("Unsupported input coordinate system");
}
