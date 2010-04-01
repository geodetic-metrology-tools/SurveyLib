//TLSLocalSysFreeCnstrCG.h : header file
//
/*!Concrete Class for a LS contrib generator processing
 constraints for free calculation defined in a local system*/
//
// Copyright 2003, CERN, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////////////////////////




#ifndef SU_TLSLOCALSYS_LIBR_CG
#define SU_TLSLOCALSYS_LIBR_CG


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
//class TFreeCnstrMeas;

#include "TALSFreeCnstrContribGenerator.h"
#include "TDist.h"


////////////////////
// Class declaration
////////////////////
class TLSLocalSysFreeCnstrCG : public TALSFreeCnstrContribGenerator{

public :

	/*!@name Constructors / Destructor*/
	//@{
		//!Default constructor
		TLSLocalSysFreeCnstrCG();
		//!Destructor
		virtual ~TLSLocalSysFreeCnstrCG();
	//@}

	//!Calculates the contributions of a constraint and puts them in the matrices
	/*!\param ptIt an iterator pointing to the point which has a constraint to be processed*/
	virtual	bool	processFreeCnstr(TLSCalcWorkingPosVec* ptList,TLSInputMatrices& matrices, TLSConstraintIdentifier& cnstr);
	

};
#endif

