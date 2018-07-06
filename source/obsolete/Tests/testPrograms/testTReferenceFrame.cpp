//////////////////////////////////////////////////////
// test file for TReferenceFrame
//////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include  "TReferenceFrame.h"
#include  "TReferenceEllipsoid.h"
#include  "TLength.h"
#include  "TAngle.h"
#include  "TSpatialPosition.h"
#include  "TSpatialPointName.h"
#include  "TSpatialPoint.h"
#include  "TCoordinateSystem.h"
#include  "TCoordinateSystemCatalogue.h"
#include <string>
using namespace std;



void main ()
{/*	//create reference frame
	TReferenceFrame Mardi();
	string st("Mardi");
	Mardi.setName(st);
	cout<<Mardi.getName()<<endl;
	
	//create position
	TLength x(50);
	TLength y(200);
	TLength z(1000);
	TSpatialPosition origine;
	origine.setXCoord(x);
	origine.setYCoord(y);
	origine.setZCoord(z);

	//create point
	string orig("origi");
	char c='n';
	string s("e");
	TSpatialPointName originname(orig, c, s);
	cout<<originname.getPtName()<<endl;
	cout<<originname.getDBName()<<endl;
	TSpatialPoint origin(originname, &origine);

	//create reference frame
	TReferenceEllipsoid WGS84(6378137,0.08189191025);
	TReferenceFrame Mardi(&WGS84, &origin);
	string st("Mardi");
	Mardi.setName(st);
	cout<<Mardi.getName()<<endl;
	
	//test set/get origine
	Mardi.setOrigin (&origin);
	cout<<Mardi.OriginSet()<<endl;
	TSpatialPosition origineposition;
	origineposition=(Mardi.getOrigin())->getPosition(Mardi);
	TLength ipX;
	ipX=origineposition.getXCoord();
	LengthValue X;
	X=ipX.getMetresValue();
	cout<<X<<endl;
	
/*	//test set/get ref ellipsoid
	TReferenceEllipsoid WGS84(6378137,0.08189191025);
	Mardi.setReferenceEllipsoid(&WGS84);
	cout<<setprecision(15)<< (Mardi.getReferenceEllipsoid())->getB()<<endl;
	
	//test set/get false origine
	Mardi.setFalseOrigin(&origine);
	TSpatialPosition *falseorigineposition;
	falseorigineposition = Mardi.getFalseOrigin();
	ipX=falseorigineposition->getYCoord();
	X=ipX.getMetresValue();
	cout<<X<<endl;*/

	TLength x(2000);
	TLength y(2097.79265);
	TLength z(433.65921);
	TSpatialPosition origine;
	origine.setXCoord(x);
	origine.setYCoord(y);
	origine.setZCoord(z);
	
	string orig("origi");
	char c='n';
	string s("e");
	TSpatialPointName originname(orig, c, s);
	TSpatialPoint origin(originname, &origine);

	TReferenceEllipsoid GRS80(6378137,0.0818191910428);
	TReferenceFrame Cern(&GRS80, &origin);
	string st("Cern");
	Cern.setName(st);
	Cern.setDimension(3);
	cout<<Cern.getName()<<endl;
	cout<<Cern.getDimension()<<endl;
	
	TLength x1(4395149.8285686);
	TLength y1(465723.5356206);
	TLength z1(4583171.7722458);
	TSpatialPosition po;
	po.setXCoord(x1);
	po.setYCoord(y1);
	po.setZCoord(z1);

	cout<<"po"<<endl;
	cout<<setprecision(15)<<(po.getXCoord()).getMetresValue()<<endl;
	cout<<setprecision(15)<<(po.getYCoord()).getMetresValue()<<endl;
	cout<<setprecision(15)<<(po.getZCoord()).getMetresValue()<<endl;
	
	TCoordinateSystem *sys;
	TCoordinateSystem CCS(TCoordinateSystem::kGeodetic);
	
	CCS.setCoordTokens(TSpatialPosition::kPhi, TSpatialPosition::kLambda, TSpatialPosition::kHEllipse);
	sys=(TCoordinateSystem *)&CCS;
 	Cern.addCoordinateSystem(sys);
	
/*	TAngle phiellips, lambdaellips;
	TLength hellips;
	phiellips = po.getPhiEllipsoid(Cern);
	lambdaellips = po.getLambdaEllipsoid(Cern);
	hellips = po.getHEllipsoid(Cern);
	double phi,lambda, h;
	phi = phiellips.getGonsValue();
	lambda = lambdaellips.getGonsValue();
	h = hellips.getMetresValue();
	cout<<setprecision(15)<<phi<<endl;
	cout<<setprecision(15)<<lambda<<endl;
	cout<<setprecision(15)<<h<<endl;*/

	//test set
	TAngle p(0.806912913224);
	TAngle l(0.105556643112);
	TLength he(489.97467);

	po.setPhiEllipsoid(p, Cern);
	po.setLambdaEllipsoid(l, Cern);
	po.setHEllipsoid(he, Cern);
	cout<<setprecision(15)<<po.getXCoord().getMetresValue()<<endl;
	cout<<setprecision(15)<<po.getYCoord().getMetresValue()<<endl;
	cout<<setprecision(15)<<po.getZCoord().getMetresValue()<<endl;
	
	po.setPLH(p,l,he,Cern);
	cout<<setprecision(15)<<po.getXCoord().getMetresValue()<<endl;
	cout<<setprecision(15)<<po.getYCoord().getMetresValue()<<endl;
	cout<<setprecision(15)<<po.getZCoord().getMetresValue()<<endl;

}