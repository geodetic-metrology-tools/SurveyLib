//  TTerrestrialReferenceFrame.h
/*
© Copyright CERN 2000-2021. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** A Terrestrial reference frame like ETRF or ITRF
	Specific solution at specific epoch



*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_TERRESTRIAL_REFERENCE_FRAME
#define SU_TERRESTRIAL_REFERENCE_FRAME


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  "TA3DEuclideanRefFrame.h"

//
//
////////////////////////////////////////////////////////////////


/*! \ingroup spatialobjects
	@{*/

//! A Geocentric terrestrial Reference Frame
class TTerrestrialReferenceFrame : public TA3DEuclideanRefFrame //: public TObject  
{

public:
	TTerrestrialReferenceFrame();
	~TTerrestrialReferenceFrame();

private:

};


#endif // SU_TERRESTRIAL_REFERENCE_FRAME
