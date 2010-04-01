//#include "TInstrumentStation.h"
#include "TDistMeasStation.h"
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
//	TLSCalcDistMeasStation cDSt;

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



//	TAngle alpha;
//	TAngle sigal;
//	sigal.setGonsValue(0.001);

	TLength zero;
	zero.setMetresValue(0.0);
	TLength newValue;
	newValue.setMetresValue(0.005);
	
	TLength dmes, sigma;
	sigma.setMetresValue(0.002);
	TLength hs;
	hs.setMetresValue(0.05);

//ST1
	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	
	TDistMeasStation* dmSt = new TDistMeasStation(ws, iterPt);
	delete dmSt;

	iterPt = spPoint.getNtPoint();


	TWorkingStations::DistStIterator iterD = ws->getDistStBeginIterator();
	

//ROM11
	TSpatialDistROM* sdRom = new TSpatialDistROM(*iterD);
	delete sdRom;

	TDistMeasStation::SpatialDistROMIterator iterSR= iterD->getSpatialDistROMBeginIterator();


	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	dmes.setMetresValue(100.192);
	TSpatialDistMeasurement* sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	dmes.setMetresValue(100.135);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	dmes.setMetresValue(100.178);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	dmes.setMetresValue(100.123);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	dmes.setMetresValue(100.301);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	dmes.setMetresValue(100.135);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "I", "xxx"));
	dmes.setMetresValue(100.178);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	dmes.setMetresValue(100.214);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;


//ST2
	
	iterPt = wp->getPoint(TSpatialPointName("pt", "B", "xxx"));
	
	dmSt = new TDistMeasStation(ws, iterPt);
	delete dmSt;

	iterPt = spPoint.getNtPoint();


	iterD++;
	

//ROM21
	sdRom = new TSpatialDistROM(*iterD);
	delete sdRom;

	iterSR= iterD->getSpatialDistROMBeginIterator();


	iterPt = wp->getPoint(TSpatialPointName("pt", "C", "xxx"));
	dmes.setMetresValue(100.188);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "H", "xxx"));
	dmes.setMetresValue(100.264);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "E", "xxx"));
	dmes.setMetresValue(100.239);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "D", "xxx"));
	dmes.setMetresValue(100.093);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "G", "xxx"));
	dmes.setMetresValue(100.231);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "I", "xxx"));
	dmes.setMetresValue(100.096);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "A", "xxx"));
	dmes.setMetresValue(100.178);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;

	iterPt = wp->getPoint(TSpatialPointName("pt", "F", "xxx"));
	dmes.setMetresValue(100.097);
	sd = new TSpatialDistMeasurement(*iterSR, iterPt, dmes, sigma, hs);
	delete sd;







	iterD = ws->getDistStBeginIterator();
	
	TWorkingStations::DistStIterator iD1 = iterD;
	TWorkingStations::DistStIterator iD2 = ++iterD;

	TUnknownLength hi;
	TLength l;
	l.setMetresValue(0.20);
	hi.setProvisionalValue(l);
	iD1->setInstrumentHeight(hi);
	iD1->setInstHeightStatus(TANumericValue::kFixed);
	
	cout << ((iD1->getInstrumentHeight()).getProvisionalValue()).getMetresValue() << endl;

	TDistMeasStation::SpatialDistROMIterator iterSDR = iD1->getSpatialDistROMBeginIterator();
	TDistMeasStation::SpatialDistROMIterator iterSDREnd = iD1->getSpatialDistROMEndIterator();
	while (iterSDR != iterSDREnd){
		TSpatialDistROM::SpatialDistMeasIterator iterSD = iterSDR->getDistMeasBeginIterator();
		TSpatialDistROM::SpatialDistMeasIterator iterSDEnd = iterSDR->getDistMeasEndIterator();
		while (iterSD != iterSDEnd)
		{
			
			cout << iterSD->getMeasKind() << endl;
			cout << (iterSD->getDistValue()).getMetresValue()  << endl;
			cout << (iterSD->getSigma()).getMetresValue()  << endl;
			iterSD->ifNotDoneSetSigma(newValue);
			cout << (iterSD->getSigma()).getMetresValue()  << endl;
			cout << (iterSD->getPrismeHeight()).getMetresValue() << endl;

			iterSD++;
		}
		


		iterSDR++;
	}

	

	l.setMetresValue(0.20);
	hi.setProvisionalValue(l);
	
	iD2->setInstrumentHeight(hi);
	iD2->setInstHeightStatus(TANumericValue::kVariable);


	cout << ((iD2->getInstrumentHeight()).getProvisionalValue()).getMetresValue() << endl;
	
	
	iterSDR = iD2->getSpatialDistROMBeginIterator();
	iterSDREnd = iD2->getSpatialDistROMEndIterator();
	while (iterSDR != iterSDREnd){
		TSpatialDistROM::SpatialDistMeasIterator iterSD = iterSDR->getDistMeasBeginIterator();
		TSpatialDistROM::SpatialDistMeasIterator iterSDEnd = iterSDR->getDistMeasEndIterator();
		while (iterSD != iterSDEnd)
			{

			cout << iterSD->getMeasKind() << endl;
			cout << (iterSD->getDistValue()).getMetresValue()  << endl;
			cout << (iterSD->getSigma()).getMetresValue()  << endl;
			cout << (iterSD->getPrismeHeight()).getMetresValue() << endl;

			iterSD++;
		}
			
		iterSDR++;

	}


 	cout << "fin de la premiere partie du test" << endl;


	


/*	TLSCalcDataSet lscDS(lgcDS);
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
/*	cout << CiT1->variableInstHeight() << endl;

	
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
*/


/*	TLSCalcDataSet* plscDS = &lscDS;
	TLSInputMatricesFiller tlsIMF (plscDS);

	tlsIMF.setLSLocalSysCalcType();
	tlsIMF.fillMatrices();
*/

//	TLSInputMatricesFiller* ptlsIMF = &tlsIMF;
//	const TLSInputMatrices* ptlsIM = ptlsIMF->getInputMatrices();
//	TLSLocalSysZenithDistMeasCG locsysZD (ptlsIM);
	



}

