///////////////////////////////////////////////////////////////////
// TEssaisLibrary.cpp
//////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
// other forward declarations
#include	"stdio.h"
#include	"TEssaisLibrary.h"
#include	"errmesg.h"
#include	"geo_utils.h"
#include	"vecmat.h"
#include	"vecmatdefs.h"
#include	"ptcovdefs.h"
#include	"primtvdefs.h"
#include	"libgenmat.h"
#include	"liblsapps.h"
#include	"libgeofit.h"
#include	"TEssaisLibrary.h"



/////////////////////////////////////////////////////////////////////////////
//constructor / destructor
/////////////////////////////////////////////////////////////////////////////
TEssaisLibrary::TEssaisLibrary()
{//default constructor
	unsigned long int* i = 0;
	Mmn def  = matrix(0,2 ,0 ,2, i);
	fMatrix = def;
}


TEssaisLibrary::~TEssaisLibrary()
{//destructor

}



void	TEssaisLibrary::InverseMatrix()
{
	unsigned long int* i = 0;

	fMatrix.mat[0][0] = 1;
	fMatrix.mat[0][1] = 4.39;
	fMatrix.mat[0][2] = 1;
	fMatrix.mat[1][0] = 8;
	fMatrix.mat[1][1] = 1;
	fMatrix.mat[1][2] = 5;
	fMatrix.mat[2][0] = 1;
	fMatrix.mat[2][1] = 1;
	fMatrix.mat[2][2] = 12;

	fMatrix = aasen_inv(&fMatrix, i);

	cout<<"[ ["<<fMatrix.mat[0][0]<<", "<<fMatrix.mat[0][1]<<", "<<fMatrix.mat[0][2]<<"]"<<endl;
	cout<<"["<<fMatrix.mat[1][0]<<", "<<fMatrix.mat[1][1]<<", "<<fMatrix.mat[1][2]<<"]"<<endl;
	cout<<"["<<fMatrix.mat[2][0]<<", "<<fMatrix.mat[2][1]<<", "<<fMatrix.mat[2][2]<<"] ]"<<endl;


	return;
}