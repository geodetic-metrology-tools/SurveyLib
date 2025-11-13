// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

/* test file
*/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//#include  "TTLength.h"
//#include "TReflection.h"
#include  "SpatialObjCFns.h"
//#include  "TGraph.h"


void main() {

	//TReflection ref(TReflection::kZEqual0);
	//ref.inverse();


	//TTLength len(LITERAL(12.0));

	real a(LITERAL(2000.0)), b(2000), c(2000);
	real N(LITERAL(0.0));
	cout.precision(7);
	cout << getCG2000N0(a,b,&N);
	cout << "   " << N << endl;
	cout << getCG2000NMachine(a,b,&N) << endl;
	cout << "   " << N << endl;
	//cout << getCG2000TopoN(a,b,c) << endl;

	cout << getCG1985N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG1985NMachine(a,b,&N) << endl;
	cout << "   " << N << endl;

	a=-LITERAL(4565.12580), b=LITERAL(1478.25020);
	cout << getCG2000N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG2000NMachine(a,b,&N) << endl;
	cout << "   " << N << endl;
	//cout << getCG2000TopoN(a,b,c) << endl;

	cout << getCG1985N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG1985NMachine(a,b,&N) << endl << endl << endl;
	cout << "   " << N << endl;

	a=-LITERAL(3758.34500), b=LITERAL(11000.0);
	cout << getCG2000N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG2000NMachine(a,b,&N) << endl;
	cout << "   " << N << endl;

	cout << getCG1985N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG1985NMachine(a,b,&N) << endl << endl << endl;
	cout << "   " << N << endl;

	a=-LITERAL(5000.0), b=LITERAL(0.0);
	cout << getCG2000N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG2000NMachine(a,b,&N) << endl;
	cout << "   " << N << endl;
	//cout << getCG2000TopoN(a,b,c) << endl;

	cout << getCG1985N0(a,b,&N) << endl;
	cout << "   " << N << endl;
	cout << getCG1985NMachine(a,b,&N) << endl << endl << endl;
	cout << "   " << N << endl;




	real x0(-3500), y0(4500), z0(LITERAL(2433.660));
	real x(3000), y(2500), z(2400);
//	real x3, y3, z3;
	//char* geoid = "CG2000";

	
	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(7);

	cout << transformToMLA(-3500, 4500, LITERAL(2433.660), &x, &y, &z, "CG1985") << endl;
	cout << x << "  " << y << "  " << z << endl;


	cout << transformFromMLA(-3500, 4500, LITERAL(2433.660), &x, &y, &z, "CG1985") << endl;
	cout << x << "  " << y << "  " << z << endl;




	cout << transformToMLA2(-3500, 4500, LITERAL(2433.660), &x, &y, &z, "CG1985") << endl;
	cout << x << "  " << y << "  " << z << endl;

	cout << transformFromMLA2(-3500, 4500, LITERAL(2433.660), &x, &y, &z, "CG1985") << endl;
	cout << x << "  " << y << "  " << z << endl;
	
	
	real x2(-LITERAL(4258.36987)), y2(LITERAL(6987.36524)), z2(LITERAL(2436.25896));


	cout << transformToMLA2(-3500, 4500, LITERAL(2433.660), &x2, &y2, &z2, "CG1985") << endl;
	cout << x2 << "  " << y2 << "  " << z2 << endl;

	cout << transformToMLA2(-3500, 4500, LITERAL(2433.660), &x0, &y0, &z0, "CG2000") << endl;
	cout << x0 << "  " << y0 << "  " << z0 <<endl<<endl<<endl<<endl<<endl;


	//test descente verticale
	fstream* stream = new fstream("C:\\workspace\\testDescendeH\\avecDeltaH\\descH.out", ios_base::out);
	stream->setf(ios_base::fixed,ios_base::floatfield);
	stream->precision(7);

	real xr, yr, hr;
	real xv1 = LITERAL(1999.9999639);
	real yv1 = LITERAL(3000.0141029);
	real hv1 = LITERAL(550.0628652);
	*stream<<"descente pour V1"<<endl;
	*stream<<"V1 : "<<xv1<<" / "<<yv1<<" / "<<hv1<<endl;
	*stream<<"premier point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, -50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl;
	*stream<<"deuxieme point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, 50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl<<endl<<endl;

	xv1 = LITERAL(499.9770428);
	yv1 = LITERAL(5000.0455373);
	hv1 = LITERAL(250.8321779);
	*stream<<"descente pour V2"<<endl;
	*stream<<"V2 : "<<xv1<<" / "<<yv1<<" / "<<hv1<<endl;
	*stream<<"premier point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, -50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl;
	*stream<<"deuxieme point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, 50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl<<endl<<endl;

	xv1 = -LITERAL(4500.0976325);
	yv1 = LITERAL(11000.1399937);
	hv1 = LITERAL(459.4004262);
	*stream<<"descente pour V3"<<endl;
	*stream<<"V3 : "<<xv1<<" / "<<yv1<<" / "<<hv1<<endl;
	*stream<<"premier point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, -50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl;
	*stream<<"deuxieme point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, 50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl<<endl<<endl;

	xv1 = LITERAL(5999.0605985);
	yv1 = LITERAL(9.9675598);
	hv1 = LITERAL(451.5534551);
	*stream<<"descente pour V4"<<endl;
	*stream<<"V4 : "<<xv1<<" / "<<yv1<<" / "<<hv1<<endl;
	*stream<<"premier point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, -50, &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl;
	*stream<<"deuxieme point :"<<endl;
	*stream<<"return 1 si il n'a pas d'erreur : "<<descenteVert(xv1, yv1, hv1, LITERAL(50.00), &xr, &yr, &hr)<<endl;
	*stream<<xr<<" / "<<yr<<" / "<<hr<<endl<<endl<<endl;

	return;
}
