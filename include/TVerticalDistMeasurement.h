// TVerticalDistMeasurement.h
//
/*! Class for a vertical distance measurement 

	Patterns:
 
	Copyright 2000 CERN EST/SU. All rights reserved.
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_TVerticalDistMeasurement
#define SU_TVerticalDistMeasurement


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
#include "TLength.h"
#include  "TAMeasurement.h"
#include  "TDistConstants.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*! \ingroup spatialmeasurements
	@{*/

//! Class for a vertical distance measurement
class  TVerticalDistMeasurement : public TAPointMeasurement  
{
};
/*@}*/


/**@name Typedefs*/
//@{
/// Type of the container used to store the vertical dist measurements
typedef list< TVerticalDistMeasurement > VertDistContainer;
/// Type of the iterator pointing to an element of the vertical dists container
typedef VertDistContainer::iterator VertDistMeasIterator;
/// Type of the const iterator pointing to an element of the vertical dists container
typedef VertDistContainer::const_iterator VertDistMeasConstIter;
//@}


#endif // SU_TVerticalDistMeasurement


