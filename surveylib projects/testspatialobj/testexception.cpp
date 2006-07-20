
//#include "TSpatialPointName.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include	"TSUException.h"

/*void foo()
{
	int i;
	i=-15;
	throw i;
}*/

void fool()
{
	string p("sergv3e");
	//char s;
	throw  *(TSUException::Instance(p));
};

void main()
{	
	//try
	//{
		try
		{//foo();
		fool();
		}
		catch(int n)
		{cout<<n;}
		//catch(char text)
		//{cout<<text<<endl;}
		//catch(string s)
		//{cout<<s<<endl;}
		catch(TSUException tsue)
		{//cout<<tsue.getErrorMessage()<<endl;
		//string t("test");
		//tsue.add2Message(t);
		//throw tsue;
		}
		cout<<2<<endl;
		cout<<"exception eliminee"<<endl;
		return;
	//}
	//catch(TSUException tsue)
	//{cout<<tsue.getErrorMessage()<<endl;}

}