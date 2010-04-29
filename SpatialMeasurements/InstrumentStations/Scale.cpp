// 
// Scale.cpp : implementation file
//

#include "Scale.h"


Scale::Scale(const string& id, const TLength* const spDSigma, const TLength* ppmE,
			 const TDistConstants* dc, const TLength* sdc, const TLength* sic, const TLength* to, const TLength* sto, int dcun)
	: TAFreeInstrument(id, sic)
{	
	distanceCorrection = dc;
	distanceCorrectionSigma = sdc;
	distanceCorrectionUnknownNumber = dcun;

	spatialDistanceSigma = spDSigma;
	ppm = ppmE;
	targetOffset = to;
	targetOffsetSigma = sto;
}

Scale::~Scale()
{
	delete distanceCorrection;
	delete distanceCorrectionSigma;
	delete spatialDistanceSigma;
	delete ppm;
	delete targetOffset;
	delete targetOffsetSigma;
}
