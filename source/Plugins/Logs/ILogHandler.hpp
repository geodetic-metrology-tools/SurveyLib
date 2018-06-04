/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef ILOGHANDLER_HPP
#define ILOGHANDLER_HPP

#include "LogMessage.hpp"

/**
 * Interface for logging handlers.
 *
 * Implement this interface to create a handler able to receive LogMessage coming from the Logger.
 *
 * The goal of a handler is to present the messages received to the user, by the best mean. This can be
 * done by writing in a file (like the FileLogHandler), or putting info on the standard output (like the
 * ConsoleLogHandler)...
 *
 * The only method you need to override is log().
 *
 * Finally, it is possible to filter the messages received by the handlers. With the method setThreshold(),
 * you can give the minimum of importance before the messages are sent to the handler. The order is
 * as follow (defined in the enum LogMessage::Type):
 * 1. LogMessage::Type::DEBUG
 * 2. LogMessage::Type::INFO
 * 3. LogMessage::Type::WARNING
 * 4. LogMessage::Type::CRITICAL
 * 5. LogMessage::Type::FATAL
 *
 * It means that if you set the threshold to LogMessage::Type::CRITICAL, only critical and fatal messages
 * will be sent to the handler, all others will be silently ignored. Default min is LogMessage::Type::WARNING.
 *
 * @see Logger, LogMessage, FileLogHandler, ConsoleLogHandler
 */
class ILogHandler
{
public:
	virtual ~ILogHandler() = default;

	/**
	 * Show the given message to the user.
	 *
	 * @param message the message sent by the Logger that should be presented to the user.
	 *
	 * @note This method must be overriden.
	 */
	virtual void log(const LogMessage& message) = 0;

	/**
	* Set the minimum importance of logged messages that should be received by the handler.
	*
	* You can give the minimum of importance before the messages are sent to the handler. The order is
	* as follow (defined in the enum LogMessage::Type):
	* 1. LogMessage::Type::DEBUG
	* 2. LogMessage::Type::INFO
	* 3. LogMessage::Type::WARNING
	* 4. LogMessage::Type::CRITICAL
	* 5. LogMessage::Type::FATAL
	*
	* It means that if you set the minimum to LogMessage::Type::CRITICAL, only critical and fatal messages
	* will be sent to the handler, all others will be silently ignored. Default min is LogMessage::Type::WARNING.
	*
	* @param type the minimum level of importance to set
	* @see getThreshold()
	*/
	void setThreshold(LogMessage::Type type) { _threshold = type; }
	/**
	 * @return the threshold
	 * @see setThreshold()
	 */
	LogMessage::Type getThreshold() const { return _threshold; }
	
protected:
	/** The minimum level of importance to send messages to the handlers. */
	LogMessage::Type _threshold = LogMessage::Type::WARNING;
};

#endif // ILOGHANDLER_HPP
