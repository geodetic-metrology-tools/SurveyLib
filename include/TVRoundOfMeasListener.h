//
// TVRoundOfMeasListener.h : header file
//////////////////////////////////////////////////////////////////////////

#ifndef SU_TVROMLISTENER
#define SU_TVROMLISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//! Pure abstract base class : defines an interface each object listening to round of measurements will implement
class TVRoundOfMeasListener{

public:

	virtual			~TVRoundOfMeasListener() = 0;
	//! Enumeration of the update messages (other than active/inactive) the listener can receive
	enum			EUpdateMessage{kSeriesChange, kReferenceChange, kCountsChange, kEnoughTotalEqns};

	//! Reacts to the disactivation of a listened to round of measurements
	virtual void	roundOfMeasDisactivated() = 0;
	//! Reacts to the activation of a listened to round of measurements
	virtual void	roundOfMeasActivated() = 0;
	//! Reacts to an update of a listened to round of measurements
	/*@param um an update message part of the class's EUpdateMessage enumeration*/
	virtual void	roundOfMeasUpdated(EUpdateMessage um) = 0;
};
#endif 
