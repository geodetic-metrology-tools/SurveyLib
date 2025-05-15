// SPDX-FileCopyrightText: 2025 CERN

// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TEDMStation.h"
#include "TEDMDistROM.h"
#include "TEDMDistMeasurement.h"
#include "TAngle.h"
#include "TWorkingPoints.h"
#include "TSpatialPoint.h"
#include "TSpatialPosition.h"
#include "TEuclideanRefFrame.h"

#include "TWorkingStations.h"
#include "UEOIndices.h"
#include "TLSInputMatricesFiller.h"

#include "TLGCDataSet.h"
#include "TLSCalcDataSet.h"

#include "TLSCalculation.h"

#include <iostream>


void main(){

	TLGCDataSet lgcDS;
	TWorkingPoints* wp = lgcDS.getWorkingPoints();
	TWorkingStations* ws = lgcDS.getWorkingStations();

	TWorkingPoints::PointIterator iterPt;

	TEuclideanRefFrame erf("Temporary");
	TSpatialPoint* sp;
	TSpatialPointName* spn;
	//pt1
	TPositionVector pv1(7306.080, 2262.270, 0.0);
	TSpatialPosition* p1 = new TSpatialPosition(&erf);
	p1->setXYZ(pv1);
	p1->setPositionStatus(TPositionStatus::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "1", "xxx");
	sp = new TSpatialPoint(*spn, p1);
	wp->addPoint(sp);
	delete sp;
	delete spn;
	//pt2
	TPositionVector pv2(7435.890, 2091.880, 0.0);
	TSpatialPosition* p2 = new TSpatialPosition(&erf);
	p2->setXYZ(pv2);
	p2->setPositionStatus(TPositionStatus::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "2", "xxx");
	sp = new TSpatialPoint(*spn, p2);
	wp->addPoint(sp);
	delete sp;
	delete spn;
	//pt3
	TPositionVector pv3(7147.450, 2056.830, 0.0);
	TSpatialPosition* p3 = new TSpatialPosition(&erf);
	p3->setXYZ(pv3);
	p3->setPositionStatus(TPositionStatus::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "3", "xxx");
	sp = new TSpatialPoint(*spn, p3);
	wp->addPoint(sp);
	delete sp;
	delete spn;
	//pt4
	TPositionVector pv4(7173.300, 2196.320, 0.0);
	TSpatialPosition* p4 = new TSpatialPosition(&erf);
	p4->setXYZ(pv4);
	p4->setPositionStatus(TPositionStatus::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "4", "xxx");
	sp = new TSpatialPoint(*spn, p4);
	wp->addPoint(sp);
	delete sp;
	delete spn;
	//ptM
	TPositionVector pvm(7289.780, 2152.360, 0.0);
	TSpatialPosition* pM = new TSpatialPosition(&erf);
	pM->setXYZ(pvm);
	pM->setPositionStatus(TPositionStatus::EPositionStatus::kVxy);
	spn = new TSpatialPointName("pt", "M", "xxx");
	sp = new TSpatialPoint(*spn, pM);
	wp->addPoint(sp);
	delete sp;
	delete spn;


//ST1
	iterPt = wp->getPoint(TSpatialPointName("pt", "1", "xxx"));
	TEDMStation* edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	TWorkingStations::EDMStIterator iterEDMSt = ws->getEDMStBeginIterator();
	
//ROM11
	TEDMDistROM* edmRom = new TEDMDistROM(*iterEDMSt);
	TEDMStation::EDMDistROMIterator iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	iterPt = wp->getPoint(TSpatialPointName("pt", "M", "xxx"));
	TEDMDistMeasurement* edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(111.080), TLength(0.026));

	delete edmDist;


//ST2
	iterPt = wp->getPoint(TSpatialPointName("pt", "2", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);
	delete edmSt;

//ROM21
	iterEDMSt ++;
	edmRom= new TEDMDistROM(*iterEDMSt);
	delete edmRom;

	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	iterPt = wp->getPoint(TSpatialPointName("pt", "M", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, TLength(158.200), TLength(0.031));

	delete edmDist;

//ST3
	iterPt = wp->getPoint(TSpatialPointName("pt", "3", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);
	delete edmSt;

//ROM31
	iterEDMSt++;
	edmRom = new TEDMDistROM(*iterEDMSt);
	delete edmRom;

	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	iterPt = wp->getPoint(TSpatialPointName("pt", "M", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, TLength(171.400), TLength(0.033));

	delete edmDist;

//ST4
	iterPt = wp->getPoint(TSpatialPointName("pt", "4", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);
	delete edmSt;
//ROM41
	iterEDMSt++;
	edmRom = new TEDMDistROM(*iterEDMSt);
	delete edmRom;

	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	iterPt = wp->getPoint(TSpatialPointName("pt", "M", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, TLength(124.490), TLength(0.028));

	delete edmDist;

//ST5
	iterPt = wp->getPoint(TSpatialPointName("pt", "3", "xxx"));
	TTheodoliteStation* ThSt = new TTheodoliteStation(ws, iterPt);
	delete ThSt;

	TWorkingStations::TheodStIterator iterTh = ws->getTheodStBeginIterator();

//ROM51
	THorAngleROM* HARom = new THorAngleROM(*iterTh);
	delete HARom;

	TTheodoliteStation::HorAngROMIterator iterHArom = iterTh->getHorAngROMBeginIterator();

	TAngle l1;
	l1.setGonsValue(146.234);
	TAngle sigml1;
	sigml1.setGonsValue(0.002);
	iterPt = wp->getPoint(TSpatialPointName("pt", "2", "xxx"));
	THorAngleMeasurement* hang = new THorAngleMeasurement(*iterHArom, iterPt, l1, sigml1);
	delete hang;

	TAngle l2;
	l2.setGonsValue(116.302);
	TAngle sigml2;
	sigml2.setGonsValue(0.002);

	iterPt = wp->getPoint(TSpatialPointName("pt", "M", "xxx"));
	hang = new THorAngleMeasurement(*iterHArom, iterPt, l2, sigml2);
	delete hang;

	iterPt = wp->getPointsBeginIterator();
	while (iterPt != wp->getPointsEndIterator())
		iterPt++;

/*	TWorkingStations::TheodStIterator iterT;
	TWorkingStations::EDMStIterator iterE;
	iterT = ws->getTheodStBeginIterator();
	iterE = ws->getEDMStBeginIterator();
	while (iterE != ws->getEDMStEndIterator()){
		cout << "EDMSt : " << iterE->getSetup() << endl;
		iterE++;
	}
	while (iterT != ws->getTheodStEndIterator()){
		cout << "TheodSt : " << iterT->getSetup() << endl;
		iterT++;
	}
*/
/*	iterT --;
	TTheodoliteStation::HorAngROMIterator harIter = iterT->getHorAngROMBeginIterator();
	//(harIter->getMe())->disactivate();
	THorAngleROM::HorAngMeasIterator haIter = harIter->getHorAngMeasBeginIterator();
	haIter++;
	//haIter->disactivate();
*/

	TLSCalculation lsCalc(lgcDS);
	lsCalc.setLSLocalSysCalcType();
	//lsCalc.simulation();
	lsCalc.setConvCriteria(0.000001);
	lsCalc.setS0APrioriScaleFactor(0.001);
	//lsCalc.s0APosterioriVariances();
	lsCalc.computeSolution();


	const TLSCalcDataSet* lscDS = lsCalc.getCalcDataSet();

	TLSCalcWorkingPoints* cwp = lscDS->getWorkingPoints();
	TLSCalcWorkingPoints::CalcPtIterator citerPt= cwp->getPointsBeginIterator();
	TLSCalcWorkingPoints::CalcPtIterator citerPtEnd = cwp->getPointsEndIterator();

	while (citerPt != citerPtEnd)
		citerPt++;

	TLSCalcWorkingStations* cws = lscDS->getWorkingStations();
	TLSCalcWorkingStations::CalcEDMStIterator citerEDMSt = cws->getEDMStBeginIterator();
	TLSCalcWorkingStations::CalcEDMStIterator citerEDMStEnd = cws->getEDMStEndIterator();
	while (citerEDMSt != citerEDMStEnd)
		citerEDMSt++;

	TLSCalcWorkingStations::CalcTheodStIterator citerTSt = cws->getTheodStBeginIterator();
	TLSCalcWorkingStations::CalcTheodStIterator citerTStEnd = cws->getTheodStEndIterator();
	while (citerTSt != citerTStEnd){
		TLSCalcTheodoliteStation::CalcHorAngROMIterator citerHAROM = citerTSt->getHorAngROMBeginIterator();
		citerTSt++;
	}

	
}



/*	set<TEDMDistROM>::iterator iterromed = st2->getEDMDistROM(4);
	TEDMDistROM* edr = iterromed->getMe();
	set<TEDMDistMeasurement>::iterator itered = iterromed->getDistMeas(&spa);
	TEDMDistMeasurement* ed = itered->getMe();

	(spc.getNetListnr())->disactivate();
	(ed->getNetListnr())->disactivate();
	set<THorAngleROM>::iterator iterrom = st3->getHorAngleROM(&spc);
	THorAngleROM* har1 = iterrom->getMe();
	(har1->getNetListnr())->reactivate();

	TWorkingStations ws;

	ws.addTheodStation(st1);
	ws.addTheodStation(st3);
	ws.addEDMStation(st2);

	set<TTheodoliteStation>::iterator itertst = ws.getTheodStation(&spf);
	TTheodoliteStation* tst = itertst->getMe();
	iterrom = tst->getHorAngleROM(&spc);
	THorAngleROM* har = iterrom->getMe();
	set<THorAngleMeasurement>::iterator iterang;
	iterang = har->getHorAngleMeas(&spa);
	THorAngleMeasurement* ha = iterang->getMe();

	TWorkingPoints wp;

	wp.addPoint(&spa);
	wp.addPoint(&spb);
	wp.addPoint(&spc);
	wp.addPoint(&spd);
	wp.addPoint(&spe);
	wp.addPoint(&spf);
	wp.addPoint(&spg);
	wp.addPoint(&sph);
	wp.addPoint(&spi);
	wp.addPoint(&spj);
	wp.addPoint(&spk);
	wp.addPoint(&spl);


	UEOIndices ueoi = {0,0,0};

	ueoi = wp.setPointIndices(ueoi);

	ws.setStationIndices(ueoi);
*/
