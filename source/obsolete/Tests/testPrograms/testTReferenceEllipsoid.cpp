// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿//////////////////////////////////////////////////////
// test file for TreferenceEllipsoid
//////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include "TReferenceEllipsoid.h"
#include <string>
using namespace std;

void main();

void main ()
{

TReferenceEllipsoid WGS84(6378137,0.08189191025);
//double a=6378137;
//double e=0.08189191025;
string n("WGS84");

//WGS84.setAAndE(a,e);
WGS84.setName(n);

cout<<setprecision(15)<<WGS84.getA()<<endl;
cout<<WGS84.getF()<<endl;
cout<<setprecision(15)<<WGS84.getB()<<endl;
cout<<setprecision(15)<<WGS84.getE()<<endl;
cout<<setprecision(15)<<WGS84.getSqrE()<<endl;
cout<<setprecision(15)<<WGS84.getEPrime()<<endl;
cout<<setprecision(15)<<WGS84.getSqrEPrime()<<endl;
cout<<WGS84.getName()<<endl;
}
