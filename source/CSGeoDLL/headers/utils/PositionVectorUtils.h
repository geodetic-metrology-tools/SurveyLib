/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CSGEODLL_POSITION_VECTOR_UTILS_H_e1f47af6538b4dd9bb47c4ffeff0fa0c
#define CSGEODLL_POSITION_VECTOR_UTILS_H_e1f47af6538b4dd9bb47c4ffeff0fa0c

#include <TPositionVector.h>

class TSpatialPosition;
class TDataParameters;

namespace utils
{
    /**
     * Function for building a SurveyLib TPositionVector in a given
     * coordinate system from the provided points.
     * RATIONALE: SurveyLib provides functionality for transforming
     *     a TSpatialPoint from one reference frame to another. However
     *     the user of the DLL cannot pass a TSpatialPoint. Thus it is
     *     necessary to build the TPositionVector comprising the TSpatialPoint.
     *     There are three possible coordinate systems.
     */
    TPositionVector getPositionVector(
        double x_long, double y_lat, double z_h, 
        const TDataParameters & dp);
    

    /**
     * Function for extracting raw coordinates in a given coordinate system
     * from the provided TSpatialPosition.
     * This function basically does the inverse operation to the getPositionVector
     */
    void extractCoordinates(
        const TSpatialPosition & position,
        double * x_long, double * y_lat, double * z_h,
        const TDataParameters & dp);
}

#endif
