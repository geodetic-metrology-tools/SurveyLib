// TALSRadialCnstrContribGenerator.cpp
//
//! Abstract base class for all LS Radial Constraint contribution generators
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TALSRadialCnstrContribGenerator.h"
////////////////////////////////////////////////////////////////


//ClassImp(TALSRadialCnstrContribGenerator)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TALSRadialCnstrContribGenerator::TALSRadialCnstrContribGenerator():
fInputMatrices(0)
{	// default constructor
}

/**Constructor setting the link to the input matrices
@param im a pointer to the LS input matrices (for the generator to know where the put the contributions)*/
TALSRadialCnstrContribGenerator::TALSRadialCnstrContribGenerator(TLSInputMatrices* im):
fInputMatrices(im)
{

}

// Copy constructor
TALSRadialCnstrContribGenerator::TALSRadialCnstrContribGenerator( const  TALSRadialCnstrContribGenerator& source ):
fInputMatrices(source.fInputMatrices)
{	

}


//Destructor
TALSRadialCnstrContribGenerator::~TALSRadialCnstrContribGenerator()
{
}

