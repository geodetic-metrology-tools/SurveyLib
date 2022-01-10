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
#include  "TSpatialPosition.h"
#include  "TTerrestrialReferenceFrame.h"
//#include  "THelmertRefFrameTransform.h"

class  THelmertTransformation;
class  TScaleFactor;
class  TRotation;
class  TTranslation;

/*!\ingroup spatialobjects
	@{*/

//! The definition of the transformation between two terrestrial reference frames (ITRF or ETRF)
class TTrf2TrfTransformation : public TARefFrameTransformation //: public TObject  
{
public:

	/**@name Constructors and Destructors */
//@{
	/// Default Constructor 
	TTrf2TrfTransformation();

	/// Constructor taking pointers to the source and destination reference frames
	TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to, THelmertTransformation*);

	/// Constructor taking parameters of a THelmertTransformation
	TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to, const TScaleFactor&, const TRotation&, const TTranslation&);

	/// Constructor taking parameters of the full coefficient table
	TTrf2TrfTransformation::TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to, const TMatrix* coeffTransfoITRF, const TMatrix* coeffTransfoETRF);

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

	/// Return the helmert transformation
	virtual THelmertTransformation*     getTransform() const { return fTransform; }

	/// Set the source frame
	virtual void						setSourceFrame(TTerrestrialReferenceFrame* from) { fFrom = from; return; }

	/// Set the destination frame
	virtual void						setDestinationFrame(TTerrestrialReferenceFrame* to) { fTo = to; return; }

	/// Set the Helmert transformation
	virtual void						setTransform(THelmertTransformation* helmert);

	/// Set the helmert transformation using the parameters of the transformation
	virtual void						setTransform(const TScaleFactor&, const TRotation&, const TTranslation&);

	/// transform a position vector
	virtual  bool						transform(TPositionVector& pv) const;

/*	/// transform a free vector
	virtual  bool						transform(TFreeVector& fv) const;

	/// transform a Rotation Matrix
	virtual  bool						transform(TRotationMatrix& rmx) const;
*/
	bool								isInitialised() const { return (fFrom != 0 && fTo != 0); }

	///  Set the difference of epoch
	virtual void						setDeltaEpoch(TReal deltaE) { fDeltaEpoch = deltaE; return; }

	/// Return the difference of epoch
	virtual TReal						getDeltaEpoch() const { return fDeltaEpoch; }

	///  Calculate the difference of epoch
	virtual void						calcDeltaEpoch();

	/// Find the correct parameters
	int									findITRFSolution(TTerrestrialReferenceFrame* refFrame) const;

	/// Find the correct parameters
	int									findETRFSolution(TTerrestrialReferenceFrame* refFrame) const;

	///  Compute the local velocity of the point (ITRF2014 plate motion model)
	TPositionVector TTrf2TrfTransformation::itrf2014velocity(TPositionVector& pv) const;

	/// Apply plate velocity
	TPositionVector TTrf2TrfTransformation::applyPlateVelocity(TPositionVector& pv, TPositionVector& velocityVec, TReal deltaEpoch) const;

	/// ITRF to ITRF transformation
	//THelmertTransformation TTrf2TrfTransformation::itrf2itrf(TMatrix coeff_toPastITRF, TPositionVector& pv, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* itrfOut) const;
	bool TTrf2TrfTransformation::itrf2itrf(TMatrix coeff_toPastITRF, TPositionVector& pv, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* itrfOut) const;

	///ITRF to ITRF transformation rate
	THelmertTransformation TTrf2TrfTransformation::itrf2itrfRate(TMatrix coeff_toPastITRF, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* itrfOut) const;

	///ITRF to ETRF transformation
	bool TTrf2TrfTransformation::itrf2etrf(TMatrix coeffITRFyy_toETRFyy, TPositionVector& pv, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* etrfOut) const;

	/// ITRF to ETRF transformation rate
	THelmertTransformation TTrf2TrfTransformation::itrf2etrfRate(TMatrix coeffITRFyy_toETRFyy, TTerrestrialReferenceFrame* etrfOut) const;
	//@}

	

private:
	
	THelmertTransformation* fTransform;
	TTerrestrialReferenceFrame* fFrom;
	TTerrestrialReferenceFrame* fTo;
	
	TReal fDeltaEpoch;
	TMatrix fcoeff_toPastITRF;
	TMatrix fcoeff_ITRFtoETRF;

};
/*@}*/

#endif // SU_TRF_2_TRF
