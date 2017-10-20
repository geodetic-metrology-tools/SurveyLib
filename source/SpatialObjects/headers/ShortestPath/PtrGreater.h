/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch


*/#ifndef PTR_GREATER
#define PTR_GREATER

#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable:4786)
#endif


template<class T>
/*!\ingroup ShortestPath
	@{*/
struct PtrGreater
{
	bool operator()(T x, T y) const { return *y < *x; }
};
/*@}*/

#endif
