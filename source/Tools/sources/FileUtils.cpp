#include "FileUtils.h"

#include <filesystem>

#include "Logger.hpp"

namespace fs = std::filesystem;

namespace svlTools
{
std::string getCurrentDirectory()
{
	return fs::current_path().make_preferred().string();
}

std::string getPathFileName(const std::string &fileName)
{
	return fs::weakly_canonical(fs::absolute(fileName)).make_preferred().string();
}

void changePathDirSlash(std::string &path)
{
	fs::path p(path);
	path = p.make_preferred().string();
}

std::string getFilePathWithoutExtension(const std::string &path)
{
	const fs::path p(path);
	return (p.parent_path() / p.stem()).make_preferred().string();
}

void createOutputFile(const std::string outFilePath)
{
	fs::path p(outFilePath);
	if (p.has_filename())
		p = p.parent_path();
	try
	{
		fs::create_directories(p);
	}
	catch (const fs::filesystem_error &e)
	{
		logWarning() << "Output directory does not exist and could not be created :'" << e.what() << "'";
	}
}
} // namespace svlTools
