#include <algorithm>

#include "Logger.hpp"

std::unique_ptr<Logger> Logger::_instance = nullptr;

Logger & Logger::getLogger()
{
	if (!_instance)
		_instance.reset(new Logger());
	return *_instance;
}

void Logger::log(const LogMessage & message)
{
	if (message.getType() == LogMessage::Type::WARNING)
		_warningnumber++;
	else if (message.getType() >= LogMessage::Type::CRITICAL)
		_errornumber++;
	for (auto& h : _handlers)
	{
		if (message.getType() >= h->getThreshold())
			h->log(message);
	}
}

void Logger::removeHandler(ILogHandler * handler)
{
	auto it = std::find_if(std::begin(_handlers), std::end(_handlers), [&handler](const std::unique_ptr<ILogHandler> &h) -> bool { return h.get() == handler; });
	if (it != std::end(_handlers))
		_handlers.erase(it);
}
