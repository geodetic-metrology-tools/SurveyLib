#include  "TSpatialPosition.h"
#include  "TSpatialVector.h"
//#include  "TSpatialOrientation.h"

#include  "TLength.h"
#include  "TGeodeticRefFrame.h"
#include  "TModifiedLocalGeodeticRF.h"
//#include  "TReferenceEllipsoid.h"

#include  "TTranslation.h"
#include  "TReflection.h"

#include  "TRefSystemFactory.h"
//#include  "TGraph.h"

#include  <iostream>



void main(){

	//test TSpatialPosition

/*	string essai = "Euclidean Reference Frame";
	string ellipsoid = "RefEllipsoid";

	TReferenceEllipsoid refEll(ellipsoid);
	TReferenceEllipsoid* p_refEll = &refEll;

	TLocalAstronomicalRefFrame rframe(essai, p_refEll);
	TLocalAstronomicalRefFrame* p_rframe = &rframe;
*/
	TSpatialPosition spos(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)),
		spos1(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));

	TLength len1(123), len2(345), len3(432);
	TPositionVector pv(321,543,234, TCoordSysFactory::k3DCartesian), pv1(TCoordSysFactory::k3DCartesian);
	TAngle phi(0.66), lambda(0.5);
	pv1.setX(len1);
	pv1.setY(len2);
	pv1.setZ(len3);
	pv1.setStatus(TVNumericValue::kKnown);
	cout << pv1.getStatus() << endl;

	spos.setCoordinates(pv);

	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(14);
	cout << "spos : " << spos.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getGonsValue() << "  ";
	cout << spos.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getGonsValue() << "  ";
	cout << spos.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue() << endl;
	cout << "position vector status : " << spos.getCoordinates(TCoordSysFactory::kGeodetic).getStatus() << endl;
	cout << "spatial position status : " << spos.getObjectStatus() << endl << endl;

	spos1.setCoordinates(pv1);

	cout.setf(ios_base::floatfield);
	cout << "spos1 : " << spos1.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue() << "  ";
	cout << spos1.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue() << "  ";
	cout << spos1.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue() << endl;
	cout << spos1.getObjectStatus() << endl << endl;


//	spos.setPhiEllipsoid(phi);
//	spos.setLambdaEllipsoid(lambda);
//	spos.setH(len1);

//	spos1.setPLH(lambda, phi, len2);

/*	cout << spos1.getPhiEllipsoid(spos1.getReferenceFrame()->getLocalGeodeticRF()->getReferenceEllipsoid()).getRadiansValue() << endl;
	cout << spos1.getLambdaEllipsoid(spos1.getReferenceFrame()->getLocalGeodeticRF()->getReferenceEllipsoid()).getRadiansValue() << endl;
	cout << spos1.getH(spos1.getReferenceFrame()->getLocalGeodeticRF()->getReferenceEllipsoid()).getMetresValue() << endl;


	spos.setXCoordStatus(TANumericValue::kFixed);
	spos.setYCoordStatus(TANumericValue::kUnknown);
	spos.setZCoordStatus(TANumericValue::kVariable);

	spos1.setPositionStatus(TSpatialStatus::kVz);
//	spos1.setPositionStatus(< TPositionStatus > kFixed);

	
	pv1 = spos.getXYZ();
	len1 = spos.getXCoord();
	len2 = spos.getYCoord();
	len3 = spos.getZCoord();

	phi = spos.getPhiEllipsoid(spos.getReferenceFrame()->getLocalGeodeticRF()->getReferenceEllipsoid());
	lambda = spos.getLambdaEllipsoid(spos.getReferenceFrame()->getLocalGeodeticRF()->getReferenceEllipsoid());
	len1 = spos.getH(spos.getReferenceFrame()->getLocalGeodeticRF()->getReferenceEllipsoid());


	cout<<spos.getXCoordStatus()<<endl;
	cout<<spos.getYCoordStatus()<<endl;
	cout<<spos.getZCoordStatus()<<endl;

	cout<<spos.getPositionStatus()<<endl;
	cout<<spos1.getPositionStatus()<<endl;

	cout<<spos.knownXCoord()<<endl;
	cout<<spos.knownYCoord()<<endl;
	cout<<spos.knownZCoord()<<endl;

	cout<<spos.getVariableDimension()<<endl;
	cout<<spos1.getVariableDimension()<<endl;

	cout<<spos.getReferenceFrame()->getName()<<endl;



	//test TSpatialPositionError
/*	TSpatialPositionError err(TGraph::getGraph()->getRefFrame(TGraph::kCCS));
	TSpatialPosition* sp = &spos;
	err.setAssociatedPosition(sp);

	//counted_ptr<TPositionStatus> ps;
	//TPositionStatus ps2(*(ps.get()));
	//ps->getPositionStatus();
	//err.setPositionStatus(ps);

	err.setToZero();
	cout<<err.getSigmaXX().getMetresValue()<<" "<<err.getSigmaYY().getMetresValue()<<" "<<err.getSigmaZZ().getMetresValue()<<endl;
	cout<<err.getSigmaXY().getMetresValue()<<" "<<err.getSigmaYZ().getMetresValue()<<" "<<err.getSigmaXZ().getMetresValue()<<endl;

	err.setSigmaXX(len1);
	err.setSigmaXY(len2);
	err.setSigmaXZ(len3);

	err.setSigmaYY(len3);
	err.setSigmaYZ(len1);
	err.setSigmaZZ(len2);

	cout<<err.getSigmaXX().getMetresValue()<<" "<<err.getSigmaYY().getMetresValue()<<" "<<err.getSigmaZZ().getMetresValue()<<endl;
	cout<<err.getSigmaXY().getMetresValue()<<" "<<err.getSigmaYZ().getMetresValue()<<" "<<err.getSigmaXZ().getMetresValue()<<endl;


	err.setSigmaXStatus(TANumericValue::kFixed);
	err.setSigmaYStatus(TANumericValue::kUnknown);
	err.setSigmaZStatus(TANumericValue::kVariable);

	TFreeVector fv;
	fv=err.getVariances();
	
	cout<<fv[0]<<" "<<fv[1]<<" "<<fv[2]<<endl<<endl;
	
	T3DMatrix mat = err.getCovariances();
	cout<<mat.getC11()<<" "<<mat.getC12()<<" "<<mat.getC13()<<endl;
	cout<<mat.getC21()<<" "<<mat.getC22()<<" "<<mat.getC23()<<endl;
	cout<<mat.getC31()<<" "<<mat.getC32()<<" "<<mat.getC33()<<endl<<endl;

	cout<<err.getReferenceFrame()->getName()<<endl<<endl;

*/

	
	//test TEuclideanRefFrame
	//toutes les fonctions sont testées avec les deux classes précédentes.




	//test AffineTransformation
/*	TTranslation transl(12,14,9);
	TTranslation* trans = &transl;
	
	cout<<spos.transform(trans)<<endl;

	TReflection reflect(TReflection::kXEqual0);
	TReflection* refl = &reflect;

	cout<<spos.transform(refl)<<endl;


	//test TSpatialVector
/*	TSpatialVector svec(p_rframe), svec1(p_rframe);

	TLength len1(123), len2(345), len3(432);
	TFreeVector pv(321,543,234), pv1;
	

	svec.setXComponent(len1);
	svec.setYComponent(len2);
	svec.setZComponent(len3);

	svec1.setXYZVector(pv);

	svec.setXCompStatus(TANumericValue::kFixed);
	svec.setYCompStatus(TANumericValue::kNull);
	svec.setZCompStatus(TANumericValue::kVariable);

	svec1.setVectorStatus(TSpatialVectorStatus::kVz);


	
	pv1 = svec.getXYZVector();
	len2 = svec.getXComponent();
	len3 = svec.getYComponent();
	len1 = svec.getZComponent();

	cout<<svec.getXCompStatus()<<endl;
	cout<<svec.getYCompStatus()<<endl;
	cout<<svec.getZCompStatus()<<endl;

	cout<<svec.getVectorStatus()<<endl;
	cout<<svec1.getVectorStatus()<<endl;

	cout<<svec.knownXComp()<<endl;
	cout<<svec.knownYComp()<<endl;
	cout<<svec.knownZComp()<<endl;

	cout<<svec.getVariableDimension()<<endl;
	cout<<svec1.getVariableDimension()<<endl;

	cout<<svec.getReferenceFrame()->getName()<<endl;

	svec1 + svec;

	svec1 - svec;




	//test AffineTransformation pour TSpatialVector
	TTranslation transl(12,14,9);
	TTranslation* trans = &transl;
	
	cout<<svec.transform(trans)<<endl;

	TReflection reflect(TReflection::kXEqual0);
	TReflection* refl = &reflect;

	cout<<svec.transform(refl)<<endl;


		//test TSpatialVectorError
	TSpatialVectorError err(p_rframe);
	TSpatialVector* sp = &svec;
	err.setAssociatedVector(sp);

	
	err.setToZero();
	cout<<err.getSigmaXX().getMetresValue()<<" "<<err.getSigmaYY().getMetresValue()<<" "<<err.getSigmaZZ().getMetresValue()<<endl;
	cout<<err.getSigmaXY().getMetresValue()<<" "<<err.getSigmaYZ().getMetresValue()<<" "<<err.getSigmaXZ().getMetresValue()<<endl;

	err.setSigmaXX(len1);
	err.setSigmaXY(len2);
	err.setSigmaXZ(len3);

	err.setSigmaYY(len3);
	err.setSigmaYZ(len1);
	err.setSigmaZZ(len2);

	cout<<err.getSigmaXX().getMetresValue()<<" "<<err.getSigmaYY().getMetresValue()<<" "<<err.getSigmaZZ().getMetresValue()<<endl;
	cout<<err.getSigmaXY().getMetresValue()<<" "<<err.getSigmaYZ().getMetresValue()<<" "<<err.getSigmaXZ().getMetresValue()<<endl;


	err.setSigmaXStatus(TANumericValue::kFixed);
	err.setSigmaYStatus(TANumericValue::kUnknown);
	err.setSigmaZStatus(TANumericValue::kVariable);

	TFreeVector fv;
	fv=err.getVariances();
	
	cout<<fv[0]<<" "<<fv[1]<<" "<<fv[2]<<endl<<endl;
	
	T3DMatrix mat = err.getCovariances();
	cout<<mat.getC11()<<" "<<mat.getC12()<<" "<<mat.getC13()<<endl;
	cout<<mat.getC21()<<" "<<mat.getC22()<<" "<<mat.getC23()<<endl;
	cout<<mat.getC31()<<" "<<mat.getC32()<<" "<<mat.getC33()<<endl<<endl;

	cout<<err.getReferenceFrame()->getName()<<endl<<endl;

*/




	//test TSpatialOrientation
/*	TSpatialOrientation sori(p_rframe), sori1(p_rframe);

	TAngle a(0.5),b(-.3),c(.6);
	TRotationMatrix rm;

//	rm(0,0) = 1;
//	rm(1,0) = 0;
//	rm(2,0) = 0;
//	rm(0,1) = 0;
//	rm(1,1) = 1;
//	rm(2,1) = 0;
//	rm(0,2) = 0;
//	rm(1,2) = 0;
//	rm(2,2) = 1;
//	sori.setMatrix(rm);


	sori.setXAxisRotation(b);
	sori.setYAxisRotation(c);
	sori.setZAxisRotation(a);

	sori1.setAllRotations(a,b,c);

	

//	spos.setXCoordStatus(TANumericValue::kFixed);
//	spos.setYCoordStatus(TANumericValue::kUnknown);
//	spos.setZCoordStatus(TANumericValue::kVariable);

//	spos1.setPositionStatus(TPositionStatus::kVz);

	
	rm = sori.getMatrix();

	

//	cout<<spos.getXCoordStatus()<<endl;
//	cout<<spos.getYCoordStatus()<<endl;
//	cout<<spos.getZCoordStatus()<<endl;

//	cout<<spos.getPositionStatus()<<endl;
//	cout<<spos1.getPositionStatus()<<endl;

//	cout<<spos.knownXCoord()<<endl;
//	cout<<spos.knownYCoord()<<endl;
//	cout<<spos.knownZCoord()<<endl;

//	cout<<spos.getVariableDimension()<<endl;
//	cout<<spos1.getVariableDimension()<<endl;

	cout<<sori.getReferenceFrame()->getName()<<endl;

	



	//test AffineTransformation pour TSpatialOrientation
	TTranslation transl(12,14,9);
	TTranslation* trans = &transl;
	
	cout<<sori.transform(trans)<<endl;

	TReflection reflect(TReflection::kXEqual0);
	TReflection* refl = &reflect;

	cout<<sori.transform(refl)<<endl;
	*/

}