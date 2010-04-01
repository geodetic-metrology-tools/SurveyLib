// TWorkingPlanes.h : Header File.
//////////////////////////////////////////////////////////////////////

#ifndef SU_WORKING_PLANES
#define SU_WORKING_PLANES

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif 


#include <list>
#include <algorithm>
#include <sstream>
using namespace std;


#include "TSpatialPlane.h"




//! Class used to store a set of TSpatialPlanes
class TWorkingPlanes //: public TObject  
{
public:

	

	/*!@name Constructors/Destructor*/
	//@{
	//!Default constructor
	TWorkingPlanes();
	//!Destructor
	virtual ~TWorkingPlanes();
	//@}

	//!Adds a point to the container
	/*!@param sp a pointer to the point to be stored (the pointed to point object is copied)
	@return a true boolean if the point was added to the container (no point with the same name stored yet)*/
	bool				addPlane(TSpatialPlane* sp);
	/*!@return the number of stored Planes*/
	int					numberOfPlanes() const;
	/*!@return an iterator pointing to the first plane of the container*/
	PlaneIterator		getPlanesBeginIterator();
	/*!@return a cons iterator pointing to the first plane of the container*/
	PlaneConstIter		getPlanesBeginIterator() const;
	/*!@return an iterator pointing to one past the last plane of the container*/
	PlaneIterator		getPlanesEndIterator();
	/*!@return a cons iterator pointing to one past the last plane of the container*/
	PlaneConstIter		getPlanesEndIterator() const;
	/*!@return an iterator pointing to a plane specified through its name*/
	PlaneIterator		getPlane(string);
	/*!@return a const iterator pointing to a plane specified through its name*/
	PlaneConstIter		getPlane(string) const;

private:
	
	SpatialPlaneContainer	fWorkingPlanes;
};
#endif 
