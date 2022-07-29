/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_UEOINDICES
#define SU_UEOINDICES

#ifdef USE_SERIALIZER
#include <Serializer.hpp>
#endif // USE_SERIALIZER

// Definition of the structure holding the 3 indices : 
// unknown index, equation index and observation index

//matrix index type
typedef int MatrixIndex;


//structure for unknowns, equations and observations indicies
#ifdef USE_SERIALIZER
struct UEOIndices : public Serializable
#else
struct UEOIndices
#endif // USE_SERIALIZER
{

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;

#ifdef USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(SerializerObject::SerializationHelper &obj) const
	{
		obj.addProperty("UIndex", UIndex);
		obj.addProperty("EIndex", EIndex);
		obj.addProperty("OIndex", OIndex);
	};
#endif // USE_SERIALIZER
};

#endif
