/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <functional>
#include <memory>
#include <unordered_set>

#include "LogMessage.hpp"

/** @warning Internal macro, you shouldn't use it. */
#define _logMessage(type) (LogMessage((type), __FILE__, __LINE__, __func__, "", true))
/**
* Automatically log everything you stream in it as a debug message.
*
* @note Space is automatically added between the values.
*
* @code{cpp}
* logDebug() << "function worked as expected:" << (int) i;
* @endcode
* 
* @see LogMessage, Logger
*/
#define logDebug() (_logMessage(LogMessage::Type::DEBUG))
/**
* Automatically log everything you stream in it as an info message.
*
* @note Space is automatically added between the values.
*
* @code{cpp}
* logInfo() << "current step:" << (int) i;
* @endcode
* 
* @see LogMessage, Logger
*/
#define logInfo() (_logMessage(LogMessage::Type::INFO))
/**
* Automatically log everything you stream in it as a warning message.
*
* @note Space is automatically added between the values.
*
* @code{cpp}
* logWarning() << "Bad entry (expected positive number):" << (int) i;
* @endcode
* 
* @see LogMessage, Logger
*/
#define logWarning() (_logMessage(LogMessage::Type::WARNING))
/**
* Automatically log everything you stream in it as a critical (error) message.
*
* @note Space is automatically added between the values.
*
* @code{cpp}
* logCritical() << "An error occurred:" << (int) i;
* @endcode
* 
* @see LogMessage, Logger
*/
#define logCritical() (_logMessage(LogMessage::Type::CRITICAL))
/**
* Automatically log everything you stream in it as a fatal (unrecoverable error) message.
*
* @note Space is automatically added between the values.
*
* @code{cpp}
* logFatal() << "unrecoverrable error:" << (int) i;
* @endcode
* 
* @see LogMessage, Logger
*/
#define logFatal() (_logMessage(LogMessage::Type::FATAL))

class ILogHandler;

/**
 * Singleton that dispatch the logs to registered handlers.
 *
 * This is the heart of the logging system. To log a message, you just need to use the log() function.
 * The goal of the log system is to have one entry point to log everything, no matter where we are in the code (in a UI or in
 * the SurveyLib). Then, the software will be responsible to print the messages to the users. This is done by a handler. I.E.
 * if we are in a CLI application, we can use one or several of the basic handlers (see FileLogHandler and ConsoleLogHandler).
 * The message will automatically be dispatch to the different handlers.
 *
 * Several handlers can be registered, thus it is possible to register the messages in a file and show
 * them in live to the user. There is no warranty on which one will be called first.
 *
 * A handler must implement the ILogHandler interface. You have two basic handlers already implemented:
 * ConsoleLogHandler and FileLogHandler. A handler can define a threshold for the type of messages to
 * receive, see ILogHandler::setThreshold().
 *
 * @note The best way to log messages is to use one of the provided macro:
 * - logDebug()
 * - logInfo()
 * - logWarning()
 * - logCritical()
 * - logFatal()
 * @code{cpp}
 * // Space is automatically added between the values.
 * logDebug() << "something happened" << (int) i;
 * logInfo() << "computation finished";
 * logCritical() << "an error occurred with a =" << a;
 * @endcode
 *
 * @see ILogHandler, ConsoleLogHandler, FileLogHandler, LogMessage, LogMessage::Type, logDebug(),
 *      logInfo(), logWarning(), logCritical(), logFatal()
 */
class Logger
{
public:
	/** @return the instance of the Logger (singleton) */
	static Logger& getLogger();

	/**
	 * Log the given message.
	 *
	 * Call the ILogHandler::log() function for all registered handlers **if** the type of the
	 * message is above their threshold.
	 *
	 * You may want to *not* use this method directly, but rather use one of the provided macro:
	 * - logDebug()
	 * - logInfo()
	 * - logWarning()
	 * - logCritical()
	 * - logFatal()
	 *
	 * @param message the message to log
	 * @see LogMessage, ILogHandler::log()
	 */
	void log(const LogMessage& message);
	/**
	 * Add a handler to which the logged messages will be sent.
	 *
	 * You can add multiple handlers, however the order on which they will be called is not
	 * warrantied.
	 *
	 * @param handler the handler to register
	 * @see removeHandler(), clearHandlers(), ILogHandler
	 */
	void addHandlers(ILogHandler * handler) { _handlers.insert(handler); }
	/**
	 * Add handlers.
	 *
	 * @param handler, rest the list of pionters to handlers to add.
	 * @see addHandlers()
	 */
	template<class... Ts>
	void addHandlers(ILogHandler* handler, Ts... rest) { addHandlers(handler); addHandlers(rest...); }
	/**
	 * @param handler the handler to remove
	 * @see addHandlers(), clearHandlers(), ILogHandler
	 */
	void removeHandler(ILogHandler * handler) { _handlers.erase(handler); }
	/** @see addHandlers(), removeHandler(), ILogHandler */
	void clearHandlers() { _handlers.clear(); }

private:
	Logger() = default;

private:
	/** Pointer on the current instance (singleton). */
	static std::unique_ptr<Logger> _instance;

	/** List of registered handlers. */
	std::unordered_set<ILogHandler *> _handlers;
};

#endif // LOGGER_HPP
