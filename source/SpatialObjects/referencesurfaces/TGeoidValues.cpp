// TGeoidValues.cpp
//
// Class for geoidal values as defined for survey purposes
//
// Copyright 1999,2000, Mark Jones, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////


//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"

// other forward declarations

#include	"TGeoidValues.h"
#include	"TAngle.h"
////////////////////////////////////////////////////////////////



//ClassImp(TGeoidValues)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TGeoidValues::TGeoidValues()
{	// default constructor 
}


TGeoidValues::TGeoidValues(GeoidValue fNValue, GeoidValue fXiValue, GeoidValue fEtaValue, GeoidValue fDAlphaValue)
{
	setN(fNValue);
	setXi(fXiValue);
	setEta(fEtaValue);
	setDAlpha(fDAlphaValue);
}


TGeoidValues::TGeoidValues(const TGeoidValues& tgv)
{
	fNValue=tgv.fNValue;
	fXiValue=tgv.fXiValue;
	fEtaValue=tgv.fEtaValue;
	fDAlphaValue=tgv.fDAlphaValue;
}

TGeoidValues::~TGeoidValues()
{
}

//////////////////////////////////////////////////////////////////////
// Operator =
//////////////////////////////////////////////////////////////////////
TGeoidValues& TGeoidValues::operator=(const TGeoidValues& tgv)
{
		if (this != &tgv)
	{
		fNValue=tgv.fNValue;
		fXiValue=tgv.fXiValue;
		fEtaValue=tgv.fEtaValue;
		fDAlphaValue=tgv.fDAlphaValue;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////


GeoidValue	TGeoidValues::getXiAzimuth(TAngle azimuth)
{//
	double  az = azimuth.getRadiansValue();
	GeoidValue	XiAzimuthValue;
	XiAzimuthValue = fXiValue*cos(az) + fEtaValue*sin(az);
	return XiAzimuthValue;
}


GeoidValue	TGeoidValues::getEtaAzimuth(TAngle azimuth)
{//
	double  az = azimuth.getRadiansValue();
	GeoidValue	EtaAzimuthValue;
	EtaAzimuthValue = fEtaValue*cos(az) - fXiValue*sin(az);
	return EtaAzimuthValue;
}