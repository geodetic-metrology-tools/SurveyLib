// TALSRadialCnstrContribGenerator.h
//
//! Abstract base class for all LS Radial Constraint contribution generators
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_TALSRadialCnstrContribGenerator
#define SU_TALSRadialCnstrContribGenerator


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
class  TLSInputMatrices;
#include  "TLSCalcWorkingConstraints.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TALSRadialCnstrContribGenerator //: public TObject  
{
public:

	/**Calculates the contributions of a radial constraint and puts them in the matrices
	@param iterRC an iterator pointing to the radial constraint to be processed*/
	virtual	void	processRadialConstraint(TLSCalcWorkingConstraints::CalcRadCnstrIterator iterRC) = 0;

	///Destructor
	virtual ~TALSRadialCnstrContribGenerator();

protected:

	///Default constructor
	TALSRadialCnstrContribGenerator();
	/**Constructor
	@param im a pointer to the LS input matrices (for the generator to know where the put the contributions)*/
	explicit TALSRadialCnstrContribGenerator(TLSInputMatrices* im);
	///Copy constructor
	TALSRadialCnstrContribGenerator(const TALSRadialCnstrContribGenerator& source);

	TLSInputMatrices *									fInputMatrices;
	
};

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////
#endif // SU_TALSRadialCnstrContribGenerator
