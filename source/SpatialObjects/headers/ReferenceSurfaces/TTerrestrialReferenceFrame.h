//  TTerrestrialReferenceFrame.h
/*
© Copyright CERN 2000-2021. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
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

	/// Constructor taking the name of the reference frame, the associated ellipsoid and epoch
	TTerrestrialReferenceFrame(const std::string& name, TReferenceEllipsoid* ell, TReal& epoch);

	/// Destructor
	virtual ~TTerrestrialReferenceFrame();
	//@}


	/**@name Member Functions */
	//@{

	//! return the epoch of the coordinates
	virtual TReal getEpoch() const { return fEpoch; }
	
	//! set the epoch of the coordinates
	virtual bool setEpoch(TReal epoch);
	 

	//@}

private:
	TReal fEpoch;                   ///*!< pointer to the current epoch */


};


#endif // SU_TERRESTRIAL_REFERENCE_FRAME
