// SPDX-FileCopyrightText: 2025 CERN

// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TLSCalcOrientationParam.cpp

#include "TLSCalcOrientationParam.h"
#include <iostream>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR / DESTRUCTOR
/////////////////////////////////////////////////////////////////////////

// Default constructor
TLSCalcOrientationParam::TLSCalcOrientationParam():TALSCalcParameter("") {
	
	for (int i=0;i<3;i++)
		fOrientIndex[i]=-1;

	fProvisionalValue.omega = TAngle(LITERAL(0.0));
	fProvisionalValue.phi = TAngle(LITERAL(0.0));
	fProvisionalValue.kappa = TAngle(LITERAL(0.0));
	fCorrection.omega = TAngle(LITERAL(0.0));
	fCorrection.phi = TAngle(LITERAL(0.0));
	fCorrection.kappa = TAngle(LITERAL(0.0));
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision.omega = TAngle(LITERAL(0.0));
	fEstimatedPrecision.phi = TAngle(LITERAL(0.0));
	fEstimatedPrecision.kappa = TAngle(LITERAL(0.0));
	fStatus.first = TALSCalcParameter::kVariable;
	fStatus.second = TALSCalcParameter::kVariable;
	fStatus.third = TALSCalcParameter::kVariable;
}

// Constructor using a structure angle (provisional value) and parameter status as argument
TLSCalcOrientationParam::TLSCalcOrientationParam(const struct Angles& provAng,struct LSParaStatus ems, std::string name):
fProvisionalValue(provAng), fStatus(ems), TALSCalcParameter(name) {
	fCorrection.omega = TAngle(LITERAL(0.0));
	fCorrection.phi = TAngle(LITERAL(0.0));
	fCorrection.kappa = TAngle(LITERAL(0.0));
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision.omega = TAngle(LITERAL(0.0));
	fEstimatedPrecision.phi = TAngle(LITERAL(0.0));
	fEstimatedPrecision.kappa = TAngle(LITERAL(0.0));
	// Sets the index to -1
	for (int i=0;i<3;i++)
		fOrientIndex[i]=-1;
}

// Copy constructor
TLSCalcOrientationParam::TLSCalcOrientationParam(const TLSCalcOrientationParam& source):
TALSCalcParameter(source.getName()) {
	
	fProvisionalValue = source.fProvisionalValue; 
	fCorrection = source.fCorrection;
	fEstimatedValue = source.fEstimatedValue;
	fEstimatedPrecision = source.fEstimatedPrecision;
	fStatus = source.fStatus;
	for (int i=0;i<3;i++)
		fOrientIndex[i] = source.fOrientIndex[i];
}

// Destructor
TLSCalcOrientationParam::~TLSCalcOrientationParam() {
}


//Copy assignment operator
TLSCalcOrientationParam& TLSCalcOrientationParam::operator=(const TLSCalcOrientationParam& source) {

	if (this != &source)
	{
		setName(source.getName());
	
		fProvisionalValue = source.fProvisionalValue; 
		fCorrection = source.fCorrection;
		fEstimatedValue = source.fEstimatedValue;
		fEstimatedPrecision = source.fEstimatedPrecision;
		fStatus = source.fStatus;
		for (int i=0;i<3;i++)
			fOrientIndex[i] = source.fOrientIndex[i];
	}

	return *this;
}

// re-initialises the parameters alterred during or after a least squares calculation
void	TLSCalcOrientationParam::reInitialise()
{
	fCorrection.omega = TAngle(LITERAL(0.0));
	fCorrection.phi = TAngle(LITERAL(0.0));
	fCorrection.kappa = TAngle(LITERAL(0.0));
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision.omega = TAngle(LITERAL(0.0));
	fEstimatedPrecision.phi = TAngle(LITERAL(0.0));
	fEstimatedPrecision.kappa = TAngle(LITERAL(0.0));

	return;
}


////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
////////////////////////////////////////////////////////////////////////////
void TLSCalcOrientationParam::resetValues()
{
	fProvisionalValue.omega = TAngle(LITERAL(0.0));
	fProvisionalValue.phi = TAngle(LITERAL(0.0));
	fProvisionalValue.kappa = TAngle(LITERAL(0.0));
	fCorrection.omega = TAngle(LITERAL(0.0));
	fCorrection.phi = TAngle(LITERAL(0.0));
	fCorrection.kappa = TAngle(LITERAL(0.0));
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision.omega = TAngle(LITERAL(0.0));
	fEstimatedPrecision.phi = TAngle(LITERAL(0.0));
	fEstimatedPrecision.kappa = TAngle(LITERAL(0.0));

}




// Returns the angle's provisional value as an Angles structure
struct Angles TLSCalcOrientationParam::getProvisionalValue() const {
	
	return fProvisionalValue;
}

//! Returns the angle's correction 
struct Angles	TLSCalcOrientationParam::getCorrection() const {

	return fCorrection;
}

// Returns the angle's estimated value as an Angles structure
struct Angles TLSCalcOrientationParam::getEstimatedValue() const {

	return fEstimatedValue;
}

// Returns the estimated angle's precision as a TAngle instance
struct Angles TLSCalcOrientationParam::getEstimatedPrecision() const {

	return fEstimatedPrecision;
}

// Returns the omega angle's unknown index 
MatrixIndex	TLSCalcOrientationParam::getOmegaIndex() const {

	return fOrientIndex[0];
}

// Returns the phi angle's unknown index 
MatrixIndex	TLSCalcOrientationParam::getPhiIndex() const {

	return fOrientIndex[1];
}

// Returns the kappa angle's unknown index 
MatrixIndex	TLSCalcOrientationParam::getKappaIndex() const {

	return fOrientIndex[2];
}

// Returns the omega angle's status (unknown, variable or fixed) 
TALSCalcParameter::ELSStatus	TLSCalcOrientationParam::getOmegaStatus() const {

	return fStatus.first;
}

// Returns the phi angle's status (unknown, variable or fixed) 
TALSCalcParameter::ELSStatus	TLSCalcOrientationParam::getPhiStatus() const {

	return fStatus.second;
}

// Returns the kappa angle's status (unknown, variable or fixed) 
TALSCalcParameter::ELSStatus	TLSCalcOrientationParam::getKappaStatus() const {

	return fStatus.third;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC & PROTECTED SETTINGS METHODS
///////////////////////////////////////////////////////////////////////////

// Sets the angle's provisional value 
void TLSCalcOrientationParam::setProvisionalValue( TAngle pvo,TAngle pvp,TAngle pvk ) {

	fProvisionalValue.omega = pvo;
	fProvisionalValue.phi = pvp;
	fProvisionalValue.kappa = pvk;

	fEstimatedValue = fProvisionalValue;
}

// Sets the correction to the angle's provisional value 
void TLSCalcOrientationParam::setCorrection(TAngle ocorr,TAngle pcorr,TAngle kcorr) {

	fCorrection.omega = ocorr;
	fCorrection.phi = pcorr;
	fCorrection.kappa = kcorr;

	setEstimatedValue();
}

// Sets the estimated angle's precision 
void TLSCalcOrientationParam::setEstimatedPrecision(TAngle epo,TAngle epp,TAngle epk) {

	fEstimatedPrecision.omega = epo;
	fEstimatedPrecision.phi = epp;
	fEstimatedPrecision.kappa = epk;
}

// Sets the angle's fixed/variable/1D variable status 
void TLSCalcOrientationParam::setStatus(struct LSParaStatus lss) {

	fStatus = lss;
}

// Sets the estimated orient. value (observed + residual)
void TLSCalcOrientationParam::setEstimatedValue() {
		
	fEstimatedValue.omega += fCorrection.omega;
	fEstimatedValue.phi += fCorrection.phi ;
	fEstimatedValue.kappa += fCorrection.kappa;

}

// Sets the orientation parameter's unknown index 
UEOIndices		TLSCalcOrientationParam::setUIndex(UEOIndices ui) {

	if (fStatus.first == TALSCalcParameter::kVariable)
		fOrientIndex[0] = ui.UIndex ++;

	if (fStatus.second == TALSCalcParameter::kVariable)
		fOrientIndex[1] = ui.UIndex ++;

	if (fStatus.third == TALSCalcParameter::kVariable)
		fOrientIndex[2] = ui.UIndex ++;
	
	return ui;
}

