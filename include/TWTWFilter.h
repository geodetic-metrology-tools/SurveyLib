// TWTWFilter.h: 
//
// Purely Abstract Base Class (Interface) for a TWTWFilter.
// Handles the IO of an TWireToWireDistMeas object for all horizontal/vertical
// combinations. A different concrete class exists for each of these cases.
// 
// Patterns:
// Works as a Strategy of a TLGCTStreamFormatter object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////




#ifndef SU_TWTWFilter
#define SU_TWTWFilter


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
class  TLGCTStream;
class TWireToWireDistMeas;
//#include  "**classname**.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TWTWFilter //: public TObject  
{
public:

	enum EWTWMeasType{kHoriz, kVert, k2D};

	///inputs a TWireToWireDistMeas object
	virtual void input(TLGCTStream&, TWireToWireDistMeas&) const = 0;

private:

	//ClassDef(TWTWFilter, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_TWTWFilter
