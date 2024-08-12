//  TMLA2XYHeTransformation.h
/*
© Copyright CERN 2000-2024. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** The transformation from a modified local
	astronomical reference frame to a XYHe projection.


	Patterns:

*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_MLA_2_XYHE_TRANSFORMATION
#define SU_MLA_2_XYHE_TRANSFORMATION

#if _MSC_VER >= 1000
#	pragma once
#endif // _MSC_VER >= 1000

////////////////////////////////////////////////////////////////
// Forward declarations
//
// #include  <##classname##>
//
#include "TAModifiedLocalAstronomicalRF.h"
#include "TARefFrameTransformation.h"
#include "TAReferenceFrame.h"
#include "TCompositeAffTransform.h"
#include "TXYHeProjection.h"

// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! The transformation from a modified local astronomical reference frame to a XYHe projection
class TMLA2XYHeTransformation : public TARefFrameTransformation //: public TObject
{
public:
	/**@name Constructors and Destructors */
	//@{
	/// Default Constructor
	TMLA2XYHeTransformation();

	/// Constructor taking pointers to the source and destination reference frames
	TMLA2XYHeTransformation(TXYHeProjection *to);

	/// Copy Constructor
	TMLA2XYHeTransformation(const TMLA2XYHeTransformation &);

	/// Destructor
	virtual ~TMLA2XYHeTransformation();
	//@}

	/**@name Member Functions */
	//@{
	using TARefFrameTransformation::transform;

	/// Copy Assignment Operator
	TMLA2XYHeTransformation &operator=(const TMLA2XYHeTransformation &);

	/// Return a pointer to a clone of this reference frame
	virtual TMLA2XYHeTransformation *clone() const;

	/// Return a pointer to the inverse of this transformtion
	virtual TARefFrameTransformation *inverse() const;

	/// Return the source frame
	virtual TAReferenceFrame *getSourceFrame() const { return fFrom; }

	/// Return the destination frame
	virtual TAReferenceFrame *getDestinationFrame() const { return fTo; }

	/// Return the ellipsoid of the transformation
	virtual TReferenceEllipsoid *getEllipsoid() const { return fEllipsoid; }

	/// Set the XYHe source frame
	virtual void setDestinationFrame(TXYHeProjection *xyhe)
	{
		fTo = xyhe;
		return;
	}

	//! tranformation of a position vector between reference frames
	virtual bool transform(TPositionVector &pv) const;

	//@}

private:
	/// Set the MLA destination frame
	virtual void setSourceFrame(TAModifiedLocalAstronomicalRF *LA)
	{
		fFrom = LA;
		return;
	}

	/// Set the ellipsoid
	virtual void setEllipsoid(TReferenceEllipsoid *ellipsoid)
	{
		fEllipsoid = ellipsoid;
		return;
	}

	virtual TAModifiedLocalAstronomicalRF *getMLARF() const { return fFrom; }
	virtual TXYHeProjection *getXYHe() const { return fTo; }

	TAModifiedLocalAstronomicalRF *fFrom;
	TXYHeProjection *fTo;
	TReferenceEllipsoid *fEllipsoid;

	// ClassDef(TMLA2XYHeTransformation, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

#endif // SU_MLA_2_XYHE_TRANSFORMATION
