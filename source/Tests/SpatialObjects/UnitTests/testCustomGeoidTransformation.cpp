// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <filesystem>

#include <tut/tut.hpp>

#include <TPositionVector.h>
#include <TRefFrameInfo.h>
#include <TSpatialPosition.h>

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
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Transform translation point");
	const double tol = 1e-6;

	// Original unit vector
	TLength xTranslation(2202.2102702479288);
	TLength yTranslation(2710.6388201471618);
	TLength zTranslation(2359.0065601466191);

	TLength xOrig(0.0);
	TLength yOrig(0.0);
	TLength zOrig(0.0);

	TPositionVector pv(xOrig, yOrig, zOrig, TCoordSysFactory::k3DCartesian);

	// Path to folder containing Swiss geoid (ensure trailing backslash)
#ifdef _WIN32
	const std::string path = "C:/Users/bweyer/cernbox/Documents/Geodesy/GeoidGrid/Geoid_OGD_suisse/chgeo2004_ETRS.agr";
#else
	// const std::string path = "/eos/project/g/geodetic-metrology/Geodesy/CAD_Systems/TransformationMatrixCATIA/1101_SURVEY.TRSF";
#endif

	// Create position with CAD-in reference frame (forward matrix)
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS));
	position.setCoordinates(pv);
	bool ok1 = position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95, nullptr, NO_VALf, "noSolution", path));

	ensure_equals("CCS X is equal to translation", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX(), xTranslation, tol);
	ensure_equals("CCS Y is equal to translation", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY(), yTranslation, tol);
	ensure_equals("CCS Z is equal to translation", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ(), zTranslation, tol);
}
} // namespace tut
