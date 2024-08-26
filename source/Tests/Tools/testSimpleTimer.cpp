#include <tut/tut.hpp>

#include <thread>

#include "SimpleTimer.h"

namespace tut
{
struct toolsSimpleTimer
{
};

typedef test_group<toolsSimpleTimer> tst;
tst tools_simpleTimer_group("Test Tools - SimpleTimer package.");
typedef tst::object testobject;
} // namespace tut

namespace tut
{
template<>
template<>
void testobject::test<1>()
{
	set_test_name("SimpleTimer: test start stop");

	SimpleTimer timer;
	timer.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	size_t duration = timer.stop();
	ensure_distance(duration, (size_t)200, (size_t)100);
}

template<>
template<>
void testobject::test<2>()
{
	set_test_name("SimpleTimer: test start step stop");

	SimpleTimer timer;
	timer.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	timer.step();
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	timer.step();
	timer.stop();
	timer.printSteps();
	auto steps = timer.getSteps();
	ensure_distance(steps[0], (size_t)200, (size_t)100);
	ensure_distance(steps[1], (size_t)500, (size_t)100);
}
}
