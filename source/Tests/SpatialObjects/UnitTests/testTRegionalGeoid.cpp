// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <tut/tut.hpp>
#include <tut/tut_macros.hpp>

#include <TRegionalGeoid.h>
#include <TRefFrameInfo.h>
#include <ConsoleLogHandler.hpp>

namespace tut
{
struct test_TRegionalGeoid
{
};
typedef test_group<test_TRegionalGeoid> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test TRegionalGeoid class");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Test opening grid file");
	const double tolHeight = 1e-3;
	std::string pathToFile(std::string(SPATIALOBJECTS_TEST_FILES_DIR) + "/noGeoidGridHere.tif");

	// Initialize geoid model with a non existing grid file. This should throw an exception
	TAReferenceFrame *ETRF93(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kETRF93));
	ensure_THROW(TRegionalGeoid("ghostGeoid", TRefSystemFactory::EGeoid::kCUSTOMgeoid, ETRF93,
					 TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), ETRF93, pathToFile),
		std::invalid_argument);

	pathToFile = std::string(SPATIALOBJECTS_TEST_FILES_DIR) + "/chgeo2004_ETRS_crop_fcc.tif";
	TRegionalGeoid *CHgeoid = new TRegionalGeoid("ghostGeoid", TRefSystemFactory::EGeoid::kCUSTOMgeoid, ETRF93,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), ETRF93, pathToFile);
	ensure_THROW(CHgeoid->setPathToFile("noGeoidGridHere.tif"), std::invalid_argument);

	ensure_NO_THROW(CHgeoid->setPathToFile(pathToFile));

}

template<>
template<>
void object::test<2>()
{
	set_test_name("Test with swiss geoid and compare wiht Reframe");
	const double tolHeight = 1e-3;
	std::string pathToFile(std::string(SPATIALOBJECTS_TEST_FILES_DIR) + "/chgeo2004_ETRS_crop_fcc.tif");

	TAReferenceFrame *CHTRF95(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCHTRF95));
	TRegionalGeoid *CHgeoid = new TRegionalGeoid("CHGeo2004", TRefSystemFactory::EGeoid::kCUSTOMgeoid, CHTRF95,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), CHTRF95, pathToFile, 4933, GRIORA_Bilinear);

	// Coordinate of P0
	TAngle lambda(6.0486633109, TAngle::kDeciDegs);
	TAngle phi(46.2321561210, TAngle::kDeciDegs);
	TLength h(483.62404);
	TLength nReframe(483.62404 - 433.67048); // Geoid height given by Swisstopo Reframe (ellipsoidal height - orthometric height)
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95));
	position.setCoordinates(pv);

	ensure_equals("N", CHgeoid->getN(position).getMetresValue(), nReframe, tolHeight);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Test with australian geoid ");
	double tolHeight = 1e-3;
	std::string pathToFile(std::string(SPATIALOBJECTS_TEST_FILES_DIR) + "/AUSGeoid2020_20180201_extract.tif");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *AUSGeoid2020 = new TRegionalGeoid("AUSGeoid2020", TRefSystemFactory::EGeoid::kCUSTOMgeoid, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia 325.02592363760 (34.97407636240S)    138.70887100110E    727.2197 ellipsoidalHeight
	// Comparison with results given by the online tool https://geodesyapps.ga.gov.au/ausgeoid2020
	TAngle lambda(138.70887100110, TAngle::kDeciDegs);
	TAngle phi(325.02592363760, TAngle::kDeciDegs);
	TLength h(727.2197);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
	position.setCoordinates(pv);

	ensure_equals("N", AUSGeoid2020->getN(position).getMetresValue(), 0.419, tolHeight);

	
	// Coordinate of a point in Australia S35 00  0.000 E138 00  0.000 h200
	// Comparison with results given by the online tool https://geodesyapps.ga.gov.au/ausgeoid2020
	lambda.setDMSValue(138, 0, 0.000);
	phi.setDMSValue(-35, 0, 0.000);
	h.setMetresValue(200);
	
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);
	position.setCoordinates(pv);
	ensure_equals("N", AUSGeoid2020->getN(position).getMetresValue(), -1.353, tolHeight);
}

template<>
template<>
void object::test<4>()
{
	set_test_name("Test with American Geoid18");
	const double tolHeight = 1e-3;
	std::string pathToFile(std::string(SPATIALOBJECTS_TEST_FILES_DIR) + "/g2018u0_extract.bin");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *GEOID18 = new TRegionalGeoid("GEOID18", TRefSystemFactory::EGeoid::kCUSTOMgeoid, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in the US 35.9320N     97.2W    250.00000 ellipsoidal Height
	// comparison with results given by the online tool https://geodesy.noaa.gov/GEOID/GEOID18/computation.html
	TAngle lambda(-97.2, TAngle::kDeciDegs);
	TAngle phi(35.932, TAngle::kDeciDegs);
	TLength h(250.00000);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
	position.setCoordinates(pv);

	ensure_equals("N", GEOID18->getN(position).getMetresValue(), -27.929, tolHeight);

}

template<>
template<>
void object::test<5>()
{
	set_test_name("Test with swiss geoid with input coordinates in a different reference frame");
	const double tolHeight = 1e-3;
	std::string pathToFile(std::string(SPATIALOBJECTS_TEST_FILES_DIR) + "/chgeo2004_ETRS_crop_fcc.tif");

	TAReferenceFrame *CHTRF95(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCHTRF95));
	TRegionalGeoid *CHgeoid = new TRegionalGeoid("CHGeo2004", TRefSystemFactory::EGeoid::kCUSTOMgeoid, CHTRF95,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), CHTRF95, pathToFile, 4933, GRIORA_Bilinear);

	// Coordinate of P0 
	TAngle lambda(6.049116, TAngle::kDeciDegs);
	TAngle phi(46.23228, TAngle::kDeciDegs);
	TLength h(433.65921);
	TLength nReframe(483.62404 - 433.67048); // Geoid height given by Swisstopo Reframe (ellipsoidal height - orthometric height)
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRF));
	position.setCoordinates(pv);

	ConsoleLogHandler *logger = new ConsoleLogHandler();
	
	ensure_equals("N", CHgeoid->getN(position).getMetresValue(), nReframe, tolHeight);

}

}


