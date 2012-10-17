// TECVEMeasurement
/*!
	Class for a horizontal distance between a point and a spatial line
	
	Patterns:
  
	Copyright 2003, CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_ECVE_MEASUREMENT
#define SU_ECVE_MEASUREMENT

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



/////////////////////////////////////////////////////
// Forward declarations
//
#include "TALineMeasurement.h"
/////////////////////////////////////////////////////

/*! \ingroup spatialmeasurements
	@{*/ 

//! Class for a horizontal distance measurement
class	TECVEMeasurement : public TALineMeasurement{

public :



	/*!@name Constructors/Destructor */
	//@{
		/*! Default constructor */
		TECVEMeasurement();

		/*! Constructor 
		\param setupPtName the measurement's station's setup point's name
		\param targetname  the measurement's target point's name
		\param obsDist the observed distance as a TLength
		\param sigma the observed distance's precision as a TLength*/
		TECVEMeasurement(string targetName, TLength obsDist, TLength sigma);
	
		/*! Copy constructor */
		TECVEMeasurement(const TECVEMeasurement &source);

		/*! Destructor */
		~TECVEMeasurement();
	//@}

	/*!@Member functions */
	//@{
		/*! Copy assignment operator */
		TECVEMeasurement&	operator=(const TECVEMeasurement& source);
		//DANGER : shallow copy (see NetworkSurveyMeas)

		/*! return a string indicating this measurement is a TECVE measurement */
		virtual string				getMeasKind() const;

};
/*@}*/

#endif

