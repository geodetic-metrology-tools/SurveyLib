//
// TVStationListener.h : header file
//////////////////////////////////////////////////////////////////////////

#ifndef SU_TVSTLISTENER
#define SU_TVSTLISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//! Pure abstract base class : defines an interface each object listening to an instrument station implements
class TVStationListener{

public:

	virtual			~TVStationListener();

	//! Enumeration of the update messages (other than active/inactive) the listener can receive
	enum			EUpdateMessage{kInstNumberChange, kSetupChange, kCountsChange, kEnoughTotalEqns};

	//! Reacts to the disactivation of a listened to station
	virtual void	stationDisactivated() = 0;
	//! Reacts to the activation of a listened to station
	virtual void	stationActivated() = 0;
	//! Reacts to an update of a listened to station
	/*!@param um an update message part of the class's EUpdateMessage enumeration*/
	virtual void	stationUpdated(EUpdateMessage um) = 0;
};
#endif


