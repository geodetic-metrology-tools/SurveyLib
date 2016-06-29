#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace{

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
		ERR_savingEmptyDataSet,
		ERR_readingContent,
		ERR_transformation,
		ERR_UnknownExcptInTransformation,

		ERR_endOfTheWorld
	};

	std::string ErrorMessages[ERR_endOfTheWorld] =
	{
		"",
		"Action canceled",
		"The project file is missing",
		"The input file is missing or the filename isn't provided",
		"The input file exists but can't be read",
		"An output file is missing",
		"No output file has been loaded",
		"The output file exists bun can't be read",
		"The program is unable to save the project file",
		"The program is unable to save the file",
		"The program doesn't allow to save an empty dataset"
		"Error happened when reading file content",
		"An error happened when transforming point with error code : NotInLepGridException",
		"Unknown Exception thrown during the transformation",

		"The end of the world will be coming soon. You can go home and enjoy a last drink. You're welcome."
	};
}

class Error 
{
public:

	Error() { errorCode = ERR_noError; errorMessage = additional = ""; }
	Error(ErrorCode err, std::string add = "")
	{
		errorCode = err;
		errorMessage = ErrorMessages[err-1];
		additional = add;
	}
	operator bool() { return errorCode == ERR_noError;}
	operator ErrorCode() { return errorCode; }

public:

	ErrorCode errorCode = ERR_noError;
	std::string errorMessage = "";
	std::string additional = "";
};

#endif // ERROR_H