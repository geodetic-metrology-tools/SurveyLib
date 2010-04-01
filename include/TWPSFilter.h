// TWPSFilter.h: 
//
// Purely Abstract Base Class (Interface) for a TWPSFilter.
// Handles the IO of an TWPSMeasurement object for all transverse/vertical
// combinations. A different concrete class exists for each of these cases.
// 
// Patterns:
// Works as a Strategy of a TLGCTStreamFormatter object. 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////




#ifndef SU_TWPSFilter
#define SU_TWPSFilter


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
//class  TLGCTStream;
class TAStreamFormatter;
class TWPSMeasurement;
//#include  "**classname**.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TWPSFilter //: public TObject  
{
public:

	enum EWPSMeasType{kTrans, kVert, k2D};

	///inputs a TWPSMeasurement object
	//virtual void input(TLGCTStream&, TWPSMeasurement&) const = 0;
	virtual void input(TAStreamFormatter&, TWPSMeasurement&) const = 0;

private:

	//ClassDef(TWPSFilter, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_TWPSFilter
