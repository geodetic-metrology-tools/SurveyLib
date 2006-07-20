//
// TAStationListener.h : header file


#ifndef SU_TASTATIONLISTENER
#define SU_TASTATIONLISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//include files
#include "TVStationListener.h"

//! Abstract base class defining the default implementations of the TVStationListener interface's methods
class TAStationListener : public TVStationListener{

public:

	virtual			~TAStationListener();

	virtual void	stationDisactivated();
	virtual void	stationActivated();
	
	virtual void	stationUpdated(EUpdateMessage);

protected:

	TAStationListener();
};
#endif