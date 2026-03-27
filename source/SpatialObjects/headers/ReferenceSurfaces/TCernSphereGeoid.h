/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TCernSphereGeoid.h

/** Geoid in CERN's area interpolated trought a Sphere of values

	Concrete Class derived from TAGeoidModel.


    Patterns:

*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_CERN_SPHE_GEOID
#define SU_CERN_SPHE_GEOID


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include	<string>

class	TRefSystemFactory;

#include	"TPositionVector.h"
#include	"TAGeoidModel.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Concrete Class derived from TAGeoidModel
class  TCernSphereGeoid : public TAGeoidModel  
{
public:



	/**@name Constructors and Destructors */
	//@{
		/// default constructor
		TCernSphereGeoid();
		
		/// constructor taking the name, the definition reference frame and ellipsoid, and the calculation reference frame
		TCernSphereGeoid(const std::string &name, const TRefSystemFactory::EGeoid& geoidId, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc);
		
		/// Destructor
		virtual  ~TCernSphereGeoid();
	//@}


	/**@name Member Functions */
	//@{
		/// Returns the geoidal undulation (geoidal height) at the given Point's position	
		virtual  TLength  getN( const TSpatialPosition& ) const;
		
		/// Returns the deflection of the vertical in the prime vertical at the given Point's position	
		virtual  TAngle  getEta( const TSpatialPosition& ) const;
		
		/// Returns the deflection of the vertical in the meridian at the given Point's position	
		virtual  TAngle  getXi( const TSpatialPosition& ) const;
		
		/// Returns the Laplace correction at the given Point's position (phi is given)	
		virtual  TAngle  getDAlpha( const TSpatialPosition&, const TAngle& ) const;
	//@}

};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_CERN_SPHE_GEOID
