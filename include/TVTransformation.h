//  TVTransformation.h
//
/** Classe de base purement abstraite pour une transformation spatiale
 
  
    Patterns:
  
    Copyright 2000 CERN EST/SU. All rights reserved.
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
class  TVReferenceFrame;
#include  "TPositionVector.h"
#include  "TFreeVector.h"
#include  "TRotationMatrix.h"

#include  "TGlobalDefs.h"
//#include  "TSpatialPosition.h"
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
