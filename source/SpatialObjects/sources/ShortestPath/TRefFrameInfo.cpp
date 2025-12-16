// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <TRefFrameInfo.h>

#include <memory> // for std::auto_ptr
#include <stdexcept>
#include <utility> // for std::make_pair

TRefFrameInfo::TDetails::TDetails(
								  const std::string & refFrameName,
                                  const std::string & name, 
                                  TCoordSysFactory::ECoordSys defaultCoordSys,
                                  int allowedCoordsys,
                                  bool local)
: fRefFrameName(refFrameName)
, fName(name)
, fDefaultCoordSys(defaultCoordSys)
, fAllowedCoordSys(allowedCoordsys|defaultCoordSys)
, fLocal(local)
{
}

const TRefFrameInfo::MappingType & TRefFrameInfo::getMapping()
{
	typedef std::unique_ptr<MappingType> MapPtr;
	static MapPtr mapping;
	if(mapping.get()==NULL)
	{
		MapPtr tmp = MapPtr(new MappingType);
		tmp->insert(std::make_pair(TRefSystemFactory::kCCS, 
            TDetails("kCCS","CCS - CERN XYZ", TCoordSysFactory::k3DCartesian)));
        tmp->insert(std::make_pair(TRefSystemFactory::kLAp0, 
            TDetails("kLAp0","LAp0", TCoordSysFactory::k3DCartesian)));
        tmp->insert(std::make_pair(TRefSystemFactory::kLGp0, 
            TDetails("kLGp0","LGp0", TCoordSysFactory::k3DCartesian)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCGRF, 
            TDetails("kCGRF","CERN GRF", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kITRF97, 
            TDetails("kITRF97","ITRF97 ep98.5", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kWGS84_G2139, 
            TDetails("kWGS84_G2139","WGS84 (G2139)", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kETRF93,
            TDetails("kETRF93","ETRF93", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCH1903plus,
            TDetails("kCH1903plus","CH1903+", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kCGRF_new,
			TDetails("kCGRF2", "new CERN GRF", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kITRFin,
			TDetails("kITRFin", "Internation Terrestrial Reference Frame (ITRF input)", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kITRFout,
			TDetails("kITRFout", "Internation Terrestrial Reference Frame (ITRF output)", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kETRFin,
			TDetails("kETRFin", "European Terrestrial Reference Frame (ETRF input)", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kETRFout,
			TDetails("kETRFout", "European Terrestrial Reference Frame (ETRF output)", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHe, 
            TDetails("kCernXYHe","CERN XYHe", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernX0Y0He, 
            TDetails("kCernX0Y0He","CERN XoYoHe (Map Transfer)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg00, 
            TDetails("kCernXYHg00","CERN XYHg00", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg00Topo, 
            TDetails("kCernXYHg00Topo","CERN XYHg00Topo", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg00Machine, 
            TDetails("kCernXYHg00Machine","CERN XYHg (RS2K)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg85, 
            TDetails("kCernXYHg85","CERN XYHg1985 (Surface Topo)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCernXYHg85Machine, 
            TDetails("kCernXYHg85Machine","CERN XYHg1985 (LHC)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCERNXYHsSphereSPS, 
            TDetails("kCERNXYHsSphereSPS","CERN XYHs (SPS)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kCGRFSphere,
            TDetails("kCGRFSphere","CERN GRF sphere", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kCGRFMercator_eh,
            TDetails("kCGRFMercator_eh","CERN GRF Transverse Mercator Projection", TCoordSysFactory::k2DPlusH)));
#ifdef USE_SWISSTOPO
        tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV95_eh,
            TDetails("kSwissLV95_eh","Swiss LV95 (ellipsoidal height)", TCoordSysFactory::k2DPlusH)));
        tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV03_eh,
            TDetails("kSwissLV03_eh","Swiss LV03 (ellipsoidal height)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV03_lhn95,
			TDetails("kSwissLV03_lhn95", "Swiss LV03 (LHN95 (orthometric) height)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV95_lhn95,
			TDetails("kSwissLV95_lhn95", "Swiss LV95 (LHN95 (orthometric) height)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV03_ln02,
			TDetails("kSwissLV03_ln02", "Swiss LV03 (LN02 (leveled) height)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kSwissLV95_ln02,
			TDetails("kSwissLV95_ln02", "Swiss LV95 (LN02 (leveled) height)", TCoordSysFactory::k2DPlusH)));
#endif
        tmp->insert(std::make_pair(TRefSystemFactory::kFrenchRGF93_CC46_eh,
            TDetails("kFrenchRGF93_CC46_eh","French RGF93 CC46 (ellipsoidal height)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kFrenchRGF93_CC46_ign69,
            TDetails("kFrenchRGF93_CC46_ign69","French RGF93 CC46 (NGF-IGN69)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLambert93_eh,
			TDetails("kLambert93_eh","French Lambert93 (ellipsoidal height)", TCoordSysFactory::k2DPlusH)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLambert93_ign69,
			TDetails("kLambert93_ign69","French Lambert93 (NGF-IGN69)", TCoordSysFactory::k2DPlusH)));
		//RGF93 CHTRF95
		tmp->insert(std::make_pair(TRefSystemFactory::kRGF93,
            TDetails("kRGF93","RGF93 v2b", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		tmp->insert(std::make_pair(TRefSystemFactory::kCHTRF95,
            TDetails("kCHTRF95","CHTRF95", TCoordSysFactory::k3DCartesian, TCoordSysFactory::kGeodetic)));
		//


		tmp->insert(std::make_pair(TRefSystemFactory::kMLA1985Machine,
			TDetails("kMLA1985Machine", "MLAMachine (1985)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kMLA1985H0,
			TDetails("kMLA1985H0", "MLAH0 (1985)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kMLA2000Machine,
			TDetails("kMLA2000Machine", "MLAMachine (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kMLA2000Topo,
			TDetails("kMLA2000Topo", "MLATopo (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kMLA2000H0,
			TDetails("kMLA2000H0", "MLAH0 (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
        tmp->insert(std::make_pair(TRefSystemFactory::kMLASphere, 
            TDetails("kMLASphere","MLA (Sphere)", TCoordSysFactory::k3DCartesian, 0, true)));
        
		tmp->insert(std::make_pair(TRefSystemFactory::kLA1985Machine, 
			TDetails("kLA1985Machine", "LAMachine (1985)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLA1985H0,
			TDetails("kLA1985H0", "LAH0 (1985)", TCoordSysFactory::k3DCartesian, 0, true)));
		
		tmp->insert(std::make_pair(TRefSystemFactory::kLA2000Machine,
			TDetails("kLA2000Machine", "LAMachine (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLA2000Topo,
			TDetails("kLA2000Topo", "LATopo (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLA2000H0,
			TDetails("kLA2000H0", "LAH0 (2000)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLASphere,
			TDetails("kLASphere", "LA (Sphere)", TCoordSysFactory::k3DCartesian, 0, true)));

		
		tmp->insert(std::make_pair(TRefSystemFactory::kMLGGRS80, 
			TDetails("kMLGGRS80","MLG", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kMLGSphere, 
			TDetails("kMLGSphere","MLG (Sphere)", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLGGRS80, 
			
			TDetails("kLGGRS80","LG ", TCoordSysFactory::k3DCartesian, 0, true)));
		tmp->insert(std::make_pair(TRefSystemFactory::kLGSphere, 
			TDetails("kLGSphere","LG (Sphere)", TCoordSysFactory::k3DCartesian, 0, true)));

        tmp->insert(std::make_pair(TRefSystemFactory::kLocalRefFrame, 
            TDetails("kLocalRefFrame","LocalRefFrame (RESERVED)", TCoordSysFactory::k3DCartesian, 0, true)));

		tmp->insert(std::make_pair(TRefSystemFactory::kLocalRFin,
			TDetails("kLocalRFin", "CAD Input", TCoordSysFactory::k3DCartesian, 0, false)));

		tmp->insert(std::make_pair(TRefSystemFactory::kLocalRFout,
			TDetails("kLocalRFout", "CAD Output", TCoordSysFactory::k3DCartesian, 0, false)));
		// ...
		mapping = std::move(tmp);
	}
	return *mapping;
}

const TRefFrameInfo::RefFrameSet & TRefFrameInfo::getRefFrameSet()
{
	typedef std::unique_ptr<RefFrameSet> SetPtr;
	static SetPtr refFrameSet;
	if(refFrameSet.get()==NULL)
	{
		SetPtr tmp = SetPtr(new RefFrameSet);
		const MappingType & mapping = getMapping();
		for(MappingType::const_iterator it=mapping.begin(); it!=mapping.end(); ++it)
		{
			tmp->insert(it->first);
		}
		refFrameSet = std::move(tmp);
	}
	return *refFrameSet;
}

const TRefFrameInfo::StringMappingType & TRefFrameInfo::getStringMapping()
{
	typedef std::unique_ptr<StringMappingType> StringMapPtr;
	static StringMapPtr stringMap;
	if(stringMap.get()==NULL)
	{
		StringMapPtr tmp = StringMapPtr(new StringMappingType);
		const MappingType & mapping = getMapping();
		for(MappingType::const_iterator it=mapping.begin(); it!=mapping.end(); ++it)
		{
			tmp->insert(std::make_pair(it->second.fRefFrameName, it->first));
		}
		stringMap = std::move(tmp);
	}
	return *stringMap;
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

std::string TRefFrameInfo::getEnumString(TRefSystemFactory::ERefFrame frame)
{
	MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if(iter!=getMapping().end())
	{
		return iter->second.fRefFrameName;
	}
	throw std::invalid_argument("Unknown ERefFrame value");
}

TRefSystemFactory::ERefFrame TRefFrameInfo::fromString(const std::string & s)
{
	StringMappingType::const_iterator it = getStringMapping().find(s);
	if(it==getStringMapping().end())
		throw std::invalid_argument("String does not match any known refframe");
	return it->second;
}

std::string TRefFrameInfo::getName(int frame)
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
		return ( (iter->second.fAllowedCoordSys&sys) > 0);

   throw std::invalid_argument("Unknown ERefFrame value");
}

int TRefFrameInfo::getAllowedCoordSysCount(int frame)
{
	MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if(iter!=getMapping().end())
	{
		int v = iter->second.fAllowedCoordSys;
		// count bits in an int:
		v = v - ((v >> 1) & 0x55555555);                    // reuse input as temporary
		v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     // temp
		return ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
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

bool TRefFrameInfo::isRotatedLocalRefFrame(int frame) {
    MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
    if(iter!=getMapping().end())
	{
		// if the name starts with ML, it is a local modiefeid (i.e. rotated) frame
		return (iter->second.fRefFrameName.find("kML") == 0);
	}
	throw std::invalid_argument("Unknown ERefFrame value");}

bool TRefFrameInfo::isTerrestrialRefFrame(int frame) {
	MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if (iter != getMapping().end())
	{
		return ((iter->second.fRefFrameName.find("kITRFin") != std::string::npos) ||
			(iter->second.fRefFrameName.find("kITRFout") != std::string::npos) ||
			(iter->second.fRefFrameName.find("kETRFin") != std::string::npos) ||
			(iter->second.fRefFrameName.find("kETRFout") != std::string::npos));
	}
	throw std::invalid_argument("Unknown ERefFrame value");
}

bool TRefFrameInfo::isLocalRFWithMatrix(int frame)
{
	MappingType::const_iterator iter = getMapping().find(static_cast<TRefSystemFactory::ERefFrame>(frame));
	if (iter != getMapping().end())
	{
		return (iter->second.fRefFrameName.find("kLocalRFin") != std::string::npos ||
			iter->second.fRefFrameName.find("kLocalRFout") != std::string::npos);
	}
	throw std::invalid_argument("Unknown ERefFrame value");
}

TAReferenceFrame * TRefFrameInfo::getReferenceFrame(int frame, const TLocalSystemOrigin *lso, TReal epoch, std::string solution)
{
	bool isdefinedlocal = false;
	TRefSystemFactory::EGeoid localgeoid = TRefSystemFactory::kNoGeoid;
    TRefSystemFactory::ERefFrame refFrame = fromNumber(frame);

	if (refFrame >= TRefSystemFactory::kMLA1985Machine && 
		refFrame <= TRefSystemFactory::kLGSphere) isdefinedlocal = true;

	if (refFrame == TRefSystemFactory::kITRFin ||
		refFrame == TRefSystemFactory::kITRFout ||
		refFrame == TRefSystemFactory::kETRFin ||
		refFrame == TRefSystemFactory::kETRFout)
	{
		TRefSystemFactory::getRefSystemFactory()->updateTerrestrialRefFrame(epoch, solution, refFrame);
	}

	if (isdefinedlocal && lso == NULL) 
		throw std::invalid_argument("LocalSystemOrigin required for the local reference frames!");
	else if (!isdefinedlocal && lso != NULL)
		throw std::invalid_argument("LocalSystemOrigin parameter is not needed for the non-*LA reference frames!");

	// determine the geoid of the predefined local frame
	switch (frame)
	{
		case TRefSystemFactory::kMLA1985Machine:
		case TRefSystemFactory::kLA1985Machine:
			localgeoid = TRefSystemFactory::kCG1985Machine;
			break;
		case TRefSystemFactory::kMLA1985H0:
		case TRefSystemFactory::kLA1985H0:
			localgeoid = TRefSystemFactory::kCG1985;
			break;
		case TRefSystemFactory::kMLA2000Machine:
		case TRefSystemFactory::kLA2000Machine:
			localgeoid = TRefSystemFactory::kCG2000Machine;
			break;
		case TRefSystemFactory::kMLA2000Topo:
		case TRefSystemFactory::kLA2000Topo:
			localgeoid = TRefSystemFactory::kCG2000topo;
			break;
		case TRefSystemFactory::kMLA2000H0:
		case TRefSystemFactory::kLA2000H0:
			localgeoid = TRefSystemFactory::kCG2000;
			break;
		case TRefSystemFactory::kMLASphere:
		case TRefSystemFactory::kMLGSphere:
		case TRefSystemFactory::kLASphere:
		case TRefSystemFactory::kLGSphere:
			localgeoid = TRefSystemFactory::kCGSphere;
			break;
	}


	// return an appropriate instance
	if (isdefinedlocal)
		return TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame(*lso, localgeoid, refFrame);
	else if(refFrame==TRefSystemFactory::kLocalRefFrame)
        return TRefSystemFactory::getRefSystemFactory()->getNewLocalRefFrame();
	else
		return TRefSystemFactory::getRefSystemFactory()->getRefFrame(refFrame);
}

TAReferenceFrame *TRefFrameInfo::getReferenceFrame(int frame, const std::string &pathToTransformationMatrix)
{
	if (frame != TRefSystemFactory::kLocalRFin && frame != TRefSystemFactory::kLocalRFout)
	{
		throw std::invalid_argument("This method is only valid for CAD reference frame!");
	}
	return TRefSystemFactory::getRefSystemFactory()->updatePathTotransformationMatrix(pathToTransformationMatrix, fromNumber(frame));
}
