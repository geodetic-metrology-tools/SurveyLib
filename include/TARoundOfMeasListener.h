//
// TARoundOfMeasListener.h : header file
///////////////////////////////////////////////////////////

#ifndef SU_TAROMLISTENER
#define SU_TAROMLISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//include files
#include "TVRoundOfMeasListener.h"

//! Class providing a default implementation for the methods of the VRoundOfMeasListener interface
class TARoundOfMeasListener : public TVRoundOfMeasListener{

public:

	virtual			~TARoundOfMeasListener();

	virtual void	roundOfMeasDisactivated();
	virtual void	roundOfMeasActivated();
	
	virtual void	roundOfMeasUpdated(EUpdateMessage);

protected:

	TARoundOfMeasListener();
};
#endif 