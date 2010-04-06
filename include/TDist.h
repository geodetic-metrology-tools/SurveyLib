/*!
	TDist.h : definitions of distance functions taking TLength
	objects as argument

	Patterns:
	
	Copyright 2002 CERN EST/SU. All rights reserved
*/

#ifndef SU_DIST_FCTS
#define SU_DIST_FCTS

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "TLength.h"

/*! \name Distance Fonction*/
//@{
/*! computation of the distance from 2D coordinates
	\param TLength x1, coordinate  x of the first point
	\param TLength y1, coordinate  y of the first point
	\param TLength x2, coordinate  x of the second point
	\param TLength y2, coordinate  y of the second point
	\return Distance as real
	*/
	/*!\addtogroup spatialobjects
	@{*/
	real	dist(TLength x1, TLength y1, TLength x2, TLength y2);
	/*@}*/

/*! computation of the distance from 2D coordinates
	\param real x1, coordinate  x of the first point
	\param real y1, coordinate  y of the first point
	\param real x2, coordinate  x of the second point
	\param real y2, coordinate  y of the second point
	\return Distance as real
	*/
	/*!\addtogroup spatialobjects
	@{*/
	real	dist(real x1, real y1, real x2, real y2);
	/*@}*/



/*! computation of the distance from 3D coordinates
	\param TLength x1, coordinate  x of the first point
	\param TLength y1, coordinate  y of the first point
	\param TLength z1, coordinate  z of the first point
	\param TLength x2, coordinate  x of the second point
	\param TLength y2, coordinate  y of the second point
	\param TLength z2, coordinate  z of the second point
	\return Distance as real
	*/
	/*!\addtogroup spatialobjects
	@{*/
	real	dist3D(TLength x1, TLength y1, TLength z1, TLength x2, TLength y2, TLength z2);
	/*@}*/

/*! computation of the distance from 3D coordinates
	\param real x1, coordinate  x of the first point
	\param real y1, coordinate  y of the first point
	\param real z1, coordinate  z of the first point
	\param real x2, coordinate  x of the second point
	\param real y2, coordinate  y of the second point
	\param real z2, coordinate  z of the second point
	\return Distance as real
	*/
	/*!\addtogroup spatialobjects
	@{*/
	real	dist3D(real x1, real y1, real z1, real x2, real y2, real z2);
	/*@}*/


//@}



#endif
