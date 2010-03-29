// Test du module SpatialMeasurements: test des fonctions de stockage uniquement.

#include <iostream>
#include <string>
#include <list>

using namespace std;

#include "TTheodoliteStation.h"
#include "TDistMeasStation.h"
#include "TWPSStation.h"
#include "TWTWDistStation.h"
#include "TLevelStation.h"

void main() {
	
	
	// mise en place des valeurs et tests sur les HorAngles et ZenithDist	
	TSpatialPointName testSt("stationTest");
	TSpatialPointName testTg1("targetTest1");
	TSpatialPointName testTg2("targetTest2");
	TSpatialPointName testTg3("targetTest3");

	/* LEVELING MEASUREMENT STATION*/

	// test sur les vert.dist. measurements
	TLength	dist(LITERAL(1.004)); 
	TLength	sigma(LITERAL(0.0001));
	TLength	dist1(LITERAL(1.003)); 
	TLength	sigma1(LITERAL(0.0002)); 
	TLength	dist2(LITERAL(1.023)); 
	TLength	sigma2(LITERAL(0.0001)); 
	TLength	dist3(LITERAL(0.985)); 
	TLength	sigma3(LITERAL(0.0003)); 
	TLength	dist4(LITERAL(0.752)); 
	TLength	sigma4(LITERAL(0.0001)); 
	
	TVerticalDistMeasurement vdm(testSt,dist,sigma);
	TVerticalDistMeasurement vdm1(testTg1,dist1,sigma1);
	TVerticalDistMeasurement vdm2(testTg2,dist2,sigma2);
	TVerticalDistMeasurement vdm3(testTg3,dist3,sigma3);

	cout << vdm.getMeasKind() << endl;
	cout << vdm.getTargetPoint().getName() << endl;
	cout << vdm.getVDistValue().getMetresValue() << endl;
	cout << vdm.getSigma().getMetresValue() << endl << endl;
	cout << vdm1.getMeasKind() << endl;
	cout << vdm1.getTargetPoint().getName() << endl;
	cout << vdm1.getVDistValue().getMetresValue() << endl;
	cout << vdm1.getSigma().getMetresValue() << endl << endl;
	cout << vdm2.getMeasKind() << endl;
	cout << vdm2.getTargetPoint().getName() << endl;
	cout << vdm2.getVDistValue().getMetresValue() << endl;
	cout << vdm2.getSigma().getMetresValue() << endl << endl;
	cout << vdm3.getMeasKind() << endl;
	cout << vdm3.getTargetPoint().getName() << endl;
	cout << vdm3.getVDistValue().getMetresValue() << endl;
	cout << vdm3.getSigma().getMetresValue() << endl << endl;

//	vdm.ifNotDoneSetSigma(sigma3);
//	cout << vdm.getSigma().getMetresValue() << endl << endl;
//	vdm.setTargetPoint(testTg2);
//	cout << vdm.getTargetPoint().getName() << endl;

//	TVerticalDistMeasurement vdmbis;
//	vdmbis=vdm;
//	cout << vdmbis.getMeasKind() << endl;
//	cout << vdmbis.getTargetPoint().getName() << endl;
//	cout << vdmbis.getVDistValue().getMetresValue() << endl;
//	cout << vdmbis.getSigma().getMetresValue() << endl;

	// test sur les vert.dist. ROMs
	TVerticalDistROM vertROM(testTg3);
	vertROM.setSeries("serie1");
	vertROM.addVertDist(&vdm);
	vertROM.addVertDist(&vdm1);
	
	TVerticalDistROM vertROM2(testTg1);
	vertROM2.setSeries("serie2");
	vertROM2.addVertDist(&vdm2);
	vertROM2.addVertDist(&vdm3);
	vertROM2.addVertDist(&vdm);
	if (vertROM2.notInContainer(&vdm))
		vertROM2.addVertDist(&vdm);
	else
		cout << "deja dans la liste!!" << endl;

//	cout << vertROM.getVertDistMeas(testTg1)->getTargetPoint().getName() << endl;
//	cout << vertROM.getVertDistMeas(testTg1)->getVDistValue().getMetresValue() << endl << endl;

	cout << vertROM.getSeries() << " / Ref.Point: " << vertROM.getRefPtName().getName() << endl;
	VertDistMeasIterator iterB = vertROM.getVertDistMeasBeginIterator();
	VertDistMeasIterator iterE = vertROM.getVertDistMeasEndIterator();

	while (iterB!=iterE) {
		cout << iterB->getTargetPoint().getName() << endl;
		cout << iterB->getVDistValue().getMetresValue() << endl;
		iterB++;
	}

	cout << endl;

//	cout << vertROM2.getVertDistMeas(testTg2)->getTargetPoint().getName() << endl;
//	cout << vertROM2.getVertDistMeas(testTg2)->getVDistValue().getMetresValue() << endl << endl;

	cout << vertROM2.getSeries() << " / Ref.Point: " << vertROM2.getRefPtName().getName() << endl;
	VertDistMeasIterator iterB1 = vertROM2.getVertDistMeasBeginIterator();
	VertDistMeasIterator iterE1 = vertROM2.getVertDistMeasEndIterator();

	while (iterB1!=iterE1) 
	{
		cout << iterB1->getTargetPoint().getName() << endl;
		cout << iterB1->getVDistValue().getMetresValue() << endl;
		iterB1++;
	}

	cout << endl <<endl;

	// test de Level Station
	TLevelStation level,bidon;
	
	level.addVertDistROM(&vertROM);
	level.addVertDistROM(&vertROM2);

	if(level.notInContainer(&vertROM2))
		level.addVertDistROM(&vertROM2);
	else
		cout << "deja dans la liste!!" << endl << endl;

	level.setSetup("LEVEL STATION");

	cout << level.getSetup() << endl << endl;
	
	VertDistROMIterator  iterB2 = level.getVertDistROMBeginIterator();
	VertDistROMIterator  iterE2 = level.getVertDistROMEndIterator();

//	cout << level.getVertDistROM(testTg3)->getSeries() << endl;

	while (iterB2!=iterE2) 
	{
		cout << iterB2->getSeries() << endl;
		iterB2++;
	}


	bidon=level;

	cout << bidon.getSetup() << endl;

////////////////////////////////////////////////////////////////////////////////////////////////

	/* DISTANCE MEASUREMENT STATION */

	// test de mise en place des SpatialDist, HorizontalDist, 2DOffset...
	TLength	spDistObs1(LITERAL(12.036521));
	TLength spDistObs2(LITERAL(25.125489));
	TLength spDistObs3(LITERAL(7.2585654));

	TLength spDistSigma1(LITERAL(0.000500));
	TLength spDistSigma23(LITERAL(0.000100));
	
	string prismNb("1");
	TLength prismH1(LITERAL(0.012025));
	TLength prismH2(LITERAL(0.008523));
	TLength prismH3(LITERAL(0.015632));

	string line("line"); 
	TLength vobs(LITERAL(0.002)); 
	TLength	vsigma(LITERAL(0.0001));								
	TLength	hobs(LITERAL(0.004)); 
	TLength	hsigma(LITERAL(0.0002));

	T2DOffsetMeasurement om(line,hobs,hsigma,vobs,vsigma);

	THorizontalDistMeas hdm1(testTg1,spDistObs1,spDistSigma1);
	THorizontalDistMeas hdm2(testTg2,spDistObs2,spDistSigma23);
	THorizontalDistMeas hdm3(testTg3,spDistObs3,spDistSigma23);

	TSpatialDistMeasurement sdm1(testTg1,spDistObs1,spDistSigma1,prismH1,prismNb);
	TSpatialDistMeasurement sdm2(testTg2,spDistObs2,spDistSigma23,prismH2,prismNb);
	TSpatialDistMeasurement sdm3(testTg3,spDistObs3,spDistSigma23,prismH3,prismNb);

//	sdm3.setTargetPoint(testTg3);

	cout << "TEST DISTANCE MEASUREMENTS" << endl << endl;
	cout << "Spatial Distances" << endl;
	cout << sdm1.getTargetPoint().getName() << endl;
	cout << sdm1.getMeasKind() << endl;
	cout << sdm1.getDistValue().getMetresValue() << endl;
	cout << sdm1.getSigma().getMetresValue() << endl;
	cout << "prism" << endl;
	cout << sdm1.getPrismNumber() << " / " << sdm2.getPrismHeight().getMetresValue() << endl << endl;
	cout << sdm2.getTargetPoint().getName() << endl;
	cout << sdm2.getMeasKind() << endl;
	cout << sdm2.getDistValue().getMetresValue() << endl;
	cout << sdm2.getSigma().getMetresValue() << endl;
	cout << "prism" << endl;
	cout << sdm2.getPrismNumber() << " / " << sdm2.getPrismHeight().getMetresValue() << endl << endl;
	cout << sdm3.getTargetPoint().getName() << endl;
	cout << sdm3.getMeasKind() << endl;
	cout << sdm3.getDistValue().getMetresValue() << endl;
	cout << sdm3.getSigma().getMetresValue() << endl;
	cout << "prism" << endl;
	cout << sdm3.getPrismNumber() << " / " << sdm3.getPrismHeight().getMetresValue() << endl << endl;

	cout << "Horizontal Distance" << endl;
	cout << hdm1.getTargetPoint().getName() << endl;
	cout << hdm1.getMeasKind() << endl;
	cout << hdm1.getDistValue().getMetresValue() << endl;
	cout << hdm1.getSigma().getMetresValue() << endl << endl;
	cout << hdm2.getTargetPoint().getName() << endl;
	cout << hdm2.getMeasKind() << endl;
	cout << hdm2.getDistValue().getMetresValue() << endl;
	cout << hdm2.getSigma().getMetresValue() << endl << endl;
	cout << hdm3.getTargetPoint().getName() << endl;
	cout << hdm3.getMeasKind() << endl;
	cout << hdm3.getDistValue().getMetresValue() << endl;
	cout << hdm3.getSigma().getMetresValue() << endl << endl;

	cout << "2D Offset" << endl;
	cout << om.getMeasKind() << " / " << om.getLineName() << endl;
	cout << om.getHorOffset().getMetresValue() << " / " << om.getHorSigma().getMetresValue() << endl;
	cout << om.getVertOffset().getMetresValue() << " / " << om.getVertSigma().getMetresValue() << endl << endl;


////////////////////////////////////////////////////////////////////////////////////////////////
// test sur les SpatialROM

	TSpatialDistROM sdrom;
	THorizontalDistROM hdrom;

	sdrom.setSeries("Spatial Distance ROM");
	sdrom.addSpatialDist(&sdm1);
	sdrom.addSpatialDist(&sdm2);
	sdrom.addSpatialDist(&sdm3);
	
	if (sdrom.notInContainer(&sdm2))
		sdrom.addSpatialDist(&sdm2);
	else
		cout << "deja dans la liste!!" << endl;

//	cout << sdrom.getDistMeas(testTg1)->getDistValue().getMetresValue() << endl;

	cout << sdrom.getSeries() << endl;

	SpatialDistMeasIterator iterBmeasSD = sdrom.getDistMeasBeginIterator();
	SpatialDistMeasIterator iterEmeasSD = sdrom.getDistMeasEndIterator();

	while ( iterBmeasSD != iterEmeasSD ) 
	{
		cout << iterBmeasSD->getDistValue().getMetresValue() << endl;
		iterBmeasSD++;
	}
	
	cout << endl;


////////////////////////////////////////////////////////////////////////////////////////////////
// test sur les HorizontalROM

	hdrom.setSeries("Horizontal Distance ROM");
	hdrom.addHorDist(&hdm1);
	hdrom.addHorDist(&hdm2);
//	hdrom.addHorDist(&hdm3);

	if (hdrom.notInContainer(&hdm3))
		hdrom.addHorDist(&hdm3);
	else
		cout << "déjà dans la liste!!" << endl;

	cout << hdrom.getSeries() << endl;

	HorDistMeasIterator iterBmeasHD = hdrom.getDistMeasBeginIterator();
	HorDistMeasIterator iterEmeasHD = hdrom.getDistMeasEndIterator();

	while ( iterBmeasHD != iterEmeasHD )
	{
		cout << iterBmeasHD->getDistValue().getMetresValue() << endl;
		iterBmeasHD++;
	}

	cout << endl;



////////////////////////////////////////////////////////////////////////////////////////////////
// tests sur les ROM de distances spatiales

	TDistMeasStation distSt(testSt);
	
	distSt.addSpatialDistROM(&sdrom);
	distSt.addHorDistROM(&hdrom);
	
	SpatialDistROMIterator iterBromSD = distSt.getSpatialDistROMBeginIterator();
	SpatialDistROMIterator iterEromSD = distSt.getSpatialDistROMEndIterator();

	while ( iterBromSD != iterEromSD )
	{
		cout << iterBromSD->getSeries() << endl;
		cout << iterBromSD->getDistMeas(testTg3)->getTargetPoint().getName() << endl;
		cout << iterBromSD->getDistMeas(testTg3)->getDistValue().getMetresValue() << endl;
		cout << iterBromSD->getDistMeas(testTg3)->getSigma().getMetresValue() << endl;
		iterBromSD++;
	}
	cout << endl;



////////////////////////////////////////////////////////////////////////////////////////////////
// tests sur les ROM de distances horizontales


	HorDistROMIterator iterBromHD = distSt.getHorDistROMBeginIterator();
	HorDistROMIterator iterEromHD = distSt.getHorDistROMEndIterator();

	while ( iterBromHD != iterEromHD ) 
	{
		cout << iterBromHD->getSeries() << endl;
		cout << iterBromHD->getDistMeas(testTg3)->getTargetPoint().getName() << endl;
		cout << iterBromHD->getDistMeas(testTg3)->getDistValue().getMetresValue() << endl;
		cout << iterBromHD->getDistMeas(testTg3)->getSigma().getMetresValue() << endl;
		iterBromHD++;
	}

	cout << endl;











/////////////////////////////////////////////////////////////////////////////////////////////////

	/* THEODOLITE STATION */

	TAngle	orie1(1);
	TAngle	orie2(2);
	TAngle	orie3(3);

	TAngle	sigmaOrie1(LITERAL(0.001));
	TAngle	sigmaOrie2(LITERAL(0.002));
	TAngle	sigmaOrie3(LITERAL(0.003));

	TAngle	angleObsH1(LITERAL(0.785236)); TAngle  angleObsZ1(LITERAL(0.356245));
	TAngle	angleObsH2(LITERAL(0.856321)); TAngle  angleObsZ2(LITERAL(0.451262));
	TAngle	angleObsH3(LITERAL(0.945631)); TAngle  angleObsZ3(LITERAL(0.216354));

	TAngle	sigmaObsH1(LITERAL(0.001526)); TAngle  sigmaObsZ1(LITERAL(0.003215));
	TAngle	sigmaObsH2(LITERAL(0.002005)); TAngle  sigmaObsZ2(LITERAL(0.002991));
	TAngle	sigmaObsH3(LITERAL(0.000998)); TAngle  sigmaObsZ3(LITERAL(0.002554));

	THorAngleMeasurement angHorMeas1(testTg1,angleObsH1,sigmaObsH1);
	THorAngleMeasurement angHorMeas2(testTg2,angleObsH2,sigmaObsH2);
	THorAngleMeasurement angHorMeas3(testTg3,angleObsH3,sigmaObsH3);

	TZenithDistMeasurement angZenMeas1(testTg1,angleObsZ1,sigmaObsZ1);
	TZenithDistMeasurement angZenMeas2(testTg2,angleObsZ2,sigmaObsZ2);
	TZenithDistMeasurement angZenMeas3(testTg3,angleObsZ3,sigmaObsZ3);

	TSpatialPointName stName("station");
	TSpatialPointName tg1Name("target1");
	TSpatialPointName tg2Name("target2");
	TSpatialPointName tg3Name("target3");

	THorAngleMeasurement gisMeas1(tg1Name,orie1,sigmaOrie1);
	THorAngleMeasurement gisMeas2(tg2Name,orie2,sigmaOrie2);
	THorAngleMeasurement gisMeas3(tg3Name,orie3,sigmaOrie3);

	cout << "TEST THEODOLITE MEASUREMENTS" << endl << endl;
	cout << angHorMeas1.getTargetPoint().getName() << endl;
	cout << angHorMeas1.getMeasKind() << endl;	
	cout << angHorMeas1.getAngleValue().getRadiansValue() << endl;
	cout << angHorMeas1.getSigma().getRadiansValue() << endl;
	cout << angZenMeas1.getMeasKind() << endl;
	cout << angZenMeas1.getAngleValue().getRadiansValue() << endl;
	cout << angZenMeas1.getSigma().getRadiansValue() << endl << endl;

	cout << angZenMeas2.getTargetPoint().getName() << endl;
	cout << angHorMeas2.getMeasKind() << endl;
	cout << angHorMeas2.getAngleValue().getRadiansValue() << endl;
	cout << angHorMeas2.getSigma().getRadiansValue() << endl;
	cout << angZenMeas2.getMeasKind() << endl;
	cout << angZenMeas2.getAngleValue().getRadiansValue() << endl;
	cout << angZenMeas2.getSigma().getRadiansValue() << endl << endl;

	cout << angHorMeas3.getTargetPoint().getName() << endl;
	cout << angHorMeas3.getMeasKind() << endl;
	cout << angHorMeas3.getAngleValue().getRadiansValue() << endl;
	cout << angHorMeas3.getSigma().getRadiansValue() << endl;
	cout << angZenMeas3.getMeasKind() << endl;
	cout << angZenMeas3.getAngleValue().getRadiansValue() << endl;
	cout << angZenMeas3.getSigma().getRadiansValue() << endl << endl;
	
	// test sur les classes de ZenithROM et HorROM
	THorAngleROM horAngROM;
	TZenithDistROM zenAngROM;
	
	horAngROM.setSeries("Horizontal ROM");

	horAngROM.addHorAngle(&angHorMeas1);
	horAngROM.addHorAngle(&angHorMeas2);
	horAngROM.addHorAngle(&angHorMeas3);
	
	if (horAngROM.notInContainer(&angHorMeas2))
		horAngROM.addHorAngle(&angHorMeas2);
	else
		cout << "deja dans la liste!!" << endl;

//	cout << horAngROM.getHorAngMeas(testTg1)->getAngleValue().getRadiansValue() << endl;

	cout << horAngROM.getSeries() << endl;

	HorAngMeasIterator iterBmeasHA = horAngROM.getHorAngMeasBeginIterator();
	HorAngMeasIterator iterEmeasHA = horAngROM.getHorAngMeasEndIterator();

	while ( iterBmeasHA != iterEmeasHA )
	{
		cout << iterBmeasHA->getAngleValue().getRadiansValue() << endl;
		iterBmeasHA++;
	}
//	cout << horAngROM.getRefMeas()->getAngleValue().getRadiansValue() << endl;

	cout << endl;




	zenAngROM.setSeries("Zenithal ROM");
	
	zenAngROM.addZenithDist(&angZenMeas1);
	zenAngROM.addZenithDist(&angZenMeas2);
//	zenAngROM.addZenithDist(&angZenMeas3);

	if (zenAngROM.notInContainer(&angZenMeas3))
		zenAngROM.addZenithDist(&angZenMeas3);
	else
		cout << "deja dans la liste!!" << endl;
	
	cout << zenAngROM.getSeries() << endl;
	cout << zenAngROM.getZenithDistMeas(testTg2)->getAngleValue().getRadiansValue() << endl;

	ZenithDistMeasIterator iterBmeasV = zenAngROM.getZenithDistMeasBeginIterator();
	ZenithDistMeasIterator iterEmeasV = zenAngROM.getZenithDistMeasEndIterator();

	while ( iterBmeasV != iterEmeasV ) 
	{
		cout << iterBmeasV->getAngleValue().getRadiansValue() << endl;
		iterBmeasV++;
	}

	cout << endl;


	TGyroOrientationROM orieROM;

	string serie = 	"orientation ROM serie 1";
	orieROM.setSeries(serie);

	orieROM.addGyroOrientation(&gisMeas1);
	orieROM.addGyroOrientation(&gisMeas2);
	orieROM.addGyroOrientation(&gisMeas3);
	
	if (orieROM.notInContainer(&angHorMeas2))
	{
		orieROM.addGyroOrientation(&angHorMeas2);
	}
	else
	{
		cout << "deja dans la liste!!" << endl;
	}

	cout <<"serie :"<< orieROM.getSeries() << endl;

	HorAngMeasIterator iterBmeasGyro = orieROM.getGyroOrieMeasBeginIterator();
	HorAngMeasIterator iterEmeasGyro = orieROM.getGyroOrieMeasEndIterator();

	while ( iterBmeasGyro != iterEmeasGyro)
	{
		cout << iterBmeasGyro->getAngleValue().getRadiansValue() << endl;
		iterBmeasGyro ++;
	}

	cout << endl;



	// tests sur la classe theodolite station
	TTheodoliteStation theo(testSt);

	theo.addHorAngleROM(&horAngROM);
	theo.addZenithDistROM(&zenAngROM);
	theo.addGyroOrieROM(&orieROM);
	

////////////////////////////////////////////////////////////////////////////////////////////////
// tests sur les ROM d angles horizontaux

	HorAngROMIterator iterBromHA = theo.getHorAngROMBeginIterator();
	HorAngROMIterator iterEromHA =theo.getHorAngROMEndIterator();

	while ( iterBromHA != iterEromHA )
	{
		cout << iterBromHA->getSeries() << endl;
		cout << iterBromHA->getHorAngMeas(testTg3)->getTargetPoint().getName() << endl;
		cout << iterBromHA->getHorAngMeas(testTg3)->getAngleValue().getRadiansValue() << endl;
		cout << iterBromHA->getHorAngMeas(testTg3)->getSigma().getRadiansValue() << endl;
		cout << iterBromHA->getRefMeas()->getTargetPoint().getName() << endl;
		cout << iterBromHA->getRefMeas()->getAngleValue().getRadiansValue() << endl;
		cout << iterBromHA->getRefMeas()->getSigma().getRadiansValue() << endl;
		iterBromHA++;
	}


////////////////////////////////////////////////////////////////////////////////////////////////
// tests sur les ROM de distances zenitales

	ZenithDistROMIterator iterBromV = theo.getZenithDistROMBeginIterator();
	ZenithDistROMIterator iterEromV =theo.getZenithDistROMEndIterator();

	while ( iterBromV!=iterEromV )
	{
		cout << iterBromV->getSeries() << endl;
		cout << iterBromV->getZenithDistMeas(testTg3)->getTargetPoint().getName() << endl;
		cout << iterBromV->getZenithDistMeas(testTg3)->getAngleValue().getRadiansValue() << endl;
		cout << iterBromV->getZenithDistMeas(testTg3)->getSigma().getRadiansValue() << endl;
//		cout << iterBromV->getRefMeas()->getTargetPoint().getName() << endl;
//		cout << iterBromV->getRefMeas()->getAngleValue().getRadiansValue() << endl;
//		cout << iterBromV->getRefMeas()->getSigma().getRadiansValue() << endl;
		iterBromV++;
	}

	cout << endl;



////////////////////////////////////////////////////////////////////////////////////////////////
// tests sur les ROM d orientations



	cout<<"Gyro ROM's number : "<<theo.getGyroOrieROMDimension()<<endl;

	cout<<"is serie in list : "<<theo.notInContainer(&orieROM)<<endl;

	//GyroOrieROMIterator iterROM = theo.getGyroOrieROM(serie);

	
	GyroOrieROMIterator iterBromGyro = theo.getGyroOrieROMBeginIterator();
	GyroOrieROMIterator iterEromGyro =theo.getGyroOrieROMEndIterator();

	while ( iterBromGyro != iterEromGyro )
	{
		cout << iterBromGyro->getSeries() << endl;
		cout << iterBromGyro->getGyroOrieMeas(tg1Name)->getTargetPoint().getName() << endl;
		cout << iterBromGyro->getGyroOrieMeas(tg1Name)->getAngleValue().getRadiansValue() << endl;
		cout << iterBromGyro->getGyroOrieMeas(tg1Name)->getSigma().getRadiansValue() << endl;
		iterBromGyro++;
	}
	cout << endl;


////////////////////////////////////////////////////////////////////////////////
//test ECTH ECHO ECSP ECVE
////////////////////////////////////////////////////////////////////////////////

	TLength	offset1(LITERAL(1.12));
	TLength c (49);
	TLength distSigma1(LITERAL(0.0001));
	TLength distSigma2(11111111111);//test des fonction ifNotDoneSet....
	TLength distSigmaPpm1(LITERAL(0.0003));

	string planeName("plane");
	TSpatialLineName lineName (testTg1);

	//TOffsetToTheoPlaneMeasurement meas1(planeName,dist1,distSigma1);
	//TOffsetToVerPlaneMeasurement meas1(planeName,dist1,distSigma1);
	//TOffsetToSpaLineMeasurement meas1(lineName,dist1,distSigma1);
	TOffsetToVerLineMeasurement measECVE1(lineName,offset1,distSigma1);

	measECVE1.ifNotDoneSetSigma(distSigma2);
//	measECVE1.ifNotDoneSetSigmaPpm(distSigmaPpm1);

	//TOffsetToTheoPlaneMeasurement meas2, meas3;
	//TOffsetToVerPlaneMeasurement meas2, meas3;
	//TOffsetToSpaLineMeasurement meas2, meas3;
	TOffsetToVerLineMeasurement measECVE2, measECVE3;

	measECVE2 = measECVE1;

	//TOffsetToTheoPlaneMeasurement meas4 (meas1);
	//TOffsetToVerPlaneMeasurement meas4 (meas1);
	//TOffsetToSpaLineMeasurement meas4 (meas1);
	TOffsetToVerLineMeasurement measECVE4 (measECVE1);
	
	//meas3.setTargetPlane(planeName);
	measECVE3.ifNotDoneSetSigma(distSigma1);
	measECVE3.setId(3);
	measECVE3.setComment("essai commentaire");

	TDistConstants constant (c, TAMeasurement::kFixed);
	measECVE3.ifNotDoneSetMeasConst(constant);


	cout << "Test ECTH, ECHO, ECSP, ECVE" << endl;

//	cout <<"Target Name : "<< meas1.getTargetPlane() << endl;
	cout <<"Target Name : "<< measECVE1.getTargetLineName().getName() << endl;
	cout <<"kind of measure : "<<measECVE1.getMeasKind() << endl;
	cout <<"distance : "<< measECVE1.getLengthValue().getMetresValue() << endl;
//	cout <<"sigmaPpm : "<<measECVE1.getSigmaPpm().getMetresValue() << endl;
	cout <<"sigma : "<<measECVE1.getSigma().getMetresValue() << endl << endl;
	cout << endl;

//	cout <<"Target Name : "<< meas2.getTargetPlane() << endl;
	cout <<"Target Name : "<< measECVE2.getTargetLineName().getName() << endl;
	cout <<"kind of measure : "<<measECVE2.getMeasKind() << endl;
	cout <<"distance : "<< measECVE2.getLengthValue().getMetresValue() << endl;
	cout <<"sigma : "<<measECVE2.getSigma().getMetresValue() << endl << endl;
	cout << endl;

//	cout <<"Target Name : "<< meas3.getTargetPlane() << endl;
	cout <<"Target Name : "<< measECVE3.getTargetLineName().getName() << endl;
	cout <<"kind of measure : "<<measECVE3.getMeasKind() << endl;
	cout <<"distance : "<< measECVE3.getLengthValue().getMetresValue() << endl;
	cout <<"sigma : "<<measECVE3.getSigma().getMetresValue() << endl;
	cout <<"Id : "<< measECVE3.getId()<< endl;
	cout <<"Comment : "<<measECVE3.getComment()<< endl;
//	cout <<"sigmaPpm : "<<measECVE3.getSigmaPpm().getMetresValue() << endl;
	cout <<"DistConstants : "<<measECVE3.getMeasConst().getValue().getMetresValue() << endl << endl;
	cout << endl;

//	cout <<"Target Name : "<< meas4.getTargetPlane() << endl;
	cout <<"Target Name : "<< measECVE4.getTargetLineName().getName() << endl;
	cout <<"kind of measure : "<<measECVE4.getMeasKind() << endl;
	cout <<"distance : "<< measECVE4.getLengthValue().getMetresValue() << endl;
	cout <<"sigma : "<<measECVE4.getSigma().getMetresValue() << endl << endl;
	cout << endl;

	//dist station
	TDistMeasStation dm(stName);
//	TOffsetToTheoPlaneMeasurement meas(lineName,dist1,distSigma1);
//	TOffsetToVerPlaneMeasurement meas(lineName,dist1,distSigma1);
//	TOffsetToSpaLineMeasurement meas(lineName,dist1,distSigma1);
	TOffsetToVerLineMeasurement measECVE(lineName,offset1,distSigma1);

//	dm.addMeasurement(meas);

//	if(!(dm.isOffsetToTheoPlaneMeasSet()))
//	if(!(dm.isOffsetToVerPlaneMeasSet()))
//	if(!(dm.isOffsetToSpaLineMeasSet()))
	if(dm.notInContainer(&measECVE))
	{
		dm.addOffsetToVerLineMeas(&measECVE);
	//	cout<<"dist value : "<<dm.getOffsetToTheoPlaneMeas()->getDistValue().getMetresValue()<<endl;
	//	cout<<"dist value : "<<dm.getOffsetToVerPlaneMeas()->getDistValue().getMetresValue()<<endl;
	//	cout<<"dist value : "<<dm.getOffsetToSpaLineMeas()->getDistValue().getMetresValue()<<endl;
		OffsetToVerLineMeasIterator itECVEbeg = dm.getOffsetToVerLineMeasBeginIterator();
		OffsetToVerLineMeasIterator itECVEend = dm.getOffsetToVerLineMeasEndIterator();

		while(itECVEbeg != itECVEend)
		{
			cout<<"dist value : "<<itECVEbeg->getLengthValue().getMetresValue()<<endl;
			itECVEbeg++;
		}
	}
	else
	{
		cout<<"EC measurement already set"<<endl;
	}



	return;
};
	
	

