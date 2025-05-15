// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿

#ifndef SPIOEXCEPTION_HPP
#define SPIOEXCEPTION_HPP

#include <exception>
#include <string>

/**
 * Exception class for IO operations on @ref shpoints object.
 *
 * SPIOException is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * This class offers a way to store the filename, the contents, and the offset where the error occurred.
 */
class SPIOException : public std::exception
{
public:
	/**
	 * Constructor.
	 *
	 * @param error the error message
	 * @param filename the path to the file
	 * @param contents the contents (string where the error occurred)
	 * @param offset the offset inside the file where the error occured (by default = -1)
	 */
	SPIOException(std::string error, std::string filename = "", std::string contents = "", int offset = -1) :
		_error(std::move(error)),
		_filename(std::move(filename)),
		_contents(std::move(contents)),
		_offset(offset)
	{
	}

	virtual ~SPIOException() override = default;

	virtual const char *what() const noexcept override { return _error.c_str(); }

	/**
	 * @return the error message as a string.
	 * @see what()
	 */
	const std::string &error() const noexcept { return _error; }
	/** @return the filename where the error occurred. */
	const std::string &filename() const noexcept { return _filename; }
	/** @return the contents where the error occurred. */
	const std::string &contents() const noexcept { return _contents; }
	/** @return the offset in the file where the error occurred, if it is possible to know. -1 otherwise. */
	int offset() const noexcept { return _offset; }

private:
	/** The error message. */
	std::string _error;
	/** The filename related to the error. */
	std::string _filename;
	/** The contents related to the error. */
	std::string _contents;
	/** the offset inside the file where the error occured. */
	int _offset = -1;
};

#endif // SPIOEXCEPTION_HPP
