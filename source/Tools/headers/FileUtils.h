/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef __FILE_UTILS__
#define __FILE_UTILS__

#ifdef __linux__
#	define slash '/'
#else
#	define slash '\\'
#endif

#include <string>

/**
 * File utilities regrouped in the namespace svlTools.
 *
 * This is just a wrapper around the new C++17 std::filesystem library. Prefer using directly std::filesystem from now.
 * See https://en.cppreference.com/w/cpp/filesystem
 */

namespace svlTools
{
/**
 * Returns the current directory
 */
[[deprecated("Use methods from std::filesystem instead.")]]
std::string getCurrentDirectory();

/**
 * Returns the full absolute path and filename, changing the slash symbols when necessary (Windows)
 * If no absolute path defined in the given filename, it appends the current directory.
 *
 * @param fileName Simple filename or complete absolute path
 */
[[deprecated("Use methods from std::filesystem instead.")]]
std::string getPathFileName(const std::string &fileName);

/**
 * Changes the directory path separator to std::filesystem::path::preferred_separator.
 *
 * @param path Reference to the path to be modified
 */
[[deprecated("Use methods from std::filesystem instead.")]]
void changePathDirSlash(std::string &path);

/**
 * Returns the filename(or full path + filename) without its possible extension
 *
 * @param path Full path or filename
 */
[[deprecated("Use methods from std::filesystem instead.")]]
std::string getFilePathWithoutExtension(const std::string &path);

/**
 * Creates a new output directory
 *
 * @param outFilePath Full path or filename
 */
[[deprecated("Use methods from std::filesystem instead.")]]
void createOutputFile(const std::string outFilePath);
} // namespace svlTools

#endif // __FILE_UTILS__
