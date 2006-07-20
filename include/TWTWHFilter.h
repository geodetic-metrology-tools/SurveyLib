// TWTWHFilter.h
//
// Concrete Class of the TWTWFilter PABC.
// Handles the IO of an TWireToWireDistMeas object for the case
// where there is only a horizontal distance
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TLGCTStream object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


#ifndef SU_TWTWHFilter
#define SU_TWTWHFilter


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
//class  **classname**;
#include  "TWTWFilter.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TWTWHFilter : public TWTWFilter  
{
	//constants
public:

	//member functions
	static	TWTWHFilter *instance();
	virtual void input(TLGCTStream &, TWireToWireDistMeas&) const;

protected:
	// constructors and destructors
	TWTWHFilter();
	virtual ~TWTWHFilter();

private:
	// member attributes
	static TWTWHFilter	*fFilter;

	//copy constructor declaration
	TWTWHFilter(const TWTWHFilter&);
	
	//ClassDef(TWTWTFilter, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

#endif // SU_TWTWTFilter



