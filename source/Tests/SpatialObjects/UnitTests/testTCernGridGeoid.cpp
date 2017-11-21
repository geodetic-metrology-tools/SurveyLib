#include <TRefFrameInfo.h>
#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>
#include <TRefSystemFactory.h>

#include <tut/tut.hpp>
#include <tut/tut_macros.hpp>

#include <stdexcept>


namespace tut
{
    struct test_exceptions{};
    typedef test_group<test_exceptions> factory;
	factory test_group("Test for proper handling of exceptions");
    typedef factory::object object;

    template<>
    template<>
    void object::test<1>()
    {
        set_test_name("Transforming ITRF to XYHg(RS2k)");
		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97), 1121473.242, 2492108.804, 479.081, TCoordSysFactory::k3DCartesian);

		ensure_THROW(position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCernXYHg00Machine)), std::runtime_error);
	}
}
