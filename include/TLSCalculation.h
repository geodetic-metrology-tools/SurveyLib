

#ifndef SU_LS_CALCULATION
#define SU_LS_CALCULATION

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
//
class TALSComputer;
class TLSResultsMatrices;

#include "TLGCDataSet.h"
#include "LSCalcDataSet.h"
#include "ObservationSet.h"
#include "TLSInputMatricesFiller.h"
#include "TLSResultsMatricesExtractor.h"
#include "TLGCCalcparams.h"


//!Class managing the ls calculation from input matrices preparation to the final results extraction*/
class TLSCalculation{ 

public:

	/*!@name Constructors / Destructor*/
	//@{
	/*!Default Constructor*/
	TLSCalculation();
	/*! Constructor
	\param calcParams Calculation parameters used to compute a solution */
	explicit TLSCalculation(const TLGCCalcParams& calcParams);
	//!Destructor
	virtual ~TLSCalculation();
	//@}

	
	/*! Computes the solution of the unknown survey network.
	Sends the relevant messages from the filling of the input matrices to extraction of the results.
	Runs additional iterations if necessary provided the maximum number of iterations isn't exceeded
	@return a true boolean if a solution was found*/
	virtual bool					computeSolution(const ObservationSet& obsSet, LSCalcDataSet& dataSet);


	/*! Computes the solution with simulated value for the observations.
	@return a true boolean if a solution was found*/
	virtual bool					computeSimulatedSolution(const ObservationSet& obsSet, LSCalcDataSet& dataSet);

	/*! Computes the solution for a free survey network.
	\return a true boolean if a solution was found*/
	virtual bool					computeFreeSolution(const ObservationSet& obsSet, LSCalcDataSet& dataSet);

	/*!@return the error*/
	virtual string	getError() const;

	/*!turn to true the boolean indicating that a geodetic system is used*/
	virtual void  useGeodSys() {fGeodSys = true;}

	

protected:

private:
	
	
	TLSResultsMatrices*				fResultsMatrices; /*!< pointer to the results matrices */ 
	int								fMaxIterations; /*!< maximum of iterations that can be carried out */
	double							fConvCriteria; /*!< convergence criteria that has to be exceeded to stop the iterative process */
	int								fNumberOfMadeIterations; /*!< indicates how many iteration have been carried out */
	string							fError; /*!< error from the calculation */
	
	TLGCCalcParams					fCalcParams;

	bool							fGeodSys; /*!< boolean indicating if the used coordinate system is geodetic or not */
};
#endif
