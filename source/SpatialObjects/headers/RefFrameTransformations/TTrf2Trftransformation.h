/*
© Copyright CERN 2000-2011. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TRF_2_TRF
#define SU_TRF_2_TRF

#if _MSC_VER >= 1000
#pragma once
#endif

#include  "TARefFrameTransformation.h"
#include <TTerrestrialReferenceFrame.h>



//! The definition of the transformation between two terrestrial reference frames (ITRF or ETRF)
class TTrf2TrfTransformation : public TARefFrameTransformation //: public TObject  
{
public:

	/**@name Constructors and Destructors */
//@{
	/// Default Constructor 
	TTrf2TrfTransformation();

	/// Constructor taking pointers to the source and destination reference frames
	TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to);

	
	/// Copy Constructor 
	TTrf2TrfTransformation(const  TTrf2TrfTransformation&);

	/// Destructor
	virtual  ~TTrf2TrfTransformation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
	TTrf2TrfTransformation& operator=(const TTrf2TrfTransformation&);

	/// Return a pointer to a clone of this reference frame
	virtual TTrf2TrfTransformation* clone() const;

	/// Return a pointer to the inverse of this transformtion
	virtual TTrf2TrfTransformation* inverse() const;

	//! Invert the transformation, replaces the current transformation parameters
	virtual void  invert();

	/// Return the source frame
	virtual TTerrestrialReferenceFrame* getSourceFrame() const { return fFrom; }

	/// Return the destination frame
	virtual TTerrestrialReferenceFrame* getDestinationFrame() const { return fTo; }

	/// Set the source frame
	virtual void						setSourceFrame(TTerrestrialReferenceFrame* from) { fFrom = from; return; }

	/// Set the destination frame
	virtual void						setDestinationFrame(TTerrestrialReferenceFrame* to) { fTo = to; return; }

		/// transform a position vector
	virtual  bool						transform(TPositionVector& pv) const;

	/// transform a free vector
	virtual  bool						transform(TFreeVector& fv) const;

	/// transform a Rotation Matrix
	virtual  bool						transform(TRotationMatrix& rmx) const;

	bool								isInitialised() const { return (fFrom != 0 && fTo != 0); }
	//@}

	

private:

	TTerrestrialReferenceFrame* fFrom;
	TTerrestrialReferenceFrame* fTo;

};


#endif // SU_TRF_2_TRF
