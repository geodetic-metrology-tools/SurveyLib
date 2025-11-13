// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <PlainTransform.h>
#include <TPlainDataParameters.h>

#include <tut/tut.hpp>


namespace tut
{
    struct test_plainTransform{};
    typedef test_group<test_plainTransform> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test of csgeoDLL PlainTransform functionality");
}

namespace tut
{
    /*
    *DLL test with correct data
    */

	template<>
    template<>
    void object::test<1>()
    {
		set_test_name("DLL test with correct data");

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 4; // this corresponds to kITRF97
		inputParams.fCoordSys = 1; // this corresponds to k3DCarthesian
        inputParams.fAngUnits = 1; // this corresponds to kGons

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 7; // this corresponds to kETRF93
		outputParams.fCoordSys = 1; // this corresponds to k3DCartesian
        outputParams.fAngUnits = 1; // this corresponds to kGons

		double x = 4331297.1801;
		double y = 567555.7634;
		double z = 4633133.8516;

		int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);

		ensure_equals("Result code",result, 0);
		ensure_distance(x, 4331297.34291, 0.00001);
		ensure_distance(y, 567555.63549, 0.00001);
		ensure_distance(z, 4633133.71549, 0.00001);
    }

    /*
    *Testing MLA transformations with DLL
    */
    template<>
    template<>
    void object::test<2>()
    {
		set_test_name("Testing transformations from CCS to MLA with DLL");

        TPlainLocalSystemOrigin oLSO;
        
        oLSO.fX = 1686.0;
        oLSO.fY = 2036.7;
        oLSO.fZ = 2434.4;
        oLSO.fGisement = 278.1;
        oLSO.fSlope = 0.0;

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 0; // this corresponds to kCCS
		inputParams.fCoordSys = 1; // this corresponds to k3DCartesian
        inputParams.fAngUnits = 1; // this corresponds to kGons

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 1000; // this corresponds to kMLA1985Machine
		outputParams.fCoordSys = 1; // this corresponds to k3DCartesian
        outputParams.fAngUnits = 1; // this corresponds to kGons

		double x = 1753.43696;
		double y = 2060.07526;
		double z = 2434.94253;

		int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, &oLSO);
        ensure_equals("Result code",result, 0);
        ensure_distance(x, -0.73802, 0.00001);
		ensure_distance(y, -71.36950, 0.00001);
		ensure_distance(z, 0.53910, 0.00001);        
    }
	
   /*
    *Testing MLA transformations with DLL
    */
    template<>
    template<>
    void object::test<3>()
    {
		set_test_name("Testing transformations from MLA to CCS with DLL");

        TPlainLocalSystemOrigin iLSO;
        
        iLSO.fX = 1686.0;
        iLSO.fY = 2036.7;
        iLSO.fZ = 2434.4;
        iLSO.fGisement = 278.1;
        iLSO.fSlope = 0.0;

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 1000; // this corresponds to kMLA1985Machine
		inputParams.fCoordSys = 1; // this corresponds to k3DCarthesian
        inputParams.fAngUnits = 1; // this corresponds to kGons

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 0; // this corresponds to kCCS
		outputParams.fCoordSys = 1; // this corresponds to k3DCarthesian
        outputParams.fAngUnits = 1; // this corresponds to kGons

		double x = -0.73802;
		double y = -71.36950;
		double z = 0.53910;

		int result = transformPoint(&x, &y, &z, &inputParams, &iLSO, &outputParams, NULL);
        ensure_equals("Result code",result, 0);
        ensure_distance(x, 1753.43696, 0.00001);
		ensure_distance(y, 2060.07526, 0.00001);
		ensure_distance(z, 2434.94253, 0.00001);        
    }

    /*
    *DLL test with incorrect data
    */
	template<>
    template<>
    void object::test<4>()
    {
		set_test_name("DLL test with incorrect data");

        TPlainDataParameters inputParams;
	    inputParams.fRefFrame = 4; // this corresponds to kITRF97
		inputParams.fCoordSys = 1; // this corresponds to k3DCarthesian
        inputParams.fAngUnits = 1; // this corresponds to kGons

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 1000; // this corresponds to kMLA1985Machine
		outputParams.fCoordSys = 1; // this corresponds to k3DCarthesian
        outputParams.fAngUnits = 1; // this corresponds to kGons

		double x = 4331297.1801;
		double y = 567555.7634;
		double z = 4633133.8516;

		int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);

        ensure_equals("Correct return value", result, kMissingOutputLSO);
    }

	/*
	 *DLL test different angles units
	 */
	template<>
	template<>
	void object::test<5>()
	{
		set_test_name("DLL Gons and Decimal degrees management");

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 4; // this corresponds to kITRF97
		inputParams.fCoordSys = 2; // this corresponds to kGeodetic
		inputParams.fAngUnits = 5; // this corresponds to kDeciDegs
		
		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 4; // this corresponds to kITRF97
		outputParams.fCoordSys = 2; // this corresponds to kGeodetic
		outputParams.fAngUnits = 1; // this corresponds to kGons

		double x = 6.1;
		double y = 46.1;
		double z = 200.0;

		double x_ctrl = x * DEG2RAD * RAD2GON;
		double y_ctrl = y * DEG2RAD * RAD2GON;
		double z_ctrl = z;


		int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);

		ensure_equals("Result code", result, 0);
		ensure_distance("X", x, x_ctrl, 1e-13); // (1e-13 gons ~ 1e-8 m at the surface of the Earth)
		ensure_distance("Y", y, y_ctrl, 1e-13); // (1e-13 gons ~ 1e-8 m at the surface of the Earth)
		ensure_distance("Z", z, z_ctrl, 1e-8);
	}

	/*
	 *DLL test kTransformError
	 */
	template<>
	template<>
	void object::test<6>()
	{
		set_test_name("DLL Generic kTransformError (point outside RAF 20 grid)");

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 209; // this corresponds to kRGF93
		inputParams.fCoordSys = 2; // this corresponds to kGeodetic
		inputParams.fAngUnits = 5; // this corresponds to kDeciDegs

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 208; // this corresponds to KLambert93_raf
		outputParams.fCoordSys = 4; // this corresponds to k2DplusH
		outputParams.fAngUnits = 1; // this corresponds to kGons

		// This point is outside the RAF 20 grid. An error has to be raised
		double x = 15.0;
		double y = 46.0;
		double z = 620.5;

		int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
		ensure_equals("Result code", result, 12);
	}

	#ifdef USE_SWISSTOPO
		/*
	 *DLL test kTransformError
	 */
	template<>
	template<>
	void object::test<7>()
	{
		set_test_name("DLL Generic kTransformError (point outside CHGeo 2004 grid)");

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 210; // this corresponds to CHTRF95
		inputParams.fCoordSys = 2; // this corresponds to kGeodetic
		inputParams.fAngUnits = 5; // this corresponds to kDeciDegs

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 111; // this corresponds to kSwissLV95_ortho
		outputParams.fCoordSys = 4; // this corresponds to k2DplusH
		outputParams.fAngUnits = 1; // this corresponds to kGons

		// This point is outside the CHGeo2004 geoid grid. An error has to be raised
		double x = 15.0;
		double y = 46.0;
		double z = 620.5;

		int result = transformPoint(&x, &y, &z, &inputParams, NULL, &outputParams, NULL);
		ensure_equals("Result code", result, 12);
	}
	#endif

	/*
	 *DLL test MLA to MLA
	 */
	template<>
	template<>
	void object::test<8>()
	{
		set_test_name("Testing transformations from MLA to other MLA with DLL");

        TPlainLocalSystemOrigin iLSO;
		iLSO.fX = 10.0;
		iLSO.fY = 20.0;
		iLSO.fZ = 30.0;
		iLSO.fGisement = 1.0;
		iLSO.fSlope = 0.02;

		TPlainDataParameters inputParams;
		inputParams.fRefFrame = 1000; // this corresponds to kMLA1985Machine
		inputParams.fCoordSys = 1; // this corresponds to k3DCarthesian
		inputParams.fAngUnits = 1; // this corresponds to kGons

		TPlainLocalSystemOrigin oLSO;
		oLSO.fX = 1.0;
		oLSO.fY = 2.0;
		oLSO.fZ = 3.0;
		oLSO.fGisement = 2.0;
		oLSO.fSlope = 0.01;

		TPlainDataParameters outputParams;
		outputParams.fRefFrame = 1000; // this corresponds to kMLA1985Machine
		outputParams.fCoordSys = 1; // this corresponds to k3DCartesian
		outputParams.fAngUnits = 1; // this corresponds to kGons

		double x = -0.73802;
		double y = -71.36950;
		double z = 0.53910;

		int result = transformPoint(&x, &y, &z, &inputParams, &iLSO, &outputParams, &oLSO);
		ensure_equals("Result code", result, 0);
		ensure_distance(x, 8.82089, 0.00001);
		ensure_distance(y, -53.08922, 0.00001);
		ensure_distance(z, 27.53059, 0.00001);   
	}
}

