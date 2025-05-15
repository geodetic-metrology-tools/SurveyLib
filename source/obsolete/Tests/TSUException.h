/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿// TSUException.h: 
//
// Singleton that deals with the exceptions
// 
// 
//
//////////////////////////////////////////////////////////////////////

#ifndef SU_EXCEPTION
#define SU_EXCEPTION

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <string>
using namespace std;


// Class Definition
class	TSUException 
{
public:
	static TSUException* Instance();//create the singleton
	static TSUException* Instance(string &);//create the singleton using a string 
	void  add2Message(string &);//for "rethrowed" exception message to be completed
	string getErrorMessage();//used to get the exit message
	virtual ~TSUException();//destructor
	
protected:
	TSUException();//default constructor
	TSUException(string &);//constructor taking a string
	

private:
	static TSUException* fException;//pointer to the unique exception
	static string fError_Message;//message that is send before exiting the program
};

///////////////////////////////////////////////////////////////////////////
// inline functions
///////////////////////////////////////////////////////////////////////////
inline string TSUException::getErrorMessage() {return fError_Message;}
#endif
