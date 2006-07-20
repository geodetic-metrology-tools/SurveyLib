// TWorkingTargetObjects.cpp
//
/** Class storing all the target objects (except points) */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TWorkingTargetObjects.h"
////////////////////////////////////////////////////////////////


//ClassImp(TWorkingTargetObjects)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TWorkingTargetObjects::TWorkingTargetObjects()
{	// default constructor
	fLastWireNbr = 0;
	fLastSpLineNbr = 0;
}

// **This needs to be implemented**
TWorkingTargetObjects::TWorkingTargetObjects( const  TWorkingTargetObjects& source ):
fWires(source.fWires), fLastWireNbr(source.fLastWireNbr),
fSpLines(source.fSpLines), fLastSpLineNbr(source.fLastSpLineNbr)
{	// copy constructor

}


TWorkingTargetObjects::~TWorkingTargetObjects()
{
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
// **This needs to be implemented**
TWorkingTargetObjects&  TWorkingTargetObjects::operator=(const TWorkingTargetObjects& right)
{	// Copy Assignment operator
	if (this != &right)
	{
		fWires = right.fWires;
		fLastWireNbr = right.fLastWireNbr;
		fSpLines = right.fSpLines;
		fLastSpLineNbr = right.fLastSpLineNbr;
	}
	return *this;
}


//*******/////////////////////////////////////////////////////////////
// Utility Member Functions
//*******/////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// returns an iterator pointing to the first wire of the container
//////////////////////////////////////////////////////////////////
TWorkingTargetObjects::WireIterator TWorkingTargetObjects::getWireBeginIterator() {

	return fWires.begin();
}

///////////////////////////////////////////////////////////////////////
// returns a const iterator pointing to the first wire of the container
///////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::WireConstIter TWorkingTargetObjects::getWireBeginIterator() const{

	return fWires.begin();
}

//////////////////////////////////////////////////////////////////////////
// returns an iterator pointing to one past the last wire of the container
//////////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::WireIterator TWorkingTargetObjects::getWireEndIterator() {

	return fWires.end();
}

///////////////////////////////////////////////////////////////////////////////
// returns a const iterator pointing to one past the last wire of the container
///////////////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::WireConstIter TWorkingTargetObjects::getWireEndIterator() const{

	return fWires.end();
}

////////////////////////////////////////////////
// returns a wire being given its two end points
////////////////////////////////////////////////
TWorkingTargetObjects::WireIterator TWorkingTargetObjects::
getWire(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2) {

	WireIterator iterW = getWireBeginIterator();
	WireIterator iterWend = getWireEndIterator();

	bool notFound = true;

	while ((iterW != iterWend) && notFound){

		if ((iterW->getFirstEnd() == end1) && (iterW->getSecondEnd() == end2))
			notFound = false;
		else
			iterW++;
	}

	return iterW;
}

////////////////////////////////////////////////
// returns a wire being given its two end points
////////////////////////////////////////////////
TWorkingTargetObjects::WireConstIter TWorkingTargetObjects::
getWire(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2) const{

	WireConstIter iterW = getWireBeginIterator();
	WireConstIter iterWend = getWireEndIterator();

	bool notFound = true;

	while ((iterW != iterWend) && notFound){

		if ((iterW->getFirstEnd() == end1) && (iterW->getSecondEnd() == end2))
			notFound = false;
		else
			iterW++;
	}

	return iterW;
}

/////////////////////////////////////
// returns the number of stored wires
/////////////////////////////////////
int	TWorkingTargetObjects::numberOfWires() const{

	return fWires.size();
}



//////////////////////////////////////////////////////
// checks if a wire is already stored in the container
//////////////////////////////////////////////////////
bool TWorkingTargetObjects::notInContainer(TWire* wire) const{

	WireConstIter iter = getWireBeginIterator();
	WireConstIter iterEnd = getWireEndIterator();

	bool notPresent = true;

	while (iter != iterEnd){

		if ((*iter) == (*wire)){
			notPresent = false;
			iter = iterEnd;
		}
		else
			iter++;
	}

	return notPresent;
}

///////////////////////////////
// adds a wire to the container
///////////////////////////////
void TWorkingTargetObjects::addWire(TWire* wire){

	if (notInContainer(wire)){
		string empty("");
		if (wire->getName() == empty){
			ostringstream oss;
			fLastWireNbr ++;
			oss << "Wire" << fLastWireNbr;
			wire->setName(oss.str());
		}
		fWires.push_back(*wire);
	}
}
		

//////////////////////////////////////////////////////////////////////////
// returns an iterator pointing to the first spatial line of the container
//////////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::SpLineIterator TWorkingTargetObjects::getSpLineBeginIterator() {

	return fSpLines.begin();
}

///////////////////////////////////////////////////////////////////////////////
// returns a const iterator pointing to the first spatial line of the container
///////////////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::SpLineConstIter TWorkingTargetObjects::getSpLineBeginIterator() const{

	return fSpLines.begin();
}

//////////////////////////////////////////////////////////////////////////////////
// returns an iterator pointing to one past the last spatial line of the container
//////////////////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::SpLineIterator TWorkingTargetObjects::getSpLineEndIterator() {

	return fSpLines.end();
}

///////////////////////////////////////////////////////////////////////////////////////
// returns a const iterator pointing to one past the last spatial line of the container
///////////////////////////////////////////////////////////////////////////////////////
TWorkingTargetObjects::SpLineConstIter TWorkingTargetObjects::getSpLineEndIterator() const{

	return fSpLines.end();
}

////////////////////////////////////////////////////////
// returns a spatial line being given its two end points
////////////////////////////////////////////////////////
TWorkingTargetObjects::SpLineIterator TWorkingTargetObjects::
getSpLine(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2) {

	SpLineIterator iterW = getSpLineBeginIterator();
	SpLineIterator iterWend = getSpLineEndIterator();

	bool notFound = true;

	while ((iterW != iterWend) && notFound){

		if ((iterW->getFirstEnd() == end1) && (iterW->getSecondEnd() == end2))
			notFound = false;
		else
			iterW++;
	}

	return iterW;
}

////////////////////////////////////////////////////////
// returns a spatial line being given its two end points
////////////////////////////////////////////////////////
TWorkingTargetObjects::SpLineConstIter TWorkingTargetObjects::
getSpLine(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2) const{

	SpLineConstIter iterW = getSpLineBeginIterator();
	SpLineConstIter iterWend = getSpLineEndIterator();

	bool notFound = true;

	while ((iterW != iterWend) && notFound){

		if ((iterW->getFirstEnd() == end1) && (iterW->getSecondEnd() == end2))
			notFound = false;
		else
			iterW++;
	}

	return iterW;
}

//////////////////////////////////////////////
// returns a spatial line being given its name
//////////////////////////////////////////////
TWorkingTargetObjects::SpLineIterator TWorkingTargetObjects::getSpLine(string lineName) {

	SpLineIterator iterW = getSpLineBeginIterator();
	SpLineIterator iterWend = getSpLineEndIterator();

	bool notFound = true;

	while ((iterW != iterWend) && notFound){

		if (iterW->getName() == lineName)
			notFound = false;
		else
			iterW++;
	}

	return iterW;
}

//////////////////////////////////////////////
// returns a spatial line being given its name
//////////////////////////////////////////////
TWorkingTargetObjects::SpLineConstIter TWorkingTargetObjects::getSpLine(string lineName) const{

	SpLineConstIter iterW = getSpLineBeginIterator();
	SpLineConstIter iterWend = getSpLineEndIterator();

	bool notFound = true;

	while ((iterW != iterWend) && notFound){

		if (iterW->getName() == lineName)
			notFound = false;
		else
			iterW++;
	}

	return iterW;
}

/////////////////////////////////////
// returns the number of stored spatial lines
/////////////////////////////////////
int	TWorkingTargetObjects::numberOfSpLines() const{

	return fSpLines.size();
}



//////////////////////////////////////////////////////
// checks if a spatial line is already stored in the container
//////////////////////////////////////////////////////
bool TWorkingTargetObjects::notInContainer(TSpatialLine* wire) const{

	SpLineConstIter iter = getSpLineBeginIterator();
	SpLineConstIter iterEnd = getSpLineEndIterator();

	bool notPresent = true;

	while (iter != iterEnd){

		if ((*iter) == (*wire)){
			notPresent = false;
			iter = iterEnd;
		}
		else
			iter++;
	}

	return notPresent;
}

///////////////////////////////
// adds a spatial line to the container
///////////////////////////////
void TWorkingTargetObjects::addSpLine(TSpatialLine* spl){

	if (notInContainer(spl)){
		string empty("");
		if (spl->getName() == empty){
			ostringstream oss;
			fLastSpLineNbr ++;
			oss << "SpLine" << fLastSpLineNbr;
			spl->setName(oss.str());
		}
		fSpLines.push_back(*spl);
	}
}
		

