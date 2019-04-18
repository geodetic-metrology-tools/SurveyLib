#include <TAngle.h>
#include <TLocalSystemOrigin.h>
#include <TRefSystemFactory.h>

#include <tut/tut.hpp>

namespace tut
{
    struct test_LocalSystems{};
    typedef test_group<test_LocalSystems> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test Local Systems");
}

namespace tut
{
	static bool test1_ok = false;
	static const TCoordSysFactory::ECoordSys k3D = TCoordSysFactory::k3DCartesian;
	// The following points should be the result of the transformations to the local systems
	struct PTheo {
		TSpatialPosition *data[4];
		PTheo(TAReferenceFrame* rf) {
			data[0] = new TSpatialPosition(rf,   0,   0,   0,  k3D);  
			data[1] = new TSpatialPosition(rf, 100,   0,   0,  k3D);  
			data[2] = new TSpatialPosition(rf,   0, 100,   0,  k3D);  
			data[3] = new TSpatialPosition(rf,   0,   0, 100,  k3D);  
		}
		~PTheo() {
			for (int i = 0; i < 4; i++)
				delete data[i];
		}
	};

	/*
	Base point for advanced tests: 
	
	in LAp0:
	2000, 2000, 100
	in CGRF:
	4393822.13218031	467629.008429449	4584913.91387969
	in CGRFsphere:
	4381234.06780204	466295.038416085	4602586.89768278

	Idea:	Construct a local system by building a normal (Z') to the 
			ellipsoid/geoid using the existing classes by adding height
			in the geodetic view.
			Calculate the vector from the base point to a point on the Z-axis
			near the north pole (N').
			The result of N' x Z' is the local X axis (X')
			Z' x X' finally defines the local Y axis (Y')

			These vectors in the GRF allow the computation of the 0..100 points
			in the GRF, so after transforming them to the local system, the theoretical
			coordinates 0..100 are expectes as the result

			In the case of astronomical systems, the deflections at the base point
			are read from the geoid model. The normal vector on the base point
			is corrected by the deflection values, the following setup of the
			coordinate axes is done in the same way as in the geodetic case
	*/

	// 
	void createUnitAxes100(const TSpatialPosition& base, 
						   TPositionVector& x100, TPositionVector& y100, TPositionVector& z100,
						   bool isSpherical)
	{
		TPositionVector basev = (isSpherical)?
								base.getCoordinates(TCoordSysFactory::kGeodeticSphere):
								base.getCoordinates(TCoordSysFactory::kGeodetic);


		// TODO: vertical deflections


		z100 = basev;
		z100.setH(basev.getH()+TLength(100));
		TFreeVector ez = (z100 - basev);
		ez.normalize();

		TPositionVector pN(0, 0, 6137000, basev.getCoordSys()); // Approx. north pole
		TFreeVector pBN = pN - basev; // Free vector from base point to north
		pBN.normalize();
		TFreeVector ex = pBN.cross(ez);
		x100 = basev + (ex*100); //Point on X-axis: base+ v perpendicular  on north-normal-plane

		y100 = basev + ez.cross(ex)*100;
	}

	/*
	Origin and points on axis at 100 m of LGp0 in CCS:
	p0	2000	2097.79265	2433.66
	p1	2082.90299989079	2153.71306317001	2433.66000000011
	p2	1944.07958682994	2180.69564989063	2433.65999999999
	p3	2000.00000000005	2097.79264999995	2533.65999999994

	Transform to an LG with origin p0 (4395400.36378173, 465785.056735627, 4583458.22601372) should lead to the points

	p0	  0,   0,   0
	p1	100,   0,   0
	p2	  0, 100,   0
	p3	  0,   0, 100
	*/
	template<>
    template<>
    void object::test<1>()
    {
		set_test_name("Local Geodetic System: LG");
		// TODO make this test work
		tut::skip("Fix this test: it doesn't work because of the cross between 2 non carthesian vectors.");
		
		TAReferenceFrame *CCS(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
		TAReferenceFrame *GRF(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		
		// test points in CCS
		TSpatialPosition p_trafo[4] = {
			TSpatialPosition(CCS,  2000,	2097.79265,	2433.66, k3D),
			TSpatialPosition(CCS,  2082.90299989079,	2153.71306317001,	2433.66000000011, k3D),
			TSpatialPosition(CCS,  1944.07958682994,	2180.69564989063,	2433.65999999999, k3D),
			TSpatialPosition(CCS,  2000.00000000005,	2097.79264999995,	2533.65999999994, k3D)
		};

		// Construct an LG which is equal to LGp0
		TLocalSystemOrigin lso(p_trafo[0], TAngle(0), TAngle(0), "LSO pt NORTH");
		TAReferenceFrame *LG(TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kLGGRS80));
		PTheo p_theo(LG);
		
		for (int i = 0; i < 4; i++) 
			p_trafo[i].transform(LG);

		for (int i = 0; i < 4; i++) {
			TReal d = p_theo.data[i]->getCoordinates(k3D).dist(p_trafo[i].getCoordinates(k3D)).getMetresValue() ;
			ensure_distance("Testing distance between expected and calculated points", TReal(0), d, TReal(1e-5));
		}

		// Test the north orientation by moving p_trafo[2] north by 1 deg of latitude
		// the X coordinate in the cartesian view must be the same afterwards
		TPositionVector pnorthv = p_trafo[2].getCoordinates(TCoordSysFactory::kGeodetic);
		pnorthv.setPhiEllipsoid(pnorthv.getPhiEllipsoid()+TAngle(GON2RAD));
		TSpatialPosition pnorth(p_trafo[2]);
		pnorth.setCoordinates(pnorthv);

		{
			TReal d = pnorth.getCoordinates(k3D).getX().getMetresValue() - p_theo.data[2]->getCoordinates(k3D).getX().getMetresValue();
			ensure_distance("Difference in X must be 0 after moving north", TReal(0), d, TReal(1e-5));
		}

		
		// CCRF test points constructed from base point
		TSpatialPosition p_trafo2base(GRF, 4393822.13218031, 467629.008429449, 4584913.91387969, k3D);
		TPositionVector p_trafo2[3] = { TPositionVector(k3D), TPositionVector(k3D), TPositionVector(k3D)};
		createUnitAxes100(p_trafo2base, p_trafo2[0],  p_trafo2[1],  p_trafo2[2], false);
		
		TLocalSystemOrigin lso2(p_trafo2base, TAngle(0), TAngle(0), "LSO NOT p0 pt NORTH");
		LG = TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso2, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kLGGRS80);
		
		TSpatialPosition p_trafo3[4] = {
			p_trafo2base, TSpatialPosition(GRF), TSpatialPosition(GRF), TSpatialPosition(GRF)
		};

		for (int i = 0; i < 4; i++) { 
			if (i > 0) p_trafo3[i].setCoordinates(p_trafo2[i-1]);
			p_trafo3[i].transform(LG);
			TReal d = p_theo.data[i]->getCoordinates(k3D).dist(p_trafo3[i].getCoordinates(k3D)).getMetresValue() ;
			ensure_distance("Testing distance between expected and calculated points", TReal(0), d, TReal(1e-5));
		}

		test1_ok = true;
    }


	/*
		Test the modified system: The 0..100 Coordinates of test 1 are rotated by 18 Gons around Z

		p0	0	0	0
		p1	96.0293685676943	-27.8991106039229	0
		p2	27.8991106039229	96.0293685676943	0
		p3	0	0	100


		Transform to CCS

		p0	2000	2097.79265	2433.66
		p1	2095.21252523922	2128.36347003428	2433.65999999983
		p2	1969.42917996571	2193.00517523939	2433.65999999952
		p3	2000.00000000005	2097.79264999995	2533.65999999994


		Transforming the CCS points to an MLG with the origin an P0 and a gisement
		of 18 Gons must lead to the points

		p0	  0,   0,   0
		p1	100,   0,   0
		p2	  0, 100,   0
		p3	  0,   0, 100

	*/
	
	template<>
    template<>
    void object::test<2>()
    {	
		set_test_name("Modified Local Geodetic System: MLG");
		
		TAReferenceFrame *CCS(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
		TAReferenceFrame *GRF(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		
		// test points in CCS
		TSpatialPosition p_trafo[4] = {
			TSpatialPosition(CCS, 2000,	2097.79265,	2433.66 ,  k3D),
			TSpatialPosition(CCS, 2095.21252523922,	2128.36347003428,	2433.65999999983 ,  k3D),
			TSpatialPosition(CCS, 1969.42917996571,	2193.00517523939,	2433.65999999952 ,  k3D),
			TSpatialPosition(CCS, 2000.00000000005,	2097.79264999995,	2533.65999999994 ,  k3D)
		};

		// Construct an LG whith its origin at p0 and a rotation of 18 gons around Z
		TLocalSystemOrigin lso(p_trafo[0], TAngle((18.0-37.77864)*GON2RAD),TAngle(0), "LSO GISEMENT 18");
		TAReferenceFrame *MLG(TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kMLGGRS80));
		PTheo p_theo(MLG);
		
		for (int i = 0; i < 4; i++)
			p_trafo[i].transform(MLG);

		for (int i = 0; i < 4; i++) {
			TReal d = p_theo.data[i]->getCoordinates(k3D).dist(p_trafo[i].getCoordinates(k3D)).getMetresValue() ;
			ensure_distance("Testing distance between expected and calculated points (at p0)", TReal(0), d, TReal(1e-5));
		}

		if (test1_ok) {
			// transform the manually rotated points from a north-LG to CGRF and test if they become the 0..100 points in the MLG
			TSpatialPosition p_trafo2base(GRF, 4393822.13218031, 467629.008429449, 4584913.91387969, k3D);
			TLocalSystemOrigin lso2(p_trafo2base, TAngle(0), TAngle(0), "LSO NOT p0 pt NORTH");
			TAReferenceFrame *LG = TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso2, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kLGGRS80);

			// build a rotated system at the same point
			TLocalSystemOrigin lso3(p_trafo2base, TAngle((18-37.77864)*GON2RAD),TAngle(0), "LSO GISEMENT 18 P1000");
			TAReferenceFrame *MLG2(TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso3, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kMLGGRS80));

			TSpatialPosition unrotated[4] = {
				TSpatialPosition(LG, 0,0,0, k3D),
				TSpatialPosition(LG, 96.0293685676943,	-27.8991106039229,	0, k3D),
				TSpatialPosition(LG, 27.8991106039229,	 96.0293685676943,	0, k3D),
				TSpatialPosition(LG, 0,0,100, k3D)
			};

			
			for (int i = 0; i < 4; i++) {
				unrotated[i].transform(MLG2);
				TReal d = p_theo.data[i]->getCoordinates(k3D).dist(unrotated[i].getCoordinates(k3D)).getMetresValue() ;
				ensure_distance("Testing distance between expected and calculated points (manual system)", TReal(0), d, TReal(1e-1));
			}

		}
	}

	

	// Simple test of spherical LG: Must be the same as LG at P0
	template<>
    template<>
    void object::test<3>()
    {	
		set_test_name("Local Geodetic Spherical System: LGs (Simple test == LG at P0)");
		
		TAReferenceFrame *CCS(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
		
		// test points in CCS
		TSpatialPosition p_trafo[4] = {
			TSpatialPosition(CCS,  2000,	2097.79265,	2433.66, k3D),
			TSpatialPosition(CCS,  2082.90299989079,	2153.71306317001,	2433.66000000011, k3D),
			TSpatialPosition(CCS,  1944.07958682994,	2180.69564989063,	2433.65999999999, k3D),
			TSpatialPosition(CCS,  2000.00000000005,	2097.79264999995,	2533.65999999994, k3D)
		};

		// Construct an LGs which is equal to LGp0
		TLocalSystemOrigin lso(p_trafo[0], TAngle(0), TAngle(0), "LSO pt NORTH");
		TAReferenceFrame *LGs(TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kLGSphere));
		PTheo p_theo(LGs);

		for (int i = 0; i < 4; i++)
			p_trafo[i].transform(LGs);

		for (int i = 0; i < 4; i++) {
			TReal d = p_theo.data[i]->getCoordinates(k3D).dist(p_trafo[i].getCoordinates(k3D)).getMetresValue() ;
			ensure_distance("Testing distance between expected and calculated points", TReal(0), d, TReal(1e-5));
		}

		// Test the north orientation by moving p_trafo[2] north by 1 deg of latitude
		// the X coordinate in the cartesian view must be the same afterwards
		TPositionVector pnorthv = p_trafo[2].getCoordinates(TCoordSysFactory::kGeodetic);
		pnorthv.setPhiEllipsoid(pnorthv.getPhiEllipsoid()+TAngle(GON2RAD));
		TSpatialPosition pnorth(p_trafo[2]);
		pnorth.setCoordinates(pnorthv);

		TReal d = pnorth.getCoordinates(k3D).getX().getMetresValue()-
			      p_theo.data[2]->getCoordinates(k3D).getX().getMetresValue();
		ensure_distance("Difference in X must be 0 after moving north", TReal(0), d, TReal(1e-5));
	}

		
	// Simple test of spherical MLG: Must be the same as MLG test at P0
	template<>
    template<>
    void object::test<4>()
    {	
		set_test_name("Modified Local Geodetic Spherical System: MLGs (Simple test == LG at P0)");
		
		TAReferenceFrame *CCS(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
		TAReferenceFrame *GRF(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCGRF));
		
		// test points in CCS
		TSpatialPosition p_trafo[4] = {
			TSpatialPosition(CCS, 2000,	2097.79265,	2433.66 ,  k3D),
			TSpatialPosition(CCS, 2095.21252523922,	2128.36347003428,	2433.65999999983 ,  k3D),
			TSpatialPosition(CCS, 1969.42917996571,	2193.00517523939,	2433.65999999952 ,  k3D),
			TSpatialPosition(CCS, 2000.00000000005,	2097.79264999995,	2533.65999999994 ,  k3D)
		};

		// Construct an LGs whith its origin at p0 and a rotation of 18 gons around Z
		TLocalSystemOrigin lso(p_trafo[0], TAngle((18.0-37.77864)*GON2RAD),TAngle(0), "LSO GISEMENT 18");
		TAReferenceFrame *MLGs(TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kMLGSphere));
		PTheo p_theo(MLGs);
		
		for (int i = 0; i < 4; i++)
			p_trafo[i].transform(MLGs);

		for (int i = 0; i < 4; i++) {
			TReal d = p_theo.data[i]->getCoordinates(k3D).dist(p_trafo[i].getCoordinates(k3D)).getMetresValue() ;
			ensure_distance("Testing distance between expected and calculated points (at p0)", TReal(0), d, TReal(1e-5));
		}

		if (test1_ok) {
			// transform the manually rotated points from a north-LG to CGRF and test if they become the 0..100 points in the MLG
			TSpatialPosition p_trafo2base(GRF, 4393822.13218031, 467629.008429449, 4584913.91387969, k3D);
			TLocalSystemOrigin lso2(p_trafo2base, TAngle(0), TAngle(0), "LSO NOT p0 pt NORTH");
			TAReferenceFrame *LG = TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso2, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kLGGRS80);

			// build a rotated system at the same point
			TLocalSystemOrigin lso3(p_trafo2base, TAngle((18-37.77864)*GON2RAD),TAngle(0), "LSO GISEMENT 18 P1000");
			TAReferenceFrame *MLG2(TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(lso3, TRefSystemFactory::kNoGeoid, TRefSystemFactory::kMLGGRS80));

			TSpatialPosition unrotated[4] = {
				TSpatialPosition(LG, 0,0,0, k3D),
				TSpatialPosition(LG, 96.0293685676943,	-27.8991106039229,	0, k3D),
				TSpatialPosition(LG, 27.8991106039229,	 96.0293685676943,	0, k3D),
				TSpatialPosition(LG, 0,0,100, k3D)
			};

			
			for (int i = 0; i < 4; i++) {
				unrotated[i].transform(MLG2);
				TReal d = p_theo.data[i]->getCoordinates(k3D).dist(unrotated[i].getCoordinates(k3D)).getMetresValue() ;
				ensure_distance("Testing distance between expected and calculated points (manual system)", TReal(0), d, TReal(1e-1));
			}

		}
		
	}
}
