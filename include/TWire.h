//
// TWire.h : header file


#ifndef SU_WIRE
#define SU_WIRE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////
// forward declariations and includes
/////
#include <list>
#include <string>
using namespace std;


#include "TWorkingPoints.h"
#include "TVSpatialPtListener.h"
#include "TVMeasurableEntityLstnr.h"

/*!\ingroup spatialobjects
	@{*/

//! Class modelising a wire stretched between two points
class TWire : public TVSpatialPtListener{

public:

	/*!@name Typedefs*/
	//@{
	//! Type of the container used for the broadcast list
	typedef list< TVMeasurableEntityLstnr* > WireListnrContainer;
	//! Type of an iterator pointing to an element of the broadcast list
	typedef WireListnrContainer::iterator WireListnrIterator;
	//! Type of an iterator pointing to an element of the broadcast list
	typedef WireListnrContainer::iterator WireListnrIterator;
	//@}


	/*!@name Constructors / Destructor*/
	//@{
	//!Constructor
	/*!@param firstEnd an iterator pointing to the wire's first end point
	@param secondEnd an iterator pointing to the wire's second end point
	@param name a name for the wire*/
	TWire(PointIterator firstEnd, PointIterator secondEnd, string name = "");
	//!Copy constructor
	TWire(const TWire& source);
	//!Destructor
	~TWire();
	//@}

	//!Sets the name of the wire
	virtual void							setName(string name);

	/*!@name Overloaded operators*/
	//@{
	//!Less than operator
	virtual bool							operator<(const TWire& right) const;
	//!Equality operator
	virtual bool							operator==(const TWire& right) const;
	//@}

	/*!@name Access methods*/
	//@{
	/*!@return an iterator to the wire's first end point*/
	virtual	PointConstIter	getFirstEnd() const;
	/*!@return an iterator to the wire's second end point*/
	virtual	PointConstIter	getSecondEnd() const;
	/*!@return the wire's name*/
	virtual string							getName() const;
	//@}

	/*!@name Active / Inactive related*/
	//@{
	//!Activates the wire
	virtual void							activate();
	//!Disactivates the wire
	virtual void							disactivate();
	//!Tells all the conerned objects that the wire is activated
	virtual void							sendActivatedToAll();
	//!Tells all the conerned objects that the wire is disactivated
	virtual void							sendDisactivatedToAll();
	/*!@return a true boolean if the wire is active*/
	virtual bool							isActive() const;
	//@}

	//!Update thw wire's equation count
	/*!@param eqCountUpdt the update to the equation count*/
	virtual void							updateEqCount(int eqCountUpdt);
	//!Adds a listener to the broadcast list
	/*! mel a pointer to the listener to be added. The pointer will be copied into the broadcast list*/
	virtual void							addListener(TVMeasurableEntityLstnr*  mel);

	
	

	//inherited from TVSpatialPtListener
	//!Reacts to the activation of one of the end points
	virtual void							pointActivated();
	//!Reacts to the disactivation of one of the end points
	virtual void							pointDisactivated();
	//!Reacts to the change of state of one of the end points (other than active/inactive)
	/*!@param um an element of the point update messages enumeration*/

	virtual void							pointUpdated(TVSpatialPtListener::EUpdateMessage um);


private:

	virtual void							updateNeededEquations();


	PointConstIter							fFirstEnd;
	PointConstIter							fSecondEnd;

	bool									fUsedInCalc;
	bool									fEndsActive;
	int										fEqCount;
	int										fNeededEquations;

	string									fName;

	WireListnrContainer						fWireListeners;
};
/*@}*/
#endif