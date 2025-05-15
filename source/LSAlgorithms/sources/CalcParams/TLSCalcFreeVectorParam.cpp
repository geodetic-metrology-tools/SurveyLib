// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TLSCalcFreeVectorParam.h"

//////////////////////////////////////////////////////////////////////
// CONSTRUCTORS / DESTRUCTOR
//////////////////////////////////////////////////////////////////////

// Default constructor
TLSCalcFreeVectorParam::TLSCalcFreeVectorParam(): TALSCalcParameter(""),
fProvisionalValue(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fCorrection(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fEstimatedValue(fProvisionalValue),
fEstimatedPrecision(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fCovariance(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian)
 {
	for (int i=0;i<3;i++)
		fFreeVectorIndices[i]=-1;
	fStatus.first = TALSCalcParameter::kVariable;
	fStatus.second = TALSCalcParameter::kVariable;
	fStatus.third = TALSCalcParameter::kVariable;
}

// Constructor taking provisional value and parameter status as argument
TLSCalcFreeVectorParam::TLSCalcFreeVectorParam(TFreeVector pos,struct LSParaStatus status,
	std::string name ): TALSCalcParameter(name),
fProvisionalValue(pos),
fCorrection(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fEstimatedValue(fProvisionalValue),
fEstimatedPrecision(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fCovariance(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian),
fStatus(status)
{
	for (int i=0;i<3;i++)
		fFreeVectorIndices[i]=-1;
}



// Copy constructor 
TLSCalcFreeVectorParam::TLSCalcFreeVectorParam(const TLSCalcFreeVectorParam& source): TALSCalcParameter(source.getName()),
fProvisionalValue(source.fProvisionalValue),
fCorrection(source.fCorrection),
fEstimatedValue(source.fEstimatedValue),
fEstimatedPrecision(source.fEstimatedPrecision),
fCovariance(source.fCovariance){
	
	fStatus = source.fStatus; 
	for (int i=0;i<3;i++)
		fFreeVectorIndices[i] = source.fFreeVectorIndices[i]; 
}


// Destructor
TLSCalcFreeVectorParam::~TLSCalcFreeVectorParam() {
}

/*
// Copy assignement operator
TLSCalcFreeVectorParam& TLSCalcFreeVectorParam::operator =(const TLSCalcFreeVectorParam& right) {

	//not implemented
}
*/

// re-initialises the parameters alterred during or after a least squares calculation
void	TLSCalcFreeVectorParam::reInitialise()
{
	TFreeVector zeroVec(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian);
	fCorrection = zeroVec;
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = zeroVec;
	fCovariance = zeroVec;

	return;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////

// Returns the provisional value of the position vector 
TFreeVector	TLSCalcFreeVectorParam::getProvisionalValue() const {

	return fProvisionalValue;
}
	
// Returns the correction value 
TFreeVector	TLSCalcFreeVectorParam::getCorrection() const {

	return fCorrection;
}
	
//! Returns the estimated value for the position 
TFreeVector	TLSCalcFreeVectorParam::getEstimatedValue() const {

	return fEstimatedValue;
}

// Returns the estimated precision for the position 
TFreeVector	TLSCalcFreeVectorParam::getEstimatedPrecision() const {

	return fEstimatedPrecision;
}

// Returns the covariance element for the position 
TFreeVector	TLSCalcFreeVectorParam::getEstimatedCovariance() const {

	return fCovariance;
}

// Returns the status of the X-position for calculation 
TALSCalcParameter::ELSStatus	TLSCalcFreeVectorParam::getXStatus() const {

	return fStatus.first;
}

// Returns the status of the Y-position for calculation 
TALSCalcParameter::ELSStatus	TLSCalcFreeVectorParam::getYStatus() const {

	return fStatus.second;
}

// Returns the status of the Z-position for calculation 
TALSCalcParameter::ELSStatus	TLSCalcFreeVectorParam::getZStatus() const {

	return fStatus.third;
}
	

// Returns the unknown index of the X-position 
MatrixIndex	TLSCalcFreeVectorParam::getXIndex() const {
	
	return fFreeVectorIndices[0];
}

// Returns the unknown index of the Y-position  
MatrixIndex	TLSCalcFreeVectorParam::getYIndex() const {

	return fFreeVectorIndices[1];
}
	
// Returns the unknown index of the Z-position  
MatrixIndex	TLSCalcFreeVectorParam::getZIndex() const {

	return fFreeVectorIndices[2];
}

/*!Retutns the status (Cala, Vxy....)*/
TSpatialStatus::ESpatialStatus	TLSCalcFreeVectorParam::getGlobalStatus() const
{
	TSpatialStatus::ESpatialStatus status = TSpatialStatus::kUnknown;

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVx;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVy;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVz;}

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVxy;}

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVxz;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVyz;}

	if(this->getXStatus() == TALSCalcParameter::kVariable &&
		this->getYStatus() == TALSCalcParameter::kVariable &&
		this->getZStatus() == TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kVxyz;}

	if(this->getXStatus() != TALSCalcParameter::kVariable &&
		this->getYStatus() != TALSCalcParameter::kVariable &&
		this->getZStatus() != TALSCalcParameter::kVariable)
	{ status = TSpatialStatus::kCala;}
	
	return status;
}



///////////////////////////////////////////////////////////////////////////
// PUBLIC & PROTECTED SETTINGS METHODS
///////////////////////////////////////////////////////////////////////////
int TLSCalcFreeVectorParam::size()
{
	int count = 0;
	if (this->getXStatus() == TALSCalcParameter::kVariable)
		count++;
	if (this->getYStatus() == TALSCalcParameter::kVariable)
		count++;
	if (this->getZStatus() == TALSCalcParameter::kVariable)
		count++;
	
	return count;

}

void TLSCalcFreeVectorParam::resetValues()
{
//fProvisionalValue(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian);
TFreeVector zero(LITERAL(0.0),LITERAL(0.0),LITERAL(0.0),TCoordSysFactory::k3DCartesian);
fCorrection = zero;
fEstimatedValue = fProvisionalValue;
fEstimatedPrecision = zero;
fCovariance = zero;
}

// Sets the provisional value of the position vector 
void	TLSCalcFreeVectorParam::setProvisionalValue(TFreeVector pv) {

	fProvisionalValue = pv;
	setEstimatedValueVector(pv);

}
// Sets the estimated value of the position vector 
void	TLSCalcFreeVectorParam::setEstimatedValueVector(TFreeVector evv) {

	fEstimatedValue = evv;
}


// Sets the correction value 
void	TLSCalcFreeVectorParam::setCorrection(TFreeVector corr) {

	fCorrection = corr;
	setEstimatedValue();
}

// Sets the estimated precision after calculation 
void	TLSCalcFreeVectorParam::setEstimatedPrecision(TFreeVector ep) {

	fEstimatedPrecision = ep;
}

// Sets the estimated precision after calculation 
void	TLSCalcFreeVectorParam::setEstimatedCovariance(TFreeVector cov) {

	fCovariance = cov;
}

// Sets the status of the vector 
void	TLSCalcFreeVectorParam::setStatus(struct LSParaStatus stat) {

	fStatus = stat;
}

// Sets the estimated value (last estimated + correction) 
void	TLSCalcFreeVectorParam::setEstimatedValue() 
{

	fEstimatedValue += fCorrection;
}

// Sets the position vector parameter's unknown index 
UEOIndices		TLSCalcFreeVectorParam::setUIndex(UEOIndices ui) {

	if (fStatus.first == TALSCalcParameter::kVariable)
		fFreeVectorIndices[0] = ui.UIndex ++;

	if (fStatus.second == TALSCalcParameter::kVariable)
		fFreeVectorIndices[1] = ui.UIndex ++;

	if (fStatus.third == TALSCalcParameter::kVariable)
		fFreeVectorIndices[2] = ui.UIndex ++;
	
	return ui;
}

