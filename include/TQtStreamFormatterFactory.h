// TQtStreamFormatterFactory.h: 
//
/** A Factory producing the different TQtStreamFormatter objects.

    Patterns:
	A singleton to ensure only one Factory exists.

 
    Copyright 2000 CERN EST/SU. All rights reserved.
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
class  QTextStream;
class  TAQtStreamFormatter;
//
#include  "TAQtStreamFormatter.h"
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
class TQtStreamFormatterFactory //: public TObject  
{
public:

	/**@name Member Functions */
	//@{
		/// Instance method to obtain a pointer to the Factory
		static	TQtStreamFormatterFactory *instance();

		/// Get a new formatter of a given type
		TAQtStreamFormatter *getFormatter( TAQtStreamFormatter::ETextFormat, QTextStream* );

		/// Get a description of a given formatter
		string  descriptionOf( TAQtStreamFormatter::ETextFormat )  const;

		/// Get a formatter enumeration from a given description
		TAQtStreamFormatter::ETextFormat  whichDataSet( const string& )  const;
	//@}


protected:
	/**@name Constructors and Destructors */
	//@{
		/// Default Constructor 
		TQtStreamFormatterFactory();

		/// Destructor
		virtual ~TQtStreamFormatterFactory();
	//@}


private:
	/// Copy Constructor 
	TQtStreamFormatterFactory(const  TQtStreamFormatterFactory&);

	/// Copy Assignment Operator 
	TQtStreamFormatterFactory& operator=( const TQtStreamFormatterFactory& );


	static	TQtStreamFormatterFactory *fFactory;

	//ClassDef(TDMSFilter, 1)
};



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_QT_STREAM_FORMATTER_FACTORY
