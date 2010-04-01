//#include "TInstrumentStation.h"
#include "TTheodoliteStation.h"
#include "TEDMStation.h"
#include "TWorkingPoints.h"
#include "TWorkingStations.h"
#include "TEuclideanRefFrame.h"
#include "UEOIndices.h"

#include "TLength.h"

#include "TLGCDataSet.h"
#include "TLSCalcDataSet.h"

#include "TLSLocalSysZenithDistMeasCG.h"


#include "TLSCalculation.h"

#include <iostream>


void main(){

	TLGCDataSet lgcDS;
	
	TWorkingPoints* wp = lgcDS.getWorkingPoints();
	TWorkingStations* ws = lgcDS.getWorkingStations();
	

	TWorkingPoints::PointIterator iterPt;
	TLSCalcSpPoint spPoint;
	TLSCalcTheodoliteStation cThSt;

	TEuclideanRefFrame erf("Test");
	TSpatialPoint* sp;
	TSpatialPointName* spn;
	
	//ptA
	TPositionVector pvA(200, 600, 50);
	TSpatialPosition* pA = new TSpatialPosition(&erf);
	pA->setXYZ(pvA);
	pA->setPositionStatus(TPositionStatus::kCala);
	//pA->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "A", "xxx");
	sp = new TSpatialPoint(*spn, pA);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptB
	TPositionVector pvB(250, 580, 50);
	TSpatialPosition* pB = new TSpatialPosition(&erf);
	pB->setXYZ(pvB);
	pB->setPositionStatus(TPositionStatus::kVz);
	//pB->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "B", "xxx");
	sp = new TSpatialPoint(*spn, pB);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptC
	TPositionVector pvC(240, 630, 50);
	TSpatialPosition* pC = new TSpatialPosition(&erf);
	pC->setXYZ(pvC);
	pC->setPositionStatus(TPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "C", "xxx");
	sp = new TSpatialPoint(*spn, pC);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptD
	TPositionVector pvD(150, 550, 50);
	TSpatialPosition* pD = new TSpatialPosition(&erf);
	pD->setXYZ(pvD);
	pD->setPositionStatus(TPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "D", "xxx");
	sp = new TSpatialPoint(*spn, pD);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptE
	TPositionVector pvE(250, 540, 50);
	TSpatialPosition* pE = new TSpatialPosition(&erf);
	pE->setXYZ(pvE);
	pE->setPositionStatus(TPositionStatus::kCala);
	spn = new TSpatialPointName("pt", "E", "xxx");
	sp = new TSpatialPoint(*spn, pE);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptF
	TPositionVector pvF(160, 620, 50);
	TSpatialPosition* pF = new TSpatialPosition(&erf);
	pF->setXYZ(pvF);
	pF->setPositionStatus(TPositionStatus::kVz);
	spn = new TSpatialPointName("pt", "F", "xxx");
	sp = new TSpatialPoint(*spn, pF);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptG
	TPositionVector pvG(210, 570, 50);
	TSpatialPosition* pG = new TSpatialPosition(&erf);
	pG->setXYZ(pvG);
	pG->setPositionStatus(TPositionStatus::kVz);
	spn = new TSpatialPointName("pt", "G", "xxx");
	sp = new TSpatialPoint(*spn, pG);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptH
	TPositionVector pvH(270, 610, 50);
	TSpatialPosition* pH = new TSpatialPosition(&erf);
	pH->setXYZ(pvH);
	pH->setPositionStatus(TPositionStatus::kVz);
	spn = new TSpatialPointName("pt", "H", "xxx");
	sp = new TSpatialPoint(*spn, pH);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	//ptI
	TPositionVector pvI(150, 580, 50);
	TSpatialPosition* pI = new TSpatialPosition(&erf);
	pI->setXYZ(pvI);
	pI->setPositionStatus(TPositionStatus::kVz);
	//pI->setZCoordStatus(TSpatialPosition::ECoordStatus::kUnknown);
	spn = new TSpatialPointName("pt", "I", "xxx");
	sp = new TSpatialPoint(*spn, pI);
	wp->addPoint(sp);
	delete sp;
	delete spn;

	
	iterPt = wp->getPointsBeginIterator();
	while (iterPt != wp->getPointsEndIterator())
		iterPt++;



	TAngle alpha;
//	alpha.setGonsValue(146.234);
	TAngle sigal;
	sigal.setGonsValue(0.001);
	TAngle zero;
	zero.setGonsValue(0.0);
	TAngle newValue;
	newValue.setGonsValue(0.005);
	TLength hs;
	hs.setMetresValue(0.05);

//ST1
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	
	TTheodoliteStation* thSt = new TTheodoliteStation(ws, iterPt);
/*	TUnknownLength hi;
	TLength l;
	l.setMetresValue(0.20);
	hi.setProvisionalValue(l);
	thSt->setInstrumentHeight(hi);
	thSt->setInstHeightStatus(TANumericValue::kFixed);*/
	delete thSt;

	iterPt = spPoint.getNtPoint();


	TWorkingStations::TheodStIterator iterTh = ws->getTheodStBeginIterator();
	

//ROM11
	TZenithDistROM* zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	TTheodoliteStation::ZenithDistROMIterator iterZDR= iterTh->getZenithDistROMBeginIterator();


	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	alpha.setGonsValue(100.192);
	TZenithDistMeasurement* zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	alpha.setGonsValue(100.135);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	alpha.setGonsValue(100.178);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	alpha.setGonsValue(100.123);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	alpha.setGonsValue(100.301);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	alpha.setGonsValue(100.135);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "I", "xxx"));
	alpha.setGonsValue(100.178);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	alpha.setGonsValue(100.214);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;


//ST2
	
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	
	thSt = new TTheodoliteStation(ws, iterPt);
/*	l.setMetresValue(0.20);
	hi.setProvisionalValue(l);
	thSt->setInstrumentHeight(hi);
	thSt->setInstHeightStatus(TANumericValue::kUnknown);*/
	delete thSt;

	iterPt = spPoint.getNtPoint();


	iterTh++;
	

//ROM21
	zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	iterZDR= iterTh->getZenithDistROMBeginIterator();


	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	alpha.setGonsValue(100.188);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	alpha.setGonsValue(100.264);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	alpha.setGonsValue(100.239);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	alpha.setGonsValue(100.093);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	alpha.setGonsValue(100.231);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "I", "xxx"));
	alpha.setGonsValue(100.096);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	alpha.setGonsValue(100.178);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	alpha.setGonsValue(100.097);
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal, hs);
	delete zd;




/*
//	TZenithDistMeasurement zenDist;

	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	
	TZenithDistMeasurement (zenDist);
//	cout << zenDist.addToStation(wp,ws) << endl;
	TZenithDistMeasurement* zd = new TZenithDistMeasurement (*iterZDR, iterPt, alpha, zero);
//	zd->ifNotDoneSetSigma(newValue);
//	cout << (zd->getSigma()).getGonsValue() << endl;
	
	iterPt = spPoint.getNtPoint();
	
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	iterPt = spPoint.getNtPoint();
//	cout << zd->addToStation(wp,ws) << endl;
 	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	iterPt = spPoint.getNtPoint();
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, zero, sigal);
	iterPt = spPoint.getNtPoint();
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, zero);
//	cout << (zd->getSigma()).getGonsValue() << endl;
	zd->ifNotDoneSetSigma(newValue);
//	cout << (zd->getSigma()).getGonsValue() << endl;
	iterPt = spPoint.getNtPoint();
//	cout << (zd->getSigma()).getGonsValue() << endl;
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

//ROM11
	zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	iterZDR++;


	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
 	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, zero);
	zd->ifNotDoneSetSigma(newValue);
	//cout << (zd->getSigma()).getGonsValue() << endl;
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;



//ROM12
	zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	iterZDR++;

	
	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));

	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	//************debug begin
//	TZenithDistROM::ZenithDistMeasIterator debugIter = iterZDR->getZenithDistMeasBeginIterator();
//	debugIter++;
//	debugIter++;
	//************debug end

	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	cout << zd->addToStation(wp,ws) << endl;
	delete zd;




//ROM13
	zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	iterZDR++;

	
	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;



//ST3
	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	thSt = new TTheodoliteStation(ws, iterPt);
	delete thSt;

	iterTh++;
//	iterCTh++;

//ROM31
	zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	iterZDR= iterTh->getZenithDistROMBeginIterator();

	
	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	delete zd;

//ROM32
	zdRom = new TZenithDistROM(*iterTh);
	delete zdRom;

	iterZDR++;

	
	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
//	cout << zd->addToStation(wp,ws) << endl;
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	delete zd;
	
	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	delete zd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	zd = new TZenithDistMeasurement(*iterZDR, iterPt, alpha, sigal);
	delete zd;

*/


//Theodolite related iterators
	iterTh = ws->getTheodStBeginIterator();
	
	TWorkingStations::TheodStIterator iT1 = iterTh;
	TWorkingStations::TheodStIterator iT2 = ++iterTh;

	TUnknownLength hi;
	TLength l;
	l.setMetresValue(0.20);
	hi.setProvisionalValue(l);
	iT1->setInstrumentHeight(hi);
	iT1->setInstHeightStatus(TANumericValue::kFixed);
	
	cout << ((iT1->getInstrumentHeight()).getProvisionalValue()).getMetresValue() << endl;

	TTheodoliteStation::ZenithDistROMIterator iterZR = iT1->getZenithDistROMBeginIterator();
	TTheodoliteStation::ZenithDistROMIterator iterZREnd = iT1->getZenithDistROMEndIterator();
	while (iterZR != iterZREnd){
		TZenithDistROM::ZenithDistMeasIterator iterZ = iterZR->getZenithDistMeasBeginIterator();
		TZenithDistROM::ZenithDistMeasIterator iterZEnd = iterZR->getZenithDistMeasEndIterator();
		while (iterZ != iterZEnd)
		{
			
			cout << iterZ->getMeasKind() << endl;
			cout << (iterZ->getAngleValue()).getGonsValue()  << endl;
			cout << (iterZ->getSigma()).getGonsValue()  << endl;
			iterZ->ifNotDoneSetSigma(newValue);
			cout << (iterZ->getSigma()).getGonsValue()  << endl;
			cout << (iterZ->getPrismeHeight()).getMetresValue() << endl;

			iterZ++;
		}
		


		iterZR++;
	}

	

	l.setMetresValue(0.20);
	hi.setProvisionalValue(l);
	
	iT2->setInstrumentHeight(hi);
	iT2->setInstHeightStatus(TANumericValue::kVariable);


	cout << ((iT2->getInstrumentHeight()).getProvisionalValue()).getMetresValue() << endl;
	
	
	iterZR = iT2->getZenithDistROMBeginIterator();
	iterZREnd = iT2->getZenithDistROMEndIterator();
	while (iterZR != iterZREnd){
		TZenithDistROM::ZenithDistMeasIterator iterZ = iterZR->getZenithDistMeasBeginIterator();
		TZenithDistROM::ZenithDistMeasIterator iterZEnd = iterZR->getZenithDistMeasEndIterator();
		while (iterZ != iterZEnd)
			{

			cout << iterZ->getMeasKind() << endl;
			cout << (iterZ->getAngleValue()).getGonsValue()  << endl;
			cout << (iterZ->getSigma()).getGonsValue()  << endl;
			cout << (iterZ->getPrismeHeight()).getMetresValue() << endl;

			iterZ++;
		}
			
		iterZR++;

	}


 	cout << "fin de la premiere partie du test" << endl;


	TLSCalcDataSet lscDS(lgcDS);
//	TLSCalcWorkingPoints* wcp = lscDS.getWorkingPoints();
	TLSCalcWorkingStations* wcs = lscDS.getWorkingStations();
	TLSCalcWorkingStations::CalcTheodStIterator iterCTh = wcs->getTheodStBeginIterator();


	TLSCalcWorkingStations::CalcTheodStIterator CiT1 = iterCTh;
	TLSCalcWorkingStations::CalcTheodStIterator CiT2 = ++iterCTh;

	TLSCalcTheodoliteStation::CalcZenithDistROMIterator iterCZR = CiT1->getZenithDistROMBeginIterator();
	TLSCalcTheodoliteStation::CalcZenithDistROMIterator iterCZREnd = CiT1->getZenithDistROMEndIterator();
	
	cout << ((CiT1->getInstrumentHeight()).getProvisionalValue()).getMetresValue() << endl;
/*	bool var = CiT1->variableInstHeight();
	if (var)
		cout << "true" << endl;
	else 
		cout << "false" << endl;*/
	cout << CiT1->variableInstHeight() << endl;

	
	while (iterCZR != iterCZREnd){
		TLSCalcZenithDistROM::CalcZenithDistIterator iterCZ = iterCZR->getZenithDistMeasBeginIterator();
		TLSCalcZenithDistROM::CalcZenithDistIterator iterCZEnd = iterCZR->getZenithDistMeasEndIterator();
		while (iterCZ != iterCZEnd)
		{
			cout << (iterCZ->getObsAngleValue()).getGonsValue() <<endl;
			cout << (iterCZ->getSigmaAPriori()).getGonsValue() << endl;
			cout << (iterCZ->getHeight()).getMetresValue() << endl;
			
			iterCZ++;
		}
		
		iterCZR++;
	}


	iterCZR = CiT2->getZenithDistROMBeginIterator();
	iterCZREnd = CiT2->getZenithDistROMEndIterator();

	cout << ((CiT2->getInstrumentHeight()).getProvisionalValue()).getMetresValue() << endl;
	cout << CiT2->variableInstHeight() << endl;
	cout << (CiT2->getInstrumentHeight()).known() << endl;

	while (iterCZR != iterCZREnd){
		TLSCalcZenithDistROM::CalcZenithDistIterator iterCZ = iterCZR->getZenithDistMeasBeginIterator();
		TLSCalcZenithDistROM::CalcZenithDistIterator iterCZEnd = iterCZR->getZenithDistMeasEndIterator();
		while (iterCZ != iterCZEnd)
		{
			cout << (iterCZ->getObsAngleValue()).getGonsValue() <<endl;
			cout << (iterCZ->getSigmaAPriori()).getGonsValue() << endl;
			cout << (iterCZ->getHeight()).getMetresValue() << endl;
			
			iterCZ++;
		}
		
		iterCZR++;
	}




	TLSCalculation tlsc (lgcDS);
	tlsc.setLSLocalSysCalcType();
	tlsc.setConvCriteria(0.0001);

	tlsc.computeSolution();

	cout << "fin du test de calcul" << endl;



/*	TLSCalcDataSet* plscDS = &lscDS;
	TLSInputMatricesFiller tlsIMF (plscDS);

	tlsIMF.setLSLocalSysCalcType();
	tlsIMF.fillMatrices();
*/

//	TLSInputMatricesFiller* ptlsIMF = &tlsIMF;
//	const TLSInputMatrices* ptlsIM = ptlsIMF->getInputMatrices();
//	TLSLocalSysZenithDistMeasCG locsysZD (ptlsIM);
	



}

