// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
		//Test modified after the implementation of standard transformation model between ITRF and ETRF (feb. 2022)
        set_test_name("Converting Zimmerwald cartesian ETRF93 at epoch 1993.0 -> ITRF 97 at epoch 1998.5 and ITRF 97 at epoch 1998.5 ->  ETRF93 at epoch 1993.0. Predefined ITRF97 and ETRF93");
		TPositionVector pv(4331297.348, 567555.639, 4633133.728, TCoordSysFactory::k3DCartesian);
		//Position given by Swisstopo (valid since 2018)
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97));

		ensure_equals("ITRF 97 at epoch 1998.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.185), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.767), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.864), static_cast<TReal>(0.001));

        // Inverse transformation - take the ITRF result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure_equals("ETRF 93 at epoch 1993.0 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.348), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.639), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.728), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<2>()
	{
		set_test_name("Converting Zimmerwald cartesian ETRF93 at epoch 1993.0 -> ITRF 97 at epoch 1998.5 and ITRF 97 at epoch 1998.5 ->  ETRF93 at epoch 1993.0. Predefined ITRF97");
		TPositionVector pv(4331297.348, 567555.639, 4633133.728, TCoordSysFactory::k3DCartesian);
		// Position given by Swisstopo (valid since 2018)

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 1993.0, "ETRF 93"));
		ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

		position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97));

		ensure_equals("ITRF 97 at epoch 1998.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.185), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.767), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.864), static_cast<TReal>(0.001));

		// Inverse transformation - take the ITRF result and convert back
		position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFout, nullptr, 1993.0, "ETRF 93"));
		ensure_equals("ETRF 93 at epoch 1993.0 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.348), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.639), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.728), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<3>()
	{
		set_test_name("Converting Zimmerwald cartesian ETRF93 at epoch 1993.0 -> ITRF 97 at epoch 1998.5 and ITRF 97 at epoch 1998.5 ->  ETRF93 at epoch 1993.0. Predifined ETRF93");
		TPositionVector pv(4331297.348, 567555.639, 4633133.728, TCoordSysFactory::k3DCartesian);
		// Position given by Swisstopo (valid since 2018)

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

		position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 1998.5, "ITRF 97"));

		ensure_equals("ITRF 97 at epoch 1998.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.185), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.767), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.864), static_cast<TReal>(0.001));

		// Inverse transformation - take the ITRF result and convert back
		TPositionVector pvT(position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(),
			position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(),
			position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), TCoordSysFactory::k3DCartesian);
		TSpatialPosition positionT(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
		ensure("Setting the coordinates of TSpatialPosition", positionT.setCoordinates(pvT));

		positionT.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure_equals("ETRF 93 at epoch 1993.0 X", positionT.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.348), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Y", positionT.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.639), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Z", positionT.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.728), static_cast<TReal>(0.001));
	}

	template<>
	template<>
	void object::test<4>()
	{
		set_test_name("Converting Zimmerwald cartesian ETRF93 at epoch 1993.0 -> ITRF 97 at epoch 1998.5 and ITRF 97 at epoch 1998.5 ->  ETRF93 at epoch 1993.0");
		TPositionVector pv(4331297.348, 567555.639, 4633133.728, TCoordSysFactory::k3DCartesian);
		// Position given by Swisstopo (valid since 2018)

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 1993.0, "ETRF 93"));
		ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));

		position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 1998.5, "ITRF 97"));

		ensure_equals("ITRF 97 at epoch 1998.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.185), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.767), static_cast<TReal>(0.001));
		ensure_equals("ITRF 97 at epoch 1998.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.864), static_cast<TReal>(0.001));

		// Inverse transformation - take the ITRF result and convert back
		TPositionVector pvT(position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(),
							position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(),
							position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), TCoordSysFactory::k3DCartesian);
		TSpatialPosition positionT(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
		ensure("Setting the coordinates of TSpatialPosition", positionT.setCoordinates(pvT));

		positionT.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFout, nullptr, 1993.0, "ETRF 93"));
		ensure_equals("ETRF 93 at epoch 1993.0 X", positionT.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4331297.348), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Y", positionT.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(567555.639), static_cast<TReal>(0.001));
		ensure_equals("ETRF 93 at epoch 1993.0 Z", positionT.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4633133.728), static_cast<TReal>(0.001));
	}



    template<>
	template<>
	void object::test<5>()
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
		ensure_equals("ETRF93 Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(1.385301), static_cast<TReal>(1e-4));

        ensure_equals("ETRF93 Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("ETRF93 Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
		ensure_equals("ETRF93 Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(6.983077), static_cast<TReal>(1e-4));

		ensure_equals("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(504.935), static_cast<TReal>(1e-3));
	}

    template<>
	template<>
	void object::test<6>()
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
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		ensure_equals("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4273147.936), static_cast<TReal>(0.001));
		ensure_equals("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(575368.294), static_cast<TReal>(0.001));
		ensure_equals("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4684903.639), static_cast<TReal>(0.001));
	}

    template<>
	template<>
	void object::test<7>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("(Transformation) Converting Chrischona ETRF93(X,Y,Z)->CH1903+(XYZ)");
		TPositionVector pv(4273147.936, 575368.294, 4684903.639, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));

		ensure_equals("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));

        // Inverse transformation - take the CH1903+ result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure_equals("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4273147.936), static_cast<TReal>(0.001));
		ensure_equals("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(575368.294), static_cast<TReal>(0.001));
		ensure_equals("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4684903.639), static_cast<TReal>(0.001));

    }

    template<>
	template<>
	void object::test<8>()
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
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));

		ensure_equals("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_equals("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));

        // Inverse transformation - take the CH1903+ result and convert back
        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		ensure_equals("ETRF93 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4273147.936), static_cast<TReal>(0.001));
		ensure_equals("ETRF93 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(575368.294), static_cast<TReal>(0.001));
		ensure_equals("ETRF93 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4684903.639), static_cast<TReal>(0.001));

        ensure_equals("ETRF93 Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("ETRF93 Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
		ensure_equals("ETRF93 Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(1.385301), static_cast<TReal>(1e-4));

        ensure_equals("ETRF93 Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("ETRF93 Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
		ensure_equals("ETRF93 Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(6.983077), static_cast<TReal>(1e-4));

		ensure_equals("ETRF93 H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(504.935), static_cast<TReal>(1e-3));
    }

    template<>
	template<>
	void object::test<9>()
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
            TLength h(457.138);
            ensure("pv.setPhiEllipsoid",pv.setPhiEllipsoid(phi));
	        ensure("pv.setLambdaEllipsoid",pv.setLambdaEllipsoid(lam));
	        ensure("pv.setH",pv.setH(h));
        }
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        ensure_distance("CH1903+ X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4272473.562), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(575353.239), static_cast<TReal>(0.001));
		ensure_distance("CH1903+ Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4684498.293), static_cast<TReal>(0.001));
	}

    template<>
	template<>
	void object::test<10>()
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

        ensure_distance("CH1903+ H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(457.138), static_cast<TReal>(1e-3));
	}

    template<>
	template<>
	void object::test<11>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("Converting Chrischona CH11903+(XYZ)->LV95");
#ifndef _WIN32
        skip();
#else
		TPositionVector pv(4272473.562, 575353.239, 4684498.293, TCoordSysFactory::k3DCartesian);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Transformation OK", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh)));
		ensure_distance("LV95 E", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(2617306.920), static_cast<TReal>(0.001));
		ensure_distance("LV95 N", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(1268507.870), static_cast<TReal>(0.001));
		ensure_distance("LV95 H", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue(), static_cast<TReal>(457.138 ), static_cast<TReal>(0.001));
#endif
	}

    template<>
	template<>
	void object::test<12>()
	{
        /* Reference data taken from:
           "Formulas and constants for the calculation of the Swiss conformal cylindrical projection..."
         */
        set_test_name("Converting Chrischona LV95->CH1903+");
#ifndef _WIN32
        skip();
#else
		TPositionVector pv(2617306.920, 1268507.870, (457.138 ), TCoordSysFactory::k2DPlusH);
		
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));
        ensure("Transformation OK", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCH1903plus)));
        

        ensure_equals("CH1903+ Phi (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getDegreesValue(), 47);
        ensure_equals("CH1903+ Phi (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getMinutesValue(), 34);
        ensure_distance("CH1903+ Phi (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getPhiEllipsoid().getSecondsValue(), static_cast<TReal>(6.404965), static_cast<TReal>(1e-4));

        ensure_equals("CH1903+ Lam (Deg)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getDegreesValue(), 7);
        ensure_equals("CH1903+ Lam (Min)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getMinutesValue(), 40);
        ensure_distance("CH1903+ Lam (Sec)", position.getCoordinates(TCoordSysFactory::kGeodetic).getLambdaEllipsoid().getSecondsValue(), static_cast<TReal>(10.574820), static_cast<TReal>(1e-4)); 

        ensure_distance("CH1903+ H", position.getCoordinates(TCoordSysFactory::kGeodetic).getH().getMetresValue(), static_cast<TReal>(457.138), static_cast<TReal>(1e-3));
#endif

	}

    template<>
	template<>
	void object::test<13>()
	{
        set_test_name("Transforming Bellegard from RGF93 into RGF93 CC46");
        TPositionVector pv(4407040.76287, 449723.28541, 4573892.46194, TCoordSysFactory::k3DCartesian);
      
        TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

        position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_eh));     

        ensure_distance("RGF93 CC46 X", position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue(), static_cast<TReal>(1918471.0676), static_cast<TReal>(0.0001));
		ensure_distance("RGF93 CC46 Y", position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue(), static_cast<TReal>(5215917.6067), static_cast<TReal>(0.0001));
		ensure_distance("RGF93 CC46 H", position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue(), static_cast<TReal>(400.157 ), static_cast<TReal>(0.001));   
    }

	template<>
	template<>
	void object::test<14>()
	{
		set_test_name("Bug fix - did not convert back from RGF93_5 to CCS");
		TPositionVector pv(1934404.452, 5230706.747, 531.563, TCoordSysFactory::k2DPlusH);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kFrenchRGF93_CC46_eh));
		ensure("Setting the coordinates of TSpatialPosition",position.setCoordinates(pv));

		position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS));     

		ensure_distance("CCS X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(1200.67), static_cast<TReal>(0.01)); 
		ensure_distance("CCS Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(2077.57), static_cast<TReal>(0.01));
		ensure_distance("CCS Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(2481.52), static_cast<TReal>(0.01));   
	}

	template<>
	template<>
	void object::test<15>()
	{
		set_test_name("Transforming geodetic to geocentric coordinates");

		TAngle latitude(46.25695113844469, TAngle::kDeciDegs);
		TAngle longitude(6.06056092735124, TAngle::kDeciDegs);

		TPositionVector pvGeodetic(latitude.getRadiansValue(), longitude.getRadiansValue(), 525.932, TCoordSysFactory::kGeodetic);

		TAReferenceFrame *rgf93(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kRGF93));
		TSpatialPosition *position = new TSpatialPosition(rgf93);
		ensure("Setting the coordinates of TSpatialPosition", position->setCoordinates(pvGeodetic));
		TSpatialPoint spPoint("Point");
		spPoint.setPosition(position);
		TPositionVector pvCartesian = spPoint.getPosition().getCoordinates(TCoordSysFactory::k3DCartesian);

		// Comparison with the PROJ command: "6.06056092735124 46.25695113844469 525.932" | cct - d 10 + proj = cart + ellps = GRS80
		// That gives: 4393400.8200132158  466460.6261707481  4585421.5726383748
		ensure_equals("RGF93 X", pvCartesian.getX().getMetresValue(), static_cast<TReal>(4393400.8200132158), static_cast<TReal>(1e-9));
		ensure_equals("RGF93 Y", pvCartesian.getY().getMetresValue(), static_cast<TReal>(466460.6261707481), static_cast<TReal>(1e-9));
		ensure_equals("RGF93 Z", pvCartesian.getZ().getMetresValue(), static_cast<TReal>(4585421.5726383748), static_cast<TReal>(1e-9));
	}
	}
