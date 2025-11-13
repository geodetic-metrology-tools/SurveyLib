// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TAngle.h"
#include "TWorkingPoints.h"
#include "TSpatialPoint.h"
#include "TSpatialPosition.h"

#include "TWorkingStations.h"
#include "UEOIndices.h"
#include "TLSInputMatricesFiller.h"

#include "TLGCDataSet.h"
#include "TLSCalcDataSet.h"

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
	TPositionVector pvA(138.49, 276.21, 54.99);
	TSpatialPosition* pA = new TSpatialPosition(&erf);
	pA->setXYZ(pvA);
	pA->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	//pA->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "A", "xxx");
	sp = new TSpatialPoint(*spn, pA);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptB
	TPositionVector pvB(201.06, 311.55, 47.32);
	TSpatialPosition* pB = new TSpatialPosition(&erf);
	pB->setXYZ(pvB);
	pB->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	//pB->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "B", "xxx");
	sp = new TSpatialPoint(*spn, pB);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptC
	TPositionVector pvC(143.58, 342.63, 48.17);
	TSpatialPosition* pC = new TSpatialPosition(&erf);
	pC->setXYZ(pvC);
	pC->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "C", "xxx");
	sp = new TSpatialPoint(*spn, pC);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptD
	TPositionVector pvD(100.000, 280.540, 0.0);
	TSpatialPosition* pD = new TSpatialPosition(&erf);
	pD->setXYZ(pvD);
	pD->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "D", "xxx");
	sp = new TSpatialPoint(*spn, pD);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptE
	TPositionVector pvE(159.600, 202.210, 50.49);
	TSpatialPosition* pE = new TSpatialPosition(&erf);
	pE->setXYZ(pvE);
	pE->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "E", "xxx");
	sp = new TSpatialPoint(*spn, pE);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptF
	TPositionVector pvF(207.120, 314.250, 46.38);
	TSpatialPosition* pF = new TSpatialPosition(&erf);
	pF->setXYZ(pvF);
	pF->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "F", "xxx");
	sp = new TSpatialPoint(*spn, pF);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptG
	TPositionVector pvG(253.110, 328.440, 0.0);
	TSpatialPosition* pG = new TSpatialPosition(&erf);
	pG->setXYZ(pvG);
	pG->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "G", "xxx");
	sp = new TSpatialPoint(*spn, pG);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptH
	TPositionVector pvH(158.990, 218.140, 67.05);
	TSpatialPosition* pH = new TSpatialPosition(&erf);
	pH->setXYZ(pvH);
	pH->setPositionStatus(TSpatialPosition::EPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "H", "xxx");
	sp = new TSpatialPoint(*spn, pH);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptM1
	TPositionVector pvM1(157.370, 288.930, 51.91);
	TSpatialPosition* pM1 = new TSpatialPosition(&erf);
	pM1->setXYZ(pvM1);
	pM1->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	//pM1->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "M1", "xxx");
	sp = new TSpatialPoint(*spn, pM1);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptM2
	TPositionVector pvM2(176.480, 296.010, 72.27);
	TSpatialPosition* pM2 = new TSpatialPosition(&erf);
	pM2->setXYZ(pvM2);
	pM2->setPositionStatus(TSpatialPosition::EPositionStatus::kVxyz);
	//pM2->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "M2", "xxx");
	sp = new TSpatialPoint(*spn, pM2);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	iterPt = wp->getPointsBeginIterator();
	while (iterPt != wp->getPointsEndIterator())
		iterPt++;



//*Station EDM en C 
	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	TEDMStation* edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	TWorkingStations::EDMStIterator iterEDMSt = ws->getEDMStBeginIterator();
	
//Unique Serie de mesures de distance
	TEDMDistROM* edmRom = new TEDMDistROM(*iterEDMSt);
	TEDMStation::EDMDistROMIterator iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	//mesure sur A
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	TEDMDistMeasurement* edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(66.654), TLength(0.016));
	delete edmDist;
	//mesure sur M1
	iterPt = wp->getPoint(TSpatialPointName("pt", "M1", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(55.448), TLength(0.014));
	delete edmDist;


//*Station EDM en D
	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);
	delete edmSt;

	//unique serie de mesures
	iterEDMSt ++;
	edmRom= new TEDMDistROM(*iterEDMSt);
	delete edmRom;

	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, TLength(38.743), TLength(0.010));

	delete edmDist;


//*Station EDM en E 
	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	iterEDMSt++;
	
//Unique Serie de mesures de distance
	edmRom = new TEDMDistROM(*iterEDMSt);
	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	//mesure sur A
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(76.931), TLength(0.019));
	delete edmDist;
	//mesure sur M2
	iterPt = wp->getPoint(TSpatialPointName("pt", "M2", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(95.319), TLength(0.024));
	delete edmDist;



//*Station EDM en F
	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	iterEDMSt++;
	
//Unique Serie de mesures de distance
	edmRom = new TEDMDistROM(*iterEDMSt);
	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	//mesure sur B
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(6.614), TLength(0.002));
	delete edmDist;
	//mesure sur M1
	iterPt = wp->getPoint(TSpatialPointName("pt", "M1", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(55.841), TLength(0.014));
	delete edmDist;


//*Station EDM en G
	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);
	delete edmSt;

//unique serie de mesures
	iterEDMSt ++;
	edmRom= new TEDMDistROM(*iterEDMSt);
	delete edmRom;

	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom, iterPt, TLength(54.731), TLength(0.014));

	delete edmDist;


//*Station EDM en H 
	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	edmSt = new TEDMStation(ws, iterPt);

	delete edmSt;

	iterEDMSt++;
	
//Unique Serie de mesures de distance
	edmRom = new TEDMDistROM(*iterEDMSt);
	iterEDMrom = iterEDMSt->getEDMDistROMBeginIterator();

	delete edmRom;

	//mesure sur A
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(102.488), TLength(0.026));
	delete edmDist;
	//mesure sur M2
	iterPt = wp->getPoint(TSpatialPointName("pt", "M2", "xxx"));
	edmDist = new TEDMDistMeasurement(*iterEDMrom,iterPt, TLength(79.798), TLength(0.020));
	delete edmDist;



//** observations WPS

	TWorkingTargetObjects* wto = lgcDS.getWorkingTargetObjects();

	//creation du fil entre A et B
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	iterPt2 = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	TWire* wire = new TWire(iterPt, iterPt2, "wireAB");

	wto->addWire(wire);
	delete wire;

	TAngle nullAngle(0);
	//*station WPS en M1
	iterPt = wp->getPoint(TSpatialPointName("pt", "M1", "xxx"));
	TWPSStation* wpsSt = new TWPSStation(ws, iterPt, nullAngle, nullAngle, nullAngle); 
	delete wpsSt;

	TWorkingStations::WPSStIterator iterWPSSt = ws->getWPSStBeginIterator();

	TWorkingTargetObjects::WireIterator iterWire = wto->getWireBeginIterator();
	//mesure de M1 au fil
	TWPSMeasurement* wpsMeas = 
		new TWPSMeasurement(*iterWPSSt, iterWire, TLength(-0.756) , TLength(0.001), TLength(1.780), TLength(0.002));
	delete wpsMeas;
	iterWPSSt->getWPSMeas()->disactivateVOffset();	



	//*station WPS en M2
	iterPt = wp->getPoint(TSpatialPointName("pt", "M2", "xxx"));
	wpsSt = new TWPSStation(ws, iterPt, nullAngle, nullAngle, nullAngle); 
	delete wpsSt;

	iterWPSSt++;
	//mesure de M2 au fil
	wpsMeas = new TWPSMeasurement(*iterWPSSt, iterWire, TLength(21.773) , TLength(0.001), TLength(-1.459), TLength(0.002));
	delete wpsMeas;
	iterWPSSt->getWPSMeas()->disactivateVOffset();

/******/
/** Stations de nivellement*/
/******/

	//*Level station for the ROM referenced from A and M2
	TLevelStation* lSt = new TLevelStation(ws);
	delete lSt;
	
	TWorkingStations::LevelStIterator iterLSt = ws->getLevelStBeginIterator();

	//ROM referenced from A
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	TVerticalDistROM* vdR = new TVerticalDistROM(*iterLSt, iterPt);
	delete vdR;

	TLevelStation::VertDistROMIterator iterVDR = iterLSt->getVertDistROMBeginIterator();

	//DeltaZAC
	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	TVerticalDistMeasurement* vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-6.832), TLength(0.0067));
	delete vd;

	//DeltaZAE
	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-4.495), TLength(0.0077));
	delete vd;

	//DeltaZAM2
	iterPt = wp->getPoint(TSpatialPointName("pt", "M2", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(17.275), TLength(0.0043));
	delete vd;


	//ROM referenced from M2
	vdR = new TVerticalDistROM(*iterLSt, iterPt);
	delete vdR;

	iterVDR++;

	//DeltaZM2E
	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-21.788), TLength(0.0095));
	delete vd;

	//DeltaZM2H
	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-5.234), TLength(0.008));
	delete vd;



	//* Level station for the ROMs referenced from B and M1
	lSt = new TLevelStation(ws);
	delete lSt;

	iterLSt++;

	//ROm referenced from B
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	vdR = new TVerticalDistROM(*iterLSt, iterPt);
	delete vdR;

	iterVDR = iterLSt->getVertDistROMBeginIterator();

	//DeltaZBF
	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-0.941), TLength(0.0007));
	delete vd;

	//DeltaZBH
	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(19.723), TLength(0.0102));
	delete vd;

	//DeltaZBM1
	iterPt = wp->getPoint(TSpatialPointName("pt", "M1", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(4.593), TLength(0.0049));
	delete vd;


	//ROM referenced from M1
	vdR = new TVerticalDistROM(*iterLSt, iterPt);
	delete vdR;

	iterVDR++;

	//DeltaZM1C
	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-3.727), TLength(0.0055));
	delete vd;

	//DeltaZM1F
	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	vd = new TVerticalDistMeasurement(*iterVDR, iterPt, TLength(-5.544), TLength(0.0056));
	delete vd;





	TWorkingStations::WPSStIterator iterW;
	TWorkingStations::EDMStIterator iterE;
	TWorkingStations::LevelStIterator iterL;
	iterW = ws->getWPSStBeginIterator();
	iterE = ws->getEDMStBeginIterator();
	iterL = ws->getLevelStBeginIterator();
	while (iterE != ws->getEDMStEndIterator()){
		cout << "EDMSt : " << iterE->getSetup() << endl;
		iterE++;
	}
	while (iterW != ws->getWPSStEndIterator()){
		cout << "WPSSt : " << iterW->getSetup() << endl;
		iterW++;
	}
	while (iterL != ws->getLevelStEndIterator()){
		cout << "LevelSt : " << iterL->getSetup() << endl;
		iterL++;
	}



	TLSCalculation lsCalc(lgcDS);
	lsCalc.setLSLocalSysCalcType();
	//lsCalc.simulation();
	lsCalc.setConvCriteria(0.000001);
	lsCalc.setS0APrioriScaleFactor(0.001);
	lsCalc.s0APosterioriVariances();
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

	TLSCalcWorkingStations::CalcWPSStIterator citerWSt = cws->getWPSStBeginIterator();
	TLSCalcWorkingStations::CalcWPSStIterator citerWStEnd = cws->getWPSStEndIterator();
	while (citerWSt != citerWStEnd){
		TLSCalcWPSStation::CalcWPSMeasIterator citerWM = citerWSt->getWPSMeas();
		citerWSt++;
	}

	
}
