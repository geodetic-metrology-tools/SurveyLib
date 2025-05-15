#ifndef CONSOLELOGHANDLER_HPP
#define CONSOLELOGHANDLER_HPP

#include "ILogHandler.hpp"
#include "LogLibGlobals.hpp"

class LogMessage;

/**
 * Log handler that print the logs in the console.
 *
 * ConsoleLogHandler is part of the @ref logs module.
 * @ingroup logs
 *
 * @see logs, ILogHandler, FileLogHandler
 */
class SULIB_SHARED_EXPORT ConsoleLogHandler : public ILogHandler
{
public:
	virtual ~ConsoleLogHandler() override = default;

	/**
	 * Print the message in the standard output.
	 *
	 * If the message is LogMessage::Type::WARNING or below, the message is printed in `std::cout`.
	 * Otherwise, the message is printed in `std::cerr`.
	 */
	virtual void log(const LogMessage& message) override;
};

#endif // CONSOLELOGHANDLER_HPP
