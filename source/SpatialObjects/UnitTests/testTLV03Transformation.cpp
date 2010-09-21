#include <TLV03Transformation.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_TLV03Transformation{};
    typedef test_group<test_TLV03Transformation> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TLV03Transformation class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        TPositionVector position(2617306.920, 1268507.870, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_distance("LV03 X", position.getX().getMetresValue(), static_cast<real>(617306.300), static_cast<real>(0.001));
		ensure_distance("LV03 Y", position.getY().getMetresValue(), static_cast<real>(268507.300), static_cast<real>(0.001));
		ensure_distance("LV03 H", position.getH().getMetresValue(), static_cast<real>(0.0), static_cast<real>(0.001));
    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(617306.300, 268507.300, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_distance("LV03 X", position.getX().getMetresValue(), static_cast<real>(2617306.920), static_cast<real>(0.001));
		ensure_distance("LV03 Y", position.getY().getMetresValue(), static_cast<real>(1268507.870), static_cast<real>(0.001));
		ensure_distance("LV03 H", position.getH().getMetresValue(), static_cast<real>(0.0), static_cast<real>(0.001));
    }

}
