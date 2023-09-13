/*
© Copyright CERN 2000-2023. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/*!
	Timer

	Auxiliary class for timing

*/

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
	Timer();
	//~Timer();
	// call the finished method after execution of timed code is done
	// returns elapsed time since creation of object
	double finished();

private:
	std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIMER_H
