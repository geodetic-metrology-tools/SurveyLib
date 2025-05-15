// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TGeodeticRefFrame.h"
#include "TLocalAstronomicalRefFrame.h"
#include "TReferenceEllipsoid.h"
#include "TLA2LGTransformation.h"
#include "TCernParabolicGeoid.h"
#include "TCompositeAffTransform.h"

#include "THelmertRefFrameTransform.h"



void main(){

	string essai = "RF1";
	string essai2 = "RF2";
	string essai3 = "RF3";
	string essai4 = "RF4";

	string geodetic = "Geodetic Ref Frame";

	string ell = "Reference Ellipsoid";
	string geoide = "CERN Parabolic Geoid";

	TReferenceEllipsoid Ell(ell);
	TReferenceEllipsoid* refEll = &Ell;

	
	TGeodeticRefFrame GRF(geodetic);
	TGeodeticRefFrame* pGRF = &GRF;

	TSpatialPosition origin(pGRF);
	TLength coord(2000), coord2(2098);
	origin.setXCoord(coord);
	origin.setYCoord(coord2);
	origin.setZCoord(coord);
	
	TLocalGeodeticRefFrame rframe(essai, refEll, origin, pGRF), rframe2(essai2, refEll, origin, pGRF);
	TLocalGeodeticRefFrame *p_rframe = &rframe, *p_rframe2 = &rframe2;

	TCernParabolicGeoid geoid( geoide, 0.535, -0.096, 48.772*TAngle::gonsToRadsFactor(), p_rframe, refEll, p_rframe);
	TCernParabolicGeoid* pGeoid = &geoid;

	TLocalAstronomicalRefFrame rframe3(essai3, pGeoid, p_rframe), rframe4(essai4, pGeoid, p_rframe);
	TLocalAstronomicalRefFrame *p_rframe3 = &rframe3, *p_rframe4 = &rframe4;
	//TGeodeticRefFrame* p_rframe = new TGeodeticRefFrame(essai);



	double omega = (TAngle::piBy4()).getRadiansValue();
	TRotation rotation(omega,0,0), rotation2(0,omega,0), rotation3(-omega, omega,0);
	rotation.setStatus(TAAffineTransformation::kKnown);
	rotation2.setStatus(TAAffineTransformation::kKnown);
	rotation3.setStatus(TAAffineTransformation::kKnown);

	TRotation *p_rotation = &rotation, *p_rotation2 = &rotation2, *p_rotation3 = &rotation3;

	THelmertTransformation helm1, helm2, helm3, helm4;
	helm1.setRotation(rotation);
	helm1.setStatus(TAAffineTransformation::kKnown);
	helm2.setRotation(rotation2);
	helm2.setStatus(TAAffineTransformation::kKnown);
	//helm3.setRotation(rotation3);

	THelmertTransformation *p1 = &helm1, *p2 = &helm2;
	//, *p3 = &helm3;



	THelmertRefFrameTransform LA2LG31(p_rframe3, p_rframe, p1);
	LA2LG31.getTransform();
	THelmertRefFrameTransform LA2LG32(p_rframe3, p_rframe2, p2);
	
	TLA2LGTransformation LA2LG41(p_rframe4, p_rframe);
	TLA2LGTransformation LA2LG42(p_rframe4, p_rframe2);


/*	string geodetic = "GeodeticRefFrame";
	string localAstro = "LocalAstronomicalRefFrame";

	string refEllipsoid = "ReferenceEllipsoid";

	TReferenceEllipsoid refEll(refEllipsoid);
	TReferenceEllipsoid* p_refEll = &refEll;


	TGeodeticRefFrame geodeticRF(geodetic, p_refEll);
	TGeodeticRefFrame* p_geodeticRF = &geodeticRF;
	TLocalAstronomicalRefFrame localAstroRF(localAstro, p_refEll);
	TLocalAstronomicalRefFrame* p_localAstroRF = &localAstroRF;

	TLA2LGTransformation LA2LG(p_localAstroRF, p_geodeticRF);
*/
	cout << GRF.getName() << endl;

	cout << LA2LG31.getDestinationFrame()->getName() << endl;
	cout << LA2LG31.getSourceFrame()->getName() << endl;
	cout << LA2LG31.isInitialised() << endl << endl;

	cout << LA2LG41.getDestinationFrame()->getName() << endl;
	cout << LA2LG41.getSourceFrame()->getName() << endl;
	cout << LA2LG41.isInitialised() << endl << endl;

	cout << LA2LG32.getDestinationFrame()->getName() << endl;
	cout << LA2LG32.getSourceFrame()->getName() << endl;
	cout << LA2LG32.isInitialised() << endl << endl;

	cout << LA2LG42.getDestinationFrame()->getName() << endl;
	cout << LA2LG42.getSourceFrame()->getName() << endl;
	cout << LA2LG42.isInitialised() << endl << endl;

	TPositionVector pv,pv2;
	pv.setX(1);
	pv.setY(2);
	pv.setZ(3);


/*	
	TXAxisRotation rx(1);
	cout<<rx(1,0)<<" "<<rx(1,1)<<" "<<rx(1,2)<<endl;

	TYAxisRotation ry(1.5);

	TCompositeAffTransform transfo;
	transfo = rx*ry*rx;
	pv2 = transfo.transform(pv);

*/

	/*TCompositeAffTransform* comp;
	comp = &transfo;
	pv2 = comp->transform(pv);
	cout << pv2.getX() << endl;
	cout << pv2.getY() << endl;
	cout << pv2.getZ() << endl << endl;
	*/

//	comp = LA2LG31.getTransformer();
//  comp->transform(pv);

	pv2 = LA2LG31.transform(pv);
	cout << pv2.getX() << endl;
	cout << pv2.getY() << endl;
	cout << pv2.getZ() << endl << endl;
 
	pv2 = LA2LG31.inverse()->transform(pv2);
	cout << pv2.getX() << endl;
	cout << pv2.getY() << endl;
	cout << pv2.getZ() << endl << endl;

	pv2 = LA2LG31.transform(pv);
	cout << pv2.getX() << endl;
	cout << pv2.getY() << endl;
	cout << pv2.getZ() << endl << endl;
 
 

	return;

}
