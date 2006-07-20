////////////////////////////////////////////////////////////////////
// TPointConverter.cpp
/*!
Write a output LGC file
Creates a file from the data read and sends the appropriate messages

Patterns:

 
Copyright 2003 CERN EST/SU. All rights reserved.
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
	{
		fLocalSys = false;
	}
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
void	TPointConverter::writeName(LSPosVecConstIter pt, int width)
{
	TAStreamFormatter*	stream = getStream();

	//Write point name
	stream->width(width);
	(*stream)<<left<<(pt->getName())<<right;
	return;
}


void	TPointConverter::writeName(string ptName, int width)
{
	TAStreamFormatter*	stream = getStream();

	//Write point name
	stream->width(width);
	(*stream)<<left<<(ptName)<<right;
	return;
}



////////////////////////////////////////////////////////////////////////////////////////////////
//X Y Z and H
////////////////////////////////////////////////////////////////////////////////////////////////
void	TPointConverter::writeXYZandH(LSPosVecConstIter pt)
{
	TAStreamFormatter*	stream = getStream();
	int					coordWidth = getCoordWidth();
	string				separator = getSeparator();

	//get Coordinate as a TPositionVector
	(*stream)<<(pt->getEstimatedValue());

	//write H if point's refrence frame is CCS
	if(!isInLocalSystem())
	{
		(*stream)<<(separator);
		stream->width(coordWidth);
		(*stream)<<(pt->getHEstValue(fRefFrame));
	}

	return;
}


void	TPointConverter::writeXYZandH(	const int width,
										const int precision,
										const TLength::EUnits unit,
										const string separator,
										LSPosVecConstIter pt)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	(*stream)<<pt->getXEstValue()<<separator;

	//write Y
	(*stream)<<pt->getYEstValue()<<separator;

	//write Z
	(*stream)<<pt->getZEstValue()<<separator;

	//write H if point's refrence frame is CCS
	if(!isInLocalSystem())
	{
		(*stream)<<(pt->getHEstValue(fRefFrame));
	}

	return;
}



void	TPointConverter::writeXYZorH(	const int width,
										const int precision,
										const TLength::EUnits unit,
										const string separator,
										LSPosVecConstIter pt)
{
	if(!isInLocalSystem())
	{writeXYH(width, precision, unit, separator, pt);}
	else
	{writeXYZ(width, precision, unit, separator, pt);}
	return;
}



////////////////////////////////////////////////////////////////////////////////////////////////
//X Y H
////////////////////////////////////////////////////////////////////////////////////////////////
void	TPointConverter::writeXYH(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const string separator,
									LSPosVecConstIter pt)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	(*stream)<<pt->getXEstValue()<<separator;

	//write Y
	(*stream)<<pt->getYEstValue()<<separator;

	//write H if point's refrence frame is CCS
	if(!isInLocalSystem())
	{(*stream)<<(pt->getHEstValue(fRefFrame));}
	else
	{writeString(width, " ");}
	return;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//X Y Z 
////////////////////////////////////////////////////////////////////////////////////////////////
void	TPointConverter::writeXYZ(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const string separator,
									LSPosVecConstIter pt)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	(*stream)<<pt->getXEstValue()<<separator;

	//write Y
	(*stream)<<pt->getYEstValue()<<separator;

	//write Z
	{(*stream)<<pt->getZEstValue();}
	return;
}


void	TPointConverter::writeXYZ(	const int width,
									const int precision,
									const TLength::EUnits unit,
									const string separator,
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
	{(*stream)<<pt.getZ();}
	return;
}


void	TPointConverter::write3Coordinates(	const int width,
											const int precision,
											const TLength::EUnits unit,
											const string separator,
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
	if(pt.getCoordSys() == TCoordSysFactory::k3DCartesian)
	{(*stream)<<pt.getZ();}
	
	if(pt.getCoordSys() == TCoordSysFactory::k2DPlusH)
	{(*stream)<<pt.getH();}

	return;
}





////////////////////////////////////////////////////////////////////////////////////////////////
//N
////////////////////////////////////////////////////////////////////////////////////////////////
void	TPointConverter::writeN( const int width,
								 const int precision,
								 const TLength::EUnits unit,
								 LSPosVecConstIter pt)
{
	TRefSystemFactory::EGeoid geoid;
	if(fRefFrame ==	TRefSystemFactory::kCernXYHg85Machine)
	{geoid = TRefSystemFactory::kCG1985Machine;}
	if(fRefFrame ==	TRefSystemFactory::kCernXYHg00Machine)
	{geoid = TRefSystemFactory::kCG2000Machine;}
	if(fRefFrame ==	TRefSystemFactory::kCERNXYHsSphereSPS)
	{geoid = TRefSystemFactory::kCGSphere;}
	writeLength(width, precision ,unit ,pt->getNEstValue(geoid) );
	return;
}




void	TPointConverter::writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
												const int width,
												const int precision,
												const TLength::EUnits unit,
												const string separator,
												const TLength Xparam,
												const TLength Yparam,
												const TLength Zparam,
												const string Dparam)
{
	TAStreamFormatter*	stream = getStream();

	stream->setLengthUnits(unit);
	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	if(status == TSpatialStatus::kVx || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVxz)
		{(*stream)<<(Xparam)<<(separator);	}
		else
		{writeString(width, Dparam);
			(*stream)<<(separator);}

	//write Y
	if(status == TSpatialStatus::kVy || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVyz)
		{(*stream)<<(Yparam)<<(separator);}
		else
		{writeString(width, Dparam);
			(*stream)<<(separator);}

	//write Z
	if(status == TSpatialStatus::kVz || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxz  || status == TSpatialStatus::kVyz)
		{(*stream)<<(Zparam);}
		else
		{writeString(width, Dparam);}
	return;
}



void	TPointConverter::writeCoordinateParam(	const TSpatialStatus::ESpatialStatus status,
												const int width,
												const int precision,
												const string separator,
												const TDouble Xparam,
												const TDouble Yparam,
												const TDouble Zparam,
												const string Dparam)
{
	TAStreamFormatter*	stream = getStream();

	stream->setWidthFormat(width);
	stream->setPrecisionFormat(precision);

	//write X
	if(status == TSpatialStatus::kVx || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVxz)
		{(*stream)<<(Xparam)<<(separator);	}
		else
		{writeString(width, Dparam);
			(*stream)<<(separator);}

	//write Y
	if(status == TSpatialStatus::kVy || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxy  || status == TSpatialStatus::kVyz)
		{(*stream)<<(Yparam)<<(separator);}
		else
		{writeString(width, Dparam);
			(*stream)<<(separator);}

	//write Z
	if(status == TSpatialStatus::kVz || status == TSpatialStatus::kVxyz || status == TSpatialStatus::kVxz  || status == TSpatialStatus::kVyz)
		{(*stream)<<(Zparam);}
		else
		{writeString(width, Dparam);}
	return;
}










