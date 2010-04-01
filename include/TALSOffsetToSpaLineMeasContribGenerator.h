//TALSOffsetToSpaLineMeasContribGenerator.h : header file
//
//! Base Class for a LS contrib generator processing offset to spatial line measurements
//
//
// Copyright 2003, CERN, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////////////////////////



#ifndef SU_TALS_ECSP_MEASCONTGENERATOR
#define SU_TALS_ECSP_MEASCONTGENERATOR


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
class		TLSInputMatrices;
#include	"TLSCalcOffsetToSpaLineObservation.h"
#include	"TAObsContributionsGenerator.h"

//#include "UEOIndices.h"

////////////////////
// Class declaration
////////////////////
class TALSOffsetToSpaLineMeasContribGenerator : public TAObsContributionsGenerator{

public :

	//!Calculates the contributions of a offset to spatial line meas. and puts them in the matrices
	/*!@param iterDM an iterator pointing to the hor. dist. to be processed*/
	virtual	bool	processOffsetToSpaLineObs(LSOffsetToSpaLineConstIter iterOffset, TLSInputMatrices& matrices) = 0;
	
	/*! Calculates the local contribution
	@param xSt contribution for the x-coordinate of the stationed point
	@param ySt contribution for the y-coordinate of the stationed point
	@param zSt contribution for the z-coordinate of the stationed point
	@param xFTg contribution for the x-coordinate of the first target point
	@param yFTg contribution for the y-coordinate of the first target point
	@param zFTg contribution for the z-coordinate of the first target point
	@param xSTg contribution for the x-coordinate of the second target point
	@param ySTg contribution for the y-coordinate of the second target point
	@param zSTg contribution for the z-coordinate of the second target point*/
	virtual void calculateLocalOffsetToSpaLineContrib(LSOffsetToSpaLineConstIter iterOffset,
					double& xSt, double& ySt, double& zSt,
					double& xFTg, double& yFTg, double& zFTg,
					double& xSTg, double& ySTg, double& zSTg);

	//!Calculates the theorical value of a offset to spatial line measurement
	/*!\param offsetIt an iterator pointing to the observation to be simulated*/
	virtual	TLength	getOffsetToSpaLineCalcValue(LSOffsetToSpaLineConstIter offsetIt) const;

	//!Destructor
	virtual ~TALSOffsetToSpaLineMeasContribGenerator();

protected:

	//!Default constructor
	TALSOffsetToSpaLineMeasContribGenerator();
	
};
#endif

