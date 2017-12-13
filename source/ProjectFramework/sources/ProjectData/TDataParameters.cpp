// TDataParameters.cpp
//
// A class defining the parameters of a data file.
//       filename, filetype, reference frame, coordinate system
//
// Patterns:
//
// 
// Copyright 2000 CERN EST/SU. All rights reserved.
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TDataParameters.h"
#include  "TAReferenceFrame.h"
#include  "TRefFrameInfo.h"
#include  "TGeodeticRefFrame.h"
#include  "TModifiedLocalAstronomicalRF.h"
#include  "T3DLocalRefFrame.h"

////////////////////////////////////////////////////////////////


//ClassImp(TDataParameters)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TDataParameters::TDataParameters()
{// default constructor
	fRefFrame = nullptr;
	fLSO = nullptr;
	fOriginFile = "";
    fRefFrameEnum = TRefSystemFactory::kNotInGraph;
	fCoordUnit = TDataParameters::kNotDefined;
	fCoordSys = TCoordSysFactory::k3DCartesian;
	fAngleUnits =TAngle::kGons;
	fLengthUnits =TLength::kMetres ;
	fAnglePrecision = TObservationFormat::k10Microgons;
	fLengthPrecision = TObservationFormat::k10Micrometres;
	fCoordPrecision = TPointFormat::kMillimetre;
	fPointNameWidth=7;
}

TDataParameters::TDataParameters(const TDataParameters& original )
: fRefFrame(original.fRefFrame)
, fRefFrameEnum(original.fRefFrameEnum)
, fCoordUnit(original.fCoordUnit)
, fLSO(original.fLSO? new TLocalSystemOrigin( *original.fLSO) : 0)
, fOriginFile(original.fOriginFile)
, fCoordSys(original.fCoordSys)
, fAngleUnits(original.fAngleUnits)
, fLengthUnits(original.fLengthUnits)
, fAnglePrecision(original.fAnglePrecision)
, fLengthPrecision(original.fLengthPrecision)
, fCoordPrecision(original.fCoordPrecision)
, fPointNameWidth(original.fPointNameWidth)
{
}


TDataParameters::~TDataParameters()
{
}


//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
TDataParameters&  TDataParameters::operator=(TDataParameters rhs )
{
    // rhs is a copy of the source; hard work already done
    swap(rhs); // trade our resources for rhs'es
    return *this;    // our (old) resources get destroyed with rhs (copy)
}

void TDataParameters::swap(TDataParameters & other) throw()
{
    std::swap(fRefFrame,other.fRefFrame);
    std::swap(fRefFrameEnum,other.fRefFrameEnum);
    std::swap(fCoordUnit,other.fCoordUnit);
	std::swap(fLSO, other.fLSO);
	std::swap(fOriginFile, other.fOriginFile);
    std::swap(fCoordSys,other.fCoordSys);
    std::swap(fAngleUnits,other.fAngleUnits);
    std::swap(fLengthUnits,other.fLengthUnits);
    std::swap(fAnglePrecision,other.fAnglePrecision);
    std::swap(fLengthPrecision,other.fLengthPrecision);
    std::swap(fCoordPrecision,other.fCoordPrecision);
    std::swap(fPointNameWidth,other.fPointNameWidth);
}

bool  TDataParameters::operator==(const TDataParameters& rhs )
{//Equivalence operator
	return	fRefFrameEnum == rhs.getRefFrameEnumerator() && 
		fCoordUnit == rhs.fCoordUnit &&
        fLSO == rhs.fLSO &&
		fCoordSys == rhs.getCoordinateSystem() &&
		fAngleUnits == rhs.getAngleUnits() && 
		fLengthUnits == rhs.getLengthUnits() && 
		fAnglePrecision == rhs.getAnglePrecision() && 
		fLengthPrecision == rhs.getLengthPrecision() && 
		fCoordPrecision == rhs.getCoordPrecision() &&
		fPointNameWidth==rhs.fPointNameWidth;
}


bool  TDataParameters::defined()  const  
{ 
	// returns "true" if the parameters are defined

	bool retVal = true;

    if(fRefFrameEnum == TRefSystemFactory::kNotInGraph || fCoordUnit == kNotDefined)
	{
		retVal = false;
	}

	return retVal; 
}


bool	TDataParameters::isOriginExpected() const
{
	return TRefFrameInfo::isLocalRefFrame(fRefFrameEnum);
}



////////////////////////////////////////////////////////////////////////
//function set
////////////////////////////////////////////////////////////////////////

bool  TDataParameters::setRefFrame(TRefSystemFactory::ERefFrame rf)
{//! set the reference system identifier
	// returns "true" if the parameters are set correctly
	bool retVal = true;
	
    if( rf != TRefSystemFactory::kNotInGraph && fRefFrame == 0)
	{
		fRefFrameEnum = rf;
		
		//LSO is reset only for reference frame don't using it.
		if (fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLA2000H0 &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLA2000Machine &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLA2000Topo &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLA1985H0 &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLA1985Machine &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLASphere &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLA1985H0 &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLA1985Machine &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLA2000H0 &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLA2000Machine &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLA2000Topo &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLASphere &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLGGRS80 &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kMLGSphere &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLGGRS80 &&
			fRefFrameEnum != TRefSystemFactory::ERefFrame::kLGSphere)
		{
			fLSO = nullptr;
			fOriginFile = "";
		}
		
		//set unit to [m] for non geodetic reference frame
		if(	fRefFrameEnum != TRefSystemFactory::kCGRF && fRefFrameEnum != TRefSystemFactory::kWGS84 && 
			fRefFrameEnum != TRefSystemFactory::kROMA40 && fRefFrameEnum != TRefSystemFactory::kITRF97 &&
			fRefFrameEnum != TRefSystemFactory::kETRF93
			&& fRefFrameEnum != TRefSystemFactory::kCGRFSphere
			&& fRefFrameEnum != TRefSystemFactory::kCH1903plus
			&& fRefFrameEnum != TRefSystemFactory::kCHTRF95
			&& fRefFrameEnum != TRefSystemFactory::kRGF93)
		{//set automatically metric
			setUnits(TDataParameters::kMetric );
		}
	}
	else
	{
		retVal = false;
	}

	return retVal;
}

	
bool TDataParameters::setCoordSys(const TCoordSysFactory::ECoordSys& idNum)
{//!set the coordinate system
	bool retVal = true;

	if( idNum != TCoordSysFactory::k2DCartesian )
	{
		fCoordSys = idNum;
	}
	else
	{
		retVal = false;
	}

	return retVal;
}


bool  TDataParameters::setUnits( const TDataParameters::ECoordUnit& units )
{//! set the coordinate units
	// returns "true" if the parameters are set correctly
	bool  retVal = true;
	
	fCoordUnit= units;

	if(	fRefFrameEnum == TRefSystemFactory::kCGRF || fRefFrameEnum == TRefSystemFactory::kWGS84 || 
		fRefFrameEnum == TRefSystemFactory::kROMA40 || fRefFrameEnum == TRefSystemFactory::kITRF97 ||
		fRefFrameEnum == TRefSystemFactory::kETRF93 || fRefFrameEnum == TRefSystemFactory::kCH1903plus)
	{
		if ( units == kDMS )
		{
			fAngleUnits = TAngle::kDMS;  
			setCoordSys(TCoordSysFactory::kGeodetic);
		}
		else if (units == kGons )
		{
			fAngleUnits = TAngle::kGons;  
			setCoordSys(TCoordSysFactory::kGeodetic);
		}
		else if (units == kMetric )
		{
			fAngleUnits = TAngle::kGons;  
			//setCoordSys(TCoordSysFactory::kGeodetic);
		}
		else
		{
			retVal = false;
		}
	}
	else
	{//only metric system with this referance frame
		if (units == kMetric )
		{
			fAngleUnits = TAngle::kGons;  
		}
		else
		{
			fCoordUnit = kNotDefined;
			retVal = false;
		}
	}
	return  retVal;
}


bool  TDataParameters::setAngUnits( const TAngle::EUnits& un)
{//! set the angle units
	fAngleUnits = un;  
    return true;
	
}


bool  TDataParameters::setLenUnits( const TLength::EUnits& un)
{//! set the length units
	// returns "true" if the parameters are set correctly
	bool  retVal = true;

	if ( un > 0  &&  un < 3 )
	{
		fLengthUnits = un;  
	}
	else
	{
		retVal = false;
	}

	return  retVal;
}

//! set the coordinate precision 
void  TDataParameters::setCoordPrecision( const TPointFormat::ECoordPrecision precision )  
{
	fCoordPrecision = precision; 
	return; 
}

//! set angle precision 
void  TDataParameters::setAnglePrecision(const TObservationFormat::EAnglePrecision precision )  
{
	fAnglePrecision = precision; 
	return; 
}

//! set length precision 
void  TDataParameters::setLengthPrecision(const TObservationFormat::ELengthPrecision precision )  
{
	fLengthPrecision = precision; 
	return; 
}

void TDataParameters::setPrecision(int precision)
{

		TObservationFormat::ELengthPrecision observationPrecision;
		TPointFormat::ECoordPrecision pointPrecision;

		//Should be an integer between 0 (m) and 7 (100nm)
		switch(precision){
	
		case 0:
			observationPrecision = TObservationFormat::kMetre;
			setAnglePrecision(TObservationFormat::kGons);
			pointPrecision = TPointFormat::kMetre; break;
		case 1:
			observationPrecision = TObservationFormat::k100Millimetres; 
			setAnglePrecision(TObservationFormat::k100Milligons);
			pointPrecision = TPointFormat::k100Millimetres; break;
		case 2:
			observationPrecision = TObservationFormat::k10Millimetres; 
			setAnglePrecision(TObservationFormat::k10Milligons);
			pointPrecision = TPointFormat::k10Millimetres; break;
		case 3:
			observationPrecision = TObservationFormat::kMillimetre; 
			setAnglePrecision(TObservationFormat::kMilligons);
			pointPrecision = TPointFormat::kMillimetre; break;
		case 4:
			observationPrecision = TObservationFormat::k100Micrometres;
			setAnglePrecision(TObservationFormat::k100Microgons);
			pointPrecision = TPointFormat::k100Micrometres; break;
		case 5:
			observationPrecision = TObservationFormat::k10Micrometres;
			setAnglePrecision(TObservationFormat::k10Microgons);
			pointPrecision = TPointFormat::k10Micrometres; break;
		case 6:
			observationPrecision = TObservationFormat::kMicrometre;
			setAnglePrecision(TObservationFormat::kMicrogon);
			pointPrecision = TPointFormat::kMicrometre; break;
		case 7:
			observationPrecision = TObservationFormat::k100Nanometres;
			setAnglePrecision(TObservationFormat::k100Nanogons);
			pointPrecision = TPointFormat::k100Nanometres; break;
		default:
			observationPrecision = TObservationFormat::k10Micrometres;
			setAnglePrecision(TObservationFormat::k10Microgons);
			pointPrecision = TPointFormat::k10Micrometres; break;

		}

		setCoordPrecision(pointPrecision); 
		setLengthPrecision(observationPrecision);
		//setAnglePrecision(TObservationFormat::k10Microgons);
}

//! set point name's width precision 
void  TDataParameters::setPointNameWidth(const int width )  
{
	fPointNameWidth = width; 
	return; 
}


bool TDataParameters::setLocalSystemOrigin(const TLocalSystemOrigin & LSO)
{
    if(TRefFrameInfo::isLocalRefFrame(fRefFrameEnum)
		&& fRefFrame == 0)
	{
		//fLSO = LSO;
        fLSO = new TLocalSystemOrigin(LSO);
		return true;
	}
	return false;
}
bool TDataParameters::setLocalSystemOrigin(std::shared_ptr<TLocalSystemOrigin> lso)
{
    if(TRefFrameInfo::isLocalRefFrame(fRefFrameEnum)
		&& fRefFrame == 0)
	{
        fLSO = lso.get();
        return true;
    }
    return false;
}

void TDataParameters::setOriginFile(const std::string &f)
{
	fOriginFile = f;
}


//////////////////////////////////////////////////////////////////////
//get Functions
//////////////////////////////////////////////////////////////////////
TAReferenceFrame*  TDataParameters::getRefFrame() const
{//! get the reference system identifier
    return TRefFrameInfo::getReferenceFrame(fRefFrameEnum, fLSO);;
}


TRefSystemFactory::ERefFrame TDataParameters::getRefFrameEnumerator() const 
{//! get the reference system identifier
	return fRefFrameEnum;
}

TCoordSysFactory::ECoordSys  TDataParameters::getCoordinateSystem()  const
{//! get the coordinate system for the RefSystem data
	return fCoordSys;
}
		

TAngle::EUnits  TDataParameters::getAngleUnits() const
{//! get the angle units
	return fAngleUnits;
}
	

TLength::EUnits  TDataParameters::getLengthUnits() const
{//! get the length units
	return fLengthUnits;
}
	

TObservationFormat::EAnglePrecision  TDataParameters::getAnglePrecision() const
{//! get the angle precision
	return fAnglePrecision;
}

 
TObservationFormat::ELengthPrecision  TDataParameters::getLengthPrecision() const
{//! get the length precision
	return fLengthPrecision;
}



TPointFormat::ECoordPrecision  TDataParameters::getCoordPrecision() const
{//! get the coord precision 
	return fCoordPrecision;
}



int  TDataParameters::getPointNameWidth() const
{//! get the coord precision 
	return fPointNameWidth;
}


TLocalSystemOrigin* TDataParameters::getLocalSystemOrigin() const
{
	return fLSO;
}


const string& TDataParameters::getOriginFile() const
{
	return fOriginFile;
}

/////////////////////////////////////////////////////////////////////////////
//end
/////////////////////////////////////////////////////////////////////////////


string TDataParameters::getRFName() const
{
	switch (getRefFrameEnumerator())
	{
	case TRefSystemFactory::ERefFrame::kCCS:
		return string("CCS");
	case TRefSystemFactory::ERefFrame::kCGRF:
		return string("CGRF");
	case TRefSystemFactory::ERefFrame::kCGRFSphere:
		return string("CGRFSphere");
	case TRefSystemFactory::ERefFrame::kCernX0Y0He:
		return string("CERN_X0Y0He");
	case TRefSystemFactory::ERefFrame::kCernXYHe:
		return string("CERN_XYHe");
	case TRefSystemFactory::ERefFrame::kCernXYHg00:
		return string("CERN_XYHg_00");
	case TRefSystemFactory::ERefFrame::kCernXYHg00Machine:
		return string("CERN_XYHg_RS2K");
	case TRefSystemFactory::ERefFrame::kCernXYHg00Topo:
		return string("CERN_XYHg_00topo");
	case TRefSystemFactory::ERefFrame::kCernXYHg85:
		return string("CERN_XYHg_85");
	case TRefSystemFactory::ERefFrame::kCernXYHg85Machine:
		return string("CERN_XYHg_LHC");
	case TRefSystemFactory::ERefFrame::kCERNXYHsSphereSPS:
		return string("CERN_XYHs_SPS");
	case TRefSystemFactory::ERefFrame::kCH1903plus:
		return string("CH1903+");
	case TRefSystemFactory::ERefFrame::kCHTRF95:
		return string("CHTRF95");
	case TRefSystemFactory::ERefFrame::kETRF93:
		return string("ETRF93");
	case TRefSystemFactory::ERefFrame::kFrenchRGF93Zone5:
		return string("RGF93zone5");
	case TRefSystemFactory::ERefFrame::kITRF97:
		return string("ITRF97");
	case TRefSystemFactory::ERefFrame::kLA1985H0:
		return string("LA_85");
	case TRefSystemFactory::ERefFrame::kLA1985Machine:
		return string("LA_85Machine");
	case TRefSystemFactory::ERefFrame::kLA2000H0:
		return string("LA_00");
	case TRefSystemFactory::ERefFrame::kLA2000Topo:
		return string("LA_00Topo");
	case TRefSystemFactory::ERefFrame::kLA2000Machine:
		return string("LA_00Machine");
	case TRefSystemFactory::ERefFrame::kLambert93:
		return string("Lambert93");
		break;
	case TRefSystemFactory::ERefFrame::kLAp0:
		return string("LA_P0");
	case TRefSystemFactory::ERefFrame::kLASphere:
		return string("LASphere");
	case TRefSystemFactory::ERefFrame::kLGp0:
		return string("LG_P0");
	case TRefSystemFactory::ERefFrame::kLGSphere:
		return string("LG_Sphere");
	case TRefSystemFactory::ERefFrame::kLGGRS80:
		return string("LG_GRS80");
	case TRefSystemFactory::ERefFrame::kMLA1985H0:
		return string("MLA_85");
	case TRefSystemFactory::ERefFrame::kMLA1985Machine:
		return string("MLA_85Machine");
	case TRefSystemFactory::ERefFrame::kMLA2000H0:
		return string("MLA_00");
	case TRefSystemFactory::ERefFrame::kMLA2000Machine:
		return string("MLA_00Machine");
	case TRefSystemFactory::ERefFrame::kMLA2000Topo:
		return string("MLA_00Topo");
	case TRefSystemFactory::ERefFrame::kMLASphere:
		return string("MLA_Sphere");
	case TRefSystemFactory::ERefFrame::kMLGGRS80:
		return string("MLG_GRS80");
	case TRefSystemFactory::ERefFrame::kMLGSphere:
		return string("MLG_Sphere");
	case TRefSystemFactory::ERefFrame::kRGF93:
		return string("RGF93");
	case TRefSystemFactory::ERefFrame::kROMA40:
		return string("ROMA40");
#ifdef USE_SWISSTOPO
	case TRefSystemFactory::ERefFrame::kSwissLV03:
		return string("LV03");
	case TRefSystemFactory::ERefFrame::kSwissLV95:
		return string("LV95");
#endif
	case TRefSystemFactory::ERefFrame::kWGS84:
		return string("WGS84");
	default: return "";
	}
}








