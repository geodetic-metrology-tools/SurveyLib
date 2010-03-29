// TVNumericValue.h
//
/** Virtual class for Numerical Value */
//
// Patterns:
//
// 
// Copyright 2002-10 CERN SU, M.Jones. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_NUMERIC_VALUE
#define SU_V_NUMERIC_VALUE


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Quad.h"
#if __INTEL_COMPILER
#include	<mathimf.h>
#else
#include <math.h>
#endif

#if __INTEL_COMPILER
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

#define sqrtq __sqrtq
#define sinq __sinq
#define cosq __cosq
#define fabsq __fabsq
#define modfq __modfq
#define acosq __acosq
#define asinq __asinq
#define atan2q __atan2q
#define powq __powq
#define tanq __tanq
#define coshq __coshq
#define sinhq __sinhq
#define tanhq __tanhq
#define atanq __atanq
#define logq __logq
#define ceilq __ceilq
#define floorq __floorq

#define LITERAL(x) x ## q

#else

#define sqrtq sqrt
#define sinq sin
#define cosq cos
#define fabsq fabs
#define modfq modf
#define acosq acos
#define asinq asin
#define atan2q atan2
#define powq pow
#define tanq tan
#define coshq cosh
#define sinhq sinh
#define tanhq tanh
#define atanq atan
#define logq log
#define ceilq ceil
#define floorq floor

#define LITERAL(x) x

#endif


////////////////////////////////////////////////////////////////
// Forward declarations
//
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
		enum  EStatus { kNull, kKnown };
	//@}

	virtual	EStatus	getStatus() const = 0 ;

	virtual void setStatus( EStatus ) = 0;

	virtual bool isNull() const = 0;

	virtual ~TVNumericValue() { }






	//ClassDef(TVNumericValue, 1)
};
#endif // SU_V_NUMERIC_VALUE
