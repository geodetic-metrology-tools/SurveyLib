//////////////////////////////////////////////////////
// test file for TReferenceFrame
//////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>

#include  "TLength.h"
#include  "TAngle.h"
#include  "TSpatialPosition.h"
#include  "TPositionVector.h"
#include  "TSpatialVector.h"
#include  "TFreeVector.h"
#include  "TSpatialOrientation.h"
#include  "TRotationMatrix.h"
#include  "TEnlargement.h"
#include  "TRotation.h"
#include  "TTranslation.h"
#include  "TReflection.h"
#include  "THelmertTransformation.h"
#include  "TCompositeAffTransform.h"
#include  "TAffineTransformWrapper.h"
#include  "TVAffineTransformation.h"

#include <string>
using namespace std;



void main ()
{
	



//--------------------------------------------------------------------------------------------------------------------------------------------------------//

	// OBJETS TEST
	// TPositionVector
	TPositionVector pv(1, 2, 3);

	// TFreeVector
	TFreeVector fv(3, 2, 1);

	// TRotationMatrix
	TRotationMatrix rmx(TAngle(0.0),TAngle(0.0), TAngle::piBy2());



	// TEST TENLARGEMENT

	TEnlargement enlarge(2);
		
/*			// transformations
	TPositionVector	tpv = (enlarge.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (enlarge.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = enlarge.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;


	// bon




	// TEST TTRANSLATION

	TTranslation trans(5, 100, 2000);

			// transformations
	TPositionVector	tpv = (trans.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (trans.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = trans.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;

	TTranslation t = trans.inverse();
	tpv = (t.transform(tpv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	// bon




*/	// TEST TROTATION

	TXAxisRotation rx(TAngle::piBy2());
	TYAxisRotation ry(TAngle::piBy4());
	TZAxisRotation rz(TAngle::piBy2());
	TRotation rot(0.66, 0.335, 1.2);

/*		// transformations
		
	TPositionVector	tpv = (rot.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TRotation r = rot.inverse();
	//rot.invert();
	tpv = (r.transform(tpv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (rx.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = rot.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;

	

	// bon sf Pb si angle = pi avec atan2

*/

	// TEST TREFLECTION

	TReflection reflectx(TReflection::kXEqual0);
	TReflection reflecty(TReflection::kYEqual0);
	TReflection reflectz(TReflection::kZEqual0);
	TReflection reflectxy(TReflection::kXEqualY);
	TReflection reflectxz(TReflection::kXEqualZ);
	TReflection reflectyz(TReflection::kYEqualZ);

/*		//transformations
	TPositionVector	tpv = (reflectx.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	tpv = (reflecty.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	tpv = (reflectz.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	tpv = (reflectxy.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	tpv = (reflectxz.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	tpv = (reflectyz.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;


	TFreeVector tfv = (reflecty.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	reflectyz.invert();
	tpv = (reflectyz.transform(tpv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;


	//bon




*/	//	TEST THELMERTTRANSFORMATION

//	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232);
//	TRotation rot(6.28318117478,0.0000323393631389, 0.0000120374552168);
	TTranslation trans(94.8497984, 101.7575271, -170.7549129);
	THelmertTransformation helm2(rot, trans);
	THelmertTransformation helmi=helm2.inverse();
/*	TPositionVector	tpv = (helm2.transform(pv));
	cout<<setprecision(12)<< tpv[0].getMetresValue()<<" "<<setprecision(12)<<tpv[1].getMetresValue()<<" "<<setprecision(12)<<tpv[2].getMetresValue()<<endl;
	tpv = (helmi.transform(tpv));
	cout<<setprecision(12)<< tpv[0].getMetresValue()<<" "<<setprecision(12)<<tpv[1].getMetresValue()<<" "<<setprecision(12)<<tpv[2].getMetresValue()<<endl;

/*
	// bon 



	// TEST TCOMPOSITE
*/
	TCompositeAffTransform comp;
	comp = rx*rz;
	TPositionVector	tpv = (comp.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;


/*	comp = reflectx*reflecty*reflectz;

	TPositionVector	tpv = (comp.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;

	// bon

	
	comp.preMult(helm2);
	comp.preMult(reflectx);

		// transformation
	TPositionVector	tpv = (comp.transform(pv));
	cout<<setprecision(12)<< tpv[0].getMetresValue()<<" "<<setprecision(12)<<tpv[1].getMetresValue()<<" "<<setprecision(12)<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;

	// bon


	comp = reflectx*(helm2);

		// transformation
	TPositionVector	tpv = (comp.transform(pv));
	cout<<setprecision(12)<< tpv[0].getMetresValue()<<" "<<setprecision(12)<<tpv[1].getMetresValue()<<" "<<setprecision(12)<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;
*/
	// bon

	// TEST OPERATOR *

/*	//TEnlarge
		//*double
	TEnlargement enlarge2 = enlarge*2;

		// transformations
	TPositionVector	tpv = (enlarge2.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (enlarge2.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = enlarge2.transform(rmx);
	cout<<setprecision(5)<<trx(0,0)<<" "<<setprecision(5)<<trx(0,1)<<" "<<setprecision(5)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(1,0)<<" "<<setprecision(5)<<trx(1,1)<<" "<<setprecision(5)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(5)<<trx(2,0)<<" "<<setprecision(5)<<trx(2,1)<<" "<<setprecision(5)<<trx(2,2)<<" "<<endl;
		//bon
		

		//*translation
	TTranslation enlarge2 = enlarge*trans;

		// transformations
	TPositionVector	tpv = (enlarge2.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (enlarge2.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = enlarge2.transform(rmx);
	cout<<setprecision(12)<<trx(0,0)<<" "<<setprecision(12)<<trx(0,1)<<" "<<setprecision(12)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(1,0)<<" "<<setprecision(12)<<trx(1,1)<<" "<<setprecision(12)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(2,0)<<" "<<setprecision(12)<<trx(2,1)<<" "<<setprecision(12)<<trx(2,2)<<" "<<endl;
		//bon

		//*trotation
	comp = enlarge*rot;

	TPositionVector	tpv = (comp.transform(pv));
	cout<< tpv[0].getMetresValue()<<" "<<tpv[1].getMetresValue()<<" "<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp.transform(fv));
	cout<< tfv[0].getMetresValue()<<" "<<tfv[1].getMetresValue()<<" "<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp.transform(rmx);
	cout<<setprecision(12)<<trx(0,0)<<" "<<setprecision(12)<<trx(0,1)<<" "<<setprecision(12)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(1,0)<<" "<<setprecision(12)<<trx(1,1)<<" "<<setprecision(12)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(2,0)<<" "<<setprecision(12)<<trx(2,1)<<" "<<setprecision(12)<<trx(2,2)<<" "<<endl;
		//bon

*/
		//*treflection
//	comp = enlarge*reflectxz;
/*	TPositionVector	tpv = (comp.transform(pv));
	cout<<setprecision(12)<< tpv[0].getMetresValue()<<" "<<setprecision(12)<<tpv[1].getMetresValue()<<" "<<setprecision(12)<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp.transform(fv));
	cout<<setprecision(12)<< tfv[0].getMetresValue()<<" "<<setprecision(12)<<tfv[1].getMetresValue()<<" "<<setprecision(12)<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp.transform(rmx);
	cout<<setprecision(12)<<trx(0,0)<<" "<<setprecision(12)<<trx(0,1)<<" "<<setprecision(12)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(1,0)<<" "<<setprecision(12)<<trx(1,1)<<" "<<setprecision(12)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(2,0)<<" "<<setprecision(12)<<trx(2,1)<<" "<<setprecision(12)<<trx(2,2)<<" "<<endl;
	//bon

		//*tcomposite
	TCompositeAffTransform comp2 = (comp*reflectxz);
	TPositionVector tpv = (comp2.transform(pv));
	cout<<setprecision(12)<< tpv[0].getMetresValue()<<" "<<setprecision(12)<<tpv[1].getMetresValue()<<" "<<setprecision(12)<<tpv[2].getMetresValue()<<endl;

	TFreeVector tfv = (comp2.transform(fv));
	cout<<setprecision(12)<< tfv[0].getMetresValue()<<" "<<setprecision(12)<<tfv[1].getMetresValue()<<" "<<setprecision(12)<<tfv[2].getMetresValue()<<endl;

	TRotationMatrix trx = comp2.transform(rmx);
	cout<<setprecision(12)<<trx(0,0)<<" "<<setprecision(12)<<trx(0,1)<<" "<<setprecision(12)<<trx(0,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(1,0)<<" "<<setprecision(12)<<trx(1,1)<<" "<<setprecision(12)<<trx(1,2)<<" "<<endl;
	cout<<setprecision(12)<<trx(2,0)<<" "<<setprecision(12)<<trx(2,1)<<" "<<setprecision(12)<<trx(2,2)<<" "<<endl;
		//bon
*/	

	// TEST TRANSFO POSITION, SPATIALVECTOR, SPATIALORIENTATION
//idem
}

