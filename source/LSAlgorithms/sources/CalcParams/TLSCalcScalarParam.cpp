// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿// TLSCalcScalarParam.cpp

#include "TLSCalcScalarParam.h"

//////////////////////////////////////////////////////////////////////
// CONSTRUCTORS / DESTRUCTOR
//////////////////////////////////////////////////////////////////////

// Default constructor
TLSCalcScalarParam::TLSCalcScalarParam():
   fProvisionalValue(LITERAL(0.0) /*, TCoordSysFactory::k3DCartesian*/),
   fCorrection(LITERAL(0.0) /*, TCoordSysFactory::k3DCartesian*/),
   fEstimatedValue(fProvisionalValue),
   fEstimatedPrecision(LITERAL(0.0) /*, TCoordSysFactory::k3DCartesian*/),
   fCovariance(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/),
   TALSCalcParameter("") 
{
   fStatus = TALSCalcParameter::kVariable;
   fScalarIndices[0] = -1;
}

// Constructor taking provisional value and parameter status as argument
TLSCalcScalarParam::TLSCalcScalarParam(TReal pv, ELSStatus status, std::string name) ://does the scalar need a name?
   fProvisionalValue(pv),
   fStatus(status),TALSCalcParameter(name), 
   fCorrection(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/),
   fEstimatedValue(fProvisionalValue),
   fEstimatedPrecision(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/),
   fCovariance(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/)
{
	fScalarIndices[0] = -1;
}


// Copy constructor 
TLSCalcScalarParam::TLSCalcScalarParam(const TLSCalcScalarParam& source):
   fProvisionalValue(source.fProvisionalValue),
   fCorrection(source.fCorrection),
   fEstimatedValue(source.fEstimatedValue),
   fEstimatedPrecision(source.fEstimatedPrecision),
   fCovariance(source.fCovariance),
   TALSCalcParameter(source.getName())
{
	fStatus = source.fStatus;
	fScalarIndices[0] = source.fScalarIndices[0];
}


// Destructor
TLSCalcScalarParam::~TLSCalcScalarParam() {
}

// re-initialises the parameters alterred during or after a least squares calculation
void	TLSCalcScalarParam::reInitialise()
{
	fCorrection = TReal(LITERAL(0.0)); /*,TCoordSysFactory::k3DCartesian*/
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = TReal(LITERAL(0.0)); /*,TCoordSysFactory::k3DCartesian*/
	fCovariance = TReal(LITERAL(0.0)); /*,TCoordSysFactory::k3DCartesian*/
	fScalarIndices[0] = -1;

	return;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////

void TLSCalcScalarParam::resetValues()
{
   fProvisionalValue = TReal(LITERAL(1.0));
   fCorrection = TReal(LITERAL(0.0));
   fEstimatedValue = TReal(LITERAL(0.0));
   fEstimatedPrecision = TReal(LITERAL(0.0));
   fCovariance = TReal(LITERAL(0.0));
   fScalarIndices[0] = -1;
}

// Returns the provisional value of the position vector 
TReal	TLSCalcScalarParam::getProvisionalValue() const {

	return fProvisionalValue;
}
	
// Returns the correction value 
TReal	TLSCalcScalarParam::getCorrection() const {

	return fCorrection;
}
	
//! Returns the estimated value for the position 
TReal	TLSCalcScalarParam::getEstimatedValue() const {

	return fEstimatedValue;
}

// Returns the estimated precision for the position 
TReal	TLSCalcScalarParam::getEstimatedPrecision() const {

	return fEstimatedPrecision;
}

// Returns the covariance element for the position 
TReal	TLSCalcScalarParam::getEstimatedCovariance() const {

	return fCovariance;
}

// Returns the status of the scalar for calculation 
TALSCalcParameter::ELSStatus	TLSCalcScalarParam::getStatus() const {

	return fStatus;
}



/*!Returns the status (Cala, Vxy....)*/
TSpatialStatus::ESpatialStatus	TLSCalcScalarParam::getGlobalStatus() const
{
	TSpatialStatus::ESpatialStatus status = TSpatialStatus::kVxyz;
	return status;
}

MatrixIndex	TLSCalcScalarParam::getScalarIndex()
{
	return  fScalarIndices[0];
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC & PROTECTED SETTINGS METHODS
///////////////////////////////////////////////////////////////////////////

// Sets the provisional value of the scalar parameter 
void	TLSCalcScalarParam::setProvisionalValue(TReal pv) {

	fProvisionalValue = pv;
	setEstimatedValue(pv);
}
// Sets the estimated value of the scalar parameter 
void	TLSCalcScalarParam::setEstimatedValue(TReal evv) {

	fEstimatedValue = evv;
	}

// Sets the correction value 
void	TLSCalcScalarParam::setCorrection(TReal corr) {

	fCorrection = corr;
	setEstimatedValue();
}

// Sets the estimated precision after calculation 
void	TLSCalcScalarParam::setEstimatedPrecision(TReal ep) {

	fEstimatedPrecision = ep;
}

// Sets the estimated precision after calculation 
void	TLSCalcScalarParam::setEstimatedCovariance(TReal cov) {

	fCovariance = cov;
}

// Sets the status of the vector 
void	TLSCalcScalarParam::setStatus(ELSStatus stat) {

	fStatus = stat;
}

// Sets the estimated value (last estimated + correction) 
void	TLSCalcScalarParam::setEstimatedValue() 
{//plus signs removed as a test - 21/10/03 10:11
	fEstimatedValue += fCorrection;
}

// Sets the scalar parameter's unknown index 
UEOIndices TLSCalcScalarParam::setUIndex(UEOIndices ui) {
 
	if (fStatus == TALSCalcParameter::kVariable)
		fScalarIndices[0] = ui.UIndex ++;

	return ui;
}

