#include <tut/tut.hpp>

#include <TAngle.h>

namespace tut
{
struct test_TAngle
{
};
typedef test_group<test_TAngle> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test TAngle");
}

namespace
{
const TReal test_value = DEG2RAD;
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Problematic static initialisation fiasco discovered in TAngle");
	ensure_equals("anonymous namespace", test_value, 0.01745329251994329577, 1e-12);
	ensure_equals("function call", DEG2RAD, 0.01745329251994329577, 1e-12);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("getSecondsValue and getMinutesValue test (changed while refactoring the Quad)");
	TAngle angle1(0.987654321);
	ensure_equals("getMinutesValue", angle1.getMinutesValue(), 35);
	ensure_equals("getSecondsValue", angle1.getSecondsValue(), 18.3271602, 1e-6);

	TAngle angle2(-0.01);
	ensure_equals("getMinutesValue", angle2.getMinutesValue(), -34);
	ensure_equals("getSecondsValue", angle2.getSecondsValue(), 22.6480625, 1e-6);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Default constructor test");
	TAngle angle;
	ensure("Default value is NaN", std::isnan(angle.getRadiansValue()));
}

template<>
template<>
void object::test<4>()
{
	set_test_name("Explicit constructor test");
	TAngle angle(PI, TAngle::kRadians);
	ensure_equals("Radians value", angle.getRadiansValue(), PI);
	ensure_equals("Degrees value", angle.getDegreesValue(), 180);
}

template<>
template<>
void object::test<5>()
{
	set_test_name("Normalization test");
	TAngle angle(4 * PI);
	ensure_equals("Normalized value", angle.getRadiansValue(), 0.0);
}

template<>
template<>
void object::test<6>()
{
	set_test_name("Equality and less than operators test");
	TAngle angle1(PI / 2);
	TAngle angle2(PI / 4);
	TAngle angle3(PI / 2);
	ensure("Equality operator", angle1 == angle3);
	ensure("Less than operator", angle2 < angle1);
}

template<>
template<>
void object::test<7>()
{
	set_test_name("Addition and subtraction operators test");
	TAngle angle1(PI / 4);
	TAngle angle2(PI / 4);
	TAngle result = angle1 + angle2;
	ensure_equals("Addition", result.getRadiansValue(), PI / 2);
	result = angle1 - angle2;
	ensure_equals("Subtraction", result.getRadiansValue(), 0.0);
}

template<>
template<>
void object::test<8>()
{
	set_test_name("Multiplication operator test");
	TAngle angle(PI / 4);
	TAngle result = angle * (TReal)2;
	ensure_equals("Multiplication by scalar TReal", result.getRadiansValue(), PI / 2);
}

template<>
template<>
void object::test<9>()
{
	set_test_name("Trigonometric functions test");
	TAngle angle(PI / 4);
	ensure_equals("Cosine", angle.cosine(), std::sqrt(2) / 2, 1e-12);
	ensure_equals("Sine", angle.sine(), std::sqrt(2) / 2, 1e-12);
	ensure_equals("Tangent", angle.tangent(), 1.0, 1e-12);
}

template<>
template<>
void object::test<10>()
{
	set_test_name("Static member functions (constants)");
	ensure_equals("Pi", TAngle::pi().getRadiansValue(), PI);
	ensure_equals("Two Pi", TAngle::twoPi().getRadiansValue(), 0);
	ensure_equals("Pi by 2", TAngle::piBy2().getRadiansValue(), PI / 2);
	ensure_equals("Pi by 4", TAngle::piBy4().getRadiansValue(), PI / 4);
}

template<>
template<>
void object::test<11>()
{
	set_test_name("Average calculation test");
	TAngle test;
	test.setRadiansValue(PI);
	auto testt = TAngle(PI);
	std::vector<TAngle> angles = {TAngle(0), TAngle(PI / 2), TAngle(PI)};
	TAngle avg = TAngle::average(angles);
	ensure_equals("Average", avg.getRadiansValue(), PI / 2, 1e-12);
}

template<>
template<>
void object::test<12>()
{
	set_test_name("Average calculation test for values around -PI/2 and PI/2");

	// Values close to -PI/2 and PI/2, average should be around PI
	std::vector<TAngle> angles = {TAngle(-PI / 2), TAngle(PI / 2), TAngle(PI - 0.01), TAngle(-PI + 0.01)};

	TAngle avg = TAngle::average(angles);

	// Expected result is close to PI
	ensure_equals("Average close to PI", avg.getRadiansValue(), PI, 1e-12);
}

template<>
template<>
void object::test<13>()
{
	set_test_name("Boundary values for normalization");
	TAngle angle1(-2 * PI);
	TAngle angle2(2 * PI);
	TAngle angle3(0);

	ensure_equals("Normalized -2PI", angle1.getRadiansValue(), 0.0);
	ensure_equals("Normalized 2PI", angle2.getRadiansValue(), 0.0);
	ensure_equals("Normalized 0", angle3.getRadiansValue(), 0.0);
}

template<>
template<>
void object::test<14>()
{
	set_test_name("Edge cases for average");

	// Single angle
	std::vector<TAngle> singleAngle = {TAngle(PI / 3)};
	ensure_equals("Single angle average", TAngle::average(singleAngle).getRadiansValue(), PI / 3, 1e-12);

	// All angles the same
	std::vector<TAngle> sameAngles = {TAngle(PI / 4), TAngle(PI / 4), TAngle(PI / 4)};
	ensure_equals("All angles the same", TAngle::average(sameAngles).getRadiansValue(), PI / 4, 1e-12);

	// All angles sum to 0 in Cartesian coordinates
	std::vector<TAngle> zeroAverage = {TAngle(PI / 2), TAngle(-PI / 2), TAngle(0), TAngle(PI)};
	ensure_equals("Zero average", TAngle::average(zeroAverage).getRadiansValue(), 0.0, 1e-12);

	// Mean vector length is zero
	std::vector<TAngle> anglesZero = {TAngle(PI / 4), TAngle(-PI / 4), TAngle(PI / 4), TAngle(-PI / 4)};
	ensure_equals("Zero-length vector average", TAngle::average(anglesZero).getRadiansValue(), 0.0, 1e-12);

	// MeanX close to zero, MeanY positive
	std::vector<TAngle> anglesYPos = {TAngle(PI / 2), TAngle(PI / 2), TAngle(PI / 2)};
	ensure_equals("MeanX = 0, MeanY > 0", TAngle::average(anglesYPos).getRadiansValue(), PI / 2, 1e-12);

	// MeanY close to zero, MeanX positive
	std::vector<TAngle> anglesXPos = {TAngle(0), TAngle(0), TAngle(0)};
	ensure_equals("MeanY = 0, MeanX > 0", TAngle::average(anglesXPos).getRadiansValue(), 0.0, 1e-12);

	// MeanX and MeanY close to zero but MeanY negative
	std::vector<TAngle> anglesYNeg = {TAngle(-PI / 2), TAngle(-PI / 2), TAngle(-PI / 2)};
	ensure_equals("MeanX = 0, MeanY < 0", TAngle::average(anglesYNeg).getRadiansValue(), -PI / 2, 1e-12);
}

template<>
template<>
void object::test<15>()
{
	set_test_name("Extremely large angles normalization");
	TAngle angle1(1000 * PI);
	TAngle angle2(-1000 * PI);

	ensure_equals("Large positive angle normalization", angle1.getRadiansValue(), 0.0, 1e-12);
	ensure_equals("Large negative angle normalization", angle2.getRadiansValue(), 0.0, 1e-12);
}

template<>
template<>
void object::test<16>()
{
	set_test_name("Trigonometric functions special values");
	TAngle angle1(0);
	TAngle angle2(PI / 2);
	TAngle angle3(PI);
	TAngle angle4(-PI);

	ensure_equals("Cosine(0)", angle1.cosine(), 1.0, 1e-12);
	ensure_equals("Sine(PI/2)", angle2.sine(), 1.0, 1e-12);
	ensure_equals("Cosine(PI)", angle3.cosine(), -1.0, 1e-12);
	ensure_equals("Sine(-PI)", angle4.sine(), 0.0, 1e-12);
}

template<>
template<>
void object::test<17>()
{
	set_test_name("Stress test for average");

	std::vector<TAngle> angles(100000, TAngle(PI / 3));
	TAngle avg = TAngle::average(angles);
	ensure_equals("Large vector average", avg.getRadiansValue(), PI / 3, 1e-12);
}

template<>
template<>
void object::test<18>()
{
	set_test_name("Comparison with negative zero");
	TAngle angle1(0.0);
	TAngle angle2(-0.0);

	ensure("Negative zero is equal to zero", angle1 == angle2);
}

template<>
template<>
void object::test<19>()
{
	set_test_name("Multiplication edge cases");
	TAngle angle(PI / 4);
	ensure_equals("Multiplication by zero", (angle * TReal(0)).getRadiansValue(), 0.0);
	ensure_equals("Multiplication by negative", (angle * TReal(-1)).getRadiansValue(), -PI / 4);
}

} // namespace tut
