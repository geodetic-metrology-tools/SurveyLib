/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SU_TLS_WEIGHTED_UNK_MTD_COMPUTER
#define SU_TLS_WEIGHTED_UNK_MTD_COMPUTER

#include <UEOIndices.h>
#include "TALSComputer.h"
#include <string>

class TLSInputMatrices;
class TLSResultsMatrices;


/*!
	\ingroup CalcElements

	\brief Least squares computer used when there are standard deviation assigned to some of the unknowns, which are used to calculate the additional weight unknown matrix.
*/
class TLSWeightedUnkMtdComputer:public TALSComputer
{

public:

	///Constructor
	TLSWeightedUnkMtdComputer();
	///Destructor
	virtual ~TLSWeightedUnkMtdComputer();

	///Verify the number of unknowns and run the calculation
	virtual bool computeResults(TLSInputMatrices*, TLSResultsMatrices*);

	///Computes the results matrices with the weihted unknowns
	virtual bool computeResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*);

	///Computes the results matrices for a free calculation
	//bool computeFreeResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*);

	///Computes the residual vector and the varaiance covariance matrices
	virtual void calcResiduAndVarCovMatrice(const TLSInputMatrices* inputMtr,TLSResultsMatrices* rm);

private:
	int		count;
};

#endif

