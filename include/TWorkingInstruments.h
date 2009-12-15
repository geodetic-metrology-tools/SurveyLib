// 
// TWorkingInstruments.h : Header File
//

//

#ifndef SU_WORKING_INSTRUMENT
#define SU_WORKING_INSTRUMENT

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable:4786)

#endif // _MSC_VER >= 1000

#include "TTheodolite.h"
#include "Scale.h"
#include "EDM.h"

#include <list>
using namespace std;

#include <hash_map>
using namespace stdext;

//!Class storing all the instruments
class TWorkingInstruments
{
public:

	TTheodolite* getTheodoliteNamed(const string& name) { return theodolitesMap.find(name)->second; }

	void addTheodolite(TTheodolite* theo)
	{
		theodolitesList.push_back(theo);
		theodolitesMap[theo->getInstrumentID()] = theo;
	}
	
	Scale* getScaleNamed(const string& name) { return scalesMap.find(name)->second; }

	void addScale(Scale* scale)
	{
		scalesList.push_back(scale);
		scalesMap[scale->getInstrumentID()] = scale;
	}
	
	EDM* getEDMNamed(const string& name) { return edmsMap.find(name)->second; }

	void addEDM(EDM* edm)
	{
		edmsList.push_back(edm);
		edmsMap[edm->getInstrumentID()] = edm;
	}

    const list<TTheodolite*>& getTheodolitesList() const { return theodolitesList; }

    const list<Scale*>& getScalesList() const { return scalesList; }

    const list<EDM*>& getEDMsList() const { return edmsList; }

private :

	list<TTheodolite*> theodolitesList;
	list<Scale*> scalesList;
	list<EDM*> edmsList;

	hash_map<string, TTheodolite*> theodolitesMap;
	hash_map<string, Scale*> scalesMap;
	hash_map<string, EDM*> edmsMap;

};

#endif
