/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿#ifndef SU_UEOINDICES
#define SU_UEOINDICES

#if USE_SERIALIZER
#include <Serializer.hpp>
#endif // USE_SERIALIZER

// Definition of the structure holding the 4 indices : 
// unknown index, equation index, observation index and constraint index

//matrix index type
typedef int MatrixIndex;


//structure for unknowns, equations, observations and constraints indicies
#if USE_SERIALIZER
struct UEOIndices : public Serializable
#else
struct UEOIndices
#endif // USE_SERIALIZER
{
	UEOIndices() = default;
	UEOIndices(MatrixIndex UIndex, MatrixIndex EIndex, MatrixIndex OIndex, MatrixIndex CIndex) : UIndex(UIndex), EIndex(EIndex), OIndex(OIndex), CIndex(CIndex)
	{}

	MatrixIndex UIndex;
	MatrixIndex EIndex;
	MatrixIndex OIndex;
	MatrixIndex CIndex;

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
