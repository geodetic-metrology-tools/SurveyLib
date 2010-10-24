#include <TAngle.h>
#include <TVNumericValue.h>

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
    const TReal test_value = TAngle::decDegsToRadsFactor();
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Problematic static initialisation fiasco discovered in TAngle");
        ensure_distance("anonymous namespace", test_value, TReal(0.01745329251994329577), TReal(1e-6));
        ensure_distance("function call", TAngle::decDegsToRadsFactor(), TReal(0.01745329251994329577), TReal(1e-6));
        //std::cout << std::endl;
        //std::cout << test_value << std::endl;        
        //std::cout << TAngle::decDegsToRadsFactor() << std::endl;
    }
}
