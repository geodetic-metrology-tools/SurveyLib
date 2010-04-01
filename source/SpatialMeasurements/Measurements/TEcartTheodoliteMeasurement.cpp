// TEcartTheodoliteMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a theodolite's
	sighting line
*/


#include "TEcartTheodoliteMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TEcartTheodoliteMeasurement::TEcartTheodoliteMeasurement():TAPlaneMeasurement()
{//default constructor
}


TEcartTheodoliteMeasurement::TEcartTheodoliteMeasurement(string targetName, TLength obsDist, TLength sigma):
TAPlaneMeasurement(targetName, obsDist, sigma)
{//constructor
}


TEcartTheodoliteMeasurement::TEcartTheodoliteMeasurement(const TEcartTheodoliteMeasurement& source)
{//copy constructor
	(*this) = source;
}


TEcartTheodoliteMeasurement::~TEcartTheodoliteMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TEcartTheodoliteMeasurement&	TEcartTheodoliteMeasurement::operator=(const TEcartTheodoliteMeasurement& source)
{//copy assignement operator
	this->TAPlaneMeasurement::operator =(source);
	return (*this);
}


string				TEcartTheodoliteMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECTH measurement");
	return s;
}

