// TWPSTFilter.h
//
// Concrete Class of the TWPSFilter PABC.
// Handles the IO of an TWPSMeasurement object for the case
// where there is only a transverse offset
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TLGCTStream object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


#ifndef SU_TWPSTFilter
#define SU_TWPSTFilter


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
class  TWPSTFilter : public TWPSFilter  
{
	//constants
public:

	//member functions
	static	TWPSTFilter *instance();
	//virtual void input(TLGCTStream &, TWPSMeasurement&) const;
	virtual void input(TAStreamFormatter&, TWPSMeasurement&) const;

protected:
	// constructors and destructors
	TWPSTFilter();
	virtual ~TWPSTFilter();

private:
	// member attributes
	static TWPSTFilter	*fFilter;

	//copy constructor declaration
	TWPSTFilter(const TWPSTFilter&);
	
	//ClassDef(TWPSTFilter, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

#endif // SU_TWPSTFilter



