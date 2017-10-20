// TStreamFormatterFactory.h: 
/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/** A Factory producing the different TQtStreamFormatter objects.

    Patterns:
	A singleton to ensure only one Factory exists.
*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_QT_STREAM_FORMATTER_FACTORY
#define SU_QT_STREAM_FORMATTER_FACTORY

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
////////////////class  QTextStream;
class  TAStreamFormatter;
//
#include  "TAStreamFormatter.h"
#include  "TADataSet.h"
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
///\ingroup StreamFormatters
class TStreamFormatterFactory //: public TObject  
{
public:

	/**@name Member Functions */
	//@{
		/// Instance method to obtain a pointer to the Factory
		static	TStreamFormatterFactory *instance();

		/// Get a new formatter of a given type
		//TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, QTextStream* );
		TAStreamFormatter *getFormatter( TADataSet* ds, TAStreamFormatter::ETextFormat, string seperator);
		TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, const string&);
		TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, TAStreamFormatter::EIOType, const char*);


		/// Get a description of a given formatter
		string  descriptionOf( TAStreamFormatter::ETextFormat )  const;

		/// Get a formatter enumeration from a given description
		TAStreamFormatter::ETextFormat  whichDataSet( const string& )  const;
	//@}


protected:
	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TStreamFormatterFactory();

		/// Destructor
		virtual ~TStreamFormatterFactory();
	//@}


private:
	/// Copy Constructor 
	TStreamFormatterFactory(const  TStreamFormatterFactory&);

	/// Copy Assignment Operator 
	TStreamFormatterFactory& operator=( const TStreamFormatterFactory& );


	static	TStreamFormatterFactory *fFactory;

	//ClassDef(TDMSFilter, 1)
};



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_QT_STREAM_FORMATTER_FACTORY
