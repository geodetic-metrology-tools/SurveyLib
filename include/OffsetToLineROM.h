//
// OffsetToLineROM.h : header file
/*! 

    Patterns:
  
    Copyright 2003 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////////////////////


#ifndef SU_OFFSET_LINE_ROM
#define SU_OFFSET_LINE_ROM

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

#include "OffsetToLineOrPlaneROM.h"
#include "TPositionVector.h"
#include "TFreeVector.h"

/*! \ingroup spatialmeasurements
	@{*/

class OffsetToLineROM : public OffsetToLineOrPlaneROM
{ 

public:

	~OffsetToLineROM()
	{
		delete origin;
		delete unit;
	}

	TPositionVector* getOrigin() const { return origin; }

	TFreeVector* getUnit() const { return unit; }

private:

	TPositionVector* origin;
	TFreeVector* unit;

};


#endif

