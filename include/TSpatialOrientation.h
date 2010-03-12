// TSpatialOrientation.h
//
/** Class for the matrices of rotation used for points transformations 

 Patterns:

 
 Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_SPATIAL_ORIENTATION
#define SU_SPATIAL_ORIENTATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//

class  TAngle;
class  TAAffineTransformation;
#include  "TASpatialAttribute.h"
#include  "TVReferenceFrame.h"
#include  "TRotationMatrix.h"
#include  "TSpatialStatus.h"
#include  "TAReferenceFrame.h"
//
//typedefs
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup spatialobjects
	@{*/

//! Class for the matrices of rotation used for points transformations
class  TSpatialOrientation : public TASpatialAttribute //: public TObject  
{
public:

	friend TAReferenceFrame;
	//constants

	/*!@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TSpatialOrientation(TAReferenceFrame*);

		/// Constructor takink the angles in the choosen order
		TSpatialOrientation(TRotationMatrix::ERotationType,
							TAngle&, TAngle&, TAngle&,
							TAReferenceFrame*, TCoordSysFactory::ECoordSys );

		/// Constructor taking the radian value of the angles in the choosen order
		TSpatialOrientation(TRotationMatrix::ERotationType, quad&, quad&, quad&,
							TAReferenceFrame*, TCoordSysFactory::ECoordSys );

		//! Constructor taking a rotation matrix
		TSpatialOrientation(const TRotationMatrix, TAReferenceFrame*);

		/// Copy Constructor 
		TSpatialOrientation(const  TSpatialOrientation&);

		/// Destructor
		virtual  ~TSpatialOrientation();
	//@}


	/*!@name Member Functions */
	//@{
		//! Copy Assignment Operator 
		TSpatialOrientation& operator=( const TSpatialOrientation& );
		
		//! Return the rotation matrix
		TRotationMatrix getElements(TCoordSysFactory::ECoordSys) const;

		//! Set the rotation matrix
		bool setElements( const TRotationMatrix& );
	//@}


private:
	/*!@name Access methods*/
	//@{
		//! Return the orientation matrix
		TRotationMatrix getOrientation() const;
	//@}

	/*!@name Settings methods*/
	//@{
		//! set the orientation with a rotation matrix
		bool setOrientation( const TRotationMatrix& rm);
	//@}

private:

	/*!@name Member Attributes */
	//@{					
			TRotationMatrix* fRotationMatrix;//!< Rzyx Matrix
	//@}

	//ClassDef(TSpatialOrientation, 1)
};
/*@}*/
#endif // SU_SPATIAL_ORIENTATION
