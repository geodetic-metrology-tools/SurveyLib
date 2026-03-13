/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TModifiedLocalGeodeticRF.h

/** A Geodetic Ellisoidal Reference Frame. 
    Deals with requests for Spatial Position coordinates
    appropriate to a Geodetic reference frame.

  
    Patterns:
    A concrete STATE of a Spatial Position

*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_LOC_GEODETIC_REFERENCE_FRAME
#define SU_LOC_GEODETIC_REFERENCE_FRAME


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
//
class  TSpatialPosition;
//class  TGraph;
class  TReferenceEllipsoid;
class TGeodeticRefFrame;
class TLG2GCTransformation;
#include  "TA3DEuclideanRefFrame.h"
#include  "TSpatialOrientation.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! A Geodetic Ellisoidal Reference Frame
class  TModifiedLocalGeodeticRF : public TA3DEuclideanRefFrame  
{
public:
	
	/**@name Constructors and Destructors */
	//@{

		/// Default constructor
		TModifiedLocalGeodeticRF( const std::string& name );

		/// Constructor for a local geodetic reference frame
		TModifiedLocalGeodeticRF( const std::string& name, const TSpatialPosition spos,
			TGeodeticRefFrame* GRF );

		/// Constructor taking the name of the reference frame
		TModifiedLocalGeodeticRF( const std::string& name, const TSpatialPosition spos,
			const TFreeVector falseOrigin, const TSpatialOrientation orientation,
			TGeodeticRefFrame* GRF);

		/// Constructor taking the name of the reference frame, the geoid id.,
		/// the origin and the false origin in CCS and the beam gis. and slope
		TModifiedLocalGeodeticRF( const std::string& name, TSpatialPosition origin,
			TFreeVector falseOrigin, const TAngle gis, const TAngle slope, TGeodeticRefFrame* GRF);

		/// Destructor
		virtual  ~TModifiedLocalGeodeticRF();
	//@}


	/**@name Member Functions */
	//@{
		using TA3DEuclideanRefFrame::getOrientation;

		//! Returns the geodetic system for the local RF
		virtual TGeodeticRefFrame* getGeodeticRF() const { return fGeodeticSys; }

		//! Returns the origin of the local RF
		virtual TSpatialPosition getOrigin() const { return fOrigin; }
		
		virtual bool isInGraph() const { return false; }

		virtual TARefFrameTransformation* getRFTransfo2CGRF();

		//! Returns a pointer to the references ellipsoid
		//TReferenceEllipsoid* getReferenceEllipsoid() const;

		//! Returns the false origin of the modified local RF
		TFreeVector getFalseOrigin() const { return fFalseOrigin; }

		//! Returns the orientation matrix 
		TSpatialOrientation getOrientation() const { return fOrientationMatrix; }

		//! Returns the coordinates
		virtual TPositionVector getCoordinates(const TSpatialPosition *sp, TCoordSysFactory::ECoordSys coordsys) const override;
	//@}


protected:



private:
	// We don't want these accessible
	// Copy Constructor 
	TModifiedLocalGeodeticRF( const TModifiedLocalGeodeticRF& );

	// Copy Assignment Operator 
	TModifiedLocalGeodeticRF& operator=( const TModifiedLocalGeodeticRF& );
	
	// constants
	static const TReal precisionH;
	static const TReal precisionPhi;

	//typedef
	typedef struct {TReal phi; TReal lambda; TReal h;} TGeodeticCoords;

	

private:
	
	TSpatialPosition			fOrigin; /*!< origin */
	TGeodeticRefFrame*			fGeodeticSys;/*!< geodetic ref. frame */

	TFreeVector					fFalseOrigin; /*!< false origin */
	TSpatialOrientation			fOrientationMatrix; /*!< orientation matrix */
	TLG2GCTransformation*       fTrafoCGRF;

};

/*@}*/
//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_GEODETIC_REFERENCE_FRAME
