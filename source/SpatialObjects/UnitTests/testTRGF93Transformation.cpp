#include <TRGF93ZoneTransformation.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_TRGF93ZoneTransformation{};
    typedef test_group<test_TRGF93ZoneTransformation> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TRGF93ZoneTransformation class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Transforming a TSpatialPosition from ETRF93 into RGF93 CC46");
        TPositionVector position(4407040.76287, 449723.28541, 4573892.46194, TCoordSysFactory::k3DCartesian);
        TRGF93ZoneTransformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_distance("RGF93 CC46 X", position.getX().getMetresValue(), static_cast<TReal>(1918471.0676), static_cast<TReal>(0.0001));
		ensure_distance("RGF93 CC46 Y", position.getY().getMetresValue(), static_cast<TReal>(5215917.6067), static_cast<TReal>(0.0001));
		ensure_distance("RGF93 CC46 H", position.getH().getMetresValue(), static_cast<TReal>(400.157 /*- 1.2233*/), static_cast<TReal>(0.001));
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
        set_test_name("Transforming a TSpatialPosition from RGF93 CC46 into ETRF93");
        TPositionVector position(1918471.0676, 5215917.6066, (400.157), TCoordSysFactory::k2DPlusH); 

        TRGF93ZoneTransformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("RGF93 CC46 Phi (Deg)", position.getPhiEllipsoid().getDegreesValue(), 46);
        ensure_equals("RGF93 CC46 Phi (Min)", position.getPhiEllipsoid().getMinutesValue(), 6);
        ensure_distance("RGF93 CC46 Phi (Sec)", position.getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(30.0003), static_cast<TReal>(1e-4));

        ensure_equals("RGF93 CC46 Lam (Deg)", position.getLambdaEllipsoid().getDegreesValue(), 5);
        ensure_equals("RGF93 CC46 Lam (Min)", position.getLambdaEllipsoid().getMinutesValue(), 49);
        ensure_distance("RGF93 CC46 Lam (Sec)", position.getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(36.0008), static_cast<TReal>(1e-4)); 

        ensure_distance("RGF93 CC46 H", position.getH().getMetresValue(), static_cast<TReal>(400.157), static_cast<TReal>(1e-3));
	}
}
