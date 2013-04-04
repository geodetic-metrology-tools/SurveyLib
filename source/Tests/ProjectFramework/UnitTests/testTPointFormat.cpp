#include <TPointFormat.h>
#include <tut/tut.hpp>

namespace tut
{
    struct test_testTPointFormat{};
    typedef test_group<test_testTPointFormat> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test test_testTPointFormat");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
		TPointFormat::ECoordPrecision currPrec = TPointFormat::kMetre;

		double value = TPointFormat::getPrecision(currPrec);
		ensure_equals("TPointFormat::getPrecision", value, 0.1);
        
    }

    template<>
    template<>
    void object::test<2>()
    {
        TPointFormat::ECoordPrecision currPrec = TPointFormat::kMillimetre;

		double value = TPointFormat::getPrecision(currPrec);
		ensure_equals("TPointFormat::getPrecision", value, 0.0001);

    }

	template<>
    template<>
    void object::test<3>()
    {
		int prec = 1;

		TPointFormat::ECoordPrecision precName = TPointFormat::getPrecisionFromNumber(prec);
		ensure_equals(precName, TPointFormat::k100Millimetres);

    }

	template<>
    template<>
    void object::test<4>()
    {
		int prec = 6;

		TPointFormat::ECoordPrecision precName = TPointFormat::getPrecisionFromNumber(prec);
		ensure_equals(precName, TPointFormat::kMicrometre);

    }
}
