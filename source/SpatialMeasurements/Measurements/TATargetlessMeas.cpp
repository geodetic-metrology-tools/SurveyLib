//
// TATargetlessMeas.cpp : implementation file
// abstract base class holding the behaviour common to all
// untargeted measurements, mainly the active/inactive management

#include "TATargetlessMeas.h"

//////////////////////
// default constructor
//////////////////////
TATargetlessMeas::TATargetlessMeas(TVParentMeasTreeNode* parent){

	//fUsedInCalc = false;
	fUsedInCalc = true;
	fParent = parent;
	fParentUsedInCalc = fParent->isActive();
	fActiveMeasCount = 1;
	fActiveEqCount = 1;
	fActiveUnkCount = 0;
}

///////////////////
// copy constructor
///////////////////
TATargetlessMeas::TATargetlessMeas(const TATargetlessMeas& source):
fUsedInCalc(source.fUsedInCalc), fParentUsedInCalc(source.fParentUsedInCalc),
fActiveMeasCount(source.fActiveMeasCount), fActiveEqCount(source.fActiveEqCount),
fActiveUnkCount(source.fActiveUnkCount), fParent(source.fParent){

}


/////////////
// destructor
/////////////
TATargetlessMeas::~TATargetlessMeas(){

}

///////////////////////////////////////
// returns the measurement's equation count
///////////////////////////////////////
int TATargetlessMeas::equationsCount() const{

	return fActiveEqCount;
}

//////////////////////////////////////////
// returns the measurement's measurement count
//////////////////////////////////////////
int TATargetlessMeas::measurementsCount() const{

	return fActiveMeasCount;
}

///////////////////////////////////////
// returns the measurement's unknowns count
///////////////////////////////////////
int TATargetlessMeas::unknownsCount() const{

	return fActiveUnkCount;
}

/////////////////////////////////////////
// tells about the active/inactive status
/////////////////////////////////////////
bool TATargetlessMeas::isActive() const{

	return fUsedInCalc;
}

///////////////////////////////////////////////
// adds a measurement listener to the container
///////////////////////////////////////////////
void TATargetlessMeas::addListener(TVMeasurementListener* measListnr){

	fMeasListeners.push_back(measListnr);
}

///////////////////////////////
// disactivates the measurement
///////////////////////////////
void TATargetlessMeas::disactivate(){

	bool fWasUsedInCalc = fUsedInCalc;
	bool fParentWasUsedInCalc = fParentUsedInCalc;

	if (fUsedInCalc)
		fUsedInCalc = false;

	//Active Parent
	if ((fWasUsedInCalc) && (fParentWasUsedInCalc)){
		fParent->childDisactivated(fActiveMeasCount, fActiveEqCount, fActiveUnkCount);

		MeasListnrIterator iter = fMeasListeners.begin();
		MeasListnrIterator iterEnd = fMeasListeners.end();
		while (iter != iterEnd){
			(*iter)->measurementDisactivated();
			iter++;
		}
	}

	//Inactive Parent
	//No message sent to the Target  (would be redundant with the one 
	//sent when the Parent was set Inactive
	if ((fWasUsedInCalc) && (!fParentWasUsedInCalc)){
		fParent->childDisactivated(fActiveMeasCount, fActiveEqCount, fActiveUnkCount);

		MeasListnrIterator iter = fMeasListeners.begin();
		MeasListnrIterator iterEnd = fMeasListeners.end();
		while (iter != iterEnd){
			(*iter)->measurementDisactivated();
			iter++;
		}
	}
}

//////////////////////////////
// reactivates the measurement
//////////////////////////////
void TATargetlessMeas::activate(){

	//no reaction if fUsedInCalc

	//if !fUIC && !fOUIC message sent only to the Parent
	if ((!fUsedInCalc) && (!fParentUsedInCalc)){
		fUsedInCalc = true;
		fParent->childActivated(fActiveMeasCount, fActiveEqCount, fActiveUnkCount);

		MeasListnrIterator iter = fMeasListeners.begin();
		MeasListnrIterator iterEnd = fMeasListeners.end();
		while (iter != iterEnd){
			(*iter)->measurementActivated();
			iter++;
		}

	}

	//if !fUIC && fOUIC message sent to all concerned objects
	if ((!fUsedInCalc) && (fParentUsedInCalc)){
		fUsedInCalc = true;
		fParent->childActivated(fActiveMeasCount, fActiveEqCount, fActiveUnkCount);

		MeasListnrIterator iter = fMeasListeners.begin();
		MeasListnrIterator iterEnd = fMeasListeners.end();
		while (iter != iterEnd){
			(*iter)->measurementActivated();
			iter++;
		}
	}
}

/////////////////////////////////////////////////////////////
// responds to the disactivation of the parent ROM or station
/////////////////////////////////////////////////////////////
void TATargetlessMeas::parentDisactivated(){

	bool fWasUsedInCalc = fUsedInCalc;
	bool fParentWasUsedInCalc = fParentUsedInCalc;

	//!fParentUsedInCalc shouldn't occur

	if ((!fWasUsedInCalc) && (fParentWasUsedInCalc)){
		fParentUsedInCalc = false;
	}

	if ((fWasUsedInCalc) && (fParentWasUsedInCalc)){
		fParentUsedInCalc = false;

		MeasListnrIterator iter = fMeasListeners.begin();
		MeasListnrIterator iterEnd = fMeasListeners.end();
		while (iter != iterEnd){
			(*iter)->measurementDisactivated();
			iter++;
		}
	}
}

////////////////////////////////////////////////////////////
// responds to the reactivation of the parent ROM or station
////////////////////////////////////////////////////////////
void TATargetlessMeas::parentActivated(){

	bool fParentWasUsedInCalc = fParentUsedInCalc;
	bool fWasUsedInCalc = fUsedInCalc;

	//no reaction if fParentUsedInCalc

	if ((!fWasUsedInCalc) && (!fParentWasUsedInCalc)){
		fParentUsedInCalc = true;
	}

	if ((fWasUsedInCalc) && (!fParentWasUsedInCalc)){
		fParentUsedInCalc = true;

		MeasListnrIterator iter = fMeasListeners.begin();
		MeasListnrIterator iterEnd = fMeasListeners.end();
		while (iter != iterEnd){
			(*iter)->measurementActivated();
			iter++;
		}
	}
}

