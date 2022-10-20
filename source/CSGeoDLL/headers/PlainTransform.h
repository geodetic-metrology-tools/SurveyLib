#ifndef CSGEODLL_PLAIN_TRANSFORM_H_d7ce960c186c42ecb9f59ecaff70b1bb
#define CSGEODLL_PLAIN_TRANSFORM_H_d7ce960c186c42ecb9f59ecaff70b1bb

#include <utils/TGlobalDefs.h>

struct TPlainDataParameters;
struct TPlainLocalSystemOrigin;


/**
 * Transform the point from one reference frame to another.
 *
 * NOTE: The coordinates will be interpreted according to the
 *       parameters passed in TPlainDataParameters:
 *   - k3DCartesian - expects x, y and z coordinates in METRES!
 *   - kGeodetic - expects lambda (longitude), phi (latitude) and h (ellipsoidal or orthometric) coordinates in GONS or DECIMAL DEGREE and METRES respectively
 *   - k2DPlusH - expects x, y and h coordinates in METRES
 *   - Same rule applies for the output.
 * NOTE: Input coordinates are being overwritten!
 *
 * \param[in,out] x_long First coordinate of the point to be tranformed (X, Easting or longitude)
 * \param[in,out] y_lat Second coordinate of the point to be tranformed (Y, Northing or latitude)
 * \param[in,out] z_h Third coordinate of the point to be tranformed (Z or Height)
 * \param[in] inputParams parameters describing the input point
 * \param[in] inputLSO optional parameter for passing the information about
 *                     the local system origin needed for the MLA systems
 * \param[in] outputParams parameters describing the output point
 * \param[in] outputLSO optional parameter for passing the information about
 *                     the local system origin needed for the MLA systems
 * \return Status code - values defined in EStatusCode
 */
extern "C" SU_DECLSPEC int DLLAPI transformPoint(
	double * x_long, double * y_lat, double * z_h,
	const TPlainDataParameters * inputParams,
    const TPlainLocalSystemOrigin * inputLSO,
	const TPlainDataParameters * outputParams,
    const TPlainLocalSystemOrigin * outputLSO
	);

enum EStatusCode
{
    kOk = 0,
    kInvalidInputRefFrame = 1,
    kInvalidOutputRefFrame = 2,
    kInvalidInputCoordSys = 3,
    kInvalidOutputCoordSys = 4,
    kMissingInputLSO = 5,
    kMissingOutputLSO = 6,
    kSuperfluousInputLSO = 7,
    kSuperfluousOutputLSO = 8,
    kInvalidInputAngUnits = 9,
    kInvalidOutputAngUnits = 10,
    kCannotSetupTDataParameters = 11,
	kTransformError = 12,
    kMissingInputEpoch = 13,
    kMissingInputSolution = 14,
    kMissingOutputEpoch = 15,
    kMissingOutputSolution = 16,
	kBadInputTRF = 17,
	kBadOutputTRF = 18
};

#endif
