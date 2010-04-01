#include <set>
#include <iostream>
using namespace std;

#pragma warning(disable:4786)

class aClass{

public:

	aClass(){}
	aClass(int j){i = j;}
	int getInt() const{ return i;}

	bool operator<(const aClass& right) const{

		return (i<right.getInt());
	}

private:

	int	i;
};

void main(){


	set<aClass, less< aClass > >	testSet;
	set<aClass>::iterator iter, iterEnd, iter2;

	aClass a(1), b(2), c(3), d(4), e(0);

	testSet.insert(a);
	iter = testSet.begin();
	iterEnd = testSet.end();
	cout << "Insertion de 1" << endl;
	cout << "Element pointé par l'iterateur begin: " << iter->getInt() << endl;
	iter2 = iterEnd;
	iter2--;
	cout << "Element pointé par l'iterateur avant end: " << iter2->getInt() << endl;

	testSet.insert(b);
	//iter++;
	cout << "Insertion de 2" << endl;
	cout << "Element pointé par l'iterateur : " << iter->getInt() << endl;
	iter2 = iterEnd;
	iter2--;
	cout << "Element pointé par l'iterateur avant end: " << iter2->getInt() << endl;

	testSet.insert(c);
	cout << "Insertion de 3" << endl;
	cout << "Element pointé par l'iterateur : " << iter->getInt() << endl;
	iter2 = iterEnd;
	iter2--;
	cout << "Element pointé par l'iterateur avant end: " << iter2->getInt() << endl;

	testSet.insert(d);
	cout << "Insertion de 4" << endl;
	cout << "Element pointé par l'iterateur : " << iter->getInt() << endl;
	iter2 = iterEnd;
	iter2--;
	cout << "Element pointé par l'iterateur avant end: " << iter2->getInt() << endl;

	testSet.insert(e);
	cout << "Insertion de 0" << endl;
	cout << "Element pointé par l'iterateur : " << iter->getInt() << endl;
	iter2 = iterEnd;
	iter2--;
	cout << "Element pointé par l'iterateur avant end: " << iter2->getInt() << endl;

	iter = testSet.begin();
	cout << "Element pointé par l'iterateur begin: " << iter->getInt() << endl;

	
}

