#include <TRGF93ZoneTransformation.h>

#include <TRefFrameInfo.h>

#include <assert.h>
#define  _USE_MATH_DEFINES
#include <math.h>
#include <TVNumericValue.h>

/////////////////////////////////////////////////////////


TRGF93ZoneTransformation::TRGF93ZoneTransformation(bool fromETRF93)
: fFromETRF93(fromETRF93)
{
}

TRGF93ZoneTransformation * TRGF93ZoneTransformation::clone() const
{
    return new TRGF93ZoneTransformation(*this);
}

TRGF93ZoneTransformation * TRGF93ZoneTransformation::inverse() const
{
    return new TRGF93ZoneTransformation(!fFromETRF93);
}

TAReferenceFrame * TRGF93ZoneTransformation::getSourceFrame() const
{
    return TRefFrameInfo::getReferenceFrame(
        fFromETRF93 ? TRefSystemFactory::kETRF93 : TRefSystemFactory::kFrenchRGF93Zone5);
}

TAReferenceFrame * TRGF93ZoneTransformation::getDestinationFrame() const
{
    return TRefFrameInfo::getReferenceFrame(
        fFromETRF93 ? TRefSystemFactory::kFrenchRGF93Zone5 : TRefSystemFactory::kETRF93);
}

bool TRGF93ZoneTransformation::transform(TPositionVector & pv) const
{
    if(fFromETRF93)
        return transformFromETRF93(pv);
    return transformToETRF93(pv);
}

//////////////////////////////////////////////////////


bool TRGF93ZoneTransformation::transformToETRF93(TPositionVector & pv) const
{
     //transform x y h
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

    const double X = position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
    const double Y = position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
    const double h = position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue();

    //CONSTANTS

    //Zone number
    int zoneNumber = 5;

    //Origine latitude
    double phi0 = (41 + zoneNumber);

    //Origine longitude
    double lambda0 = 3.0;

    //changed to radians
    double phi1 = (phi0-0.75)*(M_PI/180.0);
    double phi2 = (phi0+0.75)*(M_PI/180.0);

    phi0 = phi0 * M_PI / 180.0;
    lambda0 = lambda0 * M_PI / 180.0;

    //Constant X0 [m]
    double E0 = 1700000;
    //Constant Y0 [m]
    double N0 = (zoneNumber * 1000000) + 200000;

    //Parameters of the elipsoide GRS80 from Wikipedia
    double a = 6378137.0;
    double e2 =  0.006694380022903415749574948586289306212443890;
    double e = sqrt(e2);
    
    // Calculations
    double L0 = 0.5 * log((1+sin(phi0))/(1-sin(phi0))) - (e/2) * log((1+e*sin(phi0))/(1-e*sin(phi0)));
    double L1 = 0.5 * log((1+sin(phi1))/(1-sin(phi1))) - (e/2) * log((1+e*sin(phi1))/(1-e*sin(phi1)));
    double L2 = 0.5 * log((1+sin(phi2))/(1-sin(phi2))) - (e/2) * log((1+e*sin(phi2))/(1-e*sin(phi2)));

    double n = log((a/sqrt(1-e2*sin(phi2)*sin(phi2))*cos(phi2))/(a/sqrt(1-e2*sin(phi1)*sin(phi1))*cos(phi1))) /(L1 -L2);

    double C = (a/(sqrt(1-e2 * sin(phi1) * sin(phi1)))*cos(phi1))/n * exp(n*L1);

    double Xs = E0;
    double Ys = N0 + C * exp(-n*L0);


    double R = sqrt((X-Xs)*(X-Xs)+ (Y-Ys)*(Y-Ys));
    double gama = atan((X-Xs)/(Ys-Y)); 

    double lambda = lambda0 + (gama/n);

    double LL = (-1/n)*log(abs(R/C));


    double phi = 2*atan(exp(LL))-(M_PI_2);

    for (int i = 0; i != kMaxIter; i++)
    {
        double PHInew = 2 * atan(pow((1+e*sin(phi))/(1-e*sin(phi)),(e/2)) *exp(LL))-(M_PI_2);
        double delta = abs(phi - PHInew);
        phi = PHInew;

        if(delta<1e-10)
        break;
    }

    pv = TPositionVector(phi, lambda, h, TCoordSysFactory::kGeodetic);

    return true;

}
bool TRGF93ZoneTransformation::transformFromETRF93(TPositionVector & pv) const
{
    //transform phi lambda h
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

    const double phi = position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue();
    const double lambda = position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue();
    const double h = position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue();
    

    //CONSTANTS
    //Zone number
    int zoneNumber = 5;

    //Origine latitude
    double phi0 = (41 + zoneNumber);

    //Origine longitude
    double lambda0 = 3.0;

    //changed to radians
    double phi1 = (phi0-0.75)*(M_PI/180.0);
    double phi2 = (phi0+0.75)*(M_PI/180.0);

    phi0 = phi0 * M_PI / 180.0;
    lambda0 = lambda0 * M_PI / 180.0;

    //Constant X0 [m]
    double E0 = 1700000;
    //Constant Y0 [m]
    double N0 = (zoneNumber * 1000000) + 200000;

    //Parameters of the elipsoide GRS80 from Wikipedia
    double a = 6378137.0;
    double e2 =  0.006694380022903415749574948586289306212443890;
    double e = sqrt(e2);

    // Calculations
    double L =  0.5 * log((1+sin(phi))/(1-sin(phi)))   - (e/2) * log((1+e*sin(phi))/(1-e*sin(phi)));
    double L0 = 0.5 * log((1+sin(phi0))/(1-sin(phi0))) - (e/2) * log((1+e*sin(phi0))/(1-e*sin(phi0)));
    double L1 = 0.5 * log((1+sin(phi1))/(1-sin(phi1))) - (e/2) * log((1+e*sin(phi1))/(1-e*sin(phi1)));
    double L2 = 0.5 * log((1+sin(phi2))/(1-sin(phi2))) - (e/2) * log((1+e*sin(phi2))/(1-e*sin(phi2)));

    double n = log((a/sqrt(1-e2*sin(phi2)*sin(phi2))*cos(phi2))/(a/sqrt(1-e2*sin(phi1)*sin(phi1))*cos(phi1))) /(L1 -L2);

    double C = (a/(sqrt(1-e2 * sin(phi1) * sin(phi1)))*cos(phi1))/n * exp(n*L1);

    double Xs = E0;
    double Ys = N0 + C * exp(-n*L0);

    double R = C*exp(-n*L);
    double gama = n*(lambda-lambda0);

    double X = Xs + R*sin(gama);
    double Y = Ys - R*cos(gama);

    pv = TPositionVector(X, Y, h, TCoordSysFactory::k2DPlusH);

    return true;

}