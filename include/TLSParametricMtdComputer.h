

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
using namespace std;

//! Class for a least squares computer used when there are only observation equations
class TLSParametricMtdComputer {

public:

	//!Constructor
	TLSParametricMtdComputer();
	//!Destructor
	~TLSParametricMtdComputer();


	bool computeResults(TLSInputMatrices*, TLSResultsMatrices*);

	//!Computes the results matrices
	/*!@param im a pointer to the LS input matrices*/
	bool computeResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*);

	//!Computes the results matrices for a free calculation
	/*!\param im a pointer to the LS input matrices*/
	bool computeFreeResultsMtrs(TLSInputMatrices*, TLSResultsMatrices*);

	/*! Access to eventual error */
	string		getError() const { return fError; }

private:

	string			fError;		/*!< errors during calculation */
	int				count;
};

#endif

