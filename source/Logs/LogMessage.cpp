#include "LogMessage.hpp"

# include <chrono>
#include <iomanip>

#include "Logger.hpp"

LogMessage::LogMessage(Type t, const std::string & msg) :
	_type(t),
	_message(msg),
	_creationDate(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
}

LogMessage::LogMessage(Type t, const std::string & file, int line, const std::string & func, const std::string & msg, bool callLoggerOnDestruct) :
	_type(t),
	_file(file),
	_line(line),
	_function(func),
	_message(msg),
	_callLogger(callLoggerOnDestruct),
	_creationDate(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
}

LogMessage::~LogMessage()
{
	if (_callLogger)
		Logger::getLogger().log(*this);
}

LogMessage & LogMessage::operator<<(std::basic_ostream<char, std::char_traits<char>>&(*)(std::basic_ostream<char, std::char_traits<char>>&))
{
	_message += '\n';
	return *this;
}

std::string LogMessage::getDate(const std::string & format) const
{
	std::ostringstream str;
	str << std::put_time(std::localtime(&_creationDate), format.c_str());
	return str.str();
}

std::string LogMessage::getContext() const
{
	return "at '" + _file + "', line " + std::to_string(_line) + " in '" + _function + "'";
}
