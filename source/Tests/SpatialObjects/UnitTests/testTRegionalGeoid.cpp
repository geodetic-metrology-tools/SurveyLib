// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <tut/tut.hpp>
#include <TRegionalGeoid.h>
#include <TRefFrameInfo.h>

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
	set_test_name("Test with australian geoid");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\AUSGeoid2020_20180201.gsb");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *AUSGeoid2020 = new TRegionalGeoid("AUSGeoid2020", TRefSystemFactory::EGeoid::kCUSTOMgeoid, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia 325.02592363760 (34.97407636240S)    138.70887100110E    727.2197 ellipsoidalHeight
	// comparison with results given by the online tool https://geodesyapps.ga.gov.au/ausgeoid2020
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
}

}


