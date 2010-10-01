// TVNumericValue.h
//
/** A Purely abstract base class for a numeric value, that
    enumerates the different computational states of a numeric value, and
	the methods for determining the computational status
  
   Patterns:
  
   
   Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_V_NUMERIC_VALUE
#define SU_V_NUMERIC_VALUE


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//#include  <**classname**>
//using namespace std;
//
//class  **classname**;
//#include  "**classname**.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TVNumericValue //: public TObject  
{
public:
	/**@name Member Functions */
	//@{
		/// Returns a boolean indicating if the numeric value is NULL 
		virtual  bool  isNull() const  = 0;

		// returns the computational status of a numeric value
		virtual  EStatus  getStatus() const  = 0;
		
		// sets the computational status of a numeric value
		virtual  void  setStatus( EStatus )  = 0;
	//@}


protected:


private:

	//ClassDef(TVNumericValue, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_V_NUMERIC_VALUE
