/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLS_PARAM_MTD_COMPUTER
#define SU_TLS_PARAM_MTD_COMPUTER

#include <UEOIndices.h>
#include <string>
#include "TALSComputer.h"
class TLSInputMatrices;
class TLSResultsMatrices;

/*!
	\ingroup CalcElements
	\brief Least squares computer used when the obseved values can be separated from the unknowns of the model (parametric case), it should not be used if this condition is not fullfilled.
*/
class TLSParametricMtdComputer:public TALSComputer
{

public:

	///Constructor
	TLSParametricMtdComputer();
	///Destructor
	virtual ~TLSParametricMtdComputer();

	///Verify the number of unknowns and run the calculation
	bool computeResults(TLSInputMatrices*, TLSResultsMatrices*) override;

	///Computes the results matrices for the parametric case
	bool computeResultsMatrices(TLSInputMatrices*, TLSResultsMatrices*) override;

	///Computes the residual vector and the varaiance covariance matrices
	bool calcResidusAndVarCovMatrix(const TLSInputMatrices* inputMtr,TLSResultsMatrices* rm	) override;

private:

	int	count;
};

#endif

