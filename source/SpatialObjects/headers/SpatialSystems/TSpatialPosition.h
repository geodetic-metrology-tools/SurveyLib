// TSpatialPosition.h: 
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/*   
  The Spatial Position of a point in a given reference frame

  Patterns:
  
*/
//////////////////////////////////////////////////////////




#ifndef SU_SPATIAL_POSITION
#define SU_SPATIAL_POSITION

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////
class  TLength;
class  TAngle;
class  TVReferenceFrame;
class  TModifiedLocalAstronomicalRF;
class  TReferenceEllipsoid;
class TVRefFrameTransformation;

#include  "TASpatialAttribute.h"
#include  "counted_ptr.h"
#include  "TPositionVector.h"
#include  "TGraph.h"
#include  "TVCoordinateSystem.h"


using namespace std;

// typedefs
typedef  TReal  Coordinate;
typedef  bool  CoordKnown;
//
//
//////////////////////////////

/*!\ingroup SpatialObjectsAndSystems
	@{*/

//! The Spatial Position of a point in a given reference frame 
class TSpatialPosition : public TASpatialAttribute //: public TObject  
{

public:
	friend  class	TAReferenceFrame;
	friend  class	TA3DEuclideanRefFrame;
	friend  class	TModifiedLocalAstronomicalRF;

	/*!@name Constructors and Destructors */
	//@{
		explicit  TSpatialPosition( TAReferenceFrame* rf );

		TSpatialPosition(TAReferenceFrame* rf, const TPositionVector& pv);

		TSpatialPosition(TAReferenceFrame*, const TReal, const TReal, const TReal, TCoordSysFactory::ECoordSys );

		TSpatialPosition(TAReferenceFrame*, counted_ptr< TSpatialStatus >);

		TSpatialPosition( const TSpatialPosition& );

		virtual ~TSpatialPosition();
	//@}


	/*!@name Member Functions */
	//@{
		//! Copy Assignment Operator 
		TSpatialPosition& operator=(const TSpatialPosition&);
		
		//! Access to a copy of the position vector (managed by TVReferenceFrame)
		TPositionVector getCoordinates(TCoordSysFactory::ECoordSys) const;
		//! Setting of the position vector (managed by TVReferenceFrame)
		bool setCoordinates(const TPositionVector& pv);

		//! transformation between the definition reference frame of the spatial position and another reference frame
		bool transform(TAReferenceFrame* to);

		//! Return true if the position vector is initialised
		bool isInitialise() const { return fX->isInitialise(); }

	//@}

	


protected:

private:

	// private default constructor
	TSpatialPosition();


	/*!@name Access methods */
	//@{
		//! Access to the position vector
		TPositionVector getPositionVector() const;
	//@}
	
	/*!@name Settings methods */
	//@{
		//! Setting of the position vector
		bool setPositionVector(const TPositionVector& pv);
	//@}

	//! change the reference frame after a transformation to another reference frame
	void changeRefFrameTo(TAReferenceFrame*);

	//! get the coordinate system id of the position vector
	TCoordSysFactory::ECoordSys getCoordSys() const { return fX->getCoordSysPtr()->getCoordSysId(); }

	
	
private:
	// member attributes
	TPositionVector*  fX;

};
/*@}*/
#endif // SU_SPATIAL_POSITION
