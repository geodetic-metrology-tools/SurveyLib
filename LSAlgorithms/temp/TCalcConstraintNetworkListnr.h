//
// Class for a calculation constraint network listener
// responsible for managing the constraint's relations with the other elements of the network
// i.e. constrained points

#ifndef SU_CC_NETWORK_LISTENER
#define SU_CC_NETWORK_LISTENER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#pragma warning(disable:4786)

////////////////
// include files
#include <set>
using namespace std;


/////////////////////////////////////////////////////
// Forward declarations
class TSpPointNetworkListnr;
/////////////////////////////////////////////////////


//
// Typedefs
//set of pointers to station acquisition network listeners
typedef set< TSpPointNetworkListnr*, less< TSpPointNetworkListnr* > > PTTSpPtNtLstnrSet;


// Class Definition
class	TCalcConstraintNetworkListnr{

public :

	TCalcConstraintNetworkListnr();
	~TCalcConstraintNetworkListnr();

	

	virtual void			inactivate();
	virtual void			reactivate();

	virtual void			pointDisactivated();
	virtual void			pointReactivated();


private :
	bool					fUsedInCalc;
	PTTSpPtNtLstnrSet		fConstrainedPoints;
	
};

#endif