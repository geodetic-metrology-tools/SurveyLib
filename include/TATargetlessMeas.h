//
// TATargetlessMeas.h : header file
// abstract base class holding the behaviour common to all
// untargeted measurements, mainly the active/inactive management

#ifndef SU_TATargetlessMeas
#define SU_TATargetlessMeas

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//include files
#include <list>
using namespace std;

#include "TWorkingPoints.h"

#include "TVChildMeasTreeNode.h"
#include "TVParentMeasTreeNode.h"
#include "TVMeasurementListener.h"

//typedefs
typedef string Series;


// class declaration
class TATargetlessMeas : public TVChildMeasTreeNode{

public:

	//typedefs
	typedef list< TVMeasurementListener* >  MeasListnrList;
	typedef MeasListnrList::iterator MeasListnrIterator;

	//inherited from TVChildMeasTreeNode
	virtual bool		isActive() const;
	virtual int			measurementsCount() const;
	virtual int			equationsCount() const;
	virtual int			unknownsCount() const;

	virtual void		parentDisactivated();
	virtual void		parentActivated();


	virtual void	disactivate();
	virtual void	activate();
	virtual void	addListener(TVMeasurementListener* measListnr);

protected:

	TATargetlessMeas(TVParentMeasTreeNode*);
	TATargetlessMeas(const TATargetlessMeas& source);
	~TATargetlessMeas();

private:

	bool							fUsedInCalc;
	bool							fParentUsedInCalc;
	int								fActiveMeasCount;
	int								fActiveEqCount;
	int								fActiveUnkCount;

	MeasListnrList					fMeasListeners;

	TVParentMeasTreeNode*			fParent;
};
#endif