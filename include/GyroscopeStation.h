// GyroscopeStation.h


#ifndef SU_GYRO_STATION
#define SU_GYRO_STATION

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Station.h"
#include "TAngleConstants.h"
#include "ObservationROM.h"


#include <list>
using namespace std;

class GyroscopeStation : public Station
{

public:

	GyroscopeStation(const TSpatialPoint* sp, const TLength* ics, const TAngleConstants* consts, const TGyroOrientationROM* r) : Station(sp, NULL, NULL, false, ics, -1)
	{
		rom = r;
		constant = consts;
	}

	~GyroscopeStation()
	{
		delete rom;
		delete constant;
	}

	const TGyroOrientationROM* getGyroscopeROM() const { return rom; }

	const TAngleConstants* getAngleConstant() const { return constant; }

private:

	const TGyroOrientationROM* rom;

	const TAngleConstants* constant;
};

#endif //SU_GYRO_STATION
