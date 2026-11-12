// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <tut/tut.hpp>

#include <GeodeticConstants.h>
#include <SpatialObjCFns.h>
#include <SpatialObjFns.h>
#include <TConstants.h>

namespace tut
{
struct test_DLLMultipleTransformations
{
};
typedef test_group<test_DLLMultipleTransformations> factory;
typedef factory::object object;
} // namespace tut

namespace tut
{
tut::factory tf_surveyLibDLL("Test of SpatialObjDLL");
}
typedef int(DLLAPI *getXiRadianFn)(double, double, double *, const char *);

namespace tut
{
/*! Testing valid options */
template<>
template<>
void object::test<1>()
{
	set_test_name("SpatialObj DLL test");

	double x = 2180.15185;
	double y = 2701.74391;
	double N = 0;

	getCG2000NMachine(x, y, &N);

	tut::ensure_distance(N, 3.199512306355874e-4, 1e-6);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("SpatialObj DLL test");

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	transformToMLA(2180.15185, 2701.74391, 2359.87975, &x, &y, &z, "CG2000");

	// TODO fix this test
	tut::skip("Fix this test: returned values are wrong (see comments in code file).");
	tut::ensure_distance(x, 863.2361121728145, 1e-6); // x = -2180.0877673905798
	tut::ensure_distance(y, -510.2229651021653, 1e-6); // y = -2701.5209778501535
	tut::ensure_distance(z, -0.3143969823113366, 1e-6); // z = -2360.1941469823109
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Test at P0");

	double xi = 0;
	double eta = 0;
	double n = 0;
	std::string geoid = "CG2000_Machine";

	getXiRadian(XP0, YP0, &xi, geoid.c_str());
	getEtaRadian(XP0, YP0, &eta, geoid.c_str());
	getCG2000NMachine(XP0, YP0, &n);
	tut::ensure_equals("Xi P0 is 0", xi, 0.0);
	tut::ensure_equals("Eta P0 is 0", eta, 0.0);

	geoid = "CG2000_Topo";
	getEtaRadian(XP0, YP0, &eta, geoid.c_str());
	tut::ensure_equals("Xi P0 is 0", xi, 0.0);
	tut::ensure_equals("Eta P0 is 0", eta, 0.0);

	geoid = "CG1985_Machine";
	getXiRadian(XP0, YP0, &xi, geoid.c_str());
	getEtaRadian(XP0, YP0, &eta, geoid.c_str());
	getCG1985NMachine(XP0, YP0, &n);
	tut::ensure_equals("Xi P0 is 0", xi, 0.0);
	tut::ensure_equals("Eta P0 is 0", eta, 0.0);

	geoid = "Sphere";
	getXiRadian(XP0, YP0, &xi, geoid.c_str());
	getEtaRadian(XP0, YP0, &eta, geoid.c_str());
	getCGSphereN(XP0, YP0, &n);
	tut::ensure_equals("Xi P0 is 0", xi, 0.0);
	tut::ensure_equals("Eta P0 is 0", eta, 0.0);
}

template<>
template<>
void object::test<4>()
{
	set_test_name("Test N, Eta, Xi at grid nodes (lower left valid corner of the grid). Must be equal to value in the grid");
	double x = -5000.0;
	double y = 0.0;
	double n = 0.0;
	double xi = 0.0;
	double eta = 0.0;

	std::string geoid = "CG2000_Machine";
	getXiRadian(x, y, &xi, geoid.c_str());
	getEtaRadian(x, y, &eta, geoid.c_str());
	getCG2000NMachine(x, y, &n);

	ensure_equals("N p is 0.15771 m ", n, 0.15771);
	ensure_equals("Eta p is 25.24 cc", eta * RAD2GON, 25.24 / 10000); // values in the grid are in cc, but the function returns in gon, so we divide by 10000
	ensure_equals("Xi p is -21.80 cc", xi * RAD2GON, -21.80 / 10000);

	geoid = "CG2000_Topo";
	getXiRadian(x, y, &xi, geoid.c_str());
	getEtaRadian(x, y, &eta, geoid.c_str());
	getCG2000NTopo(x, y, &n);

	ensure_equals("N p is 0.16931 m ", n, 0.16931);
	ensure_equals("Eta p is 31.07 cc", eta * RAD2GON, 31.07 / 10000);
	ensure_equals("Xi p is -27.21 cc", xi * RAD2GON, -27.21 / 10000);
}

template<>
template<>
void object::test<5>()
{
	set_test_name("Test Eta, Xi with wrong geoid name");
	double x = -5000.0;
	double y = 0.0;
	double n = 0.0;
	double xi = 0.0;
	double eta = 0.0;

	std::string geoid = "NotAGoodGeoidName";
	int resultXi = getXiRadian(x, y, &xi, geoid.c_str());
	int resultEta = getEtaRadian(x, y, &eta, geoid.c_str());

	ensure_equals("Xi computation failed", resultXi, 0);
	ensure_equals("Eta computation failed", resultEta, 0);
}

template<>
template<>
void object::test<6>()
{
	set_test_name("Test Eta, Xi with point outside valid range");
	double x = 15000.0;
	double y = 20000.0;
	double n = 0.0;
	double xi = 0.0;
	double eta = 0.0;

	std::string geoid = "CG2000_Machine";
	int resultXi = getXiRadian(x, y, &xi, geoid.c_str());
	int resultEta = getEtaRadian(x, y, &eta, geoid.c_str());

	ensure_equals("Xi computation failed", resultXi, 0);
	ensure_equals("Eta computation failed", resultEta, 0);
}
} // namespace tut
