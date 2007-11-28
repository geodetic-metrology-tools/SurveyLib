// TLSCalcLengthParam.cpp

#include "TLSCalcLengthParam.h"

////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS / DESTRUCTOR
////////////////////////////////////////////////////////////////////////

// Default constructor
TLSCalcLengthParam::TLSCalcLengthParam():TALSCalcParameter("") {

	fProvisionalValue = TLength(0.0);
	fCorrection = TLength(0.0);
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = TLength(0.0);
	fIndex = 0;
	fStatus = TALSCalcParameter::kVariable;
}

// Constructor taking a provisional value and parameter status as argument
TLSCalcLengthParam::TLSCalcLengthParam(TLength lobs,TALSCalcParameter::ELSStatus els,string name):
fProvisionalValue(lobs),TALSCalcParameter(name) {

	fCorrection = TLength(0.0);
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = TLength(0.0);
	fIndex = 0;
	fStatus = els;
}

// Copy constructor
TLSCalcLengthParam::TLSCalcLengthParam(const TLSCalcLengthParam& source):TALSCalcParameter(source.getName()) {
	fProvisionalValue = source.fProvisionalValue; 
	fCorrection = source.fCorrection; 
	fEstimatedValue = source.fEstimatedValue; 
	fEstimatedPrecision = source.fEstimatedPrecision; 

	fIndex = source.fIndex; 
	fStatus = source.fStatus;

}

// Destructor
TLSCalcLengthParam::~TLSCalcLengthParam() {

}

/*
// Overloaded copy assignment operator
TLSCalcLengthParam& TLSCalcLengthParam::operator =(const TLSCalcLengthParam& right) {

	// not implemented
}
*/

// re-initialises the parameters alterred during or after a least squares calculation
void	TLSCalcLengthParam::reInitialise()
{
	fCorrection = TLength(0.0);
	fEstimatedValue = fProvisionalValue;
	fEstimatedPrecision = TLength(0.0);

	return;
}

////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
////////////////////////////////////////////////////////////////////////

// Returns the provisional value of the parameter 
TLength		TLSCalcLengthParam::getProvisionalValue() const {

	return fProvisionalValue;
}

// Returns the correction to be brought on the provisional value 
TLength		TLSCalcLengthParam::getCorrection() const {

	return fCorrection;
}

// Returns the estimated value of the parameter after correction 
TLength		TLSCalcLengthParam::getEstimatedValue() const {

	return fEstimatedValue;
}

// Returns the estimated precision of the parameter after calculation 
TLength		TLSCalcLengthParam::getEstimatedPrecision() const {

	return fEstimatedPrecision;
}

// Returns the LSCalc status of the parameter for calculation 
TALSCalcParameter::ELSStatus	TLSCalcLengthParam::getStatus() const {

	return fStatus;
}

// Returns the index of the parameter's unknown index 
MatrixIndex	TLSCalcLengthParam::getIndex() const {

	return fIndex;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC & PROTECTED SETTINGS METHODS
///////////////////////////////////////////////////////////////////////////

// Sets the provisional value 
void		TLSCalcLengthParam::setProvisionalValue(TLength pv) {

	fProvisionalValue = pv;
}

// Sets the correction's value 
void		TLSCalcLengthParam::setCorrection(TLength corr) {

	fCorrection = corr;
	setEstimatedValue();
}

// Sets the estimated precision 
void		TLSCalcLengthParam::setEstimatedPrecision(TLength ep) {

	fEstimatedPrecision = ep;
}

// Sets the status od the parameter 
void		TLSCalcLengthParam::setStatus(TALSCalcParameter::ELSStatus lsStat) {

	fStatus = lsStat;
}

// Sets the unknown index for calculation 
UEOIndices		TLSCalcLengthParam::setUIndex(UEOIndices ui) {

	if (fStatus == TALSCalcParameter::kVariable)
		fIndex = ui.UIndex ++;

	return ui;
}

// Sets the estimated value (provisional + correction) 
void		TLSCalcLengthParam::setEstimatedValue() {

	fEstimatedValue += fCorrection;
}

