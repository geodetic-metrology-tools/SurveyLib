

#ifndef SU_TLS_COMPUTER
#define SU_TLS_COMPUTER


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

#include "TALSComputer.h"

//! Class for a least squares computer used when there are only observation equations
class TLSComputer : public TALSComputer{

public:

	//!Constructor
	TLSComputer();
	//!Destructor
	virtual ~TLSComputer();


	//virtual bool computeResults(const TLSInputMatrices*, TLSResultsMatrices*);
	virtual bool computeResults(TLSInputMatrices*, TLSResultsMatrices*);

	//!Computes the results matrices
	/*!@param im a pointer to the LS input matrices*/
	virtual bool computeResultsByParametricMethod (TLSInputMatrices*, TLSResultsMatrices*);
	//virtual bool computeResultsMtrs(const TLSInputMatrices*, TLSResultsMatrices*);


	//!Computes the results matrices for a free calculation
	/*!\param im a pointer to the LS input matrices*/
	virtual bool computeResultsByParametricMethodWithMeislBordering (TLSInputMatrices*, TLSResultsMatrices*);
	//virtual bool computeFreeResultsMtrs(const TLSInputMatrices*, TLSResultsMatrices*);


	/*! Access to eventual error */
	string		getError() const { return fError; }

	TMatrix*		getMatrixPtrAtPA() const {return fAtPA;} 

private:

	TMatrix*		fAtPA;	/*!< matrice des équations normales */
	string			fError;		/*!< errors during calculation */
};

#endif

