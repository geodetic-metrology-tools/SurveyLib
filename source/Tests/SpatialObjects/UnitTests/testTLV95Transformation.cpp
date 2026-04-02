// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifdef _WIN32

#include <TLV95Transformation.h>
#include <TRefFrameInfo.h>
#include <vector>

#include <tut/tut.hpp>

/* Reference:
Formules et constantes pour le calcul de la projection cylindrique ?? axe oblique et pour la transformation entre des systemes de reference
Swisstopo, 2016
*/

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
        set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95 (Chrishona)");
        TPositionVector position(4272473.562, 575353.239, 4684498.293, TCoordSysFactory::k3DCartesian);
        TLV95Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2617306.920), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1268507.870), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(457.138 ), static_cast<TReal>(0.001));
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
        set_test_name("Transforming a TSpatialPosition from LV95 into CH1903+ (Chrishona)");
		
        TPositionVector position(2617306.920, 1268507.870, (457.138 ), TCoordSysFactory::k2DPlusH);
        
        TLV95Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));
	}

    template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Transformation has the right source and destination frames");
        ensure_equals("TLV95Transformation(true).getSourceFrame() -> CH1903+", 
            TLV95Transformation(true, "eh").getSourceFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
        ensure_equals("TLV95Transformation(true).getDestinationFrame() -> LV95", 
            TLV95Transformation(true, "eh").getDestinationFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh));
        ensure_equals("TLV95Transformation(false).getSourceFrame() -> LV95", 
            TLV95Transformation(false, "eh").getSourceFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh));
        ensure_equals("TLV95Transformation(false).getDestinationFrame() -> CH1903+", 
            TLV95Transformation(false, "eh").getDestinationFrame(), TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
    }

	template<>
    template<>
    void object::test<6>()
    {
        set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95");
        set_test_name("Pfaender CH1903+");
		TPositionVector position(4252889.174, 733507.303, 4681046.757, TCoordSysFactory::k3DCartesian);
		TLV95Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2776668.590), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1265372.250), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1043.615 ), static_cast<TReal>(0.001));
	}
	template<>
    template<>
    void object::test<7>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into CH1903+ (Pfaender)");
		set_test_name("Pfaender LV95");
		TPositionVector position(2776668.590, 1265372.250, (1043.615 ), TCoordSysFactory::k2DPlusH);
        
        TLV95Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4252889.174), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(733507.303), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4681046.757), static_cast<TReal>(0.001));
	}

	template<>
    template<>
    void object::test<8>()
    {
        set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95");
        set_test_name("Zimmerwald    CH1903+");
		TPositionVector position(4330616.737, 567539.766, 4632721.664, TCoordSysFactory::k3DCartesian);
		TLV95Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2602030.740), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1191775.030), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(897.361 ), static_cast<TReal>(0.001));
	}
	template<>
    template<>
    void object::test<9>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into CH1903+ (Zimmerwald)");
		set_test_name("Zimmerwald LV95");
		TPositionVector position(2602030.740, 1191775.030, (897.361 ), TCoordSysFactory::k2DPlusH);

        TLV95Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4330616.737), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(567539.766), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4632721.664), static_cast<TReal>(0.001));
	}

	template<>
    template<>
    void object::test<10>()
    {
        set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95");
        set_test_name("La Givrine    CH1903+");
		TPositionVector position(4377121.142, 467993.592, 4600671.934, TCoordSysFactory::k3DCartesian);
	
        TLV95Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2497312.650), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1145626.140), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1206.367 ), static_cast<TReal>(0.001));
	}
	template<>
    template<>
    void object::test<11>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into CH1903+ (La Givrine)");
		set_test_name("La Givrine LV95");
		TPositionVector position(2497312.650, 1145626.140, (1206.367), TCoordSysFactory::k2DPlusH); 

        TLV95Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4377121.142), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(467993.592), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4600671.934), static_cast<TReal>(0.001));
	}

	template<>
    template<>
    void object::test<12>()
    {
        set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95");
		set_test_name("Monte Generoso CH1903+");     
		TPositionVector position( 4389483.221, 696984.352, 4560589.600, TCoordSysFactory::k3DCartesian);
	
        TLV95Transformation trans(true, "eh");
        ensure("Transform returns true", trans.transform(position));

        ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2722759.059), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1087648.190), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1634.472 ), static_cast<TReal>(0.001));
	}
	template<>
    template<>
    void object::test<13>()
    {
        set_test_name("Transforming a TSpatialPosition from LV95 into CH1903+ (Monte Generoso)");
		set_test_name("Monte Generoso LV95");
		TPositionVector position(2722759.059, 1087648.190, (1634.472 ), TCoordSysFactory::k2DPlusH); 

        TLV95Transformation trans(false, "eh");
        ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4389483.221), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(696984.352), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4560589.600), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<14>()
	{
		set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95 (ortho)");
		set_test_name("Monte Generoso CH1903+");
		TPositionVector position(4389483.221, 696984.352, 4560589.600, TCoordSysFactory::k3DCartesian);

		TLV95Transformation trans(true, "lhn95");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2722759.059), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1087648.190), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1636.794), static_cast<TReal>(0.001));
	}
	template<>
	template<>
	void object::test<15>()
	{
		set_test_name("Transforming a TSpatialPosition from LV95 (ortho) into CH1903+ (Monte Generoso)");
		set_test_name("Monte Generoso LV95");
		TPositionVector position(2722759.059, 1087648.190, (1636.794), TCoordSysFactory::k2DPlusH);

		TLV95Transformation trans(false, "lhn95");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4389483.221), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(696984.352), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4560589.600), static_cast<TReal>(0.001));
	}
	template<>
	template<>
	void object::test<16>()
	{
		set_test_name("Transforming a TSpatialPosition from CH1903+ into LV95 (ortho");
		set_test_name("La Givrine    CH1903+");
		TPositionVector position(4377121.142, 467993.592, 4600671.934, TCoordSysFactory::k3DCartesian);

		TLV95Transformation trans(true, "lhn95");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("LV95 E", position.getX().getMetresValue(), static_cast<TReal>(2497312.650), static_cast<TReal>(0.001));
		ensure_equals("LV95 N", position.getY().getMetresValue(), static_cast<TReal>(1145626.140), static_cast<TReal>(0.001));
		ensure_equals("LV95 H", position.getH().getMetresValue(), static_cast<TReal>(1207.473), static_cast<TReal>(0.001));
	}
	template<>
	template<>
	void object::test<17>()
	{
		set_test_name("Transforming a TSpatialPosition from LV95 (ortho) into CH1903+ (La Givrine)");
		set_test_name("La Givrine LV95");
		TPositionVector position(2497312.650, 1145626.140, (1207.473), TCoordSysFactory::k2DPlusH);

		TLV95Transformation trans(false, "lhn95");
		ensure("Transform returns true", trans.transform(position));

		ensure_equals("CH1903+ X", position.getX().getMetresValue(), static_cast<TReal>(4377121.142), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getY().getMetresValue(), static_cast<TReal>(467993.592), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getZ().getMetresValue(), static_cast<TReal>(4600671.934), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<18>()
	{
		set_test_name("Transforming a TSpatialPosition from CCS to LV95 (ortho)");

		TAReferenceFrame *CCS(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
		TAReferenceFrame *lv95_ortho(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kSwissLV95_lhn95));
		TSpatialPosition point = TSpatialPosition(CCS, 1000.356, 540.1654, 142.023, TCoordSysFactory::k3DCartesian);

		ensure("Transform returns true", point.transform(lv95_ortho));
		ensure_equals("LV95 X", point.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(2491061.9103335), static_cast<TReal>(1e-7));
		ensure_equals("LV95 Y", point.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(1120328.9280417), static_cast<TReal>(1e-7));
		ensure_equals("LHN95 Z", point.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue(), static_cast<TReal>(-1857.7002211), static_cast<TReal>(1e-7));
	}

	}

#endif
