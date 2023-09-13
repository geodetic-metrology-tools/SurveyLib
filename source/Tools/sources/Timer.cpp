#include "Timer.h"

Timer::Timer()
{
	startTime = std::chrono::high_resolution_clock::now();
}

double Timer::finished()
{
	auto endTime = std::chrono::high_resolution_clock::now();
	double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
	return elapsedTime;
}
