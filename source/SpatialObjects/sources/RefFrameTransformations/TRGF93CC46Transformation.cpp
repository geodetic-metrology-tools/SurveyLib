#include <TRGF93CC46Transformation.h>

#include <TRefFrameInfo.h>

#include <assert.h>
#define  _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <filesystem>
#include <sstream>

#ifdef CIRCE_EXEC_DIR
	# define CIRCE_DIR CIRCE_EXEC_DIR
#endif


/////////////////////////////////////////////////////////

// Anonymous namespace for local constants
namespace
{
	  //CONSTANTS

    //Zone number
    const int zoneNumber = 5;

    //Origine latitude
    const double phi0 = (41 + zoneNumber) * (M_PI/180.0);

    //Origine longitude
    const double lambda0 = 3.0 *(M_PI/180.0);

    //changed to radians
    const double phi1 = phi0 - (0.75)*(M_PI/180.0);
    const double phi2 = phi0 + (0.75)*(M_PI/180.0);

    //Constant X0 [m]
    const double E0 = 1700000;
    //Constant Y0 [m]
    const double N0 = (zoneNumber * 1000000) + 200000;

    //Parameters of the elipsoide GRS80 from Wikipedia
    const double a = 6378137.0;
    const double e2 =  0.006694380022903415749574948586289306212443890;
    const double e = sqrt(e2);
    
    // Calculations
    const double L0 = 0.5 * log((1+sin(phi0))/(1-sin(phi0))) - (e/2) * log((1+e*sin(phi0))/(1-e*sin(phi0)));
    const double L1 = 0.5 * log((1+sin(phi1))/(1-sin(phi1))) - (e/2) * log((1+e*sin(phi1))/(1-e*sin(phi1)));
    const double L2 = 0.5 * log((1+sin(phi2))/(1-sin(phi2))) - (e/2) * log((1+e*sin(phi2))/(1-e*sin(phi2)));

    const double n = log((a/sqrt(1-e2*sin(phi2)*sin(phi2))*cos(phi2))/(a/sqrt(1-e2*sin(phi1)*sin(phi1))*cos(phi1))) /(L1 -L2);

    const double C = (a/(sqrt(1-e2 * sin(phi1) * sin(phi1)))*cos(phi1))/n * exp(n*L1);

    const double Xs = E0;
    const double Ys = N0 + C * exp(-n*L0);


}


TRGF93ZoneTransformation::TRGF93ZoneTransformation(bool fromRGF93, bool ellipsHeight)
	: fFromRGF93(fromRGF93), fEllipsHeight(ellipsHeight)
{
}

TRGF93ZoneTransformation * TRGF93ZoneTransformation::clone() const
{
    return new TRGF93ZoneTransformation(*this);
}

TRGF93ZoneTransformation * TRGF93ZoneTransformation::inverse() const
{
    return new TRGF93ZoneTransformation(!fFromRGF93, fEllipsHeight);
}

TAReferenceFrame * TRGF93ZoneTransformation::getSourceFrame() const
{
	if (fFromRGF93)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93);
	}
	else if (fEllipsHeight)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_eh);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_raf);
	}
}

TAReferenceFrame * TRGF93ZoneTransformation::getDestinationFrame() const
{
	if (!fFromRGF93)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93);
	}
	else if (fEllipsHeight)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_eh);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_raf);
	}
}

bool TRGF93ZoneTransformation::transform(TPositionVector & pv) const
{
    if(fFromRGF93)
        return transformFromRGF93(pv);
    return transformToRGF93(pv);
}

//////////////////////////////////////////////////////


bool TRGF93ZoneTransformation::transformToRGF93(TPositionVector & pv) const
{
     //transform x y h
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

	const double X = position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
    const double Y = position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
    double h = position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue();

	if (position.getRefFrame() == TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_raf))
	{
		// We call Circé developped by the french IGN to convert altitude into ellipsoidal height
		circeTransfoRafToH(X, Y, h);
	}

    double R = sqrt((X-Xs)*(X-Xs)+ (Y-Ys)*(Y-Ys));
    double gama = atan((X-Xs)/(Ys-Y)); 

    double lambda = lambda0 + (gama/n);

    double LL = (-1/n)*log(abs(R/C));


    double phi = 2*atan(exp(LL))-(TAngle::piBy2().getRadiansValue());

    for (int i = 0; i != kMaxIter; i++)
    {
        double PHInew = 2 * atan(pow((1+e*sin(phi))/(1-e*sin(phi)),(e/2)) *exp(LL))-(TAngle::piBy2().getRadiansValue());
        double delta = abs(phi - PHInew);
        phi = PHInew;

        if(delta<1e-10)
        break;
    }

	//pv = TPositionVector(phi, lambda, h, TCoordSysFactory::kGeodetic);
	// We can't leave it in the Geodetic form. Other code expects to get Cartesian
    TPositionVector tmp = TPositionVector(phi, lambda, h, TCoordSysFactory::kGeodetic);
	TSpatialPosition outpos(getDestinationFrame());
	if(!outpos.setCoordinates(tmp))
        return false;
	// Project to Carthesian
	pv = outpos.getCoordinates(TCoordSysFactory::k3DCartesian);
	
    return true;

}

bool TRGF93ZoneTransformation::transformFromRGF93(TPositionVector & pv) const
{
    //transform phi lambda h
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

    const double phi = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue();
    const double lambda = position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue();
    double h = position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue();

	double L =  0.5 * log((1+sin(phi))/(1-sin(phi)))   - (e/2) * log((1+e*sin(phi))/(1-e*sin(phi)));

    double R = C*exp(-n*L);
    double gama = n*(lambda-lambda0);

    double X = Xs + R*sin(gama);
    double Y = Ys - R*cos(gama);

	TPositionVector tmp = TPositionVector(X, Y, h, TCoordSysFactory::k2DPlusH);
	TSpatialPosition outpos(getDestinationFrame());
	if (!outpos.setCoordinates(tmp))
	{
		return false;
	}
	else if (outpos.getRefFrame() == TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_raf))
	{
		// We call Circé developped by the french IGN to convert ellipsoidal height into altitude
		circeTransfoHToRaf(X, Y, h);
	}

    pv = TPositionVector(X, Y, h, TCoordSysFactory::k2DPlusH);

    return true;

}

void TRGF93ZoneTransformation::circeTransfoRafToH(const double & X, const double & Y, double & h) const
{
	std::string circePath = CIRCE_DIR;
	std::string circeOption = "--sourceCRS=RGF93CC46.IGN69 "
							  "--sourceFormat=ENV.METERS.RADIANS "
							  "--targetCRS=RGF93CC46. "
							  "--targetFormat=ENHCS.METERS.DEGREES "
							  "--displayPrecision=0.00001 --plainDMS --gridLoading=BINARY";

	std::string cmdString = "\"" + circePath + "/circeFR.exe\"" + " --metadataFile=" + circePath + "/Data/DataFRnew.txt " + circeOption + " "
							+ std::to_string(X) + " " + std::to_string(Y) + " " + std::to_string(h);

	const char *cmd = cmdString.c_str();
	std::string result = execCirce(cmd);
	readCirceResult(result, h);
}

void TRGF93ZoneTransformation::circeTransfoHToRaf(const double &X, const double &Y, double &h) const
{
	std::string circePath = CIRCE_DIR;
	std::string circeOption = "--sourceCRS=RGF93CC46. "
							  "--sourceFormat=ENH.METERS.RADIANS "
							  "--targetCRS=RGF93CC46.IGN69 "
							  "--targetFormat=ENVCS.METERS.DEGREES "
							  "--displayPrecision=0.00001 --plainDMS --gridLoading=BINARY";

	std::string cmdString = "\"" + circePath + "/circeFR.exe\"" + " --metadataFile=" + circePath + "/Data/DataFRnew.txt " + circeOption + " "
							+ std::to_string(X) + " " + std::to_string(Y) + " " + std::to_string(h);

	const char *cmd = cmdString.c_str();
	std::string result = execCirce(cmd);
	readCirceResult(result, h);
}

std::string TRGF93ZoneTransformation::execCirce(const char *cmd) const
{
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get()))
	{
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
			result += buffer.data();
	}
	return result;
}

void TRGF93ZoneTransformation::readCirceResult(std::string result, double& h) const
{
	std::stringstream ss(result);
	double x, y, conv, scale, sigmaZ;
	std::string infoGeoid1, infoGeoid2, sep, unit;

	ss >> x >> y >> h >> conv >> scale >> infoGeoid1 >> infoGeoid2 >> sep >> sigmaZ >> unit;



}
