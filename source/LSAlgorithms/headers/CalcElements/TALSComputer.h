/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SU_VLS_COMPUTER
#define SU_VLS_COMPUTER

#if _MSC_VER >= 1000
#	pragma once
#	pragma warning(disable : 4786)
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include <string>
#include <vector>

#include <Eigen/LU>

#include <UEOIndices.h>
#include <math.h>

#include "TLSInputMatrices.h"
#include "TLSResultsMatrices.h"
#include "TSparseMatrix.h"

struct limits
{
	double s0PostUpLimit;
	double s0PostLoLimit;
};

/*!
	\ingroup CalcElements

	\brief Abstract Base Class. Defines the methods common to all least squares computers.
*/
class TALSComputer
{
public:
	//! Destructor
	virtual ~TALSComputer();

	//! Verify the number of unknowns and run the calculation
	virtual bool computeResults(TLSInputMatrices *, TLSResultsMatrices *) = 0;

	//! Computes the results matrices
	virtual bool computeResultsMatrices(TLSInputMatrices *, TLSResultsMatrices *) = 0;

	//! Computes the residual vector and the varaiance covariance matrices
	virtual bool calcResidusAndVarCovMatrix(TLSInputMatrices *inputMtr, TLSResultsMatrices *rm, bool computeObsCovar = true) = 0;

	//! Calculate the hypothesis testing limits for the sigma zero a posteriori, default value for number of constraints is zero
	struct limits calcSigmaZeroLimits(const int nbObs, const int nbUnk, const int nbCnstr = 0);

	/*! Access to eventual error */
	std::string getError() const { return fError; }

protected:
	/// Constructor
	TALSComputer();

	std::string fError; /*!< errors during calculation */
};

#endif
