// TLSCalcScalarParam.cpp

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
TALSCalcParameter("") {
	
	fStatus = TALSCalcParameter::kVariable;
	
}

// Constructor taking provisional value and parameter status as argument
TLSCalcScalarParam::TLSCalcScalarParam(TScalar pv, ELSStatus status, string name )://does the scalar need a name?
fProvisionalValue(pv),
fStatus(status),TALSCalcParameter(name), 
fCorrection(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/),
fEstimatedValue(fProvisionalValue),
fEstimatedPrecision(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/),
fCovariance(LITERAL(0.0) /*,TCoordSysFactory::k3DCartesian*/)
{
	
}


// Copy constructor 
TLSCalcScalarParam::TLSCalcScalarParam(const TLSCalcScalarParam& source):
fProvisionalValue(source.fProvisionalValue),
fCorrection(source.fCorrection),
fEstimatedValue(source.fEstimatedValue),
fEstimatedPrecision(source.fEstimatedPrecision),
fCovariance(source.fCovariance),
TALSCalcParameter(source.getName()){
	
	fStatus = source.fStatus; 
}


// Destructor
TLSCalcScalarParam::~TLSCalcScalarParam() {
}

/*
// Copy assignement operator
TLSCalcScalarParam& TLSCalcScalarParam::operator =(const TLSCalcScalarParam& right) {

	//not implemented
}
*/

// re-initialises the parameters alterred during or after a least squares calculation
void	TLSCalcScalarParam::reInitialise()
{
	fCorrection = real(LITERAL(0.0)); /*,TCoordSysFactory::k3DCartesian*/
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = real(LITERAL(0.0)); /*,TCoordSysFactory::k3DCartesian*/
	fCovariance = real(LITERAL(0.0)); /*,TCoordSysFactory::k3DCartesian*/

	return;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////

void TLSCalcScalarParam::resetValues()
{
fProvisionalValue = real(LITERAL(1.0));
fCorrection = real(LITERAL(0.0));
fEstimatedValue = real(LITERAL(0.0));
fEstimatedPrecision = real(LITERAL(0.0));
fCovariance = real(LITERAL(0.0));

}

// Returns the provisional value of the position vector 
TScalar	TLSCalcScalarParam::getProvisionalValue() const {

	return fProvisionalValue;
}
	
// Returns the correction value 
TScalar	TLSCalcScalarParam::getCorrection() const {

	return fCorrection;
}
	
//! Returns the estimated value for the position 
TScalar	TLSCalcScalarParam::getEstimatedValue() const {

	return fEstimatedValue;
}

// Returns the estimated precision for the position 
TScalar	TLSCalcScalarParam::getEstimatedPrecision() const {

	return fEstimatedPrecision;
}

// Returns the covariance element for the position 
TScalar	TLSCalcScalarParam::getEstimatedCovariance() const {

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
	return 	fScalarIndices[0];
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC & PROTECTED SETTINGS METHODS
///////////////////////////////////////////////////////////////////////////

// Sets the provisional value of the scalar parameter 
void	TLSCalcScalarParam::setProvisionalValue(TScalar pv) {

	fProvisionalValue = pv;
	setEstimatedValue(pv);
}
// Sets the estimated value of the scalar parameter 
void	TLSCalcScalarParam::setEstimatedValue(TScalar evv) {

	fEstimatedValue = evv;
	}

// Sets the correction value 
void	TLSCalcScalarParam::setCorrection(TScalar corr) {

	fCorrection = corr;
	setEstimatedValue();
}

// Sets the estimated precision after calculation 
void	TLSCalcScalarParam::setEstimatedPrecision(TScalar ep) {

	fEstimatedPrecision = ep;
}

// Sets the estimated precision after calculation 
void	TLSCalcScalarParam::setEstimatedCovariance(TScalar cov) {

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
UEOIndices		TLSCalcScalarParam::setUIndex(UEOIndices ui) {
 
	if (fStatus == TALSCalcParameter::kVariable)
		fScalarIndices[0] = ui.UIndex ++;

	return ui;
}

