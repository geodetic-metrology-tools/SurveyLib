//TALSZenithDistMeasContribGenerator.cpp : implementation file
//Base Class for a LS contrib generator processing zenithal distance measurements


#include "TLSInputMatrices.h"

#include "TALSZenithDistMeasContribGenerator.h"

//////////////////////
// default constructor
//////////////////////
TALSZenithDistMeasContribGenerator::TALSZenithDistMeasContribGenerator(){

	fInputMatrices = NULL;
}

//////////////
// constructor
//////////////
TALSZenithDistMeasContribGenerator::TALSZenithDistMeasContribGenerator(TLSInputMatrices* lsim){

	fInputMatrices = lsim;
	fS0APrioriScaleFactor = fInputMatrices->getS0APrioriScaleFactor();
}

/////////////
// destructor
/////////////
TALSZenithDistMeasContribGenerator::~TALSZenithDistMeasContribGenerator(){

}


/////////////////////////////////////////
// sets the pointer to the input matrices
/////////////////////////////////////////
void TALSZenithDistMeasContribGenerator::setLSInputMatrices(TLSInputMatrices *im){

	fInputMatrices = im;
	fS0APrioriScaleFactor = fInputMatrices->getS0APrioriScaleFactor();
}

////////////////////////////////////////////////
// sets the pointer to the current theod station
////////////////////////////////////////////////
void TALSZenithDistMeasContribGenerator::setCurrentTheodStation(TLSCalcWorkingStations::CalcTheodStIterator tst){

	fCurrentStation = tst;
}

////////////////////////////////////////////////
// sets the pointer to the current hor angle ROM
////////////////////////////////////////////////
void TALSZenithDistMeasContribGenerator::setCurrentZenithDistROM(TLSCalcTheodoliteStation::CalcZenithDistROMIterator zdr){

	fCurrentZDistROM = zdr;
}