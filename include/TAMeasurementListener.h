//
// TAMeasurementListener : header file
////////////////////////////////////////////////////////

#ifndef SU_TAMEASLISTENER
#define SU_TAMEASLISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//include files
#include "TVMeasurementListener.h"

//! Abstract base class providing a default implementation of the methods of the TVMeasurementListener interface
class TAMeasurementListener : public TVMeasurementListener{

public:

	virtual			~TAMeasurementListener();

	virtual void	measurementDisactivated();
	virtual void	measurementActivated();
	
	virtual void	measurementUpdated(EUpdateMessage);	

protected:

	TAMeasurementListener();
};
#endif
