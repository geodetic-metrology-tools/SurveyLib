/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLS_CNST_MTD_COMPUTER
#define SU_TLS_CNST_MTD_COMPUTER

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include <UEOIndices.h>
#include "TALSComputer.h"
#include <string>
class TLSInputMatrices;
class TLSResultsMatrices;

/*!
\ingroup CalcElements

\brief Class for a least squares computer, used when there are any constraints in the model.
*/
class TLSCnstMtdComputer :public TALSComputer
{

public:

	//!Constructor
	TLSCnstMtdComputer();
	//!Destructor
	virtual ~TLSCnstMtdComputer();

	//!Verify the number of unknowns and run the calculation
	bool computeResults(TLSInputMatrices*, TLSResultsMatrices*) override;

	//!Computes the results matrices with cnstr
	bool computeResultsMatrices(TLSInputMatrices*, TLSResultsMatrices*) override;

	//!Computes the results matrices for a free calculation
	bool computeFreeResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*);

	//!Computes the residual vector and the varaiance covariance matrices for a free calculation
	bool calcResidusAndVarCovMatrix(const TLSInputMatrices* inputMtr, TLSResultsMatrices* rm) override;

private:
	int		count;
};

#endif