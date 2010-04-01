// TWorkingLines.h : Header File.
//////////////////////////////////////////////////////////////////////

#ifndef SU_WORKING_LINES
#define SU_WORKING_LINES

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif 


#include <list>
#include <algorithm>
#include <sstream>
using namespace std;


#include "TSpatialLine.h"




//! Class used to store a set of TSpatialLines
class TWorkingLines //: public TObject  
{
public:

	

	/*!@name Constructors/Destructor*/
	//@{
	//!Default constructor
	TWorkingLines();
	//!Destructor
	virtual ~TWorkingLines();
	//@}

	//!Adds a point to the container
	/*!@param sp a pointer to the point to be stored (the pointed to point object is copied)
	@return a true boolean if the point was added to the container (no point with the same name stored yet)*/
	bool			addLine(TSpatialLine* sp);
	/*!@return the number of stored Lines*/
	int				numberOfLines() const;
	/*!@return an iterator pointing to the first line of the container*/
	LineIterator	getLinesBeginIterator();
	/*!@return a cons iterator pointing to the first line of the container*/
	LineConstIter	getLinesBeginIterator() const;
	/*!@return an iterator pointing to one past the last line of the container*/
	LineIterator	getLinesEndIterator();
	/*!@return a cons iterator pointing to one past the last line of the container*/
	LineConstIter	getLinesEndIterator() const;
	/*!@return an iterator pointing to a line specified through its name*/
	LineIterator	getLine(string);
	/*!@return a cons iterator pointing to a line specified through its name*/
	LineConstIter	getLine(string) const;

private:
	
	SpatialLineContainer	fWorkingLines;
};
#endif 
