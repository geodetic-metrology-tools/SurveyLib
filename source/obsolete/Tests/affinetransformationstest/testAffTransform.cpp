// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <iostream>
#include <iomanip>
#include <string>
using namespace std;



#include  "TLength.h"
#include  "TAngle.h"
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TRotationMatrix.h"
#include  "TEnlargement.h"
#include  "TRotation.h"
#include  "TTranslation.h"
#include  "TReflection.h"
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
#include  "TAffineTransformWrapper.h"
#include  "TVAffineTransformation.h"





void main ()
{
	



//--------------------------------------------------------------------------------------------------------------------------------------------------------//

	//cout.setf(ios_base::fixed,ios_base::floatfield);
	//cout.precision(5);

	// OBJETS TEST
	// TPositionVector
	TPositionVector pv(1, 2, 3, TCoordSysFactory::k3DCartesian);
/*	cout << "position vector :\n" << pv.getX().getMetresValue() << endl;
	cout << pv.getY().getMetresValue() << endl;
	cout << pv.getZ().getMetresValue() << endl;
	cout << "status : " << pv.getStatus() << endl << endl;*/

	// TFreeVector
	TFreeVector fv(3, 2, 1, TCoordSysFactory::k3DCartesian);
/*	cout << "free vector :\n" << fv.getX().getMetresValue() << endl;
	cout << fv.getY().getMetresValue() << endl;
	cout << fv.getZ().getMetresValue() << endl;
	cout << "status : " << fv.getStatus() << endl << endl;*/


	// TRotationMatrix
	TAngle a(LITERAL(0.0)), b(LITERAL(0.0)), c, d;
	c=TAngle::piBy2();
	TRotationMatrix rmx(TRotationMatrix::kRzyx, a.getRadiansValue(),b.getRadiansValue(),
		c.getRadiansValue());
/*	cout << "rotation matrix :\n" << rmx.getElt(0,0) << " " << rmx.getElt(0,1) << " " << rmx.getElt(0,2) << endl;
	cout << rmx.getElt(1,0) << " " << rmx.getElt(1,1) << " " << rmx.getElt(1,2) << endl;
	cout << rmx.getElt(2,0) << " " << rmx.getElt(2,1) << " " << rmx.getElt(2,2) << endl;
	cout << "status : " << rmx.getStatus() << endl << endl;*/
	


	
	
	
	// TEST TENLARGEMENT

	TEnlargement enlarge(LITERAL(2.57));
//	cout << "enlargement status:" << enlarge.getStatus() << endl << endl;
		
			// transformations
	// transformation with a null status
	pv.setStatus(TVNumericValue::kNull);
	//cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
	enlarge.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	//fv.setStatus(TVNumericValue::kNull);
	//cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;

	enlarge.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	//rmx.setStatus(TVNumericValue::kNull);
	//cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
	//cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
	//cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;

	enlarge.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

			// inverse transformation
	enlarge.invert();
	enlarge.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	enlarge.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	enlarge.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;


	// bon




	// TEST TTRANSLATION
	TLength tx(LITERAL(5.0)), ty(LITERAL(100.0)), tz(LITERAL(2000.0));

	TTranslation trans(tx, ty, tz);
	//trans.setStatus(TVNumericValue::kNull);
//	cout << "translation status : " << trans.getStatus() << endl << endl;

			// transformations
	//pv.setStatus(TVNumericValue::kNull);
	trans.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	trans.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	trans.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

			// inverse transformation
	TTranslation t = trans.inverse();

	t.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	t.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	t.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

	// bon



	// TEST TROTATION

//	TAngle a,b,c,d;
	a.setGonsValue(100);
	b.setGonsValue(30);
	c.setGonsValue(10);
	d.setGonsValue(-10);

	TXAxisRotation rx(a.getRadiansValue());
	TYAxisRotation ry(b.getRadiansValue());
	TZAxisRotation rz(c.getRadiansValue());

	TRotation rot(TRotationMatrix::kRzyx, LITERAL(0.66), LITERAL(0.335), LITERAL(1.2));
//	cout << "rotation status : " << rot.getStatus() << endl;

	Angles ang;
	
		// transformations
	rx.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	rx.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	rx.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

	ang = rmx.getAngles(TRotationMatrix::kRzyx);
//	cout << "omega : " << ang.omega.getRadiansValue() <<
//		" phi : " << ang.phi.getRadiansValue() <<
//		" kappa : " << ang.kappa.getRadiansValue() << endl <<endl ;

		// inverse transformation
	rx.invert();

	rx.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	rx.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	rx.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

	ang = rmx.getAngles(TRotationMatrix::kRzyx);
//	cout << "omega : " << ang.omega.getRadiansValue() <<
//		" phi : " << ang.phi.getRadiansValue() <<
//		" kappa : " << ang.kappa.getRadiansValue() << endl <<endl ;
		

	// bon sf Pb si angle = pi avec atan2q



	// TEST TREFLECTION

	TReflection reflectx(TReflection::kXEqual0);
	TReflection reflecty(TReflection::kYEqual0);
	TReflection reflectz(TReflection::kZEqual0);
	TReflection reflectxy(TReflection::kXEqualY);
	TReflection reflectxz(TReflection::kXEqualZ);
	TReflection reflectyz(TReflection::kYEqualZ);

		//transformations
		// transformations
	reflectyz.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	reflectyz.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	reflectyz.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

	
		// inverse transformation
	reflectyz.invert();

	reflectyz.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	reflectyz.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	reflectyz.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

	//bon




	//	TEST THELMERTTRANSFORMATION
	THelmertTransformation helmert(enlarge, rx, trans);
	THelmertTransformation helmi=helmert.inverse();

//	cout << "helmert transformations status : " << helmert.getStatus() << "  " << helmi.getStatus() << endl << endl;
	
	helmert.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	helmert.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	helmert.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;

	
	helmi.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	helmi.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	helmi.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;


	// bon 



		// TEST TCOMPOSITE 
	//verifier les résultats numériques à partir de ce breakpoint

	TCompositeAffTransform comp, comp3, comp4;
	//ry.setStatus(TVNumericValue::kNull);

	comp = helmert*trans*ry*reflectxy*enlarge;
//	cout<<comp.getComposite().size()<<endl;
//	cout<<comp.getComposite().size();

	comp = helmert*trans;
//	cout<<comp.getComposite().size()<<endl;

	comp3 = comp*ry*reflectxy*enlarge;
//	cout<<comp3.getComposite().size()<<endl;

	comp4 = comp*ry*reflectxy*enlarge;

//	cout<<comp4.getComposite().size()<<endl;

    
	comp3 = rot*comp;
//	cout << "composite status : " << comp.getStatus() << endl << endl;*/
	
	comp3.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	comp3.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	comp3.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;


			// inverse transformation
	comp3.invert();
	comp3.transform(pv);
//	cout << "position vector :\n" << pv.getX().getMetresValue()<<" "<<pv.getY().getMetresValue()<<" "<<pv.getZ().getMetresValue()<<endl;
//	cout << "status : " << pv.getStatus() << endl << endl;

	comp3.transform(fv);
//	cout << "free vector :\n" << fv.getX().getMetresValue()<<" "<<fv.getY().getMetresValue()<<" "<<fv.getZ().getMetresValue()<<endl;
//	cout << "status : " << fv.getStatus() << endl << endl;

	comp3.transform(rmx);
//	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
//	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
//	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
//	cout << "status : " << rmx.getStatus() << endl << endl;*/

		

	enlarge.transform(rmx);
	reflectxy.transform(rmx);
	ry.transform(rmx);
	trans.transform(rmx);
	helmert.transform(rmx);
	rot.transform(rmx);
	cout << "rotation matrix :\n" <<rmx.getElt(0,0)<<" "<<rmx.getElt(0,1)<<" "<<rmx.getElt(0,2)<<" "<<endl;
	cout<<rmx.getElt(1,0)<<" "<<rmx.getElt(1,1)<<" "<<rmx.getElt(1,2)<<" "<<endl;
	cout<<rmx.getElt(2,0)<<" "<<rmx.getElt(2,1)<<" "<<rmx.getElt(2,2)<<" "<<endl;
	cout << "status : " << rmx.getStatus() << endl << endl;

	
	cout<<"on est la"<<endl;
	
	
	// bon

	

	return;
}

