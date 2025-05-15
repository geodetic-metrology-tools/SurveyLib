/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿// T3DLocalRefFrame.h


/*!
	class for a local 3D cartesian reference frame

	Pattern:

*/

#ifndef SU_3D_LOCAL_REFFRAME
#define SU_3D_LOCAL_REFFRAME

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


///////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
//
class  TSpatialPosition;
class  TSpatialVector;
class  TReferenceEllipsoid;
#include  "TA3DEuclideanRefFrame.h"
#include  "TPositionVector.h"
/////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Defines a local 3D cartesian system
class T3DLocalRefFrame : public TA3DEuclideanRefFrame {

public:

	/*!@name Constructors/Destructors*/
	//@{
	/*! Constructor taking the name of the ref.frame */
	T3DLocalRefFrame( const std::string& name );
	/*! Destructors */
	~T3DLocalRefFrame();
	//@}

	/*!@name Access and setting methods */
	//@{
	/*! Returns a position vector with the cartesian coordinates */
	virtual TPositionVector getCoordinates(const TSpatialPosition* sp, TCoordSysFactory::ECoordSys) const;
	/*! set the coordinates of a tSpatialPosition as a TPositionVector */
	virtual bool setCoordinates(TSpatialPosition* sp, const TPositionVector& pv);
	//@}

private:
	// We don't want these accessible
	/*! Copy Constructor */
	T3DLocalRefFrame( const T3DLocalRefFrame& );
	/*! Copy Assignment Operator */
	T3DLocalRefFrame& operator=( const T3DLocalRefFrame& );
};

/*@}*/	

#endif //SU_3D_LOCAL_REFFRAME
