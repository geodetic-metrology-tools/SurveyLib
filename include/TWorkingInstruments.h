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
#include "Gyroscope.h"
#include "Level.h"

#include <list>
using namespace std;

#include <unordered_map>

//!Class storing all the instruments
class TWorkingInstruments
{
public:

	TTheodolite* getTheodoliteNamed(const string& name)
	{
		std::unordered_map<string, TTheodolite*>::iterator i = theodolitesMap.find(name);
		if (i == theodolitesMap.end())
		{
			return NULL;
		}
		return i->second;
	}

	void addTheodolite(TTheodolite* theo)
	{
		theodolitesList.push_back(theo);
		theodolitesMap[theo->getInstrumentID()] = theo;
	}
	
	Scale* getScaleNamed(const string& name)
	{
		std::unordered_map<string, Scale*>::iterator i = scalesMap.find(name);
		if (i == scalesMap.end())
		{
			return NULL;
		}
		return i->second;
	}

	void addScale(Scale* scale)
	{
		scalesList.push_back(scale);
		scalesMap[scale->getInstrumentID()] = scale;
	}
	
	EDM* getEDMNamed(const string& name)
	{
		std::unordered_map<string, EDM*>::iterator i = edmsMap.find(name);
		if (i == edmsMap.end())
		{
			return NULL;
		}
		return i->second;
	}

	void addEDM(EDM* edm)
	{
		edmsList.push_back(edm);
		edmsMap[edm->getInstrumentID()] = edm;
	}
	
	Gyroscope* getGyroscopeNamed(const string& name)
	{
		std::unordered_map<string, Gyroscope*>::iterator i = gyroscopesMap.find(name);
		if (i == gyroscopesMap.end())
		{
			return NULL;
		}
		return i->second;
	}

	void addGyroscope(Gyroscope* gyro)
	{
		gyroscopesList.push_back(gyro);
		gyroscopesMap[gyro->getInstrumentID()] = gyro;
	}
	
	Level* getLevelNamed(const string& name)
	{
		std::unordered_map<string, Level*>::iterator i = levelsMap.find(name);
		if (i == levelsMap.end())
		{
			return NULL;
		}
		return i->second;
	}

	void addLevel(Level* level)
	{
		levelsList.push_back(level);
		levelsMap[level->getInstrumentID()] = level;
	}

    const list<TTheodolite*>& getTheodolitesList() const { return theodolitesList; }

    const list<Scale*>& getScalesList() const { return scalesList; }

    const list<EDM*>& getEDMsList() const { return edmsList; }

    const list<Gyroscope*>& getGyroscopesList() const { return gyroscopesList; }

    const list<Level*>& getLevelsList() const { return levelsList; }

private :

	list<TTheodolite*> theodolitesList;
	list<Scale*> scalesList;
	list<EDM*> edmsList;
	list<Gyroscope*> gyroscopesList;
	list<Level*> levelsList;

	std::unordered_map<string, TTheodolite*> theodolitesMap;
	std::unordered_map<string, Scale*> scalesMap;
	std::unordered_map<string, EDM*> edmsMap;
	std::unordered_map<string, Gyroscope*> gyroscopesMap;
	std::unordered_map<string, Level*> levelsMap;

};

#endif
