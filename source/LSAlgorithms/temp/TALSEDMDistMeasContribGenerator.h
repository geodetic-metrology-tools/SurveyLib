//VLSDistMeasContribGenerator.h : header file
//Base Class for a LS contrib generator processing distance measurements



#ifndef SU_VLSEDMDISTMEASCONTGENERATOR
#define SU_VLSEDMDISTMEASCONTGENERATOR


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
class TLSInputMatrices;
#include "TLSCalcWorkingStations.h"
#include "TLSCalcEDMStation.h"
#include "TLSCalcEDMDistROM.h"
#include "TAObsContributionsGenerator.h"

#include "UEOIndices.h"
////////////////////
// Class declaration
////////////////////
class TALSEDMDistMeasContribGenerator : public TAObsContributionsGenerator{

public :


	virtual void	setLSInputMatrices(TLSInputMatrices *);

	virtual void	setCurrentEDMStation(TLSCalcWorkingStations::CalcEDMStIterator);
	virtual void	setCurrentEDMDistROM(TLSCalcEDMStation::CalcEDMDistROMIterator);

	virtual	void	processEDMDistMeas(TLSCalcEDMDistROM::CalcEDMDistIterator) = 0;

	virtual ~TALSEDMDistMeasContribGenerator();

protected:

	TALSEDMDistMeasContribGenerator();
	explicit TALSEDMDistMeasContribGenerator(TLSInputMatrices*);

	TLSInputMatrices*							fInputMatrices;
	TLSCalcWorkingStations::CalcEDMStIterator	fCurrentStation;
	TLSCalcEDMStation::CalcEDMDistROMIterator	fCurrentDistROM;

	double										fS0APrioriScaleFactor;

	
};
#endif