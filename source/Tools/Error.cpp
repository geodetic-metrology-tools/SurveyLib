#include <Error.h>

std::string Error::ErrorMessage[ERR_endOfTheWorld] =
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
	"Virtual project was removed because it contained no data",

	"The end of the world will be coming soon. You can go home and enjoy a last drink. You're welcome."
};

Error::Error(){}
	
Error::Error(Error const& err)
{ 
	*this = err; 
}
	
Error::Error(ErrorCode err, std::string add)
{ 
	errors.emplace_back(std::make_pair(err, add)); 
}

Error::~Error() {}

Error& Error::operator=(Error const& err)
{
	errors.clear();
	for(auto& error : err.errors)
		errors.emplace_back(error);
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
			errors.emplace_back(std::make_pair(error.first,error.second));
	return *this;
}

std::vector<std::string> Error::addings(ErrorCode const& code) const
{
	std::vector<std::string> addings;
	for(auto& error : errors)
		if(error.first == code)
			addings.emplace_back(ErrorMessage[code - 1]);
	return addings;
}