/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef CSGEODLL_T_OPTIONS_CHECK_H_acaac7fcab6442d681b471fa1f8d9ec5
#define CSGEODLL_T_OPTIONS_CHECK_H_acaac7fcab6442d681b471fa1f8d9ec5

#include <TDataParameters.h>
#include <utils/TGlobalDefs.h>

struct TPlainDataParameters;
struct TPlainLocalSystemOrigin;

/**
 * Class containing the logic for validating the parameters
 * passed to the DLL functions.
 * As DLL users can only pass parameters in form of simple types
 * and structs, it is necessary to convert them into the types
 * that are being used by SurveyLib.
 */
class SU_DECLSPEC TOptionsCheck
{
public:
    /**
     * Attempt to validate the parameters and populate the resulting
     * TDataParameters.
     * \throw EStatusCode on error
     */
    TOptionsCheck(
        const TPlainDataParameters & inputParams,
        const TPlainLocalSystemOrigin * inputLSO,
        const TPlainDataParameters & outputParams,
        const TPlainLocalSystemOrigin * outputLSO);
    const TDataParameters & getInputDataParameters() const;
    const TDataParameters & getOutputDataParameters() const;
private:
    TDataParameters fInputDataParameters;
    TDataParameters fOutputDataParameters;
};

#endif
