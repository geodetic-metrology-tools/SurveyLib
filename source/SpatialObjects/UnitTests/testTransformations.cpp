#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>

namespace tut
{
    struct test_Transformations{};
    typedef test_group<test_Transformations> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test cordinate transformations");
}

namespace tut
{
	template<>
	template<>
	void object::test<1>()
	{
        set_test_name("Converting Zimmerwald cartesian ITRF97->ETRF93 and ETRF93->ITRF97");
		TPositionVector pv(4331297.1801, 567555.7634, 4633133.8516, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));

        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4331297.34365), static_cast<real>(0.00001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(567555.63150), static_cast<real>(0.00001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4633133.70950), static_cast<real>(0.00001));

        // Inverse transformation - take the ETRF result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97));
        ensure_distance("ITRF97 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4331297.1801), static_cast<real>(0.00001));
		ensure_distance("ITRF97 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(567555.7634), static_cast<real>(0.00001));
		ensure_distance("ITRF97 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4633133.8516), static_cast<real>(0.00001));
	}

    template<>
	template<>
	void object::test<2>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Projection on GRS80) Converting Chrischona ETRF93(XYZ)->ETRF93(Phi,Lambda,H).");
		TPositionVector pv(4273147.936, 575368.294, 4684903.639, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        ensure_equals("ETRF93 Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("ETRF93 Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("ETRF93 Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<real>(1.385301), static_cast<real>(1e-4));

        ensure_equals("ETRF93 Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("ETRF93 Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("ETRF93 Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<real>(6.983077), static_cast<real>(1e-4));

        ensure_distance("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<real>(504.935), static_cast<real>(1e-3));
	}

    template<>
	template<>
	void object::test<3>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Projection on GRS80) Converting Chrischona ETRF93(Phi,Lambda,H)->ETRF93(XYZ)");
        TPositionVector pv(TCoordSysFactory::kGeodetic);
        {
            TAngle phi; 
            ensure("Setting phi",phi.setDMSValue(47, 34, 1.385301));
            TAngle lam; 
            ensure("Setting lam",lam.setDMSValue(7, 40, 6.983077));
            TLength h(504.935);
            ensure("pv.setPhiEllipsoid",pv.setPhiEllipsoid(phi));
	        ensure("pv.setLambdaEllipsoid",pv.setLambdaEllipsoid(lam));
	        ensure("pv.setH",pv.setH(h));
	        pv.setStatus(TVNumericValue::kKnown);
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4273147.936), static_cast<real>(0.001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(575368.294), static_cast<real>(0.001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4684903.639), static_cast<real>(0.001));
	}

    template<>
	template<>
	void object::test<4>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Transformation) Converting Chrischona ETRF93(X,Y,Z)->CH1903+(XYZ)");
		TPositionVector pv(4273147.936, 575368.294, 4684903.639, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));

        ensure_distance("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4272473.562), static_cast<real>(0.001));
		ensure_distance("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(575353.239), static_cast<real>(0.001));
		ensure_distance("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4684498.293), static_cast<real>(0.001));

        // Inverse transformation - take the CH1903+ result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4273147.936), static_cast<real>(0.001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(575368.294), static_cast<real>(0.001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4684903.639), static_cast<real>(0.001));

    }

    template<>
	template<>
	void object::test<5>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Transformation) Converting Chrischona ETRF93(Phi,Lam,H)->CH1903+(XYZ)");
        TPositionVector pv(TCoordSysFactory::kGeodetic);
        {
            TAngle phi; 
            ensure("Setting phi",phi.setDMSValue(47, 34, 1.385301));
            TAngle lam; 
            ensure("Setting lam",lam.setDMSValue(7, 40, 6.983077));
            TLength h(504.935);
            ensure("pv.setPhiEllipsoid",pv.setPhiEllipsoid(phi));
	        ensure("pv.setLambdaEllipsoid",pv.setLambdaEllipsoid(lam));
	        ensure("pv.setH",pv.setH(h));
	        pv.setStatus(TVNumericValue::kKnown);
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));

        ensure_distance("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4272473.562), static_cast<real>(0.001));
		ensure_distance("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(575353.239), static_cast<real>(0.001));
		ensure_distance("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4684498.293), static_cast<real>(0.001));

        // Inverse transformation - take the CH1903+ result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<real>(4273147.936), static_cast<real>(0.001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<real>(575368.294), static_cast<real>(0.001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<real>(4684903.639), static_cast<real>(0.001));

        ensure_equals("ETRF93 Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("ETRF93 Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("ETRF93 Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<real>(1.385301), static_cast<real>(1e-4));

        ensure_equals("ETRF93 Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("ETRF93 Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("ETRF93 Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<real>(6.983077), static_cast<real>(1e-4));

        ensure_distance("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<real>(504.935), static_cast<real>(1e-3));
    }

}
