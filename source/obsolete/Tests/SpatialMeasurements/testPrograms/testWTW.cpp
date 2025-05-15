// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TWorkingPoints.h"
#include "TWorkingStations.h"

#include "TEuclideanRefFrame.h"
#include "TLSCalculation.h"

#include <iostream>


void main(){

	TLGCDataSet lgcDS;
	TWorkingPoints* wp = lgcDS.getWorkingPoints();
	TWorkingStations* ws = lgcDS.getWorkingStations();

	TWorkingPoints::PointIterator iterPt;
	TWorkingPoints::PointIterator iterPt2;

	TEuclideanRefFrame erf("Test");
	TSpatialPoint* sp;
	TSpatialPointName* spn;

	//ptA
	TPositionVector pvA(100.00, 200.00, 25.00);
	TSpatialPosition* pA = new TSpatialPosition(&erf);
	pA->setXYZ(pvA);
	pA->setPositionStatus(TSpatialPosition::EPositionStatus::kVxy);
	//pA->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "A", "xxx");
	sp = new TSpatialPoint(*spn, pA);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptB
	TPositionVector pvB(170.00, 210.00, 23.00);
	TSpatialPosition* pB = new TSpatialPosition(&erf);
	pB->setXYZ(pvB);
	pB->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	//pB->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "B", "xxx");
	sp = new TSpatialPoint(*spn, pB);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptC
	TPositionVector pvC(75.00, 160.00, 22.50);
	TSpatialPosition* pC = new TSpatialPosition(&erf);
	pC->setXYZ(pvC);
	pC->setPositionStatus(TSpatialPosition::EPositionStatus::kVx);
	spn = new TSpatialPointName("pt", "C", "xxx");
	sp = new TSpatialPoint(*spn, pC);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptD
	TPositionVector pvD(150.000, 170.00, 0.0);
	TSpatialPosition* pD = new TSpatialPosition(&erf);
	pD->setXYZ(pvD);
	pD->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "D", "xxx");
	sp = new TSpatialPoint(*spn, pD);
	wp->addPoint(sp);
	delete sp;
	delete spn;



	TWorkingTargetObjects* wto = lgcDS.getWorkingTargetObjects();

	//creation du fil entre A et B
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	iterPt2 = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	TWire* wire = new TWire(iterPt2, iterPt, "wireBA");

	wto->addWire(wire);
	delete wire;

	//creation du fil entre C et D
	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	iterPt2 = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	wire = new TWire(iterPt2, iterPt, "wireDC");

	wto->addWire(wire);
	delete wire;


	
	TWorkingTargetObjects::WireIterator iterW2 = wto->getWire(iterPt2, iterPt);

	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	iterPt2 = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	TWorkingTargetObjects::WireIterator iterW1 = wto->getWire(iterPt2, iterPt);



//*** Observations WTW

	//Station WTW 1
	TWTWDistStation* wtwSt = new TWTWDistStation(ws);
	delete wtwSt;
	TWorkingStations::WTWStIterator iterWTWSt = ws->getWTWStBeginIterator();

	//Mesure WTW 1
	TWireToWireDistMeas* wtw = new TWireToWireDistMeas
		(*iterWTWSt, iterW1, TLength(15.0), iterW2, TLength(25.0), TLength(47.860), TLength(0.001), TLength(0.0), TLength(0.001));
	delete wtw;
	TWTWDistStation::WTWDistMeasIterator iterw = iterWTWSt->getWTWDistMeas();
	iterw->disactivateVDist();


	//Station WTW 2
	wtwSt = new TWTWDistStation(ws);
	iterWTWSt++;

	//Mesure WTW 2
	wtw = new TWireToWireDistMeas
		(*iterWTWSt, iterW1, TLength(20.0), iterW2, TLength(35.0), TLength(48.519), TLength(0.001), TLength(0.0), TLength(0.001));
	delete wtw;
	iterw = iterWTWSt->getWTWDistMeas();
	iterw->disactivateVDist();



	//Station WTW 3
	wtwSt = new TWTWDistStation(ws);
	iterWTWSt++;

	//Mesure WTW 3
	wtw = new TWireToWireDistMeas
		(*iterWTWSt, iterW1, TLength(60.0), iterW2, TLength(50.0), TLength(65.182), TLength(0.001), TLength(0.0), TLength(0.001));
	delete wtw;
	iterw = iterWTWSt->getWTWDistMeas();
	iterw->disactivateVDist();



	//Station WTW 4
	wtwSt = new TWTWDistStation(ws);
	iterWTWSt++;

	//Mesure WTW 4
	wtw = new TWireToWireDistMeas
		(*iterWTWSt, iterW1, TLength(65.0), iterW2, TLength(70.0), TLength(61.757), TLength(0.001), TLength(0.0), TLength(0.001));
	delete wtw;
	iterw = iterWTWSt->getWTWDistMeas();
	iterw->disactivateVDist();


	
	//Station WTW 5
	wtwSt = new TWTWDistStation(ws);
	iterWTWSt++;

	//Mesure WTW 5
	wtw = new TWireToWireDistMeas
		(*iterWTWSt, iterW1, TLength(1.0), iterW2, TLength(70.0), TLength(65.749), TLength(0.001), TLength(0.0), TLength(0.001));
	delete wtw;
	iterw = iterWTWSt->getWTWDistMeas();
	iterw->disactivateVDist();


	//Station WTW 6
	wtwSt = new TWTWDistStation(ws);
	iterWTWSt++;

	//Mesure WTW 6
	wtw = new TWireToWireDistMeas
		(*iterWTWSt, iterW1, TLength(69.0), iterW2, TLength(1.0), TLength(104.933), TLength(0.001), TLength(0.0), TLength(0.001));
	delete wtw;
	iterw = iterWTWSt->getWTWDistMeas();
	iterw->disactivateVDist();


//***
//** Observations EDM
//****

	//*Station EDM en C 
	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	TEDMStation* edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	TWorkingStations::EDMStIterator iterEDMSt = ws->getEDMStBeginIterator();
	
	//Unique Serie de mesures de distance
	TEDMDistROM* edmRom = new TEDMDistROM(*iterEDMSt);
	TEDMStation::EDMDistROMIterator iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	TEDMDistMeasurement* edmDist;
/*	//mesure sur A
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(102.488), TLength(0.002));
	delete edmDist;*/
	//mesure sur B
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(79.798), TLength(0.002));
	delete edmDist;



	//*Station EDM en D 
	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	iterEDMSt++;
	
	//Unique Serie de mesures de distance
	edmRom = new TEDMDistROM(*iterEDMSt);
	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	//mesure sur A
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(102.488), TLength(0.002));
	delete edmDist;
	//mesure sur B
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(79.798), TLength(0.002));
	delete edmDist;



//***
// Calcul
//***

	TLSCalculation lsCalc(lgcDS);
	lsCalc.setLSLocalSysCalcType();
	lsCalc.simulation();
	lsCalc.setConvCriteria(0.0002);
	lsCalc.setS0APrioriScaleFactor(0.001);
	//lsCalc.s0APosterioriVariances();
	lsCalc.computeSolution();

	const TLSCalcDataSet* lscDS = lsCalc.getCalcDataSet();

	TLSCalcWorkingPoints* cwp = lscDS->getWorkingPoints();
	TLSCalcWorkingPoints::CalcPtIterator citerPt= cwp->getPointsBeginIterator();
	TLSCalcWorkingPoints::CalcPtIterator citerPtEnd = cwp->getPointsEndIterator();


	while (citerPt != citerPtEnd)
		citerPt++;
}






