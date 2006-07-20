#include "TXYHg2XYHeTransformation.h"
//#include "TGraph.h"
//#include "TPositionVector.h"
//#include "TLength.h"

#include <string>
#include <iostream>
using namespace std;

void main() {

/*	NE MARCHE PAS !!	
	string grs("GRS80");
	TReferenceEllipsoid* pGRS80 = new TReferenceEllipsoid(grs);
	pGRS80->setAAndESquared(6378137.0, 0.0066943800229);
	pGRS80->setEllId(kGRS80);
	fRefEllList.push_back(pGRS80);

	string cgrf("CGRF");
	TGeodeticRefFrame* pCGRF = new TGeodeticRefFrame(cgrf);
	pCGRF->setRefFrameId(kCGRF);
	fRefFrameList.push_back(pCGRF);

	TSpatialPosition origin(pCGRF);
	TAngle phi, lambda;
	TLength H;
	phi.setGonsValue(51.3692);
	lambda.setGonsValue(6.72124);
	H.setMetresValue(433.65921);
	
	origin.setPLH( phi, lambda, H, pGRS80 );

	TModifiedLocalGeodeticRF* pLG = new TModifiedLocalGeodeticRF( "LG CCS", pGRS80, origin, pCGRF);
	pLG->setRefFrameId(kLG);
	fRefFrameList.push_back(pLG);
  
	TAngle etaP0(0), xsiP0(0), dAlphaP0(0);
	TGraphLocalAstronomicalRF* pLA = new TGraphLocalAstronomicalRF( "LA CCS", etaP0, xsiP0, dAlphaP0, pLG );
	string ccs("CCS");
	TFreeVector falseOrigin;	
	falseOrigin.setXYZComponents(2000, 2097.79265, 2433.66000);
	TAngle omega(0), phi2(0), kappa;
	kappa.setGonsValue(37.77864);
	TAModifiedLocalAstronomicalRF* pCCS = new TGraphMLARF(ccs, falseOrigin,
		pLA, omega, phi2, kappa);*/

	TXYHeProjection* xyhe = new TXYHeProjection("test",TGraph::getGraph()->getEllipsoid(TGraph::kGRS80),TGraph::getGraph()->getRefFrame(TGraph::kCCS));
	TXYHgProjection* xyhg("test1",TGraph::getGraph()->getGeoid(TGraph::kCG1985),xyhe)
	TXYHg2XYHeTransformation transfo(xyhg);
	TPositionVector pv(2000,6500,520),pv1;
	pv1=transfo.transform(pv);
	cout << pv1.getX() << endl;
	cout << pv1.getY() << endl;
	cout << pv1.getZ() << endl;
	return;
}

