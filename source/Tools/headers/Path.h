/*
© Copyright CERN 2000-2023. All rights reserved. This software is released under a CERN proprietary software license.
Any permission to use it shall be granted in writing. Request shall be addressed to CERN through mail-KT@cern.ch
*/

#ifndef __PATH__
#define __PATH__

#include <string>

/**
 * A singleton @Path class containing only input file inputPath.
 *
 * This class is used to propagate the input inputPath throught any application using SurveyLib.
 * The inputPath can only be set once on the first call to @Path::getPath. Subsequent calls with some other inputPath do not do anything.
 * You can get an instance of this class by calling @Path::getPath (without arguments) and the absolute path with @getInputPath, or the
 * absolute path without an extension with @getExtensionlessInputPath.
 */
class Path
{
public:
	static Path &getPath(const std::string &s = "");

	~Path() = default;

	// A singleton class
	Path(const Path &) = delete;
	Path(Path &&) = delete;
	Path &operator=(const Path &) = delete;
	Path &operator=(Path &&) = delete;

	const std::string &getInputPath();
	const std::string &getExtensionlessInputPath();

private:
	/** Private constructor for a singleton. */
	Path(const std::string &path = "");

private:
	const std::string inputPath;
	const std::string extensionlessInputPath;
};

#endif // __PATH__
