// TEcartTheodoliteMeasurement
/*!
	Class for a horizontal distance between a point and a theodolite's
	sighting line
	
	Patterns:
  
	Copyright 2003, CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_ECTH_MEASUREMENT
#define SU_ECTH_MEASUREMENT

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



/////////////////////////////////////////////////////
// Forward declarations
//
#include "TAPlaneMeasurement.h"
/////////////////////////////////////////////////////

/*! \ingroup spatialmeasurements
	@{*/ 

//! Class for a horizontal distance measurement
class	TEcartTheodoliteMeasurement : public TAPlaneMeasurement{

public :



	/*!@name Constructors/Destructor */
	//@{
		/*! Default constructor */
		TEcartTheodoliteMeasurement();

		/*! Constructor 
		\param setupPtName the measurement's station's setup point's name
		\param targetname  the measurement's target point's name
		\param obsDist the observed distance as a TLength
		\param sigma the observed distance's precision as a TLength*/
		TEcartTheodoliteMeasurement(string targetName, TLength obsDist, TLength sigma);
	
		/*! Copy constructor */
		TEcartTheodoliteMeasurement(const TEcartTheodoliteMeasurement &source);

		/*! Destructor */
		~TEcartTheodoliteMeasurement();
	//@}

	/*!@Member functions */
	//@{
		/*! Copy assignment operator */
		TEcartTheodoliteMeasurement&	operator=(const TEcartTheodoliteMeasurement& source);
		//DANGER : shallow copy (see NetworkSurveyMeas)

		/*! return a string indicating this measurement is a TECTH measurement */
		virtual string				getMeasKind() const;

};
/*@}*/

#endif

