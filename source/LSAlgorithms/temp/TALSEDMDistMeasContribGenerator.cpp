//TALSEDMDistMeasContribGenerator.cpp : implementation file
//Base Class for a LS contrib generator processing distance measurements


#include "TLSInputMatrices.h"

#include "TALSEDMDistMeasContribGenerator.h"

//////////////////////////
// no argument constructor
//////////////////////////
TALSEDMDistMeasContribGenerator::TALSEDMDistMeasContribGenerator(){

	fInputMatrices = NULL;
}

////////////////////////////////////////////////////////
// constructor setting the pointer to the input matrices
////////////////////////////////////////////////////////
TALSEDMDistMeasContribGenerator::TALSEDMDistMeasContribGenerator(TLSInputMatrices* lsim){

	fInputMatrices = lsim;
	fS0APrioriScaleFactor = fInputMatrices->getS0APrioriScaleFactor();
}

/////////////
// destructor
/////////////
TALSEDMDistMeasContribGenerator::~TALSEDMDistMeasContribGenerator(){

}


/////////////////////////////////////////
// sets the pointer to the input matrices
/////////////////////////////////////////
void TALSEDMDistMeasContribGenerator::setLSInputMatrices(TLSInputMatrices *im){

	fInputMatrices = im;
	fS0APrioriScaleFactor = fInputMatrices->getS0APrioriScaleFactor();
}

//////////////////////////////////////////////
// sets the pointer to the current EDM station
//////////////////////////////////////////////
void TALSEDMDistMeasContribGenerator::setCurrentEDMStation(TLSCalcWorkingStations::CalcEDMStIterator edmst){

	fCurrentStation = edmst;
}

///////////////////////////////////////////////
// sets the pointer to the current EDM dist ROM
///////////////////////////////////////////////
void TALSEDMDistMeasContribGenerator::setCurrentEDMDistROM(TLSCalcEDMStation::CalcEDMDistROMIterator edmdr){

	fCurrentDistROM = edmdr;
}