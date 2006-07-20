// TWPS2DFilter.h
//
// Concrete Class of the TWPSFilter PABC.
// Handles the IO of an TWPSMeasurement object for the case
// where there are both transverse and vertical offsets
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TLGCTStream object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


#ifndef SU_TWPS2DFilter
#define SU_TWPS2DFilter


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
class  TWPS2DFilter : public TWPSFilter  
{

public:
	//constants

	//member functions
	static	TWPS2DFilter *instance();
	virtual void input(TLGCTStream &, TWPSMeasurement&) const;

protected:
	// constructors and destructors
	TWPS2DFilter();
	virtual ~TWPS2DFilter();

private:
	// member attributes
	static TWPS2DFilter	*fFilter;

	//copy constructor declaration
	TWPS2DFilter(const TWPS2DFilter&);
	
	//ClassDef(TWPS2DFilter, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TWPS2DFilter
