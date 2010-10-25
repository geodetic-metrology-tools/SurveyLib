

#ifndef SU_TLS_PARAM_MTD_COMPUTER
#define SU_TLS_PARAM_MTD_COMPUTER


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
class TLSInputMatrices;
class TLSResultsMatrices;
//using namespace std;

//! Class for a least squares computer used when there are only observation equations
class TLSParametricMtdComputer {

public:

	//!Constructor
	TLSParametricMtdComputer();
	//!Destructor
	~TLSParametricMtdComputer();


	bool computeResults(TLSInputMatrices*, TLSResultsMatrices*, bool isCombinedCase, bool isFreeNetworkOrECHO, bool hasConstraints);

	//!Computes the results matrices
	/*!@param im a pointer to the LS input matrices*/
	bool computeResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*, bool isCombinedCase);

	//!Computes the results matrices for a free calculation
	/*!\param im a pointer to the LS input matrices*/
	bool computeFreeOrConstrainedResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*, bool isCombinedCase, bool isFreeNetworkOrECHO);

	/*! Access to eventual error */
    std::string		getError() const { return fError; }

private:

	std::string			fError;		/*!< errors during calculation */
	int				count;
};

#endif

