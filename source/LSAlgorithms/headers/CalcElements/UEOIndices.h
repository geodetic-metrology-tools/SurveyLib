/*
© Copyright CERN 2000-2023. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_UEOINDICES
#define SU_UEOINDICES

#if USE_SERIALIZER
#include <Serializer.hpp>
#endif // USE_SERIALIZER

// Definition of the structure holding the 5 indices : 
// unknown index, equation index, observation index, constarint index, (unknown parameter) weights index

//matrix index type
typedef int MatrixIndex;


//structure for unknowns, equations, observations, constraints, weights indicies
#if USE_SERIALIZER
struct UEOIndices : public Serializable
#else
struct UEOIndices
#endif // USE_SERIALIZER
{
	UEOIndices() = default;
	UEOIndices(MatrixIndex UIndex, MatrixIndex EIndex, MatrixIndex OIndex, MatrixIndex CIndex, MatrixIndex WIndex) : UIndex(UIndex), EIndex(EIndex), OIndex(OIndex), CIndex(CIndex), WIndex(WIndex)
	{}

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;
	MatrixIndex CIndex;
	MatrixIndex WIndex;

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const
	{
		obj.addProperty("UIndex", UIndex);
		obj.addProperty("EIndex", EIndex);
		obj.addProperty("OIndex", OIndex);
		obj.addProperty("CIndex", CIndex);
	};
#endif // USE_SERIALIZER
};

#endif
