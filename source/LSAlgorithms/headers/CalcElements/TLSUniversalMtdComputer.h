/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SU_TLS_UNIVERSAL_MTD_COMPUTER
#define SU_TLS_UNIVERSAL_MTD_COMPUTER

#if _MSC_VER >= 1000
#	pragma once
#	pragma warning(disable : 4786)
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include <string>
#include <memory>

#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>

#include <UEOIndices.h>

#include "TALSComputer.h"
#include "TSparseMatrix.h"

class TLSInputMatrices;
class TLSResultsMatrices;

/*!
\ingroup CalcElements

\brief Class for a least squares computer, used for Problems of type parametric, combined and constrained.
*/
class TLSUniversalMtdComputer : public TALSComputer
{
public:
	//! Constructor
	TLSUniversalMtdComputer();
	//! Destructor
	virtual ~TLSUniversalMtdComputer();

	//! Verify the number of unknowns and run the calculation
	bool computeResults(TLSInputMatrices *, TLSResultsMatrices *) override;

	//! Computes the results matrices
	bool computeResultsMatrices(TLSInputMatrices *, TLSResultsMatrices *) override;

	//! Computes the residual vector and the varaiance covariance matrices for a free calculation
	bool calcResidusAndVarCovMatrix(const TLSInputMatrices *inputMtr, TLSResultsMatrices *rm) override;

private:
	int count;

	// Stored LDLT factorization of N2 (unconstrained case only),
	// reused across solve and covariance steps
	std::unique_ptr<Eigen::SimplicialLDLT<TSparseMatrix>> storedLDLT;
	TVector storedScaling;
	int storedNbUnk = 0;
};

#endif
