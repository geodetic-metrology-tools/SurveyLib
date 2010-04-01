// TLSCalcWorkingPosVec.cpp

#include "TLSCalcWorkingPosVec.h"

////////////////////////////////////////////////////////////////
// PUBLIC METHODS		
////////////////////////////////////////////////////////////////
LSPosVecIter TLSCalcWorkingPosVec::insert(LSPosVecIter it, TLSCalcPosVectorParam& posVec)
{
	hash_map<string, LSPosVecIter>::iterator iter = calcParamsMap.find(posVec.getName());
	LSPosVecIter lsPVIter;

	// if the observation isn't in the container -> insert
	if (iter == calcParamsMap.end())
	{
		lsPVIter = paramsList.insert(it, posVec);
		calcParamsMap[posVec.getName()] = lsPVIter;
	}
	else
	{
		lsPVIter = iter->second;
	}
	
	return lsPVIter; 
}

LSPosVecIter TLSCalcWorkingPosVec::getPoint(const string name)
{//returns an iterator on a point, given its Name
	hash_map<string, LSPosVecIter>::iterator iter = calcParamsMap.find(name);
	if (iter == calcParamsMap.end())
	{
		return paramsList.end();
	}

	return iter->second;
}


LSPosVecConstIter	TLSCalcWorkingPosVec::getPoint(const string name) const
{//returns a const iterator on a point, given its Name
	hash_map<string, LSPosVecIter>::const_iterator iter = calcParamsMap.find(name);
	if (iter == calcParamsMap.end())
	{
		return paramsList.end();
	}

	return iter->second;
}


////////////////////////////////////////////////////////////////
//END		
////////////////////////////////////////////////////////////////
