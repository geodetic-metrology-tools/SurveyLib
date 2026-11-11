/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TGeoidHeightRefFrame.h

/** A reference frame identical to a base reference frame with ellipsoidal heights
	(geodetic frame in kGeodetic, or 2D+1 projection in k2DPlusH), except that the
	third coordinate is a height above a geoid model (H = h - N).

	The frame is not part of TGraph: it is connected to its base frame (which is in the graph)
	by a TGeoidHeightTransformation, the same way local frames are connected to their
	geodetic frame (see TAReferenceFrame::transform).

	Instances are owned by TRefSystemFactory, see TRefSystemFactory::getGeoidHeightRefFrame.

	Patterns: decorator of a reference frame

*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_GEOID_HEIGHT_REF_FRAME
#define SU_GEOID_HEIGHT_REF_FRAME

#if _MSC_VER >= 1000
#	pragma once
#endif // _MSC_VER >= 1000

#include <memory>
#include <string>

#include "TAReferenceFrame.h"

class TAGeoidModel;
class TGeoidHeightTransformation;

/*! \ingroup spatialobjects
	@{*/

//! Reference frame with heights above a geoid, built on top of a frame with ellipsoidal heights
class TGeoidHeightRefFrame : public TAReferenceFrame
{
public:
	/*!@name Constructors and Destructors */
	//@{
	/*! Constructor taking the base frame (with ellipsoidal heights) and the geoid model.
		\throw std::invalid_argument if the base frame is neither a TGeodeticRefFrame nor a TA2DPlus1MapProjection,
		or if the base frame is itself not in the graph */
	TGeoidHeightRefFrame(TAReferenceFrame *base, TAGeoidModel *geoid);

	//! Destructor
	virtual ~TGeoidHeightRefFrame();
	//@}

	/*!@name Member functions */
	//@{
	//! Return the base frame (ellipsoidal heights)
	TAReferenceFrame *getBaseRF() const { return fBase; }

	//! Return the geoid model
	TAGeoidModel *getGeoid() const { return fGeoid; }

	//! Coordinate system of the coordinates in this frame (kGeodetic or k2DPlusH)
	TCoordSysFactory::ECoordSys getHeightCoordSys() const { return fHeightCoordSys; }

	//! The frame is not in the graph: it is connected to its base frame
	virtual bool isInGraph() const { return false; }

	//! Frame used to enter the graph: the base frame
	virtual TAReferenceFrame *getGraphAnchorRF() const { return fBase; }

	//! Geodetic reference frame of the base frame
	virtual TGeodeticRefFrame *getGeodeticRF() const;

	//! Transformation from this frame to its base frame (h = H + N)
	virtual TARefFrameTransformation *getRFTransfo2CGRF();
	//@}

	/*!@name TVReferenceFrame's data extraction methods
		Only getHeightCoordSys() is supported, 3D cartesian coordinates have no meaning with geoid heights */
	//@{
	virtual TPositionVector getCoordinates(const TSpatialPosition *sp, TCoordSysFactory::ECoordSys) const;
	virtual TFreeVector getElements(const TSpatialVector *sv, TCoordSysFactory::ECoordSys) const;
	virtual TRotationMatrix getElements(const TSpatialOrientation *so, TCoordSysFactory::ECoordSys) const;
	//@}

	/*!@name TVReferenceFrame's settings methods */
	//@{
	virtual bool setCoordinates(TSpatialPosition *sp, const TPositionVector &pv);
	virtual bool setElements(TSpatialVector *sv, const TFreeVector &fv);
	virtual bool setElements(TSpatialOrientation *so, const TRotationMatrix &rm);
	//@}

private:
	TGeoidHeightRefFrame(const TGeoidHeightRefFrame &);
	TGeoidHeightRefFrame &operator=(const TGeoidHeightRefFrame &);

	static std::string buildName(TAReferenceFrame *base, TAGeoidModel *geoid);

	TAReferenceFrame *fBase; //!< base frame, with ellipsoidal heights (not owned)
	TAGeoidModel *fGeoid; //!< geoid model (not owned)
	TCoordSysFactory::ECoordSys fHeightCoordSys; //!< kGeodetic or k2DPlusH
	std::unique_ptr<TGeoidHeightTransformation> fToBase; //!< H -> h transformation
};

/*@}*/

#endif // SU_GEOID_HEIGHT_REF_FRAME
