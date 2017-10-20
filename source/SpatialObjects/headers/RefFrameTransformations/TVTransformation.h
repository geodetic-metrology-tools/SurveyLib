//  TVTransformation.h
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** Classe de base purement abstraite pour une transformation spatiale
 
  
    Patterns:
  
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_TRANSFORMATION
#define SU_V_TRANSFORMATION


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <##classname##>
//using namespace std;
//
class  TPositionVector;
class  TFreeVector;
class  TRotationMatrix;

//#include  "TGlobalDefs.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialobjects
	@{*/

//! Classe de base purement abstraite pour une transformation spatiale
class /*SU_DECLSPEC*/ TVTransformation //: public TObject  
{
public:

	virtual ~TVTransformation() { }

	/**@name Member Functions */
	//@{
		//! transform a position vector
		virtual  bool  transform( TPositionVector& ) const = 0;

		//! transform a free vector
		virtual  bool  transform( TFreeVector& ) const = 0;

		//! transform a Rotation Matrix
		virtual  bool  transform( TRotationMatrix& ) const = 0;
	//@}


private:

	//ClassDef(TVTransformation, 1)
};
/*@}*/

//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_V_TRANSFORMATION
