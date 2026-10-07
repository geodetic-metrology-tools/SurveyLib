// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdexcept>

#include <tut/tut.hpp>
#include <tut/tut_macros.hpp>

#include <GeodeticConstants.h>
#include <TCernParabolicGeoid.h>
#include <TRefFrameInfo.h>
#include <TRefSystemFactory.h>
#include <TSpatialPosition.h>

namespace tut
{
struct test_ParabolicGeoid
{
};
typedef test_group<test_ParabolicGeoid> factory;
factory testCernParabolicGeoid("Test of parabolic geoid");
typedef factory::object object;

template<>
template<>
void object::test<1>()
{
	set_test_name("Test N, Eta, Xi and DAlpha at P0 (must be 0)");
	TPositionVector p0(XP0, YP0, ZP0, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS), p0);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG1985Machine));
	ensure_equals("N P0 is zero", geoidModel->getN(position).getMetresValue(), 0.0);
	ensure_equals("Eta P0 is zero", geoidModel->getEta(position).getRadiansValue(), 0.0);
	ensure_equals("Xi P0 is zero", geoidModel->getXi(position).getRadiansValue(), 0.0);
	ensure_equals("DAlpha P0 is zero", geoidModel->getDAlpha(position).getRadiansValue(), 0.0);
}
} // namespace tut
