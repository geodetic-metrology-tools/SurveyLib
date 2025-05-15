// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <tut/tut.hpp>

#include "TDist.h"

namespace tut
{
struct test_TDist
{
};
typedef test_group<test_TDist> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test TDist");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Test dist3D with zero distance");

	TPositionVector p1(0, 0, 0, TCoordSysFactory::k3DCartesian);
	TPositionVector p2(0, 0, 0, TCoordSysFactory::k3DCartesian);

	TReal result = dist3D(p1, p2);

	ensure_equals("Distance should be zero", result, 0);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("Test dist3D with unit distance along x-axis");

	TPositionVector p1(0, 0, 0, TCoordSysFactory::k3DCartesian);
	TPositionVector p2(1, 0, 0, TCoordSysFactory::k3DCartesian);

	TReal result = dist3D(p1, p2);

	ensure_equals("Distance should be 1", result, 1.0);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Test dist3D with arbitrary points");

	TPositionVector p1(1, 2, 3, TCoordSysFactory::k3DCartesian);
	TPositionVector p2(4, 5, 6, TCoordSysFactory::k3DCartesian);

	TReal result = dist3D(p1, p2);
	TReal expected = std::sqrt(27); // sqrt((4-1)^2 + (5-2)^2 + (6-3)^2)

	ensure_equals("Distance should be sqrt(27)", result, expected);
}

} // namespace tut
