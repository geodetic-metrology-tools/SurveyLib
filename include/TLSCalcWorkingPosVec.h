// TLSCalcWorkingPosVec.h

#ifndef SU_LS_WORK_POSVEC
#define SU_LS_WORK_POSVEC

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLSCalcPosVectorParam.h"
#include "TAMeasurement.h"

class TLSCalcWorkingPosVec {

public:

	/*!@name Constructor / Destructor */
	//@{
	/*! Default constructor */
	TLSCalcWorkingPosVec();
	/*! Destructor */
	~TLSCalcWorkingPosVec();
	//@}

	/*!@name Methods borrowed from the lists properties, named after them */
	//@{
		/*! Returns an iterator to the first element in the list */
		LSPosVecIter		begin() {return fLSPosVectorList.begin();}

		/*! Returns a const iterator to the first element in the list */
		LSPosVecConstIter	begin() const {return fLSPosVectorList.begin();}

		/*! Returns an iterator pointing after the last element in the list */
		LSPosVecIter		end() {return fLSPosVectorList.end();}

		/*! Returns a const iterator pointing after the last element in the list */
		LSPosVecConstIter	end() const {return fLSPosVectorList.end();}

		/*! Adds a new TLSCalcPosVectorParam at the end of the list, if it is not done yet (tests first if the object is
		already in the list or not)
		\returns an iterator to the TLSCalcPosVectorParam wether it was already inserted or just being inserted */
		LSPosVecIter	push_back(TLSCalcPosVectorParam& posVec);


		LSPosVecIter	insert(LSPosVecIter, TLSCalcPosVectorParam& posVec);

		/*! Erases the selected TLSCalcPosVectorParam and deletes its corresponding pointer from the list */
		bool	erase(TLSCalcPosVectorParam& posVec);

		/*!\return an iterator pointing to a point specified through its name*/
		LSPosVecIter		getPoint(const string);

		/*!\return a cons iterator pointing to a point specified through its name*/
		LSPosVecConstIter	getPoint(const string) const;

		/*! Returns the size of the list*/
		int					size() const {return fLSPosVectorList.size();}

		/*!function used for order posVecParam like points in thr input file
		Move Pos2 to pos1*/
		void				splice(LSPosVecIter pos1, LSPosVecIter pos2) {fLSPosVectorList.splice(pos1,fLSPosVectorList,pos2); return;}

		/*!reverse the list*/
		void				reverse() {fLSPosVectorList.reverse();return;}
	//@}

private:

	LSPosVecContainer	fLSPosVectorList; /*!< list of position vector parameters */
	int					fLastElNbr;	/*!< last number of elements in the list */
	bool				fListError; /*!< handling error attribute: false if no errors */

};

#endif //SU_LS_WORK_POSVEC