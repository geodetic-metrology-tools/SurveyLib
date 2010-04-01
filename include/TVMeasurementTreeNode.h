

#ifndef SU_TVMEASTREENODE
#define SU_TVMEASTREENODE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
//
// typedefs
//
////////////////////////////////////////////////////////////////


//! Pure Abstract Base Class defining an interface for measurement tree nodes
class	TVMeasurementTreeNode{

public:	

	//!Disactivates the node
	virtual void		disactivate() = 0;
	//!Activates the node
	virtual void		activate() = 0;
	/*!@return a boolean telling if the node is active or not*/
	virtual bool		isActive() const = 0;
	/*!@return the node's number of active measurements*/
	virtual int			measurementsCount() const = 0;
	/*!@return the node's number of active equations*/
	virtual int			equationsCount() const = 0;
	/*!@return the node's number of active unknowns*/
	virtual int			unknownsCount() const = 0;
};
#endif
