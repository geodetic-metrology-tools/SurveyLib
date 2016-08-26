#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
#include <utility>

namespace{

}

class Error 
{
public:

	enum ErrorCode
	{
		ERR_noError = 1,
		ERR_actionCanceled,
		ERR_projectFileMissing,
		ERR_inputFileMissing,
		ERR_FileUnReadable,
		ERR_outputFileMissing,
		ERR_noOutputFile,
		ERR_outputFileUnReadable,
		ERR_savingProjectFile,
		ERR_savingFile,
		ERR_ignoreChanges,
		ERR_readingContent,
		ERR_transformation,
		ERR_UnknownExcptInTransformation,
		ERR_VirtualProjectRemoved,

		ERR_endOfTheWorld
	};

	static std::string ErrorMessage[ERR_endOfTheWorld];
	static std::string message(unsigned int);

	Error();
	
	Error(Error const& err);
	
	Error(ErrorCode err, std::string add = "");

	~Error();

	Error& operator=(Error const& err);

	operator bool();
	
	bool operator==(ErrorCode const& code);

	bool operator[](ErrorCode const& code);
	
	Error& operator +=(Error const& err);

	std::vector<std::string> addings(ErrorCode const& code) const;

	std::vector<Error> split() const;

	Error extract(ErrorCode const& code);

	unsigned int size() const;

	ErrorCode code() const;

	std::string additionalInfo(ErrorCode const& code) const;

private:

	std::vector<std::pair<ErrorCode, std::string>> errors;
};

#endif // ERROR_H