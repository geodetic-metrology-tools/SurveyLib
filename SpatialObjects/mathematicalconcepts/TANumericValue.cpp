// TANumericValue.cpp
/*
The TANumericValue class implements the interface for a
numerical value.
 
It is a abstract base class (PABC) that should be inherited 
by all numerical values. 

The methods declared in the TVNumericValue for accessing, 
changing, and assessing the status of a numerical value 
are defined.

Patterns:
 
 
Copyright 2002 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////////////


//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
//
#include	"TANumericValue.h"
////////////////////////////////////////////////////////////////



//ClassImp(TANumericValue)

TANumericValue::TANumericValue()
{
	fStatus = kNull;
}


//////////////
// Test Status
//////////////



TANumericValue::EStatus TANumericValue::testStatus(TANumericValue obj) const
{   // Determines the status of a numerical value that should
    // be assigned when an operation is performed on this 
	// numeric value and the given value.
	
	if (fStatus==kNull || obj.getStatus()==kNull)
	{
		return kNull;
	}
	else if (fStatus==obj.getStatus())
	{
		return fStatus;
	}
	else
	{
		return kNull;
	}
			
}
