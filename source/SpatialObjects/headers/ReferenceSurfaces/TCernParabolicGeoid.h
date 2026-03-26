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

		//TCernParabolicGeoid( const string& name, const TReal a, const TReal b, const TReal ths);

		TCernParabolicGeoid(const std::string &name, const TRefSystemFactory::EGeoid &geoidId, const TReal a, const TReal b, const TReal ths, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc);


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
		virtual  TAngle  getDAlpha( const TSpatialPosition& ) const;

		/// Returns the Laplace correction at the given Point's position	
		virtual TAngle getDAlpha(const TSpatialPosition &, const TAngle &) const;

		/// Returns the name of the geoid
		virtual  std::string	 getName()  const { return fName; }

		/// Get the definition reference frame
		virtual TAReferenceFrame* getDefRefFrame() const { return fDefRFPtr; }

		/// Get the definition reference ellipsoid
		virtual TReferenceEllipsoid* getDefRefEll() const { return fDefEllPtr; }

		/// Get the calculation reference frame
		virtual TAReferenceFrame* getCalcRefFrame() const { return fCalcRFPtr; }

		/// return the geoid identifier
		virtual  TRefSystemFactory::EGeoid  getGeoidId()  const { return fGeoidId; }

	//@}

private:
		// member functions
	bool computeLocalParaboloidCoordinates(const TSpatialPosition &sp, TReal &xp, TReal &yp) const;

	//constants
	static const TReal scaleFactor;
	static const TReal scaleFactorM;
	
	
	// member attributes
	std::string  fName;
	TReal  fA;
	TReal  fB;
	TReal  fThs;
	TReal  costhc, cosazp, sinthc, sinazp;

	TAReferenceFrame*			fDefRFPtr;
	TReferenceEllipsoid*		fDefEllPtr;
	TAReferenceFrame*			fCalcRFPtr;


	TRefSystemFactory::EGeoid		fGeoidId;
	

	//ClassDef(TCernParabolicGeoid, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TCernParabolicGeoid
