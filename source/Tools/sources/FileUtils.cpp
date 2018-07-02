#include <cstdio>  
#include "FileUtils.h"
#include "Logger.hpp"

#ifdef __linux__    
#include <unistd.h>
#define GetCurrentDir getcwd
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#else
#include <direct.h>
#define GetCurrentDir _getcwd
#include <windows.h>
#include <regex>
#endif



namespace svlTools
{

	/// Returns the current directory
	std::string getCurrentDirectory() {

		char cCurrentPath[FILENAME_MAX];
		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		{
			logWarning() << "System could no retrieve the current directory!";
			return "";
		}
		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
		logDebug() << "Current directory retrieved by the system: " << cCurrentPath;
		return std::string(cCurrentPath);
	}

	/// Returns the filename including its absolute path
	/// If no absolute path defined in the given filename, it appends the current directory
	std::string getPathFileName(std::string fileName)
	{
		std::string filePath = "";
#ifdef __linux__    
		if (fileName[0] != slash)
			filePath = svlTools::getCurrentDirectory() + slash + fileName;
		else
			filePath = fileName;
#else
		svlTools::changePathDirSlash(fileName);

		std::regex disk("[[:alpha:]]:");
		if ((regex_match(fileName.substr(0, 2), disk) && fileName.substr(2, 3).compare("\\")) || fileName.substr(0, 1).compare("\\") == 0)
			filePath = fileName;
		else
			filePath = svlTools::getCurrentDirectory() + slash + fileName;
#endif
		return filePath;
	}

	/// Windows only method
	/// Change the path directory path -/ become \ (for windows)
	void changePathDirSlash(std::string& path)
	{
#ifndef __linux__
		int found = 1;
		while (found < path.length())
		{
			found = (int)path.find_first_of("/");
			if (found == std::string::npos)
				break;
			else
			{
				path = path.substr(0, found) + "\\" + path.substr(found + 1, path.length());
				found += 1;
			}
		}
#endif // !__linux__
	}

	/// Returns the filename (or full path+filename) without the possible extension
	std::string getFilePathWithoutExtension(const std::string& path)
	{
		std::size_t found = path.find_last_of(".");
		return path.substr(0, found);
	}

	/// Create the output file
	void createOutputFile(const std::string outFilePath)
	{
		std::string outputFileDirectory = outFilePath.substr(0, outFilePath.find_last_of(slash));
		//If does not exist, needs to be created
#ifdef __linux__
		struct stat st = { 0 };
		if (stat(outputFileDirectory.c_str(), &st) == -1)
			if (creat(outputFileDirectory.c_str(), S_IRWXU | S_IRWXG) == -1) {
				logWarning() << "Output directory does not exist and could not be created";
			}
#else
		CreateFile(outputFileDirectory.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		DWORD ftyp = GetFileAttributesA(outputFileDirectory.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES) { //This means that the directory still does not exist, using default one
			logWarning() << "Output directory does not exist and could not be created";
		}
#endif
	}

} // namespace svlTools
