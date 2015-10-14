

#include  "SpatialObjFns.h"
#include  "TSpatialPosition.h"
#include  "TGraph.h"
#include  "TRefSystemFactory.h"
#include  "TLength.h"
#include  "TVGeoidModel.h"
#include  "TVReferenceFrame.h"
#include  "TModifiedLocalAstronomicalRF.h"

//#include  "TTLength.h"

SpatialObjFns::SpatialObjFns()
{

}
// N value for CG2000 at 0-level
int SpatialObjFns::getCG2000N0( double  x, double  y, double* N)
{
	//TTLength le(8.8);
	//le.getKMetresValue();

	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x<(-5000+lim)) || (x>(6000-lim)) || (y<lim) || (y>(12000-lim)) )
	{
		return 0;
	}
	

	// get the CCS spatial position corresponding to the double values
	TSpatialPosition spos(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TPositionVector vector(x,y,0.0, TCoordSysFactory::k3DCartesian);
	spos.setCoordinates(vector);
	
	// get N value in CG2000
	*N = TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG2000)
		->getN(spos).getMetresValue();

	
	return 1;
	
}


// N value for CG2000 at LEP-level
int SpatialObjFns::getCG2000NMachine( double  x, double  y, double* N)
{
	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x<(-5000+lim)) || (x>(6000-lim)) || (y<lim) || (y>(12000-lim)) )
	{
		return 0;
	}

	// get the CCS spatial position corresponding to the double values
	TSpatialPosition spos(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TPositionVector vector(x,y,0.0, TCoordSysFactory::k3DCartesian);
	spos.setCoordinates(vector);

	// return the N value in CG2000
	*N = TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG2000Machine)
		->getN(spos).getMetresValue();

	return 1;
	
}




// N value for CG1985 at 0-level
int SpatialObjFns::getCG1985N0( double  x, double  y, double* N)
{
	// get the CCS spatial position corresponding to the double values
	TSpatialPosition spos(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TPositionVector vector(x,y,0.0, TCoordSysFactory::k3DCartesian);
	spos.setCoordinates(vector);

	// return the N value in CG2000
	*N = TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG1985)
		->getN(spos).getMetresValue();

	return 1;
	
}

// N value for CG1985 at LEP-level
int SpatialObjFns::getCG1985NMachine( double  x, double  y, double* N)
{
	// get the CCS spatial position corresponding to the double values
	TSpatialPosition spos(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	TPositionVector vector(x,y,0.0, TCoordSysFactory::k3DCartesian);
	spos.setCoordinates(vector);

	// return the N value in CG2000
	*N = TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG1985Machine)
		->getN(spos).getMetresValue();

	return 1;
	
}


// coordinates transformation to MLA system
int SpatialObjFns::transformToMLA(double x0, double y0, double z0,
					double* x, double* y, double* z, char* geoid)
{
	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x0<(-5000+lim)) || (x0>(6000-lim)) || (y0<lim) || (y0>12000-lim) )
	{
		return 0;
	}

	TPositionVector vectOrigin(x0, y0, z0, TCoordSysFactory::k3DCartesian),
		vectPoint(*x, *y, *z, TCoordSysFactory::k3DCartesian);

	TSpatialPosition origin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)),
		point(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	origin.setCoordinates(vectOrigin);
	point.setCoordinates(vectPoint);

	TSpatialPosition P0(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getOrigin());
	P0.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

	TRefSystemFactory::EGeoid pGeoid;
	string cg00("CG2000"), cg85("CG1985");
	if (geoid == cg00)
		pGeoid = TRefSystemFactory::kCG2000Machine;
	else 
		if (geoid == cg85)
			pGeoid = TRefSystemFactory::kCG1985Machine;
		else 
			return 0;


	//DIF *1
	TAngle gis, slope(0);
	gis = gis.aTan2( (x0-P0.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue()),
		(y0-P0.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue()) );

	
	// MLA system construction
	TFreeVector falseOrigin(x0,y0,z0,TCoordSysFactory::k3DCartesian);
	TModifiedLocalAstronomicalRF* pMLA = new TModifiedLocalAstronomicalRF( "MLA",
		pGeoid, origin, falseOrigin, gis, slope);

	point.transform(pMLA);

/*	cout << point.getXCoord().getMetresValue() << endl;
	cout << point.getYCoord().getMetresValue() << endl;
	cout << point.getZCoord().getMetresValue() << endl;
*/

	*x = point.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue();
	*y = point.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue();
	*z = point.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue();

	delete pMLA;

	return 1;


}



// coordinates transformation from MLA system to CCS
int SpatialObjFns::transformFromMLA(double x0, double y0, double z0,
					  double* x, double* y, double* z, char* geoid)
{
	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x0<(-5000+lim)) || (x0>(6000-lim)) || (y0<lim) || (y0>12000-lim) )
	{
		return 0;
	}

	TPositionVector vectOrigin(x0, y0, z0, TCoordSysFactory::k3DCartesian),
		vectPoint(*x, *y, *z, TCoordSysFactory::k3DCartesian);

	TSpatialPosition origin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	origin.setCoordinates(vectOrigin);


	TSpatialPosition P0(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getOrigin());
	P0.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

	TRefSystemFactory::EGeoid pGeoid;
	string cg00("CG2000"), cg85("CG1985");
	if (geoid == cg00)
		pGeoid = TRefSystemFactory::kCG2000Machine;
	else 
		if (geoid == cg85)
			pGeoid = TRefSystemFactory::kCG1985Machine;
		else 
			return 0;

	// DIF *2
	TAngle gis, slope(0);
	gis = gis.aTan2( (x0-P0.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue()),
		(y0-P0.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue()) );

	
	// MLA system construction
	TFreeVector falseOrigin(x0,y0,z0,TCoordSysFactory::k3DCartesian);
	TModifiedLocalAstronomicalRF* pMLA = new TModifiedLocalAstronomicalRF( "MLA",
		pGeoid, origin, falseOrigin, gis, slope);

	 
	TSpatialPosition point(pMLA);
	point.setCoordinates(vectPoint);


	point.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

/*	cout << point.getXCoord().getMetresValue() << endl;
	cout << point.getYCoord().getMetresValue() << endl;
	cout << point.getZCoord().getMetresValue() << endl;
*/

	*x = point.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue();
	*y = point.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue();
	*z = point.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue();

	delete pMLA;

	return 1;


}


// coordinates transformation to MLA system (with bearing, slope and false origin = 0)
int SpatialObjFns::transformToMLA2(double x0, double y0, double z0,
					double* x, double* y, double* z, char* geoid)
{
	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x0<(-5000+lim)) || (x0>(6000-lim)) || (y0<lim) || (y0>12000-lim) )
	{
		return 0;
	}
	
	TPositionVector vectOrigin(x0, y0, z0,TCoordSysFactory::k3DCartesian),
		vectPoint(*x, *y, *z, TCoordSysFactory::k3DCartesian);

	TSpatialPosition origin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)),
		point(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	origin.setCoordinates(vectOrigin);
	point.setCoordinates(vectPoint);

	TSpatialPosition P0(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getOrigin());
	P0.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));

	TRefSystemFactory::EGeoid pGeoid;
	string cg00("CG2000"), cg85("CG1985");
	if (geoid == cg00)
		pGeoid = TRefSystemFactory::kCG2000Machine;
	else 
		if (geoid == cg85)
			pGeoid = TRefSystemFactory::kCG1985Machine;
		else 
		{
			return 0;
		}

	//DIF *1
	TAngle gis(0), slope(0);
	
	
	// MLA system construction
	TFreeVector falseOrigin(0,0,0, TCoordSysFactory::k3DCartesian);
	TModifiedLocalAstronomicalRF* pMLA = new TModifiedLocalAstronomicalRF( "MLA",
		pGeoid, origin, falseOrigin, gis, slope);

	point.transform(pMLA);

/*	cout << point.getXCoord().getValue() << endl;
	cout << point.getYCoord().getValue() << endl;
	cout << point.getZCoord().getValue() << endl;
*/

	*x = point.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue();
	*y = point.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue();
	*z = point.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue();

	delete pMLA;

	return 1;


}


// coordinates transformation from MLA system to CCS (with bearing, slope and false origin = 0)
int SpatialObjFns::transformFromMLA2(double x0, double y0, double z0,
					  double* x, double* y, double* z, char* geoid)
{
	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x0<(-5000+lim)) || (x0>(6000-lim)) || (y0<lim) || (y0>12000-lim) )
	{
		return 0;
	}
	

	TPositionVector vectOrigin(x0,y0,z0,TCoordSysFactory::k3DCartesian),
		vectPoint(*x,*y,*z,TCoordSysFactory::k3DCartesian);

	TSpatialPosition origin(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	origin.setCoordinates(vectOrigin);


	TSpatialPosition P0(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS)->getOrigin());
	P0.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));


	TRefSystemFactory::EGeoid pGeoid;
	string cg00("CG2000"), cg85("CG1985");
	if (geoid == cg00)
		pGeoid = TRefSystemFactory::kCG2000Machine;
	else 
		if (geoid == cg85)
			pGeoid = TRefSystemFactory::kCG1985Machine;
		else 
			return 0;

	//DIF *2
	TAngle gis(0), slope(0);
	

	// MLA system construction
	TFreeVector falseOrigin(0,0,0,TCoordSysFactory::k3DCartesian);
	TModifiedLocalAstronomicalRF* pMLA = new TModifiedLocalAstronomicalRF( "MLA",
		pGeoid, origin, falseOrigin, gis, slope);

	TSpatialPosition point(pMLA);
	point.setCoordinates(vectPoint);
	point.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));


/*	cout << point.getXCoord().getValue() << endl;
	cout << point.getYCoord().getValue() << endl;
	cout << point.getZCoord().getValue() << endl;
*/

	*x = point.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue();
	*y = point.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue();
	*z = point.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue();

	delete pMLA;

	return 1;


}


// coordinates of a point on the vertical of another
int SpatialObjFns::descenteVert(double x, double y, double h, double deltaH, double* xt, double* yt, double* ht)
{

	double lim = 0.000000001;
	// test to know if the origin is in the Cern grid for geoid definition
	if ( (x<(-5000+lim)) || (x>(6000-lim)) || (y<lim) || (y>12000-lim) )
	{
		return 0;
	}


	//Create the old point
	TPositionVector oldPtVec(x,y,h,TCoordSysFactory::k2DPlusH);

	TSpatialPosition oldPoint(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernXYHg00Machine));
	oldPoint.setCoordinates(oldPtVec);


	//create a LA (Origin = oldPoint)
	//origin must be in CGRF
	oldPoint.transform(TRefSystemFactory::getRefSystemFactory()->getGeoRefFrame(TRefSystemFactory::kCGRF));

	TModifiedLocalAstronomicalRF* localRF = new TModifiedLocalAstronomicalRF(	"Local reference frame",
																				TRefSystemFactory::kCG2000Machine,
																				oldPoint);


	//create new point in LA
	TPositionVector newPtVec(0,0, deltaH,TCoordSysFactory::k3DCartesian);
	TSpatialPosition newPoint(localRF);
	newPoint.setCoordinates(newPtVec);

	//transform new point in kCernXYHg00Machine
	newPoint.transform(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCernXYHg00Machine));

	delete localRF;

	TPositionVector res = newPoint.getCoordinates(TCoordSysFactory::k2DPlusH);

	//if((h + deltaH>= hres - 0.000005) && (h + deltaH<= hres + 0.000005))
	//{
		*xt = res.getX().getValue();
		*yt = res.getY().getValue();
		*ht = h + deltaH;
		return 1;
	//}
	//else
	//{
		//return 0;
	//}
}

