// 
// TCalcConstrWrapper.cpp : implementation File
//
// Wrapper class arround a TInstrumentStation
//


#include "VCalculationConstraint.h"
#include "VCalcConstrContribGenerator.h"
#include "VContribGeneratorsFactory.h"

#include "TCalcConstrWrapper.h"


//////////////////////////
// no argument constructor
//////////////////////////
TCalcConstrWrapper::TCalcConstrWrapper(){

	fCalcConstr = NULL;
}

//////////////////////////////////////
// constructor setting the wrapped VSM
//////////////////////////////////////
TCalcConstrWrapper::TCalcConstrWrapper(VCalculationConstraint *cc){

	fCalcConstr = cc;
}


/////////////
// destructor
/////////////
TCalcConstrWrapper::~TCalcConstrWrapper(){

}


//////////////
// == operator
//////////////
bool TCalcConstrWrapper::operator==(const TCalcConstrWrapper &right) const{

	if ((*fCalcConstr) == (*(right.fCalcConstr)))
		return true;
	else
		return false;
}


/////////////
// < operator
/////////////
bool TCalcConstrWrapper::operator<(const TCalcConstrWrapper &right) const{

	if ((*fCalcConstr) < (*(right.fCalcConstr)))
		return true;
	else
		return false;
}


/////////////////////////////////
// returns the kind of constraint
/////////////////////////////////
string TCalcConstrWrapper::getConstrKind(){

	return fCalcConstr->getConstrKind();
}

//////////////////////////////////////////////
// returns the relevant contribution generator
//////////////////////////////////////////////
VCalcConstrContribGenerator* TCalcConstrWrapper::getContribGenerator(VContribGeneratorsFactory *cgf){

	return fCalcConstr->getContribGenerator(cgf);
}
