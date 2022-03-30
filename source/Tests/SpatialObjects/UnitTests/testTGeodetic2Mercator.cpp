#include <TGeodetic2Mercator.h>
#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>

namespace tut
{
struct test_TGeodetic2Mercator
{
};
typedef test_group<test_TGeodetic2Mercator> factory;
typedef factory::object object;
}

namespace
{
tut::factory tf("Test TGeodetic2Mercator class");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Transforming a TSpatialPosition from CGRF (geodetic) into CGRF (Local Transverse Mercator projection)");
	TReal lam_rad = 6.074649334 * PI / 180.0;
	TReal phi_rad = 46.293933869 * PI / 180.0;
	TPositionVector pv(phi_rad, lam_rad, (0.000), TCoordSysFactory::kGeodetic);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRF));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRFMercator_eh)));

	// Comparison with coordinates computed using PROJ pipeline
	// 6.074649334 46.293933869 | proj +proj=tmerc +lat_0=0 +lon_0=6.14 +k_0=1.00006 +x_0=0 +y_0=0 +ellps=GRS80 +units=m -d 3

	ensure_equals("Transverse Mercator East", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(-5035.708), static_cast<TReal>(0.001));
	ensure_equals("Transverse Mercator North", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(5129067.709), static_cast<TReal>(0.001));
	ensure_equals("Transverse Mercator H (ellipsoidal height)", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue(), static_cast<TReal>(0.000), static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<2>()
{
	set_test_name("Transforming a TSpatialPosition from CGRF (Local Transverse Mercator projection) into CGRF (geodetic)");
	TPositionVector pv(-5035.708, 5129067.709, (0.000), TCoordSysFactory::k2DPlusH);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRFMercator_eh));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCGRF)));

	// Comparison with coordinates computed using PROJ pipeline
	// -5035.708 5129067.709 | invproj +proj=tmerc +lat_0=0 +lon_0=6.14 +k_0=1.00006 +x_0=0 +y_0=0 +ellps=GRS80 +units=m -d 9

	ensure_equals("CGRF Lambda", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue(), static_cast<TReal>(6.074649330 * PI / 180.0), static_cast<TReal>(1.6e-10)); //(1 mm ~1.6e-10 rad)
	ensure_equals("CGRF Phi", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue(), static_cast<TReal>(46.293933871 * PI / 180.0), static_cast<TReal>(1.6e-10)); //(1 mm ~1.6e-10 rad)
	ensure_equals("CGRF H (ellipsoidal height)", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(0.000), static_cast<TReal>(0.001));

}

} // namespace tut
