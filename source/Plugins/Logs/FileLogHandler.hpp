/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef FILELOGHANDLER_HPP
#define FILELOGHANDLER_HPP

#include "ILogHandler.hpp"

#include <string>

class LogMessage;

/**
 * Log handler that prints the logs in a file.
 *
 * You must give the path to a file to use this handler.
 *
 * Note that the logs are appended to the given file (the file is not erased).
 */
class FileLogHandler : public ILogHandler
{
public:
	/** @param file the path to the log file where to write the logs */
	FileLogHandler(const std::string& file = "") : _filePath(file) {}
	virtual ~FileLogHandler() = default;

	/** Write the message to the file. */
	virtual void log(const LogMessage& message) override;

	void setLogFile(const std::string& file) { _filePath = file; }
	const std::string& getLogFile() const { return _filePath; }

private:
	/** the path to the file where to write the logs */
	std::string _filePath;
};

#endif // FILELOGHANDLER_HPP
