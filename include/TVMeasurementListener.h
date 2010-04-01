//
// TVMeasurementListener.h : header file
//////////////////////////////////////////////////////////////////////////

#ifndef SU_TVMEASLISTENER
#define SU_TVMEASLISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//! Pure abstract base class : defines an interface each object listening to a measurement will implement
class TVMeasurementListener{

public:

	virtual			~TVMeasurementListener();

	//! Enumeration of the update messages (other than active/inactive) the listener can receive
	enum			EUpdateMessage{kTargetChange, kOwnerChange};

	//! Reacts to the disactivation of a listened to measurement
	virtual void	measurementDisactivated() = 0;
	//! Reacts to the activation of a listened to measurement
	virtual void	measurementActivated() = 0;
	//! Reacts to an update of a listened to measurement
	/*@param um an update message part of the class's EUpdateMessage enumeration*/
	virtual void	measurementUpdated(EUpdateMessage um) = 0;
};
#endif
