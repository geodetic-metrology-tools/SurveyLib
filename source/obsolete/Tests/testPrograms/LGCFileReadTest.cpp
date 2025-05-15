// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#pragma warning(disable:4786)

#include "TEDMStation.h"
#include "TEDMDistROM.h"
#include "TLevelStation.h"
#include "TWTWDistStation.h"
#include "TVerticalDistROM.h"
#include "TLGCDataSet.h"
#include "QFile.h"
#include "QTextStream.h"
#include "TLGCTStream.h"

#include "TLGCFileReader.h"
#include "TWorkingStations.h"

void main(){

	TLGCDataSet ds;

	QFile inFile("c:\\Temp\\testlgc2\\testlgcfr.dat");

	if (inFile.open(IO_ReadOnly)){

	TLGCFileReader lgcFR(&ds, &inFile);

	lgcFR.readLGCFile();

	inFile.close();

	//Check Points
	TWorkingPoints::PointIterator iterPti = ds.getWorkingPoints()->getPointsBeginIterator();
	iterPti++;
	iterPti++;
	iterPti++;
	iterPti++;

	//Check EDMS
	TWorkingStations::EDMStIterator iterEDMSt = ds.getWorkingStations()->getEDMStBeginIterator();

	TEDMDistROM::EDMDistMeasIterator iterEDM = 
		iterEDMSt->getEDMDistROMBeginIterator()->getDistMeasBeginIterator();

	iterEDMSt++;
	iterEDM = iterEDMSt->getEDMDistROMBeginIterator()->getDistMeasBeginIterator();
	iterEDMSt++;
	iterEDM = iterEDMSt->getEDMDistROMBeginIterator()->getDistMeasBeginIterator();
	iterEDMSt++;
	iterEDM = iterEDMSt->getEDMDistROMBeginIterator()->getDistMeasBeginIterator();
	}


	//Check leveling
	TWorkingStations::LevelStIterator lSt = ds.getWorkingStations()->getLevelStBeginIterator();

	TLevelStation::VertDistROMIterator vdRom = lSt->getVertDistROMBeginIterator();

	TVerticalDistROM::VertDistMeasIterator vd = vdRom->getVertDistMeasBeginIterator();
	vd++;
	vd++;

	vdRom++;
	
	vd = vdRom->getVertDistMeasBeginIterator();

	vdRom++;

	vd = vdRom->getVertDistMeasBeginIterator();
	vd++;
	vd++;


	//Check angles
	TWorkingStations::TheodStIterator tSt = ds.getWorkingStations()->getTheodStBeginIterator();

	TTheodoliteStation::HorAngROMIterator haRom = tSt->getHorAngROMBeginIterator();

	THorAngleROM::HorAngMeasIterator ha = haRom->getHorAngMeasBeginIterator();
	ha++;
	ha++;

	tSt++;
	haRom = tSt->getHorAngROMBeginIterator();
	ha = haRom->getHorAngMeasBeginIterator();

	//Check offsets
	TWorkingStations::WPSStIterator wpsSt = ds.getWorkingStations()->getWPSStBeginIterator();

	TWPSStation::WPSMeasIterator wps = wpsSt->getWPSMeas();

	wpsSt++;
	wps = wpsSt->getWPSMeas();

	wpsSt++;
	wps = wpsSt->getWPSMeas();

	wpsSt++;
	wps = wpsSt->getWPSMeas();

	wpsSt++;
	wps = wpsSt->getWPSMeas();

	wpsSt++;
	wps = wpsSt->getWPSMeas();



	//Check WTWs
	TWorkingStations::WTWStIterator wtwSt = ds.getWorkingStations()->getWTWStBeginIterator();

	TWTWDistStation::WTWDistMeasIterator wtw = wtwSt->getWTWDistMeas();

	wtwSt++;
	wtw = wtwSt->getWTWDistMeas();

	wtwSt++;
	wtw = wtwSt->getWTWDistMeas();

	wtwSt++;
	wtw = wtwSt->getWTWDistMeas();

	wtwSt++;
	wtw = wtwSt->getWTWDistMeas();

	wtwSt++;
	wtw = wtwSt->getWTWDistMeas();


/*
	//output test
	QFile outFile("c:\\Temp\\testlgc2\\testlgcfrOut.dat");

	if (outFile.open(IO_WriteOnly)){

		TLGCTStream* lgcStream = new TLGCTStream( new QTextStream(&outFile));

		TPointFormat ptf(6, 7, TPointFormat::kCm, 10, TPointFormat::kUm, false);

		(static_cast< TAQtStreamFormatter* >(lgcStream))->operator<<(ptf);

		TWorkingPoints::PointIterator iterPt = ds.getWorkingPoints()->getPointsBeginIterator();

		*lgcStream << *iterPt << '\n';
		iterPt++;

		*lgcStream << *iterPt << '\n';
		iterPt++;

		*lgcStream << *iterPt << '\n';
		iterPt++;

		*lgcStream << *iterPt << '\n';
	}

	outFile.close();
*/

}

