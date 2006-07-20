//
// TARoundOfMeasListener.cpp : implementation file
// Class providing a default implementation for the methods 
// of the VRoundOfMeasListener interface
///////////////////////////////////////////////////////////

#include "TARoundOfMeasListener.h"

///////////////////////////
// no arguments constructor
///////////////////////////
TARoundOfMeasListener::TARoundOfMeasListener(){

}

////////////
//destructor
////////////
TARoundOfMeasListener::~TARoundOfMeasListener(){

}

//////////////////////////////////////////
// default response to a rom disactivation
//////////////////////////////////////////
void TARoundOfMeasListener::roundOfMeasDisactivated(){

}

/////////////////////////////////////////
// default response to a rom reactivation
/////////////////////////////////////////
void TARoundOfMeasListener::roundOfMeasActivated(){

}

///////////////////////////////////
// default response to a rom update
///////////////////////////////////
void TARoundOfMeasListener::roundOfMeasUpdated(EUpdateMessage umess){

	switch (umess){

	case kSeriesChange:
		break;

	case kReferenceChange:
		break;

	default:
		break;
	}
}
