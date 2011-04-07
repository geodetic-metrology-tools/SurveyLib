#include <TCoordSysInfo.h>

#include <memory> // for std::auto_ptr
#include <utility> // for std::make_pair

const TCoordSysInfo::CoordMapType & TCoordSysInfo::getCoordSysMap()
{
	typedef std::auto_ptr<CoordMapType> MapPtr;
	static MapPtr mapping;

	if(mapping.get()==NULL)
	{
		MapPtr tmp = MapPtr(new CoordMapType);
		tmp->insert(std::make_pair(1, "k3DCartesian"));
		tmp->insert(std::make_pair(2, "kGeodetic"));
		tmp->insert(std::make_pair(4, "k2DPlusH"));
		tmp->insert(std::make_pair(8, "k2DCartesian"));
		tmp->insert(std::make_pair(16, "kGeodeticSphere"));

		mapping = tmp;
	}
	return *mapping;
}

bool TCoordSysInfo::isValidNumber (int system)
{
	CoordMapType::const_iterator it = getCoordSysMap().find(system);
	return it != getCoordSysMap().end();

}

std::string TCoordSysInfo::fromString (const std::string & systemName)
{
	CoordMapType::const_iterator it = getCoordSysMap().begin();
	while(it != getCoordSysMap().end())
	{
		if (systemName==it->second)
			return it->second;
		++it;
	}
	
	throw std::invalid_argument("Unknown Coordinate System");

}
std::string TCoordSysInfo::toString (TCoordSysFactory::ECoordSys number)
{
	CoordMapType::const_iterator it = getCoordSysMap().find(number);
	if(it != getCoordSysMap().end())
		return (it->second);

	throw std::invalid_argument("Unknown Coordinate System");

}

