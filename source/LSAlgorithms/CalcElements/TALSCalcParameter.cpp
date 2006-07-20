// TALSCalcParameter.cpp

#include "TALSCalcParameter.h"

/*
// Default constructor
TALSCalcParameter::TALSCalcParameter() {

	//not implemented
}
*/


// Copy constructor
TALSCalcParameter::TALSCalcParameter(const TALSCalcParameter& source) {

	fName = source.fName;
}


// Constructor using an identifier
TALSCalcParameter::TALSCalcParameter(string name) : fName(name) 
{
}

// Destructor
TALSCalcParameter::~TALSCalcParameter() {
}

// Overloaded equality operator
bool  TALSCalcParameter::operator==(const TALSCalcParameter& right) {

	bool isEqualTo = false;

	if (fName == right.fName)
		isEqualTo = true;

	return isEqualTo;
}

// Returns the parameter's name
string TALSCalcParameter::getName() const {

	return fName;
}

// Sets the parameter's name
void TALSCalcParameter::setName(string name) {

	fName = name;
}

