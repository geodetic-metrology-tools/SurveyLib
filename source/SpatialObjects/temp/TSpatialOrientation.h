// TSpatialOrientation.h
//
/** Class for the matrices of rotation used for points transformations */
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_SPATIAL_ORIENTATION
#define SU_SPATIAL_ORIENTATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
class  TAngle;
#include  "TRotationMatrix.h"
#include  "TEuclideanRefFrame.h"
//
//typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TSpatialOrientation //: public TObject  
{
public:
	//constants

	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TSpatialOrientation(TEuclideanRefFrame*);

		/// Constructor takink the radians value of the angles in the order omega-phi-kappa
		//TSpatialOrientation(double, double, double);

		/// Constructor takink the angles in the order omega-phi-kappa
		TSpatialOrientation(TAngle&, TAngle&, TAngle&, TEuclideanRefFrame*);

		/// Copy Constructor 
		TSpatialOrientation(const  TSpatialOrientation&);

		/// Destructor
		virtual  ~TSpatialOrientation();
	//@}


	/**@name Member Functions */
	//@{
		/// Copy Assignment Operator 
		TSpatialOrientation& operator=( const TSpatialOrientation& );
		
		///set the 3 rotations taking TAngles in the order Rx(omega)-Ry(phi)-Rz(kappa)
		void setAllRotations(TAngle&, TAngle&, TAngle&);

		/// set the omega
		void setXAxisRotation(TAngle&);

		/// set the phi
		void setYAxisRotation(TAngle&);

		/// set the kappa
		void setZAxisRotation(TAngle&);

		/// fill the matrix of rotation Rzyx
		void fillRotationMatrix();

		/// set the pointer to RF
		void setReferenceFrame(TEuclideanRefFrame*);

		/// set the rotation matrix
		void setMatrix(const TRotationMatrix&);

		///get a pointer to the RF
		TEuclideanRefFrame* getReferenceFrame() const;

		/// return omega as a TAngle
		TAngle getXAxisRotation()const;

		/// return phi as a TAngle
		TAngle getYAxisRotation()const;

		/// return kappa as a TAngle
		TAngle getZAxisRotation()const;

		/// return the associated TRotationMatrix
		TRotationMatrix getMatrix();

		/// return the bearing
		TAngle bearing();

		//@}


private:
	/**@name Member Attributes */
	//@{
			TAngle fXAxisRotation;//omega
			TAngle fYAxisRotation;//phi
			TAngle fZAxisRotation;//kappa
			
			TRotationMatrix fRotationMatrix;//Rzyx Matrix

			TEuclideanRefFrame* fFrameOfReference;
			
			//@}

	//ClassDef(TSpatialOrientation, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////

inline	TAngle TSpatialOrientation::getXAxisRotation()const{return fXAxisRotation;}
inline	TAngle TSpatialOrientation::getYAxisRotation()const{return fYAxisRotation;}
inline	TAngle TSpatialOrientation::getZAxisRotation()const{return fZAxisRotation;}
inline  TEuclideanRefFrame* TSpatialOrientation::getReferenceFrame() const {return fFrameOfReference;}

#endif // SU_SPATIAL_ORIENTATION
