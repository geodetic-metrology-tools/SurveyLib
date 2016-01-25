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

        TPositionVector position(1268507.870, 2617306.920, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV03 X", position.getX().getMetresValue(), static_cast<TReal>(268507.300), static_cast<TReal>(0.001));
		ensure_equals("LV03 Y", position.getY().getMetresValue(), static_cast<TReal>(617306.300), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(268507.300, 617306.300, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 X", position.getX().getMetresValue(), static_cast<TReal>(1268507.870), static_cast<TReal>(0.001));
		ensure_equals("LV95 Y", position.getY().getMetresValue(), static_cast<TReal>(2617306.920), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }


	template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("Pfaender LV95");
        TPositionVector position(1265372.250, 2776668.590, (0 /*- 1.2233*/), TCoordSysFactory::k2DPlusH);

        TLV03Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV03 X", position.getX().getMetresValue(), static_cast<TReal>(265372.681), static_cast<TReal>(0.001));
		ensure_equals("LV03 Y", position.getY().getMetresValue(), static_cast<TReal>(776668.105), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(265372.681, 776668.105, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 X", position.getX().getMetresValue(), static_cast<TReal>(1265372.250), static_cast<TReal>(0.001));
		ensure_equals("LV95 Y", position.getY().getMetresValue(), static_cast<TReal>(2776668.590), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

	template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("Zimmerwald LV95");
        TPositionVector position(1191775.030, 2602030.740, (0 /*- 1.2233*/), TCoordSysFactory::k2DPlusH);

        TLV03Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV03 X", position.getX().getMetresValue(), static_cast<TReal>(191775.030), static_cast<TReal>(0.001));
		ensure_equals("LV03 Y", position.getY().getMetresValue(), static_cast<TReal>(602030.680), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<6>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(191775.030, 602030.680, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 X", position.getX().getMetresValue(), static_cast<TReal>(1191775.030), static_cast<TReal>(0.001));
		ensure_equals("LV95 Y", position.getY().getMetresValue(), static_cast<TReal>(2602030.740), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

	template<>
    template<>
    void object::test<7>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("La Givrine LV95");
        TPositionVector position(1145626.140, 2497312.650, (0 /*- 1.2233*/), TCoordSysFactory::k2DPlusH); 

        TLV03Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV03 X", position.getX().getMetresValue(), static_cast<TReal>(145625.438), static_cast<TReal>(0.001));
		ensure_equals("LV03 Y", position.getY().getMetresValue(), static_cast<TReal>(497313.292), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<8>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(145625.438, 497313.292, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 X", position.getX().getMetresValue(), static_cast<TReal>(1145626.140), static_cast<TReal>(0.001));
		ensure_equals("LV95 Y", position.getY().getMetresValue(), static_cast<TReal>(2497312.650), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }
	template<>
    template<>
    void object::test<9>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("Monte Generoso LV95");
        TPositionVector position(1087648.190, 2722759.059, (0 /*- 1.2233*/), TCoordSysFactory::k2DPlusH); 

        TLV03Transformation trans(true);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV03 X", position.getX().getMetresValue(), static_cast<TReal>(87649.670), static_cast<TReal>(0.001));
		ensure_equals("LV03 Y", position.getY().getMetresValue(), static_cast<TReal>(722758.809), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<10>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(87649.670, 722758.809, 0, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(false);
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 X", position.getX().getMetresValue(), static_cast<TReal>(1087648.190), static_cast<TReal>(0.001));
		ensure_equals("LV95 Y", position.getY().getMetresValue(), static_cast<TReal>(2722759.059), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(0.0), static_cast<TReal>(0.001));
    }


}
