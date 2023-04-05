// TACoordinateSystem.h
/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** Abstract class for Coordonate System */
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_COORDINATE_SYSTEM
#define SU_A_COORDINATE_SYSTEM


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "TVCoordinateSystem.h"


/*! \ingroup MathematicalConcepts 
	@{*/
//! Abstract class for Coordinate System
class TACoordinateSystem : public TVCoordinateSystem //: public TObject
{
public:
	virtual ~TACoordinateSystem() override = default;

	/*!\name Functions for Vector*/
	//@{
		/*!get the H coordinate of a position vector, default def:
		\return TLength Null*/
		virtual TLength getH(const TPositionVector*) const;

		/*!get the Lambda coordinate of a position vector, default def: 
		\return TLength Null*/
		virtual TAngle getLambdaEllipsoid(const TPositionVector*) const;

		/*!get the Phi coordinate of a position vector, default def: 
		\return TAngle Null*/
		virtual TAngle getPhiEllipsoid(const TPositionVector*) const;

		/*!get the X coordinate of a position vector or a free vector, default def: 
		\return TLength Null*/
		virtual TLength getX(const TACoordSysVector*) const;

		/*!get the Y coordinate of a position vector or a free vector, default def: 
		\return TLength Null*/
		virtual TLength getY(const TACoordSysVector*) const;

		/*!get the Z coordinate of a position vector or a free vector, default def: 
		\return TLength Null*/
		virtual TLength getZ(const TACoordSysVector*) const;

		/*!set the H Coordinate of a position vector, default def:
		\return false*/
		virtual bool setH(TPositionVector*, const TLength&);

		/*!set the Lambda Coordinate of a position vector, default def:
		\return false*/
		virtual bool setLambdaEllipsoid(TPositionVector*, const TAngle&);

		/*!set the Phi Coordinate of a position vector, default def:
		\return false*/
		virtual bool setPhiEllipsoid(TPositionVector*, const TAngle&);

		/*!set the X Coordinate of a position vector or a free vector, default def:
		\return false*/
		virtual bool setX(TACoordSysVector*, const TLength&);

		/*!set the Y Coordinate of a position vector or a free vector, default def:
		\return false*/
		virtual bool setY(TACoordSysVector*, const TLength&);

		/*!set the Z Coordinate of a position vector or a free vector, default def:
		\return false*/
		virtual bool setZ(TACoordSysVector*, const TLength&);
	//@}

	/*!\name Functions for Matrix*/
	//@{
		using TVCoordinateSystem::getElt;

		/*!create a TRotationMatrix default def:
		\return false*/
		virtual bool setAllRotations(TRotationMatrix*, TRotationMatrix::ERotationType kR, TReal &om, TReal &p, TReal &k);

		/*!get angles of a TRotationMatrix return a structure (omega, phi, kappa), default def
		\return false*/
		virtual	struct Angles getAngles(const TRotationMatrix*, const TRotationMatrix::ERotationType kR) const;
		
		//!change a rotation matrix into the identity matrix, default def: return false
		virtual bool identity(TRotationMatrix*);
		
		//!set a element into a 3D matrix
		virtual	bool setElt(T3DMatrix*, const int, const int, const TReal);

		//!get a element from a 3D matrix
		virtual	TReal getElt(const T3DMatrix*, const int, const int) const;
		
		//!get a element from a rotation matrix
		virtual	TReal getElt(const TRotationMatrix*, const int, const int) const;
		
	//@}

	/*!\name Member Functions*/
	//@{
		//! set the coordinate system identifier
		virtual void setCoordSysId(TCoordSysFactory::ECoordSys);

		//! get the coordinate system identifier
		virtual TCoordSysFactory::ECoordSys getCoordSysId() const;
	//@}

#if USE_SERIALIZER
		// Inherited via Serializable
		virtual void serialize(SerializerObject::SerializationHelper &obj) const override;
#endif	

protected:

	/*!\name Member Protected Functions for Vector*/
	//@{
		//!get the Xi coordinate of a vector in all Coordinate System
		TReal	getX(const TACoordSysVector*, const int& ) const;


		//!set the Xi coordinate of a vector in all Coordinate System
		void	setX(TACoordSysVector*, const int&, const TReal&);
	//@}
		
	/*!\name Member Protected Functions for Matrix*/
	//@{
		//!get the (i,j) value of a matrix
		TReal getC(const TACoordSysMatrix*, const int& i, const int& j) const;

		//!set value to (i,j) of a matrix
		void setC(TACoordSysMatrix*, const int& i, const int& j, TReal value);
	//@}

private:
	
	TCoordSysFactory::ECoordSys			fCoordSysId; /*!< coordinate system identifier */
		
	

	//ClassDef(TACoordinateSystem, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_A_COORDINATE_SYSTEM
