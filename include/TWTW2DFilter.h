// TWTW2DFilter.h
//
// Concrete Class of the TWTWFilter PABC.
// Handles the IO of an TWireToWireDistMeas object for the case
// where there are both a horizontal and a vertical distance measurements
//
// Patterns:
// This class is a Singleton.
// Works as a Strategy of a TLGCTStream object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////


#ifndef SU_TWTW2DFilter
#define SU_TWTW2DFilter


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
class  TWTW2DFilter : public TWTWFilter  
{
	//constants
public:

	//member functions
	static	TWTW2DFilter *instance();
	virtual void input(TLGCTStream &, TWireToWireDistMeas&) const;

protected:
	// constructors and destructors
	TWTW2DFilter();
	virtual ~TWTW2DFilter();

private:
	// member attributes
	static TWTW2DFilter	*fFilter;

	//copy constructor declaration
	TWTW2DFilter(const TWTW2DFilter&);
	
	//ClassDef(TWTWTFilter, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

#endif // SU_TWTWTFilter



