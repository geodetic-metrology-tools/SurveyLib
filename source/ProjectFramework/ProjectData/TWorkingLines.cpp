// TWorkingLines.cpp: implementation of the TWorkingLines class.
//




#include "TWorkingLines.h"
//ClassImp(TWorkingLines)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TWorkingLines::TWorkingLines()
{//constructor
}

TWorkingLines::~TWorkingLines()
{//destructor
}


/////////////////////////////////////////////////////////////
//Member function
/////////////////////////////////////////////////////////////
bool TWorkingLines::addLine(TSpatialLine* sp)
{//Adding a Spatial line to the LinesSet member variable
	
	string empty("");
	bool insert_ok = false;
	
	if( count(fWorkingLines.begin(), fWorkingLines.end(), *sp) == 0 )
	{// check that the line is not already in the list
		if ((sp->getName()) == empty)
		{
			sp->buildErrorName();
		}
		fWorkingLines.push_back(*sp);
		insert_ok = true;
	}
	return insert_ok;
}


int TWorkingLines::numberOfLines() const
{//Returns the number of Spatial Lines stored in the LinesSet
	return fWorkingLines.size();
}


LineIterator TWorkingLines::getLinesBeginIterator()
{//Returns an iterator on the first element of the fWorkingLines
	return fWorkingLines.begin();
}


LineConstIter TWorkingLines::getLinesBeginIterator() const
{//Returns a const iterator on the first element of the fWorkingLines
	return fWorkingLines.begin();
}


LineIterator TWorkingLines::getLinesEndIterator()
{//returns an iterator on one element past the end of fWorkingLines
	return fWorkingLines.end();
}


LineConstIter TWorkingLines::getLinesEndIterator() const
{//returns a const iterator on one element past the end of fWorkingLines
	return fWorkingLines.end();
}


LineIterator TWorkingLines::getLine(string name)
{//returns an iterator on a line, given its name
	LineIterator iter = fWorkingLines.begin();
	LineIterator iterEnd = fWorkingLines.end();

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


LineConstIter TWorkingLines::getLine(string name) const
{//returns a const iterator on a line, given its name
	LineConstIter iter = fWorkingLines.begin();
	LineConstIter iterEnd = fWorkingLines.end();

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


////////////////////////////////////////////////////////
//END
////////////////////////////////////////////////////////
