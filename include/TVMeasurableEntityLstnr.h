//
// TVMeasurableEntityListnr.h : header file
/*! 
pure Abstract Base Class : defines a common interface for measurable entity listeners

Patterns:

Copyright 1999,2000, CERN, EST/SU. All rights reserved.

*/

#ifndef SU_MEAS_ENT_LISTNR
#define SU_MEAS_ENT_LISTNR

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////
// forward declarations and includes
/////

/*!\ingroup spatialobjects
	@{*/

//! pure Abstract Base Class 
class TVMeasurableEntityLstnr{

public:

	virtual			~TVMeasurableEntityLstnr();
	//! Enumeration of the update messages (other than active/inactive) the listener can receive
	enum			EUpdateMessage{kPointChange, kNeededEqChange, kEqCountChange};
	//! Reacts to the disactivation of a listened to measurable entity
	virtual void	measEntityDisactivated() = 0;
	//! Reacts to the activation of a listened to measurable entity
	virtual void	measEntityActivated() = 0;
	//! Reacts to an update of a listened to measurable entity
	/*@param um an update message part of the class's EUpdateMessage enumeration*/
	virtual void	measEntityUpdated(EUpdateMessage um) = 0;
};
/*@}*/
#endif

