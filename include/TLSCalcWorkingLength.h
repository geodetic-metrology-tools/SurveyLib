// TLSCalcWorkingLength.h

#ifndef SU_LS_WORK_LENGTH
#define SU_LS_WORK_LENGTH

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLSCalcLengthParam.h"
#include "TAMeasurement.h"

class TLSCalcWorkingLength {

public:

	/*!@name Constructor / Destructor */
	//@{
	/*! Default constructor */
	TLSCalcWorkingLength();
	/*! Destructor */
	~TLSCalcWorkingLength();
	//@}

	/*!@name Methods borrowed from the lists properties, named after them */
	//@{
		/*! Returns an iterator to the first element in the list */
		LSLengthIter		begin();
		/*! Returns a const iterator to the first element in the list */
		LSLengthConstIter	begin() const;
		/*! Returns an iterator pointing after the last element in the list */
		LSLengthIter		end();
		/*! Returns a const iterator pointing after the last element in the list */
		LSLengthConstIter	end() const;
		/*! Adds a new TLSCalcLengthParam at the end of the list, if it is not done yet (tests first if the object is
		already in the list or not)
		\returns an iterator to the TLSCalcLengthParam wether it was already inserted or just being inserted */
		LSLengthIter		push_back(TLSCalcLengthParam& length);
		/*! Erases the selected TLSCalcLengthParam and deletes its corresponding pointer from the list */
		bool				erase(TLSCalcLengthParam& length);
		/*! Returns the size of the list*/
		int					size() const {return fLSLengthList.size();}
	//@}

private:

	LSLengthContainer	fLSLengthList; /*!< list of length parameters */
	int					fLastElNbr;	/*!< last number of elements in the list */
	bool				fListError; /*!< handling error attribute: false if no errors */

};

#endif //SU_LS_WORK_LENGTH