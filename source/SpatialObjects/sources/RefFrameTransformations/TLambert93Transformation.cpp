#include <TLambert93Transformation.h>

#include <TRefFrameInfo.h>

#include <assert.h>
#define  _USE_MATH_DEFINES
#include <math.h>
#include <array>
#include <string>
#include <filesystem>
#include <iostream>
#include <sstream>

#ifdef CIRCE_EXEC_DIR
#	define CIRCE_DIR CIRCE_EXEC_DIR
#endif 

/////////////////////////////////////////////////////////

// Anonymous namespace for local constants
namespace
{
	//CONSTANTS

    //Origine latitude
    const double phi0 = (46+30/60.0) * (M_PI/180.0);

    //Origine longitude
    const double lambda0 = 3.0 *(M_PI/180.0);

    //changed to radians
    const double phi1 = 44 *(M_PI/180.0);
    const double phi2 = 49 *(M_PI/180.0);

    //Constant X0 [m]
    const double X0 = 700000;
    //Constant Y0 [m]
    const double Y0 = 6600000;

    //Parameters of the elipsoide GRS80 from Wikipedia
    const double a = 6378137.0;
    const double e2 =  0.006694380022903415749574948586289306212443890;
    const double e = sqrt(e2);
    //
    //// Calculations

	const double L0 = log(tan(M_PI/4 + phi0/2.0) * pow(  ( (1-e * sin(phi0))/(1+e * sin(phi0)) ),(e/2)  ));
	const double L1 = log(tan(M_PI/4 + phi1/2.0) * pow(  ( (1-e * sin(phi1))/(1+e * sin(phi1)) ),(e/2)  ));
	const double L2 = log(tan(M_PI/4 + phi2/2.0) * pow(  ( (1-e * sin(phi2))/(1+e * sin(phi2)) ),(e/2)  ));

	const double N1 = a/sqrt(1 - pow( (e * sin(phi1)), 2) );
	const double N2 = a/sqrt(1 - pow( (e * sin(phi2)), 2) );

	const double lambda_c = lambda0;

	const double n = log(N2 * cos(phi2)/(N1 * cos(phi1)) )/(L1 - L2);

	const double C = N1 * cos(phi1)/n * exp(n * L1);

	const double XS = X0;
	const double YS = Y0 + C * exp(-n * L0);

}


TLambert93Transformation::TLambert93Transformation(bool fromRGF93, bool ellipsHeight)
	: fFromRGF93(fromRGF93), fEllipsHeight(ellipsHeight)
{
	/*
	std::cout << "####" << std::endl;
	std::cout << "phi0:" << phi0 << std::endl;
    std::cout << "e:" << e << std::endl;
	std::cout << "L0:" << L0 << std::endl;
	std::cout << "L1:" << L1 << std::endl;
	std::cout << "L2:" << L2 << std::endl;
	std::cout << "N1:" << N1 << std::endl;
	std::cout << "N2:" << N2 << std::endl;
	std::cout << "lambda_c:" << lambda_c << std::endl;
	std::cout << "n:" << n << std::endl;
	std::cout << "C:" << C << std::endl;
	std::cout << "XS:" << XS << std::endl;
	std::cout << "YS:" << YS << std::endl;
	*/
}

TLambert93Transformation * TLambert93Transformation::clone() const
{
    return new TLambert93Transformation(*this);
}

TLambert93Transformation * TLambert93Transformation::inverse() const
{
    return new TLambert93Transformation(!fFromRGF93, fEllipsHeight);
}

TAReferenceFrame * TLambert93Transformation::getSourceFrame() const
{
	if (fFromRGF93)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93);
	}
	else if (fEllipsHeight)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_eh);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_raf);
	}   
}

TAReferenceFrame * TLambert93Transformation::getDestinationFrame() const
{
	if (!fFromRGF93)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93);
	}
	else if (fEllipsHeight)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_eh);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_raf);
	}
}

bool TLambert93Transformation::transform(TPositionVector & pv) const
{
    if(fFromRGF93)
        return transformFromRGF93(pv);
    return transformToRGF93(pv);
}

//////////////////////////////////////////////////////


bool TLambert93Transformation::transformToRGF93(TPositionVector & pv) const
{
    //transform x y h
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

    const double X = position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
    const double Y = position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
    double h = position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue();

	if (position.getRefFrame() == TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_raf))
	{
		// We call Circé developped by the french IGN to convert altitude into ellipsoidal height
		circeTransfoRafToH(X, Y, h);
	}

	double R = sqrt((X - XS)*(X - XS)+ (Y - YS)*(Y - YS));
    double gamma = atan((X - XS)/(YS - Y));

	double lambda = lambda_c + (gamma/n);
	double L = -1/n * log(abs(R/C));


	double phi_0 = 2 * atan (exp(L)) - TAngle::piBy2().getRadiansValue();
	double phi = phi_0;

	for (int i = 0; i != kMaxIter; i++)
	{
		double phi_i = 2 * atan(  pow( (  (1 + e * sin(phi))/(1 - e * sin(phi))  ),(e/2)) * exp(L))- M_PI/2;
    
		double delta = abs(phi - phi_i);
		phi = phi_i;    
    
		if(delta<1e-11)
			break;

	}

    TPositionVector tmp = TPositionVector(phi, lambda, h, TCoordSysFactory::kGeodetic);
	TSpatialPosition outpos(getDestinationFrame());
	if(!outpos.setCoordinates(tmp))
        return false;
	// Project to Carthesian
	pv = outpos.getCoordinates(TCoordSysFactory::k3DCartesian);
	
    return true;

}
bool TLambert93Transformation::transformFromRGF93(TPositionVector & pv) const
{
    //transform phi lambda h
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

    const double phi = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue();
    const double lambda = position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue();
    double h = position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue();

	double L = log(tan(M_PI/4 + phi/2) * pow(  ( (1-e * sin(phi))/(1+e * sin(phi)) ),(e/2)  ));

	double X = XS + C*exp(-n*L)*sin(n*(lambda-lambda_c));
	double Y = YS - C*exp(-n*L)*cos(n*(lambda-lambda_c));

	TPositionVector tmp = TPositionVector(X, Y, h, TCoordSysFactory::k2DPlusH);
	TSpatialPosition outpos(getDestinationFrame());
	if (!outpos.setCoordinates(tmp))
	{
		return false;
	}
	else if (outpos.getRefFrame() == TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_raf))
	{
		// We call Circé developped by the french IGN to convert ellipsoidal height into altitude
		circeTransfoHToRaf(X, Y, h);
	}


    pv = TPositionVector(X, Y, h, TCoordSysFactory::k2DPlusH);

    return true;

}

void TLambert93Transformation::circeTransfoRafToH(const double &X, const double &Y, double &h) const
{
	std::string circePath = CIRCE_DIR;
	std::string circeOption = "--sourceCRS=RGF93LAMB93.IGN69 "
							  "--sourceFormat=ENV.METERS.RADIANS "
							  "--targetCRS=RGF93LAMB93. "
							  "--targetFormat=ENHCS.METERS.DEGREES "
							  "--displayPrecision=0.00001 --plainDMS --gridLoading=BINARY";

	std::string cmdString = "\"" + circePath + "/circeFR.exe\"" + " --metadataFile=" + circePath + "/Data/DataFRnew.txt " + circeOption + " " + std::to_string(X) + " "
		+ std::to_string(Y) + " " + std::to_string(h);

	const char *cmd = cmdString.c_str();
	std::string result = execCirce(cmd);
	readCirceResult(result, h);
}

void TLambert93Transformation::circeTransfoHToRaf(const double &X, const double &Y, double &h) const
{
	std::string circePath = CIRCE_DIR;
	std::string circeOption = "--sourceCRS=RGF93LAMB93. "
							  "--sourceFormat=ENH.METERS.RADIANS "
							  "--targetCRS=RGF93LAMB93.IGN69 "
							  "--targetFormat=ENVCS.METERS.DEGREES "
							  "--displayPrecision=0.00001 --plainDMS --gridLoading=BINARY";

	std::string cmdString = "\"" + circePath + "/circeFR.exe\"" + " --metadataFile=" + circePath + "/Data/DataFRnew.txt " + circeOption + " " + std::to_string(X) + " "
		+ std::to_string(Y) + " " + std::to_string(h);

	const char *cmd = cmdString.c_str();
	std::string result = execCirce(cmd);
	readCirceResult(result, h);
}

std::string TLambert93Transformation::execCirce(const char *cmd) const
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

void TLambert93Transformation::readCirceResult(std::string result, double &h) const
{
	std::stringstream ss(result);
	double x, y, conv, scale, sigmaZ;
	std::string infoGeoid1, infoGeoid2, sep, unit;

	ss >> x >> y >> h >> conv >> scale >> infoGeoid1 >> infoGeoid2 >> sep >> sigmaZ >> unit;
}


// TLambert93Transformation& TLambert93Transformation::operator=(const TLambert93Transformation& fLambert)
// {
// 	*this = fLambert;
// 	return *this;
// }
