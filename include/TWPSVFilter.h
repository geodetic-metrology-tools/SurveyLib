// TWPSVFilter.h
//
// Concrete Class of the TWPSFilter PABC.
// Handles the IO of an TWPSMeasurement object for the case
// where there is only a vertical offset
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TLGCTStream object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


#ifndef SU_TWPSVFilter
#define SU_TWPSVFilter


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
#include  "TWPSFilter.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TWPSVFilter : public TWPSFilter  
{
	//constants
public:

	//member functions
	static	TWPSVFilter *instance();
	virtual void input(TLGCTStream &, TWPSMeasurement&) const;

protected:
	// constructors and destructors
	TWPSVFilter();
	virtual ~TWPSVFilter();

private:
	// member attributes
	static TWPSVFilter	*fFilter;

	//copy constructor declaration
	TWPSVFilter(const TWPSVFilter&);
	
	//ClassDef(TWPSVFilter, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

#endif // SU_TWPSVFilter
