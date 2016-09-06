#include <Behavior.h>

std::string Behavior::ErrorMessage[ERR_endOfTheWorld] =
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

std::string Behavior::message(Behavior::BehaviorCode i)
{
	return ErrorMessage[i-1];
}

Behavior::Behavior(){}
	
Behavior::Behavior(Behavior const& err)
{ 
	*this = err; 
}
	
Behavior::Behavior(BehaviorCode err, std::string add)
{ 
	errors.push_back(std::make_pair(err, add)); 
}

Behavior::~Behavior() {}

Behavior& Behavior::operator=(Behavior const& err)
{
	errors.clear();
	for(auto& error : err.errors)
		errors.push_back(error);
	return *this;
}

Behavior::operator bool() 
{ 
	bool ret = true;
	for(size_t i = 0; i < errors.size();)
		if(errors[i].first == Behavior::BehaviorCode::ERR_noError)
			errors.erase(errors.begin() + i);
		else 
		{
			ret = false;
			i++;
		}
	return ret;
}

Behavior Behavior::extract(BehaviorCode const& code)
{
	Behavior extractedError;

	for(size_t i = 0; i < errors.size();)
		if(errors[i].first == code)
		{
			extractedError = Behavior(errors[i].first, errors[i].second);
			errors.erase(errors.begin() + i);
			return extractedError;
		}
		else
			i++;

	return extractedError;
}
	
bool Behavior::operator==(BehaviorCode const& code)
{
	for(auto& error : errors)
		if(error.first == code)
			return true;
	return false;
}

bool Behavior::operator[](BehaviorCode const& code)
{
	return *this == code;
}
	
Behavior& Behavior::operator +=(Behavior const& err)
{
	for(auto& error : err.errors)
		// Filter : only adds real errors
		if(error.first != Behavior::BehaviorCode::ERR_noError)
			errors.push_back(std::make_pair(error.first,error.second));
	return *this;
}

std::string Behavior::additionalInfo(BehaviorCode const& code) const
{
	for(auto& err : errors)
		if(err.first == code)
			return err.second;
	return "";
}

// split the vector of codes into a list of single Errors
std::vector<Behavior> Behavior::split() const
{
	std::vector<Behavior> errorList;

	for(auto& err : errors)
		if(err.first != ERR_noError)
			errorList.push_back(Behavior(err.first, err.second));

	return errorList;
}

unsigned int Behavior::size() const
{
	return unsigned int(errors.size());
}

// return no_Error or the first code
Behavior::BehaviorCode Behavior::code() const
{
	return (size() == 0) ? ERR_noError : errors[0].first;
}

Behavior::Type Behavior::getType() const
{
	switch(code())
	{
		// INFO
		case Behavior::ERR_noError:
		case Behavior::ERR_savingOk:
		case Behavior::ERR_endOfTheWorld:
		case Behavior::ERR_actionCanceled:
			return Type::Info;

		// ERROR
		case Behavior::ERR_projectFileMissing:
		case Behavior::ERR_inputFileMissing:
		case Behavior::ERR_savingProjectFile:
		case Behavior::ERR_savingFile:
		case Behavior::ERR_transformation:
		case Behavior::ERR_UnknownExcptInTransformation:
		case Behavior::ERR_inputData:
		case Behavior::ERR_LSCalculation:
		case Behavior::ERR_results:
			return Type::Error;

		// WARNING
		case Behavior::ERR_FileUnReadable:
		case Behavior::ERR_outputFileMissing:
		case Behavior::ERR_noOutputFile:
		case Behavior::ERR_outputFileUnReadable:
		case Behavior::ERR_ignoreChanges:
		case Behavior::ERR_readingContent:
		case Behavior::ERR_VirtualProjectRemoved:
			return Type::Warning;

		default:
			return Type::Info;
	}
}