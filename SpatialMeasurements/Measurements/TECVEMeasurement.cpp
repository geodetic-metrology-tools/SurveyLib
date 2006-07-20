// TECVEMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a vertical line
*/


#include "TECVEMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TECVEMeasurement::TECVEMeasurement():TALineMeasurement()
{//default constructor
}


TECVEMeasurement::TECVEMeasurement(string targetName, TLength obsDist, TLength sigma):
TALineMeasurement(targetName, obsDist, sigma)
{//constructor
}


TECVEMeasurement::TECVEMeasurement(const TECVEMeasurement& source)
{//copy constructor
	(*this) = source;
}


TECVEMeasurement::~TECVEMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TECVEMeasurement&	TECVEMeasurement::operator=(const TECVEMeasurement& source)
{//copy assignement operator
	this->TALineMeasurement::operator =(source);
	return (*this);
}


string				TECVEMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECVE measurement");
	return s;
}

