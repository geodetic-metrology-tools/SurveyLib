#include <Behavior.h>
#include <stdexcept>

std::wstring Behavior::ErrorMessage[ERR_endOfTheWorld] =
{
	L"",										// ERR_noError
	L"Files saved",								// ERR_savingOk
	L"Action canceled",							// ERR_actionCanceled
	L"Negative Scale found",					// ERR_NegativeScale
	L"Project file is missing",					// ERR_projectFileMissing
	L"Input file is missing or corrupted",		// ERR_inputFileMissing
	L"Input file exists but can't be read",		// ERR_fileUnReadable
	L"An output file is missing",				// ERR_outputFileMissing
	L"No output file has been loaded",			// ERR_noOutputFile
	L"Unable to save the project file",			// ERR_savingProjectFile
	L"Unable to save the file",					// ERR_savingFile
	L"Changes ignored",							// ERR_ignoreChanges
	L"Error when reading file content",			// ERR_readingContent
	L"Transformation exception",				// ERR_transformation
	L"Unknown Exception when transforming",		// ERR_unknownExcptInTransformation
	L"Unknown Reference Frame",					// ERR_unknownReferenceFrame
	L"Virtual project removed because empty",	// ERR_virtualProjectRemoved
	L"Error in the Input Data (LS process)",	// ERR_inputData
	L"Error in the Least Square Process",		// ERR_LSCalculation
	L"Problem with results",					// ERR_results
	
	L"The end of the world will come soon."
};

std::wstring Behavior::message(Behavior::BehaviorCode i)
{
	return ErrorMessage[i-1];
}

Behavior Behavior::extract(BehaviorCode const& code)
{
	Behavior extractedError;
	const auto& pos = errors.find(code);
	if (pos != errors.cend())
	{
		extractedError = Behavior(pos->first, pos->second);
		errors.erase(pos);
	}

	return extractedError;
}

Behavior Behavior::filterType(Behavior::Type const &type)
{
	Behavior extractedError;
	//if const auto &pos = errors.find(code);
	for (auto& err : errors)
	{
		if (Behavior(err.first, err.second).getType() == type)
		{
			extractedError += Behavior(err.first, err.second);
		}
	}
	return extractedError;
}

bool Behavior::operator==(BehaviorCode const& code) const
{
	if(size() == 0 && code == BehaviorCode::ERR_noError)
		return true;

	return errors.find(code) != errors.cend();
}

std::wstring Behavior::additionalInfo(BehaviorCode const& code) const
{
	const auto& pos = errors.find(code);
	return pos == errors.cend() ? L"" : pos->second;
}

// split the vector of codes into a list of single Errors
std::vector<Behavior> Behavior::split() const
{
	std::vector<Behavior> errorList;

	for(const auto& err : errors)
		if(err.first != ERR_noError)
			errorList.push_back(Behavior(err.first, err.second));

	return errorList;
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
		case Behavior::ERR_unknownExcptInTransformation:
		case Behavior::ERR_inputData:
		case Behavior::ERR_LSCalculation:
		case Behavior::ERR_results:
		case Behavior::ERR_unknownReferenceFrame:
			return Type::Error;

		// WARNING
		case Behavior::ERR_fileUnReadable:
		case Behavior::ERR_outputFileMissing:
		case Behavior::ERR_noOutputFile:
		case Behavior::ERR_ignoreChanges:
		case Behavior::ERR_readingContent:
		case Behavior::ERR_virtualProjectRemoved:
		case Behavior::ERR_NegativeScale:
			return Type::Warning;

		default:
			return Type::Info;
	}
}
