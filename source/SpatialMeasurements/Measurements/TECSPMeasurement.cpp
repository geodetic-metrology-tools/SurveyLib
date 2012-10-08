// TECSPMeasurement.cpp 
/*!
	Class for a distance between a point and a spacial line
*/


#include "TECSPMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TECSPMeasurement::TECSPMeasurement():TALineMeasurement()
{//default constructor
}


TECSPMeasurement::TECSPMeasurement(string targetName, TLength obsDist, TLength sigma):
TALineMeasurement(targetName, obsDist, sigma)
{//constructor
}


TECSPMeasurement::TECSPMeasurement(const TECSPMeasurement& source)
{//copy constructor
	(*this) = source;
}


TECSPMeasurement::~TECSPMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TECSPMeasurement&	TECSPMeasurement::operator=(const TECSPMeasurement& source)
{//copy assignement operator
	this->TALineMeasurement::operator =(source);
	return (*this);
}


string				TECSPMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECSP measurement");
	return s;
}

