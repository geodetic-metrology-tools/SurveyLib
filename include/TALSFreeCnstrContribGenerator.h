//TALSFreeCnstrContribGenerator.h : header file
//
/*! Base Class for a LS contrib generator
processing constraints in a free survey network*/
//
//
// Copyright 2003, CERN, EST/SU. All rights reserved.
////////////////////////////////////////////////////////////////////////////////////



#ifndef SU_TALS_FREE_CNSTRCONTGENERATOR
#define SU_TALS_FREE_CNSTRCONTGENERATOR


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
class		TLSInputMatrices;
#include	"TAObsContributionsGenerator.h"
#include	"TLSCalcPosVectorParam.h"
#include	"TLSConstraintIdentifier.h"

////////////////////
// Class declaration
////////////////////
class TALSFreeCnstrContribGenerator : public TAObsContributionsGenerator{

public :

	//!Calculates the contributions of a offset (LIBR) constraints and puts them in the matrices
	/*!\param ptIter an iterator pointing to the point which has a constraint to be processed*/
	virtual	bool	processFreeCnstr(TLSCalcWorkingPosVec* ptList,TLSInputMatrices& matrices, TLSConstraintIdentifier& cnstr) = 0;

	//!Destructor
	virtual ~TALSFreeCnstrContribGenerator();

	/*! Calculates the local contribution
	@param dx contribution for the dx freedom
	@param dy contribution for the dy freedom
	@param dz contribution for the dz freedom
	@param rx contribution for the rx freedom
	@param ry contribution for the ry freedom
	@param rz contribution for the rz freedom
	@param rz contribution for the scale freedom*/
/*	virtual void calculateLocalFreeCnstrContrib(LSPosVecConstIter cnstrIt, TLSConstraintIdentifier& cnstr,
					double& dx, double& dy, double& dz,
					double& rx, double& ry, double& rz,
					double& k);*/

	double		getRxCalcValue(LSPosVecConstIter ptIt, TLSConstraintIdentifier& cnstr);	

	double		getRyCalcValue(LSPosVecConstIter ptIt, TLSConstraintIdentifier& cnstr);	

	double		getRzCalcValue(LSPosVecConstIter ptIt, TLSConstraintIdentifier& cnstr);	

	double		getScaleCalcValue(LSPosVecConstIter ptIt, TLSConstraintIdentifier& cnstr);

protected:

	//!Default constructor
	TALSFreeCnstrContribGenerator();
	
};
#endif

