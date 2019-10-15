/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_UEOINDICES
#define SU_UEOINDICES

// Definition of the structure holding the 3 indices : 
// unknown index, equation index and observation index

//matrix index type
typedef int MatrixIndex;


//structure for unknowns, equations and observations indicies
struct UEOIndices{

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;

};

#endif
