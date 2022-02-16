#include <TLambert93Transformation.h>
#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_TLambert93Transformation{};
    typedef test_group<test_TLambert93Transformation> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TLambert93Transformation class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
		set_test_name("Transforming a TSpatialPosition from CGRF93v2b (geodetic) into Lambert 93 (ellipsoidal height)");
		TPositionVector pv(0.872664626, 0.145512099, (400.157), TCoordSysFactory::kGeodetic); 


		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		ensure("Transform returns true", 
			position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_eh)));


        //TLambert93Transformation trans(true);
        //ensure("Transform returns true", trans.transform(position));
			
		//Comparison with coordinates computed using IGN Circé software
        ensure_equals("Lambert 93 X", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(1082722.205), static_cast<TReal>(0.001));
		ensure_equals("Lambert 93 Y", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(7001994.409), static_cast<TReal>(0.001));
		ensure_equals("Lambert 93 H (ellipsoidal height)", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue(),static_cast<TReal>(400.157 /*- 1.2233*/), static_cast<TReal>(0.001));
	}

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Test the clone method");
    }

    template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Test the inverse method");
    }

    template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Transforming a TSpatialPosition from Lambert 93 (ellipsoidal height) into RGF93v2b (geodetic)");
        TPositionVector pv(1082722.205, 7001994.409, (400.157), TCoordSysFactory::k2DPlusH); 
		
		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_eh));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		ensure("Transform returns true", 
			position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93)));

		// Comparison with coordinates computed using IGN Circé software
        ensure_equals("ETRF93 PHI", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue(), static_cast<TReal>(0.872664626), static_cast<TReal>(1.6e-10)); //(1 mm ~1.6e-10 rad)
        ensure_equals("ETRF93 LAM", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue(), static_cast<TReal>(0.145512099), static_cast<TReal>(1.6e-10)); //(1 mm ~1.6e-10 rad) 
        ensure_equals("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(400.157), static_cast<TReal>(1e-3));
	}

	template<>
	template<>
	void object::test<5>()
	{
		set_test_name("Transforming a TSpatialPosition from Lambert 93 (altitude NGF-IGN69) into RGF93v2b (geodetic)");
		TPositionVector pv(1082722.205, 7001994.409, (352.697), TCoordSysFactory::k2DPlusH);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_raf));
		ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

		ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93)));

		// Comparison with coordinates computed using IGN Circé software
		ensure_equals("ETRF93 PHI", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue(), static_cast<TReal>(0.872664626),
			static_cast<TReal>(1.6e-10)); //(1 mm ~1.6e-10 rad)
		ensure_equals("ETRF93 LAM", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue(), static_cast<TReal>(0.145512099),
			static_cast<TReal>(1.6e-10)); //(1 mm ~1.6e-10 rad)
		ensure_equals("ETRF93 H (ellipsoidal height)", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(400.157),
			static_cast<TReal>(1e-3));
	}

	template<>
	template<>
	void object::test<6>()
	{
		set_test_name("Transforming a TSpatialPosition from CGRF93v2b (geodetic) into Lambert 93 (Altitude NGF-IGN69 using RAF20 transformation grid)");
		TPositionVector pv(0.872664626, 0.145512099, (400.157), TCoordSysFactory::kGeodetic);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93));
		ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

		ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93_raf)));

		// Comparison with coordinates computed using IGN Circé software
		ensure_equals("Lambert 93 X", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(1082722.205), static_cast<TReal>(0.001));
		ensure_equals("Lambert 93 Y", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(7001994.409), static_cast<TReal>(0.001));
		ensure_equals("Lambert 93 H (altitude NGF-IGN69)", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue(),static_cast<TReal>(352.697), static_cast<TReal>(0.001));
	}

}
