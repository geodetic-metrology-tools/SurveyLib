// TLSCalcWorkingOrientation.h

#ifndef SU_LS_WORK_ORIENT
#define SU_LS_WORK_ORIENT

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLSCalcOrientationParam.h"
#include "TAMeasurement.h"

class TLSCalcWorkingOrientation {

public:

	/*!@name Constructor / Destructor */
	//@{
	/*! Default constructor */
	TLSCalcWorkingOrientation();
	/*! Destructor */
	~TLSCalcWorkingOrientation();
	//@}

	/*!@name Methods borrowed from the lists properties, named after them */
	//@{
		/*! Returns an iterator to the first element in the list */
		LSOrientIter		begin();
		/*! Returns a const iterator to the first element in the list */
		LSOrientConstIter	begin() const;
		/*! Returns an iterator pointing after the last element in the list */
		LSOrientIter		end();
		/*! Returns a const iterator pointing after the last element in the list */
		LSOrientConstIter	end() const;
		/*! Adds a new TLSCalcOrientationParam at the end of the list, if it is not done yet (tests first if the object is
		already in the list or not)
		\returns an iterator to the TLSCalcOrientationParam wether it was already inserted or just being inserted */
		LSOrientIter		push_back(TLSCalcOrientationParam& orient);
		/*! Erases the selected TLSCalcOrientationParam and deletes its corresponding pointer from the list */
		bool				erase(TLSCalcOrientationParam& orient);
		/*! Returns the size of the list*/
		int					size() const {return fLSOrientList.size();}
	//@}

private:

	LSOrientContainer	fLSOrientList; /*!< list of orientation parameters */
	int					fLastElNbr;	/*!< last number of elements in the list */
	bool				fListError; /*!< handling error attribute: false if no errors */

};

#endif //SU_LS_WORK_ORIENT