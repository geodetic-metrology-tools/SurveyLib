#include <TRefFrameInfo.h>

#include <memory> // for std::auto_ptr
#include <stdexcept>
#include <utility> // for std::make_pair

TRefFrameInfo::TDetails::TDetails(
                                  const std::string & name, 
                                  TCoordSysFactory::ECoordSys coordSys,
                                  bool local)
: fName(name), fDefaultCoordSys(coordSys), fLocal(local)
{
}

const TRefFrameInfo::MappingType & TRefFrameInfo::getMapping()
{
	typedef std::auto_ptr<MappingType> MapPtr;
	static MapPtr mapping;
	if(mapping.get()==NULL)
	{
		MapPtr tmp = MapPtr(new MappingType);
		tmp->insert(std::make_pair(TRefSystemFactory::kCCS, TDetails("CCS", TCoordSysFactory::k3DCartesian)));
		tmp->insert(std::make_pair(TRefSystemFactory::kETRF93, TDetails("ETRF93", TCoordSysFactory::k3DCartesian)));
		tmp->insert(std::make_pair(TRefSystemFactory::kITRF97, TDetails("ITRF97", TCoordSysFactory::k3DCartesian)));
		tmp->insert(std::make_pair(TRefSystemFactory::kROMA40, TDetails("ROMA40", TCoordSysFactory::k3DCartesian)));
		tmp->insert(std::make_pair(TRefSystemFactory::kWGS84, TDetails("WGS84", TCoordSysFactory::k3DCartesian)));

        tmp->insert(std::make_pair(TRefSystemFactory::kCERNXYHsSphereSPS, TDetails("CERNXYHsSphereSPS", TCoordSysFactory::k2DPlusH)));

        tmp->insert(std::make_pair(TRefSystemFactory::kMLA1985Machine, TDetails("MLA1985Machine", TCoordSysFactory::k3DCartesian, true)));
        tmp->insert(std::make_pair(TRefSystemFactory::kMLA2000Machine, TDetails("MLA2000Machine", TCoordSysFactory::k3DCartesian, true)));
		// ...
		mapping = tmp;
	}
	return *mapping;
}

const TRefFrameInfo::RefFrameSet & TRefFrameInfo::getRefFrameSet()
{
	typedef std::auto_ptr<RefFrameSet> SetPtr;
	static SetPtr refFrameSet;
	if(refFrameSet.get()==NULL)
	{
		SetPtr tmp = SetPtr(new RefFrameSet);
		const MappingType & mapping = getMapping();
		for(MappingType::const_iterator it=mapping.begin(); it!=mapping.end(); ++it)
		{
			tmp->insert(it->first);
		}
		refFrameSet = tmp;
	}
	return *refFrameSet;
}

bool TRefFrameInfo::isValidNumber(int frame)
{
	MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	return iter!=getMapping().end();
}

TRefSystemFactory::ERefFrame TRefFrameInfo::fromNumber(int frame)
{
	if(isValidNumber(frame))
		return static_cast<TRefSystemFactory::ERefFrame>(frame);
	else
		throw std::invalid_argument("Unknown ERefFrame value");
}

const std::string & TRefFrameInfo::getName(int frame)
{
	MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if(iter!=getMapping().end())
	{
		return iter->second.fName;
	}
	throw std::invalid_argument("Unknown ERefFrame value");
}

TCoordSysFactory::ECoordSys TRefFrameInfo::getDefaultCoordSys(int frame)
{
    MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if(iter!=getMapping().end())
	{
		return iter->second.fDefaultCoordSys;
	}
	throw std::invalid_argument("Unknown ERefFrame value");
}

bool TRefFrameInfo::isLocalRefFrame(int frame)
{
    MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
    if(iter!=getMapping().end())
	{
		return iter->second.fLocal;
	}
	throw std::invalid_argument("Unknown ERefFrame value");
}

TAReferenceFrame * TRefFrameInfo::getReferenceFrame(int frame, const LocalSystemOrigin *lso)
{
    TRefSystemFactory::ERefFrame refFrame = fromNumber(frame);
    if(refFrame==TRefSystemFactory::kMLA1985Machine || refFrame==TRefSystemFactory::kMLA2000Machine)
    {
        if(lso == NULL)
            throw std::invalid_argument("LocalSystemOrigin required for the MLA reference frames!");
        if(refFrame==TRefSystemFactory::kMLA1985Machine)
            return TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(*lso, TRefSystemFactory::kCG1985Machine);
        if(refFrame==TRefSystemFactory::kMLA2000Machine)
            return TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(*lso, TRefSystemFactory::kCG2000Machine);
    }
    else
    {
        if(lso != NULL)
            throw std::invalid_argument("LocalSystemOrigin parameter is not needed for the non-MLA reference frames!");
        return TRefSystemFactory::getRefSystemFactory()->getRefFrame(refFrame);
    }
    throw std::invalid_argument("Could not get the TAReferenceFrame for the given input");
}
