// TVNumericValue.h
//
/** Virtual class for Numerical Value */
//
// Patterns:
//
// 
// Copyright 2002 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_NUMERIC_VALUE
#define SU_V_NUMERIC_VALUE


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Quad.h"
extern "C" {
_Quad __sqrtq (_Quad x);
_Quad __sinq (_Quad x);
_Quad __cosq (_Quad x);
_Quad __fabsq (_Quad x);
_Quad __modfq (_Quad x, _Quad* y);
_Quad __acosq (_Quad x);
_Quad __asinq (_Quad x);
_Quad __atan2q (_Quad x, _Quad y);
_Quad __powq (_Quad x, _Quad y);
_Quad __tanq(_Quad x);
_Quad __coshq(_Quad x);
_Quad __sinhq(_Quad x);
_Quad __tanhq(_Quad x);
_Quad __atanq(_Quad x);
_Quad __logq(_Quad x);
_Quad __ceilq(_Quad x);
_Quad __floorq(_Quad x);
}


////////////////////////////////////////////////////////////////
// Forward declarations
//
 class TANumericValue;
//using namespace std;
//
//
//typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TVNumericValue  //: public TObject

{
public:
	/**@name Constants */
	//@{
		enum  EStatus {kNull, kKnown};
	//@}

	virtual	EStatus	getStatus()const =0 ;

	virtual void setStatus(EStatus)=0;

	virtual bool isNull() const=0;

	virtual ~TVNumericValue() { }






	//ClassDef(TVNumericValue, 1)
};
#endif // SU_V_NUMERIC_VALUE
