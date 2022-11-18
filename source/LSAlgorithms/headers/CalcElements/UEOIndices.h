/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_UEOINDICES
#define SU_UEOINDICES

// Definition of the structure holding the 4 indices : 
// unknown index, equation index, observation index and constraint index

//matrix index type
typedef int MatrixIndex;


//structure for unknowns, equations, observations and constraints indicies
struct UEOIndices{

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;
	MatrixIndex CIndex;

};

#endif
