// SPDX-FileCopyrightText: 2025 CERN

// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

///////////#include <string>
#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TLength.h"

#include "TRotation.h"
#include "TRotationMatrix.h"
#include "TTranslation.h"
#include "TEnlargement.h"

#include "TSpatialPosition.h"
#include "TVReferenceFrame.h"
#include "TVRefFrameTransformation.h"

#include "THelmertRefFrameTRansform.h"

#include "TGeodeticRefFrame.h"
#include "TReferenceEllipsoid.h"

#include "TModifiedLocalAstronomicalRF.h"
//#include "TGC2IMLATransformation.h"

//#include "TModifiedLocalGeodeticRF.h"

#include "TSpatialPoint.h"
#include "TSpatialPointName.h"

#include <iostream>
//#include "TXYHg2XYHeTransformation.h"



void main()
{
	
/*	cout.setf(ios_base::fixed,ios_base::floatfield);

	TSpatialPosition P3(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
	TPositionVector pv3(LITERAL(4387471.2929123), LITERAL(465158.5961008), LITERAL(4590473.7950682), TCoordSysFactory::k3DCartesian);	
	P3.setCoordinates(pv3);

	TSpatialPosition P2(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	TAngle phi, lambda;
	phi.setGonsValue(LITERAL(51.401284151381));
	lambda.setGonsValue(LITERAL(6.787226063805));
	TLength h;
	h.setMetresValue(LITERAL(2.4494467));
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);
	pv.setStatus(TVNumericValue::kKnown);
	P2.setCoordinates(pv);



	
	// ellipsoidal and cartesian coordinates for CGRF
	cout.precision(7);
	cout <<"P2 :"<<endl;
	cout <<"X : "<<P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout <<"Y : "<<P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout <<"Z : "<<P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	cout.precision(7);
	cout <<"P2 :"<<endl;
	cout <<"Phi : "<<P2.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getGonsValue() << endl;
	cout <<"Lambda : "<<P2.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getGonsValue() << endl;
	cout <<"H : "<<P2.getCoordinates(TCoordSysFactory::kGeodetic).getH().getKMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;

	cout.precision(7);
	cout <<"P2 :"<<endl;
	cout <<"X : "<< P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getKMetresValue() << endl;
	cout <<"Y : "<< P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getKMetresValue() << endl;
	cout <<"Z : "<< P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getKMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	// transformations between reference frames

	TModifiedLocalAstronomicalRF* localRF;
	TFreeVector falseOrigin(LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), TCoordSysFactory::k3DCartesian);
	TSpatialPosition origin (TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
	TPositionVector pvOri(LITERAL(4000471.2929123), LITERAL(400058.5961008), LITERAL(4000473.7950682), TCoordSysFactory::k3DCartesian);	
	origin.setCoordinates(pvOri);

	localRF = new TModifiedLocalAstronomicalRF("Instrument Local Ref Frame",
												TRefSystemFactory::kCG1985Machine,
												origin,
												falseOrigin,
												TAngle(LITERAL(0.0)),
												TAngle(LITERAL(0.0)));
	
	P2.transform(localRF);

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;

	
*/

/*	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;

	

	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kROMA40));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;



	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;




	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;




	
	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;






	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kROMA40));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;






	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kITRF97));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;






	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernXYHe));
//	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;






	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernX0Y0He));
//	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernXYHe));
//	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;






	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernXYHg85Machine));
//	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernXYHe));
//	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

	cout.precision(7);
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;






	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;




	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLGp0));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kLAp0));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << P2.getRefFrame()->getName() << endl << endl;





	P2.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << endl;
	cout << P2.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;

	cout << P2.getRefFrame()->getName() << endl << endl;*/





	//construction d'une transformation d helmert
	//trans entre ccs et cgrf sphere
	TAngle rx, ry, rz;
	rx.setGonsValue(-LITERAL(42.726243230216));
	ry.setGonsValue(-LITERAL(25.285434244947));
	rz.setGonsValue(-LITERAL(77.864346765085));
	TRotation rs(TRotationMatrix::kRzyx, rx.getRadiansValue(), ry.getRadiansValue(), rz.getRadiansValue());
	//translation pour situer le centre de la sphere
	TLength txs (LITERAL(4381882.331989)), tys (LITERAL(461505.530464)), tzs (LITERAL(4598944.364158));
	TTranslation transls(txs, tys, tzs);
	//facteur d echelle
	TEnlargement ks (LITERAL(1.0));


	THelmertRefFrameTransform* helmert =
		new THelmertRefFrameTransform(
			TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS),
			TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRFSphere),
			ks,
			rs,
			transls);


/*	TVRefFrameTransformation* clone = helmert->clone();
	delete clone;
	delete helmert*/

/*	TVRefFrameTransformation* tvPtr = helmert;
	delete tvPtr;*/

/*	TARefFrameTransformation* taPtr = helmert;
	delete taPtr;*/

	delete helmert;

	//delete graph
	TRefSystemFactory::getRefSystemFactory()->deleteRefSystemFactory();
	TCoordSysFactory::getCoordSysFactoryPtr()->deleteCoordSysFactory();
//	delete localRF;
	int i = 0;
	cin >> i;
	
	return;

}





