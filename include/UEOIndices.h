//
// Definition of the structure holding the 3 indices : 
// unknown index, equation index and observation index
//

#ifndef SU_UEOINDICES
#define SU_UEOINDICES


#include "Quad.h"
//matrix index type
typedef int MatrixIndex;
//matrix element type
typedef quad MatrixElmt;


//structure for unknowns, equations and observations indicies
struct UEOIndices{

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;

};

#endif