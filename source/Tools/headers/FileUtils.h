#ifndef __FILE_UTILS__
#define __FILE_UTILS__


#ifdef __linux__    
	#define slash '/'
#else
	#define slash '\\'
#endif

#include <string>


/**
* File utilities regrouped in the namespace svlTools 
*/

namespace svlTools
{
	/**
	* Returns the current directory
	*/
	std::string getCurrentDirectory();

	/**
	* Returns the full absolute path and filename, changing the slash symbols when necessary (Windows)
	* If no absolute path defined in the given filename, it appends the current directory.
	*
	* @param fileName Simple filename or complete absolute path
	*/
	std::string getPathFileName(std::string fileName);

	/**
	* Windows only method: Changes the directory path -/ become \
	*
	* @param path Reference to the path to be modified 
	*/
	void changePathDirSlash(std::string& path);


	/**
	* Returns the filename(or full path + filename) without its possible extension
	*
	* @param path Full path or filename
	*/
	std::string getFilePathWithoutExtension(const std::string& path);

	/**
	* Creates a new output file
	*
	* @param outFilePath Full path or filename
	*/
	void createOutputFile(const std::string outFilePath);
}


#endif // __FILE_UTILS__
