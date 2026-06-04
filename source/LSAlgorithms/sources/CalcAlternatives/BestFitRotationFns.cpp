// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "BestFitRotationFns.h"

#include <Eigen/SVD>

#include "TRotationMatrix.h"

Eigen::Matrix3d bestFitRotation(const Eigen::Matrix3d &H, bool &ok)
{
	ok = false;

	// Kabsch: with H = U * S * V^T, R = V * D * U^T,
	// where D corrects for reflection so det(R) = +1.
	Eigen::JacobiSVD<Eigen::Matrix3d> svd(H, Eigen::ComputeFullU | Eigen::ComputeFullV);

	// Two non-zero singular values are required to fix the rotation;
	// otherwise the directions are collinear and the rotation about the
	// shared axis is undetermined.
	if (svd.singularValues()(1) < 1e-6)
		return Eigen::Matrix3d::Identity();

	Eigen::Matrix3d D = Eigen::Matrix3d::Identity();
	D(2, 2) = (svd.matrixV() * svd.matrixU().transpose()).determinant() > 0 ? 1.0 : -1.0;

	ok = true;
	return svd.matrixV() * D * svd.matrixU().transpose();
}

Eigen::Matrix3d bestFitRotation(const std::vector<Eigen::Vector3d> &src, const std::vector<Eigen::Vector3d> &dst, bool &ok)
{
	ok = false;
	if (src.size() != dst.size() || src.size() < 2)
		return Eigen::Matrix3d::Identity();

	Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
	for (size_t i = 0; i < src.size(); ++i)
		H += src[i] * dst[i].transpose();

	return bestFitRotation(H, ok);
}

TRotation makeBestFitRotation(const std::vector<Eigen::Vector3d> &src, const std::vector<Eigen::Vector3d> &dst, bool &ok)
{
	const Eigen::Matrix3d R = bestFitRotation(src, dst, ok);
	if (!ok)
		return TRotation();

	TRotationMatrix m;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			m.setC(i, j, R(i, j));

	return TRotation(m);
}
