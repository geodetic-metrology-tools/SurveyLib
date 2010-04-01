// TECHOMeasurement
/*!
	Class for a horizontal distance between a point and a line
	
	Patterns:
  
	Copyright 2003, CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_ECHO_MEASUREMENT
#define SU_ECHO_MEASUREMENT

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
class	TECHOMeasurement : public TAPlaneMeasurement{

public :



	/*!@name Constructors/Destructor */
	//@{
		/*! Default constructor */
		TECHOMeasurement();

		/*! Constructor 
		\param setupPtName the measurement's station's setup point's name
		\param targetname  the measurement's target point's name
		\param obsDist the observed distance as a TLength
		\param sigma the observed distance's precision as a TLength*/
		TECHOMeasurement(string targetName, TLength obsDist, TLength sigma);
	
		/*! Copy constructor */
		TECHOMeasurement(const TECHOMeasurement &source);

		/*! Destructor */
		~TECHOMeasurement();
	//@}

	/*!@Member functions */
	//@{
		/*! Copy assignment operator */
		TECHOMeasurement&	operator=(const TECHOMeasurement& source);
		//DANGER : shallow copy (see NetworkSurveyMeas)

		/*! return a string indicating this measurement is a TECHO measurement */
		virtual string				getMeasKind() const;

};
/*@}*/

#endif

