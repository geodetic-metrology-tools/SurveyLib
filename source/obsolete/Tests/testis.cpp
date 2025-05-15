// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

//#include "TInstrumentStation.h"
#include "TTheodoliteStation.h"
#include "TEDMStation.h"
#include "TWorkingPoints.h"
#include "TReferenceFrame.h"
#include "TWorkingStations.h"
#include "UEOIndices.h"

#include "TLGCDataSet.h"

#include <iostream>


void main(){

	TLGCDataSet lgcDS;
	TWorkingPoints* wp = lgcDS.getWorkingPoints();
	TWorkingStations* ws = lgcDS.getWorkingStations();

	TWorkingPoints::PointIterator iterPt;

	TReferenceFrame rf;
	TSpatialPoint* sp;
	TSpatialPointName* spn;
	
	//pta
	TSpatialPosition* pa = new TSpatialPosition(100.000, 200.000, 300.0, rf);
	pa->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	spn = new TSpatialPointName("pt", "a", "xxx");
	sp = new TSpatialPoint(*spn, pa);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptb
	TSpatialPosition* pb = new TSpatialPosition(200.000, 300.000, 400.0, rf);
	pb->setPositionStatus(TSpatialPosition::EPositionStatus::kVyz);
	spn = new TSpatialPointName("pt", "b", "xxx");
	sp = new TSpatialPoint(*spn, pb);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptc
	TSpatialPosition* pc = new TSpatialPosition(300.000, 400.000, 500.0, rf);
	pc->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	spn = new TSpatialPointName("pt", "c", "xxx");
	sp = new TSpatialPoint(*spn, pc);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	iterPt = wp->getPointsBeginIterator();

	//ptd
	TSpatialPosition* pd = new TSpatialPosition(500.000, 600.000, 700.0, rf);
	pd->setPositionStatus(TSpatialPosition::EPositionStatus::kVyz);
	spn = new TSpatialPointName("pt", "d", "xxx");
	sp = new TSpatialPoint(*spn, pd);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//pte
	TSpatialPosition* pe = new TSpatialPosition(600.000, 700.000, 800.0, rf);
	pe->setPositionStatus(TSpatialPosition::EPositionStatus::kVyz);
	spn = new TSpatialPointName("pt", "e", "xxx");
	sp = new TSpatialPoint(*spn, pe);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptf
	TSpatialPosition* pf = new TSpatialPosition(700.000, 800.000, 900.0, rf);
	pf->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	spn = new TSpatialPointName("pt", "f", "xxx");
	sp = new TSpatialPoint(*spn, pf);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptg
	TSpatialPosition* pg = new TSpatialPosition(800.000, 900.000, 1000.0, rf);
	pg->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "g", "xxx");
	sp = new TSpatialPoint(*spn, pg);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//pth
	TSpatialPosition* ph = new TSpatialPosition(900.000, 1000.000, 1100.0, rf);
	ph->setPositionStatus(TSpatialPosition::EPositionStatus::kVxz);
	spn = new TSpatialPointName("pt", "h", "xxx");
	sp = new TSpatialPoint(*spn, ph);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//pti
	TSpatialPosition* pi = new TSpatialPosition(1000.000, 1100.000, 1200.0, rf);
	pi->setPositionStatus(TSpatialPosition::EPositionStatus::kVy);
	spn = new TSpatialPointName("pt", "i", "xxx");
	sp = new TSpatialPoint(*spn, pi);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptj
	TSpatialPosition* pj = new TSpatialPosition(1100.000, 1200.000, 1300.0, rf);
	pj->setPositionStatus(TSpatialPosition::EPositionStatus::kVz);
	spn = new TSpatialPointName("pt", "j", "xxx");
	sp = new TSpatialPoint(*spn, pj);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptk
	TSpatialPosition* pk = new TSpatialPosition(1200.000, 1300.000, 1400.0, rf);
	pk->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "k", "xxx");
	sp = new TSpatialPoint(*spn, pk);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptl
	TSpatialPosition* pl = new TSpatialPosition(1300.000, 1400.000, 1500.0, rf);
	pl->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "l", "xxx");
	sp = new TSpatialPoint(*spn, pl);
	wp->addPoint(sp);
	delete sp;
	delete spn;

///
/// Point Iterators
	iterPt = wp->getPointsBeginIterator();
	TWorkingPoints::PointIterator iPta = iterPt;
	TWorkingPoints::PointIterator iPtb = ++iterPt;
	TWorkingPoints::PointIterator iPtc = ++iterPt;
	TWorkingPoints::PointIterator iPtd = ++iterPt;
	TWorkingPoints::PointIterator iPte = ++iterPt;
	TWorkingPoints::PointIterator iPtf = ++iterPt;
	TWorkingPoints::PointIterator iPtg = ++iterPt;
	TWorkingPoints::PointIterator iPth = ++iterPt;
	TWorkingPoints::PointIterator iPti = ++iterPt;
	TWorkingPoints::PointIterator iPtj = ++iterPt;
	TWorkingPoints::PointIterator iPtk = ++iterPt;
	TWorkingPoints::PointIterator iPtl = ++iterPt;




	TAngle alpha;
	alpha.setGonsValue(146.234);
	TAngle sigal;
	sigal.setGonsValue(0.002);

//ST1
	iterPt = wp->getPoint(TSpatialPointName("pt", "a", "xxx"));
	TTheodoliteStation* thSt = new TTheodoliteStation(ws, iterPt);
	delete thSt;

	TWorkingStations::TheodStIterator iterTh = ws->getTheodStBeginIterator();

//ROM11
	THorAngleROM* haRom = new THorAngleROM(*iterTh);
	delete haRom;

	TTheodoliteStation::HorAngROMIterator iterHAR= iterTh->getHorAngROMBeginIterator();

	//reference measurement
	iterPt = wp->getPoint(TSpatialPointName("pt", "c", "xxx"));
	THorAngleMeasurement* ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "b", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
 	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "d", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "e", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

//ROM12
	haRom = new THorAngleROM(*iterTh);
	delete haRom;

	iterHAR++;

	//reference measurement
	iterPt = wp->getPoint(TSpatialPointName("pt", "f", "xxx"));

	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "c", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "g", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	//************debug begin
	THorAngleROM::HorAngMeasIterator debugIter = iterHAR->getHorAngMeasBeginIterator();
	debugIter++;
	debugIter++;
	//************debug end

	iterPt = wp->getPoint(TSpatialPointName("pt", "h", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;




//ROM13
	haRom = new THorAngleROM(*iterTh);
	delete haRom;

	iterHAR++;

	//reference measurement
	iterPt = wp->getPoint(TSpatialPointName("pt", "g", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "f", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "i", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "j", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

//ST2
	iterPt = wp->getPoint(TSpatialPointName("pt", "c", "xxx"));
	TEDMStation* edmSt = new TEDMStation(ws, iterPt);
	delete edmSt; 

	TWorkingStations::EDMStIterator iterEDMSt = ws->getEDMStBeginIterator();

	TEDMDistROM* edmRom = new TEDMDistROM(*iterEDMSt);
	delete edmRom;

	TEDMStation::EDMDistROMIterator iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	iterPt = wp->getPoint(TSpatialPointName("pt", "k", "xxx"));
	TEDMDistMeasurement* edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, 171.400, 0.033);
	delete edmDist;

	iterPt = wp->getPoint(TSpatialPointName("pt", "a", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, 171.400, 0.033);
	delete edmDist;

	iterPt = wp->getPoint(TSpatialPointName("pt", "b", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, 171.400, 0.033);
	delete edmDist;

	iterPt = wp->getPoint(TSpatialPointName("pt", "d", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, 171.400, 0.033);
	delete edmDist;


//ST3
	iterPt = wp->getPoint(TSpatialPointName("pt", "f", "xxx"));
	thSt = new TTheodoliteStation(ws, iterPt);
	delete thSt;

	iterTh++;

//ROM31
	haRom = new THorAngleROM(*iterTh);
	delete haRom;

	iterHAR= iterTh->getHorAngROMBeginIterator();

	//rewference meas
	iterPt = wp->getPoint(TSpatialPointName("pt", "h", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "c", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "g", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

//ROM32
	haRom = new THorAngleROM(*iterTh);
	delete haRom;

	iterHAR++;

	//reference meas
	iterPt = wp->getPoint(TSpatialPointName("pt", "c", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "a", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "e", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "g", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;
	
	iterPt = wp->getPoint(TSpatialPointName("pt", "h", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "i", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "j", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;

	iterPt = wp->getPoint(TSpatialPointName("pt", "k", "xxx"));
	ha = new THorAngleMeasurement(*iterHAR, iterPt, alpha, sigal);
	delete ha;



//Theodolite related iterators
	iterTh = ws->getTheodStBeginIterator();
	TWorkingStations::TheodStIterator iT1 = iterTh;
	TWorkingStations::TheodStIterator iT3 = ++iterTh;

	//ST1
	iterHAR = iT1->getHorAngROMBeginIterator();
	TTheodoliteStation::HorAngROMIterator irom11 = iterHAR;
	TTheodoliteStation::HorAngROMIterator irom12 = ++iterHAR;
	TTheodoliteStation::HorAngROMIterator irom13 = ++iterHAR;

	THorAngleROM::HorAngMeasIterator iterHA = irom11->getHorAngMeasBeginIterator();
	THorAngleROM::HorAngMeasIterator iterR11 = iterHA;
	THorAngleROM::HorAngMeasIterator iterH111 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH112 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH113 = ++iterHA;

	iterHA = irom12->getHorAngMeasBeginIterator();
	THorAngleROM::HorAngMeasIterator iterR12 = iterHA;
	THorAngleROM::HorAngMeasIterator iterH121 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH122 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH123 = ++iterHA;

	iterHA = irom13->getHorAngMeasBeginIterator();
	THorAngleROM::HorAngMeasIterator iterR13 = iterHA;
	THorAngleROM::HorAngMeasIterator iterH131 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH132 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH133 = ++iterHA;

	//ST3
	iterHAR = iT3->getHorAngROMBeginIterator();
	TTheodoliteStation::HorAngROMIterator irom31 = iterHAR;
	TTheodoliteStation::HorAngROMIterator irom32 = ++iterHAR;

	iterHA = irom31->getHorAngMeasBeginIterator();
	THorAngleROM::HorAngMeasIterator iterR31 = iterHA;
	THorAngleROM::HorAngMeasIterator iterH311 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH312 = ++iterHA;

	iterHA = irom32->getHorAngMeasBeginIterator();
	THorAngleROM::HorAngMeasIterator iterR32 = iterHA;
	THorAngleROM::HorAngMeasIterator iterH321 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH322 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH323 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH324 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH325 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH326 = ++iterHA;
	THorAngleROM::HorAngMeasIterator iterH327 = ++iterHA;

//EDM related

	TEDMDistROM::EDMDistMeasIterator iterD = iterEDMrom->getDistMeasBeginIterator();
	TEDMDistROM::EDMDistMeasIterator iterD211 = iterD;
	TEDMDistROM::EDMDistMeasIterator iterD212 = ++iterD;
	TEDMDistROM::EDMDistMeasIterator iterD213 = ++iterD;
	TEDMDistROM::EDMDistMeasIterator iterD214 = ++iterD;

	iterEDMSt->disactivate();
	iterD213->disactivate();
	iterD213->activate();

	
}

