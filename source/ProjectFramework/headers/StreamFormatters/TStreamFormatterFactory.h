/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿// TStreamFormatterFactory.h: 

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
		TAStreamFormatter *getFormatter( TADataSet* ds, TAStreamFormatter::ETextFormat, std::string seperator);
		TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, const std::string&);
		TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, TAStreamFormatter::EIOType, const char*);


		/// Get a description of a given formatter
		std::string  descriptionOf( TAStreamFormatter::ETextFormat )  const;

		/// Get a formatter enumeration from a given description
		TAStreamFormatter::ETextFormat  whichDataSet( const std::string& )  const;
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
