// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ProjectPath.h"

#include <filesystem>
#include <stdexcept>

ProjectPath &ProjectPath::getPath(const std::string &s)
{
	static ProjectPath _instance(s);
	return _instance;
}

const std::string &ProjectPath::getInputPath()
{
	return inputPath;
}

const std::string &ProjectPath::getExtensionlessInputPath()
{
	return extensionlessInputPath;
}

ProjectPath::ProjectPath(const std::string &path) :
	inputPath(std::filesystem::path(path).make_preferred().string()), extensionlessInputPath(std::filesystem::path(inputPath).replace_extension().string())
{
	if (path.empty())
		throw std::runtime_error{"ProjectPath not initialized"};
}
