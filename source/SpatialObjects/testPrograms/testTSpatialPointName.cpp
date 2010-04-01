//////////////////////////////////////////////////////
// test file for TSpatialPointName
//////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "TSpatialPointName.h"

void main ()
{	TSpatialPointName test("merc"/*, "fev", '9'*/);
//	test.setPtName("merc", "fev", '9');
//	cout<<test.getDBName()<<endl;
	cout<<test.getPtName()<<endl;
	cout<<test.getName()<<endl;
	cout<<test.getClass()<<endl;
	cout<<test.getPoint()<<endl;
	test.setDBName("clas___point1");
	cout<<test.getPoint()<<endl;
	cout<<test.getName()<<endl;
	cout<<test.getClass()<<endl;
	
	
}