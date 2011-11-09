

#ifndef SU_TLS_SPARSE_MATRIX_COMPUTER
#define SU_TLS_SPARSE_MATRIX_COMPUTER


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
#include <iostream>
#include "UEOIndices.h"
class TMatrix;
class TLSInputSparseMatrices;
class TLSResultsSparseMatrices;
//using namespace std;

//! Class for a least squares computer used when there are only observation equations
class TLSSparseMatrixComputer {

public:

	//!Constructor
	TLSSparseMatrixComputer();
	//!Destructor
	~TLSSparseMatrixComputer();


	bool computeResults(TLSInputSparseMatrices*, TLSResultsSparseMatrices*, bool isCombinedCase, bool isFreeNetworkOrECHO, bool hasConstraints);

	//!Computes the results matrices
	/*!@param im a pointer to the LS input matrices*/
	bool computeResultsMtrs(TLSInputSparseMatrices*, TLSResultsSparseMatrices*, bool isCombinedCase);

	//!Computes the results matrices for a free calculation
	/*!\param im a pointer to the LS input matrices*/
	bool computeFreeOrConstrainedResultsMtrs(TLSInputSparseMatrices*, TLSResultsSparseMatrices*, bool isCombinedCase, bool isFreeNetworkOrECHO);

	/*! Access to eventual error */
    std::string		getError() const { return fError; }

private:

	std::string			fError;		/*!< errors during calculation */
	int				count;
};

#endif

