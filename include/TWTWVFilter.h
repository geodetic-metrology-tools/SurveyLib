// TWTWVFilter.h
//
// Concrete Class of the TWTWFilter PABC.
// Handles the IO of an TWireToWireDistMeas object for the case
// where there is only a vertical distance
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TLGCTStream object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


#ifndef SU_TWTWVFilter
#define SU_TWTWVFilter


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
class  TWTWVFilter : public TWTWFilter  
{
	//constants
public:

	//member functions
	static	TWTWVFilter *instance();
	virtual void input(TLGCTStream &, TWireToWireDistMeas&) const;

protected:
	// constructors and destructors
	TWTWVFilter();
	virtual ~TWTWVFilter();

private:
	// member attributes
	static TWTWVFilter	*fFilter;

	//copy constructor declaration
	TWTWVFilter(const TWTWVFilter&);
	
	//ClassDef(TWTWTFilter, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

#endif // SU_TWTWVFilter


