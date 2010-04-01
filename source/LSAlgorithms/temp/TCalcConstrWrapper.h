// 
// TCalcConstrWrapper.h : Header File
//
// Wrapper class arround a VCalculationConstraint *
//

#ifndef SU_TCALCCONSTRWRAPPER
#define SU_TCALCCONSTRWRAPPER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//
#include <string>
using namespace std;
//

class VCalculationConstraint;
class VCalcConstrContribGenerator;
class VContribGeneratorsFactory;


// Class Definition
class	TCalcConstrWrapper{

public :
	TCalcConstrWrapper();
	TCalcConstrWrapper(VCalculationConstraint *);
	~TCalcConstrWrapper();

	bool operator	==(const TCalcConstrWrapper&) const;//compare equal
	bool operator	<(const TCalcConstrWrapper&) const;//compare equal

	string							getConstrKind();
	VCalcConstrContribGenerator*	getContribGenerator(VContribGeneratorsFactory*);



private : 

	VCalculationConstraint			*fCalcConstr;


};

#endif