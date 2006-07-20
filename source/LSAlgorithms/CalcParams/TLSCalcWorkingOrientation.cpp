// TLSCalcWorkingOrientation.cpp

#include "TLSCalcWorkingOrientation.h"

//////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
//////////////////////////////////////////////////////////

// Default constructor 
TLSCalcWorkingOrientation::TLSCalcWorkingOrientation():fLastElNbr(0),fListError(false) {
}

//Destructor 
TLSCalcWorkingOrientation::~TLSCalcWorkingOrientation()
{
	fLSOrientList.clear();
}

////////////////////////////////////////////////////////////////
// PUBLIC METHODS		
////////////////////////////////////////////////////////////////

//Returns an iterator to the first element in the list 
LSOrientIter TLSCalcWorkingOrientation::begin() {

	return fLSOrientList.begin();
}

// Returns a const iterator to the first element in the list 
LSOrientConstIter TLSCalcWorkingOrientation::begin() const {

	return fLSOrientList.begin();
}

// Returns an iterator pointing after the last element in the list
LSOrientIter	TLSCalcWorkingOrientation::end() {

	return fLSOrientList.end();
}

// Returns a const iterator pointing after the last element in the list 
LSOrientConstIter TLSCalcWorkingOrientation::end() const {

	return fLSOrientList.end();
}

	
// Inserts a new TLSCalcOrientationParam in the list, if it is not done yet (tests first if the object is already in the list or not)
LSOrientIter	TLSCalcWorkingOrientation::push_back(TLSCalcOrientationParam& orient) {

	LSOrientIter lsOrIter;

	if(!fListError)
	{
		// Checks if the observation is already in the container or not
		bool notFound = true;

		LSOrientIter iterB = begin();
		LSOrientIter iterE = end();

		while (iterB!=iterE && notFound)
		{
			if (orient == *iterB) {	
				lsOrIter = iterB; 
				notFound = false;
			}
			else
				iterB++;
		}
		
		// if the observation isn't in the container -> addition at the end of the list
		if (notFound) {	
			fLSOrientList.push_back(orient);
			fLastElNbr++;
			// Debugging for the case where the push_back method fails
			if(fLastElNbr == fLSOrientList.size())
			{
				//no error
				lsOrIter = --(fLSOrientList.end());
			}
			else
			{
				//error
				//treat error
				fListError = true;
				lsOrIter = end();
			}
		}
	}
	else
	{
		lsOrIter = end();
	}
		
	return lsOrIter; 

}

// Erases the selected TLSCalcOrientationParam and deletes its corresponding pointer from the list if it exists
bool TLSCalcWorkingOrientation::erase(TLSCalcOrientationParam& orient) {

	bool isErased = false;

	LSOrientIter iterB = begin();
	LSOrientIter iterE = end();

	while (iterB!=iterE) {
		if (orient == *iterB ) {
			fLSOrientList.erase(iterB);
			isErased = true;
			fLastElNbr--;
			iterB = iterE; }
		else
			iterB++;
	}
		
	return isErased;
}
	
