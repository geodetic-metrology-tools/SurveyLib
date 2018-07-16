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

/**
 * @defgroup logs Logs
 *
 * The module Logs holds the new logging mechanism in the SurveyLib.
 *
 * This mechanism should be used in all SU software from now. Is is a very simple way to log information,
 * here is an example (see below for more information):.
 * @code{cpp}
 * logWarning() << "Wrong input!!!" << myInput;
 * @endcode
 *
 * # Concepts #
 *
 * The goal of the log system is to have one entry point to log everything, no matter where we are in the code (in a UI or in
 * the SurveyLib). Then, the software will be responsible to print the messages to the users. This system is based on the `qDebug()`
 * system from Qt, having in mind that "if it is easy to log, people will do it".
 *
 * The SU applications generally have a bad logging system, which leads to few or no logging at all, leaving the end-user with no
 * explanations on their weird behaviors. In order to improve the logging, this class has been made so we can easily add log information
 * everywhere in existing code. At term, this is supposed to completely replace the Behavior class.
 *
 * The logging system works on 3 concepts: the LogMessage, the Logger and the ILogHandler.
 *
 * ## LogMessage ##
 *
 * Each logging information is stocked in a LogMessage object. This object can holds the logging message, along with its context,
 * the time where the event happened, and its criticality.
 *
 * The criticality is represented by the enum LogMessage::Type which holds 5 levels as below:
 * - LogMessage::Type::DEBUG
 * - LogMessage::Type::INFO
 * - LogMessage::Type::WARNING
 * - LogMessage::Type::CRITICAL
 * - LogMessage::Type::FATAL
 *
 * See the section "Log a message" below to see how to correctly log a message.
 *
 * ## Logger ##
 *
 * The Logger is the heart of the logging system: it receives the created LogMessages dispatch them to the handlers so they can present them
 * to the end-user.
 *
 * The Logger is a singleton class, so there is only one instance in all the software. To learn how to use it, see the "Use it" section below.
 *
 * ## ILogHandler ##
 *
 * ILogHandler is an interface for all the handlers we can have. As said before, the Logger receives the logged messages and dispatch them to
 * the handlers. A handler is a class implementing the ILogHandler interface, which role is to show the logged message to the end-user.
 * This can be done via several methods: from writing the logs in a file to print them in a popup window.
 *
 * 2 default handlers exist in the SurveyLib: the ConsoleLogHandler and the FileLogHandler.
 *
 * A handler has a criticality threshold, meaning that logged messages with a criticality below this threshold will not be sent to them.
 * This threshold is customizable via the method ILogHandler::setThreshold().
 *
 * # Use it #
 *
 * It is very simple to use the logging system. As said earlier, the Logging class is a singleton, so it exists as a unique object in the
 * application. You don't have anything to do to make the logging mechanisms work.
 *
 * However, by default, the Logger class has no handlers to show the messages. So all logged messages will be silently ignored. In order
 * to be able to show the messages to the end-user, we need to add one or more handlers.
 *
 * ## Add handlers ##
 *
 * A handler is a class that will show the messages to the end-user. You can have multiple handlers installed at the same time: say you
 * have a CLI application, you can have a ConsoleLogHandler that will print in the console all warning (or more critical) information,
 * and a FileLogHandler that will log everything in a file. To do so, you just need to do the following in your code:
 *
 * @code{cpp}
 * #include "Logs/Logger.hpp"
 * #include "Logs/ConsoleLogHandler.hpp"
 * #include "Logs/FileLogHandler.hpp"
 *
 * int main()
 * {
 *     FileLogHandler *h = new FileLogHandler("myLogFile.log");
 *     h->setThreshold(LogMessage::Type::DEBUG);
 *     Logger::getLogger().addHandlers(
 *         h,
 *         new ConsoleLogHandler()
 *     );
 *     // do stuff...
 *     return 0;
 * }
 * @endcode
 *
 * Note that it is important to install the handlers as soon as possible because, as long as there is no handler, the logged messages are lost.
 *
 * ## Log a message ##
 *
 * It is very simple to log a message, you just need to use one of the provided macro, according to the criticality level of your message:
 * - logDebug()
 * - logInfo()
 * - logWarning()
 * - logCritical()
 * - logFatal()
 *
 * You just need to stream all the required information in the maccro. Note that spaces are automatically added betweend values:
 * @code{cpp}
 * int i;
 * std::cin >> i;
 * if (!std::cin.good())
 *     logCritical() << "You must enter a valid integer. For the rest of the program, i will have the value" << i;
 * @endcode
 *
 * The macro will automatically create and log a valid LogMessage, with the full context (file, line, function).
 * Here is the output that the FileLogHandler would produce:
 * ```
 * 06/11/18 15:37:46 ERROR: 'You must enter a valid integer. For the rest of the program, i will have the value 0'
 * 	at 'c:\path\to\file.cpp', line 317 in 'myfunction'
 * ```
 *
 * @note For information, the macros create a temporary LogMessage object that will call the Logger::log() method on destruction.
 * You could achieve more or less the same with the code below, but note that it is way more complex and don't take the context
 * of the message:
 * @code{cpp}
 * Logger::getLogger().log(LogMessage("You must enter a valid integer. For the rest of the program, i will have the value " + std::to_string(i)));
 * @endcode
 *
 * ## Implement new handlers ##
 *
 * You have 2 default handlers, but you can create some to customize their behavior. The most obvious example is to have a GUI handler to be able to show
 * logged messages from a GUI application. To do so, you just need to implement the ILogHandler interface and override its ILogHandler::log() method.
 *
 * This method receives a LogMessage. You can do whatever you want with it. The 2 default handlers first print the date and then the message. In case of
 * criticality level debug, or critical or more, the context is also printed.
 */

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
 * @ingroup logs
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
 * @ingroup logs
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
 * @ingroup logs
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
 * @ingroup logs
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
 * @ingroup logs
 * @see LogMessage, Logger
 */
#define logFatal() (_logMessage(LogMessage::Type::FATAL))

class ILogHandler;

/**
 * Singleton that dispatch the logs to registered handlers.
 *
 * Logger is part of the @ref logs module.
 * @ingroup logs
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
 * Each time an error or a warning is logged, an internal counter is increased. Thus, you can get the number of errors or warnings
 * with the methods errorNumber() and warningNumber(). To reset these counters, you can call the method clearCounters().
 * Note that the counters are incremented, even if there is no handlers.
 *
 * @see logs
 */
class Logger
{
public:
	/** @return the instance of the Logger (singleton) */
	static Logger& getLogger();

	Logger(const Logger&) = delete; // can't copy
	Logger(const Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger& operator=(const Logger&&) = delete;

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
	void clearHandlers() noexcept { _handlers.clear(); }

	/**
	 * @return true if some errors have been logged.
	 * @see errorNumber(), clearCounters()
	 */
	bool hasErrors() const noexcept { return _errornumber > 0; }
	/**
	 * @return the number of logged warnings.
	 * @see hasErrors(), clearCounters()
	 */
	size_t errorNumber() const noexcept { return _errornumber; }
	/**
	 * @return true if some warnings have been logged.
	 * @see warningNumber(), clearCounters()
	 */
	bool hasWarnings() const noexcept { return _warningnumber > 0; }
	/**
	 * @return the number of logged warnings.
	 * @see hasWarnings(), clearCounters()
	 */
	size_t warningNumber() const noexcept { return _warningnumber; }
	/**
	 * Clear the error and warning counters.
	 * @see hasErrors(), errorNumber(), hasWarnings(), warningNumber()
	 */
	void clearCounters() noexcept { _errornumber = _warningnumber = 0; }

private:
	Logger() = default;

private:
	/** Pointer on the current instance (singleton). */
	static std::unique_ptr<Logger> _instance;

	/** List of registered handlers. */
	std::unordered_set<ILogHandler *> _handlers;
	/** number of errors */
	size_t _errornumber = 0;
	/** number of warnings */
	size_t _warningnumber = 0;
};

#endif // LOGGER_HPP
