// TLSConstraintIdentifier.h

//////////////////////////////////////////////////////////////////////

/*! Class for create the constraint vector for *LIBR

  Pattern:

  Copyright 2003 CERN EST/SU. All rights reserved.
*/


//////////////////////////////////////////////////////////////////////


#ifndef SU_TLSCONSTRAINTIDENTIFIER
#define SU_TLSCONSTRAINTIDENTIFIER


#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////
//using namespace std;
#include "TLSCalcWorkingPosVec.h"
#include "ObservationSet.h"
#include "TLength.h"

struct freeCnstr {bool dx; bool dy; bool dz; bool rx; bool ry; bool rz; bool k; };
struct freeCnstrRank {int dx; int dy; int dz; int rx; int ry; int rz; int k; };

//! class for input matrices used in the ls-calculation
class TLSConstraintIdentifier{

public:

	/*!@name Constructors / Destructor*/
	//@{
		//!Constructor
		TLSConstraintIdentifier();
		//!Destructor
		~TLSConstraintIdentifier();
	//@}

	/*!initialise translation, rotation and scale constraints using point's status*/
	void	initCnstrIdentifier(TLSCalcWorkingPosVec*, const ObservationSet&);

	void	setEstimatedGravityCenterCoord(TLength x, TLength y, TLength z);

	/*!@name Access methods*/
	//@{
		struct freeCnstr		getFreeConstraints() const { return fCnstrVector;} 
		TLength					getXGravityCenter() const { return fXcg;}
		TLength					getYGravityCenter() const { return fYcg;}
		TLength					getZGravityCenter() const { return fZcg;}
		TLength					getXEstimatedGravityCenter() const { return fXcgEst;}
		TLength					getYEstimatedGravityCenter() const { return fYcgEst;}
		TLength					getZEstimatedGravityCenter() const { return fZcgEst;}
		struct freeCnstrRank	getIndiceOfConstraint() const { return fCnstrNumber;}
		int						getNumberOfConstraint() const;

	//@}


private:

	/*!@name Private Member functions*/
	//@{
		void	setCnstrIdentifier(const bool dx, const bool dy, const bool dz, 
											const bool rx, const bool ry, const bool rz, 
											const bool k);

		void	addCnstr(const struct freeCnstr);

	//@}



	struct freeCnstr		fCnstrVector; /*!<constraint vector*/
	TLength					fXcg;/*!<x coordinate of the gravity center*/
	TLength					fYcg;/*!<y coordinate of the gravity center*/
	TLength					fZcg;/*!<z coordinate of the gravity center*/
	TLength					fXcgEst;/*!<x estimated coordinate of the gravity center*/
	TLength					fYcgEst;/*!<y estimated coordinate of the gravity center*/
	TLength					fZcgEst;/*!<z estimated coordinate of the gravity center*/
	struct freeCnstrRank	fCnstrNumber;
};


#endif