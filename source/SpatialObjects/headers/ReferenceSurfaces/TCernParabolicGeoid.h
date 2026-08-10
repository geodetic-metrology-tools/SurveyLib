/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TCernParabolicGeoid.h

/** Paraboloid defined to model the geoid in CERN's area

	Concrete Class derived from TAGeoidModel.


    Patterns:
  
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_CERN_PARABOLIC_GEOID
#define SU_CERN_PARABOLIC_GEOID


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <string>

class  TRefSystemFactory;

#include  "TAGeoidModel.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Paraboloid defined to model the geoid in CERN's area
class  TCernParabolicGeoid : public TAGeoidModel  
{
public:
	// Constants for the paraboloid as given in A SIMULATION OF THE GRAVITY FIELD AROUND LEP, p. 49
	// EDMS document 308419 
	static const TAngle ang_h0;
	static const TReal a_h0;
	static const TReal b_h0;
	static const TAngle ang_LEP;
	static const TReal a_LEP;
	static const TReal b_LEP;

	/**@name Constructors and Destructors */
	//@{
		/** Constructor taking the geoid model name and the parameters of the 
		    paraboloid as arguments.
			
			The paraboloid is of the form:
			    
								a                 b
				  z = (xp*xp) * -   +   (yp*yp) * -
								2                 2
			

			Where the coordinates xp, yp are specified to be in kilometers, and
			the z-value in the obtained in centimetres

			@param ths bearing of the yp axis with respect to the Swiss x-axis
		
		*/


		TCernParabolicGeoid();

		TCernParabolicGeoid(const std::string &name, const TRefSystemFactory::EGeoid &geoidId, const TReal a, const TReal b, const TAngle ths, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc);


		/// Destructor
		virtual  ~TCernParabolicGeoid();
	//@}


	/**@name Member Functions */
	//@{
		/// Returns the geoidal undulation (geoidal height) at the given Point's position	
		virtual  TLength  getN( const TSpatialPosition& ) const;
		
		/// Returns the deflection of the vertical in the prime vertical at the given Point's position	
		virtual TAngle getEta(const TSpatialPosition &) const;
	
		/// Returns the deflection of the vertical in the meridian at the given Point's position	
		virtual  TAngle  getXi( const TSpatialPosition& ) const;

		/// Returns the Laplace correction at the given Point's position	
		virtual TAngle getDAlpha(const TSpatialPosition &, const TAngle &) const override;

	//@}

private:
		// member functions
	bool computeLocalParaboloidCoordinates(const TSpatialPosition &sp, TReal &xp, TReal &yp) const;

	//constants
	static const TReal scaleFactor;
	static const TReal scaleFactorM;

	// member attributes
	TReal  fA;
	TReal  fB;
	TReal  fThs;
	TReal  costhc, cosazp, sinthc, sinazp;
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TCernParabolicGeoid
