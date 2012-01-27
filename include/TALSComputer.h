

#ifndef SU_VLS_COMPUTER
#define SU_VLS_COMPUTER


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include <math.h>


class TLSInputMatrices;
class TLSResultsMatrices;

//! Abstract Base Class. Defines the methods common to all least squares computers
class TALSComputer{

public:
	//!Destructor
	virtual ~TALSComputer();

	//!Computes the results matrices
	/*!@param im a pointer to the LS input matrices
	!@param rm a pointer to the LS results matrices*/
	virtual bool computeResultsByParametricMethod(TLSInputMatrices* im, TLSResultsMatrices* rm) = 0;
	//!Sets the scale factor for the sigma zero a priori
//	virtual void				setS0APrioriScaleFactor(TReal scalefac);

	//!makes the variances to be calculated with respect to the sigma zero a priori
//	virtual void				s0APrioriVariances();
	//!makes the variances to be calculated with respect to the sigma zero a posteriori
//	virtual void				s0APosterioriVariances();


protected:
	///Constructor
	TALSComputer();

//	bool		fS0APosterioriVariances;
//	TReal		fS0APrioriScaleFactor;


};

#endif

