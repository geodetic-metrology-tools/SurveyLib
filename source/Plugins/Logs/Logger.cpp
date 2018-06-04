#include "Logger.hpp"

#include "ILogHandler.hpp"

std::unique_ptr<Logger> Logger::_instance = nullptr;

Logger & Logger::getLogger()
{
	if (!_instance)
		_instance.reset(new Logger());
	return *_instance;
}

void Logger::log(const LogMessage & message)
{
	for (auto& h : _handlers)
	{
		if (message.getType() >= h->getThreshold())
			h->log(message);
	}
}
