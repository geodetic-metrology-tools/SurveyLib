// TLSCalcWorkingLength.cpp

#include "TLSCalcWorkingLength.h"

//////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////

// Default constructor 
TLSCalcWorkingLength::TLSCalcWorkingLength():fLastElNbr(0),fListError(false) {
}

//Destructor 
TLSCalcWorkingLength::~TLSCalcWorkingLength()
{
	fLSLengthList.clear();
}

////////////////////////////////////////////////////////////////
// PUBLIC METHODS		
////////////////////////////////////////////////////////////////

//Returns an iterator to the first element in the list 
LSLengthIter TLSCalcWorkingLength::begin() {

	return fLSLengthList.begin();
}

// Returns a const iterator to the first element in the list 
LSLengthConstIter TLSCalcWorkingLength::begin() const {

	return fLSLengthList.begin();
}

// Returns an iterator pointing after the last element in the list
LSLengthIter	TLSCalcWorkingLength::end() {

	return fLSLengthList.end();
}

// Returns a const iterator pointing after the last element in the list 
LSLengthConstIter TLSCalcWorkingLength::end() const {

	return fLSLengthList.end();
}

	
// Inserts a new TLSCalcLengthParam in the list, if it is not done yet (tests first if the object is already in the list or not)
LSLengthIter	TLSCalcWorkingLength::push_back(TLSCalcLengthParam& length) {

	LSLengthIter lsLIter;

	if(!fListError)
	{
		// Checks if the observation is already in the container or not
		bool notFound = true;

		LSLengthIter iterB = begin();
		LSLengthIter iterE = end();

		while (iterB!=iterE && notFound)
		{
			if (length == *iterB) {	
				lsLIter = iterB; 
				notFound = false;
			}
			else
				iterB++;
		}
		
		// if the observation isn't in the container -> addition at the end of the list
		if (notFound) {	
			fLSLengthList.push_back(length);
			fLastElNbr++;
			// Debugging for the case where the push_back method fails
			if(fLastElNbr == fLSLengthList.size())
			{
				//no error
				lsLIter = --(fLSLengthList.end());
			}
			else
			{
				//error
				//treat error
				fListError = true;
				lsLIter = end();
			}
		}
	}
	else
	{
		lsLIter = end();
	}
		
	return lsLIter; 

}

// Erases the selected TLSCalcLengthParam and deletes its corresponding pointer from the list if it exists
bool TLSCalcWorkingLength::erase(TLSCalcLengthParam& length) {

	bool isErased = false;

	LSLengthIter iterB = begin();
	LSLengthIter iterE = end();

	while (iterB!=iterE) {
		if (length == *iterB ) {
			fLSLengthList.erase(iterB);
			isErased = true;
			fLastElNbr--;
			iterB = iterE; }
		else
			iterB++;
	}
		
	return isErased;
}
	
