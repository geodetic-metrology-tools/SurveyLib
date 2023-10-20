#include "ProjectPath.h"

//#include <filesystem>
#include <stdexcept>
#include <string>

std::string make_preferred(const std::string &path)
{
#ifdef _WIN32
	std::string new_path = path;
	std::replace(new_path.begin(), new_path.end(), '/', '\\');
	return new_path;
#else
	return path; // For UNIX systems, it's already '/'
#endif
}

std::string replace_extension(const std::string &path)
{
	size_t pos = path.find_last_of('.');
	if (pos == std::string::npos)
	{
		return path;
	}
	else
	{
		return path.substr(0, pos);
	}
}



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

ProjectPath::ProjectPath(const std::string &path)
//	:
//	inputPath(std::filesystem::path(path).make_preferred().string()), extensionlessInputPath(std::filesystem::path(inputPath).replace_extension().string())
{
	std::string inputPath = make_preferred(path);
	std::string extensionlessInputPath = replace_extension(inputPath);
	inputPath = extensionlessInputPath;
	if (path.empty())
		throw std::runtime_error{"ProjectPath not initialized"};
}
