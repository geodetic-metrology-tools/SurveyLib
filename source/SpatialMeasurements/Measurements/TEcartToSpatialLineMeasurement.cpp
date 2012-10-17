// TEcartToSpatialLineMeasurement.cpp 
/*!
	Class for a distance between a point and a spacial line
*/


#include "TEcartToSpatialLineMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TEcartToSpatialLineMeasurement::TEcartToSpatialLineMeasurement():TALineMeasurement()
{//default constructor
}


TEcartToSpatialLineMeasurement::TEcartToSpatialLineMeasurement(string targetName, TLength obsDist, TLength sigma):
TALineMeasurement(targetName, obsDist, sigma)
{//constructor
}


TEcartToSpatialLineMeasurement::TEcartToSpatialLineMeasurement(const TEcartToSpatialLineMeasurement& source)
{//copy constructor
	(*this) = source;
}


TEcartToSpatialLineMeasurement::~TEcartToSpatialLineMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TEcartToSpatialLineMeasurement&	TEcartToSpatialLineMeasurement::operator=(const TEcartToSpatialLineMeasurement& source)
{//copy assignement operator
	this->TALineMeasurement::operator =(source);
	return (*this);
}


string				TEcartToSpatialLineMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECSP measurement");
	return s;
}

