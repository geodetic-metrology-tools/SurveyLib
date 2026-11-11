// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <cmath>
#include <stdexcept>
#include <string>

#include <tut/tut.hpp>

#include <TAngle.h>
#include <TGeoidHeightRefFrame.h>
#include <TPositionVector.h>
#include <TRefFrameInfo.h>
#include <TSpatialPosition.h>

#include "GeoidTestGrid.h"

namespace tut
{
struct test_CustomGeoidTransformations
{
};
typedef test_group<test_CustomGeoidTransformations> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test Custom Geoid Transformations");

// Test point (near CERN), inside the synthetic grid
const double kLon = 6.05;
const double kLat = 46.25;
const double kH = 500.0; // ellipsoidal height in ETRF93 / GRS80

const double kTolMetres = 1e-6;
const double kTolDegrees = 1e-10;

std::string gridA()
{
	return geoidtestgrid::createGrid("surveylib_test_geoid_A_v1.tif");
}

// Same grid shifted by 10 m
std::string gridB()
{
	return geoidtestgrid::createGrid("surveylib_test_geoid_B_v1.tif", 10.0);
}

TAReferenceFrame *etrf93()
{
	return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93);
}

TAReferenceFrame *withGeoid(int frame, const std::string &grid)
{
	return TRefFrameInfo::getReferenceFrame(frame, nullptr, NO_VALf, "noSolution", grid);
}

TPositionVector geodetic(double lonDeg, double latDeg, double h)
{
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setLambdaEllipsoid(TAngle(lonDeg, TAngle::kDeciDegs));
	pv.setPhiEllipsoid(TAngle(latDeg, TAngle::kDeciDegs));
	pv.setH(TLength(h));
	return pv;
}

TSpatialPosition etrf93Point()
{
	TSpatialPosition position(etrf93());
	position.setCoordinates(geodetic(kLon, kLat, kH));
	return position;
}

// tut::ensure_distance does not fail on NaN (all comparisons are false): check the value is finite first
void ensureClose(const char *msg, double actual, double expected, double tolerance)
{
	tut::ensure(std::string(msg) + ": finite value", std::isfinite(actual));
	tut::ensure_distance(msg, actual, expected, tolerance);
}

double heightOf(const TSpatialPosition &position, TCoordSysFactory::ECoordSys coordSys)
{
	return position.getCoordinates(coordSys).getH().getMetresValue();
}
} // namespace

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("ETRF93 ellipsoidal height to height above the geoid: H = h - N");

	TSpatialPosition position = etrf93Point();
	ensure("transformation succeeded", position.transform(withGeoid(TRefSystemFactory::kETRF93, gridA())));

	const TPositionVector pv = position.getCoordinates(TCoordSysFactory::kGeodetic);
	ensureClose("H = h - N", pv.getH().getMetresValue(), kH - geoidtestgrid::expectedN(kLon, kLat), kTolMetres);
	ensureClose("longitude unchanged", pv.getLambdaEllipsoid().getDeciDegsValue(), kLon, kTolDegrees);
	ensureClose("latitude unchanged", pv.getPhiEllipsoid().getDeciDegsValue(), kLat, kTolDegrees);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("Height above the geoid to ETRF93 ellipsoidal height: h = H + N");

	const double H = 450.0;
	TSpatialPosition position(withGeoid(TRefSystemFactory::kETRF93, gridA()));
	ensure("coordinates accepted", position.setCoordinates(geodetic(kLon, kLat, H)));
	ensure("transformation succeeded", position.transform(etrf93()));

	ensureClose("h = H + N", heightOf(position, TCoordSysFactory::kGeodetic), H + geoidtestgrid::expectedN(kLon, kLat), kTolMetres);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Round trip ETRF93 + geoid -> CCS -> ETRF93 + geoid");

	TAReferenceFrame *frame = withGeoid(TRefSystemFactory::kETRF93, gridA());
	const TPositionVector original = geodetic(kLon, kLat, 450.0);

	TSpatialPosition position(frame);
	position.setCoordinates(original);
	ensure("to CCS", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS)));
	ensure("back to ETRF93 + geoid", position.transform(frame));

	const TPositionVector pv = position.getCoordinates(TCoordSysFactory::kGeodetic);
	ensureClose("H", pv.getH().getMetresValue(), 450.0, kTolMetres);
	ensureClose("longitude", pv.getLambdaEllipsoid().getDeciDegsValue(), kLon, kTolDegrees);
	ensureClose("latitude", pv.getPhiEllipsoid().getDeciDegsValue(), kLat, kTolDegrees);
}

template<>
template<>
void object::test<4>()
{
	set_test_name("Base frame on another ellipsoid (CH1903+ / Bessel): same height above the geoid as ETRF93");

	// The geoid is defined in ETRF93 / GRS80: H must not depend on the ellipsoid of the base frame
	TSpatialPosition inETRF = etrf93Point();
	ensure(inETRF.transform(withGeoid(TRefSystemFactory::kETRF93, gridA())));

	TSpatialPosition inCH = etrf93Point();
	ensure(inCH.transform(withGeoid(TRefSystemFactory::kCH1903plus, gridA())));

	// sanity check: the Bessel ellipsoidal height is really different from the GRS80 one
	TSpatialPosition plainCH = etrf93Point();
	ensure(plainCH.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus)));
	ensure("Bessel and GRS80 heights differ", std::abs(heightOf(plainCH, TCoordSysFactory::kGeodetic) - kH) > 1.0);

	ensureClose("same H in CH1903+ and ETRF93", heightOf(inCH, TCoordSysFactory::kGeodetic), heightOf(inETRF, TCoordSysFactory::kGeodetic), 1e-4);

	// and back to ETRF93
	ensure(inCH.transform(etrf93()));
	ensureClose("h back in ETRF93", heightOf(inCH, TCoordSysFactory::kGeodetic), kH, 1e-4);
}

template<>
template<>
void object::test<5>()
{
	set_test_name("Projection base frame (Lambert93 eh, k2DPlusH)");

	TSpatialPosition plain = etrf93Point();
	ensure(plain.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_eh)));

	TSpatialPosition withN = etrf93Point();
	TAReferenceFrame *frame = withGeoid(TRefSystemFactory::kLambert93_eh, gridA());
	ensure(withN.transform(frame));
	ensure_equals("coordinates in 2D+H", static_cast<TGeoidHeightRefFrame *>(frame)->getHeightCoordSys(), TCoordSysFactory::k2DPlusH);

	const TPositionVector pvPlain = plain.getCoordinates(TCoordSysFactory::k2DPlusH);
	const TPositionVector pvWithN = withN.getCoordinates(TCoordSysFactory::k2DPlusH);
	ensureClose("E unchanged", pvWithN.getX().getMetresValue(), pvPlain.getX().getMetresValue(), kTolMetres);
	ensureClose("N unchanged", pvWithN.getY().getMetresValue(), pvPlain.getY().getMetresValue(), kTolMetres);
	ensureClose("H = h(ETRF93) - N", pvWithN.getH().getMetresValue(), kH - geoidtestgrid::expectedN(kLon, kLat), 1e-4);
}

template<>
template<>
void object::test<6>()
{
	set_test_name("Different geoids on input and output");

	const double HA = 450.0;
	TSpatialPosition position(withGeoid(TRefSystemFactory::kETRF93, gridA()));
	position.setCoordinates(geodetic(kLon, kLat, HA));

	// output frame created after the input one: the input geoid must not be replaced
	ensure(position.transform(withGeoid(TRefSystemFactory::kETRF93, gridB())));

	// h = HA + NA = HB + NB, with NB = NA + 10
	ensureClose("HB = HA - 10", heightOf(position, TCoordSysFactory::kGeodetic), HA - 10.0, kTolMetres);
}

template<>
template<>
void object::test<7>()
{
	set_test_name("Geoid height frames are cached by (frame, geoid file)");

	TAReferenceFrame *a1 = withGeoid(TRefSystemFactory::kETRF93, gridA());
	TAReferenceFrame *a2 = withGeoid(TRefSystemFactory::kETRF93, gridA());
	TAReferenceFrame *b = withGeoid(TRefSystemFactory::kETRF93, gridB());

	ensure("same instance for the same frame and file", a1 == a2);
	ensure("different instance for another file", a1 != b);
	ensure("not in the graph", !a1->isInGraph());
	ensure("name differs from the base frame", a1->getName() != etrf93()->getName());
}

template<>
template<>
void object::test<8>()
{
	set_test_name("Invalid uses of a geoid file");

	// Frame already using a vertical datum
	try
	{
		withGeoid(TRefSystemFactory::kLambert93_ign69, gridA());
		fail("a geoid on Lambert93 IGN69 must be refused");
	}
	catch (const std::invalid_argument &)
	{
	}

	// Missing grid file
	try
	{
		withGeoid(TRefSystemFactory::kETRF93, "this/file/does/not/exist.tif");
		fail("a missing geoid file must be refused");
	}
	catch (const std::invalid_argument &)
	{
	}

	// 3D cartesian coordinates have no meaning with heights above the geoid
	TSpatialPosition position = etrf93Point();
	ensure(position.transform(withGeoid(TRefSystemFactory::kETRF93, gridA())));
	try
	{
		position.getCoordinates(TCoordSysFactory::k3DCartesian);
		fail("3D cartesian coordinates must be refused");
	}
	catch (const std::invalid_argument &)
	{
	}
	ensure_not("3D cartesian coordinates can not be set", position.setCoordinates(TPositionVector(0.0, 0.0, 0.0, TCoordSysFactory::k3DCartesian)));
}

template<>
template<>
void object::test<9>()
{
	set_test_name("Grid file without SRS (ESRI ASCII grid): the SRS is given by the EPSG code");

	const std::string grid = geoidtestgrid::createAsciiGrid("surveylib_test_geoid_ascii_v1.asc");

	TSpatialPosition position = etrf93Point();
	ensure("transformation succeeded", position.transform(withGeoid(TRefSystemFactory::kETRF93, grid)));
	ensureClose("H = h - N", heightOf(position, TCoordSysFactory::kGeodetic), kH - geoidtestgrid::expectedN(kLon, kLat), kTolMetres);
}
} // namespace tut
