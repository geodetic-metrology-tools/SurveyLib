//
// OffsetToSpatialLineROM.cpp
/*!

    Patterns:
  
    Copyright 2002 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////////////////////


#include "OffsetToSpatialLineROM.h"

OffsetToSpatialLineROM::OffsetToSpatialLineROM(const TSpatialPoint* firstPointOnLine, const TSpatialPoint* secondPointOnLine)
{
	this->firstPointOnLine = firstPointOnLine;
	this->secondPointOnLine = secondPointOnLine;
}
