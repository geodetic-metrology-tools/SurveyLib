#include <tut/tut.hpp>

#include <TPositionVector.h>

namespace tut
{
struct test_TPositionVector
{
};
typedef test_group<test_TPositionVector> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test TPositionVector");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Substract a FreeVector to a PositionVector");
	TReal posX = 10, posY = 20, posZ = 30;
	TPositionVector position(posX, posY, posZ, TCoordSysFactory::k3DCartesian);
	TReal deltaX = 1, deltaY = 2, deltaZ = 3;
	TFreeVector delta(deltaX, deltaY, deltaZ, TCoordSysFactory::k3DCartesian);

	TFreeVector result = position - delta;

	ensure_equals("Result X", result.getX(), posX - deltaX);
	ensure_equals("Result Y", result.getY(), posY - deltaY);
	ensure_equals("Result Z", result.getZ(), posZ - deltaZ);
}
template<>
template<>
void object::test<2>()
{
	set_test_name("Substract two PositionVector");
	TReal posX1 = 10, posY1 = 20, posZ1 = 30;
	TPositionVector position1(posX1, posY1, posZ1, TCoordSysFactory::k3DCartesian);
	TReal posX2 = 1, posY2 = 2, posZ2 = 3;
	TPositionVector position2(posX2, posY2, posZ2, TCoordSysFactory::k3DCartesian);
	TFreeVector delta(posX2, posY2, posZ2, TCoordSysFactory::k3DCartesian);

	TFreeVector result1 = position1 - position2;

	ensure_equals("Result X", result1.getX(), posX1 - posX2);
	ensure_equals("Result Y", result1.getY(), posY1 - posY2);
	ensure_equals("Result Z", result1.getZ(), posZ1 - posZ2);

	TFreeVector result2 = position2 - position1;
	ensure_equals("Result X", result2.getX(), posX2 - posX1);
	ensure_equals("Result Y", result2.getY(), posY2 - posY1);
	ensure_equals("Result Z", result2.getZ(), posZ2 - posZ1);
}
template<>
template<>
void object::test<3>()
{
	set_test_name("Substract a FreeVector to a const PositionVector");
	TReal posX = 10, posY = 20, posZ = 30;
	const TPositionVector position(posX, posY, posZ, TCoordSysFactory::k3DCartesian);
	TReal deltaX = 1, deltaY = 2, deltaZ = 3;
	TFreeVector delta(deltaX, deltaY, deltaZ, TCoordSysFactory::k3DCartesian);

	TFreeVector result = position - delta;

	ensure_equals("Result X", result.getX(), posX - deltaX);
	ensure_equals("Result Y", result.getY(), posY - deltaY);
	ensure_equals("Result Z", result.getZ(), posZ - deltaZ);
}
template<>
template<>
void object::test<4>()
{
	set_test_name("Substract a const FreeVector to a const PositionVector");
	TReal posX = 10, posY = 20, posZ = 30;
	const TPositionVector position(posX, posY, posZ, TCoordSysFactory::k3DCartesian);
	TReal deltaX = 1, deltaY = 2, deltaZ = 3;
	const TFreeVector delta(deltaX, deltaY, deltaZ, TCoordSysFactory::k3DCartesian);

	TFreeVector result = position - delta;

	ensure_equals("Result X", result.getX(), posX - deltaX);
	ensure_equals("Result Y", result.getY(), posY - deltaY);
	ensure_equals("Result Z", result.getZ(), posZ - deltaZ);
}
template<>
template<>
void object::test<5>()
{
	set_test_name("Substract two const PositionVector");
	TReal posX1 = 10, posY1 = 20, posZ1 = 30;
	const TPositionVector position1(posX1, posY1, posZ1, TCoordSysFactory::k3DCartesian);
	TReal posX2 = 1, posY2 = 2, posZ2 = 3;
	const TPositionVector position2(posX2, posY2, posZ2, TCoordSysFactory::k3DCartesian);
	TFreeVector delta(posX2, posY2, posZ2, TCoordSysFactory::k3DCartesian);

	TFreeVector result1 = position1 - position2;

	ensure_equals("Result X", result1.getX(), posX1 - posX2);
	ensure_equals("Result Y", result1.getY(), posY1 - posY2);
	ensure_equals("Result Z", result1.getZ(), posZ1 - posZ2);

	TFreeVector result2 = position2 - position1;
	ensure_equals("Result X", result2.getX(), posX2 - posX1);
	ensure_equals("Result Y", result2.getY(), posY2 - posY1);
	ensure_equals("Result Z", result2.getZ(), posZ2 - posZ1);
}
template<>
template<>
void object::test<6>()
{
	set_test_name("Add a FreeVector to a PositionVector");
	TReal posX = 10, posY = 20, posZ = 30;
	TPositionVector position(posX, posY, posZ, TCoordSysFactory::k3DCartesian);
	TReal deltaX = 1, deltaY = 2, deltaZ = 3;
	TFreeVector delta(deltaX, deltaY, deltaZ, TCoordSysFactory::k3DCartesian);

	TFreeVector result = position + delta;

	ensure_equals("Result X", result.getX(), posX + deltaX);
	ensure_equals("Result Y", result.getY(), posY + deltaY);
	ensure_equals("Result Z", result.getZ(), posZ + deltaZ);
}
template<>
template<>
void object::test<7>()
{
	set_test_name("Add a FreeVector to a const PositionVector");
	TReal posX = 10, posY = 20, posZ = 30;
	const TPositionVector position(posX, posY, posZ, TCoordSysFactory::k3DCartesian);
	TReal deltaX = 1, deltaY = 2, deltaZ = 3;
	TFreeVector delta(deltaX, deltaY, deltaZ, TCoordSysFactory::k3DCartesian);

	TFreeVector result = position + delta;

	ensure_equals("Result X", result.getX(), posX + deltaX);
	ensure_equals("Result Y", result.getY(), posY + deltaY);
	ensure_equals("Result Z", result.getZ(), posZ + deltaZ);
}
} // namespace tut
