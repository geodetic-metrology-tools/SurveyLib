// TVGeoidModel.h: 
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/*!Purely Abstract Base Class (Interface) for a TGeoid.*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_GEOID
#define SU_GEOID


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>

class  TSpatialPosition;

#include "TGeoidValues.h"
#include "TLength.h"
#include <TAngle.h>
#include "TRefSystemFactory.h"
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Purely Abstract Base Class (Interface) for a TGeoid
class TVGeoidModel //: public TObject  
{
public:

	//!@name Member functions
	//@{
		/*! \Returns the geoidal undulation (geoidal height) at the given Point's position*/
		virtual TLength getN(const TSpatialPosition&) const = 0;
		
		/*! \Returns the deflection of the vertical in the prime vertical
		at the given Point's position*/
		virtual TAngle getEta(const TSpatialPosition&) const = 0;

		/*!\Returns the deflection of the vertical in the meridian
		at the given Point's position*/	
		virtual TAngle getXi(const TSpatialPosition&) const = 0;
		
		/*! \Returns the Laplace correction at the given Point's position*/	
		virtual TAngle getDAlpha(const TSpatialPosition&) const = 0;

		/*! \Returns the Laplace correction at the given Point's position
		(phi is given)*/
		virtual TAngle getDAlpha(const TSpatialPosition&, const TAngle&) const = 0;

		/*! \Returns the name of the geoid*/
		virtual std::string	getName() const = 0;

		/*! \Returns the definition reference frame*/
		virtual TAReferenceFrame* getDefRefFrame() const = 0;

		/*! \Returns the definition reference ellipsoid*/
		virtual TReferenceEllipsoid* getDefRefEll() const = 0;

		/*! \Returns the calculation reference frame*/
		virtual TAReferenceFrame* getCalcRefFrame() const = 0;

		/*! Set the geoid identifier as an enum type*/
		virtual void setGeoidId(const TRefSystemFactory::EGeoid geoidId) = 0;

		/*! \Returns the geoid identifier*/
		virtual TRefSystemFactory::EGeoid  getGeoidId() const = 0;
	//@}
};

/*@}*/



#endif // SU_GEOID
