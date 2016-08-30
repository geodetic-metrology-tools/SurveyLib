/*!
	Error.h

	This class groups behavioral information of a process. 
	Lot of errors can occur during a process like reading or saving a project. Running a Least Square algorithm, doing transformations on data, etc...
	This class is in charge of these errors storage. It provides a c++ standard code being integrated in all software core, devoid from external libraries.
	It groups in a list : error codes, descripting the error/behavioral problem, and an additional information, software dependant. 
	It provides common errors associated to common messages, available for every software using the SurveyLib. 
	Moreover, it's used by a component of the GraphicalLibrary : The InfoStack. This component displays common widgets in a common view with the provided messages and displaying the additional one, software dependant.
*/

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
#include <utility>

class Error 
{
public:

	// Error code. Some ones might be used for behavioral information
	enum ErrorCode
	{
		//! Default code. Can be pushed but means that everything is ok
		ERR_noError = 1,
		//! Can be pushed when an action is canceled
		ERR_actionCanceled,
		//! Can be pushed when a project file is missing
		ERR_projectFileMissing,
		//! Can be pushed when a input file is missing 
		ERR_inputFileMissing,
		//! Usefull to alert that a file exists but isn't readable
		ERR_FileUnReadable,
		//! Can be pushed when an output file is missing 
		ERR_outputFileMissing,
		//! Alert from the absence of output file
		ERR_noOutputFile,
		//! Usefull when an output file is unreadable
		ERR_outputFileUnReadable,
		//! Error occurs when saving the project file
		ERR_savingProjectFile,
		//! Error occurs when saving a file
		ERR_savingFile,
		//! behavioral information : Modifications have been ignored (unsave a modified project for exemple)
		ERR_ignoreChanges,
		//! A problem occured when reading the content of a file
		ERR_readingContent,
		//! A problem occured during a transformation (usefull at least in CSGeo)
		ERR_transformation,
		//! Means that this exception was thrown during a process. (The exception is from the SurveyLib)
		ERR_UnknownExcptInTransformation,
		//! Usefull within CSGeo
		ERR_VirtualProjectRemoved,
		//! This Error code shall never be used. It's sometimes so as to describe a behavior that should never happen. It it does, there is a problem when manipulating this class.
		ERR_endOfTheWorld
	};

	//! Message table declaration
	static std::string ErrorMessage[ERR_endOfTheWorld];
	//! Returns message to the associated code
	static std::string message(Error::ErrorCode);

	//! Default ctor
	Error();
	//! Copy ctor
	Error(Error const& err);
	//! Param ctor. The most used, taking a code an potential additional information
	Error(ErrorCode err, std::string add = "");
	//! dtor
	~Error();
	//! Copy operator
	Error& operator=(Error const& err);
	//! Returns true when no error exists, and delete noError codes at the same time.
	operator bool();
	//! Allows to know if the errors owns this error code. Same as []op
	bool operator==(ErrorCode const& code);
	//! Allows to know if the errors owns this error code. Same as ==op
	bool operator[](ErrorCode const& code);
	//! Allows to add two errors
	Error& operator +=(Error const& err);
	//! Retrieves the additional information (software dependant) of the first code pair
	std::string additionalInfo(ErrorCode const& code) const;
	//! Retrieves a vector of errors with unique codes. Might be empty
	std::vector<Error> split() const;
	//! Retrieves a unique error from *this, by removing the code from *this. 
	//  If the code doesn't belong to this, it returns an empty error.
	Error extract(ErrorCode const& code);
	//! Returns the numbers of codes include ERR_noError
	unsigned int size() const;
	//! Retrieves the code of the first error of the table, else ERR_noError
	ErrorCode code() const;

private:

	//! pairs of codes and additional information
	std::vector<std::pair<ErrorCode, std::string>> errors;
};

#endif // ERROR_H