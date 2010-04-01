// TECSPMeasurement
/*!
	Class for a distance between a point and a spatial line
	
	Patterns:
  
	Copyright 2003, CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_ECSP_MEASUREMENT
#define SU_ECSP_MEASUREMENT

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
class	TECSPMeasurement : public TALineMeasurement{

public :



	/*!@name Constructors/Destructor */
	//@{
		/*! Default constructor */
		TECSPMeasurement();

		/*! Constructor 
		\param setupPtName the measurement's station's setup point's name
		\param targetname  the measurement's target point's name
		\param obsDist the observed distance as a TLength
		\param sigma the observed distance's precision as a TLength*/
		TECSPMeasurement(string targetName, TLength obsDist, TLength sigma);
	
		/*! Copy constructor */
		TECSPMeasurement(const TECSPMeasurement &source);

		/*! Destructor */
		~TECSPMeasurement();
	//@}

	/*!@Member functions */
	//@{
		/*! Copy assignment operator */
		TECSPMeasurement&	operator=(const TECSPMeasurement& source);
		//DANGER : shallow copy (see NetworkSurveyMeas)

		/*! return a string indicating this measurement is a TECSP measurement */
		virtual string				getMeasKind() const;

};
/*@}*/

#endif

