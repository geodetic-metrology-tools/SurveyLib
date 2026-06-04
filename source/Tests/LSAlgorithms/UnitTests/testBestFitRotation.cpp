// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <tut/tut.hpp>

#include <BestFitRotationFns.h>
#include <TRotation.h>
#include <TRotationMatrix.h>

#include <Eigen/Dense>

#include <cmath>
#include <vector>

namespace tut
{
struct test_bestFitRotation
{
};
typedef test_group<test_bestFitRotation> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test bestFitRotation");

void ensureMatrixClose(const char *label, const Eigen::Matrix3d &actual, const Eigen::Matrix3d &expected, double tol)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			tut::ensure_equals(label, actual(i, j), expected(i, j), tol);
		}
	}
}
} // namespace

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("pair overload: identity when src == dst");

	std::vector<Eigen::Vector3d> src{ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
	std::vector<Eigen::Vector3d> dst = src;

	bool ok = false;
	const Eigen::Matrix3d R = bestFitRotation(src, dst, ok);

	ensure("ok", ok);
	ensureMatrixClose("identity", R, Eigen::Matrix3d::Identity(), 1e-12);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("pair overload: round-trips a known rotation");

	// A non-trivial rotation: 0.3 rad about z.
	const double c = std::cos(0.3);
	const double s = std::sin(0.3);
	Eigen::Matrix3d R0;
	R0 << c, -s, 0,
	      s,  c, 0,
	      0,  0, 1;

	std::vector<Eigen::Vector3d> src{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
		Eigen::Vector3d(1, 1, 0).normalized(),
	};
	std::vector<Eigen::Vector3d> dst;
	dst.reserve(src.size());
	for (const auto &v : src)
		dst.emplace_back(R0 * v);

	bool ok = false;
	const Eigen::Matrix3d R = bestFitRotation(src, dst, ok);

	ensure("ok", ok);
	ensureMatrixClose("recovered matrix", R, R0, 1e-10);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("pair overload: fails on size mismatch");

	std::vector<Eigen::Vector3d> src{ { 1, 0, 0 }, { 0, 1, 0 } };
	std::vector<Eigen::Vector3d> dst{ { 1, 0, 0 } };

	bool ok = true;
	bestFitRotation(src, dst, ok);
	ensure("not ok", !ok);
}

template<>
template<>
void object::test<4>()
{
	set_test_name("pair overload: fails with fewer than two pairs");

	std::vector<Eigen::Vector3d> src{ { 1, 0, 0 } };
	std::vector<Eigen::Vector3d> dst{ { 0, 1, 0 } };

	bool ok = true;
	bestFitRotation(src, dst, ok);
	ensure("not ok", !ok);
}

template<>
template<>
void object::test<5>()
{
	set_test_name("pair overload: fails on collinear inputs");

	// Two parallel src vectors leave the rotation about that axis undetermined;
	// only the largest singular value of H is non-zero, the others collapse.
	std::vector<Eigen::Vector3d> src{ { 1, 0, 0 }, { 2, 0, 0 } };
	std::vector<Eigen::Vector3d> dst{ { 0, 1, 0 }, { 0, 2, 0 } };

	bool ok = true;
	bestFitRotation(src, dst, ok);
	ensure("not ok", !ok);
}

template<>
template<>
void object::test<6>()
{
	set_test_name("pair overload: reflection-prone inputs yield det = +1");

	// Coplanar pairs where the naive SVD product can yield det = -1 unless the
	// reflection-fix term is applied.
	std::vector<Eigen::Vector3d> src{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		Eigen::Vector3d(1, 1, 0).normalized(),
	};
	std::vector<Eigen::Vector3d> dst{
		{ -1, 0, 0 },
		{ 0, -1, 0 },
		Eigen::Vector3d(-1, -1, 0).normalized(),
	};

	bool ok = false;
	const Eigen::Matrix3d R = bestFitRotation(src, dst, ok);
	ensure("ok", ok);
	ensure_equals("det(R) is +1, not a reflection", R.determinant(), 1.0, 1e-10);

	for (size_t i = 0; i < src.size(); ++i)
	{
		const Eigen::Vector3d rotated = R * src[i];
		ensure_equals("dst x", rotated(0), dst[i](0), 1e-10);
		ensure_equals("dst y", rotated(1), dst[i](1), 1e-10);
		ensure_equals("dst z", rotated(2), dst[i](2), 1e-10);
	}
}

template<>
template<>
void object::test<7>()
{
	set_test_name("matrix overload: recovers rotation from constructed H");

	// Build H = sum src_i * dst_i^T directly with a known R0, then call the
	// H-overload. Exercises the kernel without going through the pair API.
	const double c = std::cos(0.2);
	const double s = std::sin(0.2);
	Eigen::Matrix3d R0;
	R0 << 1, 0, 0,
	      0, c, -s,
	      0, s,  c;

	std::vector<Eigen::Vector3d> src{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
	};
	Eigen::Matrix3d H = Eigen::Matrix3d::Zero();
	for (const auto &v : src)
		H += v * (R0 * v).transpose();

	bool ok = false;
	const Eigen::Matrix3d R = bestFitRotation(H, ok);

	ensure("ok", ok);
	ensureMatrixClose("recovered matrix", R, R0, 1e-10);
}

template<>
template<>
void object::test<8>()
{
	set_test_name("matrix overload: fails on rank-deficient H");

	// H built from a single outer product has only one non-zero singular value.
	const Eigen::Matrix3d H = Eigen::Vector3d(1, 0, 0) * Eigen::Vector3d(0, 1, 0).transpose();

	bool ok = true;
	bestFitRotation(H, ok);
	ensure("not ok", !ok);
}

template<>
template<>
void object::test<9>()
{
	set_test_name("makeBestFitRotation wraps the result into an initialised TRotation");

	// Smoke test for the TRotation wrapper. Confirms the packing into
	// TRotationMatrix preserves the recovered rotation.
	TRotation r0(TRotationMatrix::kRzyx, 0.1, -0.2, 0.3);
	const Eigen::Matrix3d m0 = r0.getRotationMatrix().getMat();

	std::vector<Eigen::Vector3d> src{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
	};
	std::vector<Eigen::Vector3d> dst;
	dst.reserve(src.size());
	for (const auto &v : src)
		dst.emplace_back(m0 * v);

	bool ok = false;
	TRotation r = makeBestFitRotation(src, dst, ok);

	ensure("ok", ok);
	ensure("initialised", r.getRotationMatrix().isInitialise());
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ensure_equals("element", r.getRotationMatrix().getElt(i, j), r0.getRotationMatrix().getElt(i, j), 1e-10);
}

template<>
template<>
void object::test<10>()
{
	set_test_name("makeBestFitRotation propagates ok = false on failure");

	std::vector<Eigen::Vector3d> src{ { 1, 0, 0 } };
	std::vector<Eigen::Vector3d> dst{ { 0, 1, 0 } };

	bool ok = true;
	makeBestFitRotation(src, dst, ok);
	ensure("not ok", !ok);
}
} // namespace tut
