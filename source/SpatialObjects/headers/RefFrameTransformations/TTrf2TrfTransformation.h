/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SU_TRF_2_TRF
#define SU_TRF_2_TRF

#if _MSC_VER >= 1000
#pragma once
#endif

#include  "TARefFrameTransformation.h"
#include  "TSpatialPosition.h"
#include  "TTerrestrialReferenceFrame.h"

class  THelmertTransformation;
class  TScaleFactor;
class  TRotation;
class  TTranslation;

/*!\ingroup spatialobjects
	@{*/
namespace TrfTransformationCoefficients
{
// Transformation parameters from ITRF2020 to past ITRFs and their rates
// Data format: Tx[mm], Ty[mm], Tz[mm],D (scale factor) [ppb], Rx [0.001"], Ry [0.001"], Rz [0.001"],Epoch, vTx [mm/yr], vTy [mm/yr], vTz [mm/yr], vD [ppb/yr], vRx
// [0.001"/yr], vRy [0.001"/yr], vRz [0.001"/yr] https://itrf.ign.fr/docs/solutions/itrf2020/Transfo-ITRF2020_TRFs.txt
//
static const std::array<std::array<TReal, 15>, 13> coeffITRF2020_toPastITRF = {{
	{LITERAL(-1.4), LITERAL(-0.9), LITERAL(1.4), LITERAL(-0.42), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00), LITERAL(2015.0), LITERAL(0.0), LITERAL(-0.1), LITERAL(0.2), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00)}, // ITRF2014
	{LITERAL(0.2), LITERAL(1.0), LITERAL(3.3), LITERAL(-0.29), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00), LITERAL(2015.0), LITERAL(0.0), LITERAL(-0.1), LITERAL(0.1),	LITERAL(0.03), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00)}, // ITRF2008
	{LITERAL(2.7), LITERAL(0.1), LITERAL(-1.4), LITERAL(0.65), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00), LITERAL(2015.0), LITERAL(0.3), LITERAL(-0.1), LITERAL(0.1),	LITERAL(0.03), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00)}, // ITRF2005
	{LITERAL(-0.2), LITERAL(0.8), LITERAL(-34.2), LITERAL(2.25), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00), LITERAL(2015.0), LITERAL(0.1), LITERAL(0.0), LITERAL(-1.7), LITERAL(0.11), LITERAL(0.00), LITERAL(0.00), LITERAL(0.00)}, // ITRF2000
	{LITERAL(6.5), LITERAL(-3.9), LITERAL(-77.9), LITERAL(3.98), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF97
	{LITERAL(6.5), LITERAL(-3.9), LITERAL(-77.9), LITERAL(3.98), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF96
	{LITERAL(6.5), LITERAL(-3.9), LITERAL(-77.9), LITERAL(3.98), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF94
	{LITERAL(-65.8), LITERAL(1.9), LITERAL(-71.3), LITERAL(4.47), LITERAL(-3.36), LITERAL(-4.33), LITERAL(0.75), LITERAL(2015.0), LITERAL(-2.8), LITERAL(-0.2), LITERAL(-2.3), LITERAL(0.12), LITERAL(-0.11), LITERAL(-0.19), LITERAL(0.07)}, // ITRF93
	{LITERAL(14.5), LITERAL(-1.9), LITERAL(-85.9), LITERAL(3.27), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF92
	{LITERAL(26.5), LITERAL(12.1), LITERAL(-91.9), LITERAL(4.67), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF91
	{LITERAL(24.5), LITERAL(8.1), LITERAL(-107.9), LITERAL(4.97), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF90
	{LITERAL(29.5), LITERAL(32.1), LITERAL(-145.9), LITERAL(8.37), LITERAL(0.00), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)}, // ITRF89
	{LITERAL(24.5), LITERAL(-3.9), LITERAL(-169.9), LITERAL(11.47), LITERAL(0.10), LITERAL(0.00), LITERAL(0.36), LITERAL(2015.0), LITERAL(0.1), LITERAL(-0.6), LITERAL(-3.1), LITERAL(0.12), LITERAL(0.00), LITERAL(0.00), LITERAL(0.02)} // ITRF88
}};

// Transformation parameters from ITRFyy to past ETRFyy at epoch 1989.0 and their rates
// Data format: Tx[mm], Ty[mm], Tz[mm],D (scale factor) [ppb], Rx [0.001"], Ry [0.001"], Rz [0.001"],Epoch, vTx [mm/yr], vTy [mm/yr], vTz [mm/yr], vD [ppb/yr], vRx [0.001"/yr], vRy [0.001"/yr], vRz [0.001"/yr]
// Altamimi, Z. (2018) EUREF Technical Note 1: Relationship and Transformation between the Internationaland the European Terrestrial Reference Systems
static const std::array<std::array<TReal, 15>, 11> coeffITRFyy_toETRFyy = {{
	{LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.085), LITERAL(0.531), LITERAL(-0.770)}, // ETRF2014
	{LITERAL(56.0), LITERAL(48.0), LITERAL(-37.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.054), LITERAL(0.518), LITERAL(-0.781)}, // ETRF2005
	{LITERAL(54.0), LITERAL(51.0), LITERAL(-48.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.081), LITERAL(0.490), LITERAL(-0.792)}, // ETRF2000
	{LITERAL(41.0), LITERAL(41.0), LITERAL(-49.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.200), LITERAL(0.500), LITERAL(-0.650)}, // ETRF97
	{LITERAL(41.0), LITERAL(41.0), LITERAL(-49.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.200), LITERAL(0.500), LITERAL(-0.650)}, // ETRF96
	{LITERAL(41.0), LITERAL(41.0), LITERAL(-49.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.200), LITERAL(0.500), LITERAL(-0.650)}, // ETRF94
	{LITERAL(19.0), LITERAL(53.0), LITERAL(-21.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.320), LITERAL(0.780), LITERAL(-0.670)}, // ETRF93
	{LITERAL(38.0), LITERAL(40.0), LITERAL(-37.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.210), LITERAL(0.520), LITERAL(-0.680)}, // ETRF92
	{LITERAL(21.0), LITERAL(25.0), LITERAL(-37.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.210), LITERAL(0.520), LITERAL(-0.680)}, // ETRF91
	{LITERAL(19.0), LITERAL(28.0), LITERAL(-23.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.110), LITERAL(0.570), LITERAL(-0.710)}, // ETRF90
	{LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.000), LITERAL(0.000), LITERAL(0.000), LITERAL(1989.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), LITERAL(0.00), LITERAL(0.110), LITERAL(0.570), LITERAL(-0.710)} // ETRF89
}};
}

//! The definition of the transformation between two terrestrial reference frames (ITRF or ETRF)
class TTrf2TrfTransformation : public TARefFrameTransformation  
{
public:

	/**@name Constructors and Destructors */
//@{
	/// Default Constructor 
	TTrf2TrfTransformation();

	/// Constructor taking pointers to the source and destination reference frames
	TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to);

	/// Constructor taking parameters of a THelmertTransformation
	TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to, const TScaleFactor&, const TRotation&, const TTranslation&);

	/// Constructor taking parameters of the full coefficient table
	TTrf2TrfTransformation(TTerrestrialReferenceFrame* from, TTerrestrialReferenceFrame* to, const TMatrix* coeffTransfoITRF, const TMatrix* coeffTransfoETRF);

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

	//! Convert a position vector in free vector (required for working with velocities)
	TFreeVector positionToFree(TPositionVector &pv) const;

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
	bool								isInitialised() const;

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
	TFreeVector itrf2014velocity(TPositionVector& pv) const;

	/// Apply plate velocity
	TPositionVector applyPlateVelocity(TPositionVector& pv, TFreeVector& velocityVec, TReal deltaEpoch) const;

	/// Transform ITRF2014 velocity into another ITRF
	TFreeVector itrf2014velocityToOtherITRF(TMatrix coeff_toPastITRF, TPositionVector& pv, TFreeVector& velITRF2014, TTerrestrialReferenceFrame* itrfIn) const;

	/// Apply velocity translation, rotation and scale factor rates (ITRF to ITRF)
	TFreeVector transformITRFVelocity(TPositionVector &pv, TFreeVector &velITRF_yy, THelmertTransformation &itrf2itrfTransfoRate) const;

	/// Apply velocity translation, rotation and scale factor rates (ITRF to ETRF)
	TFreeVector transformETRFVelocity(TPositionVector &pv, TFreeVector &velITRF_yy, THelmertTransformation &itrf2etrfTransfoRate) const;


	/// Transform ITRF2014 velocity into another ITRF
	TPositionVector itrf2014velocityToOtherITRF(TMatrix coeff_toPastITRF, TPositionVector& pv, TPositionVector& velITRF2014, TTerrestrialReferenceFrame* itrfIn) const;

	/// ITRF to ITRF transformation
	bool itrf2itrf(TMatrix coeff_toPastITRF, TPositionVector& pv, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* itrfOut) const;

	///ITRF to ITRF transformation rate
	THelmertTransformation itrf2itrfRate(TMatrix coeff_toPastITRF, TTerrestrialReferenceFrame* itrfIn, TTerrestrialReferenceFrame* itrfOut) const;

	///ITRF to ETRF transformation
	bool itrf2etrf(TMatrix coeffITRFyy_toETRFyy, TPositionVector& pv, TTerrestrialReferenceFrame* itrf, TTerrestrialReferenceFrame* etrf, bool inverse) const;

	/// ITRF to ETRF transformation rate
	THelmertTransformation itrf2etrfRate(TMatrix coeffITRFyy_toETRFyy, TTerrestrialReferenceFrame* etrf, bool inverse) const;
	//@}

	

private:
	
	THelmertTransformation* fTransform;
	TTerrestrialReferenceFrame* fFrom;
	TTerrestrialReferenceFrame* fTo;
	
	TReal fDeltaEpoch;
	TMatrix fcoeff_toPastITRF;
	TMatrix fcoeff_ITRFtoETRF;

	// Parameters to be updated if a new solution is available
	const std::string lastITRFsolution = "ITRF 2020";
	const std::string missingETRFsolution = "ETRF 2008";
	const std::string lastITRFvelSolution = "ITRF 2014";

};
/*@}*/

#endif // SU_TRF_2_TRF
