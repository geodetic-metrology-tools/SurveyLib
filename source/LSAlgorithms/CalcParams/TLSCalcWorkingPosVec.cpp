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
	hash_map<string, LSPosVecIter>::iterator iter = posVectorMap.find(posVec.getName());
	LSPosVecIter lsPVIter;

	if(!fListError)
	{
		// if the observation isn't in the container -> insert
		if (iter == posVectorMap.end())
		{
			lsPVIter = fLSPosVectorList.insert(it, posVec);
			posVectorMap[posVec.getName()] = lsPVIter;
			fLastElNbr++;
		}
		else
		{
			lsPVIter = iter->second;
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

	hash_map<string, LSPosVecIter>::iterator iter = posVectorMap.find(posVec.getName());
	LSPosVecIter lsPVIter;

	if(!fListError)
	{
		// if the observation isn't in the container -> insert
		if (iter == posVectorMap.end())
		{
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
			posVectorMap[posVec.getName()] = lsPVIter;
		}
		else
		{
			lsPVIter = iter->second;
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

	hash_map<string, LSPosVecIter>::iterator iter = posVectorMap.find(posVec.getName());

	if (iter == posVectorMap.end())
	{
		return false;
	}
	fLSPosVectorList.erase(iter->second);
	posVectorMap.erase(posVec.getName());
		
	return true;
}
	

LSPosVecIter	TLSCalcWorkingPosVec::getPoint(const string name)
{//returns an iterator on a point, given its Name
	hash_map<string, LSPosVecIter>::iterator iter = posVectorMap.find(name);
	if (iter == posVectorMap.end())
	{
		return fLSPosVectorList.end();
	}

	return iter->second;
}


LSPosVecConstIter	TLSCalcWorkingPosVec::getPoint(const string name) const
{//returns a const iterator on a point, given its Name
	hash_map<string, LSPosVecIter>::const_iterator iter = posVectorMap.find(name);
	if (iter == posVectorMap.end())
	{
		return fLSPosVectorList.end();
	}

	return iter->second;
}


////////////////////////////////////////////////////////////////
//END		
////////////////////////////////////////////////////////////////
