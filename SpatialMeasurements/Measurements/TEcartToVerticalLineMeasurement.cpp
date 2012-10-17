// TEcartToVerticalLineMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a vertical line
*/


#include "TEcartToVerticalLineMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TEcartToVerticalLineMeasurement::TEcartToVerticalLineMeasurement():TALineMeasurement()
{//default constructor
}


TEcartToVerticalLineMeasurement::TEcartToVerticalLineMeasurement(string targetName, TLength obsDist, TLength sigma):
TALineMeasurement(targetName, obsDist, sigma)
{//constructor
}


TEcartToVerticalLineMeasurement::TEcartToVerticalLineMeasurement(const TEcartToVerticalLineMeasurement& source)
{//copy constructor
	(*this) = source;
}


TEcartToVerticalLineMeasurement::~TEcartToVerticalLineMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TEcartToVerticalLineMeasurement&	TEcartToVerticalLineMeasurement::operator=(const TEcartToVerticalLineMeasurement& source)
{//copy assignement operator
	this->TALineMeasurement::operator =(source);
	return (*this);
}


string				TEcartToVerticalLineMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECVE measurement");
	return s;
}

