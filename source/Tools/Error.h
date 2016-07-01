#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
#include <utility>

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

	std::string ErrorMessage[ERR_endOfTheWorld] =
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

	Error(){}
	
	Error(Error const& err)
	{ 
		*this = err; 
	}
	
	Error(ErrorCode err, std::string add = "")
	{ 
		errors.emplace_back(std::make_pair(err, add)); 
	}

	Error& operator=(Error const& err)
	{
		errors.clear();
		for(auto& error : err.errors)
			errors.emplace_back(error);
		return *this;
	}

	operator bool() 
	{ 
		bool ret = true;
		for(size_t i = 0; i < errors.size();)
			if(errors[i].first == ERR_noError)
				errors.erase(errors.begin() + i);
			else 
			{
				ret = false;
				i++;
			}
		return ret;
	}
	
	bool operator==(ErrorCode const& code)
	{
		for(auto& error : errors)
			if(error.first == code)
				return true;
		return false;
	}

	bool operator[](ErrorCode const& code)
	{
		return *this == code;
	}
	
	Error& operator +=(Error const& err)
	{
		for(auto& error : err.errors)
			// Filter : only adds real errors
			if(error.first != ERR_noError)
				errors.emplace_back(std::make_pair(error.first,error.second));
		return *this;
	}

	//Error operator+(Error& err1, Error const& err2) const
	//{
	//	err1 += err2;
	//	return err1;
	//}

	std::vector<std::string> addings(ErrorCode const& code) const
	{
		std::vector<std::string> addings;
		for(auto& error : errors)
			if(error.first == code)
				addings.emplace_back(ErrorMessage[code - 1]);
		return addings;
	}
	
	//Error(Error && t)
	//{
	//	errors.push_back(std::make_pair(ERR_noError, ""));
	//}

private:

	std::vector<std::pair<ErrorCode, std::string>> errors;
};

#endif // ERROR_H