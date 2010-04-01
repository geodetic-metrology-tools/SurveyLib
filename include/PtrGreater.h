#ifndef PTR_GREATER
#define PTR_GREATER

#if _MSC_VER >= 1000
#pragma once
#endif

#pragma warning (disable:4786)

template<class T>
/*!\ingroup spatialobjects
	@{*/
struct PtrGreater
{
	bool operator()(T x, T y) const { return *y < *x; }
};
/*@}*/

#endif