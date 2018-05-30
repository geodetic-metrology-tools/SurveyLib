/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef CONSOLELOGHANDLER_HPP
#define CONSOLELOGHANDLER_HPP

#include "ILogHandler.hpp"

class LogMessage;

/**
 * Log handler that print the logs in the console.
 */
class ConsoleLogHandler : public ILogHandler
{
public:
	virtual ~ConsoleLogHandler() = default;

	/**
	 * Print the message in the standard output.
	 *
	 * If the message is LogMessage::Type::WARNING or below, the message is printed in `std::cout`.
	 * Otherwise, the message is printed in `std::cerr`.
	 */
	virtual void log(const LogMessage& message) override;
};

#endif // CONSOLELOGHANDLER_HPP
