/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef LOGMESSAGE_HPP
#define LOGMESSAGE_HPP

#include <ctime>
#include <string>
#include <sstream>

#include "LogLibGlobals.hpp"

/**
 * Hold a message to be logged.
 *
 * LogMessage is part of the @ref logs module.
 * @ingroup logs
 *
 * A message is composed of:
 * - a type (see the internal enum `Type`) which can be `DEBUG`, `INFO`, `WARNING`, `CRITICAL` or `FATAL`.
 *   Note that these types are close to the Qt ones.
 * - a creation date
 * - a context, which tells where the event happened: the file, the line in the file, and the function responsible of it.
 * - a message that explains the event.
 *
 * Thus, to be able to log anything from anywhere, the interface is very simple: you just need to use one of the provided
 * macro:
 * - logDebug()
 * - logInfo()
 * - logWarning()
 * - logCritical()
 * - logFatal()
 *
 * Notice that the operator<<() automatically adds spaces between values.
 * @code{cpp}
 * logDebug() << "something happened" << (int) i;
 * logInfo() << "computation finished";
 * logCritical() << "an error occurred with a =" << a;
 * @endcode
 *
 * Internally, when you use such a method, it creates a temporary LogMessage and fill it. When the temporary object is destroyed,
 * it will automatically log itself into the Logger class.
 * If you want to do it manually, make sure to use the first constructor and / or put the boolean `callLoggerOnDestruct` to
 * false. Otherwise your message will be logged twice. This is how you would manually do (but note that the macro method is
 * way easier!):
 * @code{cpp}
 * Logger::getLogger().log(LogMessage(LogMessage::Type::DEBUG, "my debug message"));
 * @endcode
 *
 * @see logs, Logger, logDebug(), logInfo(), logWarning(), logCritical(), logFatal()
 */
class SUGL_SHARED_EXPORT LogMessage
{
public:
	/**
	 * List of possible types for a LogMessage.
	 *
	 * Related function: operator<<(std::ostream& stream, const LogMessage::Type& type)
	 */
	enum class Type {
		/** Debug messages, only useful for the developers. */
		DEBUG,
		/** Info messages, only useful to see informations. */
		INFO,
		/** Warning messages, shows when the user is doing something wrong. */
		WARNING,
		/** Debug messages, an error occurred. */
		CRITICAL,
		/** Fatal messages, an unrecoverable error occurred (the application crashed or is about to). */
		FATAL
	};

	/**
	 * User constructor.
	 *
	 * Use it if you don't want to use the macros.
	 *
	 * @param t the type of the message
	 * @param msg the message
	 */
	LogMessage(Type t, const std::string& msg = "");
	/**
	 * Internal constructor, you shouldn't use it.
	 *
	 * Constructor used by the macros.
	 *
	 * @param t the type of the message
	 * @param file,line,func the context where the event occurred (generally `__FILE__`, `__LINE__` and `__func__`)
	 * @param msg the message
	 * @param callLoggerOnDestruct boolean that says if the LogMessage should register itself in the Logger class when destroyed.
	 *                             This is true when the LogMessage has been created with a macro, otherwise you should let it to false.
	 */
	LogMessage(Type t, const std::string& file, int line, const std::string& func, const std::string& msg = "", bool callLoggerOnDestruct = false);
	LogMessage(const LogMessage&) = delete; // can't copy
	LogMessage(LogMessage&&) = default;
	LogMessage& operator=(const LogMessage&) = delete;
	LogMessage& operator=(LogMessage&&) = default;
	~LogMessage();

	/** Append the object to the message. */
	template <class T>
	LogMessage& operator<<(const T& tolog);
	/** Manage the std::endl case. */
	LogMessage& operator<<(std::basic_ostream<char, std::char_traits<char>>& (*)(std::basic_ostream<char, std::char_traits<char>>&));

	/**
	 * Return the date of creation of the message as a string.
	 *
	 * @param format the format of the date, by default "%c" (standard date and time string). See the documentation of `std::put_time` for more info.
	 * @return the date of creation as a string
	 */
	std::string getDate(const std::string& format="%c") const;
	/**
	 * Gives the context.
	 *
	 * Returns a phrase where is written the file, the line and function, like this: `at 'FILE', line LINE in 'FUNCTION'`
	 *
	 * @return the context
	 * @see getFile(), getLine(), getFunction()
	 */
	std::string getContext() const;
	void setType(Type t) noexcept { _type = t; }
	Type getType() const noexcept { return _type; }
	void setMessage(const std::string& msg) { _message = msg; }
	const std::string& getMessage() const noexcept { return _message; }
	void setFile(const std::string& file) { _file = file; }
	const std::string& getFile() const noexcept { return _file; }
	void setLine(const int line) noexcept { _line = line; }
	int getLine() const noexcept { return _line; }
	void setFunction(const std::string& func) { _function = func; }
	const std::string& getFunction() const noexcept { return _function; }

private:
	/** the type of the message */
	Type _type;
	/** the file where the event occurred */
	std::string _file;
	/** the line in the file */
	int _line = -1;
	/** the function responsible for the event */
	std::string _function;
	/** the message */
	std::string _message;
	/** if true, the object will register itself in the Logger class on destruction */
	const bool _callLogger = false;
	/** the date of creation of the object */
	const std::time_t _creationDate;
};

/**
 * Stream operator for LogMessage::Type enumeration.
 *
 * It will convert the type to a string as follow:
 *
 * - LogMessage::Type::DEBUG gives `"DEBUG"`
 * - LogMessage::Type::INFO gives `"INFO"`
 * - LogMessage::Type::WARNING gives `"WARNING"`
 * - LogMessage::Type::CRITICAL gives `"ERROR"` *(notice the difference)*
 * - LogMessage::Type::FATAL gives `"FATAL"`
 */
template <class T>
T& operator<<(T& stream, const LogMessage::Type& type)
{
	switch (type)
	{
	case LogMessage::Type::DEBUG:
		stream << "DEBUG";
		break;
	case LogMessage::Type::INFO:
		stream << "INFO";
		break;
	case LogMessage::Type::WARNING:
		stream << "WARNING";
		break;
	case LogMessage::Type::CRITICAL:
		stream << "ERROR";
		break;
	case LogMessage::Type::FATAL:
		stream << "FATAL";
		break;
	}
	return stream;
}

template<class T>
LogMessage& LogMessage::operator<<(const T& tolog)
{
	std::ostringstream str;
	str << tolog;
	if (!_message.empty())
		_message += ' ';
	_message += str.str();
	return *this;
}

#endif // LOGMESSAGE_HPP
