//Copyright 2017 CERN EN/ACE/SU.  All rights reserved.

//
// Definition of the structure holding the 3 indices : 
// unknown index, equation index and observation index
//

#ifndef SU_UEOINDICES
#define SU_UEOINDICES

//matrix index type
typedef int MatrixIndex;


//structure for unknowns, equations and observations indicies
struct UEOIndices{

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;

};

#endif
