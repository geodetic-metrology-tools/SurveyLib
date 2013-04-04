#include <TLambert93Transformation.h>
#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_TLambert93Transformation{};
    typedef test_group<test_TLambert93Transformation> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test TLambert93Transformation class");
}

namespace tut
{
	template<>
    template<>
    void object::test<1>()
    {
		set_test_name("Transforming a TSpatialPosition from ETRF93 into Lambert93");
		TPositionVector pv(0.872664626, 0.145512099, (400.157), TCoordSysFactory::kGeodetic); 
		

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		ensure("Transform returns true", 
			position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93)));


        //TLambert93Transformation trans(true);
        //ensure("Transform returns true", trans.transform(position));

		//std::cout << "X: " << position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue() << std::endl;
		//std::cout << "Y: " << position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue() << std::endl;
			

        ensure_distance("Lambert 93 X", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(1082722.205), static_cast<TReal>(0.001));
		ensure_distance("Lambert 93 Y", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(7001994.409), static_cast<TReal>(0.001));
		//ensure_distance("RGF93 CC46 H", position.getH().getMetresValue(), static_cast<TReal>(400.157 /*- 1.2233*/), static_cast<TReal>(0.001));
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
        set_test_name("Transforming a TSpatialPosition from Lambert93 into ETRF93");
        TPositionVector pv(1082722.205, 7001994.409, (400.157), TCoordSysFactory::k2DPlusH); 
		
		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kLambert93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		ensure("Transform returns true", 
			position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93)));

		//std::cout << "PHI deg: " << position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue() << std::endl;
		//std::cout << "PHI min: " << position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue() << std::endl;
		//std::cout << "PHI sec: " << position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue() << std::endl;

		//std::cout << "LAM: " << position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue() << std::endl;
																																		
        ensure_distance("ETRF93 PHI", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getRadiansValue(), static_cast<TReal>(0.872664626), static_cast<TReal>(1e-4));
        ensure_distance("ETRF93 LAM", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getRadiansValue(), static_cast<TReal>(0.145512099), static_cast<TReal>(1e-4)); 
        //ensure_distance("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(4573892.46194), static_cast<TReal>(1e-3));
	}
}
