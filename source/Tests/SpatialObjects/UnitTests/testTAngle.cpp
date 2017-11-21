#include <TAngle.h>
#include <tut/tut.hpp>

namespace tut
{
    struct test_TAngle{};
    typedef test_group<test_TAngle> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TAngle");
}

namespace {
    const TReal test_value = DEG2RAD;
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Problematic static initialisation fiasco discovered in TAngle");
        ensure_equals("anonymous namespace", test_value, TReal(0.01745329251994329577), TReal(1e-6));
        ensure_equals("function call", DEG2RAD, TReal(0.01745329251994329577), TReal(1e-6));
    }

    template<>
    template<>
    void object::test<2>()
    {
        set_test_name("getSecondsValue and getMinutesValue test (changed while refactoring the Quad)");
        TAngle angle1(0.987654321);
        ensure_equals("getMinutesValue", angle1.getMinutesValue(), 35);
        ensure_equals("getSecondsValue", angle1.getSecondsValue(), TReal(18.3271602), TReal(1e-5));

        TAngle angle2(-0.01);
        ensure_equals("getMinutesValue", angle2.getMinutesValue(), -34);
        ensure_equals("getSecondsValue", angle2.getSecondsValue(), TReal(22.6480625), TReal(1e-5));
    }
}
