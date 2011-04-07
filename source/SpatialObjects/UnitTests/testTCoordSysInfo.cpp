#include <TCoordSysInfo.h>

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

		ensure(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(1)),TCoordSysFactory::k3DCartesian);
		ensure(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(2)),TCoordSysFactory::kGeodetic);
		ensure(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(4)),TCoordSysFactory::k2DPlusH);
		ensure(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(8)),TCoordSysFactory::k2DCartesian);
		ensure(TCoordSysInfo::toString(static_cast<TCoordSysFactory::ECoordSys>(16)),TCoordSysFactory::kGeodeticSphere);

	}

	template<>
    template<>
    void object::test<4>()
    {
        set_test_name("Perform a safe conversion between a valid string and TCoordSysFactory::ECoordSys");
		//ensure(TCoordSysInfo::fromString("k3DCartesian"), "k3DCartesian");
		//static std::string fromString (const std::string & systemName);
	}

}