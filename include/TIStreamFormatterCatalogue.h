// TIStreamFormatterCatalogue.h: 
//
// A catalogue for obtaining TAStreamFormatter objects.
//
//
// Patterns:
// A singleton to ensure only one catalogue exists.
// 
//
// Copyright 2000, CERN, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#ifndef SU_QT_STREAM_FORMATTER_CATALOGUE
#define SU_QT_STREAM_FORMATTER_CATALOGUE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
////////////////////class  QTextStream;
class  TAStreamFormatter;
//
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
class TIStreamFormatterCatalogue //: public TObject  
{
public:
	//constants
	enum  ETextFormat { kFreeFormat };

	//member functions
	static	TIStreamFormatterCatalogue *instance();

	//TAStreamFormatter *getFormatter( ETextFormat, QTextStream* );
	TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat);
	TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, const string&);
	TAStreamFormatter *getFormatter( TAStreamFormatter::ETextFormat, TAStreamFormatter::EIOType, const char*);


protected:
	// constructors and destructors
	TIStreamFormatterCatalogue();
	virtual ~TIStreamFormatterCatalogue();


private:
	static	TIStreamFormatterCatalogue *fCatalogue;

	//copy constructor declaration
	TIStreamFormatterCatalogue( const TIStreamFormatterCatalogue& );
	
	//ClassDef(TDMSFilter, 1)
};



//////////////////////////////////////////////////////////////////////
// Inline Definitions
//////////////////////////////////////////////////////////////////////


#endif // SU_QT_STREAM_FORMATTER_CATALOGUE
