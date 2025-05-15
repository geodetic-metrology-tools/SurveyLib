// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <TOptionsCheck.h>
#include <PlainTransform.h>
#include <utils/PositionVectorUtils.h>
#include <TPlainDataParameters.h>
#include <TRefFrameInfo.h>
#include <array>

namespace
{
    void errorMessage(const std::string & msg, EStatusCode code);
    void setDataParameters(
        TDataParameters & dp,
        const TPlainDataParameters & plainParams,
        const TPlainLocalSystemOrigin * LSO);
}

TOptionsCheck::TOptionsCheck(const TPlainDataParameters & inputParams, 
                             const TPlainLocalSystemOrigin * inputLSO,
                             const TPlainDataParameters & outputParams,
                             const TPlainLocalSystemOrigin * outputLSO)
{
    // Check the input reference frame related parameters:
	if(!TRefFrameInfo::isValidNumber(inputParams.fRefFrame))
        errorMessage("Invalid input reference frame number",kInvalidInputRefFrame);
    // Check if the valid coordinate system has been given
    if(inputParams.fCoordSys!=TCoordSysFactory::k3DCartesian
        && inputParams.fCoordSys!=TCoordSysFactory::kGeodetic
        && inputParams.fCoordSys!=TCoordSysFactory::k2DPlusH
    )
        errorMessage("Invalid input coordinate system number",kInvalidInputCoordSys);
    else if(!TRefFrameInfo::isCoordSysAllowed(inputParams.fRefFrame, static_cast<TCoordSysFactory::ECoordSys>(inputParams.fCoordSys)))
        errorMessage("Specified input coordinate system is not allowed for the given reference frame", kInvalidInputCoordSys);
    // Angular units
    if(inputParams.fAngUnits!=TAngle::kRadians 
        && inputParams.fAngUnits!=TAngle::kGons
        && inputParams.fAngUnits!=TAngle::kDeciDegs
    )
        errorMessage("Invalid input angle units number", kInvalidInputAngUnits);
    // We need LSO information for Local Reference Frames
    if(TRefFrameInfo::isLocalRefFrame(inputParams.fRefFrame) && inputLSO==NULL)
        errorMessage("Input LSO information required for the given input reference frame",kMissingInputLSO);
    // But it should not be present for the other reference frames
    if(!TRefFrameInfo::isLocalRefFrame(inputParams.fRefFrame) && inputLSO!=NULL)
        errorMessage("No input LSO information should be specified for the given input reference frame",kSuperfluousInputLSO);    
    // We need solution and epoch for terrestrial Reference Frame
	if (TRefFrameInfo::isTerrestrialRefFrame((inputParams.fRefFrame)) && std::isnan(inputParams.fEpoch))
        errorMessage("Input Epoch information required for the given input reference frame", kMissingInputEpoch);
    if (TRefFrameInfo::isTerrestrialRefFrame((inputParams.fRefFrame)) && std::string(inputParams.fSolution) == "")
        errorMessage("Input Solution information required for the given input reference frame", kMissingInputSolution);
	// For terrestrial reference frame we check if it's ITRFout or ETRFout and not ITRFin or ETRFin
	if (TRefFrameInfo::isTerrestrialRefFrame((inputParams.fRefFrame)) && inputParams.fRefFrame == TRefSystemFactory::ERefFrame::kITRFout)
		errorMessage("Wrong input terrestrial reference frame, use 13 (kITRFin) instead", kBadInputTRF);
	if (TRefFrameInfo::isTerrestrialRefFrame((inputParams.fRefFrame)) && inputParams.fRefFrame == TRefSystemFactory::ERefFrame::kETRFout)
		errorMessage("Wrong input terrestrial reference frame, use 15 (kETRFin) instead", kBadInputTRF);

    // Check the output reference frame related parameters:
	if(!TRefFrameInfo::isValidNumber(outputParams.fRefFrame))
        errorMessage("Invalid output reference frame number",kInvalidOutputRefFrame);
    // Check if the valid coordinate system has been given
    if(outputParams.fCoordSys!=TCoordSysFactory::k3DCartesian
        && outputParams.fCoordSys!=TCoordSysFactory::kGeodetic
        && outputParams.fCoordSys!=TCoordSysFactory::k2DPlusH
    )
        errorMessage("Invalid output coordinate system number",kInvalidOutputCoordSys);
    else if(!TRefFrameInfo::isCoordSysAllowed(outputParams.fRefFrame, static_cast<TCoordSysFactory::ECoordSys>(outputParams.fCoordSys)))
        errorMessage("Specified output coordinate system is not allowed for the given reference frame", kInvalidOutputCoordSys);
    // Angular units
    if(outputParams.fAngUnits!=TAngle::kRadians 
        && outputParams.fAngUnits!=TAngle::kGons
		&& outputParams.fAngUnits!=TAngle::kDeciDegs
    )
        errorMessage("Invalid output angle units number", kInvalidOutputAngUnits);
    // We need LSO information for Local Reference Frames
    if(TRefFrameInfo::isLocalRefFrame(outputParams.fRefFrame) && outputLSO==NULL)
        errorMessage("Output LSO information required for the given output reference frame",kMissingOutputLSO);
    // But it should not be present for the other reference frames
    if(!TRefFrameInfo::isLocalRefFrame(outputParams.fRefFrame) && outputLSO!=NULL)
        errorMessage("No output LSO information should be specified for the given output reference frame",kSuperfluousOutputLSO);
    // We need solution and epoch for terrestrial Reference Frame
	if (TRefFrameInfo::isTerrestrialRefFrame((outputParams.fRefFrame)) && std::isnan(outputParams.fEpoch))
        errorMessage("Input Epoch information required for the given output reference frame", kMissingOutputEpoch);
	if (TRefFrameInfo::isTerrestrialRefFrame((outputParams.fRefFrame)) && std::string(outputParams.fSolution) == "")
        errorMessage("Input Solution information required for the given output reference frame", kMissingOutputSolution);
	// For terrestrial reference frame we check if it's ITRFout or ETRFout and not ITRFin or ETRFin
	if (TRefFrameInfo::isTerrestrialRefFrame((outputParams.fRefFrame)) && outputParams.fRefFrame == TRefSystemFactory::ERefFrame::kITRFin)
		errorMessage("Wrong output terrestrial reference frame, use 14 (kITRFout) instead", kBadOutputTRF);
	if (TRefFrameInfo::isTerrestrialRefFrame((outputParams.fRefFrame)) && outputParams.fRefFrame == TRefSystemFactory::ERefFrame::kETRFin)
		errorMessage("Wrong output terrestrial reference frame, use 16 (kETRFout) instead", kBadOutputTRF);


    setDataParameters(fInputDataParameters, inputParams, inputLSO);
    setDataParameters(fOutputDataParameters, outputParams, outputLSO);
}

const TDataParameters & TOptionsCheck::getInputDataParameters() const
{
    return fInputDataParameters;
}

const TDataParameters & TOptionsCheck::getOutputDataParameters() const
{
    return fOutputDataParameters;
}

namespace
{
    std::array<std::string, 13>listITRF = { "ITRF 88", "ITRF 89", "ITRF 90", "ITRF 91", "ITRF 92", "ITRF 93", "ITRF 94", "ITRF 96", "ITRF 97", "ITRF 2000", "ITRF 2005", "ITRF 2008", "ITRF 2014" };
	std::array<std::string, 13> listETRF = {"ETRF 89", "ETRF 90", "ETRF 91", "ETRF 92", "ETRF 93", "ETRF 94", "ETRF 96", "ETRF 97", "ETRF 2000", "ETRF 2005", "ETRF 2014"};

    void errorMessage(const std::string & msg, EStatusCode code)
    {
        std::cerr << std::endl << "CSGEODLL: " << msg << std::endl;
        //if (code != kSuperfluousInputLSO && code != kSuperfluousOutputLSO)
			throw code;
    }
    void setDataParameters(
        TDataParameters & dp,
        const TPlainDataParameters & plainParams,
        const TPlainLocalSystemOrigin * LSO)
    {
        // Populate the TDataParameters
        if(!dp.setRefFrame(TRefFrameInfo::fromNumber(plainParams.fRefFrame)))
            errorMessage("setRefFrame returned false",kCannotSetupTDataParameters);
        // Static cast legal, as we have checked earlier that the number corresponds to valid enum
        if(!dp.setCoordSys(static_cast<TCoordSysFactory::ECoordSys>(plainParams.fCoordSys)))
            errorMessage("setCoordSys returned false",kCannotSetupTDataParameters);
        if(!dp.setAngUnits(static_cast<TAngle::EUnits>(plainParams.fAngUnits)))
            errorMessage("setAngUnits returned false",kCannotSetupTDataParameters);		
		// Create the TLocalSystemOrigin if needed
		if (LSO != NULL)
		{
			TAngle gisement(LSO->fGisement * GON2RAD);
			TAngle slope(LSO->fSlope);
			TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS), LSO->fX, LSO->fY, LSO->fZ, TCoordSysFactory::k3DCartesian);
			TLocalSystemOrigin localSystemOrigin(position, gisement, slope);

			if (TRefFrameInfo::isLocalRefFrame(plainParams.fRefFrame) && !dp.setLocalSystemOrigin(localSystemOrigin))
				errorMessage("setLocalSystemOrigin returned false", kCannotSetupTDataParameters);
		}
		// Populate solution and epoch if needed
        if (TRefFrameInfo::isTerrestrialRefFrame(plainParams.fRefFrame))
        {
            dp.setCoordEpoch(plainParams.fEpoch);
        
            if (plainParams.fRefFrame == TRefSystemFactory::ERefFrame::kITRFin ||
				plainParams.fRefFrame == TRefSystemFactory::ERefFrame::kITRFout)
            {
                if (std::find(std::begin(listITRF), std::end(listITRF), std::string(plainParams.fSolution)) != std::end(listITRF))
                    dp.setSolution(plainParams.fSolution);
                else
                    errorMessage("ITRF solution " + std::string(plainParams.fSolution) + " not supported", kCannotSetupTDataParameters);
            }
			else if ((plainParams.fRefFrame == TRefSystemFactory::ERefFrame::kETRFin ||
					  plainParams.fRefFrame == TRefSystemFactory::ERefFrame::kETRFout))
            {
				if (std::find(std::begin(listETRF), std::end(listETRF), std::string(plainParams.fSolution)) != std::end(listETRF))
                    dp.setSolution(plainParams.fSolution);
                else
					errorMessage("ETRF solution " + std::string(plainParams.fSolution) + " not supported", kCannotSetupTDataParameters);
            }      
        }           
    }
}
