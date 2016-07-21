// TACoordSysVector.h
//
/** Abstract class use for explain TPositionVector and TFreeVector in a Coordonate System 
//
// Patterns:
//
// 
// Copyright 2002 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_A_COORDSYS_VECTOR
#define SU_A_COORDSYS_VECTOR


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "TLength.h"
#include "TDouble.h"
#include  "TCoordSysFactory.h"

class TVCoordinateSystem;



/*! \ingroup MathematicalConcepts
	@{*/

//! Abstract class use for explain TPositionVector and TFreeVector
class  TACoordSysVector
{
public:

	friend class TACoordinateSystem;

	TACoordSysVector();
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
	//@}

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
