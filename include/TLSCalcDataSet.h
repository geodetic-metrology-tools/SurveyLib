//TLSCalcDataSet.h : header file

#ifndef SU_TLS_CALC_DATA_SET
#define SU_TLS_CALC_DATA_SET


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include "TLSCalcWorkingPoints.h"
#include "TLSCalcWorkingStations.h"
#include "TLSCalcWorkingConstants.h"
#include "TLSCalcWorkingTargetObjects.h"
#include "TLSCalcWorkingConstraints.h"
class TLGCDataSet;
#include "UEOIndices.h"

//! Class for a data set holding all the LS calc data
/*! Counterpart of the LGCDataSet*/
class TLSCalcDataSet{

public:

	/*!@name Constructors / Destructor*/
	//@{
	//!Default constructor
	TLSCalcDataSet();
	//!Constructor
	/*!@param lgcDS a pointer to the LGCDataSet counterpart*/
	explicit TLSCalcDataSet(const TLGCDataSet& lgcDS);
	//!Destructor
	~TLSCalcDataSet();
	//@}

	/*!@name Acess methods*/
	//@{
	//!Gets the working stations
	/*!@return a pointer to the TLSCalcWorkingStations object*/
	virtual TLSCalcWorkingStations*			getWorkingStations() const;
	//!Gets the working points
	/*!@return a pointer to the TLSCalcWorkingPoints object*/
	virtual TLSCalcWorkingPoints*			getWorkingPoints() const;
	//!Gets the working constants
	/*!@return a pointer to the TLSCalcWorkingConstants object*/
	virtual TLSCalcWorkingConstants*			getWorkingConstants() const;
	//!Gets the working target objects
	/*!@return a pointer to the TLSCalcWorkingTargetObjects object*/
	virtual TLSCalcWorkingTargetObjects*	getWorkingTargetObjects() const;
	//!Gets the working constraints
	/*!@return a pointer to the TLSCalcWorkingConstraints object*/
	virtual TLSCalcWorkingConstraints*		getWorkingConstraints() const;

	//!Gets the current number of unknowns, equations and observations
	/*!@return a UEOIndices structure holding the three numbers*/
	virtual UEOIndices						getDimensions() const;
	//@}

	//!Attributes indices to whatever needs some for the calculation
	virtual void							setIndices();

	//!Prepares the elements of the LSCalcDataSet for a further iteration of the least squares calculation
	virtual void							prepareNextIteration();

	//!Prepares the elements of the LSCalcDataSet for an additional simulation
	virtual void							prepareNextSimulation();


private:

	TLSCalcWorkingPoints*			fWorkingPoints;
	TLSCalcWorkingStations*			fWorkingStations;
	TLSCalcWorkingConstants*		fWorkingConstants;
	TLSCalcWorkingTargetObjects*	fWorkingTargetObjects;
	TLSCalcWorkingConstraints*		fWorkingConstraints;

	UEOIndices				fUEOIndices;
};
#endif