//
// TAMeasurementListener : împlementation file
// abstract base class providing a default implementation 
// of the methods of the TVMeasurementListener interface
////////////////////////////////////////////////////////

#include "TAMeasurementListener.h"

///////////////////////////
// no arguments constructor
///////////////////////////
TAMeasurementListener::TAMeasurementListener(){

}

/////////////
// destructor
/////////////
TAMeasurementListener::~TAMeasurementListener(){

}

///////////////////////////////////////////
// default response to a meas disactivation
///////////////////////////////////////////
void TAMeasurementListener::measurementDisactivated(){

}

//////////////////////////////////////////
// default response to a meas reactivation
//////////////////////////////////////////
void TAMeasurementListener::measurementActivated(){

}

///////////////////////////////////////////
// default response to a measurement update
///////////////////////////////////////////
void TAMeasurementListener::measurementUpdated(EUpdateMessage umess){

	switch (umess){

	case  kTargetChange:
		break;

	case kOwnerChange:
		break;

	default:
		break;
	}
}




