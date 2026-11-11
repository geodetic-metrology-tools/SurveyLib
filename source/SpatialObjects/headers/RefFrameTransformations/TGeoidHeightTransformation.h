/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TGeoidHeightTransformation.h

/** Transformation between a reference frame with ellipsoidal heights and the same
	reference frame with heights above a geoid (orthometric / normal heights).

	Only the height component is modified, horizontal coordinates of the base frame are kept:
	- kHeightToEllipsoidal: h = H + N
	- kEllipsoidalToHeight: H = h - N

	The geoid undulation N is given with respect to the definition reference frame
	(and ellipsoid) of the geoid. The arithmetic on the heights is therefore done in that frame,
	which makes the transformation valid even when the base frame uses another ellipsoid.

	Patterns:

*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_GEOID_HEIGHT_TRANSFORMATION
#define SU_GEOID_HEIGHT_TRANSFORMATION

#if _MSC_VER >= 1000
#	pragma once
#endif // _MSC_VER >= 1000

#include "TARefFrameTransformation.h"

class TAGeoidModel;
class TGeoidHeightRefFrame;

/*!\ingroup spatialobjects
	@{*/

//! Transformation between ellipsoidal heights and heights above a geoid in a given base frame
class TGeoidHeightTransformation : public TARefFrameTransformation
{
public:
	//! Direction of the transformation
	enum EDirection
	{
		kHeightToEllipsoidal, //!< from TGeoidHeightRefFrame (H) to its base frame (h)
		kEllipsoidalToHeight //!< from the base frame (h) to TGeoidHeightRefFrame (H)
	};

	/**@name Constructors and Destructors */
	//@{
	/// Constructor taking the geoid height frame and the direction
	TGeoidHeightTransformation(TGeoidHeightRefFrame *frame, EDirection direction);

	/// Destructor
	virtual ~TGeoidHeightTransformation();
	//@}

	/**@name Member Functions */
	//@{
	using TARefFrameTransformation::transform;

	/// Return a pointer to a clone of this transformation
	virtual TGeoidHeightTransformation *clone() const;

	/// Return a pointer to the inverse of this transformation
	virtual TARefFrameTransformation *inverse() const;

	/// Return the source frame
	virtual TAReferenceFrame *getSourceFrame() const;

	/// Return the destination frame
	virtual TAReferenceFrame *getDestinationFrame() const;

	/// Return the direction of the transformation
	EDirection getDirection() const { return fDirection; }

	/// Transformation of a position vector: only the height is modified
	virtual bool transform(TPositionVector &pv) const;

	/// Transformation of a free vector: unchanged (height datum shift does not affect vectors)
	virtual bool transform(TFreeVector &) const { return true; }

	/// Transformation of a rotation matrix: unchanged
	virtual bool transform(TRotationMatrix &) const { return true; }
	//@}

private:
	TGeoidHeightRefFrame *fFrame; //!< the frame with heights above the geoid
	EDirection fDirection; //!< direction of the transformation
};

/*@}*/

#endif // SU_GEOID_HEIGHT_TRANSFORMATION
