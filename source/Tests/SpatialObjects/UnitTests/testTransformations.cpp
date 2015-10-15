#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>

#include <tut/tut.hpp>

#include <iostream>
#include <fstream>

#include <map>
#include <string>

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

        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4331297.34365), static_cast<TReal>(0.00001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(567555.63150), static_cast<TReal>(0.00001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4633133.70950), static_cast<TReal>(0.00001));

        // Inverse transformation - take the ETRF result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97));
        ensure_distance("ITRF97 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4331297.1801), static_cast<TReal>(0.00001));
		ensure_distance("ITRF97 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(567555.7634), static_cast<TReal>(0.00001));
		ensure_distance("ITRF97 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4633133.8516), static_cast<TReal>(0.00001));
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
        ensure_distance("ETRF93 Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(1.385301), static_cast<TReal>(1e-4));

        ensure_equals("ETRF93 Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("ETRF93 Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("ETRF93 Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(6.983077), static_cast<TReal>(1e-4));

        ensure_distance("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getValue(), static_cast<TReal>(504.935), static_cast<TReal>(1e-3));
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
            TReal h(504.935);
            ensure("pv.setPhiEllipsoid",pv.setPhiEllipsoid(phi));
	        ensure("pv.setLambdaEllipsoid",pv.setLambdaEllipsoid(lam));
	        ensure("pv.setH",pv.setH(h));
	        pv.setStatus(TVNumericValue::kKnown);
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4273147.936), static_cast<TReal>(0.001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(575368.294), static_cast<TReal>(0.001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4684903.639), static_cast<TReal>(0.001));
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

        ensure_distance("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));

        // Inverse transformation - take the CH1903+ result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4273147.936), static_cast<TReal>(0.001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(575368.294), static_cast<TReal>(0.001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4684903.639), static_cast<TReal>(0.001));

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
            TReal h(504.935);
            ensure("pv.setPhiEllipsoid",pv.setPhiEllipsoid(phi));
	        ensure("pv.setLambdaEllipsoid",pv.setLambdaEllipsoid(lam));
	        ensure("pv.setH",pv.setH(h));
	        pv.setStatus(TVNumericValue::kKnown);
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));

        ensure_distance("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));

        // Inverse transformation - take the CH1903+ result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
        ensure_distance("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4273147.936), static_cast<TReal>(0.001));
		ensure_distance("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(575368.294), static_cast<TReal>(0.001));
		ensure_distance("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4684903.639), static_cast<TReal>(0.001));

        ensure_equals("ETRF93 Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("ETRF93 Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("ETRF93 Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(1.385301), static_cast<TReal>(1e-4));

        ensure_equals("ETRF93 Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("ETRF93 Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("ETRF93 Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(6.983077), static_cast<TReal>(1e-4));

        ensure_distance("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getValue(), static_cast<TReal>(504.935), static_cast<TReal>(1e-3));
    }

    template<>
	template<>
	void object::test<6>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Projection on GRS80) Converting Chrischona CH1903+(Phi,Lambda,H)->CH1903+(XYZ)");
        TPositionVector pv(TCoordSysFactory::kGeodetic);
        {
            TAngle phi; 
            ensure("Setting phi",phi.setDMSValue(47, 34, 6.404965));
            TAngle lam; 
            ensure("Setting lam",lam.setDMSValue(7, 40, 10.574820));
            TReal h(457.138);
            ensure("pv.setPhiEllipsoid",pv.setPhiEllipsoid(phi));
	        ensure("pv.setLambdaEllipsoid",pv.setLambdaEllipsoid(lam));
	        ensure("pv.setH",pv.setH(h));
	        pv.setStatus(TVNumericValue::kKnown);
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        ensure_distance("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));
	}

    template<>
	template<>
	void object::test<7>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Projection on Bessel1841) Converting Chrischona CH11903+(XYZ)->CH1903+(Phi,Lambda,H).");
		TPositionVector pv(4272473.562, 575353.239, 4684498.293, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        ensure_equals("CH1903+ Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("CH1903+ Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("CH1903+ Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(6.404965), static_cast<TReal>(1e-4));

        ensure_equals("CH1903+ Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("CH1903+ Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("CH1903+ Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(10.574820), static_cast<TReal>(1e-4)); 

        ensure_distance("CH1903+ H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getValue(), static_cast<TReal>(457.138), static_cast<TReal>(1e-3));
	}

    template<>
	template<>
	void object::test<8>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("Converting Chrischona CH11903+(XYZ)->LV95");
		TPositionVector pv(4272473.562, 575353.239, 4684498.293, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Transformation OK", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95)));
        ensure_distance("LV95 X", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getValue(), static_cast<TReal>(1268507.870), static_cast<TReal>(0.001));
		ensure_distance("LV95 Y", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getValue(), static_cast<TReal>(2617306.920), static_cast<TReal>(0.001));
		ensure_distance("LV95 H", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getValue(), static_cast<TReal>(457.138 /*- 1.2233*/), static_cast<TReal>(0.001));
	}

    template<>
	template<>
	void object::test<9>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("Converting Chrischona LV95->CH1903+");
        TPositionVector pv(1268507.870, 2617306.920, (457.138 /*- 1.2233*/), TCoordSysFactory::k2DPlusH);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Transformation OK", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus)));
        

        ensure_equals("CH1903+ Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("CH1903+ Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("CH1903+ Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(6.404965), static_cast<TReal>(1e-4));

        ensure_equals("CH1903+ Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("CH1903+ Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("CH1903+ Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(10.574820), static_cast<TReal>(1e-4)); 

        ensure_distance("CH1903+ H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getValue(), static_cast<TReal>(457.138), static_cast<TReal>(1e-3));

	}

    template<>
	template<>
	void object::test<10>()
	{
        set_test_name("Transforming Bellegard from ETRF93 into RGF93 CC46");
        TPositionVector pv(4407040.76287, 449723.28541, 4573892.46194, TCoordSysFactory::k3DCartesian);
      
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93Zone5));     

        ensure_distance("RGF93 CC46 X", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getValue(), static_cast<TReal>(1918471.0676), static_cast<TReal>(0.0001));
		ensure_distance("RGF93 CC46 Y", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getValue(), static_cast<TReal>(5215917.6067), static_cast<TReal>(0.0001));
		ensure_distance("RGF93 CC46 H", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getValue(), static_cast<TReal>(400.157 /*- 1.2233*/), static_cast<TReal>(0.001));   
    }

	template<>
	template<>
	void object::test<11>()
	{
		set_test_name("Bug fix - did not convert back from RGF93_5 to CCS");
		TPositionVector pv(1934404.452, 5230706.747, 531.563, TCoordSysFactory::k2DPlusH);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93Zone5));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS));     

		ensure_distance("CCS X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getValue(), static_cast<TReal>(1200.67), static_cast<TReal>(0.01)); 
		ensure_distance("CCS Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getValue(), static_cast<TReal>(2077.57), static_cast<TReal>(0.01));
		ensure_distance("CCS Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getValue(), static_cast<TReal>(2481.52), static_cast<TReal>(0.01));   
	}
}
