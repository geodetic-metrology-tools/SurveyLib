#include <TRefFrameInfo.h>

#include <memory> // for std::auto_ptr
#include <stdexcept>
#include <utility> // for std::make_pair

TRefFrameInfo::TDetails::TDetails(
                                  const std::string & name, 
                                  TCoordSysFactory::ECoordSys defaultCoordSys,
                                  int allowedCoordsys,
                                  bool local)
: fName(name), fDefaultCoordSys(defaultCoordSys), fAllowedCoordSys(allowedCoordsys|defaultCoordSys), fLocal(local)
{
}

const TRefFrameInfo::MappingType & TRefFrameInfo::getMapping()
{
	typedef std::auto_ptr<MappingType> MapPtr;
	static MapPtr mapping;
	if(mapping.get()==NULL)
	{
		MapPtr tmp = MapPtr(new MappingType);
		tmp->insert(std::make_pair(TRefSystemFactory::kCCS, 
            TDetails("CCS - CERN XYZ", TCoordSysFactory::k3DCartesian)));
        tmp->insert(std::make_pair(TRefSystemFactory::kLAp0, 
            TDetails("LAp0", TCoordSysFactory::k3DCartesian)));
        tmp->insert(std::make_pair(TRefSystemFactory::kLGp0, 
            TDetails("LGp0", TCoordSysFactory::k3DCartesian)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCGRF, 
            TDetails("CERN GRF", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kITRF97, 
            TDetails("ITRF97 ep98.5", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kWGS84, 
            TDetails("WGS84", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kROMA40, 
            TDetails("ROMA40", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kETRF93,
            TDetails("ETRF93", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCH1903plus,
            TDetails("CH1903+", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		 
		 
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHe, 
            TDetails("CERN XYHe", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernX0Y0He, 
            TDetails("CERN XoYoHe (Map Transfer)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg00, 
            TDetails("CERN XYHg00", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg00Topo, 
            TDetails("CERN XYHg00Topo", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg00Machine, 
            TDetails("CERN XYHg (RS2K)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg85, 
            TDetails("CERN XYHg1985 (Surface Topo)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg85Machine, 
            TDetails("CERN XYHg1985 (LHC)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCERNXYHsSphereSPS, 
            TDetails("CERN XYHs (SPS)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCGRFSphere,
            TDetails("CERN GRF sphere", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV95,
            TDetails("Swiss LV95 (ellipsoidal height)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV03,
            TDetails("Swiss LV03 (ellipsoidal height)", TCoordSysFactory::k2DPlusH)));

        tmp->insert(std::make_pair(TRefSystemFactory::kMLA1985Machine, 
            TDetails("MLA (1985)", TCoordSysFactory::k3DCartesian, 0, true)));
        tmp->insert(std::make_pair(TRefSystemFactory::kMLA2000Machine, 
            TDetails("MLA (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
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

bool TRefFrameInfo::isCoordSysAllowed(int frame, TCoordSysFactory::ECoordSys sys)
{
    MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if(iter!=getMapping().end())
	{
		return iter->second.fAllowedCoordSys & sys;
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

TAReferenceFrame * TRefFrameInfo::getReferenceFrame(int frame, const TLocalSystemOrigin *lso)
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
