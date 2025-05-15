// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/*#include "TLength.h"
#include "TAngle.h"*/
extern void f();

void main();

void main()
{
	try {f();}
	catch (char *text)
	{ cout<<text<<endl;}
	return;
}

//#include "testTLength&TAngle.cpp"
