#include <algorithm>
#include <functional>
#include <unordered_set>

#include "ILogHandler.hpp"
#include "Logger.hpp"

class Logger::_Logger_pimpl
{
public:
	/** List of registered handlers. */
	std::unordered_set<std::unique_ptr<ILogHandler>> handlers;
	/** number of errors */
	size_t errornumber = 0;
	/** number of warnings */
	size_t warningnumber = 0;
};

Logger & Logger::getLogger()
{
	static Logger instance;
	return instance;
}

Logger::~Logger() = default;

void Logger::log(const LogMessage & message)
{
	if (message.getType() == LogMessage::Type::WARNING)
		_pimpl->warningnumber++;
	else if (message.getType() >= LogMessage::Type::CRITICAL)
		_pimpl->errornumber++;
	for (auto& h : _pimpl->handlers)
	{
		if (message.getType() >= h->getThreshold())
			h->log(message);
	}
}

void Logger::addHandlers(ILogHandler * handler)
{
	_pimpl->handlers.emplace(handler);
}

void Logger::removeHandler(ILogHandler * handler)
{
	auto it = std::find_if(std::begin(_pimpl->handlers), std::end(_pimpl->handlers), [&handler](const std::unique_ptr<ILogHandler> &h) -> bool { return h.get() == handler; });
	if (it != std::end(_pimpl->handlers))
		_pimpl->handlers.erase(it);
}

void Logger::clearHandlers() noexcept
{
	_pimpl->handlers.clear();
}

bool Logger::hasErrors() const noexcept
{
	return _pimpl->errornumber > 0;
}

size_t Logger::errorNumber() const noexcept
{
	return _pimpl->errornumber;
}

bool Logger::hasWarnings() const noexcept
{
	return _pimpl->warningnumber > 0;
}

size_t Logger::warningNumber() const noexcept
{
	return _pimpl->warningnumber;
}

void Logger::clearCounters() noexcept
{
	_pimpl->errornumber = _pimpl->warningnumber = 0;
}

Logger::Logger() : _pimpl(std::make_unique<_Logger_pimpl>())
{
}
