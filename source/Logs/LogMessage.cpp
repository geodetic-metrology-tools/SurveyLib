#include "LogMessage.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>

#include "Logger.hpp"

class LogMessage::_LogMessage_pimpl
{
public:
	/** the type of the message */
	LogMessage::Type type;
	/** the message */
	std::string message;
	/** the date of creation of the object */
	const std::time_t creationDate;
	/** the file where the event occurred */
	std::string file;
	/** the line in the file */
	int line = -1;
	/** the function responsible for the event */
	std::string function;
	/** if true, the object will register itself in the Logger class on destruction */
	const bool callLogger = false;
};

LogMessage::LogMessage(Type t, const std::string & msg) : _pimpl(new _LogMessage_pimpl{
	t,
	msg,
	std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())
	})
{
}

LogMessage::LogMessage(Type t, const std::string & file, int line, const std::string & func, const std::string & msg, bool callLoggerOnDestruct) : _pimpl(new _LogMessage_pimpl{
	t,
	msg,
	std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
	file,
	line,
	func,
	callLoggerOnDestruct
	})
{
}

LogMessage::LogMessage(LogMessage &&) = default;

LogMessage & LogMessage::operator=(LogMessage &&) = default;

LogMessage::~LogMessage()
{
	if (_pimpl && _pimpl->callLogger)
		Logger::getLogger().log(*this);
}

LogMessage & LogMessage::operator<<(std::basic_ostream<char, std::char_traits<char>>&(*)(std::basic_ostream<char, std::char_traits<char>>&))
{
	_pimpl->message += '\n';
	return *this;
}

std::string LogMessage::getDate(const std::string & format) const
{
	std::ostringstream str;
	str << std::put_time(std::localtime(&_pimpl->creationDate), format.c_str());
	return str.str();
}

std::string LogMessage::getContext() const
{
	return "at '" + _pimpl->file + "', line " + std::to_string(_pimpl->line) + " in '" + _pimpl->function + "'";
}

void LogMessage::setType(Type t) noexcept
{
	_pimpl->type = t;
}

LogMessage::Type LogMessage::getType() const noexcept
{
	return _pimpl->type;
}

void LogMessage::setMessage(const std::string & msg)
{
	_pimpl->message = msg;
}

const std::string & LogMessage::getMessage() const noexcept
{
	return _pimpl->message;
}

void LogMessage::setFile(const std::string & file)
{
	_pimpl->file = file;
}

const std::string & LogMessage::getFile() const noexcept
{
	return _pimpl->file;
}

void LogMessage::setLine(const int line) noexcept
{
	_pimpl->line = line;
}

int LogMessage::getLine() const noexcept
{
	return _pimpl->line;
}

void LogMessage::setFunction(const std::string & func)
{
	_pimpl->function = func;
}

const std::string & LogMessage::getFunction() const noexcept
{
	return _pimpl->function;
}
