/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// TAGeoidModel.h: 

/*!Purely Abstract Base Class (Interface) for a TGeoid.*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_A_GEOID
#define SU_A_GEOID


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>

class  TSpatialPosition;

#include "TLength.h"
#include <TAngle.h>
#include "TRefSystemFactory.h"
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Purely Abstract Base Class (Interface) for a TGeoid
class TAGeoidModel  
{
public:
	/**@name Constructors and Destructors */
	//@{
		/// default constructor
		TAGeoidModel();

		/// constructor taking the name, the definition reference frame and ellipsoid, and the calculation reference frame
		TAGeoidModel(const std::string &name, const TRefSystemFactory::EGeoid &geoidId, TAReferenceFrame *def, TReferenceEllipsoid *ell, TAReferenceFrame *calc);

		/// Destructor
		virtual  ~TAGeoidModel();
	//@}

	//!@name Member functions
	//@{
		/*! \Returns the geoidal undulation (geoidal height) at the given Point's position*/
		virtual TLength getN(const TSpatialPosition &) const = 0;
		
		/*! \Returns the deflection of the vertical in the prime vertical
		at the given Point's position*/
		virtual TAngle getEta(const TSpatialPosition &) const = 0;

		/*!\Returns the deflection of the vertical in the meridian
		at the given Point's position*/	
		virtual TAngle getXi(const TSpatialPosition &) const = 0;
		
		/*! \Returns the Laplace correction at the given Point's position*/	
		TAngle getDAlpha(const TSpatialPosition &sp) const;

		/*! \Returns the Laplace correction at the given Point's position
		(phi is given)*/
		virtual TAngle getDAlpha(const TSpatialPosition&, const TAngle&) const {TAngle null; return null;}

		/*! \Returns the name of the geoid*/
		std::string getName() const { return fName; }

		/*! \Returns the definition reference frame*/
		TAReferenceFrame *getDefRefFrame() const { return fDefRFPtr; }

		/*! \Returns the definition reference ellipsoid*/
		TReferenceEllipsoid *getDefRefEll() const { return fDefEllPtr; }

		/*! \Returns the calculation reference frame*/
		TAReferenceFrame *getCalcRefFrame() const { return fCalcRFPtr; }

		/*! \Returns the geoid identifier*/
		TRefSystemFactory::EGeoid getId() const { return fGeoidId; }

		/// Set the definiton reference frame
		void setDefRefFrame(TAReferenceFrame *def) { fDefRFPtr = def;}

		/// Set the definition reference ellipsoid
		void setRefEll(TReferenceEllipsoid *ell) { fDefEllPtr = ell;}

		/// Set the Calculation Reference Frame
		void setCalcRefFrame(TAReferenceFrame *calc) { fCalcRFPtr = calc;}
	//@}

protected:
		TSpatialPosition getSpatialPositionInRefFrame(const TSpatialPosition &sp, TAReferenceFrame *refFrame) const;
		TAngle computeLaplaceCorrection(const TSpatialPosition &position, const TAngle &latitude) const;

		/**@name Member Attributes */
		//@{
		std::string fName; /*!< name  */

		TAReferenceFrame *fDefRFPtr; /*!< pointer to the def. reference frame  */
		TReferenceEllipsoid *fDefEllPtr; /*!< pointer to the reference ellispoid  */
		TAReferenceFrame *fCalcRFPtr; /*!< pointer to the  calc. reference frame */

		TRefSystemFactory::EGeoid fGeoidId; /*!< geoid indentifier */

		//@}
};

/*@}*/



#endif // SU_A_GEOID
