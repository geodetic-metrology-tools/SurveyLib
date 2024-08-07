#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>

template<class T>
class basicSimpleTimer {
public:
	basicSimpleTimer() = default;
	~basicSimpleTimer() = default;
	void start() { m_startPoint = std::chrono::high_resolution_clock::now(); }
	void step() { m_steps.emplace_back(std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_startPoint).count()); }
	void stop() 
	{
		auto measuredTime = std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_startPoint).count();
		std::cout << "Elapsed Time in milliseconds: " << measuredTime << "ms" << std::endl;
	}
	std::string printSteps() 
	{ 
		std::stringstream output("[");
		for (int i = 0; i < m_steps.size(); i++)
		{
			output << m_steps[i].count() << "ms, ";
		}
		output << "]";
		std::cout << output.str() << std::endl;
		return output.str();
	}
	void reset()
	{
		m_startPoint = std::chrono::steady_clock::time_point();
		m_steps.clear();
	}
	std::vector<T> m_steps;
private:
	std::chrono::steady_clock::time_point m_startPoint;
};

#define SimpleTimer basicSimpleTimer<std::chrono::milliseconds>
