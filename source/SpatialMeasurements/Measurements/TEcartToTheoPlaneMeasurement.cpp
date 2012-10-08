// TEcartToTheoPlaneMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a theodolite's
	sighting line
*/


#include "TEcartToTheoPlaneMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TEcartToTheoPlaneMeasurement::TEcartToTheoPlaneMeasurement():TAPlaneMeasurement()
{//default constructor
}


TEcartToTheoPlaneMeasurement::TEcartToTheoPlaneMeasurement(string targetName, TLength obsDist, TLength sigma):
TAPlaneMeasurement(targetName, obsDist, sigma)
{//constructor
}


TEcartToTheoPlaneMeasurement::TEcartToTheoPlaneMeasurement(const TEcartToTheoPlaneMeasurement& source)
{//copy constructor
	(*this) = source;
}


TEcartToTheoPlaneMeasurement::~TEcartToTheoPlaneMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TEcartToTheoPlaneMeasurement&	TEcartToTheoPlaneMeasurement::operator=(const TEcartToTheoPlaneMeasurement& source)
{//copy assignement operator
	this->TAPlaneMeasurement::operator =(source);
	return (*this);
}


string				TEcartToTheoPlaneMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECTH measurement");
	return s;
}

