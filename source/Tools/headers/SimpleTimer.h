/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>

template<class T = std::chrono::milliseconds>
class SimpleTimer {
public:
	SimpleTimer() = default;
	~SimpleTimer() = default;
	void start() { m_startPoint = std::chrono::high_resolution_clock::now(); } 
	/**
	* Records the time into steps. The recorded time is always relative to when the timer was started
	* and NOT compared to the previous step. 
	*/
	void step() { m_steps.emplace_back(std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_startPoint).count()); }
	[[maybe_unused]] size_t stop() 
	{
		auto measuredTime = std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_startPoint).count();
		printStop(measuredTime);
		return measuredTime;
	}
	void printSteps() 
	{ 
		if (!m_steps.size())
		{
			std::cout << "[]" << std::endl;
			return;
		}
		std::stringstream output;
		output << "[";
		for (int i = 0; i < m_steps.size() - 1; i++)
		{
			output << m_steps[i].count() << "ms, ";
		}
		output << m_steps[m_steps.size() - 1].count() << "ms]";
		std::cout << output.str() << std::endl;
	}
	std::vector<size_t> getSteps()
	{
		std::vector<size_t> result;
		result.reserve(m_steps.size());
		for (auto step : m_steps)
		{
			result.emplace_back(step.count());
		}
		return result;
	}
	void reset()
	{
		m_startPoint = std::chrono::steady_clock::time_point();
		m_steps.clear();
	}
	std::vector<T> m_steps;
private:
	void printStop(size_t duration) {std::cout << "Elapsed Time: " << duration << std::endl;}
	std::chrono::high_resolution_clock::time_point m_startPoint;
};

template<>
void SimpleTimer<std::chrono::milliseconds>::printStop(size_t duration)
{
	std::cout << "Elapsed Time in milliseconds: " << duration << "ms" << std::endl;
}

template<>
void SimpleTimer<std::chrono::seconds>::printStop(size_t duration)
{
	std::cout << "Elapsed Time in seconds: " << duration << "s" << std::endl;
}
