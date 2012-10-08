//
// TAStationListener.cpp : implementation file
// abstract base class defining the default implementations 
// of the TVStationListener interface's methods

#include "TAStationListener.h"

///////////////////////////
// no arguments constructor
///////////////////////////
TAStationListener::TAStationListener(){

}

/////////////
// destructor
/////////////
TAStationListener::~TAStationListener(){

}
//////////////////////////////////////////////
// default response to a station disactivation
//////////////////////////////////////////////
void TAStationListener::stationDisactivated(){

	return;
}

/////////////////////////////////////////////
// default response to a station reactivation
/////////////////////////////////////////////
void TAStationListener::stationActivated(){

	return;
}

///////////////////////////////////////
// default response to a station update
///////////////////////////////////////
void TAStationListener::stationUpdated(EUpdateMessage umess){

	switch (umess){

	case kInstNumberChange:
		break;

	case kSetupChange:
		break;

	default:
		break;
	}
}