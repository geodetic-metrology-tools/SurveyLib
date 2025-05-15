// SPDX-FileCopyrightText: 2025 CERN

// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <TCoordSysInfo.h>

#include <tut/tut.hpp>

#include <sstream>
#include <stdexcept>


namespace tut
{
    struct test_TCoordSysInfo{};
    typedef test_group<test_TCoordSysInfo> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TCoordSysInfo class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
        /*set_test_name("Iterating over the all registered map values");

		std::stringstream out;

		TCoordSysInfo::CoordMapType::const_iterator it;
		for (it = TCoordSysInfo::getCoordSysMap().begin(); it != TCoordSysInfo::getCoordSysMap().end(); ++it)
		{
			out << it->first <<"\t"<< it->second <<std::endl();
		}*/

	}

	template<>
    template<>
    void object::test<2>()
    {
        set_test_name("Check if a number corresponds to a valid TCoordSysFactory");

		ensure(TCoordSysInfo::isValidNumber(2));
		ensure_not(TCoordSysInfo::isValidNumber(-1));
	}

	template<>
    template<>
    void object::test<3>()
    {
        set_test_name("Perform a safe conversion between a valid int and TCoordSysFactory::ECoordSys");

		ensure_equals(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(1)), "k3DCartesian");
		ensure_equals(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(2)), "kGeodetic");
		ensure_equals(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(4)), "k2DPlusH");
		ensure_equals(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(8)), "k2DCartesian");
		ensure_equals(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(16)), "kGeodeticSphere");

	}

	template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Perform a safe conversion between a valid string and TCoordSysFactory::ECoordSys");

		ensure_equals(TCoordSysInfo::fromString("k3DCartesian"), TCoordSysFactory::ECoordSys::k3DCartesian);
		ensure_equals(TCoordSysInfo::fromString("kGeodetic"), TCoordSysFactory::ECoordSys::kGeodetic);
		ensure_equals(TCoordSysInfo::fromString("k2DPlusH"), TCoordSysFactory::ECoordSys::k2DPlusH);
		ensure_equals(TCoordSysInfo::fromString("k2DCartesian"), TCoordSysFactory::ECoordSys::k2DCartesian);
		ensure_equals(TCoordSysInfo::fromString("kGeodeticSphere"), TCoordSysFactory::ECoordSys::kGeodeticSphere);
	}

}
