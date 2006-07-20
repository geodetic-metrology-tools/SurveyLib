//
// VLSComputer.h : header file
// abstract base class for a least squares computer 
//

#include "TALSComputer.h"

//////////////////////////
// no argument constructor
//////////////////////////
TALSComputer::TALSComputer()
{
//	fS0APosterioriVariances = true;
//	fS0APrioriScaleFactor = 1;
}

/////////////
// destructor
/////////////
TALSComputer::~TALSComputer(){

}
/*
////////////////////////////////////////
// sets the sigma0 a priori scale factor
////////////////////////////////////////
void TALSComputer::setS0APrioriScaleFactor(double scalefac){

	fS0APrioriScaleFactor = scalefac;
}*/
/*
//////////////////////////////////////////////////////////////////////
// sets the variances to be calculated with respect to the s0 a priori
//////////////////////////////////////////////////////////////////////
void TALSComputer::s0APrioriVariances(){

	fS0APosterioriVariances = false;
}

//////////////////////////////////////////////////////////////////////////
// sets the variances to be calculated with respect to the s0 a posteriori
//////////////////////////////////////////////////////////////////////////
void TALSComputer::s0APosterioriVariances(){

	fS0APosterioriVariances = true;
}*/