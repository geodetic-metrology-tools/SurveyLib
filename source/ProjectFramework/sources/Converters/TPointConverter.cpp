// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿////////////////////////////////////////////////////////////////////
// TPointConverter.cpp
/*!
Write a output LGC file
Creates a file from the data read and sends the appropriate messages

Patterns:

 
*/
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
// other forward declarations
#include	"TPointConverter.h"
#include	"TPointFormat.h"
#include	"TAStreamFormatter.h"


/////////////////////////////////////////////////////////////////////

//ClassImp(TPointConverter)


//////////////////////////////////////////////////////////////////////
// Definitions and Initialisations
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//constructor / destructor
/////////////////////////////////////////////////////////////////////////////

TPointConverter::TPointConverter(TAStreamFormatter* stream,
								 const TRefSystemFactory::ERefFrame	refFrame):
TAConverter(stream)
{//constructor

	fRefFrame = refFrame;

	TAReferenceFrame* pointRefFrame = stream->getReferenceFrame();
	TAReferenceFrame* ccsRefFrame = (TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCCS));
	if(pointRefFrame == ccsRefFrame)
		fLocalSys = false;
	else
		fLocalSys = true;
}


TPointConverter::~TPointConverter()
{//destructor
}


TPointConverter& 	TPointConverter::operator=(const TPointConverter& source)
{//! copy assignment operator
	this->TAConverter::operator =(source);
	fLocalSys = source.fLocalSys;
	fRefFrame = source.fRefFrame;
	return *this;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEMBER PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////
//Name
//////////////////////////////////////////////////////////////////////////////////
void	TPointConverter::writeName(std::string ptName, int width)
{
	TAStreamFormatter*	stream = getStream();

	//Write point name
	stream->width(width);
	(*stream)<<left<<(ptName)<<right << this->getSeparator();
	return;
}



////////////////////////////////////////////////////////////////////////////////////////////////
//X Y Z and H
////////////////////////////////////////////////////////////////////////////////////////////////

//Write position vector in any 
void	TPointConverter::writeXYZandH(const TPositionVector& pt)
{
	TAStreamFormatter*	stream = getStream();
	std::string				separator = getSeparator();

	//get Coordinate as a TPositionVector
	(*stream) << (pt);

	if (pt.getCoordSys() == TCoordSysFactory::k2DPlusH)
		(*stream) << separator << pt.getH();
	else
		stream->writeString(getCoordWidth(), "");

	return;
}


void	TPointConverter::writeXYZandH(const TPositionVector& pt, TLength heightH)
{
	TAStreamFormatter*	stream = getStream();
	int					coordWidth = getCoordWidth();
	std::string				separator = getSeparator();

	stream->setLengthUnits(TLength::EUnits::kMetres);
	stream->setWidthFormat(coordWidth);
	stream->setPrecisionFormat(getLengthPrecision());

	//get Coordinate as a TPositionVector
	//(*stream)<<(pt);
	this->writeXYZ(coordWidth, getLengthPrecision(), TLength::EUnits::kMetres, separator, pt);
	(*stream)<<heightH << separator;

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//X Y H
////////////////////////////////////////////////////////////////////////////////////////////////

void	TPointConverter::writeXYH(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const std::string separator,
                           const TLength Xparam,
						   const TLength Yparam,
						   const TLength Hparam)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	(*stream)<< Xparam << separator;

	//write Y
	(*stream)<< Yparam << separator;

	//write H if point's refrence frame is CCS
	if(!isInLocalSystem())
		(*stream)<< Hparam; 
	else
		writeString(width, " ");
	
	(*stream) << separator; 
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//X Y Z 
////////////////////////////////////////////////////////////////////////////////////////////////

void	TPointConverter::writeXYZ(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const std::string separator,
									const TPositionVector pt)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	(*stream)<<pt.getX()<<separator;

	//write Y
	(*stream)<<pt.getY()<<separator;

	//write Z
	(*stream)<<pt.getZ() << separator;
	return;
}


void	TPointConverter::write3Coordinates(	const int width,
											const int precision,
											const std::string separator,
											const TPositionVector pt)
{
	TAStreamFormatter*	stream = getStream();

	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	(*stream)<<pt.getX()<<separator;

	//write Y
	(*stream)<<pt.getY()<<separator;

	//write Z
	if(pt.getCoordSys() == TCoordSysFactory::k3DCartesian)
		(*stream)<<pt.getZ() << separator;
	
	if(pt.getCoordSys() == TCoordSysFactory::k2DPlusH)
		(*stream)<<pt.getH()<< separator;

	return;
}



void	TPointConverter::writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
												const int width,
												const int precision,
												const std::string separator,
												TReal Xparam,
												TReal Yparam,
												TReal Zparam,
												const std::string Dparam,
												bool isCovar)
{
	TAStreamFormatter*	stream = getStream();

	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);
	
	//write X
	if((isCovar &&  (status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy))  || 
		!isCovar && (status == TSpatialStatus::kVx || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVxz))
		(*stream)<<(Xparam);	
	else
		writeString(width, Dparam);

	(*stream)<<(separator);


	//write Y
	if((isCovar &&  (status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxz))  || 
		!isCovar && (status == TSpatialStatus::kVy || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVyz))
		(*stream)<<(Yparam);
	else
		writeString(width, Dparam);

	(*stream)<<(separator);


	//write Z
	if((isCovar &&  (status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVyz))  || 
		!isCovar && (status == TSpatialStatus::kVz || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxz  || status == TSpatialStatus::kVyz))
		(*stream)<<(Zparam);
	else
		writeString(width, Dparam);

	(*stream)<<(separator);

	return;
}


void	TPointConverter::writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
												const int width,
												const int precision,
												const TLength::EUnits unit,
												const std::string separator,
												const TLength Xparam,
												const TLength Yparam,
												const TLength Zparam,
												const std::string Dparam,
												bool isCovar)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);
	
	//write X
	if((isCovar &&  (status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy))  || 
		!isCovar && (status == TSpatialStatus::kVx || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVxz))
		(*stream)<<(Xparam);	
	else
		writeString(width, Dparam);

	(*stream)<<(separator);


	//write Y
	if((isCovar &&  (status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxz))  || 
		!isCovar && (status == TSpatialStatus::kVy || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVyz))
		(*stream)<<(Yparam);
	else
		writeString(width, Dparam);

	(*stream)<<(separator);


	//write Z
	if((isCovar &&  (status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVyz))  || 
		!isCovar && (status == TSpatialStatus::kVz || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxz  || status == TSpatialStatus::kVyz))
		(*stream)<<(Zparam);
	else
		writeString(width, Dparam);

	(*stream)<<(separator);

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//N
////////////////////////////////////////////////////////////////////////////////////////////////


/*void	TPointConverter::writeN( const int width,
								 const int precision,
								 const TLength::EUnits unit,
								 TAdjustablePoint pt)
{
	TRefSystemFactory::EGeoid geoid(TRefSystemFactory::kNoGeoid);
	
	// Set geoeid depending on the ref frame
	if(fRefFrame ==	TRefSystemFactory::kCERNXYHsSphereSPS)
		geoid = TRefSystemFactory::kCGSphere;
	if(fRefFrame ==	TRefSystemFactory::kCernXYHg85Machine)
		geoid = TRefSystemFactory::kCG1985Machine;
	if(fRefFrame ==	TRefSystemFactory::kCernXYHg00Machine)
		geoid = TRefSystemFactory::kCG2000Machine;
	
	//writeLength(width, precision ,unit , pt.getNEstValue(geoid) );
}*/


void	TPointConverter::writeN( const int width,
								 const int precision,
								 TReal N)
{
	writeDouble(width, precision ,N );
	return;
}
