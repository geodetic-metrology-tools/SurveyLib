#include <TRefFrameInfo.h>

#include <tut/tut.hpp>

#include <sstream>
#include <stdexcept>


namespace tut
{
    struct test_TRefFrameInfo{};
    typedef test_group<test_TRefFrameInfo> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TRefFrameInfo class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Iterating over the all registered ERefFrame values");

		TRefFrameInfo::RefFrameSet set = TRefFrameInfo::getRefFrameSet();
		ensure(set.count(TRefSystemFactory::kITRF97));
		ensure(set.count(TRefSystemFactory::kCCS));
		// Example
        std::stringstream out;
		for(TRefFrameInfo::RefFrameSet::const_iterator it = set.begin(); it!=set.end(); ++it)
        {
			out << *it << std::endl;
        }
        //std::cout << out.str() << std::endl;
	}

	template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Get the textual description of a given ERefFrame");

		ensure_equals(TRefFrameInfo::getName(TRefSystemFactory::kCCS), "CCS - CERN XYZ");
		ensure_equals(TRefFrameInfo::getName(TRefSystemFactory::kWGS84), "WGS84");
		// ...
	}

	template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Check if a number corresponds to a valid ERefFrame");

        ensure(TRefFrameInfo::isValidNumber(0));
        ensure_not(TRefFrameInfo::isValidNumber(-1));
	}

	template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Perform a safe conversion between a valid int and TRefFrameFactory::ERefFrame");

        ensure_equals(TRefFrameInfo::fromNumber(0), TRefSystemFactory::kCCS);
        ensure_equals(TRefFrameInfo::fromNumber(TRefSystemFactory::kITRF97), TRefSystemFactory::kITRF97);
	}

    template<>
    template<>
    void object::test<5>()
    {
        set_test_name("Get the default coordinate system for a given reference frame");

        ensure_equals(TRefFrameInfo::getDefaultCoordSys(TRefSystemFactory::kCCS), TCoordSysFactory::k3DCartesian);
        ensure_equals(TRefFrameInfo::getDefaultCoordSys(TRefSystemFactory::kITRF97), TCoordSysFactory::k3DCartesian);
        ensure_equals(TRefFrameInfo::getDefaultCoordSys(TRefSystemFactory::kCernXYHg00Machine), TCoordSysFactory::k2DPlusH);
	}

    template<>
    template<>
    void object::test<6>()
    {
        set_test_name("Check whether the reference frame handles a given coordinate system");

        ensure(TRefFrameInfo::isCoordSysAllowed(TRefSystemFactory::kCCS, TCoordSysFactory::k3DCartesian));
        ensure_not(TRefFrameInfo::isCoordSysAllowed(TRefSystemFactory::kCCS, TCoordSysFactory::kGeodetic));
        ensure_not(TRefFrameInfo::isCoordSysAllowed(TRefSystemFactory::kCCS, TCoordSysFactory::k2DPlusH));

        ensure(TRefFrameInfo::isCoordSysAllowed(TRefSystemFactory::kITRF97, TCoordSysFactory::k3DCartesian));
        ensure(TRefFrameInfo::isCoordSysAllowed(TRefSystemFactory::kITRF97, TCoordSysFactory::kGeodetic));
        ensure_not(TRefFrameInfo::isCoordSysAllowed(TRefSystemFactory::kITRF97, TCoordSysFactory::k2DPlusH));
    }

    template<>
    template<>
    void object::test<7>()
    {
        set_test_name("Check whether the reference frame is local");
        ensure_not(TRefFrameInfo::isLocalRefFrame(TRefSystemFactory::kCCS));
        ensure(TRefFrameInfo::isLocalRefFrame(TRefSystemFactory::kMLA1985Machine));
        ensure(TRefFrameInfo::isLocalRefFrame(TRefSystemFactory::kMLA2000Machine));
    }


	template<>
    template<>
    void object::test<10>()
    {
        set_test_name("An exception in case of conversion from invalid number");
		try
		{
            TRefFrameInfo::fromNumber(-1);
			ensure("Should have thrown",false);
		}
		catch (const std::invalid_argument & e)
		{
		}
	}

	template<>
    template<>
    void object::test<11>()
    {
        set_test_name("An exception when getting a description for invalid number");
		try
		{
			TRefFrameInfo::getName(-1);
			ensure("Expected exception!",false);
		}
		catch (const std::invalid_argument & e)
		{
			// std::cout << e.what() << std::endl;
		}
	}
}
