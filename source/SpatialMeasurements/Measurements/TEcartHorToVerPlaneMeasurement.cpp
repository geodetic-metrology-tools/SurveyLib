// TEcartHorToVerPlaneMeasurement.cpp 
/*!
	Class for a horizontal distance between a point and a line
*/


#include "TEcartHorToVerPlaneMeasurement.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TEcartHorToVerPlaneMeasurement::TEcartHorToVerPlaneMeasurement():TAPlaneMeasurement()
{//default constructor
}


TEcartHorToVerPlaneMeasurement::TEcartHorToVerPlaneMeasurement(string targetName, TLength obsDist, TLength sigma):
TAPlaneMeasurement(targetName, obsDist, sigma)
{//constructor
}


TEcartHorToVerPlaneMeasurement::TEcartHorToVerPlaneMeasurement(const TEcartHorToVerPlaneMeasurement& source)
{//copy constructor
	(*this) = source;
}


TEcartHorToVerPlaneMeasurement::~TEcartHorToVerPlaneMeasurement()
{//destructor
}




////////////////////////////////////////////////////////////////////////////////////
//Member function
////////////////////////////////////////////////////////////////////////////////////
TEcartHorToVerPlaneMeasurement&	TEcartHorToVerPlaneMeasurement::operator=(const TEcartHorToVerPlaneMeasurement& source)
{//copy assignement operator
	this->TAPlaneMeasurement::operator =(source);
	return (*this);
}


string				TEcartHorToVerPlaneMeasurement::getMeasKind() const
{//returns the string representing the measurement kind
	string s("ECHO measurement");
	return s;
}

