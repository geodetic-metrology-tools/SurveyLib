//  TRefSystemFactory.cpp
//
/* Factory for reference surfaces, reference frames et reference frame transformations. 
  
   
    Copyright 2002 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include <limits>
#include <iomanip>

#include "TReferenceEllipsoid.h"
#include "TGeodeticRefFrame.h"
#include "TAModifiedLocalastronomicalRF.h"
#include "TModifiedLocalAstronomicalRF.h"
#include "TGraphMLARF.h"
#include "TXYHeProjection.h"
#include "TX0Y0HeProjection.h"
#include "TXYHgProjection.h"
#include "TCernGridGeoid.h"
#include "TCernParabolicGeoid.h"
#include "TCernSphereGeoid.h"
#include "T3DLocalRefFrame.h"

#include "TMLA2GCTransformation.h"
#include "TGC2MLATransformation.h"
#include "TXYHs2MLATransformation.h"
#include "TMLA2XYHsTransformation.h"
#include "TLA2LGTransformation.h"
#include "TLG2LATransformation.h"
#include "TLG2GCTransformation.h"
#include "TGC2LGTransformation.h"
#include "THelmertTransformation.h"
#include "THelmertRefFrameTransform.h"
#include "TXYHe2MLATransformation.h"
#include "TMLA2XYHeTransformation.h"
#include "TX0Y0He2XYHeTransformation.h"
#include "TXYHe2X0Y0HeTransformation.h"
#include "TXYHg2XYHeTransformation.h"
#include "TXYHe2XYHgTransformation.h"


#include "TRefSystemFactory.h"
////////////////////////////////////////////////////////////////


//ClassImp(TRefSystemFactory)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
// fGraph initialisation to 0
TRefSystemFactory*  TRefSystemFactory::fRefSystemFactory = 0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TRefSystemFactory::TRefSystemFactory()
{// default constructor: build the unique instance of TRefSystemFactory
}



TRefSystemFactory::~TRefSystemFactory()
{// destructor
	//la fonction deleteRefSystemFactory est appele dans les destructeurs des projets
}


//////////////////////////////////////////////////////////////////////
//INIT FUNCTION
//////////////////////////////////////////////////////////////////////
void	TRefSystemFactory::init()
{// default constructor: build the unique instance of TRefSystemFactory
	
	///////////////////////////////////////////////////////////////////
	// Definition of the ellipsoid list
	string grs("GRS80"), wgsEll("WGS84 Ellipsoid"), internationalEll("Hayford1903 Ellipsoid"), sps("SphereSPS");

		// Sphere SPS
	TReferenceEllipsoid* pSphere = new TReferenceEllipsoid(sps);
	pSphere->setAAndESquared(6371000.0, 0.0);
	pSphere->setEllId(kSphere);
	fRefEllList.push_back(pSphere);	

		// GRS80
	TReferenceEllipsoid* pGRS80 = new TReferenceEllipsoid(grs);
	pGRS80->setAAndESquared(6378137.0, 0.0066943800229);
	pGRS80->setEllId(kGRS80);
	fRefEllList.push_back(pGRS80);

		// WGS
	TReferenceEllipsoid* pWGSEll = new TReferenceEllipsoid(wgsEll);
	pWGSEll->setAAndReciprocalF(6378137.0, 298.257223563);
	pWGSEll->setEllId(kWGSEll);
	fRefEllList.push_back(pWGSEll);

		// ROMA
	TReferenceEllipsoid* pInternationalEll = new TReferenceEllipsoid(internationalEll);
	pInternationalEll->setAAndESquared(6378388.0, 0.006722670022);
	pInternationalEll->setEllId(kInternationalEll);
	fRefEllList.push_back(pInternationalEll);



	// Definition of the reference frame list
	string cgrf("CGRF"), cgrfs("CGRFSphere"), itrf("ITRF97"), wgs("WGS84"), roma("ROMA40");
	string ccs("CCS");
	
		// CGRF
	TGeodeticRefFrame* pCGRF = new TGeodeticRefFrame(cgrf, pGRS80);
	pCGRF->setRefFrameId(kCGRF);
	fRefFrameList.push_back(pCGRF);
	fCGRF = pCGRF;
	
		// CGRF sphere
	TGeodeticRefFrame* pCGRFs = new TGeodeticRefFrame(cgrfs, pSphere);
	pCGRFs->setRefFrameId(kCGRFSphere);
	fRefFrameList.push_back(pCGRFs);
	fCGRFSphere = pCGRFs;

		// ITRF97
	TGeodeticRefFrame* pITRF = new TGeodeticRefFrame(itrf, pGRS80);
	pITRF->setRefFrameId(kITRF97);
	fRefFrameList.push_back(pITRF);

		// WGS84
	TGeodeticRefFrame* pWGS = new TGeodeticRefFrame(wgs, pWGSEll);
	pWGS->setRefFrameId(kWGS84);
	fRefFrameList.push_back(pWGS);

		// ROMA40
	TGeodeticRefFrame* pROMA = new TGeodeticRefFrame(roma, pInternationalEll);
	pROMA->setRefFrameId(kROMA40);
	fRefFrameList.push_back(pROMA);

		// Local Geodesique at CERN: origin = principal point of the system = P0 
	TSpatialPosition origin(pCGRF);
	TAngle phi, lambda;
	TLength H;
	phi.setGonsValue(51.3692);
	lambda.setGonsValue(6.72124);
	H.setMetresValue(433.65921);

	TPositionVector pos(TCoordSysFactory::kGeodetic);
	pos.setPhiEllipsoid(phi);
	pos.setLambdaEllipsoid(lambda);
	pos.setH(H);
	pos.setStatus(TVNumericValue::kKnown);
	
	origin.setCoordinates( pos );
	origin.setObjectStatus( TSpatialStatus::kCala );

	TModifiedLocalGeodeticRF* pLGp0 = new TModifiedLocalGeodeticRF( "LG P0", origin, pCGRF);
	pLGp0->setRefFrameId(kLGp0);
	fRefFrameList.push_back(pLGp0);

		// Local Astronomic at CERN: origin = principal point of the system = P0
	TAngle etaP0(0), xsiP0(0), dAlphaP0(0);
	TGraphLocalAstronomicalRF* pLAp0 = new TGraphLocalAstronomicalRF( "LA P0", etaP0, xsiP0, dAlphaP0, pLGp0 );
	pLAp0->setRefFrameId(kLAp0);
	fRefFrameList.push_back(pLAp0);
	
		// CCS : CERN Modified Local Astronomical system : principal point = P0 defined as false origin
	TFreeVector falseOrigin(2000, 2097.79265, 2433.66000, TCoordSysFactory::k3DCartesian);
	TAngle omega(0), phi2(0), kappa;
	kappa.setGonsValue(37.77864);

	TAModifiedLocalAstronomicalRF* pCCS = new TGraphMLARF(ccs, falseOrigin,
		pLAp0, omega, phi2, kappa);
	pCCS->setRefFrameId(kCCS);
	fRefFrameList.push_back(pCCS);

	

	///////////////////////////////////////////////////////////////////////////////	
	// Definition of the geoid list
	string cg00, cg00topo, cg00Machine, cg85, cg85Machine, cgSphere;
	cg00 = "CG2000 h=0";
	cg00topo = "CG2000 h=surface";
	cg00Machine = "CG2000 h=Machine";
	cg85 = "CG1985 h=0";
	cg85Machine = "CG1985 h=Machine";
	cgSphere = "Sphere";

	TPositionVector dl(-5000, 0, 0, TCoordSysFactory::k3DCartesian),
		ur(6000, 12000, 0, TCoordSysFactory::k3DCartesian);
	

		// CG2000 h=0
	TMatrix *NMatrix0 = new TMatrix(15,14);
	TMatrix *EtaMatrix0 = new TMatrix(15,14);
	TMatrix *XsiMatrix0 = new TMatrix(15,14);

	double n[15][14] = {{0.16748,0.13360,0.09381,0.05738,0.02980,0.01181,0.00240,-0.00096,-0.00140,0.00180,0.01058,0.02504,0.04444,0.06777},
		{0.17550,0.13998,0.09831,0.06061,0.03242,0.01400,0.00414,0.00047,-0.00043,0.00237,0.01038,0.02291,0.04020,0.06165},
		{0.18175,0.14509,0.10205,0.06361,0.03508,0.01624,0.00552,0.00103,-0.00005,0.00268,0.01036,0.02179,0.03703,0.05673},
		{0.18662,0.14954,0.10585,0.06678,0.03776,0.01842,0.00687,0.00135,-0.00001,0.00265,0.00986,0.02071,0.03483,0.05318},
		{0.19059,0.15388,0.10987,0.07004,0.04039,0.02042,0.00813,0.00185,0.00008,0.00228,0.00881,0.01907,0.03277,0.05020},
		{0.19351,0.15736,0.11321,0.07286,0.04264,0.02200,0.00908,0.00239,0.00017,0.00159,0.00725,0.01683,0.03023,0.04713},
		{0.19511,0.15907,0.11525,0.07489,0.04431,0.02315,0.00972,0.00261,0.00004,0.00075,0.00531,0.01410,0.02704,0.04355},
		{0.19567,0.15932,0.11599,0.07618,0.04572,0.02417,0.01020,0.00254,-0.00042,-0.00025,0.00320,0.01093,0.02310,0.03899},
		{0.19530,0.15838,0.11547,0.07670,0.04692,0.02523,0.01064,0.00233,-0.00116,-0.00148,0.00110,0.00777,0.01872,0.03336},
		{0.19377,0.15638,0.11395,0.07651,0.04753,0.02596,0.01111,0.00224,-0.00195,-0.00300,-0.00106,0.00489,0.01472,0.02791},
		{0.19033,0.15343,0.11216,0.07609,0.04797,0.02686,0.01194,0.00246,-0.00269,-0.00463,-0.00333,0.00197,0.01113,0.02347},
		{0.18503,0.14967,0.11067,0.07648,0.04949,0.02879,0.01345,0.00295,-0.00341,-0.00635,-0.00578,-0.00119,0.00737,0.01934},
		{0.18000,0.14658,0.11074,0.07892,0.05304,0.03223,0.01597,0.00396,-0.00383,-0.00777,-0.00788,-0.00409,0.00346,0.01493},
		{0.17974,0.14761,0.11436,0.08423,0.05900,0.03765,0.01979,0.00582,-0.00358,-0.00852,-0.00955,-0.00682,-0.00044,0.01042},
		{0.18700,0.15568,0.12296,0.09276,0.06729,0.04480,0.02449,0.00814,-0.00287,-0.00893,-0.01104,-0.00953,-0.00417,0.00625}};


	double eta[15][14] = {{11.71,18.31,19.51,16.21,11.11,6.61,2.31,0.21,-0.49,-3.09,-5.79,-7.89,-9.59,-10.79},
		{13.11,19.81,20.71,16.71,11.31,6.71,2.71,0.71,-0.09,-3.09,-5.39,-7.19,-8.99,-10.09},
		{14.11,21.01,21.51,16.81,11.41,7.01,3.31,1.21,0.11,-2.79,-4.99,-6.49,-8.19,-10.09},
		{14.61,21.31,21.61,16.91,11.61,7.21,3.91,1.51,0.01,-2.59,-4.49,-5.99,-7.69,-9.69},
		{14.51,21.21,22.01,17.31,11.91,7.71,4.41,1.81,0.01,-1.99,-3.99,-5.39,-7.29,-9.09},
		{14.61,21.71,22.71,17.81,12.41,8.21,4.81,2.01,0.41,-1.49,-3.39,-4.99,-6.99,-8.49},
		{15.11,22.11,23.01,18.21,12.81,8.61,5.11,2.31,0.61,-0.79,-2.79,-4.49,-6.59,-7.89},
		{15.91,22.51,23.11,18.21,12.91,8.81,5.41,2.71,0.81,-0.29,-2.09,-3.99,-5.99,-7.19},
		{16.71,22.91,23.11,17.91,12.91,9.11,5.71,3.11,1.11,0.11,-1.49,-3.49,-5.19,-6.29},
		{17.71,23.41,22.71,17.41,13.11,9.31,5.91,3.21,1.51,0.51,-1.19,-3.29,-4.69,-5.99},
		{18.31,23.31,21.91,16.81,12.61,8.91,5.91,3.51,2.01,0.91,-0.79,-2.79,-4.39,-5.79},
		{18.41,22.41,20.31,15.51,11.41,8.41,6.01,4.11,2.61,1.31,-0.39,-2.39,-3.99,-5.49},
		{17.31,20.01,17.81,13.71,10.41,8.11,6.21,4.61,3.01,1.41,-0.49,-2.09,-3.59,-5.39},
		{14.81,16.31,14.81,12.01,9.31,7.91,6.71,5.31,3.31,1.71,0.01,-1.49,-2.99,-5.49},
		{11.41,13.31,12.71,10.91,8.71,8.61,8.01,6.21,3.81,2.01,0.51,-0.89,-2.79,-5.69}};

	
	double xsi[15][14] = {{-14.80,-17.90,-17.00,-13.60,-9.50,-6.10,-3.10,-1.70,-0.60,1.70,4.40,7.60,10.10,12.30},
		{-14.30,-17.80,-17.20,-13.70,-9.70,-6.30,-2.90,-1.10,-0.50,1.70,3.50,5.90,9.00,11.50},
		{-13.70,-17.90,-17.40,-13.80,-9.80,-6.40,-3.20,-0.90,-0.10,1.90,3.60,5.10,7.80,10.00},
		{-13.30,-17.90,-18.00,-14.10,-10.00,-6.50,-3.70,-1.20,0.00,1.90,3.70,5.20,6.70,9.10},
		{-12.60,-17.90,-18.20,-14.30,-10.10,-6.60,-3.80,-1.60,-0.10,1.90,3.80,5.40,6.80,8.60},
		{-11.60,-16.90,-17.80,-14.10,-10.00,-6.60,-3.80,-1.60,-0.20,1.60,3.80,5.50,7.10,8.40},
		{-11.00,-15.80,-16.90,-13.70,-9.90,-6.60,-3.80,-1.50,-0.10,1.30,3.70,5.50,7.40,8.60},
		{-10.80,-15.10,-16.10,-13.30,-10.00,-6.90,-3.90,-1.60,0.00,1.10,3.20,5.40,7.60,9.10},
		{-10.70,-14.60,-14.90,-12.40,-9.60,-7.00,-4.20,-1.80,0.00,1.10,2.80,4.90,7.10,9.10},
		{-10.20,-14.10,-14.20,-11.70,-9.20,-6.80,-4.40,-2.10,-0.30,1.00,2.60,4.50,6.10,8.10},
		{-8.90,-13.40,-13.70,-11.30,-9.10,-7.00,-4.80,-2.60,-0.70,0.80,2.50,4.40,5.90,7.20},
		{-7.80,-12.30,-13.10,-11.50,-9.70,-7.70,-5.50,-3.10,-1.10,0.60,2.30,4.20,5.90,7.20},
		{-8.70,-12.10,-13.30,-12.20,-10.70,-8.80,-6.60,-4.10,-1.80,-0.10,1.70,3.50,5.50,7.40},
		{-12.70,-14.40,-14.80,-13.50,-11.90,-10.40,-7.80,-5.30,-2.60,-0.70,1.30,3.20,5.10,7.30},
		{-16.30,-18.10,-17.40,-15.30,-12.90,-11.80,-9.10,-6.00,-3.20,-1.10,0.80,2.60,4.60,6.90}};

	
	for(int i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*NMatrix0)(i,j) = n[i][j];
		
	}


	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*EtaMatrix0)(i,j) = eta[i][j];
	}

	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*XsiMatrix0)(i,j) = xsi[i][j];
	}


	TCernGridGeoid* pCG2000 = new TCernGridGeoid(cg00,
		NMatrix0, EtaMatrix0, XsiMatrix0, dl, ur, pCGRF, pGRS80, pCCS);
	pCG2000->setGeoidId(kCG2000);
	fGeoidList.push_back(pCG2000);


		// CG2000 h=topo
	TMatrix *NMatrixTopo = new TMatrix(15,14);
	TMatrix *EtaMatrixTopo = new TMatrix(15,14);
	TMatrix *XsiMatrixTopo = new TMatrix(15,14);

	double nTopo[15][14] = {{0.21922,0.16100,0.10373,0.05752,0.02649,0.00767,-0.00007,-0.00098,-0.00152,0.00108,0.01032,0.02581,0.04698,0.07243},
		{0.23180,0.16931,0.10849,0.06065,0.02924,0.01044,0.00194,0.00081,-0.00018,0.00220,0.01096,0.02393,0.04252,0.06572},
		{0.24023,0.17527,0.11153,0.06374,0.03237,0.01326,0.00333,0.00092,0.00033,0.00298,0.01177,0.02378,0.03968,0.06077},
		{0.24589,0.18158,0.11658,0.06768,0.03575,0.01604,0.00510,0.00060,0.00000,0.00322,0.01171,0.02364,0.03817,0.05754},
		{0.25172,0.18940,0.12259,0.07182,0.03913,0.01867,0.00667,0.00115,0.00031,0.00308,0.01069,0.02205,0.03652,0.05485},
		{0.25389,0.19378,0.12654,0.07508,0.04188,0.02062,0.00793,0.00218,0.00082,0.00257,0.00920,0.01966,0.03410,0.05246},
		{0.25441,0.19465,0.12844,0.07729,0.04381,0.02203,0.00886,0.00269,0.00113,0.00210,0.00724,0.01686,0.03094,0.04930},
		{0.25449,0.19398,0.12933,0.07875,0.04585,0.02351,0.00967,0.00275,0.00095,0.00171,0.00520,0.01355,0.02680,0.04447},
		{0.25124,0.19106,0.12864,0.08017,0.04816,0.02524,0.01042,0.00273,0.00054,0.00084,0.00325,0.01035,0.02205,0.03773},
		{0.24888,0.18706,0.12580,0.08069,0.04922,0.02611,0.01104,0.00293,0.00003,-0.00052,0.00128,0.00777,0.01817,0.03158},
		{0.24325,0.18406,0.12281,0.08000,0.04943,0.02714,0.01236,0.00370,-0.00059,-0.00218,-0.00078,0.00514,0.01508,0.02728},
		{0.22627,0.17768,0.11998,0.08020,0.05104,0.02968,0.01425,0.00431,-0.00132,-0.00405,-0.00337,0.00184,0.01117,0.02327},
		{0.20634,0.16703,0.11818,0.08264,0.05539,0.03378,0.01752,0.00550,-0.00198,-0.00557,-0.00530,-0.00092,0.00709,0.01845},
		{0.20062,0.16063,0.12180,0.08893,0.06287,0.04081,0.02246,0.00794,-0.00158,-0.00597,-0.00671,-0.00357,0.00294,0.01328},
		{0.21137,0.17139,0.13180,0.09834,0.07351,0.05069,0.02838,0.01065,-0.00039,-0.00604,-0.00794,-0.00645,-0.00137,0.00893}};
			
	double etaTopo[15][24] = {{23.27,29.57,26.87,19.47,11.77,6.67,0.37,-1.13,0.47,-3.13,-6.43,-8.53,-10.23,-11.63},
		{27.57,31.07,29.27,19.77,11.97,5.97,1.37,-0.43,0.57,-4.03,-5.93,-7.93,-9.83,-10.73},
		{28.57,35.17,29.57,19.37,11.87,6.87,2.17,0.07,0.87,-3.63,-5.73,-7.53,-9.33,-11.33},
		{30.67,32.77,28.27,18.77,11.97,6.87,3.37,0.87,0.07,-3.53,-5.23,-6.63,-8.23,-10.43},
		{25.67,35.57,29.77,19.27,12.07,7.37,4.37,0.87,-0.53,-2.33,-4.63,-5.73,-7.63,-9.93},
		{25.17,37.97,32.17,20.17,12.97,8.07,4.47,1.27,0.07,-1.93,-4.13,-5.33,-7.93,-9.73},
		{24.97,36.57,32.47,20.37,13.57,8.57,4.77,1.57,0.17,-0.83,-3.33,-4.73,-7.63,-8.93},
		{28.87,36.87,31.87,20.27,12.47,8.87,4.87,2.47,-0.33,-0.33,-2.43,-4.33,-6.83,-8.13},
		{30.47,36.27,32.57,18.97,13.67,9.07,5.37,2.77,0.27,0.37,-1.33,-3.83,-5.43,-6.53},
		{31.97,37.77,30.87,19.27,14.97,10.27,5.77,2.37,0.67,0.57,-1.13,-3.83,-4.93,-6.23},
		{25.17,39.17,27.97,18.27,14.07,8.77,5.57,2.87,1.77,0.77,-1.03,-3.33,-4.83,-5.43},
		{21.37,38.87,25.27,16.97,11.67,8.47,5.87,3.67,2.37,1.47,-0.53,-2.73,-4.23,-5.03},
		{17.97,33.37,21.47,14.77,10.57,7.97,5.67,4.37,2.87,1.37,-1.23,-2.43,-4.03,-4.63},
		{22.17,21.57,15.17,12.47,8.97,7.67,6.47,5.67,2.47,1.67,-0.23,-1.73,-2.53,-4.93},
		{8.47,17.77,13.87,11.17,6.27,8.77,8.67,6.77,3.27,1.77,0.47,-0.83,-2.63,-5.83}};

	double xsiTopo[15][14] = {{-27.81,-27.61,-22.01,-15.71,-10.01,-6.41,-2.01,-1.91,-1.51,1.89,4.39,7.99,10.79,13.29},
		{-26.61,-27.21,-22.01,-15.71,-9.91,-6.61,-1.91,-0.11,-1.51,1.89,2.89,5.39,9.69,13.09},
		{-24.01,-28.91,-22.11,-15.31,-10.11,-6.41,-2.81,0.69,-0.71,2.39,3.49,4.49,8.59,10.09},
		{-24.11,-30.51,-23.91,-15.81,-10.61,-6.61,-3.81,-0.41,-0.01,2.39,4.09,5.59,6.19,9.39},
		{-23.81,-27.91,-24.51,-16.31,-10.91,-6.81,-3.71,-1.31,-0.31,2.09,4.19,5.89,6.59,8.89},
		{-15.21,-26.41,-23.91,-16.31,-10.81,-6.81,-3.81,-1.41,-0.41,1.59,4.29,5.79,7.49,8.59},
		{-19.71,-25.11,-22.81,-15.41,-10.51,-6.71,-3.71,-1.01,-0.01,0.89,4.39,5.69,7.99,9.09},
		{-17.01,-23.01,-22.51,-15.21,-10.91,-7.31,-3.81,-1.51,0.39,0.49,3.49,5.79,8.19,10.19},
		{-18.11,-21.81,-20.21,-14.31,-10.51,-8.11,-4.31,-1.51,0.49,0.79,2.99,4.99,7.39,10.19},
		{-21.71,-22.01,-17.61,-13.01,-10.51,-6.91,-4.41,-1.91,-0.01,0.69,2.49,4.49,5.69,8.29},
		{-13.81,-22.31,-17.11,-12.21,-9.21,-7.21,-4.91,-2.41,-0.41,0.89,2.69,4.69,6.09,6.59},
		{5.09,-19.41,-14.71,-12.41,-10.31,-8.11,-5.61,-2.41,-0.81,0.69,2.59,4.69,6.39,6.99},
		{0.29,-15.11,-15.21,-13.01,-11.61,-9.21,-6.91,-4.21,-1.41,-0.11,1.79,3.19,5.39,7.59},
		{-18.21,-13.61,-16.61,-14.71,-12.61,-12.21,-8.11,-6.11,-2.71,-0.81,1.29,3.49,5.39,7.49},
		{-22.41,-24.61,-20.71,-16.91,-13.21,-14.31,-10.21,-6.31,-3.21,-1.11,0.69,2.39,4.69,6.89}};


	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*NMatrixTopo)(i,j) = nTopo[i][j];
	}


	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*EtaMatrixTopo)(i,j) = etaTopo[i][j];
	}

	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*XsiMatrixTopo)(i,j) = xsiTopo[i][j];
	}



	TCernGridGeoid* pCG2000Topo = new TCernGridGeoid(cg00topo,
		NMatrixTopo, EtaMatrixTopo, XsiMatrixTopo, dl, ur, pCGRF, pGRS80, pCCS);
	pCG2000Topo->setGeoidId(kCG2000topo);
	fGeoidList.push_back(pCG2000Topo);


		// CG2000 h=Machine
	TMatrix *NMatrixLEP = new TMatrix(15,14);
	TMatrix *EtaMatrixLEP = new TMatrix(15,14);
	TMatrix *XsiMatrixLEP = new TMatrix(15,14);

	double nLEP[15][14] = {{0.19361,0.15055,0.10151,0.05838,0.02779,0.00893,0.00078,-0.00076,-0.00127,0.00145,0.01059,0.02590,0.04668,0.07147},
		{0.20247,0.15771,0.10596,0.06133,0.03034,0.01144,0.00264,0.00087,-0.00011,0.00245,0.01110,0.02399,0.04227,0.06493},
		{0.20942,0.16300,0.10923,0.06412,0.03316,0.01402,0.00389,0.00099,0.00025,0.00305,0.01163,0.02349,0.03923,0.05997},
		{0.21488,0.16780,0.11332,0.06749,0.03619,0.01648,0.00540,0.00074,0.00000,0.00311,0.01133,0.02297,0.03748,0.05658},
		{0.21943,0.17330,0.11839,0.07137,0.03927,0.01886,0.00683,0.00121,0.00018,0.00282,0.01024,0.02138,0.03571,0.05379},
		{0.22271,0.17772,0.12250,0.07480,0.04196,0.02074,0.00798,0.00202,0.00052,0.00227,0.00869,0.01903,0.03321,0.05107},
		{0.22399,0.17939,0.12479,0.07720,0.04391,0.02203,0.00878,0.00242,0.00071,0.00167,0.00665,0.01614,0.03000,0.04772},
		{0.22394,0.17906,0.12557,0.07870,0.04575,0.02327,0.00942,0.00243,0.00039,0.00101,0.00452,0.01280,0.02584,0.04291},
		{0.22331,0.17753,0.12469,0.07957,0.04762,0.02481,0.01001,0.00227,-0.00022,-0.00002,0.00251,0.00952,0.02111,0.03654},
		{0.22138,0.17467,0.12235,0.07946,0.04844,0.02567,0.01061,0.00235,-0.00087,-0.00149,0.00044,0.00679,0.01709,0.03050},
		{0.21637,0.17055,0.11965,0.07855,0.04855,0.02659,0.01175,0.00293,-0.00155,-0.00320,-0.00176,0.00402,0.01374,0.02608},
		{0.20758,0.16475,0.11700,0.07858,0.05005,0.02891,0.01350,0.00344,-0.00234,-0.00511,-0.00440,0.00068,0.00986,0.02196},
		{0.19771,0.15849,0.11586,0.08109,0.05406,0.03276,0.01646,0.00445,-0.00301,-0.00666,-0.00648,-0.00225,0.00573,0.01718},
		{0.19468,0.15688,0.11933,0.08700,0.06112,0.03929,0.02098,0.00658,-0.00284,-0.00729,-0.00805,-0.00495,0.00152,0.01194},
		{0.20379,0.16617,0.12901,0.09639,0.07108,0.04835,0.02654,0.00914,-0.00192,-0.00757,-0.00942,-0.00786,-0.00276,0.00743}};

	double etaLEP[15][14] = {{15.74,23.34,23.94,18.84,11.74,6.74,0.74,-0.76,0.14,-3.16,-6.36,-8.46,-10.16,-11.46},
		{16.74,25.24,25.94,19.24,11.94,6.24,1.64,-0.06,0.44,-3.86,-5.86,-7.76,-9.66,-10.36},
		{18.04,27.24,26.64,19.04,11.84,6.94,2.54,0.44,0.64,-3.46,-5.56,-7.06,-9.06,-10.96},
		{18.64,27.34,26.34,18.54,12.04,7.04,3.44,1.04,0.04,-3.26,-5.06,-6.46,-8.06,-10.26},
		{17.94,26.54,27.14,19.04,12.24,7.44,4.34,1.04,-0.26,-2.26,-4.46,-5.76,-7.56,-9.66},
		{18.04,27.34,28.24,19.84,12.94,8.14,4.54,1.44,0.04,-1.86,-3.96,-5.26,-7.66,-9.16},
		{18.74,27.84,28.34,20.14,13.54,8.64,4.84,1.74,0.24,-0.86,-3.16,-4.76,-7.36,-8.56},
		{20.04,28.24,28.34,20.04,13.04,8.94,4.94,2.44,0.14,-0.26,-2.36,-4.26,-6.56,-7.66},
		{20.64,28.84,28.54,19.44,13.54,9.24,5.44,2.74,0.44,0.24,-1.46,-3.76,-5.46,-6.46},
		{21.84,29.64,27.74,18.84,14.34,9.94,5.74,2.54,0.94,0.44,-1.16,-3.76,-4.86,-6.16},
		{22.54,29.64,26.34,18.14,13.64,8.84,5.64,2.94,1.84,0.84,-0.96,-3.16,-4.66,-5.66},
		{22.34,29.04,24.14,16.64,11.64,8.44,5.94,3.84,2.44,1.44,-0.46,-2.66,-4.16,-5.16},
		{20.64,26.14,20.44,14.54,10.54,8.04,5.94,4.44,2.94,1.34,-0.96,-2.36,-3.96,-4.86},
		{18.54,19.64,15.84,12.44,8.94,7.74,6.64,5.54,2.84,1.64,-0.16,-1.66,-2.56,-4.86},
		{12.84,15.74,13.74,11.04,7.24,8.74,8.54,6.64,3.44,1.84,0.44,-0.86,-2.56,-5.66}};

	double xsiLEP[15][14] = {{-18.40,-22.10,-20.10,-15.20,-9.90,-6.30,-2.10,-1.80,-1.20,1.80,4.40,8.00,10.70,12.90},
		{-17.40,-21.80,-20.30,-15.20,-9.90,-6.50,-2.00,-0.50,-1.10,1.80,3.10,5.50,9.60,12.40},
		{-16.70,-22.30,-20.60,-15.00,-10.10,-6.40,-2.80,0.30,-0.40,2.40,3.70,4.80,8.40,10.10},
		{-16.70,-22.40,-22.00,-15.50,-10.50,-6.50,-3.70,-0.50,0.00,2.30,4.00,5.40,6.30,9.30},
		{-15.30,-22.80,-22.30,-16.00,-10.70,-6.70,-3.70,-1.30,-0.20,2.10,4.20,5.70,6.80,8.80},
		{-13.70,-21.20,-21.80,-15.90,-10.60,-6.70,-3.80,-1.40,-0.30,1.60,4.20,5.70,7.40,8.50},
		{-12.60,-19.40,-20.80,-15.10,-10.40,-6.60,-3.70,-1.10,0.00,1.10,4.20,5.80,7.90,8.90},
		{-12.70,-18.50,-19.70,-14.80,-10.80,-7.20,-3.80,-1.50,0.40,0.70,3.40,5.70,8.10,9.70},
		{-13.40,-18.00,-17.90,-13.70,-10.30,-7.90,-4.20,-1.50,0.40,1.00,2.90,5.10,7.40,9.90},
		{-12.30,-17.50,-16.60,-12.60,-10.00,-6.90,-4.40,-1.90,0.00,0.90,2.60,4.50,5.90,8.30},
		{-9.80,-16.80,-16.20,-12.00,-9.20,-7.20,-4.80,-2.40,-0.50,0.90,2.60,4.60,6.00,6.90},
		{-6.60,-14.80,-14.60,-12.20,-10.10,-8.00,-5.60,-2.60,-0.90,0.70,2.60,4.60,6.30,7.10},
		{-6.90,-13.40,-14.70,-13.00,-11.30,-9.10,-6.80,-4.10,-1.40,-0.10,1.80,3.30,5.60,7.60},
		{-14.80,-15.40,-16.30,-14.30,-12.60,-11.70,-8.10,-5.80,-2.50,-0.70,1.40,3.40,5.40,7.50},
		{-20.80,-21.80,-19.80,-16.50,-13.30,-13.50,-10.00,-6.30,-3.20,-1.00,0.70,2.50,4.70,6.90}};


	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*NMatrixLEP)(i,j) = nLEP[i][j];
	}


	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*EtaMatrixLEP)(i,j) = etaLEP[i][j];
	}

	for(i = 0; i<15; i++)
	{
		for (int j=0; j<14; j++)
			(*XsiMatrixLEP)(i,j) = xsiLEP[i][j];
	}



	TCernGridGeoid* pCG2000Machine = new TCernGridGeoid(cg00Machine,
		NMatrixLEP, EtaMatrixLEP, XsiMatrixLEP, dl, ur, pCGRF, pGRS80, pCCS);
	pCG2000Machine->setGeoidId(kCG2000Machine);
	fGeoidList.push_back(pCG2000Machine);



		//CGSphere
	TCernSphereGeoid* pCGSphere = new TCernSphereGeoid(cgSphere, pCGRFs, pSphere, pCCS);
	pCGSphere->setGeoidId(kCGSphere);
	fGeoidList.push_back(pCGSphere);
	
		// CG1985 h=0
	TAngle ang;
	ang.setGonsValue(48.772);
	double a(0.535), b(-0.096), th(ang.getRadiansValue());
	TCernParabolicGeoid* pCG1985 = new TCernParabolicGeoid(cg85,a,b,th, pCGRF, pGRS80, pCCS);
	pCG1985->setGeoidId(kCG1985);
	fGeoidList.push_back(pCG1985);

		// CG1985 h=Machine
	TAngle angLEP;
	angLEP.setGonsValue(48.219);
	double aLEP(0.614), bLEP(-0.106), thLEP(angLEP.getRadiansValue());
	TCernParabolicGeoid* pCG1985Machine = new TCernParabolicGeoid(cg85Machine,aLEP,bLEP,thLEP, pCGRF, pGRS80, pCCS);
	pCG1985Machine->setGeoidId(kCG1985Machine);
	fGeoidList.push_back(pCG1985Machine);

	/////////////////////////////////////////////////////////////////////
	// Definition of the CERN projection list (included in ref frame list)

			// CERN XYHs projection: XY system = CCS, Hs = height above SPS sphere (projection of the xy point on the sphere)
	TXYHeProjection* pCernXYHs = new TXYHeProjection( "CERN XYHs", pSphere, pCCS);
	pCernXYHs->setRefFrameId(kCERNXYHsSphereSPS);
	fRefFrameList.push_back(pCernXYHs);

		// CERN XYHe projection: XY system = CCS, He = height above ellipsoid (projection of the xy point on the ellipsoid)
	TXYHeProjection* pCernXYHe = new TXYHeProjection( "CERN XYHe", pGRS80, pCCS);
	pCernXYHe->setRefFrameId(kCernXYHe);
	fRefFrameList.push_back(pCernXYHe);

		// CERN X0Y0He projection: X0Y0 = projection of XY on the ellipsoid's level (h=0)
	TX0Y0HeProjection* pCernX0Y0He = new TX0Y0HeProjection( "CERN X0Y0He", pCernXYHe);
	pCernX0Y0He->setRefFrameId(kCernX0Y0He);
	fRefFrameList.push_back(pCernX0Y0He);

		// CERN XYHg projection CG2000: XY system = CCS, Hg = height above geoid CG2000 (projection of the xy point on the geoid)
	TXYHgProjection* pCernXYHg00 = new TXYHgProjection( "CERN XYHg2000", pCG2000 , pCernXYHe);
	pCernXYHg00->setRefFrameId(kCernXYHg00);
	fRefFrameList.push_back(pCernXYHg00);

		// CERN XYHg projection CG2000Topo :XY system = CCS, Hg = height above geoid CG2000Topo (projection of the xy point on the geoid)
	TXYHgProjection* pCernXYHg00Topo = new TXYHgProjection( "CERN XYHg2000Topo", pCG2000Topo , pCernXYHe);
	pCernXYHg00Topo->setRefFrameId(kCernXYHg00Topo);
	fRefFrameList.push_back(pCernXYHg00Topo);
	
		// CERN XYHg projection CG2000Machine: XY system = CCS, Hg = height above geoid CG2000Machine (projection of the xy point on the geoid)
	TXYHgProjection* pCernXYHg00Machine = new TXYHgProjection( "CERN XYHg2000Machine", pCG2000Machine , pCernXYHe);
	pCernXYHg00Machine->setRefFrameId(kCernXYHg00Machine);
	fRefFrameList.push_back(pCernXYHg00Machine);

		// CERN XYHg projection CG1985: XY system = CCS, Hg = height above geoid CG1985 (projection of the xy point on the geoid)
	TXYHgProjection* pCernXYHg85 = new TXYHgProjection( "CERN XYHg1985", pCG1985 , pCernXYHe);
	pCernXYHg85->setRefFrameId(kCernXYHg85);
	fRefFrameList.push_back(pCernXYHg85);

		// CERN XYHg projection CG1985Machine: XY system = CCS, Hg = height above geoid CG1985Machine (projection of the xy point on the geoid)
	TXYHgProjection* pCernXYHg85Machine = new TXYHgProjection( "CERN XYHg1985Machine", pCG1985Machine , pCernXYHe);
	pCernXYHg85Machine->setRefFrameId(kCernXYHg85Machine);
	fRefFrameList.push_back(pCernXYHg85Machine);



	/////////////////////////////////////////////////////////////////////////////////////////////
	// Definition of the CERN's ref. frames transformations


		// Transformation between CERN projection XYHs and CCS
	TXYHs2MLATransformation* pXYHs2CCS = new TXYHs2MLATransformation(pCernXYHs);
	pXYHs2CCS->setTransformId( kXYHsSphereSPS2CCS);
	fTransformList.push_back(pXYHs2CCS);
		//Inverse
	TARefFrameTransformation* pCCS2XYHs = pXYHs2CCS->inverse(); //utilise new
	pCCS2XYHs->setTransformId( kCCS2XYHsSphereSPS);
	fTransformList.push_back(pCCS2XYHs);


		// Transformation between CCS and CGRF
	/*Il est equivalent de mettre CG2000 ou CG1985 car les parametres du geoide au niveau de P0,
	servant a definir la transformation sont equivalent*/
	TMLA2GCTransformation* pCCS2CGRF = new TMLA2GCTransformation(pCCS, pCG1985Machine);
	pCCS2CGRF->setTransformId(kCCS2CGRF);
	fTransformList.push_back(pCCS2CGRF);
		//Inverse
	TARefFrameTransformation* pCGRF2CCS = pCCS2CGRF->inverse(); //utilise new
	pCGRF2CCS->setTransformId(kCGRF2CCS);
	fTransformList.push_back(pCGRF2CCS);


		// Transformation between CCS and CGRFSphere
	//rotation pour diriger les axes du CGRFs parallele a ceux du CGRF
	TAngle rx, ry, rz;
	rx.setGonsValue(-42.726243230216);
	ry.setGonsValue(-25.285434244947);
	rz.setGonsValue(-77.864346765085);
	TRotation rs(TRotationMatrix::kRzyx, rx.getRadiansValue(), ry.getRadiansValue(), rz.getRadiansValue());
	//translation pour situer le centre de la sphere
	TLength txs (4381882.331989), tys (461505.530464), tzs (4598944.364158);
	TTranslation transls(txs, tys, tzs);
	//facteur d echelle
	TEnlargement ks (1.0);
	THelmertRefFrameTransform* pCCS2CGRFs = new THelmertRefFrameTransform(pCCS, pCGRFs, ks, rs, transls);
	pCCS2CGRFs->setTransformId(kCCS2CGRFSphere);
	fTransformList.push_back(pCCS2CGRFs);
		//Inverse
	TARefFrameTransformation* pCGRFs2CCS = pCCS2CGRFs->inverse();//utilise new
	pCGRFs2CCS->setTransformId(kCGRFSphere2CCS);
	fTransformList.push_back(pCGRFs2CCS);


		// Transformation between LAp0 and LGp0
	TLA2LGTransformation* pLAp02LGp0 = new TLA2LGTransformation(pLAp0);
	pLAp02LGp0->setTransformId(kLAp02LGp0);
	fTransformList.push_back(pLAp02LGp0);
		//Inverse
	TARefFrameTransformation* pLGp02LAp0 = pLAp02LGp0->inverse(); //utilise new
	pLGp02LAp0->setTransformId(kLGp02LAp0);
	fTransformList.push_back(pLGp02LAp0);


		//Transformation between LGp0 and CGRF
	TLG2GCTransformation* pLGp02CGRF = new TLG2GCTransformation(pLGp0);
	pLGp02CGRF->setTransformId(kLGp02CGRF);
	fTransformList.push_back(pLGp02CGRF);
		//Inverse
	TARefFrameTransformation* pCGRF2LGp0 = pLGp02CGRF->inverse(); //utilise new
	pCGRF2LGp0->setTransformId(kCGRF2LGp0);
	fTransformList.push_back(pCGRF2LGp0);


		// Helmert Transformation between LAp0 and CCS
	TRotation r(TRotationMatrix::kRzyx, 0, 0, -(kappa.getRadiansValue()));
	TTranslation transl(falseOrigin.getX(), falseOrigin.getY(),	(falseOrigin.getZ()) );
	TEnlargement enl(1.0);
	THelmertRefFrameTransform* pLAp02CCS = new THelmertRefFrameTransform(pLAp0, pCCS, enl, r, transl);
	pLAp02CCS->setTransformId(kLAp02CCS);
	fTransformList.push_back(pLAp02CCS);
		//Inverse
	TARefFrameTransformation* pCCS2LAp0 = pLAp02CCS->inverse(); //utilise new
	pCCS2LAp0->setTransformId(kCCS2LAp0);
	fTransformList.push_back(pCCS2LAp0);

	
		// Helmert Transformation between ROMA40 and WGS84
	TAngle om1, p1, k1;
	om1.setDMSValue(0, 0, -1.822);
	p1.setDMSValue(0, 0, 3.235);
	k1.setDMSValue(0, 0, -0.762);
	TRotation r1(TRotationMatrix::kRzyx, om1.getRadiansValue(), p1.getRadiansValue(), k1.getRadiansValue());
	TLength tx(-54.62), ty(-24.26), tz(17.75);
	TTranslation transl1(tx, ty, tz);
	TEnlargement enl1(1.0 - 0.00002801);
	THelmertRefFrameTransform* pROMA2WGS = new THelmertRefFrameTransform(pROMA, pWGS, enl1, r1, transl1);
	pROMA2WGS->setTransformId(kROMA2WGS);
	fTransformList.push_back(pROMA2WGS);
		//Inverse
	TARefFrameTransformation* pWGS2ROMA = pROMA2WGS->inverse(); //utilise new
	pWGS2ROMA->setTransformId(kWGS2ROMA);
	fTransformList.push_back(pWGS2ROMA);

	
		// Helmert Transformation between WGS84 and CGRF
	TAngle om2, p2, k2;
	om2.setGonsValue(-0.0003314103458);
	p2.setGonsValue(0.0022563667184);
	k2.setGonsValue(0.0008629680740);
	TRotation r2(TRotationMatrix::kRzyx, om2.getRadiansValue(), p2.getRadiansValue(), k2.getRadiansValue());
	TLength Tx(114.1736041), Ty(114.1154332), Tz(-178.5526666);
	TTranslation transl2(Tx, Ty, Tz);
	TEnlargement enl2(0.999998644222261);
	THelmertRefFrameTransform* pWGS2CGRF = new THelmertRefFrameTransform(pWGS, pCGRF, enl2, r2, transl2);
	pWGS2CGRF->setTransformId(kWGS2CGRF);
	fTransformList.push_back(pWGS2CGRF);
		//Inverse
	TARefFrameTransformation* pCGRF2WGS = pWGS2CGRF->inverse(); //utilise new
	pCGRF2WGS->setTransformId(kCGRF2WGS);
	fTransformList.push_back(pCGRF2WGS);


		// Transformation between CERN projection XYHe and CCS
	TXYHe2MLATransformation* pXYHe2CCS = new TXYHe2MLATransformation(pCernXYHe);
	pXYHe2CCS->setTransformId(kXYHe2CCS);
	fTransformList.push_back(pXYHe2CCS);
		//Inverse
	TARefFrameTransformation* pCCS2XYHe = pXYHe2CCS->inverse(); //utilise new
	pCCS2XYHe->setTransformId(kCCS2XYHe);
	fTransformList.push_back(pCCS2XYHe);


		// Transformation between CERN projection X0Y0He and CERN projection XYHe
	TX0Y0He2XYHeTransformation* pX0Y0He2XYHe =  new TX0Y0He2XYHeTransformation(pCernX0Y0He) ;
	pX0Y0He2XYHe->setTransformId(kX0Y0He2XYHe);
	fTransformList.push_back(pX0Y0He2XYHe);
		//Inverse
	TARefFrameTransformation* pXYHe2X0Y0He =  pX0Y0He2XYHe->inverse(); //utilise new
	pXYHe2X0Y0He->setTransformId(kXYHe2X0Y0He);
	fTransformList.push_back(pXYHe2X0Y0He);


		// Transformation between CERN projection XYHg (Geoid 2000) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe = new TXYHg2XYHeTransformation(pCernXYHg00) ;
	pXYHg2XYHe->setTransformId(kXYHg2XYHe);
	fTransformList.push_back(pXYHg2XYHe);
		//Inverse
	TARefFrameTransformation* pXYHe2XYHg = pXYHg2XYHe->inverse(); //utilise new
	pXYHe2XYHg->setTransformId(kXYHe2XYHg);
	fTransformList.push_back(pXYHe2XYHg);


		// Transformation between CERN projection XYHg (Geoid 2000Topo) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe00Topo = new TXYHg2XYHeTransformation(pCernXYHg00Topo) ;
	pXYHg2XYHe00Topo->setTransformId(kXYHg2XYHe00Topo);
	fTransformList.push_back(pXYHg2XYHe00Topo);
		//Inverse
	TARefFrameTransformation* pXYHe00Topo2XYHg = pXYHg2XYHe00Topo->inverse(); //utilise new
	pXYHe00Topo2XYHg->setTransformId(kXYHe00Topo2XYHg);
	fTransformList.push_back(pXYHe00Topo2XYHg);


		// Transformation between CERN projection XYHg (Geoid 2000Machine) and XYHe 
	TXYHg2XYHeTransformation* pXYHg2XYHe00Machine = new TXYHg2XYHeTransformation(pCernXYHg00Machine) ;
	pXYHg2XYHe00Machine->setTransformId(kXYHg2XYHe00Machine);
	fTransformList.push_back(pXYHg2XYHe00Machine);
		//Inverse
	TARefFrameTransformation* pXYHe00Machine2XYHg = pXYHg2XYHe00Machine->inverse(); //utilise new
	pXYHe00Machine2XYHg->setTransformId(kXYHe00Machine2XYHg);
	fTransformList.push_back(pXYHe00Machine2XYHg);


		// Transformation between CERN projection XYHg (Geoid 1985) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe85 = new TXYHg2XYHeTransformation(pCernXYHg85) ;
	pXYHg2XYHe85->setTransformId(kXYHg2XYHe85);
	fTransformList.push_back(pXYHg2XYHe85);
		//Inverse
	TARefFrameTransformation* pXYHe852XYHg = pXYHg2XYHe85->inverse(); //utilise new
	pXYHe852XYHg->setTransformId(kXYHe852XYHg);
	fTransformList.push_back(pXYHe852XYHg);


		// Transformation between CERN projection XYHg (Geoid 1985Machine) and XYHe
	TXYHg2XYHeTransformation* pXYHg2XYHe85Machine = new TXYHg2XYHeTransformation(pCernXYHg85Machine) ;
	pXYHg2XYHe85Machine->setTransformId(kXYHg2XYHe85Machine);
	fTransformList.push_back(pXYHg2XYHe85Machine);
		//Inverse
	TARefFrameTransformation* pXYHe85Machine2XYHg = pXYHg2XYHe85Machine->inverse(); //utilise new
	pXYHe85Machine2XYHg->setTransformId(kXYHe85Machine2XYHg);
	fTransformList.push_back(pXYHe85Machine2XYHg);

	

	// TRefSystemFactory instantiated
	delete NMatrix0;
	delete EtaMatrix0;
	delete XsiMatrix0;
	delete NMatrixTopo;
	delete EtaMatrixTopo;
	delete XsiMatrixTopo;
	delete NMatrixLEP;
	delete EtaMatrixLEP;
	delete XsiMatrixLEP;
}







//////////////////////////////////////////////////////////////////////
// MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////
TRefSystemFactory* TRefSystemFactory::getRefSystemFactory()
{//returns the unique instance : clients access trought this member function
	if (fRefSystemFactory == 0)
	{
		fRefSystemFactory = new TRefSystemFactory();
		fRefSystemFactory->init();
	}

	return fRefSystemFactory;
}


void	TRefSystemFactory::deleteRefSystemFactory()
{
	if(fRefSystemFactory != 0)
	{
		TGraph::deleteGraph();

		if(fTransformList.size() != 0)
		{
			vector<TARefFrameTransformation*>::iterator iter; 
			while(fTransformList.begin() != fTransformList.end())
			{
				iter = fTransformList.begin();
				delete (*iter);
				fTransformList.erase(fTransformList.begin());
			}
		}
			fTransformList.clear();	


		if(fGeoidList.size() != 0)
		{
			vector<TAGeoidModel*>::iterator iter;
			while(fGeoidList.begin() != fGeoidList.end())
			{
				iter = fGeoidList.begin();
				delete (*iter);
				fGeoidList.erase(fGeoidList.begin());
			}
		}
			fGeoidList.clear();	

		if(fRefEllList.size() != 0)
		{
			vector<TReferenceEllipsoid*>::iterator iter;
			while(fRefEllList.begin() != fRefEllList.end())
			{
				iter = fRefEllList.begin();
				delete (*iter);
				fRefEllList.erase(fRefEllList.begin());
			}
		}
			fRefEllList.clear();	

		if(fRefFrameList.size() != 0)
		{
			vector<TAReferenceFrame*>::iterator iter;
			while(fRefFrameList.begin() != fRefFrameList.end())
			{
				iter = fRefFrameList.begin();
				delete (*iter);
				fRefFrameList.erase(fRefFrameList.begin());
			}
		}
			fRefFrameList.clear();	


		if(fLocalRefFrameList.size() != 0)
		{
			vector<TAReferenceFrame*>::iterator iter;
			while(fLocalRefFrameList.begin() != fLocalRefFrameList.end())
			{
				iter = fLocalRefFrameList.begin();
				delete (*iter);
				fLocalRefFrameList.erase(fLocalRefFrameList.begin());
			}
		}
			fLocalRefFrameList.clear();	

		delete fRefSystemFactory;
	}

	

	return;
}



TAGeoidModel*  TRefSystemFactory::getGeoid(const EGeoid geoidId)
{//return a pointer to the geoid asked for

	vector<TAGeoidModel*>::iterator iter = fGeoidList.begin();
	vector<TAGeoidModel*>::iterator iterEnd = fGeoidList.end();

	while (iter != iterEnd)
	{
		if( (*iter)->getGeoidId() == geoidId )
			return *iter;

		iter++;
	}

	cerr << "Id. not in GeoidList";
	exit(EXIT_FAILURE);

	

}


TReferenceEllipsoid* TRefSystemFactory::getEllipsoid(const ERefEll ellId)
{//return a pointer to the ellipsoid asked for
	vector<TReferenceEllipsoid*>::iterator iter, iterEnd;
	iter = fRefEllList.begin();
	iterEnd = fRefEllList.end();

	while (iter != iterEnd)
	{
		if((*iter)->getEllId() == ellId)
			return *iter;

		iter++;
	}


	cerr << "Error : Id. not in RefEllList";
	exit(EXIT_FAILURE);
}


TAReferenceFrame* TRefSystemFactory::getRefFrame(const ERefFrame refFrameId)
{//return a pointer to the ref frame askes for
	vector<TAReferenceFrame*>::iterator iter = fRefFrameList.begin();
	vector<TAReferenceFrame*>::iterator iterEnd = fRefFrameList.end();

	while (iter != iterEnd)
	{
		if((*iter)->getRefFrameId() == refFrameId)
			return *iter;

		iter++;
	}

	cerr << "Error : Id. not in RefFrameList";
	exit(EXIT_FAILURE);
}


TGeodeticRefFrame* TRefSystemFactory::getGeoRefFrame(const ERefFrame refFrameId)
{
	if( refFrameId == kCGRFSphere )
		return fCGRFSphere;
	
	if( refFrameId == kCGRF )
		return fCGRF;

	cerr << "Error : Id. not in RefFrameList";
	exit(EXIT_FAILURE);
}


TARefFrameTransformation* TRefSystemFactory::getTransformation(const ERefFrameTransform id)
{//return a pointer to the ref frame transformation asked for
	vector<TARefFrameTransformation*>::iterator iter = fTransformList.begin();
	vector<TARefFrameTransformation*>::iterator iterEnd = fTransformList.end();

	while (iter != iterEnd)
	{
		if((*iter)->getTransformId() == id)
			return *iter;

		iter++;
	}


	cerr << "Error : Id. not in TransformationList";
	exit(EXIT_FAILURE);
}


bool TRefSystemFactory::isInRFFactory( const TAReferenceFrame* rf ) 
{//test if the reference frame is in the graph or not

	vector<TAReferenceFrame*>::iterator iter = fRefFrameList.begin();
	vector<TAReferenceFrame*>::iterator iterEnd = fRefFrameList.end();

	while (iter != iterEnd)
	{
		if((*iter) == rf)
			return true;

		iter++;
	}

	return false;
}


TAReferenceFrame*	TRefSystemFactory::getNewLocalRefFrame()
{//return a pointer to a new Local ref Frame and put it in a list in order to be deleted
	T3DLocalRefFrame* pLocalRF = new T3DLocalRefFrame("Local Reference Frame");
	fLocalRefFrameList.push_back(pLocalRF);
	return pLocalRF;
}


TAReferenceFrame*	TRefSystemFactory::getNewLocalRefFrame(struct LocalSystemOrigin fLSO, EGeoid geoid)
{
	TModifiedLocalAstronomicalRF* pMLA = 0;

	if(fLSO.origin != 0)
	{
		TSpatialPosition* originPointer = fLSO.origin;
		TSpatialPosition origin (*originPointer);
		TAngle gis = fLSO.gisement;
		TAngle slope = fLSO.slope;

		TFreeVector falseOrigin (0,0,0, TCoordSysFactory::k3DCartesian);

		pMLA = new TModifiedLocalAstronomicalRF("mla", geoid, origin,falseOrigin, gis, slope);
		fLocalRefFrameList.push_back(pMLA);
	}

	return pMLA;
}





//////////////////////////////////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////////////////////////////////




