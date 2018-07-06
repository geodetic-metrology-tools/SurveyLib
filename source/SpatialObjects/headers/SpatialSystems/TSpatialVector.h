// TSpatialVector.h
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** 3D Vector used as a Spatial Position for stations or as translation vector in Helmert transformation*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_SPATIAL_VECTOR
#define SU_SPATIAL_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations

class TVReferenceFrame;
class TA2DEuclideanRefFrame;
class  TModifiedLocalAstronomicalRF;

#include  "TASpatialAttribute.h"
#include  "TLength.h"
#include  "TSpatialStatus.h"
#include  "TFreeVector.h"
#include  "TVAffineTransformation.h"



typedef TReal Component;
////////////////////////////////////////////////////////////////

/*!\ingroup SpatialObjectsAndSystems 
	@{*/

//! 3D Vector used as a Spatial Position for stations or as translation vector in Helmert transformation
class  TSpatialVector : public TASpatialAttribute   
{
public:

		friend  class  TAReferenceFrame;
		friend  class  TA3DEuclideanRefFrame;
		friend  class	TModifiedLocalAstronomicalRF;

	
	/*!@name Constructors and Destructors */
	//@{
		//! Default Constructor 
//		TSpatialVector(const TFreeVector* fv)

		explicit TSpatialVector(TAReferenceFrame* frame);
		//TSpatialVector(TRefSurfServer::ERefFrame frame);
	
		//! Constructor taking 3 TLength and the RF
		TSpatialVector(TAReferenceFrame*, const TReal, const TReal, const TReal, TCoordSysFactory::ECoordSys );

		//! Constructor taking a free vector and the RF
		//TSpatialVector(const TFreeVector& fv, TVReferenceFrame* frame);

		TSpatialVector(TAReferenceFrame* frame, counted_ptr<TSpatialStatus> svs);
		//TSpatialVector(TRefSurfServer::ERefFrame frame, counted_ptr<TSpatialVectorStatus> svs);


		//! Copy Constructor 
		TSpatialVector( const TSpatialVector&);

		//! Destructor
		virtual  ~TSpatialVector();
	//@}


	/*!@name Member Functions */
	//@{
		//! Copy Assignment Operator 
		TSpatialVector& operator=( const TSpatialVector& );

		//! Plus Operator
		TSpatialVector& operator+( const TSpatialVector& );

		//! Minus Operator
		TSpatialVector& operator-( const TSpatialVector& );

		//! Multiplication by a constant
		TSpatialVector& operator*( const TReal );

		//! Access to the coordinates of the vector as a free vector
		TFreeVector getElements(TCoordSysFactory::ECoordSys) const;
		
		//! Set the coordinates of the vector as a free vector
		bool setElements(const TFreeVector&);
		
		//! transformation between the definition reference frame of the spatial vector and another reference frame
		bool transform(TAReferenceFrame* to);

		bool isInitialise() const { return fFv->isInitialise(); }
	//@}

protected:

	/*!@name Access methods */
	//@{
	//! Return the coordinates of the spatial vector as a free vector
	TFreeVector getVector() const { return *fFv; }
	//@}

	/*!@name Settings methods*/
	//@{
	//! Set coordinates of the spatial vector as a free vector 
	bool setVector(const TFreeVector& fv);
	//@}


private:

	/*!@name private methods*/
	//@{
		//! Change the reference frame after the transformation 
		void changeRefFrameTo(TAReferenceFrame*);

		//! get the coordinate system id of the position vector
		TCoordSysFactory::ECoordSys getCoordSys() const { return fFv->getCoordSysPtr()->getCoordSysId(); }
	//@}


private:
		

	/**@name Member Attributes */
		//@{
				TFreeVector* fFv;
		//@}

	//ClassDef(TSpatialVector, 1)
};
/*@}*/

#endif // SU_SPATIAL_VECTOR
