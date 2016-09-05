#include <Error.h>

std::string Error::ErrorMessage[ERR_endOfTheWorld] =
{
	"",
	"Files saved",
	"Action canceled",
	"Project file is missing",
	"Input file is missing or corrupted",
	"Input file exists but can't be read",
	"An output file is missing",
	"No output file has been loaded",
	"Output file exists bun can't be read",
	"Unable to save the project file",
	"Unable to save the file",
	"Changes ignored",
	"Error when reading file content",
	"Transformation exception : NotInLepGrid",
	"Unknown Exception when transforming",
	"Virtual project removed because empty",
	"Problem with input data",
	"Problem of calculation ",
	"Problem with results",

	"The end of the world will come soon."
};

std::string Error::message(Error::ErrorCode i)
{
	return ErrorMessage[i-1];
}

Error::Error(){}
	
Error::Error(Error const& err)
{ 
	*this = err; 
}
	
Error::Error(ErrorCode err, std::string add)
{ 
	errors.push_back(std::make_pair(err, add)); 
}

Error::~Error() {}

Error& Error::operator=(Error const& err)
{
	errors.clear();
	for(auto& error : err.errors)
		errors.push_back(error);
	return *this;
}

Error::operator bool() 
{ 
	bool ret = true;
	for(size_t i = 0; i < errors.size();)
		if(errors[i].first == Error::ErrorCode::ERR_noError)
			errors.erase(errors.begin() + i);
		else 
		{
			ret = false;
			i++;
		}
	return ret;
}

Error Error::extract(ErrorCode const& code)
{
	Error extractedError;

	for(size_t i = 0; i < errors.size();)
		if(errors[i].first == code)
		{
			extractedError = Error(errors[i].first, errors[i].second);
			errors.erase(errors.begin() + i);
			return extractedError;
		}
		else
			i++;

	return extractedError;
}
	
bool Error::operator==(ErrorCode const& code)
{
	for(auto& error : errors)
		if(error.first == code)
			return true;
	return false;
}

bool Error::operator[](ErrorCode const& code)
{
	return *this == code;
}
	
Error& Error::operator +=(Error const& err)
{
	for(auto& error : err.errors)
		// Filter : only adds real errors
		if(error.first != Error::ErrorCode::ERR_noError)
			errors.push_back(std::make_pair(error.first,error.second));
	return *this;
}

std::string Error::additionalInfo(ErrorCode const& code) const
{
	for(auto& err : errors)
		if(err.first == code)
			return err.second;
	return "";
}

// split the vector of codes into a list of single Errors
std::vector<Error> Error::split() const
{
	std::vector<Error> errorList;

	for(auto& err : errors)
		if(err.first != ERR_noError)
			errorList.push_back(Error(err.first, err.second));

	return errorList;
}

unsigned int Error::size() const
{
	return unsigned int(errors.size());
}

// return no_Error or the first code
Error::ErrorCode Error::code() const
{
	return (size() == 0) ? ERR_noError : errors[0].first;
}
