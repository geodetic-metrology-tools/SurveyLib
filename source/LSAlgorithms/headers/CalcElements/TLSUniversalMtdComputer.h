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
#include <optional>
#include <string>

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
	bool calcResidusAndVarCovMatrix(TLSInputMatrices *inputMtr, TLSResultsMatrices *rm, bool computeObsCovar = true) override;

private:
	int count;

	// Reduced normal-equations system: produced by computeResultsMatrices and consumed by
	// calcResidusAndVarCovMatrix. This is intermediate working state of the computer - it depends only
	// on the inputs (and the mask), not on any result - so it lives here rather than in
	// TLSResultsMatrices, which now holds only true results. Engaged only after a successful
	// computeResultsMatrices(); calcResidusAndVarCovMatrix checks that before using it.
	std::optional<TSparseMatrix> fNormalMatrix; ///< NBig (u+c x u+c), reduced to the active set
	std::optional<TSparseMatrix> fInvN1Matrix;  ///< invN1 (e x e), set only in the non-block-diagonal case
};

#endif
