//TALSOffsetToTheoPlaneMeasContribGenerator.h : header file
//
//! Base Class for a LS contrib generator processing offset to theodolite plane measurements
//
//
// Copyright 2003, CERN, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////////////////////////



#ifndef SU_TALS_ECTH_MEASCONTGENERATOR
#define SU_TALS_ECTH_MEASCONTGENERATOR


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
class		TLSInputMatrices;
#include	"TLSCalcOffsetToTheoPlaneObservation.h"
#include	"TAObsContributionsGenerator.h"

//#include "UEOIndices.h"

////////////////////
// Class declaration
////////////////////
class TALSOffsetToTheoPlaneMeasContribGenerator : public TAObsContributionsGenerator{

public :

	//!Calculates the contributions of a offset to theodolite plane meas. and puts them in the matrices
	/*!@param iterDM an iterator pointing to the hor. dist. to be processed*/
	virtual	bool	processOffsetToTheoPlaneObs(LSOffsetToTheoPlaneConstIter iterOffset, TLSInputMatrices& matrices) = 0;
	
	/*! Calculates the local contribution
	@param xSt contribution for the x-coordinate of the stationed point
	@param ySt contribution for the y-coordinate of the stationed point
	@param zSt contribution for the z-coordinate of the stationed point
	@param xTheo contribution for the x-coordinate of the target point
	@param yTheo contribution for the y-coordinate of the target point
	@param zTheo contribution for the z-coordinate of the target point
	@param v contribution for the v0 of the target (theodolite) point*/
	virtual void calculateLocalOffsetToTheoPlaneContrib(LSOffsetToTheoPlaneConstIter iterOffset,
					double& xSt, double& ySt, double& zSt,
					double& xTheo, double& yTheo, double& zTheo,
					double& v);

	//!Calculates the theorical value of a offset to theodolite plane measurement
	/*!\param offsetIt an iterator pointing to the observation to be simulated*/
	virtual	TLength	getOffsetToTheoPlaneCalcValue(LSOffsetToTheoPlaneConstIter offsetIt) const;

	//!Destructor
	virtual ~TALSOffsetToTheoPlaneMeasContribGenerator();

protected:

	//!Default constructor
	TALSOffsetToTheoPlaneMeasContribGenerator();
	
};
#endif

