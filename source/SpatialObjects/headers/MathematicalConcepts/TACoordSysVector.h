// TACoordSysVector.h
/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** Abstract class use for explain TPositionVector and TFreeVector in a Coordonate System */
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_COORDSYS_VECTOR
#define SU_A_COORDSYS_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "TLength.h"
#include "TDouble.h"
#include  "TCoordSysFactory.h"
#include <TSparseMatrix.h>

class TVCoordinateSystem;

#if USE_SERIALIZER
#	include <Serializer.hpp>
#endif // USE_SERIALIZER

/*! \ingroup MathematicalConcepts
	@{*/
#if USE_SERIALIZER
class TACoordSysVector : public Serializable
#else
//! Abstract class use for explain TPositionVector and TFreeVector
class TACoordSysVector
#endif // USE_SERIALIZER

{
public:

	friend class TACoordinateSystem;

	TACoordSysVector();
	//!Constructor using a TVector, per default Cartesian
	TACoordSysVector(const TVector &, TCoordSysFactory::ECoordSys = TCoordSysFactory::k3DCartesian);

	virtual ~TACoordSysVector() { }
	
	
	/**@name Member Public Functions */
	//@{
		//!Equivalence Operator 
		bool operator==( const TACoordSysVector& ) const;

		/*!test if two object have the same coordinate system
		\return false if it s wrong*/
		bool testCoordSysCart(TCoordSysFactory::ECoordSys) const;

		//! return true if coordinates are not set to NO_VALf
		bool isInitialise() const;
		
		//!get the X coordinate of a vector in a specific Coordinate System
		TLength getX() const;

		//!get the Y coordinate of a vector in a specific Coordinate System
		TLength getY() const;

		//!get the Z coordinate of a vector in a specific Coordinate System
		TLength getZ() const;

		//!set the X coordinate of a vector in a specific Coordinate System return true if X is defined
		bool setX(const TLength&);

		//!set the Y coordinate of a vector in a specific Coordinate System return true if Y is defined
		bool setY(const TLength&);

		//!set the Z coordinate of a vector in a specific Coordinate System return true if Z is defined
		bool setZ(const TLength&);

		//! Allows to retrieve one of the coordinates of the vector
		TReal operator[](int i) const;

		//! Allows to retrieve one of the coordinates of the vector and to modify it
		TReal& operator[](int i);
		
		//!return fCoordSys
		TVCoordinateSystem* getCoordSysPtr() const;

		//!return ECoordSys
		TCoordSysFactory::ECoordSys getCoordSys() const;

		//! sets the coordinate system
		void setCoordSys(const TCoordSysFactory::ECoordSys );

		//!transpose a FreeVector or a PositionVector in a T3DMatrix
		virtual T3DMatrix transposed() const;


		// return a TVector 
		TVector toRealVector() const;
	//@}

#if USE_SERIALIZER
		// Inherited via Serializable
		virtual void serialize(ObjectSerializer &obj) const override;
#endif	


protected:


		/**@name Member Protected Functions */
	//@{
	
	//!get the Xi coordinate of a vector in all Coordinate System
	TReal	getX(const int& ) const;


	//!set the Xi coordinate of a vector in all Coordinate System
	void	setX(const int&, const TReal&);
			
	//@}
		


private:
	
			
	/**@name Member Attributes */
		//@{
				//int				fNbRows;
				TReal					fVector[3]; /*!< element of the 3*1 vector */
				TVCoordinateSystem*		fCoordSys; /*!< coordinate system */

		//@}

	//ClassDef(TACoordSysVector, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_A_COORDSYS_VECTOR
