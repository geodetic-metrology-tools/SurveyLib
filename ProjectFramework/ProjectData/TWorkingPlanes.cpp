// TWorkingPlanes.cpp: implementation of the TWorkingPlanes class.
//




#include "TWorkingPlanes.h"
//ClassImp(TWorkingPlanes)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TWorkingPlanes::TWorkingPlanes()
{//constructor
}

TWorkingPlanes::~TWorkingPlanes()
{//destructor
}


/////////////////////////////////////////////////////////////
//Member function
/////////////////////////////////////////////////////////////
bool TWorkingPlanes::addPlane(TSpatialPlane* sp)
{//Adding a Spatial plane to the PlanesSet member variable
	
	string empty("");
	bool insert_ok = false;
	
	if( count(fWorkingPlanes.begin(), fWorkingPlanes.end(), *sp) == 0 )
	{// check that the plane is not already in the list
		if ((sp->getName()) == empty)
		{
			sp->buildErrorName();
		}
		fWorkingPlanes.push_back(*sp);
		insert_ok = true;
	}
	return insert_ok;
}


int TWorkingPlanes::numberOfPlanes() const
{//Returns the number of Spatial Planes stored in the PlanesSet
	return fWorkingPlanes.size();
}


PlaneIterator TWorkingPlanes::getPlanesBeginIterator()
{//Returns an iterator on the first element of the fWorkingPlanes
	return fWorkingPlanes.begin();
}


PlaneConstIter TWorkingPlanes::getPlanesBeginIterator() const
{//Returns a const iterator on the first element of the fWorkingPlanes
	return fWorkingPlanes.begin();
}


PlaneIterator TWorkingPlanes::getPlanesEndIterator()
{//returns an iterator on one element past the end of fWorkingPlanes
	return fWorkingPlanes.end();
}


PlaneConstIter TWorkingPlanes::getPlanesEndIterator() const
{//returns a const iterator on one element past the end of fWorkingPlanes
	return fWorkingPlanes.end();
}


PlaneIterator TWorkingPlanes::getPlane(string name)
{//returns an iterator on a plane, given its name
	PlaneIterator iter = fWorkingPlanes.begin();
	PlaneIterator iterEnd = fWorkingPlanes.end();

	bool notFound = true;

	while (iter != iterEnd  &&  notFound)
	{
		if ((iter->getName()) == name)
			notFound = false;
		else
			iter ++;
	}
	return iter;
}


PlaneConstIter TWorkingPlanes::getPlane(string name) const
{//returns a const iterator on a plane, given its name
	PlaneConstIter iter = fWorkingPlanes.begin();
	PlaneConstIter iterEnd = fWorkingPlanes.end();

	bool notFound = true;
	while (iter != iterEnd  &&  notFound)
	{
		if ((iter->getName()) == name)
			notFound = false;
		else
			iter ++;
	}
	return iter;
}



