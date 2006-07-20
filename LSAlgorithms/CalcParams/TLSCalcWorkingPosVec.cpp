// TLSCalcWorkingPosVec.cpp

#include "TLSCalcWorkingPosVec.h"

//////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////
TLSCalcWorkingPosVec::TLSCalcWorkingPosVec(): fLastElNbr(0),fListError(false)
{// Default constructor 
	fLSPosVectorList.clear();
}


TLSCalcWorkingPosVec::~TLSCalcWorkingPosVec()
{//Destructor 
	fLSPosVectorList.clear();
}


////////////////////////////////////////////////////////////////
// PUBLIC METHODS		
////////////////////////////////////////////////////////////////
LSPosVecIter	TLSCalcWorkingPosVec::insert(LSPosVecIter it, TLSCalcPosVectorParam& posVec)
{
	LSPosVecIter lsPVIter;

	if(!fListError)
	{
		// Checks if the observation is already in the container or not
		bool notFound = true;

		LSPosVecIter iterB = begin();
		LSPosVecIter iterE = end();

		while (iterB!=iterE && notFound)
		{
			if (posVec == *iterB)
			{	
				lsPVIter = iterB; 
				notFound = false;
			}
			else
			{
				iterB++;
			}
		}
		
		// if the observation isn't in the container -> insert
		if (notFound)
		{	
			lsPVIter = fLSPosVectorList.insert(it, posVec);
		}
	}
	else
	{
		lsPVIter = end();
	}
		
	return lsPVIter; 
}


LSPosVecIter	TLSCalcWorkingPosVec::push_back(TLSCalcPosVectorParam& posVec)
{// Inserts a new TLSCalcPosVectorParam in the list, 
	//if it is not done yet (tests first if the object is already in the list or not)

	LSPosVecIter lsPVIter;

	if(!fListError)
	{
		// Checks if the observation is already in the container or not
		bool notFound = true;

		LSPosVecIter iterB = begin();
		LSPosVecIter iterE = end();

		while (iterB!=iterE && notFound)
		{
			if (posVec == *iterB) {	
				lsPVIter = iterB; 
				notFound = false;
			}
			else
				iterB++;
		}
		
		// if the observation isn't in the container -> addition at the end of the list
		if (notFound) {	
			fLSPosVectorList.push_back(posVec);
			fLastElNbr++;
			// Debugging for the case where the push_back method fails
			if(fLastElNbr == fLSPosVectorList.size())
			{
				//no error
				lsPVIter = --(fLSPosVectorList.end());
			}
			else
			{
				//error
				//treat error
				fListError = true;
				lsPVIter = end();
			}
		}
	}
	else
	{
		lsPVIter = end();
	}
		
	return lsPVIter; 
}

bool TLSCalcWorkingPosVec::erase(TLSCalcPosVectorParam& posVec)
{// Erases the selected TLSCalcPosVectorParam and 
	//deletes its corresponding pointer from the list if it exists

	bool isErased = false;

	LSPosVecIter iterB = begin();
	LSPosVecIter iterE = end();

	while (iterB!=iterE) {
		if (posVec == *iterB ) {
			fLSPosVectorList.erase(iterB);
			isErased = true;
			fLastElNbr--;
			iterB = iterE; }
		else
			iterB++;
	}
		
	return isErased;
}
	

LSPosVecIter	TLSCalcWorkingPosVec::getPoint(const string name)
{//returns an iterator on a point, given its Name
	LSPosVecIter	iter = fLSPosVectorList.begin();
	LSPosVecIter	iterEnd = fLSPosVectorList.end();

	bool notFound = true;

	while (iter != iterEnd  &&  notFound){
		if ((iter->getName()) == name)
			notFound = false;
		else
			iter ++;
	}

	return iter;
}


LSPosVecConstIter	TLSCalcWorkingPosVec::getPoint(const string name) const
{//returns a const iterator on a point, given its Name
	LSPosVecConstIter	iter = fLSPosVectorList.begin();
	LSPosVecConstIter	iterEnd = fLSPosVectorList.end();

	bool notFound = true;

	while (iter != iterEnd  &&  notFound){
		if ((iter->getName()) == name)
			notFound = false;
		else
			iter ++;
	}

	return iter;
}


////////////////////////////////////////////////////////////////
//END		
////////////////////////////////////////////////////////////////
