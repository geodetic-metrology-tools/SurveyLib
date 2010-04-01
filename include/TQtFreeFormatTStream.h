// TQtFreeFormatTStream.h
//
//
// Concrete class defining the free format file syntax,
// for example the file as used in CSGeo, and Geotran.
//
// Patterns:
// A concrete decorator class of a QTextStream.
// 
// Copyright 1999,2000 CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#ifndef SU_FREE_FORMAT_TSTREAM 
#define SU_FREE_FORMAT_TSTREAM

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
class  QTextStream;
#include "TAQtStreamFormatter.h"
//
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
class TQtFreeFormatTStream :public TAQtStreamFormatter //: public TObject  
{
public:
	// constructors and destructors
	TQtFreeFormatTStream( QTextStream * );
	virtual ~TQtFreeFormatTStream();

	// member functions
	virtual  TAQtStreamFormatter  &operator>>( TAngle & );
	virtual  TAQtStreamFormatter  &operator>>( TLength & );
	virtual  TAQtStreamFormatter  &operator>>( TSpatialPointName & );
	virtual  TAQtStreamFormatter  &operator>>( TSpatialPosition & );
	virtual  TAQtStreamFormatter  &operator>>( TSpatialPoint & );

	virtual  TAQtStreamFormatter  &operator<<( const TAngle & );
	virtual  TAQtStreamFormatter  &operator<<( const TLength & );
	virtual  TAQtStreamFormatter  &operator<<( const TSpatialPointName & );
	virtual  TAQtStreamFormatter  &operator<<( const TSpatialPosition & );
	virtual  TAQtStreamFormatter  &operator<<( const TSpatialPoint & );

    virtual  void  skipCommentLines();

	///returns the charachter sequence used to separate fields
	virtual QString		separator() const;

protected:

private:
	// member attributes
	QString			fLineBuf;

	//ClassDef(TQtFreeFormatTStream, 1)
};




//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////



#endif // SU_FREE_FORMAT_TSTREAM
