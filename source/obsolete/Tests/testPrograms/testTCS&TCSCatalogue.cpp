// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿//////////////////////////////////////////////////////
// test file for TCS et TCSCatalogue
//////////////////////////////////////////////////////
#include <string>
using namespace std;
#include "TLength.h"
#include "TAngle.h"
#include <iostream>
#include <iomanip>
#include "TSpatialPosition.h"
#include "TCoordinateSystemCatalogue.h"
#include "TCoordinateSystem.h"
#include "TCoorSysCatWrapper.h"




void main ()
{
	TCoordinateSystemCatalogue *catalogue = TCoordinateSystemCatalogue::Instance();
	TCoordinateSystem *geodetic;
	//geodetic = new TCoordinateSystem(TCoordinateSystem::kGeodetic);
	geodetic = catalogue->getCoordSys(TCoordinateSystem::kGeodetic);
	cout<<geodetic->getName()<<endl;
	cout<<geodetic->getFirstCoordToken()<<endl;

}
