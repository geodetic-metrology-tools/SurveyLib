#include "Path.h"

#include <filesystem>
#include <stdexcept>

Path &Path::getPath(const std::string &s)
{
	static Path _instance(s);
	return _instance;
}

const std::string &Path::getInputPath()
{
	return inputPath;
}

const std::string &Path::getExtensionlessInputPath()
{
	return extensionlessInputPath;
}

Path::Path(const std::string &path) :
	inputPath(std::filesystem::path(path).make_preferred().string()), extensionlessInputPath(std::filesystem::path(inputPath).replace_extension().string())
{
	if (path.empty())
		throw std::runtime_error{"Path not initialized"};
}
