// TWorkingTargetObjects.h
//
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
////////////////////////////////////////////////////////



#ifndef SU_TWORK_TARGET_OBJECTS
#define SU_TWORK_TARGET_OBJECTS


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////
// Forward declarations
//
#include  <list>
using namespace std;
//
//class  **classname**;
#include  "TWorkingPoints.h"
#include "TWire.h"
#include "TSpatialLine.h"
// typedefs
//
//
////////////////////////////////////////////////////////



//! Class storing all the target objects (except points)
class  TWorkingTargetObjects //: public TObject  
{
public:
	//constants
	typedef list< TWire > WireContainer;
	typedef WireContainer::iterator WireIterator;
	typedef WireContainer::const_iterator WireConstIter;
	typedef list< TSpatialLine > SpLineContainer;
	typedef SpLineContainer::iterator SpLineIterator;
	typedef SpLineContainer::const_iterator SpLineConstIter;


	/*!@name Constructors and Destructors */
	//@{
		//! Default Constructor 
		TWorkingTargetObjects();

		//! Copy Constructor 
		TWorkingTargetObjects(const  TWorkingTargetObjects& source);

		//! Destructor
		virtual  ~TWorkingTargetObjects();
	//@}


		//! Copy Assignment Operator 
		TWorkingTargetObjects& operator=( const TWorkingTargetObjects& source);

		/*!@name Wire related functions */
		//@{
		/*!@return an iterator pointing to the first element of the wire container*/
		virtual	WireIterator		getWireBeginIterator();
		/*!@return a const iterator pointing to the first element of the wire container*/
		virtual	WireConstIter		getWireBeginIterator() const;
		/*!@return an iterator pointing one past the last element of the wire container*/
		virtual	WireIterator		getWireEndIterator();
		/*!@return a const iterator pointing one past the last element of the wire container*/
		virtual	WireConstIter		getWireEndIterator() const;
		/*!@return an iterator pointing to a specific wire of the container
		@param end1 an iterator pointing to the wire's first endpoint
		@param end2 an iterator pointing to the wire's second endpoint*/
		virtual WireIterator		getWire(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2);
		/*!@return a const iterator pointing to a specific wire of the container
		@param end1 an iterator pointing to the wire's first endpoint
		@param end2 an iterator pointing to the wire's second endpoint*/
		virtual WireConstIter		getWire(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2) const;
		/*!@return the number of stored wires*/
		virtual int					numberOfWires() const;
		//!Adds a wire to the container
		/*!@param wire a pointer to the wire which will be copied into the container*/
		virtual void				addWire(TWire* wire);
		/*!@return a true boolean if a copy of the pointed to wire isn't already stroed in the container*/
		virtual bool				notInContainer(TWire* wire) const;
		//@}

		/*!@name Spatial Line related functions */
		//@{
		/*!@return an iterator pointing to the first element of the spatial line container*/
		virtual	SpLineIterator		getSpLineBeginIterator();
		/*!@return a const iterator pointing to the first element of the spatial line container*/
		virtual	SpLineConstIter		getSpLineBeginIterator() const;
		/*!@return an iterator pointing one past the last element of the spatial container*/
		virtual	SpLineIterator		getSpLineEndIterator();
		/*!@return a const iterator pointing one past the last element of the spatial container*/
		virtual	SpLineConstIter		getSpLineEndIterator() const;
		/*!@return an iterator pointing to a specific spatial line of the container
		@param end1 an iterator pointing to the line's first endpoint
		@param end2 an iterator pointing to the line's second endpoint*/
		virtual SpLineIterator		getSpLine(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2);
		/*!@return a const iterator pointing to a specific spatial line of the container
		@param end1 an iterator pointing to the line's first endpoint
		@param end2 an iterator pointing to the line's second endpoint*/
		virtual SpLineConstIter		getSpLine(TWorkingPoints::PointIterator end1, TWorkingPoints::PointIterator end2) const;
		/*!@return an iterator pointing to a specific spatial line of the container
		@param lineName the name of the requested line*/
		virtual SpLineIterator		getSpLine(string lineName);
		/*!@return a const iterator pointing to a specific spatial line of the container
		@param lineName the name of the requested line*/
		virtual SpLineConstIter		getSpLine(string lineName) const;
		/*!@return the number of stored spatial lines*/
		virtual int					numberOfSpLines() const;
		//!Adds a spatial line to the container
		/*!@param line a pointer to the spatial line which will be copied into the container*/
		virtual void				addSpLine(TSpatialLine* line);
		/*!@return a true boolean if a copy of the pointed to line isn't already stroed in the container*/
		virtual bool				notInContainer(TSpatialLine* line) const;
		//@}

private:

	WireContainer			fWires;
	int						fLastWireNbr;
	SpLineContainer			fSpLines;
	int						fLastSpLineNbr;

	//ClassDef(TWorkingTargetObjects, 1)

};


#endif // SU_TWORK_TARGET_OBJECTS
