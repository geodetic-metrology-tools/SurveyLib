#include <TRGF93CC46Transformation.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_TRGF93CC46Transformation{};
    typedef test_group<test_TRGF93CC46Transformation> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TRGF93CC46Transformation class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
		// Comparison with coordinates computed using Circe software developped by IGN
        set_test_name("Transforming a TSpatialPosition from RGF93 into RGF93 CC46 (ellipsoidal height)");
        TPositionVector position(4407040.76287, 449723.28541, 4573892.46194, TCoordSysFactory::k3DCartesian);
        TRGF93ZoneTransformation trans(true, true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("RGF93 CC46 X", position.getX().getMetresValue(), static_cast<TReal>(1918471.0676), static_cast<TReal>(0.0001));
		ensure_equals("RGF93 CC46 Y", position.getY().getMetresValue(), static_cast<TReal>(5215917.6067), static_cast<TReal>(0.0001));
		ensure_equals("RGF93 CC46 H (ellipsoidal height)", position.getH().getMetresValue(), static_cast<TReal>(400.157 /*- 1.2233*/), static_cast<TReal>(0.001));
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
		// Comparison with coordinates computed using Circe software developped by IGN
        set_test_name("Transforming a TSpatialPosition from RGF93 CC46 (ellipsoidal height) into RGF93v2b");
        TPositionVector position(1918471.0676, 5215917.6066, (400.157), TCoordSysFactory::k2DPlusH); 

        TRGF93ZoneTransformation trans(false, true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("RGF93 X", position.getX().getMetresValue(), static_cast<TReal>(4407040.76287), static_cast<TReal>(1e-4));
        ensure_equals("RGF93 Y", position.getY().getMetresValue(), static_cast<TReal>(449723.28541), static_cast<TReal>(1e-4)); 
        ensure_equals("RGF93 Z", position.getZ().getMetresValue(), static_cast<TReal>(4573892.46194), static_cast<TReal>(1e-3));
	}

	template<>
	template<>
	void object::test<5>()
	{
		// Comparison with coordinates computed using Circe software developped by IGN
		set_test_name("Transforming a TSpatialPosition from RGF93 into RGF93 CC46 (Altitude NGF-IGN69 using RAF20 transformation grid)");
		TPositionVector position(4407040.76287, 449723.28541, 4573892.46194, TCoordSysFactory::k3DCartesian);
		TRGF93ZoneTransformation trans(true, false);
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("RGF93 CC46 X", position.getX().getMetresValue(), static_cast<TReal>(1918471.0676), static_cast<TReal>(0.0001));
		ensure_equals("RGF93 CC46 Y", position.getY().getMetresValue(), static_cast<TReal>(5215917.6067), static_cast<TReal>(0.0001));
		ensure_equals("RGF93 CC46 H (altitude NGF-IGN69)", position.getH().getMetresValue(), static_cast<TReal>(350.604), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<6>()
	{
		// Comparison with coordinates computed using Circe software developped by IGN
		set_test_name("Transforming a TSpatialPosition from RGF93 CC46 (altitude NGF-IGN69) into RGF93v2b");
		TPositionVector position(1918471.0676, 5215917.6067, (350.604), TCoordSysFactory::k2DPlusH);
		//TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF932Lambert93raf
		//
		TRGF93ZoneTransformation trans(false, false);
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("RGF93 X", position.getX().getMetresValue(), static_cast<TReal>(4407040.76287), static_cast<TReal>(0.0001));
		ensure_equals("RGF93 Y", position.getY().getMetresValue(), static_cast<TReal>(449723.28541), static_cast<TReal>(0.0001));
		ensure_equals("RGF93 Z", position.getZ().getMetresValue(), static_cast<TReal>(4573892.46194), static_cast<TReal>(0.0001));
	}
}
