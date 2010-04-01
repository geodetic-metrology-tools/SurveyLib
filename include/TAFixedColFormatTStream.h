// TAFixedColFormatTStream.h
//
//
// Base class defining the normal "fixed column size" format file syntax,
// for example the file as used in Transform.
//
// Patterns:
// A concrete decorator class of a QTextStream.
// 
// Copyright 1999,2000 CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#ifndef SU_A_FIXED_COL_FORMAT_TSTREAM 
#define SU_A_FIXED_COL_FORMAT_TSTREAM

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <string>
using namespace std;
//
class  TAngle;
class  TLength;
class  TSpatialPointName;
class  TSpatialPosition;
class  TCoordinateSystem;
class  TSpatialPoint;

#include "TAStreamFormatter.h"
//
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
class TAFixedColFormatTStream :public TAStreamFormatter //: public TObject  
{
public:
	// constructors and destructors
	TAFixedColFormatTStream(TDataParameters&);
	TAFixedColFormatTStream(const string&, TDataParameters&);
	TAFixedColFormatTStream(EIOType, TADataSet&);
	virtual ~TAFixedColFormatTStream();

	// member functions

	virtual  TAStreamFormatter  &operator>>( TSpatialPoint & ) = 0;

	virtual  TAStreamFormatter  &operator<<( const TSpatialPointName & );
	virtual  TAStreamFormatter  &operator<<( const TSpatialPosition & );
	virtual  TAStreamFormatter  &operator<<( const TSpatialPoint & ) = 0;

    virtual  void  skipCommentLines();

	///returns the charachter sequence used to spearate fields
	virtual string		separator() const;

protected:

private:
	// member attributes
	string			fLineBuf;

	//ClassDef(TAFixedColFormatTStream, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_A_FIXED_COL_FORMAT_TSTREAM
