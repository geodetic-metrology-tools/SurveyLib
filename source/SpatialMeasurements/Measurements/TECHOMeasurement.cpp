// TECHOMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a line
*/


#include "TECHOMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TECHOMeasurement::TECHOMeasurement():TAPlaneMeasurement()
{//default constructor
}


TECHOMeasurement::TECHOMeasurement(string targetName, TLength obsDist, TLength sigma):
TAPlaneMeasurement(targetName, obsDist, sigma)
{//constructor
}


TECHOMeasurement::TECHOMeasurement(const TECHOMeasurement& source)
{//copy constructor
	(*this) = source;
}


TECHOMeasurement::~TECHOMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TECHOMeasurement&	TECHOMeasurement::operator=(const TECHOMeasurement& source)
{//copy assignement operator
	this->TAPlaneMeasurement::operator =(source);
	return (*this);
}


string				TECHOMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECHO measurement");
	return s;
}

