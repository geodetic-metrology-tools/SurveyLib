// TSpatialStatus.h
//
// General class for status of spatial objects. The three components are considered to be
// linked with axis.
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
/////////////////////////////////////////////////////////////////



#ifndef SU_SPATIAL_STATUS
#define SU_SPATIAL_STATUS


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////////////////

class  TVReferenceFrame;

/////////////////////////////////////////////////////////////////

/*!\ingroup SpatialObjectsAndSystems
	@{*/

//! Class storing the statuses of objects related to a 3D position
class  TSpatialStatus //: public TObject  
{
public:
	//friend class TAReferenceFrame;

	//!@name Constants
	//@{
	enum  ESpatialStatus {kPosNull, kUnknown,  kCala, kVx, kVy, kVz, kVxy, kVxz, kVyz, kVxyz};
	//@}


	/*!@name Constructors and Destructors */
	//@{
		//! Constructor 
		TSpatialStatus();

		//! Copy Constructor 
		TSpatialStatus(const  TSpatialStatus&);

		//! Destructor
		virtual  ~TSpatialStatus();
	//@}


		//! Copy Assignment Operator 
		TSpatialStatus& operator=( const TSpatialStatus& );


	/*!@name Access methods*/
	//@{
		//! returns the 3D status if defined for the position's reference frame
		virtual ESpatialStatus	getObjectStatus() const {return fSpatialStatus;}

		/*!@return the position's number of variable coordinates*/
		virtual int				getVariableDimension() const;

	//@}


	/*!@name Set methods*/
	//@{
		//! sets the 3D status if defined in the position's Reference Frame
		virtual void			setObjectStatus(ESpatialStatus s) {fSpatialStatus = s; return;}

	//@}

	

private:

	ESpatialStatus				fSpatialStatus;

	//ClassDef(TPositionStatus, 1)
};
/*@}*/


#endif // SU_SPATIAL_STATUS
