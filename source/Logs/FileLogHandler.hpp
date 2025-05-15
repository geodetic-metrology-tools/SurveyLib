// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#ifndef FILELOGHANDLER_HPP
#define FILELOGHANDLER_HPP

#include <string>

#include "ILogHandler.hpp"
#include "LogLibGlobals.hpp"

class LogMessage;

/**
 * Log handler that prints the logs in a file.
 *
 * FileLogHandler is part of the @ref logs module.
 * @ingroup logs
 *
 * You must give the path to a file to use this handler.
 *
 * Note that the logs are appended to the given file (the file is not erased).
 *
 * @see logs, ILogHandler, ConsoleLogHandler
 */
class SULIB_SHARED_EXPORT FileLogHandler : public ILogHandler
{
public:
	/**
	 * Add the date to the filename.
	 *
	 * the date is added like this:
	 * - given original filename: "path/to/file.log"
	 * - new file name: "path/to/file_yyyy-mm-dd.log"
	 *
	 * @param filename the path we want to change the file name
	 * @return the new filename
	 */
	static std::string addDate(const std::string &filename);
	/**
	 * Remove all the files corresponding to the given file name older than nbdays.
	 *
	 * Remove all the files assuming they have been generated with FileLogHandler::addDate().
	 * - assuming filename is: "path/to/file.log"
	 * - will remove all files in the format "path/to/file_yyyy-mm-dd.log" if the date is older enough.
	 *
	 * @param filename the base filename.
	 * @param nbdays the number of days from which the files should be deleted
	 */
	static void removeOldLogs(const std::string &filename, int nbdays = 15);

	/** @param file the path to the log file where to write the logs */
	FileLogHandler(std::string file = "") noexcept : ILogHandler(), _filePath(std::move(file)) {}
	virtual ~FileLogHandler() override = default;

	/** Write the message to the file. */
	virtual void log(const LogMessage &message) override;

	void setLogFile(std::string file) noexcept { _filePath = std::move(file); }
	const std::string &getLogFile() const noexcept { return _filePath; }

private:
	/** the path to the file where to write the logs */
	std::string _filePath;
};

#endif // FILELOGHANDLER_HPP
