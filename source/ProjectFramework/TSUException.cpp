// TSUException
//
// Singleton that deals with the exceptions
//
// Handles with the exceptions thrown by SU Objects
//
//
//EST/SU 2000 copyright Mark Jones
/////////////////////////////////////////////////////////////////////////

//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
// other forward declarations
#include	"TSUException.h"
#include <iostream>
#include <iomanip>
////////////////////////////////////////////////////////////////



//ClassImp(TSUException)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////
TSUException* TSUException::fException = 0;
string  TSUException::fError_Message = "";


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSUException::TSUException()
{//default constructor
}


TSUException::TSUException(string &s)
{//constructor taking a string
	fError_Message = s;
}


TSUException::~TSUException()
{//destructor
	//print the error message on the screen
	cout<<fException->getErrorMessage()<<endl;
	//exit the program
	exit(1);
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////

TSUException  *TSUException::Instance()
{// verify that fException exist or create new using default constructor
	if(fException == 0)
	{
		fException = new TSUException;
	}

	return fException;
}


TSUException  *TSUException::Instance(string &s)
{// verify that fException exist or create new using constructor with string
	if(fException == 0)
	{
		fException = new TSUException(s);
	}

	return fException;
}


void  TSUException::add2Message(string &s)
{//add a complement to the error message
	fError_Message += s;
}