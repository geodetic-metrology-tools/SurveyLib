//
// Class for an unknown parameter as defined for survey purposes
// Used for the V0, Instrument heights, ...
// almost a structure
//

#ifndef SU_UNKNOWN_PARAMETER
#define SU_UNKNOWN_PARAMETER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
//
/////////////////////////////////////////////////////


#include "UEOIndices.h"

// Class Definition
class TUnknownParameter 
{
public :
	
	//constants
	enum EUnknownStatus {kNull, kUnknown, kVariable, kFixed};

	TUnknownParameter();
	TUnknownParameter(const TUnknownParameter& source);
	virtual ~TUnknownParameter();

	double				getProvisionalValue() const;
	double				getEstimatedValue() const;
	double				getEstimatedPrecision() const;
	MatrixIndex			getIndex() const;
	EUnknownStatus		getStatus() const;

	void				setProvisionalValue(double);
	void				setEstimatedValue(double);
	void				setEstimatedPrecision(double);
	MatrixIndex			setIndex(MatrixIndex);
	void				setStatus(EUnknownStatus);

private:
	
	EUnknownStatus		fStatus;
	
	MatrixIndex			fIndex;
	double				fProvisionalValue;
	double				fEstimatedValue;
	double				fEstimatedPrecision;
};

#endif

