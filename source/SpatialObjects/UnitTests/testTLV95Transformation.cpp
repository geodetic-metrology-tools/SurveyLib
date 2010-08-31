#include <TLV95Transformation.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_TLV95Transformation{};
    typedef test_group<test_TLV95Transformation> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TLV95Transformation class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95");
        TPositionVector position(4272473.562, 575353.239, 4684498.293, TCoordSysFactory::k3DCartesian);
        TLV95Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_distance("LV95 X", position.getX().getMetresValue(), static_cast<real>(1268507.870), static_cast<real>(0.001));
		ensure_distance("LV95 Y", position.getY().getMetresValue(), static_cast<real>(2617306.920), static_cast<real>(0.001));
		ensure_distance("LV95 H", position.getH().getMetresValue(), static_cast<real>(457.138 - 1.2233), static_cast<real>(0.001));
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
        set_test_name("Transforming a TSpatialPosition from LV95 into CH1903+");
        TPositionVector position(1268507.870, 2617306.920, (457.138 - 1.2233), TCoordSysFactory::k2DPlusH);
        
        TLV95Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("CH1903+ Phi (Deg)", position.getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("CH1903+ Phi (Min)", position.getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("CH1903+ Phi (Sec)", position.getPhiEllipsoid().getSecondsValue(), static_cast<real>(6.404965), static_cast<real>(1e-4));

        ensure_equals("CH1903+ Lam (Deg)", position.getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("CH1903+ Lam (Min)", position.getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("CH1903+ Lam (Sec)", position.getLambdaEllipsoid().getSecondsValue(), static_cast<real>(10.574820), static_cast<real>(1e-4)); 

        ensure_distance("CH1903+ H", position.getH().getMetresValue(), static_cast<real>(457.138), static_cast<real>(1e-3));
	}

    template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Transformation has the right source and destination frames");
        ensure_equals("TLV95Transformation(true).getSourceFrame() -> CH1903+", 
            TLV95Transformation(true).getSourceFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
        ensure_equals("TLV95Transformation(true).getDestinationFrame() -> LV95", 
            TLV95Transformation(true).getDestinationFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95));
        ensure_equals("TLV95Transformation(false).getSourceFrame() -> LV95", 
            TLV95Transformation(false).getSourceFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95));
        ensure_equals("TLV95Transformation(false).getDestinationFrame() -> CH1903+", 
            TLV95Transformation(false).getDestinationFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
    }

}
