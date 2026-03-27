// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdexcept>

#include <tut/tut.hpp>
#include <tut/tut_macros.hpp>

#include <GeodeticConstants.h>
#include <TCernGridGeoid.h>
#include <TRefFrameInfo.h>
#include <TRefSystemFactory.h>
#include <TSpatialPosition.h>

namespace tut
{
struct test_CernGridGeoid
{
};
typedef test_group<test_CernGridGeoid> factory;
factory testCernGridGeoid("Test of CERN grid geoid");
typedef factory::object object;

template<>
template<>
void object::test<1>()
{
	set_test_name("Test exception Transforming ITRF to XYHg(RS2k)");
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRF97), 1121473.242, 2492108.804, 479.081, TCoordSysFactory::k3DCartesian);

	ensure_THROW(position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCernXYHg00Machine)), std::runtime_error);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("Test N, Eta, Xi and DAlpha at P0 (must be 0)");
	TPositionVector p0(XP0, YP0, ZP0, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS), p0);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG2000Machine));
	ensure_equals("Eta P0 is zero", geoidModel->getEta(position).getRadiansValue(), 0.0);
	ensure_equals("Xi P0 is zero", geoidModel->getXi(position).getRadiansValue(), 0.0);
	ensure_equals("DAlpha P0 is zero", geoidModel->getDAlpha(position).getRadiansValue(), 0.0);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Test N, Eta, Xi at grid nodes. Must be equal to value in the grid");
	TPositionVector p(-5000.0, 0000.0, ZP0, TCoordSysFactory::k3DCartesian); // p is the lower left valid corner of the grid
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS), p);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG2000Machine));
	ensure_equals("N p is 0.15771 m ", geoidModel->getN(position).getMetresValue(), 0.15771, std::numeric_limits<TReal>::epsilon() * 1e2);
	ensure_equals("Eta p is 25.24 cc", geoidModel->getEta(position).getSignedCCValue(), 25.24, std::numeric_limits<TReal>::epsilon() * 1e2);
	ensure_equals("Xi p is -21.80 cc", geoidModel->getXi(position).getSignedCCValue(), -21.80, std::numeric_limits<TReal>::epsilon() * 1e2);
}

template<>
template<>
void object::test<4>()
{
	set_test_name("Test N, Eta, Xi at grid nodes. Must be equal to value in the grid");
	TPositionVector p(-5000.0, 0000.0, ZP0, TCoordSysFactory::k3DCartesian); // p is the lower left valid corner of the grid
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS), p);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG2000));
	ensure_equals("N p is 0.13998 m ", geoidModel->getN(position).getMetresValue(), 0.13998, std::numeric_limits<TReal>::epsilon() * 1e2);
	ensure_equals("Eta p is 19.81 cc", geoidModel->getEta(position).getSignedCCValue(), 19.81, std::numeric_limits<TReal>::epsilon() * 1e2);
	ensure_equals("Xi p is -17.80 cc", geoidModel->getXi(position).getSignedCCValue(), -17.80, std::numeric_limits<TReal>::epsilon() * 1e2);
}

template<>
template<>
void object::test<5>()
{
	set_test_name("Test N, Eta, Xi at grid nodes. Must be equal to value in the grid");
	TPositionVector p(-5000.0, 0000.0, ZP0, TCoordSysFactory::k3DCartesian); // p is the lower left valid corner of the grid
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS), p);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCG2000topo));
	ensure_equals("N p is 0.16931 m ", geoidModel->getN(position).getMetresValue(), 0.16931, std::numeric_limits<TReal>::epsilon() * 1e2);
	ensure_equals("Eta p is 31.07 cc", geoidModel->getEta(position).getSignedCCValue(), 31.07, std::numeric_limits<TReal>::epsilon() * 1e2);
	ensure_equals("Xi p is -27.21 cc", geoidModel->getXi(position).getSignedCCValue(), -27.21, std::numeric_limits<TReal>::epsilon() * 1e2);
}
} // namespace tut
