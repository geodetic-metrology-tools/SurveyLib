
/*!
	Behavior.h

	This class groups behavioral information of a process. 
	Lot of errors can occur during a process like reading or saving a project. Running a Least Square algorithm, doing transformations on data, etc...
	This class is in charge of these errors storage. It provides a c++ standard code being integrated in all software core, devoid from external libraries.
	It groups in a list : error codes, descripting the error/behavioral problem, and an additional information, software dependant. 
	It provides common errors associated to common messages, available for every software using the SurveyLib. 
	Moreover, it's used by a component of the GraphicalLibrary : The InfoStack. This component displays common widgets in a common view with the provided messages and displaying the additional one, software dependant.
*/

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <string>
#include <unordered_map>
#include <vector>

class Behavior
{
public:

	// Behavior code. Some ones might be used for behavioral information
	enum BehaviorCode
	{
		//! Default code. Can be pushed but means that everything is ok
		ERR_noError = 1,
		//! Behavioral code meaning that the saving is ok
		ERR_savingOk,
		//! Can be pushed when an action is canceled
		ERR_actionCanceled,
		//! Negative Scale found after a first iteration and resolved (used by Chaba)
		ERR_NegativeScale,
		//! Can be pushed when a project file is missing
		ERR_projectFileMissing,
		//! Can be pushed when a input file is missing 
		ERR_inputFileMissing,
		//! Usefull to alert that a file exists but isn't readable
		ERR_fileUnReadable,
		//! Can be pushed when an output file is missing 
		ERR_outputFileMissing,
		//! Alert from the absence of output file
		ERR_noOutputFile,
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
		//! Means that this exception was thrown during a transformation process. (The exception is from the SurveyLib)
		ERR_unknownExcptInTransformation,
		//! ReferenceFrame not recognized
		ERR_unknownReferenceFrame,
		//! Usefull within CSGeo
		ERR_virtualProjectRemoved,
		//! Misc Warning
		ERR_miscWarning,
	
		
		//error for LS process:
		//! error with the input data
		ERR_inputData,
		//! Error during the LS calculation
		ERR_LSCalculation,
		//! Problem detected by consistency checker
		ERR_consistencyCheck,
		//! Error with the results
		ERR_results,

		//! This Error code shall never be used. It's sometimes so as to describe a behavior that should never happen. It it does, there is a problem when manipulating this class.
		ERR_endOfTheWorld
	};

	// Behavior type
	enum Type {
		//! type reserved for real problems/errors (problem of calculation, input data, ...)
		Error,
		//! type associated for warnings : (means something gone wrong but doesn't avoid the processing)
		Warning,
		//! Information type : Gives relevant information to the user
		Info
	};

	//! Message table declaration
	static std::wstring ErrorMessage[ERR_endOfTheWorld];
	//! Returns message to the associated code
	static std::wstring message(BehaviorCode);

	//! Default ctor
	Behavior() {}

	//! Param ctor. The most used, taking a code an potential additional information
	Behavior(BehaviorCode err, std::wstring add = L"") { errors.emplace(err, add); }

	//! Returns true when no error exists, and delete noError codes at the same time.
	operator bool() { return errors.size() == errors.count(BehaviorCode::ERR_noError); }

	//! Allows to know if the errors owns this error code. Same as []op
	bool operator==(BehaviorCode const& code) const;

	//! Allows to know if the errors owns this error code. Same as ==op
	bool operator[](BehaviorCode const& code) const { return *this == code; }

	//! Allows to know if the errors owns this error code.
	bool operator!=(BehaviorCode const& code) const { return !(*this == code); }

	//! Allows to add two errors
	Behavior& operator+=(Behavior const& err) { errors.insert(err.errors.cbegin(), err.errors.cend()); return *this; }

	//! Retrieves the additional information (software dependant) of the first code pair
	std::wstring additionalInfo(BehaviorCode const& code) const;

	//! Retrieves a vector of errors with unique codes. Might be empty
	std::vector<Behavior> split() const;

	//! Retrieves a unique error from *this, by removing the code from *this. 
	//  If the code doesn't belong to this, it returns an empty error.
	Behavior extract(BehaviorCode const& code);

	//! Retrieves all the errors from a certain type
	Behavior filterType(Behavior::Type const &Type);

	//! Returns the numbers of codes include ERR_noError
	size_t size() const { return errors.size(); }

	//! Retrieves the code of the first error of the table, else ERR_noError
	BehaviorCode code() const { return errors.empty() ? ERR_noError : errors.cbegin()->first; }

	//! Retrieves the type of the error, associated to the BehaviorCode
	Type getType() const;

private:

	//! pairs of codes and additional information
	std::unordered_multimap<BehaviorCode, std::wstring> errors;
};

#endif // BEHAVIOR_H
