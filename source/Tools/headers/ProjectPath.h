/*
© Copyright CERN 2000-2023. All rights reserved. This software is released under a CERN proprietary software license.
Any permission to use it shall be granted in writing. Request shall be addressed to CERN through mail-KT@cern.ch
*/

#ifndef __PROJECTPATH__
#define __PROJECTPATH__

#include <string>

/**
 * A singleton @ProjectPath class containing only input file inputPath.
 *
 * This class is used to propagate the input inputPath throught any application using SurveyLib.
 * The inputPath can only be set once on the first call to @ProjectPath::getPath. Subsequent calls with some other inputPath do not do anything.
 * You can get an instance of this class by calling @ProjectPath::getPath (without arguments) and the absolute path with @getInputPath, or the
 * absolute path without an extension with @getExtensionlessInputPath.
 */
class ProjectPath
{
public:
	static ProjectPath &getPath(const std::string &s = "");

	~ProjectPath() = default;

	// A singleton class
	ProjectPath(const ProjectPath &) = delete;
	ProjectPath(ProjectPath &&) = delete;
	ProjectPath &operator=(const ProjectPath &) = delete;
	ProjectPath &operator=(ProjectPath &&) = delete;

	const std::string &getInputPath();
	const std::string &getExtensionlessInputPath();

private:
	/** Private constructor for a singleton. */
	ProjectPath(const std::string &path = "");

private:
	const std::string inputPath;
	const std::string extensionlessInputPath;
};

#endif // __PROJECTPATH__
