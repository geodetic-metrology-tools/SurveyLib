// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifdef _WIN32

#include <TLV03Transformation.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>

/* Reference:
Formules et constantes pour le calcul de la projection cylindrique ?? axe oblique et pour la transformation entre des systemes de reference
Swisstopo, 2016
*/

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

		set_test_name("Chrischona LV95");
		TPositionVector position(2617306.920, 1268507.870, 457.138, TCoordSysFactory::k2DPlusH);
        TLV03Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(617306.300), static_cast<TReal>(0.001));
		ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(268507.300), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(457.138), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(617306.300, 268507.300, 457.138, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2617306.920), static_cast<TReal>(0.001));
        ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1268507.870), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(457.138), static_cast<TReal>(0.001));
    }


	template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("Pfaender LV95");
		TPositionVector position(2776668.590, 1265372.250, (1043.616), TCoordSysFactory::k2DPlusH);

        TLV03Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(776668.105), static_cast<TReal>(0.001));
        ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(265372.681), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1043.616), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(776668.105, 265372.681, 1043.616, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2776668.590), static_cast<TReal>(0.001));
        ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1265372.250), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1043.616), static_cast<TReal>(0.001));
    }

	template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("Zimmerwald LV95");
		TPositionVector position(2602030.740, 1191775.030, (897.361), TCoordSysFactory::k2DPlusH);

        TLV03Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(602030.680), static_cast<TReal>(0.001));
        ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(191775.030), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(897.361), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<6>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(602030.680, 191775.030, 897.361, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2602030.740), static_cast<TReal>(0.001));
        ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1191775.030), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(897.361), static_cast<TReal>(0.001));
    }

	template<>
    template<>
    void object::test<7>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("La Givrine LV95");
		TPositionVector position(2497312.650, 1145626.140, (1206.367), TCoordSysFactory::k2DPlusH); 

        TLV03Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(497313.292), static_cast<TReal>(0.001));
        ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(145625.438), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1206.367), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<8>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(497313.292, 145625.438, 1206.367, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2497312.650), static_cast<TReal>(0.001));
        ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1145626.140), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1206.367), static_cast<TReal>(0.001));
    }
	template<>
    template<>
    void object::test<9>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into LV03");

        set_test_name("Monte Generoso LV95");
		TPositionVector position(2722759.059, 1087648.190, (1634.472), TCoordSysFactory::k2DPlusH); 

        TLV03Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(722758.809), static_cast<TReal>(0.001));
        ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(87649.670), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1634.472), static_cast<TReal>(0.001));
    }

    template<>
    template<>
    void object::test<10>()
    {
        set_test_name("Transforming a TSpatialPosition from LV03 into LV95");

        TPositionVector position(722758.809, 87649.670, 1634.472, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2722759.059), static_cast<TReal>(0.001));
        ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1087648.190), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1634.472), static_cast<TReal>(0.001));
    }

	template<>
	template<>
	void object::test<11>()
	{
		set_test_name("Transforming a TSpatialPosition from LV03 (LN02 leveled height) into LV95 (ellipsoidal height)");

		TPositionVector position(722758.809, 87649.670, 1636.600, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2722759.059), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1087648.190), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1634.472), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<12>()
	{
		set_test_name("Transforming a TSpatialPosition from LV95 (ellipsoidal) into LV03 (LN02 leveled)");

		set_test_name("Monte Generoso LV95");
		TPositionVector position(2722759.059, 1087648.190, (1634.472), TCoordSysFactory::k2DPlusH);

		TLV03Transformation trans(true, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(722758.809), static_cast<TReal>(0.001));
		ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(87649.670), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1636.600), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<13>()
	{
		set_test_name("Transforming a TSpatialPosition from LV95 (ellipsoidal) into LV03 (LN02 leveled)");

		set_test_name("La Givrine LV95");
		TPositionVector position(2497312.650, 1145626.140, (1206.367), TCoordSysFactory::k2DPlusH);

		TLV03Transformation trans(true, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(497313.292), static_cast<TReal>(0.001));
		ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(145625.438), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1207.434), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<14>()
	{
		set_test_name("Transforming a TSpatialPosition from LV03 (LN02 leveled) into LV95 (ellipsoidal)");

		TPositionVector position(497313.292, 145625.438, 1207.434, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2497312.650), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1145626.140), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1206.367), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<15>()
	{
		set_test_name("Transforming a TSpatialPosition from LV03 (LHN95 orthometric height) into LV95 (ellipsoidal height)");
		set_test_name("Monte Generoso LV03");

		TPositionVector position(722758.810, 87649.670, 1636.794, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "lhn95");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2722759.060), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1087648.190), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1634.472), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<16>()
	{
		set_test_name("Transforming a TSpatialPosition from LV95 (ellipsoidal) into LV03 (LN02 leveled)");

		set_test_name("Monte Generoso LV95");
		TPositionVector position(2722759.060, 1087648.190, (1634.472), TCoordSysFactory::k2DPlusH);

		TLV03Transformation trans(true, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(722758.810), static_cast<TReal>(0.001));
		ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(87649.670), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1636.600), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<17>()
	{
		set_test_name("Transforming a TSpatialPosition from LV95 (ellipsoidal) into LV03 (LN02 leveled)");

		set_test_name("La Givrine LV95");
		TPositionVector position(2497312.650, 1145626.140, (1206.367), TCoordSysFactory::k2DPlusH);

		TLV03Transformation trans(true, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV03 E", position.getX().getMetresValue(), static_cast<TReal>(497313.292), static_cast<TReal>(0.001));
		ensure_equals("LV03 N", position.getY().getMetresValue(), static_cast<TReal>(145625.438), static_cast<TReal>(0.001));
		ensure_equals("LV03 H", position.getH().getMetresValue(), static_cast<TReal>(1207.434), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<18>()
	{
		set_test_name("Transforming a TSpatialPosition from LV03 (LN02 leveled) into LV95 (ellipsoidal)");

		TPositionVector position(497313.292, 145625.438, 1207.434, TCoordSysFactory::k2DPlusH);
		TLV03Transformation trans(false, "ln02");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2497312.650), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1145626.140), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1206.367), static_cast<TReal>(0.001));
	}
	}

#endif
