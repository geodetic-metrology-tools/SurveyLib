// TECTHMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a theodolite's
	sighting line
*/


#include "TECTHMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TECTHMeasurement::TECTHMeasurement():TAPlaneMeasurement()
{//default constructor
}


TECTHMeasurement::TECTHMeasurement(string targetName, TLength obsDist, TLength sigma):
TAPlaneMeasurement(targetName, obsDist, sigma)
{//constructor
}


TECTHMeasurement::TECTHMeasurement(const TECTHMeasurement& source)
{//copy constructor
	(*this) = source;
}


TECTHMeasurement::~TECTHMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TECTHMeasurement&	TECTHMeasurement::operator=(const TECTHMeasurement& source)
{//copy assignement operator
	this->TAPlaneMeasurement::operator =(source);
	return (*this);
}


string				TECTHMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECTH measurement");
	return s;
}

