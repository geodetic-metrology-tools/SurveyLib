/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TTerrestrialReferenceFrame.h

/** A Terrestrial reference frame like ETRF or ITRF
	Specific solution at specific epoch



*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_TERRESTRIAL_REFERENCE_FRAME
#define SU_TERRESTRIAL_REFERENCE_FRAME


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  "TA3DEuclideanRefFrame.h"
#include  "TGeodeticRefFrame.h"

//
//
////////////////////////////////////////////////////////////////


/*! \ingroup spatialobjects
	@{*/

//! A Geocentric terrestrial Reference Frame
class TTerrestrialReferenceFrame : public TGeodeticRefFrame //: public TObject  
{

public:
	/**@name Constructors and Destructors */
//@{

	/// Constructor taking the name of the reference frame, the associated ellipsoid, epoch and solution
	TTerrestrialReferenceFrame(const std::string& name, TReferenceEllipsoid* ell, TReal& epoch, std::string& solution);

	/// Destructor
	virtual ~TTerrestrialReferenceFrame();
	//@}


	/**@name Member Functions */
	//@{

	//! return the epoch of the coordinates
	virtual TReal getEpoch() const { return fEpoch; }

	//! set the solution of the coordinates
	virtual std::string getSolution() const { return fSolution; }

	//! set the epoch of the coordinates
	virtual bool setEpoch(TReal epoch);

	//! set the solution of the coordinates
	virtual bool setSolution(std::string solution);	 

	//@}

private:
	TReal fEpoch;                   ///*!< pointer to the current epoch */
	std::string	fSolution;			///*!Choosen solution */


};


#endif // SU_TERRESTRIAL_REFERENCE_FRAME
