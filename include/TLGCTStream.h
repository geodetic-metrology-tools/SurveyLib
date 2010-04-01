// TLGCTStream.h
//
//
// Concrete class defining the old LGC file syntax,
//
// Patterns:
// A concrete decorator class of a QTextStream.
// 
// Copyright 1999,2000 CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



#ifndef SU_TLGCTStream
#define SU_TLGCTStream


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include  <string>
using namespace std;
//
class TWPSFilter;

class TAngle;
class TLength;
class TSpatialPointName;
class TSpatialPosition;
//class TSpatialLine;
class TCoordinateSystem;
class TLSCalcSpPoint;
///////class QTextStream;

class THorizontalDistMeas;
class TVerticalDistMeasurement;
class THorAngleMeasurement;
class TZenithDistMeasurement;
class T2DOffsetMeasurement;
/*class TWPSMeasurement;
class TWireToWireDistMeas;*/

//class TRadialOffsetCnstr;

//#include "TWPSFilter.h"
//#include "TWTWFilter.h"

#include "TAStreamFormatter.h"
// typedefs
//
//
////////////////////////////////////////////////////////////////



//Class definition
class  TLGCTStream : public TAStreamFormatter  
{
public:

	/**@name Constructors and Destructors */
	//@{
		//! Default Constructor
		TLGCTStream();
		TLGCTStream(const string&);
		TLGCTStream(TAStreamFormatter::EIOType, const char*); //(QTextStream* stream);

		//! Destructor
		virtual  ~TLGCTStream();
	//@}

	/**Sets the WPS measurements filter
	@param wpsMeasType an element of the TWPSFilter::EWPSMeastype enumeration*/
//	virtual void	setWPSFilter(TWPSFilter::EWPSMeasType wpsMeasType);
	/**Sets the WTW measurements filter
	@param wtwMeasType an element of the TWTWFilter::EWTWMeastype enumeration*/
//	virtual void	setWTWFilter(TWTWFilter::EWTWMeasType wtwMeasType);

	/**@name Overloaded stream extraction operators*/
	//@{
	//!Extraction of a TSpatialPoint object;
	virtual TAStreamFormatter &operator>>( TSpatialPoint & );
	//!Extraction of a TSpatialLine object
//	virtual TAStreamFormatter &operator>>( TSpatialLine &);
	//!Extraction of a THorizontalDistMeas object
	virtual TAStreamFormatter& operator>>( THorizontalDistMeas& );
	//!Extraction of a TVerticalDistMeasurement object
	virtual TAStreamFormatter& operator>>( TVerticalDistMeasurement& );
	//!Extraction of a THorAngleMeasurement object
	virtual TAStreamFormatter& operator>>( THorAngleMeasurement& );
	//!Extraction of a TZenithDistMeasurement object
	virtual TAStreamFormatter& operator>>( TZenithDistMeasurement& );
	//!Extraction of a T2DOffsetMeasurement object
	virtual TAStreamFormatter& operator>>( T2DOffsetMeasurement& );
	//!Extraction of a TWPSMeasurement object
//	virtual TAStreamFormatter& operator>>( TWPSMeasurement& );
	//!Extraction of a TWireToWireDistMeas object
//	virtual TAStreamFormatter& operator>>( TWireToWireDistMeas& );
	//!Extraction of a TRadialOffsetCnstr object
//	virtual TAStreamFormatter& operator>>( TRadialOffsetCnstr& );

	//@}

	/**@name Overloaded stream insertion operator*/
	//@{
	//!Insertion of a TSpatialPosition object
	virtual TAStreamFormatter &operator<<( const TSpatialPosition & );
/*
	//!Insertion of a TSpatialPositionError object
	virtual TAStreamFormatter &operator<<( const TSpatialPositionError & );
*/
	//!Insertion of a TSpatialPoint object
	virtual TAStreamFormatter &operator<<( const TSpatialPoint & );
	//!Insertion of a TLSCalcSpPoint object
	virtual TAStreamFormatter &operator<<( TLSCalcSpPoint & );
	//!Insertion of a T3DVector object
	virtual TAStreamFormatter &operator<<( TFreeVector & );
	//!Insertion of a T3DMatrix object
	virtual TAStreamFormatter &operator<<( T3DMatrix& );

	//@}

	//!Skips the comment lines
    virtual  void  skipCommentLines();

	//!returns the charachter sequence used to spearate fields
	virtual string		separator() const;



private:

/*	TWPSFilter*		fWPSFilter;
	TWTWFilter*		fWTWFilter;*/

	string			fLineBuf;

	//ClassDef(TLGCTStream, 1)
};


//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////






#endif // SU_TLGCTStream
