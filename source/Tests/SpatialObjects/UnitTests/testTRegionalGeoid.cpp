// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <tut/tut.hpp>


namespace tut
{
struct test_TRegionalGeoid
{
};
typedef test_group<test_TRegionalGeoid> factory;
typedef factory::object object;
}

namespace
{
tut::factory tf("Test TLV95Transformation class");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{




}

} // namespace tut
