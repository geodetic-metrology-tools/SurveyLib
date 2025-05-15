// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <TOptionsCheck.h>

#include <PlainTransform.h> // Move EStatus to separate file
#include <TPlainDataParameters.h>
#include <TDataParameters.h>

#include <tut/tut.hpp>

namespace tut
{
    struct test_TOptionsCheck
    {
        TPlainDataParameters inputParams;
        TPlainDataParameters outputParams;

        test_TOptionsCheck()
        {
			inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kITRF97;
			inputParams.fCoordSys = TCoordSysFactory::k3DCartesian; 
			inputParams.fAngUnits = TAngle::kGons;

		    outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kETRF93;
			outputParams.fCoordSys = TCoordSysFactory::k3DCartesian;
			outputParams.fAngUnits = TAngle::kGons;
        }
    };
    typedef test_group<test_TOptionsCheck> factory;
    typedef factory::object object;
}

namespace
{
    tut::factory tf("Test of csgeoDLL TOptionsCheck functionality");
}

namespace tut
{
    /*! Testing valid options */
	template<>
    template<>
    void object::test<1>()
    {

        TOptionsCheck options(inputParams,NULL,outputParams,NULL);
        // These options are correct. Nothing exceptional should ever happen.
        ensure_equals("Valid input Reference Frame enum",
            options.getInputDataParameters().getRefFrameEnumerator(), TRefSystemFactory::kITRF97);
        ensure_equals("Valid input coordinate system", 
            options.getInputDataParameters().getCoordinateSystem(), TCoordSysFactory::k3DCartesian);
        ensure_equals("Valid input angle units",
            options.getInputDataParameters().getAngleUnits(), TAngle::kGons);

        ensure_equals("Valid output Reference Frame enum",
            options.getOutputDataParameters().getRefFrameEnumerator(), TRefSystemFactory::kETRF93);
        ensure_equals("Valid output coordinate system", 
            options.getOutputDataParameters().getCoordinateSystem(), TCoordSysFactory::k3DCartesian);
        ensure_equals("Valid output angle units",
            options.getOutputDataParameters().getAngleUnits(), TAngle::kGons);
    }

    /*! Testing invalid kInvalidInputRefFrame */
    template<>
    template<>
    void object::test<2>()
    {
        inputParams.fRefFrame = -1;
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kInvalidInputRefFrame", e, kInvalidInputRefFrame);
        }
    }
    /*! Testing invalid kInvalidOutputRefFrame */
    template<>
    template<>
    void object::test<3>()
    {
        outputParams.fRefFrame = -1;
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kInvalidOutputRefFrame", e, kInvalidOutputRefFrame);
        }
    }
    /*! Testing invalid kInvalidInputCoordSys */
    template<>
    template<>
    void object::test<4>()
    {

        inputParams.fCoordSys = -1; // this is invalid
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kInvalidInputCoordSys", e, kInvalidInputCoordSys);
        }
    }
    /*! Testing invalid kInvalidOutputCoordSys */
    template<>
    template<>
    void object::test<5>()
    {

        outputParams.fCoordSys = -1; // this is invalid
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kInvalidOutputCoordSys", e, kInvalidOutputCoordSys);
        }
    }
    /*! Testing invalid kMissingInputLSO */
    template<>
    template<>
    void object::test<6>()
    {
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kMLA1985Machine;
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kMissingInputLSO", e, kMissingInputLSO);
        }
    }
    /*! Testing invalid kMissingOutputLSO */
    template<>
    template<>
    void object::test<7>()
    {
		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kMLA1985Machine;
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kMissingOutputLSO", e, kMissingOutputLSO);
        }
    }
    /*! Testing invalid kSuperfluousInputLSO */
	template<>
    template<>
    void object::test<8>()
    {
        TPlainLocalSystemOrigin ori;
        try
        {
            TOptionsCheck options(inputParams,&ori,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kSuperfluousInputLSO", e, kSuperfluousInputLSO);
        }
    }
    /*! Testing invalid kSuperfluousOutputLSO */
    template<>
    template<>
    void object::test<9>()
    {
        TPlainLocalSystemOrigin ori;
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,&ori);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kSuperfluousOutputLSO", e, kSuperfluousOutputLSO);
        }
    }
    /*! Testing invalid kInvalidInputAngUnits */
    template<>
    template<>
    void object::test<10>()
    {
        inputParams.fAngUnits = -1; // this is invalid
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kInvalidInputAngUnits", e, kInvalidInputAngUnits);
        }
    }
    /*! Testing invalid kInvalidOutputAngUnits */
	template<>
    template<>
    void object::test<11>()
    {
        outputParams.fAngUnits = -1; // this is invalid
        try
        {
            TOptionsCheck options(inputParams,NULL,outputParams,NULL);
            ensure("Should have thrown", false);
        }
        catch (EStatusCode e)
        {
            ensure_equals("expected kInvalidOutputAngUnits", e, kInvalidOutputAngUnits);
        }
    }
	/*! Testing invalid kMissingInputEpoch */
	template<>
	template<>
	void object::test<12>()
	{
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kITRFin;
		inputParams.fSolution = "ITRF 2014";
		try
		{
			TOptionsCheck options(inputParams, NULL, outputParams, NULL);
			ensure("Should have thrown", false);
		}
		catch (EStatusCode e)
		{
			ensure_equals("expected kMissingInputEpoch", e, kMissingInputEpoch);
		}
	}
	/*! Testing invalid kMissingOutputEpoch */
	template<>
	template<>
	void object::test<13>()
	{
		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kITRFout;
		outputParams.fSolution = "ITRF 2014";
		try
		{
			TOptionsCheck options(inputParams, NULL, outputParams, NULL);
			ensure("Should have thrown", false);
		}
		catch (EStatusCode e)
		{
			ensure_equals("expected kMissingOutputEpoch", e, kMissingOutputEpoch);
		}
	}
	/*! Testing invalid kMissingInputSolution */
	template<>
	template<>
	void object::test<14>()
	{
		inputParams.fRefFrame = TRefSystemFactory::ERefFrame::kETRFin;
		inputParams.fEpoch = 2022.5;
		try
		{
			TOptionsCheck options(inputParams, NULL, outputParams, NULL);
			ensure("Should have thrown", false);
		}
		catch (EStatusCode e)
		{
			ensure_equals("expected kMissingInputSolution", e, kMissingInputSolution);
		}
	}
	/*! Testing invalid kMissingOutputSolution */
	template<>
	template<>
	void object::test<15>()
	{
		outputParams.fRefFrame = TRefSystemFactory::ERefFrame::kETRFout;
		outputParams.fEpoch = 2022.5;
		try
		{
			TOptionsCheck options(inputParams, NULL, outputParams, NULL);
			ensure("Should have thrown", false);
		}
		catch (EStatusCode e)
		{
			ensure_equals("expected kMissingOutputSolution", e, kMissingOutputSolution);
		}
	}
	/*! Testing inconsistent coordinate system */
	template<>
	template<>
	void object::test<16>()
	{
		outputParams.fCoordSys = TRefSystemFactory::ERefFrame::kITRF97; //(ETRF93 is not a 2D+H system)
		try
		{
			TOptionsCheck options(inputParams, NULL, outputParams, NULL);
			ensure("Should have thrown", false);
		}
		catch (EStatusCode e)
		{
			ensure_equals("expected kInvalidOutputCoordSys", e, kInvalidOutputCoordSys);
		}
	}
}
