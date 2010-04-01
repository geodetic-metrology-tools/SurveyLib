// TARotationMatrix.h
//
/** Abstract class for the matrices of rotation used for points transformations */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_ROTATION_MATRIX
#define SU_A_ROTATION_MATRIX


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
class TFreeVector;
class TPositionVector;
//
#include  "TAngle.h"
using namespace std;

//
//typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TARotationMatrix 
{
public:
	//constants
		enum ERotationStatus {kNull, kKnown};

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TARotationMatrix();

		/// Destructor
		virtual  ~TARotationMatrix();
	//@}


	/**@name Member Functions */
	//@{
		
		///set the 3 rotations taking TAngles in the order omega-phi-kappa
		//virtual void setAllRotations(double& omega, double& phi, double& kappa)=0;

		/// set the omega
		//virtual void setXAxisRotation(double&)=0;

		/// set the phi
		//virtual void setYAxisRotation(double&)=0;

		/// set the kappa
		//virtual void setZAxisRotation(double&)=0;

		/// return omega as a TAngle
		//virtual TAngle getXAxisRotation()const=0;

		/// return phi as a TAngle
		//virtual TAngle getYAxisRotation()const=0;

		/// return kappa as a TAngle
		//virtual TAngle getZAxisRotation()const=0;

		/// set status
		void setStatus(ERotationStatus);

		/// get Status
		bool isNull() const;

			
		//@}


private:
	
			
		ERotationStatus fStatus;
			
			


	//ClassDef(TARotationMatrix, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_A_ROTATION_MATRIX
