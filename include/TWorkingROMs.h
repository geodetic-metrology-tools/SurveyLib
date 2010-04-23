// 
// TWorkingROMs.h : Header File
//

//

#ifndef SU_WORKING_ROMS
#define SU_WORKING_ROMS

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

#include "Scale.h"

#include <list>
using namespace std;

#include "ObservationROM.h"
#include "VerticalDistanceROM.h"
#include "OffsetToVerticalLineROM.h"
#include "OffsetToSpatialLineROM.h"

//!Class storing all the instruments
class TWorkingROMs
{
public:

	const list<const OffsetToLineOrPlaneROM*>& getOffsetToVerticalPlaneROMs() const { return offsetToVerticalPlaneROMs; }

	void addOffsetToVerticalPlaneROM(const OffsetToLineOrPlaneROM* rom) { offsetToVerticalPlaneROMs.push_back(rom); }

	const list<const OffsetToVerticalLineROM*>& getOffsetToVerticalLineROMs() const { return offsetToVerticalLineROMs; }

	void addOffsetToVerticalLineROM(const OffsetToVerticalLineROM* rom) { offsetToVerticalLineROMs.push_back(rom); }

	const list<const OffsetToSpatialLineROM*>& getOffsetToSpatialLineROMs() const { return offsetToSpatialLineROMs; }

	void addOffsetToSpatialLineROM(const OffsetToSpatialLineROM* rom) { offsetToSpatialLineROMs.push_back(rom); }

	const list<const VerticalDistanceROM*>& getVerticalDistanceROMs() const { return verticalDistanceROMs; }

	void addVerticalDistanceROM(const VerticalDistanceROM* rom) { verticalDistanceROMs.push_back(rom); }

private :

	list<const OffsetToLineOrPlaneROM*> offsetToVerticalPlaneROMs;
	list<const OffsetToVerticalLineROM*> offsetToVerticalLineROMs;
	list<const OffsetToSpatialLineROM*> offsetToSpatialLineROMs;
	list<const VerticalDistanceROM*> verticalDistanceROMs;

};

#endif
