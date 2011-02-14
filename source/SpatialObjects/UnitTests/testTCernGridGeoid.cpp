#include <TRefFrameInfo.h>
#include <TSpatialPosition.h>

#include <TRefFrameInfo.h>
#include <TRefSystemFactory.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_exceptions{};
    typedef test_group<test_exceptions> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test for proper handling of exceptions");
}

namespace tut
{
    template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Transforming ITRF to XYHg(RS2k)");
		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97), 1121473.242, 2492108.804, 479.081, TCoordSysFactory::k3DCartesian);

		try
		{
			position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCernXYHg00Machine));
			ensure("Should not get to this point", false);
		}
		catch(std::runtime_error const & e)
		{
			//std::cerr << "(EE) Exception while transforming point: "<< e.what()<<std::endl;
		}
	}
}
