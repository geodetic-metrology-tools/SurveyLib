//
// OffsetToTheodolitePlaneROM.h : header file
/*! Class for a horizontal angle round of measurements

    Patterns:
  
    Copyright 2002 CERN EST/SU. All rights reserved.
*/
////////////////////////////////////////////////////////////////////////


#ifndef SU_OTHEOPLANE_ROM
#define SU_OTHEOPLANE_ROM

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

#include <list>
using namespace std;

#include "TOffsetToTheoPlaneMeasurement.h"
#include "Scale.h"

//! Class for a round of horizontal angle measurements
class OffsetToTheodolitePlaneROM
{ 
public:

	OffsetToTheodolitePlaneROM(const Scale* scl, const TAngle* angle)
	{
		scale = scl;
		measuredAngle = angle;
	}

	~OffsetToTheodolitePlaneROM()
	{
		list<const TOffsetToTheoPlaneMeasurement*>::iterator iter = offsetToTheodolitePlaneMeasurements.begin();

		while (iter != offsetToTheodolitePlaneMeasurements.end())
		{
			delete *iter;
			iter++;
		}

		delete measuredAngle;
	}

	const list<const TOffsetToTheoPlaneMeasurement*>& getOffsetToTheodolitePlaneMeasurements() const { return offsetToTheodolitePlaneMeasurements; }

	void addMeasurement(const TOffsetToTheoPlaneMeasurement* meas) { offsetToTheodolitePlaneMeasurements.push_back(meas); }

private:

	const Scale* scale;
	const TAngle* measuredAngle;
	list<const TOffsetToTheoPlaneMeasurement*> offsetToTheodolitePlaneMeasurements;

};

#endif
