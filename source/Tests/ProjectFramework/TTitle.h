// TTitle.h: 
//
// Class for storing the tile of a application data set 
// 
//
// Copyright 1999,2000, Mark Jones, EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////

#if !defined(SU_TITLE)
#define SU_TITLE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
#include <string>
using namespace std;
//
// typedefs
////////////////////////////////////////////////////////////////



//Class definition
class TTitle //: public TObject  
{
public:
	//constants

	// constructors and destructors
	TTitle();
	TTitle( string & );
	virtual ~TTitle() = 0;

	//member functions
	void	appendLine( const string & );
	void	appendLine( const char * );
	void	appendText( const string & );

	string	getText() const;

private:
	string	fTitle;

	//ClassDef(TTitle, 1)
};



#endif // !defined(SU_TITLE)

