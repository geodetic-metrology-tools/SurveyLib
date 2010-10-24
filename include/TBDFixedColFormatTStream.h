// TBDFixedColFormatTStream.h
//
//
// Concrete class defining the normal "fixed column size" format file syntax,
// for example the file as used in Transform.
//
// Patterns:
// A concrete decorator class of a QTextStream.
// 
// Copyright 1999,2000 CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#ifndef SU_BD_FIXED_COL_FORMAT_TSTREAM 
#define SU_BD_FIXED_COL_FORMAT_TSTREAM

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <string>
//using namespace std;
//
class  TAngle;
class  TLength;
class  TSpatialPointName;
class  TSpatialPosition;
class  TCoordinateSystem;
class  TSpatialPoint;
//class  QTextStream;
#include "TAStreamFormatter.h"
#include "TAFixedColFormatTStream.h"
//
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
class TBDFixedColFormatTStream :public TAFixedColFormatTStream //: public TObject  
{
public:
	// constructors and destructors
	TBDFixedColFormatTStream(TDataParameters&);
	TBDFixedColFormatTStream(const string&, TDataParameters&);
	TBDFixedColFormatTStream(EIOType, TADataSet&);
	//TBDFixedColFormatTStream( QTextStream * );
	virtual ~TBDFixedColFormatTStream();

	virtual  TAStreamFormatter  &operator>>( TSpatialPoint & );

	
	virtual  TAStreamFormatter  &operator<<( const TSpatialPoint & );


    
protected:

private:
	

	//ClassDef(TBDFixedColFormatTStream, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_BD_FIXED_COL_FORMAT_TSTREAM
