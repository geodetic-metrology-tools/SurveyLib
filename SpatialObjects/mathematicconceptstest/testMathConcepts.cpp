#include <iostream>
#include <string>
#include <limits>
using namespace std;

#include "TANumericValue.h"
#include "TAngle.h"
#include "TLength.h"
#include "TFreeVector.h"
#include "TMatrix.h"
#include "T3DMatrix.h"
#include "TRotationMatrix.h"
#include "TPositionVector.h"
#include "TColumnVector.h"
#include "TDouble.h"
#include "TCoordSysFactory.h"


/*** overloaded iterator to produce a matrix output ***/
// why there is no implementation?
/*
std::ostream& operator<< (std::ostream& ostr,const TMatrix& m) {
	ostr << "(" << m.numRows() << "," << m.numCols() << ") Status: " << m.getStatus() << ", Error: " << m.getError().c_str() << std::endl;
	for (size_t r=0;r<m.numRows();r++)
	{
		for (size_t c=0;c<m.numCols();c++)
			ostr << std::setw(9) << m(r,c);
		ostr << std::endl;
	}
	return ostr;
}


/*** class to show instanziation while using overloaded operators *****/
/*
class copyingexample {
	public:
		copyingexample() {
			object_counter++;
			objects_in_mem++;
			std::cout << "Constructor Object #" << object_counter << "; " 
				<< objects_in_mem << " Objects in Memory." << std::endl;
		};
		~copyingexample() {
			objects_in_mem--;
			std::cout << "Destructor Object #" << object_counter << "; " 
				<< objects_in_mem << " Objects in Memory." << std::endl;
		}
	protected:
		static size_t object_counter;
		static size_t objects_in_mem;
};

size_t copyingexample::object_counter = 0;
size_t copyingexample::objects_in_mem = 0;

copyingexample operator+(const copyingexample&,const copyingexample&)
{
	return copyingexample();
}
*/

void main()
{
	//test TANumericValue
	TANumericValue num;
	num.setStatus(TANumericValue::kKnown);
	cout<<num.getStatus()<<endl;
	cout<<num.isNull()<<endl;
	

	//test TAngle
	TAngle ang1, ang2, ang3, ang4, ang5, ang6, ang7;


	double d1,d2;

	d1=0;
	d2=10;
	ang1=ang1.aTan2(d2,d1);
//	ang2=ang2.atan2(d2,d1);
	cout<<ang1.getGonsValue()<<endl<<endl;
//	cout<<ang2.getGonsValue()<<endl<<endl;


	ang1.setStatus(TANumericValue::kNull);
	cout<<"angle1: "<<ang1.getStatus()<<endl;

	ang1.setRadiansValue(1.5);
	ang2.setGonsValue(100.00);
	ang3.setDMSValue(45, 0, 0);


	cout<<"angle1: "<<ang1.getRadiansValue()<<" "<<ang1.getStatus()<<endl;
	cout<<"angle2: "<<ang2.getGonsValue()<<endl;
	cout<<"angle3: "<<ang3.getDegreesValue()<<" "<<ang3.getMinutesValue()<<" "<<ang3.getSecondsValue()<<endl;

	cout<<"angle3: "<<ang3.getGonsValue()<<endl;
	cout<<"angle3: "<<ang3.getRadiansValue()<<endl<<endl;
	
	cout<<"angle2: "<<endl;
	cout<<ang2.cosine()<<endl;
	cout<<ang2.sine()<<endl;
	cout<<ang2.tangent()<<endl<<endl;

	cout<<ang2.cosineh()<<endl;
	cout<<ang2.sineh()<<endl;
	cout<<ang2.tangenth()<<endl<<endl;

	ang4.setRadiansValue((ang4.aCos(1)).getRadiansValue());
	cout<<ang4.getGonsValue()<<endl;
	ang5.setRadiansValue((ang5.aSin(1)).getRadiansValue());
	cout<<ang5.getGonsValue()<<endl;
	ang6.setRadiansValue((ang6.aTan(1)).getRadiansValue());
	cout<<ang6.getGonsValue()<<endl;
	ang7.setRadiansValue((ang7.aTan2(1,2)).getRadiansValue());
	cout<<ang7.getGonsValue()<<endl<<endl;

	ang2.setRadiansValue(ang2.getRadiansValue()+ang2.getRadiansValue());
	cout<<ang2.getGonsValue()<<endl;

	ang2.setRadiansValue(ang2.getRadiansValue()-.5*ang2.getRadiansValue());
	cout<<ang2.getGonsValue()<<endl<<endl;

	//test operateur
	cout<<"test des operateur de TAngle"<<endl<<endl;

	TAngle tangle1, tangle2, tangle3;
	tangle1.setRadiansValue(1);
	tangle2.setRadiansValue(3);
	TDouble tdouble (5);

//	tangle1.setStatus(TVNumericValue::kNull);
//	tdouble.setStatus(TVNumericValue::kNull);

	cout<<"tangle1:"<<tangle1.getRadiansValue()<<", status:"<<tangle1.getStatus()<<endl;
	cout<<"tangle2:"<<tangle2.getRadiansValue()<<", status:"<<tangle2.getStatus()<<endl;
	cout<<"tangle3:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;
	cout<<"tdouble:"<<tdouble.getValue()<<", status:"<<tdouble.getStatus()<<endl<<endl;
	

	tangle3=tangle2+tangle1;
	cout<<"tangle3=tangle2+tangle1:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;


	tangle3+=tangle1;
	cout<<"tangle3+=tangle1:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;

	tangle3=tangle3-tangle1;
	cout<<"tangle3=tangle3-tangle1:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;

	tangle3-=tangle1;
	cout<<"tangle3-=tangle1:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;

	tangle3=tangle1*3;
	cout<<"tangle3=tangle1*3:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;

	tangle3=3*tangle1;
	cout<<"tangle3=3*tangle1:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;

	tangle1*=3;
	cout<<"tangle1*=3:"<<tangle1.getRadiansValue()<<", status:"<<tangle1.getStatus()<<endl;

	tangle3=tangle1*tdouble;
	cout<<"tangle3=tangle1*tdouble:"<<tangle3.getRadiansValue()<<", status:"<<tangle3.getStatus()<<endl;

	tangle1*=tdouble;
	cout<<"tangle1*=tdouble:"<<tangle1.getRadiansValue()<<", status:"<<tangle1.getStatus()<<endl<<endl;

	
	

	//test TLength
	cout<<"TEST TLength"<<endl<<endl;
	TLength len, len1;
	len.setMetresValue(12.00);
	cout<<len.getKMetresValue()<<" "<<len.getMMetresValue()<<endl;

	len.setKMetresValue(1);
	cout<<len.getMetresValue()<<endl;

	len.setMMetresValue(-1500);
	cout<<len.getMetresValue()<<endl;



	len1=len;

	len1.setMetresValue((len1+len).getMetresValue());
	cout<<len1.getMetresValue()<<endl;
	len1.setMetresValue((len1-.5*len).getMetresValue());
	cout<<len1.getMetresValue()<<endl;

	len1+=len;
	cout<<len1.getMetresValue()<<endl;

	len1-=len;
	cout<<len1.getMetresValue()<<endl;

	len1*=2;
	cout<<len1.getMetresValue()<<endl<<endl;


	//test operateur
	cout<<"test des operateur de TLength"<<endl<<endl;

	TLength tlength1, tlength2, tlength3;
	tlength1.setMetresValue(1);
	tlength2.setMetresValue(3);
	TDouble tdoublelen (5);

	tlength1.setStatus(TVNumericValue::kNull);
//	tdoublelen.setStatus(TVNumericValue::kNull);

	cout<<"tlength1:"<<tlength1.getMetresValue()<<", status:"<<tlength1.getStatus()<<endl;
	cout<<"tlength2:"<<tlength2.getMetresValue()<<", status:"<<tlength2.getStatus()<<endl;
	cout<<"tlength3:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;
	cout<<"tdoublelen:"<<tdoublelen.getValue()<<", status:"<<tdoublelen.getStatus()<<endl<<endl;
	

	tlength3=tlength2+tlength1;
	cout<<"tlength3=tlength2+tlength1:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;


	tlength3+=tlength1;
	cout<<"tlength3+=tlength1:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;

	tlength3=tlength3-tlength1;
	cout<<"tlength3=tlength3-tlength1:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;

	tlength3-=tlength1;
	cout<<"tlength3-=tlength1:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;

	tlength3=tlength1*3;
	cout<<"tlength3=tlength1*3:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;

	tlength3=3*tlength1;
	cout<<"tlength3=3*tlength1:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;

	tlength1*=3;
	cout<<"tlength1*=3:"<<tlength1.getMetresValue()<<", status:"<<tlength1.getStatus()<<endl;

	tlength3=tlength1*tdoublelen;
	cout<<"tlength3=tlength1*tdoublelen:"<<tlength3.getMetresValue()<<", status:"<<tlength3.getStatus()<<endl;

	tlength1*=tdoublelen;
	cout<<"tlength1*=tdoublelen:"<<tlength1.getMetresValue()<<", status:"<<tlength1.getStatus()<<endl<<endl;

	



	//test TFreeVector
	cout<<"TEST TFreeVector"<<endl;

	TLength L0;
	L0.setMetresValue(2);
	TLength L1;
	L1.setMetresValue(5);
	TLength L2;
	L2.setMetresValue(-4);

	TFreeVector v1(1,2,3, TCoordSysFactory::k3DCartesian);
	TFreeVector v2(v1);
	v2.setCoordSys(TCoordSysFactory::k3DCartesian);
	v2.setZ(L0);

	TFreeVector v3 (TCoordSysFactory::k3DCartesian);
	v3.setStatus(TVNumericValue::kKnown);
	
	v3.setX(L0); v3.setY(L1); v3.setZ(L2);

	TFreeVector v4 (v3);
	TDouble d;
	d.setStatus(TVNumericValue::kKnown);
	d.setValue(5);
	cout<<"d value:"<<d.getValue()<<", status;"<<d.getStatus()<<endl;
	
	cout<<"v1:"<<(v1.getX()).getMetresValue()<<","<<(v1.getY()).getMetresValue()<<","<<(v1.getZ()).getMetresValue()<<",status:"<<v1.getStatus()<<",sys coord:"<<v1.getCoordSys()<<endl;
	cout<<"v2:"<<(v2.getX()).getMetresValue()<<","<<(v2.getY()).getMetresValue()<<","<<(v2.getZ()).getMetresValue()<<",status:"<<v2.getStatus()<<",sys coord:"<<v2.getCoordSys()<<endl;
	cout<<"v3:"<<(v3.getX()).getMetresValue()<<","<<(v3.getY()).getMetresValue()<<","<<(v3.getZ()).getMetresValue()<<",status:"<<v3.getStatus()<<",sys coord:"<<v3.getCoordSys()<<endl;
	cout<<"v4:"<<(v4.getX()).getMetresValue()<<","<<(v4.getY()).getMetresValue()<<","<<(v4.getZ()).getMetresValue()<<",status:"<<v4.getStatus()<<",sys coord:"<<v4.getCoordSys()<<endl;

	v4=v1+v2;
	cout<<"v4=v1+v2:"<<(v4.getX()).getMetresValue()<<","<<(v4.getY()).getMetresValue()<<","<<(v4.getZ()).getMetresValue()<<",status:"<<v4.getStatus()<<",sys coord:"<<v4.getCoordSys()<<endl;

	v4=v1-v2;
	cout<<"v4=v1-v2:"<<(v4.getX()).getMetresValue()<<","<<(v4.getY()).getMetresValue()<<","<<(v4.getZ()).getMetresValue()<<",status:"<<v4.getStatus()<<",sys coord:"<<v4.getCoordSys()<<endl;

	v1-=v4;
	cout<<"v1-=v4:"<<(v1.getX()).getMetresValue()<<","<<(v1.getY()).getMetresValue()<<","<<(v1.getZ()).getMetresValue()<<",status:"<<v1.getStatus()<<",sys coord:"<<v1.getCoordSys()<<endl;

	v1+=v2;
	cout<<"v1+=v2:"<<(v1.getX()).getMetresValue()<<","<<(v1.getY()).getMetresValue()<<","<<(v1.getZ()).getMetresValue()<<",status:"<<v1.getStatus()<<",sys coord:"<<v1.getCoordSys()<<endl;

	v1=v3*6;
	cout<<"v1=v3*6:"<<(v1.getX()).getMetresValue()<<","<<(v1.getY()).getMetresValue()<<","<<(v1.getZ()).getMetresValue()<<",status:"<<v1.getStatus()<<",sys coord:"<<v1.getCoordSys()<<endl;

	v1=v2*2;
	cout<<"v1=v2*2:"<<(v1.getX()).getMetresValue()<<","<<(v1.getY()).getMetresValue()<<","<<(v1.getZ()).getMetresValue()<<",status:"<<v1.getStatus()<<",sys coord:"<<v1.getCoordSys()<<endl;

	v1=v2*d;
	//v2.setStatus(TVNumericValue::kNull);
	//v1=d*v2;
	cout<<"v1=v2*d:"<<(v1.getX()).getMetresValue()<<","<<(v1.getY()).getMetresValue()<<","<<(v1.getZ()).getMetresValue()<<",status:"<<v1.getStatus()<<",sys coord:"<<v1.getCoordSys()<<endl;

//	cout<<"longueur de v1:"<<v1.length()<<endl<<endl<<endl<<endl;
	

	


	//test TPositionVector
	cout<<"TEST TPositionVector"<<endl;

	TPositionVector vp1(1,2,3, TCoordSysFactory::k3DCartesian);
	TPositionVector vp2(vp1);
	//vp2.setStatus(TVNumericValue::kKnown);
	//vp2.setCoordSys(TCoordSysFactory::k2DCartesian);

	TFreeVector vf3 (TCoordSysFactory::k3DCartesian);
	TLength Lx;
	Lx.setMetresValue(2);
	TLength Ly;
	Ly.setMetresValue(5);
	TLength Lz;
	Lz.setMetresValue(-4);
	vf3.setX(Lx); vf3.setY(Ly); vf3.setZ(Lz);vf3.setStatus(TVNumericValue::kKnown);

	TPositionVector vp4 (1,2,5,TCoordSysFactory::k3DCartesian);
	TDouble db;
	db.setValue(4);
	db.setStatus(TVNumericValue::kKnown);

	
	cout<<"declaration"<<endl;
	cout<<"db value:"<<db.getValue()<<", status;"<<db.getStatus()<<endl;
	cout<<"vp1:"<<(vp1.getX()).getMetresValue()<<","<<(vp1.getY()).getMetresValue()<<","<<(vp1.getZ()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;
	cout<<"vp2:"<<(vp2.getX()).getMetresValue()<<","<<(vp2.getY()).getMetresValue()<<","<<(vp2.getZ()).getMetresValue()<<",status:"<<vp2.getStatus()<<",sys coord:"<<vp2.getCoordSys()<<endl;
	cout<<"vf3:"<<(vf3.getX()).getMetresValue()<<","<<(vf3.getY()).getMetresValue()<<","<<(vf3.getZ()).getMetresValue()<<",status:"<<vf3.getStatus()<<",sys coord:"<<vf3.getCoordSys()<<endl;
	cout<<"vp4:"<<(vp4.getX()).getMetresValue()<<","<<(vp4.getY()).getMetresValue()<<","<<(vp4.getZ()).getMetresValue()<<",status:"<<vp4.getStatus()<<",sys coord:"<<vp4.getCoordSys()<<endl<<endl<<endl;


	cout<<"fonction"<<endl;
//	cout<<"distance entre de vp1 et vp4:"<<vp1.dist(vp4)<<endl;

	vp4=vp1+vf3;
	cout<<"vp4=vp1+vf3:"<<(vp4.getX()).getMetresValue()<<","<<(vp4.getY()).getMetresValue()<<","<<(vp4.getZ()).getMetresValue()<<",status:"<<vp4.getStatus()<<",sys coord:"<<vp4.getCoordSys()<<endl;

	vf3=vp1-vp2;
	cout<<"vf3=vp1-vp2:"<<(vf3.getX()).getMetresValue()<<","<<(vf3.getY()).getMetresValue()<<","<<(vf3.getZ()).getMetresValue()<<",status:"<<vf3.getStatus()<<",sys coord:"<<vf3.getCoordSys()<<endl;

	vp2+=vf3;
	cout<<"vp2+=vf3:"<<(vp2.getX()).getMetresValue()<<","<<(vp2.getY()).getMetresValue()<<","<<(vp2.getZ()).getMetresValue()<<",status:"<<vp2.getStatus()<<",sys coord:"<<vp2.getCoordSys()<<endl;

	vp1=vp2*2;
	cout<<"vp1=vp2*2:"<<(vp1.getX()).getMetresValue()<<","<<(vp1.getY()).getMetresValue()<<","<<(vp1.getZ()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;

	vp1=vp2*db;
	cout<<"vp1=vp2*db:"<<(vp1.getX()).getMetresValue()<<","<<(vp1.getY()).getMetresValue()<<","<<(vp1.getZ()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl<<endl;

	cout<<"set & get"<<endl;
	cout<<"vp1:"<<(vp1.getPhiEllipsoid()).getGonsValue()<<","<<(vp1.getLambdaEllipsoid()).getGonsValue()<<","<<(vp1.getH()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;
	cout<<"status de la 1ieme coord:"<< vp1.getPhiEllipsoid().getStatus()<<endl;
	cout<<"status de la 2ieme coord:"<< vp1.getLambdaEllipsoid().getStatus()<<endl;
	cout<<"status de la 3ieme coord:"<< vp1.getH().getStatus()<<endl<<endl;
		

	cout<<"set et get de 2+h"<<endl;
	vp1.setCoordSys(TCoordSysFactory::k2DPlusH);
	cout<<"vp1:"<<(vp1.getX()).getMetresValue()<<","<<(vp1.getY()).getMetresValue()<<","<<(vp1.getZ()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;
	cout<<"status de la 3ieme coord:"<< vp1.getZ().getStatus()<<endl;
	TLength H;
	H.setKMetresValue(5);
	vp1.setH(H);
	cout<<"vp1:"<<(vp1.getX()).getMetresValue()<<","<<(vp1.getY()).getMetresValue()<<","<<(vp1.getH()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;
	cout<<"status de la 3ieme coord:"<< vp1.getH().getStatus()<<endl<<endl;

	cout<<"set et get de geodetic"<<endl;
	vp1.setCoordSys(TCoordSysFactory::kGeodetic);
	cout<<"vp1:"<<(vp1.getX()).getMetresValue()<<","<<(vp1.getY()).getMetresValue()<<","<<(vp1.getZ()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;
	cout<<"status de la 1ieme coord:"<< vp1.getX().getStatus()<<endl;
	cout<<"status de la 2ieme coord:"<< vp1.getY().getStatus()<<endl;
	cout<<"status de la 3ieme coord:"<< vp1.getZ().getStatus()<<endl<<endl;
	
	TAngle A,B;
	A.setGonsValue(90);
	B.setGonsValue(180);
//	vp1.setCoordSys(TCoordSysFactory::k3DCartesian);
//		cout<<vp1.setPhiEllipsoid(A)<<endl;
//		cout<<vp1.setLambdaEllipsoid(B)<<endl;
//		cout<<vp1.setH(H)<<endl;
	vp1.setPhiEllipsoid(A);
	vp1.setLambdaEllipsoid(B);
	vp1.setH(H);
	cout<<"vp1:"<<(vp1.getPhiEllipsoid()).getGonsValue()<<","<<(vp1.getLambdaEllipsoid()).getGonsValue()<<","<<(vp1.getH()).getMetresValue()<<",status:"<<vp1.getStatus()<<",sys coord:"<<vp1.getCoordSys()<<endl;
	cout<<"status de la 1ieme coord:"<< vp1.getPhiEllipsoid().getStatus()<<endl;
	cout<<"status de la 2ieme coord:"<< vp1.getLambdaEllipsoid().getStatus()<<endl;
	cout<<"status de la 3ieme coord:"<< vp1.getH().getStatus()<<endl<<endl;
		
	
	//test TColumnVector
	cout<<"TEST TColumnVector"<<endl;
	TDouble TD;
	TD.setStatus(TVNumericValue::kKnown);
	TD.setValue(-3);
	TColumnVector TC1;
	TC1.setDimension(4);
	TColumnVector TC2 (4);
	TC2(0)=5;
	TC2(1)=2;
	TC2(2)=3;
	TC2(3)=4;
	TColumnVector TC3(TC2);
	//TC3.setStatus(TVNumericValue::kNull);
	//TColumnVector TC3;
	//TC3.setDimension(3);
	//TC3=TC2;
	cout<<"TD:"<<TD.getValue()<<", status:"<<TD.getStatus()<<endl;
	cout<<"TC1:"<<TC1(0)<<","<<TC1(1)<<","<<TC1(2)<<","<<TC1(3)<<", status:"<<TC1.getStatus()<<", dimension:"<<TC1.dimension()<<endl;
	cout<<"TC2:"<<TC2(0)<<","<<TC2(1)<<","<<TC2(2)<<","<<TC2(3)<<", status:"<<TC2.getStatus()<<", dimension:"<<TC2.dimension()<<endl;
	cout<<"TC3:"<<TC3(0)<<","<<TC3(1)<<","<<TC3(2)<<","<<TC3(3)<<", status:"<<TC3.getStatus()<<", dimension:"<<TC3.dimension()<<endl<<endl;	

	TC3=4;
	cout<<"TC3=4:"<<TC3(0)<<","<<TC3(1)<<","<<TC3(2)<<","<<TC3(3)<<", status:"<<TC3.getStatus()<<", dimension:"<<TC3.dimension()<<endl;	

	//cout<<TC3.getFirstEltAdr()<<endl;


	TC1=TC2+TC3;
	cout<<"TC1=TC2+TC3:"<<TC1(0)<<","<<TC1(1)<<","<<TC1(2)<<","<<TC1(3)<<", status:"<<TC1.getStatus()<<", dimension:"<<TC1.dimension()<<endl;
	
	TC2+=TC3;
	cout<<"TC2+=TC3:"<<TC2(0)<<","<<TC2(1)<<","<<TC2(2)<<","<<TC2(3)<<", status:"<<TC2.getStatus()<<", dimension:"<<TC2.dimension()<<endl;
		
	TC1=TC1-TC3;
	cout<<"TC1=TC1-TC3:"<<TC1(0)<<","<<TC1(1)<<","<<TC1(2)<<","<<TC1(3)<<", status:"<<TC1.getStatus()<<", dimension:"<<TC1.dimension()<<endl;
		
	TC2-=TC3;
	cout<<"TC2-=TC3:"<<TC2(0)<<","<<TC2(1)<<","<<TC2(2)<<","<<TC2(3)<<", status:"<<TC2.getStatus()<<", dimension:"<<TC2.dimension()<<endl;
	
	TC1=TC3*5;
	cout<<"TC1=TC3*5:"<<TC1(0)<<","<<TC1(1)<<","<<TC1(2)<<","<<TC1(3)<<", status:"<<TC1.getStatus()<<", dimension:"<<TC1.dimension()<<endl;
		
	TC1=TC3*TD;
	cout<<"TC1=TC3*TD:"<<TC1(0)<<","<<TC1(1)<<","<<TC1(2)<<","<<TC1(3)<<", status:"<<TC1.getStatus()<<", dimension:"<<TC1.dimension()<<endl;
	
	TD=TC3*TC2;
	cout<<"TC3*TC2="<<TD.getValue()<<",status:"<<TD.getStatus()<<endl;

	TC2.setStatus(TVNumericValue::kKnown);
	TMatrix mx (1,4);
	mx=TC2.transposed();
	cout<<"mx:"<<mx(0,0)<<","<<mx(0,1)<<","<<mx(0,2)<<","<<mx(0,3)<<", status:"<<mx.getStatus()<<endl<<endl<<endl;
		
	
	//Test TMatrix
	cout<<"TEST TMatrix"<<endl;

	TMatrix mx1(2,2);
	TMatrix mx2 (mx1);
	TMatrix mx3;
	TMatrix mx4;
	mx4.setDimensions(4,4);
	mx4(0,0)=1;
	mx4(0,1)=2;
	mx4(0,2)=3;
	mx4(0,3)=7;
	mx4(1,0)=2;
	mx4(1,1)=5;
	mx4(1,2)=6;
	mx4(1,3)=8;
	mx4(2,0)=3;
	mx4(2,1)=6;
	mx4(2,2)=2;
	mx4(2,3)=9;
	mx4(3,0)=7;
	mx4(3,1)=8;
	mx4(3,2)=9;
	mx4(3,3)=1;

	mx4.invert();

	mx4.setStatus(TVNumericValue::kKnown);
	TColumnVector colvec (2);
	//colvec.setStatus(TVNumericValue::kNull);
	colvec(0) = 2;
	colvec(1) = 3;
	TDouble dou (5);
	//dou.setStatus(TVNumericValue::kNull);

	cout<<"Matrices initiales"<<endl;
	cout<<"mx1:[("<<mx1(0,0)<<","<<mx1(0,1)<<"),("<<mx1(1,0)<<","<<mx1(1,1)<<")], status:"<<mx1.getStatus()<<endl;
	cout<<"mx2:[("<<mx2(0,0)<<","<<mx2(0,1)<<"),("<<mx2(1,0)<<","<<mx2(1,1)<<")], status:"<<mx2.getStatus()<<endl;
	cout<<"mx3: nombre de ligne:"<<mx3.numRows()<<", nombre de col:"<<mx3.numCols()<<", status:"<<mx3.getStatus()<<endl;
	cout<<"mx4:[("<<mx4(0,0)<<","<<mx4(0,1)<<"),("<<mx4(1,0)<<","<<mx4(1,1)<<")], status:"<<mx4.getStatus()<<endl;
	cout<<"colvec:("<<colvec(0)<<","<<colvec(1)<<"), status:"<<colvec.getStatus()<<endl;
	cout<<"dou:"<<dou.getValue()<<", status:"<<dou.getStatus()<<endl;
	TMatrix mx5 (2,3);
	cout<<"mx5:[("<<mx5(0,0)<<","<<mx5(0,1)<<","<<mx5(0,2)<<"),("<<mx5(1,0)<<","<<mx5(1,1)<<","<<mx5(1,2)<<")], status:"<<mx5.getStatus()<<"\n"<<endl;



	cout<<"test fonction"<<endl;

	//test du 30/04/2003 methode inverse base sur le code en C:
	mx1.setDimensions(4,4);
	mx1 = 0;
	mx1 = mx4;
	cout<<"mx1:[("<<mx1(0,0)<<","<<mx1(0,1)<<","<<mx1(0,2)<<","<<mx1(0,3)<<"),("<<mx1(1,0)<<","<<mx1(1,1)<<","<<mx1(1,2)<<","<<mx1(1,3)<<"),("<<mx1(2,0)<<","<<mx1(2,1)<<","<<mx1(2,2)<<","<<mx1(2,3)<<"),("<<mx1(3,0)<<","<<mx1(3,1)<<","<<mx1(3,2)<<","<<mx1(3,3)<<")], status:"<<mx1.getStatus()<<endl;
	TMatrix mx9;
	mx9.setDimensions(4,4);
	mx9 = mx4.inverseSym();
	cout<<"mx9:[("<<mx9(0,0)<<","<<mx9(0,1)<<","<<mx9(0,2)<<","<<mx9(0,3)<<"),("<<mx9(1,0)<<","<<mx9(1,1)<<","<<mx9(1,2)<<","<<mx9(1,3)<<"),("<<mx9(2,0)<<","<<mx9(2,1)<<","<<mx9(2,2)<<","<<mx9(2,3)<<"),("<<mx9(3,0)<<","<<mx9(3,1)<<","<<mx9(3,2)<<","<<mx9(3,3)<<")], status:"<<mx1.getStatus()<<endl;
	mx1 = mx9 * mx1;
	cout<<"mx1:[("<<mx1(0,0)<<","<<mx1(0,1)<<","<<mx1(0,2)<<","<<mx1(0,3)<<"),("<<mx1(1,0)<<","<<mx1(1,1)<<","<<mx1(1,2)<<","<<mx1(1,3)<<"),("<<mx1(2,0)<<","<<mx1(2,1)<<","<<mx1(2,2)<<","<<mx1(2,3)<<"),("<<mx1(3,0)<<","<<mx1(3,1)<<","<<mx1(3,2)<<","<<mx1(3,3)<<")], status:"<<mx1.getStatus()<<endl;

	//mx2.setStatus(TVNumericValue::kNull);
	mx2.initDiag(6);
	cout<<"mx2:[("<<mx2(0,0)<<","<<mx2(0,1)<<"),("<<mx2(1,0)<<","<<mx2(1,1)<<")], status:"<<mx2.getStatus()<<endl;
	mx5.initDiag(6);
	cout<<"mx5:[("<<mx5(0,0)<<","<<mx5(0,1)<<","<<mx5(0,2)<<"),("<<mx5(1,0)<<","<<mx5(1,1)<<","<<mx5(1,2)<<")], status:"<<mx5.getStatus()<<endl;
	cout<<"mx5.initDiag(6), return"<<mx5.initDiag(6)<<endl;


	mx3.setDimensions(2,2);
	cout<<"mx3:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;
	mx3=mx4.transposed();
	cout<<"col"<<mx3.numCols()<<endl;
	cout<<"col"<<mx3.numRows()<<endl;
//	cout<<"mx3=mx4.transposed():[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;
//	mx2=mx3;
//	cout<<"mx2=mx3:[("<<mx2(0,0)<<","<<mx2(0,1)<<"),("<<mx2(1,0)<<","<<mx2(1,1)<<")], status:"<<mx2.getStatus()<<endl;


	cout<<"la matrice mx3 est t elle reversible?:"<<mx3.invert()<<endl;
	cout<<"mx3:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;
	mx3=mx3*mx2;
	cout<<"mx3:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;
	mx4=mx2.inverse();
	cout<<"mx4:[("<<mx4(0,0)<<","<<mx4(0,1)<<"),("<<mx4(1,0)<<","<<mx4(1,1)<<")], status:"<<mx4.getStatus()<<endl;
	mx4.clear();
	cout<<"mx4:[("<<mx4(0,0)<<","<<mx4(0,1)<<"),("<<mx4(1,0)<<","<<mx4(1,1)<<")], status:"<<mx4.getStatus()<<endl;
	mx4=2;
	cout<<"mx4:[("<<mx4(0,0)<<","<<mx4(0,1)<<"),("<<mx4(1,0)<<","<<mx4(1,1)<<")], status:"<<mx4.getStatus()<<endl;
	
	mx5=3;
	cout<<"mx5:[("<<mx5(0,0)<<","<<mx5(0,1)<<","<<mx5(0,2)<<"),("<<mx5(1,0)<<","<<mx5(1,1)<<","<<mx5(1,2)<<")], status:"<<mx5.getStatus()<<endl;
	cout<<"la matrice mx5 est t elle reversible?:"<<mx5.invert()<<endl;
	TMatrix mx6 (3,2);
	mx6=mx5.transposed();
	cout<<"mx6:[("<<mx6(0,0)<<","<<mx6(0,1)<<"),("<<mx6(1,0)<<","<<mx6(1,1)<<"),("<<mx6(2,0)<<","<<mx6(2,1)<<")], status:"<<mx6.getStatus()<<endl<<endl;


	//mx3.setStatus(TVNumericValue::kNull);
	mx1=mx2+mx3;
	cout<<"mx1=mx2+mx3:[("<<mx1(0,0)<<","<<mx1(0,1)<<"),("<<mx1(1,0)<<","<<mx1(1,1)<<")], status:"<<mx1.getStatus()<<endl;

	mx3+=mx1;
	cout<<"mx3+=mx1:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;

	//mx2.setStatus(TVNumericValue::kNull);
	mx1=mx4-mx2;
	cout<<"mx1=mx4-mx2:[("<<mx1(0,0)<<","<<mx1(0,1)<<"),("<<mx1(1,0)<<","<<mx1(1,1)<<")], status:"<<mx1.getStatus()<<endl;

	mx4-=mx2;
	cout<<"mx4-=mx2:[("<<mx4(0,0)<<","<<mx4(0,1)<<"),("<<mx4(1,0)<<","<<mx4(1,1)<<")], status:"<<mx4.getStatus()<<endl;
	//cout<<"mx6-=mx2:[("<<mx6(0,0)<<","<<mx6(0,1)<<"),("<<mx6(1,0)<<","<<mx6(1,1)<<"),("<<mx6(2,0)<<","<<mx6(2,1)<<")], status:"<<mx6.getStatus()<<endl<<endl;

	mx6=mx6*mx2;
	//cout<<"mx1=mx2*mx3:[("<<mx1(0,0)<<","<<mx1(0,1)<<"),("<<mx1(1,0)<<","<<mx1(1,1)<<")], status:"<<mx1.getStatus()<<endl;
	cout<<"mx6=mx6*mx2:[("<<mx6(0,0)<<","<<mx6(0,1)<<"),("<<mx6(1,0)<<","<<mx6(1,1)<<"),("<<mx6(2,0)<<","<<mx6(2,1)<<")], status:"<<mx6.getStatus()<<endl<<endl;

	mx6*=mx2;
	//cout<<"mx3*=mx2:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;
	cout<<"mx6*=mx2:[("<<mx6(0,0)<<","<<mx6(0,1)<<"),("<<mx6(1,0)<<","<<mx6(1,1)<<"),("<<mx6(2,0)<<","<<mx6(2,1)<<")], status:"<<mx6.getStatus()<<endl<<endl;

	TColumnVector colvecbis;
	colvecbis.setDimension(3);
	colvecbis=mx6*colvec;
	cout<<"colvecbis=mx6*colvec:("<<colvecbis(0)<<","<<colvecbis(1)<<","<<colvecbis(2)<<"), status:"<<colvecbis.getStatus()<<endl;

	mx3=mx2*2;
	cout<<"mx3=mx2*2:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;

	mx3=mx2*dou;
	cout<<"mx3=mx2*dou:[("<<mx3(0,0)<<","<<mx3(0,1)<<"),("<<mx3(1,0)<<","<<mx3(1,1)<<")], status:"<<mx3.getStatus()<<endl;

	colvec=mx3.eqnSolve(colvec);
	cout<<"colvec=mx3.eqnSolve(colvec):("<<colvec(0)<<","<<colvec(1)<<"), status:"<<colvec.getStatus()<<endl<<endl<<endl;



	//test TRotationMatrix
	cout<<"TEST de TRotationMatrix"<<endl<<endl;

	TRotationMatrix r1;
	r1.setStatus(TVNumericValue::kKnown);
	TRotationMatrix r2(r1);
	TRotationMatrix r3 (TRotationMatrix::kRzxy,1,2,3);
	TFreeVector free (1,2,3,TCoordSysFactory::k3DCartesian);
	TPositionVector pos (4,5,6,TCoordSysFactory::k3DCartesian);

	cout<<"Matrices initiales"<<endl;
	cout<<"r1:[	("<<r1.getElt(0,0)<<","<<r1.getElt(0,1)<<","<<r1.getElt(0,2)<<"),"<<endl
				<<"	("<<r1.getElt(1,0)<<","<<r1.getElt(1,1)<<","<<r1.getElt(1,2)<<"),"<<endl
				<<"	("<<r1.getElt(2,0)<<","<<r1.getElt(2,1)<<","<<r1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r1.getStatus()<<", sys coord:"<<r1.getCoordSys()<<endl;
	cout<<"r2:[	("<<r2.getElt(0,0)<<","<<r2.getElt(0,1)<<","<<r2.getElt(0,2)<<"),"<<endl
				<<"	("<<r2.getElt(1,0)<<","<<r2.getElt(1,1)<<","<<r2.getElt(1,2)<<"),"<<endl
				<<"	("<<r2.getElt(2,0)<<","<<r2.getElt(2,1)<<","<<r2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r2.getStatus()<<", sys coord:"<<r2.getCoordSys()<<endl;
	cout<<"r3:[	("<<r3.getElt(0,0)<<","<<r3.getElt(0,1)<<","<<r3.getElt(0,2)<<"),"<<endl
				<<"	("<<r3.getElt(1,0)<<","<<r3.getElt(1,1)<<","<<r3.getElt(1,2)<<"),"<<endl
				<<"	("<<r3.getElt(2,0)<<","<<r3.getElt(2,1)<<","<<r3.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r1.getStatus()<<", sys coord:"<<r1.getCoordSys()<<endl;
	cout<<"free:("<<free.getX().getMetresValue()<<","<<free.getY().getMetresValue()<<","<<free.getZ().getMetresValue()<<"), status:"<<free.getStatus()<<", sys coord:"<<free.getCoordSys()<<endl;
	cout<<"pos:("<<pos.getX().getMetresValue()<<","<<pos.getY().getMetresValue()<<","<<pos.getZ().getMetresValue()<<"), status:"<<pos.getStatus()<<", sys coord:"<<pos.getCoordSys()<<endl<<endl;

	
	cout<<"test fonction mat rotation"<<endl;
//	double a(TAngle::pi().getRadiansValue()),b(2),c(0);
	double a(1),b(2),c(3);
//	cout<<r2.setAllRotations(TRotationMatrix::kRzxy,a,b,c)<<endl;
	r2.setAllRotations(TRotationMatrix::kRzxy,a,b,c);
	r2.setStatus(TVNumericValue::kKnown);
	cout<<"r2:[	("<<r2.getElt(0,0)<<","<<r2.getElt(0,1)<<","<<r2.getElt(0,2)<<"),"<<endl
				<<"	("<<r2.getElt(1,0)<<","<<r2.getElt(1,1)<<","<<r2.getElt(1,2)<<"),"<<endl
				<<"	("<<r2.getElt(2,0)<<","<<r2.getElt(2,1)<<","<<r2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r2.getStatus()<<", sys coord:"<<r2.getCoordSys()<<endl;
	
	Angles angle = r2.getAngles(TRotationMatrix::kRzxy);
	cout<<"angles de r2:"<<angle.omega.getRadiansValue()<<","<<angle.phi.getRadiansValue()<<","<<angle.kappa.getRadiansValue()<<endl<<endl;

	//r2.setStatus(TVNumericValue::kNull);
	//r2.setCoordSys(TCoordSysFactory::kGeodetic);
	r1=r2;
	cout<<"r1=r2:[	("<<r1.getElt(0,0)<<","<<r1.getElt(0,1)<<","<<r1.getElt(0,2)<<"),"<<endl
				<<"	("<<r1.getElt(1,0)<<","<<r1.getElt(1,1)<<","<<r1.getElt(1,2)<<"),"<<endl
				<<"	("<<r1.getElt(2,0)<<","<<r1.getElt(2,1)<<","<<r1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r1.getStatus()<<", sys coord:"<<r1.getCoordSys()<<endl<<endl;

	//cout<<"r2 est elle reversible? :"<<r2.invert()<<endl;
	r2=r2.inverse();
	cout<<"r2:[	("<<r2.getElt(0,0)<<","<<r2.getElt(0,1)<<","<<r2.getElt(0,2)<<"),"<<endl
				<<"	("<<r2.getElt(1,0)<<","<<r2.getElt(1,1)<<","<<r2.getElt(1,2)<<"),"<<endl
				<<"	("<<r2.getElt(2,0)<<","<<r2.getElt(2,1)<<","<<r2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r2.getStatus()<<", sys coord:"<<r2.getCoordSys()<<endl<<endl;

	r1=r1*r2;
	cout<<"r1=r1*r2;:[	("<<r1.getElt(0,0)<<","<<r1.getElt(0,1)<<","<<r1.getElt(0,2)<<"),"<<endl
				<<"	("<<r1.getElt(1,0)<<","<<r1.getElt(1,1)<<","<<r1.getElt(1,2)<<"),"<<endl
				<<"	("<<r1.getElt(2,0)<<","<<r1.getElt(2,1)<<","<<r1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r1.getStatus()<<", sys coord:"<<r1.getCoordSys()<<endl<<endl;

	//r3.setStatus(TVNumericValue::kKnown);
	//r3.setCoordSys(TCoordSysFactory::kGeodetic);
	r1=r1*r3;
	cout<<"r1=r1*r3;:[	("<<r1.getElt(0,0)<<","<<r1.getElt(0,1)<<","<<r1.getElt(0,2)<<"),"<<endl
				<<"	("<<r1.getElt(1,0)<<","<<r1.getElt(1,1)<<","<<r1.getElt(1,2)<<"),"<<endl
				<<"	("<<r1.getElt(2,0)<<","<<r1.getElt(2,1)<<","<<r1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r1.getStatus()<<", sys coord:"<<r1.getCoordSys()<<endl<<endl;

	//r2.setStatus(TVNumericValue::kKnown);
	//r2.setCoordSys(TCoordSysFactory::kGeodetic);
	free.setCoordSys(TCoordSysFactory::kGeodetic);
	free=r2*free;
	cout<<"free=r2*free:("<<free.getX().getMetresValue()<<","<<free.getY().getMetresValue()<<","<<free.getZ().getMetresValue()<<"), status:"<<free.getStatus()<<", sys coord:"<<free.getCoordSys()<<endl;

	pos.setCoordSys(TCoordSysFactory::kGeodetic);
	pos=r2*pos;
	cout<<"pos=r2*pos:("<<pos.getX().getMetresValue()<<","<<pos.getY().getMetresValue()<<","<<pos.getZ().getMetresValue()<<"), status:"<<pos.getStatus()<<", sys coord:"<<pos.getCoordSys()<<endl<<endl;

	
	r2.setStatus(TVNumericValue::kNull);
	//r2.setCoordSys(TCoordSysFactory::kGeodetic);
	r2.identity();
	cout<<"r2.identity() ?:"<<r2.identity()<<endl;
	cout<<"r2:[	("<<r2.getElt(0,0)<<","<<r2.getElt(0,1)<<","<<r2.getElt(0,2)<<"),"<<endl
				<<"	("<<r2.getElt(1,0)<<","<<r2.getElt(1,1)<<","<<r2.getElt(1,2)<<"),"<<endl
				<<"	("<<r2.getElt(2,0)<<","<<r2.getElt(2,1)<<","<<r2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<r2.getStatus()<<", sys coord:"<<r2.getCoordSys()<<endl<<endl<<endl;

	




	//test T3DMatrix
	cout<<"TEST de T3DMatrix"<<endl<<endl;

	T3DMatrix t1 (TCoordSysFactory::k3DCartesian);
	T3DMatrix t2(t1);
	T3DMatrix t3 (TCoordSysFactory::k3DCartesian);
	TFreeVector vl(TCoordSysFactory::k3DCartesian);
 	TPositionVector vp (TCoordSysFactory::k3DCartesian);
	TDouble D;

	D.setValue(5);

	t1=2;

	//t2.setCoordSys(TCoordSysFactory::kGeodetic);
	//cout<<t2.setElt(0,0,0)<<endl;
	t2.setElt(0,0,0);
	t2.setElt(0,1,5);
	t2.setElt(0,2,0);
	t2.setElt(1,0,1);
	t2.setElt(1,1,2);
	t2.setElt(1,2,2);
	t2.setElt(2,0,3);
	t2.setElt(2,1,3);
	t2.setElt(2,2,3);

	t1.setStatus(TVNumericValue::kKnown);
	t2.setStatus(TVNumericValue::kKnown);



	cout<<"Matrices initiales"<<endl;
	cout<<"t1:[	("<<t1.getElt(0,0)<<","<<t1.getElt(0,1)<<","<<t1.getElt(0,2)<<"),"<<endl
				<<"	("<<t1.getElt(1,0)<<","<<t1.getElt(1,1)<<","<<t1.getElt(1,2)<<"),"<<endl
				<<"	("<<t1.getElt(2,0)<<","<<t1.getElt(2,1)<<","<<t1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t1.getStatus()<<", sys coord:"<<t1.getCoordSys()<<endl;
	cout<<"t2:[	("<<t2.getElt(0,0)<<","<<t2.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t2.getElt(1,0)<<","<<t2.getElt(1,1)<<","<<t2.getElt(1,2)<<"),"<<endl
				<<"	("<<t2.getElt(2,0)<<","<<t2.getElt(2,1)<<","<<t2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t2.getStatus()<<", sys coord:"<<t2.getCoordSys()<<endl;
	cout<<"t3:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
				<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl;
	cout<<"vl:("<<vl.getX().getMetresValue()<<","<<vl.getY().getMetresValue()<<","<<vl.getZ().getMetresValue()<<"), status:"<<vl.getStatus()<<", sys coord:"<<vl.getCoordSys()<<endl;
	cout<<"vp:("<<vp.getX().getMetresValue()<<","<<vp.getY().getMetresValue()<<","<<vp.getZ().getMetresValue()<<"), status:"<<vp.getStatus()<<", sys coord:"<<vp.getCoordSys()<<endl<<endl;

	
	
	cout<<"test fonction"<<endl<<endl;


	//t2.setStatus(TVNumericValue::kNull);
	//t2.setCoordSys(TCoordSysFactory::kGeodetic);
	
	t2=t2.transposed();
	cout<<"t2=t2.transposed():[	("<<t2.getElt(0,0)<<","<<t2.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t2.getElt(1,0)<<","<<t2.getElt(1,1)<<","<<t2.getElt(1,2)<<"),"<<endl
				<<"	("<<t2.getElt(2,0)<<","<<t2.getElt(2,1)<<","<<t2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t2.getStatus()<<", sys coord:"<<t2.getCoordSys()<<endl<<endl;

	t1=t2;
	cout<<"t1=t2:[	("<<t1.getElt(0,0)<<","<<t1.getElt(0,1)<<","<<t1.getElt(0,2)<<"),"<<endl
				<<"	("<<t1.getElt(1,0)<<","<<t1.getElt(1,1)<<","<<t1.getElt(1,2)<<"),"<<endl
				<<"	("<<t1.getElt(2,0)<<","<<t1.getElt(2,1)<<","<<t1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t1.getStatus()<<", sys coord:"<<t1.getCoordSys()<<endl<<endl;


	cout<<"t2 est t elle reversible?"<<t2.invert()<<endl;
	cout<<"t2.invert():[	("<<t2.getElt(0,0)<<","<<t2.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t2.getElt(1,0)<<","<<t2.getElt(1,1)<<","<<t2.getElt(1,2)<<"),"<<endl
				<<"	("<<t2.getElt(2,0)<<","<<t2.getElt(2,1)<<","<<t2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t2.getStatus()<<", sys coord:"<<t2.getCoordSys()<<endl<<endl;

	t3=t1*t2;
	cout<<"t3=t1*t2:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
				<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
				<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;

	t2=t2.inverse();
	cout<<"t2=t2.inverse():[	("<<t2.getElt(0,0)<<","<<t2.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t2.getElt(1,0)<<","<<t2.getElt(1,1)<<","<<t2.getElt(1,2)<<"),"<<endl
				<<"	("<<t2.getElt(2,0)<<","<<t2.getElt(2,1)<<","<<t2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t2.getStatus()<<", sys coord:"<<t2.getCoordSys()<<endl<<endl;

	t2.clear();
	cout<<"t2.clear():[	("<<t2.getElt(0,0)<<","<<t2.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t2.getElt(1,0)<<","<<t2.getElt(1,1)<<","<<t2.getElt(1,2)<<"),"<<endl
				<<"	("<<t2.getElt(2,0)<<","<<t2.getElt(2,1)<<","<<t2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t2.getStatus()<<", sys coord:"<<t2.getCoordSys()<<endl<<endl;

	
	//t2.setStatus(TVNumericValue::kNull);
//	t2.setCoordSys(TCoordSysFactory::kGeodetic);
	
	t2.initDiag(5);
	cout<<"t2.initDiag(5):[	("<<t2.getElt(0,0)<<","<<t2.getElt(0,1)<<","<<t2.getElt(0,2)<<"),"<<endl
				<<"	("<<t2.getElt(1,0)<<","<<t2.getElt(1,1)<<","<<t2.getElt(1,2)<<"),"<<endl
				<<"	("<<t2.getElt(2,0)<<","<<t2.getElt(2,1)<<","<<t2.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t2.getStatus()<<", sys coord:"<<t2.getCoordSys()<<endl<<endl;

	t3=t1+t2;
	cout<<"t3=t1+t2:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
			<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
			<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
			<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;

	//t2.setCoordSys(TCoordSysFactory::kGeodetic);
	t1+=t2;
	cout<<"t1+=t2:[	("<<t1.getElt(0,0)<<","<<t1.getElt(0,1)<<","<<t1.getElt(0,2)<<"),"<<endl
				<<"	("<<t1.getElt(1,0)<<","<<t1.getElt(1,1)<<","<<t1.getElt(1,2)<<"),"<<endl
				<<"	("<<t1.getElt(2,0)<<","<<t1.getElt(2,1)<<","<<t1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t1.getStatus()<<", sys coord:"<<t1.getCoordSys()<<endl;


	t1=t3-t2;
	cout<<"t1=t3-t2:[	("<<t1.getElt(0,0)<<","<<t1.getElt(0,1)<<","<<t1.getElt(0,2)<<"),"<<endl
				<<"	("<<t1.getElt(1,0)<<","<<t1.getElt(1,1)<<","<<t1.getElt(1,2)<<"),"<<endl
				<<"	("<<t1.getElt(2,0)<<","<<t1.getElt(2,1)<<","<<t1.getElt(2,2)<<"),]"<<endl
				<<"	status:"<<t1.getStatus()<<", sys coord:"<<t1.getCoordSys()<<endl<<endl;

	//t2.setCoordSys(TCoordSysFactory::kGeodetic);
	t3-=t2;
	cout<<"t3-=t2:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
			<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
			<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
			<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;

	//t2.setCoordSys(TCoordSysFactory::kGeodetic);
	t3=t3*t2;
	cout<<"t3=t3*t2:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
			<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
			<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
			<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;

	t3*=t2;
	cout<<"t3*=t2:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
			<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
			<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
			<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;


	
	TLength al,bl,cl;
	al.setMetresValue(1);
	bl.setMetresValue(2);
	cl.setMetresValue(3);

	TAngle ag, bg;
	ag.setRadiansValue(1);
	bg.setRadiansValue(2);
	
	vp.setStatus(TVNumericValue::kNull);
	//vp.setCoordSys(TCoordSysFactory::kGeodetic);
	vp.setX(al);
	vp.setY(bl);
	vp.setZ(cl);
	//vp.setPhiEllipsoid(ag);
	//vp.setLambdaEllipsoid(bg);
	//vp.setH(cl);

	cout<<"vp:("<<vp.getX().getMetresValue()<<","<<vp.getY().getMetresValue()<<","<<vp.getZ().getMetresValue()<<"), status:"<<vp.getStatus()<<", sys coord:"<<vp.getCoordSys()<<endl;
	//cout<<"vp:("<<vp.getPhiEllipsoid().getRadiansValue()<<","<<vp.getLambdaEllipsoid().getRadiansValue()<<","<<vp.getH().getMetresValue()<<"), status:"<<vp.getStatus()<<", sys coord:"<<vp.getCoordSys()<<endl;
	vp=t2*vp;
	cout<<"vp=t2*vp:("<<vp.getX().getMetresValue()<<","<<vp.getY().getMetresValue()<<","<<vp.getZ().getMetresValue()<<"), status:"<<vp.getStatus()<<", sys coord:"<<vp.getCoordSys()<<endl<<endl;
	//cout<<"vp:("<<vp.getPhiEllipsoid().getRadiansValue()<<","<<vp.getLambdaEllipsoid().getRadiansValue()<<","<<vp.getH().getMetresValue()<<"), status:"<<vp.getStatus()<<", sys coord:"<<vp.getCoordSys()<<endl;

	
	
	vl.setStatus(TVNumericValue::kKnown);
	vl.setX(al);
	vl.setY(bl);
	vl.setZ(cl);
	cout<<"vl:("<<vl.getX().getMetresValue()<<","<<vl.getY().getMetresValue()<<","<<vl.getZ().getMetresValue()<<"), status:"<<vl.getStatus()<<", sys coord:"<<vl.getCoordSys()<<endl;
	vl=t2*vl;
	cout<<"vl=t2*vl:("<<vl.getX().getMetresValue()<<","<<vl.getY().getMetresValue()<<","<<vl.getZ().getMetresValue()<<"), status:"<<vl.getStatus()<<", sys coord:"<<vl.getCoordSys()<<endl<<endl;

	
	D.setStatus(TVNumericValue::kKnown);
	t3=t2*D;
	//t3=D*t2;
	cout<<"t3=t2*D:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
			<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
			<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
			<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;

	t3=t2*6;
	cout<<"t3=t2*6:[	("<<t3.getElt(0,0)<<","<<t3.getElt(0,1)<<","<<t3.getElt(0,2)<<"),"<<endl
			<<"	("<<t3.getElt(1,0)<<","<<t3.getElt(1,1)<<","<<t3.getElt(1,2)<<"),"<<endl
			<<"	("<<t3.getElt(2,0)<<","<<t3.getElt(2,1)<<","<<t3.getElt(2,2)<<"),]"<<endl
			<<"	status:"<<t3.getStatus()<<", sys coord:"<<t3.getCoordSys()<<endl<<endl;

	

	

	//Test Tdouble
	cout<<"Test TDouble\n"<<endl;
	TDouble doublen, double0, double1, double2;
	double0.setValue(0.0);
	double1.setValue(12.0);
	double1.setStatus(TANumericValue ::kKnown);
	double2.setValue(-4.0);
	double2.setStatus(TANumericValue ::kKnown);
	cout<<"doublen:"<<doublen.getValue()<<",status:"<<doublen.getStatus()<<endl;
	cout<<"double0:"<<double0.getValue()<<",status:"<<double0.getStatus()<<endl;
	cout<<"double1:"<<double1.getValue()<<",status:"<<double1.getStatus()<<endl;
	cout<<"double2:"<<double2.getValue()<<",status:"<<double2.getStatus()<<"\n"<<endl;

	//Test TDouble +,-,*,/,=
	cout<<"Basic operators: +,-,*,/,=\n"<<endl;
	TDouble double3, double4, double5;
	double3=double1-double2;
	cout<<"double3=double1-double2:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double3=double1+double2;
	cout<<"double3=double1+double2:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double3=double2*double1;
	cout<<"double3=double2*double1:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double4=double3/double2;
	cout<<"double4=double3/double2:"<<double4.getValue()<<",status:"<<double4.getStatus()<<endl;
	double5=double3/double0;
	cout<<"double5=double3/double0:"<<double5.getValue()<<",status:"<<double5.getStatus()<<"\n"<<endl;
	
	double3=double1-doublen;
	cout<<"double3=double1-doublen:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double3=double1+doublen;
	cout<<"double3=double1+doublen:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double3=double2*doublen;
	cout<<"double3=double2*doublen:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double4=double3/doublen;
	cout<<"double4=double3/doublen:"<<double4.getValue()<<",status:"<<double4.getStatus()<<"\n"<<endl;

	double0.setValue(0.0);
	double1.setValue(1.0);
	double2.setValue(2.0);
	double3.setValue(3.0);
	double4.setValue(4.0);
	double5.setValue(5.0);
	cout<<"double0:"<<double0.getValue()<<",status:"<<double0.getStatus()<<endl;
	cout<<"double1:"<<double1.getValue()<<",status:"<<double1.getStatus()<<endl;
	cout<<"double2:"<<double2.getValue()<<",status:"<<double2.getStatus()<<endl;
	cout<<"double3:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	cout<<"double4:"<<double4.getValue()<<",status:"<<double4.getStatus()<<endl;
	cout<<"double5:"<<double5.getValue()<<",status:"<<double5.getStatus()<<"\n"<<endl;

	//Test TDouble comparaison ==, <
	cout<<"Comparaison operators ==,< \n"<<endl;
	cout<<"double4==double1?" <<(double4==double1) <<endl;
	cout<<"double3==double2?" <<(double3==double2) <<endl;
	cout<<"double4<double1?" <<(double4<double1) <<endl;
	cout<<"double3<double2?" <<(double3<double2) <<"\n"<<endl;

	//Test TDouble +=, -=, *=, /=
	cout<<"Operators  +=, -=, *=, /= \n"<<endl;
	double2+=double1;
	cout<<"double2+=double1:"<<double2.getValue()<<",status:"<<double2.getStatus()<<endl;
	double3*=double2;
	cout<<"double3*=double2:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double4-=double3;
	cout<<"double4-=double3:"<<double4.getValue()<<",status:"<<double4.getStatus()<<endl;
	double4/=double3;
	cout<<"double4/=double3:"<<double4.getValue()<<",status:"<<double4.getStatus()<<endl;
	double3/=double0;
	cout<<"double3/=double0:"<<double3.getValue()<<",status:"<<double3.getStatus()<<"\n"<<endl;

	double2+=doublen;
	cout<<"double2+=doublen:"<<double2.getValue()<<",status:"<<double2.getStatus()<<endl;
	double3*=double2;
	cout<<"double3*=double2:"<<double3.getValue()<<",status:"<<double3.getStatus()<<endl;
	double4-=double3;
	cout<<"double4-=double3:"<<double4.getValue()<<",status:"<<double4.getStatus()<<endl;
	double5/=double4;
	cout<<"double5/=double4:"<<double4.getValue()<<",status:"<<double4.getStatus()<<"\n"<<endl;
	
	//Test des  operateurs "speciaux"
	cout<<"Special operator * \n"<<endl;
	TAngle angle1 (2);
	angle1.setStatus(TANumericValue ::kKnown);
	TLength length1 (12);
	length1.setStatus(TANumericValue ::kNull);
	TMatrix mtx1(2, 2);
	mtx1.setStatus(TANumericValue ::kKnown);
	mtx1(0,0)=-6;
	mtx1(0,1)=8;
	mtx1(1,0)=3;
	mtx1(1,1)=0;
	TColumnVector cv1 (3);
	cv1(0)=-5;
	cv1(1)=4;
	cv1(2)=3;

	double3.setValue(3.0);
	double3.setStatus(TANumericValue ::kKnown);

	cout<<"angle1:"<<angle1.getRadiansValue()<<",status:"<<angle1.getStatus()<<endl;
	cout<<"length1:"<<length1.getMetresValue()<<",status:"<<length1.getStatus()<<endl;
	cout<<"mtx1:"<<"[("<<mtx1(0,0)<<","<<mtx1(0,1)<<"),("<<mtx1(1,0)<<","<<mtx1(1,1)<<")], status:"<<mtx1.getStatus()<<endl;
	cout<<"cv1:"<<"["<<cv1(0)<<","<<cv1(1)<<","<<cv1(2)<<"], status:"<<cv1.getStatus()<<endl;
	cout<<"double3:"<<double3.getValue()<<", status:"<<double3.getStatus()<<"\n"<<endl;

	TAngle angle2;
	TLength length2;
	TMatrix mtx2 (2,2);
	mtx2.setStatus(TANumericValue::kKnown);
	TColumnVector cv2 (3);

	angle2=double3*angle1;
	cout<<"angle2=double3*angle1:"<<angle2.getRadiansValue()<<",status:"<<angle2.getStatus()<<endl;
	length2=double3*length1;
	cout<<"length2=double3*length1:"<<length2.getMetresValue()<<",status:"<<length2.getStatus()<<endl;
	mtx2=double3*mtx1;
	cout<<"mtx2=double3*mtx1:[("<<mtx2(0,0)<<","<<mtx2(0,1)<<"),("<<mtx2(1,0)<<","<<mtx2(1,1)<<")], status:"<<mtx2.getStatus()<<endl;
	cv2=double3*cv1;
	cout<<"cv2=double3*cv1:["<<cv2(0)<<","<<cv2(1)<<","<<cv2(2)<<"], status:"<<cv2.getStatus()<<"\n"<<endl;

	angle2=doublen*angle1;
	cout<<"angle2=doublen*angle1:"<<angle2.getRadiansValue()<<",status:"<<angle2.getStatus()<<endl;
	length2=doublen*length1;
	cout<<"length2=doublen*length1:"<<length2.getMetresValue()<<",status:"<<length2.getStatus()<<endl;
	mtx2=doublen*mtx1;
	cout<<"mtx2=doublen*mtx1:[("<<mtx2(0,0)<<","<<mtx2(0,1)<<"),("<<mtx2(1,0)<<","<<mtx2(1,1)<<")], status:"<<mtx2.getStatus()<<endl;
	cv2=doublen*cv1;
	cout<<"cv2=doublen*cv1:["<<cv2(0)<<","<<cv2(1)<<","<<cv2(2)<<"], status:"<<cv2.getStatus()<<"\n"<<endl;



////////////////////////
//Test Patrick
////////////////////////
/*	TMatrix A(3,3);
	{
		for (size_t r=0;r<A.numRows();r++)
			for (size_t c=0;c<A.numCols();c++)
				A(r,c)=r+c;			// singular
				//A(r,c)=r+c+r*c%2;	// non-singular
	}
	TMatrix B(3,4);
	{
		for (size_t r=0;r<B.numRows();r++)
			for (size_t c=0;c<B.numCols();c++)
				B(r,c)=2*r+c;
	}

	std::cout << "A :" << std::endl << A << std::endl;
	std::cout << "B :" << std::endl << B << std::endl;

	std::cout << "B(0,0) :" << std::endl << B(0, 0) << std::endl;
	std::cout << "B(2,3) :" << std::endl << B(2, 3) << std::endl;
	std::cout << "B(3,4) :" << std::endl << B(3, 4) << std::endl;
	std::cout << "B(-6,-8) :" << std::endl << B(-6, -8) << std::endl;
	std::cout << "B(0,5) :" << std::endl << B(0, 5) << std::endl;

	// operator= is not working properly
	
/*		A=B;
		std::cout << "A=B :" << std::endl << A << std::endl;
		
		B=A;
		std::cout << "B=A :" << std::endl << B << std::endl;*/
	

	// differnt results ????
	/*
		std::cout << A*B << std::endl;
		A*=B;
		std::cout << A << std::endl;
	*/
/*		TMatrix AA(3,3);
		TMatrix BB(3,4);
		AA = A;
		BB = B;

		std::cout << AA << std::endl;
		std::cout << BB << std::endl;

		std::cout << (A*B) << std::endl;

		TMatrix M;
		M = AA*BB;
		std::cout << M << std::endl;
	
	// negative Index
	// easily avoidable use unsigned ore better size_t or size_type
	
		TMatrix D(-1,-1);
		D(-1,-1)=5;
		std::cout << D(-2,-2) << std::endl;
		std::cout << D << std::endl;
	
		std::cout << D*D << std::endl; // results in a crash

	// hmm, not very beautiful, semanticaly not clear, for example compare
	// with TMatrix(const TDouble&); (anyway this constructor is not working
	// properly
	
	/*	TMatrix E(2,2);
		E=1;
		std::cout << "E :" << std::endl << E << std::endl;
		TMatrix F=TDouble(1);
		std::cout << "F :" << std::endl << F << std::endl;
*/

	// efficency: matrix types
	// need of symmetric matrices
	// example: one lgc project with 1500 mesurements means:
	// 1499*1500*8 bytes = 17988000B = 17.2MB 
	// only in the a priori covariance matrix
	// for a medium sized project

	// efficency: copyingexample.
	// it is just an example of what is happening. It is not a question 
	// of functionality but for efficency.

/*		copyingexample cA,cB;
		copyingexample cC;
		cC=cA+cB;

	// Like this we create 4 objects in memory, even if 
	// we need just 3. If we want to use the overloaded 
	// iterators, there is no chance to avoid this
	// but we could avoid copying complete matrices around.
	// Its a huge overhead of operations like that.
	  /*  Output:
		Constructor Object #1; 1 Objects in Memory.
		Constructor Object #2; 2 Objects in Memory.
		Constructor Object #3; 3 Objects in Memory.
		Constructor Object #4; 4 Objects in Memory.
		Destructor Object #4; 3 Objects in Memory.
		Destructor Object #4; 2 Objects in Memory.
		Destructor Object #4; 1 Objects in Memory.
		Destructor Object #4; 0 Objects in Memory.*/


/*	double c=0;
	TDouble C(c/c);
	std::cout << "TDouble C : " << C.getValue() << std::endl;
	std::cout << "Status  C : " << C.getStatus() << std::endl;
	C=TDouble(numeric_limits<double>::max())*TDouble(2);
	std::cout << "TDouble C : " << C.getValue() << std::endl;
	std::cout << "Status  C : " << C.getStatus() << std::endl;
	C=TDouble(numeric_limits<double>::max())*TDouble(-2); 
	std::cout << "TDouble C : " << C.getValue() << std::endl;
	std::cout << "Status  C : " << C.getStatus() << std::endl;

	double d = numeric_limits<double>::max();
	double e = 0;
	std::cout << (d/e)<<endl;*/

	//test modulo 2pi
	TAngle angTest (-1.8);
	angTest = angTest + 2 * TAngle::pi();
	cout<<"angTest : "<< angTest.getRadiansValue()<<endl;

	angTest = angTest - 8 * TAngle::pi();
	cout<<"angTest : "<< angTest.getRadiansValue()<<endl;

	return;

}