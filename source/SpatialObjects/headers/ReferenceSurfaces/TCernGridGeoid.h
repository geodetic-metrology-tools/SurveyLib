/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TCernGridGeoid.h

/** Geoid in CERN's area interpolated trought a grid of values

	Concrete Class derived from TAGeoidModel.


    Patterns:
  
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_CERN_GRID_GEOID
#define SU_CERN_GRID_GEOID


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <string>

class	TRefSystemFactory;

#include	"TPositionVector.h"
#include	"TAGeoidModel.h"
#include	"TMatrix.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Concrete Class derived from TAGeoidModel
class  TCernGridGeoid : public TAGeoidModel  
{
public:



	/**@name Constructors and Destructors */
	//@{
		/// default constructor
		TCernGridGeoid();
		
		/// constructor taking the name, the definition reference frame and ellipsoid, and the calculation reference frame
		TCernGridGeoid(const std::string &name,
			const TRefSystemFactory::EGeoid &geoidId,
			const TMatrix *N,
			const TMatrix *Eta,
			const TMatrix *Xsi,
			const TPositionVector downLeft,
			const TPositionVector upRight,
			TAReferenceFrame *def,
			TReferenceEllipsoid *ell,
			TAReferenceFrame *calc);
		
		/// Destructor
		virtual  ~TCernGridGeoid();
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
		virtual  TAngle  getDAlpha( const TSpatialPosition&, const TAngle& ) const override;

		/// Return true if the point is in the grid
		bool isInGrid(const TSpatialPosition& point) const;
	//@}


private:

	/**@name Private Functions */
	//@{
		/*!used to interpolate Eta and Xi*/
		TAngle interpolateDoV(const TMatrix &dovMatrix, const TSpatialPosition &sp, const std::string &functionCalled) const;

		/*!used to interpolate*/
		TReal splineInterpolation(const TMatrix &mat, const TSpatialPosition &spos) const;
	
		/*!Generate message for the NotInLepGridException*/
		std::stringstream generateNotInLepGridMessage(const std::string &functionCalled, const TSpatialPosition &position) const;
	//@}
	
	/**@name Member Attributes */
	//@{
			
		TMatrix						fNMatrix; /*!< N-matrix */
		TMatrix						fEtaMatrix; /*!< Eta-matrix */
		TMatrix						fXiMatrix; /*!< Xi-matrix */

		TPositionVector				fDownLeft; /*!< position vector  */
		TPositionVector				fUpRight; /*!< position vector  */
		
	//@}


	//ClassDef(TCernGridGeoid, 1)
};
/*@}*/

#endif // SU_CERN_GRID_GEOID
