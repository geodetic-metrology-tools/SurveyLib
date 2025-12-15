// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// TDataParameters.cpp
//
// A class defining the parameters of a data file.
//       filename, filetype, reference frame, coordinate system
//
// Patterns:
//
// 
//////////////////////////////////////////////////////////////////////



//For ROOT//////////////////////////////////////////////////////
//#include	"TROOT.h"
//
// other forward declarations
#include  "TDataParameters.h"
#include  "TAReferenceFrame.h"
#include  "TRefFrameInfo.h"
#include  "TGeodeticCoordSys.h"
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
	fCoordEpoch = NO_VALf;
	fSolution = "noSolution";
	fMatrixPath = "";
	fPointNameWidth=7;
	fObsIdWidth = 0;
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
, fCoordEpoch(original.fCoordEpoch)
, fSolution(original.fSolution)
, fMatrixPath(original.fMatrixPath)
, fPointNameWidth(original.fPointNameWidth)
, fObsIdWidth(original.fObsIdWidth)
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

void TDataParameters::swap(TDataParameters & other) noexcept
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
	std::swap(fCoordEpoch, other.fCoordEpoch);
	std::swap(fSolution, other.fSolution);
	std::swap(fMatrixPath, other.fMatrixPath);
    std::swap(fPointNameWidth,other.fPointNameWidth);
	std::swap(fObsIdWidth, other.fObsIdWidth);
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
		fPointNameWidth == rhs.fPointNameWidth &&
		fObsIdWidth == rhs.fObsIdWidth;
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

bool	TDataParameters::trfInfoExpected() const
{
	return TRefFrameInfo::isTerrestrialRefFrame(fRefFrameEnum);
}

bool TDataParameters::matrixPathExpected() const
{
	return TRefFrameInfo::isCadRefFrame(fRefFrameEnum);
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
		if(	fRefFrameEnum != TRefSystemFactory::kCGRF && fRefFrameEnum != TRefSystemFactory::kWGS84_G2139 && 
			fRefFrameEnum != TRefSystemFactory::kETRF93 && fRefFrameEnum != TRefSystemFactory::kITRF97 &&
			fRefFrameEnum != TRefSystemFactory::kITRFin && fRefFrameEnum != TRefSystemFactory::kITRFout &&
			fRefFrameEnum != TRefSystemFactory::kETRFin && fRefFrameEnum != TRefSystemFactory::kETRFout
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

	if(	fRefFrameEnum == TRefSystemFactory::kCGRF || fRefFrameEnum == TRefSystemFactory::kWGS84_G2139 || 
		fRefFrameEnum == TRefSystemFactory::kITRF97 ||
		fRefFrameEnum == TRefSystemFactory::kETRF93 || fRefFrameEnum == TRefSystemFactory::kCH1903plus ||
		fRefFrameEnum == TRefSystemFactory::kITRFin || fRefFrameEnum == TRefSystemFactory::kITRFout ||
		fRefFrameEnum == TRefSystemFactory::kETRFin || fRefFrameEnum == TRefSystemFactory::kETRFout )
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
		else if (units == kDeciDegs)
		{
			fAngleUnits = TAngle::kDeciDegs;
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
		TObservationFormat::EAnglePrecision anglePrecision;
		TPointFormat::ECoordPrecision pointPrecision;

		//Should be an integer between 0 (m) and 7 (100nm)
		switch(precision){
	
		case 0:
			observationPrecision = TObservationFormat::kMetre;
			anglePrecision = TObservationFormat::kGons;
			pointPrecision = TPointFormat::kMetre; break;
		case 1:
			observationPrecision = TObservationFormat::k100Millimetres; 
			anglePrecision = TObservationFormat::k100Milligons;
			pointPrecision = TPointFormat::k100Millimetres; break;
		case 2:
			observationPrecision = TObservationFormat::k10Millimetres; 
			anglePrecision = TObservationFormat::k10Milligons;
			pointPrecision = TPointFormat::k10Millimetres; break;
		case 3:
			observationPrecision = TObservationFormat::kMillimetre; 
			anglePrecision = TObservationFormat::kMilligons;
			pointPrecision = TPointFormat::kMillimetre; break;
		case 4:
			observationPrecision = TObservationFormat::k100Micrometres;
			anglePrecision = TObservationFormat::k100Microgons;
			pointPrecision = TPointFormat::k100Micrometres; break;
		case 5:
			observationPrecision = TObservationFormat::k10Micrometres;
			anglePrecision = TObservationFormat::k10Microgons;
			pointPrecision = TPointFormat::k10Micrometres; break;
		case 6:
			observationPrecision = TObservationFormat::kMicrometre;
			anglePrecision = TObservationFormat::kMicrogon;
			pointPrecision = TPointFormat::kMicrometre; break;
		case 7:
			observationPrecision = TObservationFormat::k100Nanometres;
			anglePrecision = TObservationFormat::k100Nanogons;
			pointPrecision = TPointFormat::k100Nanometres; break;
		case 8:
			observationPrecision = TObservationFormat::k10Nanometres;
			anglePrecision = TObservationFormat::k10Nanogons;
			pointPrecision = TPointFormat::k10Nanometres;
			break;
		case 9:
			observationPrecision = TObservationFormat::kNanometres;
			anglePrecision = TObservationFormat::kNanogons;
			pointPrecision = TPointFormat::kNanometres;
			break;
		default:
			observationPrecision = TObservationFormat::k10Micrometres;
			anglePrecision = TObservationFormat::k10Microgons;
			pointPrecision = TPointFormat::k10Micrometres; break;

		}

		setCoordPrecision(pointPrecision);
		setLengthPrecision(observationPrecision);
		if (fCoordSys != TCoordSysFactory::ECoordSys::kGeodetic && fCoordSys != TCoordSysFactory::ECoordSys::kGeodeticSphere)
			setAnglePrecision(anglePrecision);
		else
		{
			const int offset = std::min(TGeodeticCoordSys::precisionNeeded(fAngleUnits) + anglePrecision, (int) TObservationFormat::EAnglePrecision::kPicogons);
			setAnglePrecision(TObservationFormat::EAnglePrecision(offset));
		}
}

//! set point name's width precision 
void  TDataParameters::setPointNameWidth(const int width )  
{
	fPointNameWidth = width; 
	return; 
}

//! set point observation id width
void TDataParameters::setObsIdWidth(const int width)
{
	fObsIdWidth = width;
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
bool TDataParameters::setLocalSystemOrigin(std::shared_ptr <TLocalSystemOrigin> lso)
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

void TDataParameters::setCoordEpoch(const TReal epoch) {
	fCoordEpoch = epoch;
}

void TDataParameters::setSolution(const std::string solution) {
	fSolution = solution;
}

void TDataParameters::setMatrixPath(std::string matrixPath)
{
	fMatrixPath = matrixPath;
}


//////////////////////////////////////////////////////////////////////
//get Functions
//////////////////////////////////////////////////////////////////////
TAReferenceFrame*  TDataParameters::getRefFrame() const
{//! get the reference system identifier
	if (fRefFrameEnum == TRefSystemFactory::ERefFrame::kCADin || fRefFrameEnum == TRefSystemFactory::ERefFrame::kCADout)
	{
		return TRefFrameInfo::getReferenceFrame(fRefFrameEnum, fMatrixPath);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(fRefFrameEnum, fLSO, fCoordEpoch, fSolution);
	}
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
{//! get the point name width 
	return fPointNameWidth;
}

int TDataParameters::getObsIdWidth() const
{ //! get the observation id width
	return fObsIdWidth;
}


TLocalSystemOrigin* TDataParameters::getLocalSystemOrigin() const
{
	return fLSO;
}


const std::string& TDataParameters::getOriginFile() const
{
	return fOriginFile;
}

TReal TDataParameters::getCoordEpoch() const
{
	return fCoordEpoch;
}

std::string TDataParameters::getSolution() const
{
	return fSolution;
}

std::string TDataParameters::getMatrixPath() const
{
	return fMatrixPath;
}

/////////////////////////////////////////////////////////////////////////////
//end
/////////////////////////////////////////////////////////////////////////////


std::string TDataParameters::getRFName() const
{
	switch (getRefFrameEnumerator())
	{
	case TRefSystemFactory::ERefFrame::kCCS:
		return "CCS";
	case TRefSystemFactory::ERefFrame::kCGRF:
		return "CGRF";
	case TRefSystemFactory::ERefFrame::kCGRFSphere:
		return "CGRFSphere";
	case TRefSystemFactory::ERefFrame::kCGRFMercator_eh:
		return "CGRFMercator_eh";
	case TRefSystemFactory::ERefFrame::kCernX0Y0He:
		return "CERN_X0Y0He";
	case TRefSystemFactory::ERefFrame::kCernXYHe:
		return "CERN_XYHe";
	case TRefSystemFactory::ERefFrame::kCernXYHg00:
		return "CERN_XYHg_00";
	case TRefSystemFactory::ERefFrame::kCernXYHg00Machine:
		return "CERN_XYHg_RS2K";
	case TRefSystemFactory::ERefFrame::kCernXYHg00Topo:
		return "CERN_XYHg_00topo";
	case TRefSystemFactory::ERefFrame::kCernXYHg85:
		return "CERN_XYHg_85";
	case TRefSystemFactory::ERefFrame::kCernXYHg85Machine:
		return "CERN_XYHg_LHC";
	case TRefSystemFactory::ERefFrame::kCERNXYHsSphereSPS:
		return "CERN_XYHs_SPS";
	case TRefSystemFactory::ERefFrame::kCH1903plus:
		return "CH1903+";
	case TRefSystemFactory::ERefFrame::kCHTRF95:
		return "CHTRF95";
	case TRefSystemFactory::ERefFrame::kETRF93:
		return "ETRF93";
	case TRefSystemFactory::ERefFrame::kFrenchRGF93_CC46_eh:
		return "RGF93_CC46_eh";
	case TRefSystemFactory::ERefFrame::kFrenchRGF93_CC46_ign69:
		return "RGF93_CC46_ign69";
	case TRefSystemFactory::ERefFrame::kITRF97:
		return "ITRF97";
	case TRefSystemFactory::ERefFrame::kLA1985H0:
		return "LA_85";
	case TRefSystemFactory::ERefFrame::kLA1985Machine:
		return "LA_85Machine";
	case TRefSystemFactory::ERefFrame::kLA2000H0:
		return "LA_00";
	case TRefSystemFactory::ERefFrame::kLA2000Topo:
		return "LA_00Topo";
	case TRefSystemFactory::ERefFrame::kLA2000Machine:
		return "LA_00Machine";
	case TRefSystemFactory::ERefFrame::kLambert93_eh:
		return "Lambert93_eh";
	case TRefSystemFactory::ERefFrame::kLambert93_ign69:
		return "Lambert93_ign69";
	case TRefSystemFactory::ERefFrame::kLAp0:
		return "LA_P0";
	case TRefSystemFactory::ERefFrame::kLASphere:
		return "LASphere";
	case TRefSystemFactory::ERefFrame::kLGp0:
		return "LG_P0";
	case TRefSystemFactory::ERefFrame::kLGSphere:
		return "LG_Sphere";
	case TRefSystemFactory::ERefFrame::kLGGRS80:
		return "LG_GRS80";
	case TRefSystemFactory::ERefFrame::kMLA1985H0:
		return "MLA_85";
	case TRefSystemFactory::ERefFrame::kMLA1985Machine:
		return "MLA_85Machine";
	case TRefSystemFactory::ERefFrame::kMLA2000H0:
		return "MLA_00";
	case TRefSystemFactory::ERefFrame::kMLA2000Machine:
		return "MLA_00Machine";
	case TRefSystemFactory::ERefFrame::kMLA2000Topo:
		return "MLA_00Topo";
	case TRefSystemFactory::ERefFrame::kMLASphere:
		return "MLA_Sphere";
	case TRefSystemFactory::ERefFrame::kMLGGRS80:
		return "MLG_GRS80";
	case TRefSystemFactory::ERefFrame::kMLGSphere:
		return "MLG_Sphere";
	case TRefSystemFactory::ERefFrame::kRGF93:
		return "RGF93";
#ifdef USE_SWISSTOPO
	case TRefSystemFactory::ERefFrame::kSwissLV03_eh:
		return "LV03_eh";
	case TRefSystemFactory::ERefFrame::kSwissLV03_ln02:
		return "LV03_ln02";
	case TRefSystemFactory::ERefFrame::kSwissLV95_eh:
		return "LV95_eh";
	case TRefSystemFactory::ERefFrame::kSwissLV95_lhn95:
		return "LV95_lhn95";
	case TRefSystemFactory::ERefFrame::kSwissLV03_lhn95:
		return "LV03_lhn95";
	case TRefSystemFactory::ERefFrame::kSwissLV95_ln02:
		return "LV95_ln02";
#endif
	case TRefSystemFactory::ERefFrame::kWGS84_G2139:
		return "WGS84 (G2139)";
	case TRefSystemFactory::ERefFrame::kITRFin:
		return "ITRF_Input";
	case TRefSystemFactory::ERefFrame::kITRFout:
		return "ITRF_Output";
	case TRefSystemFactory::ERefFrame::kETRFin:
		return "ETRF_Input";
	case TRefSystemFactory::ERefFrame::kETRFout:
		return "ETRF_Output";
	case TRefSystemFactory::ERefFrame::kCADin:
		return "CAD_Input";
	case TRefSystemFactory::ERefFrame::kCADout:
		return "CAD_Output";
	default: return "";
	}
}








