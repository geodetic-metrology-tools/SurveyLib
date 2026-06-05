/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// BestFitRotationFns.h
//
// SVD-based best-fit rotation (Kabsch algorithm), shared by
// TSparseKabschFitter::computeRotMatrx and by callers that want the result as a TRotation
// (see makeBestFitRotation).

#ifndef SU_BEST_FIT_ROTATION_FNS
#define SU_BEST_FIT_ROTATION_FNS

#if _MSC_VER >= 1000
#	pragma once
#endif // _MSC_VER >= 1000

#include <vector>

#include <Eigen/Dense>

#include "TRotation.h"

/*! \ingroup CalcAlternatives
	@{*/

/*! \brief Best-fit rotation from a 3x3 cross-covariance matrix.

	Given H = sum_i src_i * dst_i^T, returns R minimising
	sum_i || R * src_i - dst_i ||^2 (Kabsch via SVD). The reflection branch
	corrects the sign so that det(R) = +1.

	\param H   3x3 cross-covariance
	\param ok  set to true on success, false when the second singular value of
			   H is below 1e-6 (degenerate / collinear inputs). On failure the
			   returned matrix is the identity.
*/
Eigen::Matrix3d bestFitRotation(const Eigen::Matrix3d &H, bool &ok);

/*! \brief Best-fit rotation aligning paired direction vectors.

	Convenience overload: assembles H = sum_i src_i * dst_i^T and delegates to
	the matrix overload.

	\param src source direction vectors expressed in a common Cartesian frame
	\param dst target direction vectors (same size as src)
	\param ok  set to true on success, false when sizes mismatch, fewer than
			   two pairs are supplied, or the H-overload reports degeneracy.
			   On failure the returned matrix is the identity.
*/
Eigen::Matrix3d bestFitRotation(const std::vector<Eigen::Vector3d> &src, const std::vector<Eigen::Vector3d> &dst, bool &ok);

/*! \brief Best-fit rotation aligning paired direction vectors, packaged as TRotation.

	Convenience wrapper for callers that want a TRotation rather than a raw
	3x3 matrix. Delegates to the std::vector bestFitRotation overload and
	packs the result.

	\param src source direction vectors expressed in a common Cartesian frame
	\param dst target direction vectors (same size as src)
	\param ok  forwarded from the underlying bestFitRotation. On failure the
			   returned TRotation is default-constructed.
*/
TRotation makeBestFitRotation(const std::vector<Eigen::Vector3d> &src, const std::vector<Eigen::Vector3d> &dst, bool &ok);

/*@}*/

#endif // SU_BEST_FIT_ROTATION_FNS
