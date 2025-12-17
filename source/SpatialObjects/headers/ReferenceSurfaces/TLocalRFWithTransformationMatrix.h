/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/*!
	class for a local 3D cartesian reference frame used in CAD softwares

	Pattern:

*/

#ifndef SU_CAD_REFFRAME
#	define SU_CAD_REFFRAME

#	if _MSC_VER >= 1000
#		pragma once
#	endif // _MSC_VER >= 1000

#include  "T3DLocalRefFrame.h"

/*! \ingroup spatialobjects
	@{*/

//! Defines a local 3D cartesian system
class TLocalRFWithTransformationMatrix : public T3DLocalRefFrame
{
public:
	/*!@name Constructors/Destructors*/
	//@{
	/*! Constructor taking the name of the ref.frame */
	TLocalRFWithTransformationMatrix(const std::string &name, const std::string &pathToTransformationMatrix);
	/*! Destructors */
	~TLocalRFWithTransformationMatrix();
	//@}

	/**@name Member Functions */
	//@{
	//! set the path to the associated transformation matrix
	void setPathToTransformationMatrix(const std::string &pathToTransformationMatrix);

	//! return the path to the associated transformation matrix
	std::string getPathToTransformationMatrix() { return fPathToTransformationMatrix; }

private:
	std::string fPathToTransformationMatrix; ///*!Path to the associated transformation matrix */
};

#endif
