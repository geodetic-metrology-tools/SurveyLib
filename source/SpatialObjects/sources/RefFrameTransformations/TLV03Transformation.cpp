#include "TLV03Transformation.h"
#include <TRefFrameInfo.h>
#include <ReframeSwisstopo.h>


#include <iostream>
#include <sstream>

TLV03Transformation::TLV03Transformation(bool fFromLV95, std::string fVerticalDatum) : fFromLV95(fFromLV95), fVerticalDatum(fVerticalDatum)
{
}

TLV03Transformation * TLV03Transformation::clone() const
{
    return new TLV03Transformation(*this);
}

TLV03Transformation * TLV03Transformation::inverse() const
{
	return new TLV03Transformation(!fFromLV95, fVerticalDatum);
}

TAReferenceFrame * TLV03Transformation::getSourceFrame() const
{
	if (fFromLV95)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh);
	}
	else if (fVerticalDatum == "eh")
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_eh);
	}
	else if (fVerticalDatum == "ln02")
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_ln02);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_lhn95);
	}
}

TAReferenceFrame * TLV03Transformation::getDestinationFrame() const
{
	if (!fFromLV95)
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV95_eh);
	}
	else if (fVerticalDatum == "eh")
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_eh);
	}
	else if(fVerticalDatum == "ln02")
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_ln02);
	}
	else
	{
		return TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kSwissLV03_lhn95);
	}
}

bool TLV03Transformation::transform(TPositionVector & pv) const
{
    TSpatialPosition position(getSourceFrame());
	if(!position.setCoordinates(pv))
        return false;

    double x = position.getCoordinates(TCoordSysFactory::k2DPlusH).getX().getMetresValue();
    double y = position.getCoordinates(TCoordSysFactory::k2DPlusH).getY().getMetresValue();
    double h = position.getCoordinates(TCoordSysFactory::k2DPlusH).getH().getMetresValue();

	// We call the dll Reframe developped by Swisstopo to do the transformation between LV95 and LV03
	bool result = true;
	bool outsideChenyx06 = true;
	ReframeWrapper reframeLibObj;
	if (fFromLV95)
	{
		if (fVerticalDatum == "eh")
		{
			outsideChenyx06 = !reframeLibObj.ComputeReframe(x, y, h, ReframeWrapper::LV95, ReframeWrapper::LV03_Military, ReframeWrapper::Ellipsoid, ReframeWrapper::Ellipsoid);
			result = true;
		}
		else if (fVerticalDatum == "ln02")
		{
			outsideChenyx06 = !reframeLibObj.ComputeReframe(x, y, h, ReframeWrapper::LV95, ReframeWrapper::LV03_Military, ReframeWrapper::Ellipsoid, ReframeWrapper::LN02);
			result = true;
		}
		else
		{
			outsideChenyx06 = !reframeLibObj.ComputeReframe(x, y, h, ReframeWrapper::LV95, ReframeWrapper::LV03_Military, ReframeWrapper::Ellipsoid, ReframeWrapper::LHN95);
			result = true;
		}
	}
	else
	{
		if (fVerticalDatum == "eh")
		{
			outsideChenyx06 = !reframeLibObj.ComputeReframe(x, y, h, ReframeWrapper::LV03_Military, ReframeWrapper::LV95, ReframeWrapper::Ellipsoid, ReframeWrapper::Ellipsoid);
			result = true;
		}
		else if (fVerticalDatum == "ln02")
		{
			outsideChenyx06 = !reframeLibObj.ComputeReframe(x, y, h, ReframeWrapper::LV03_Military, ReframeWrapper::LV95, ReframeWrapper::LN02, ReframeWrapper::Ellipsoid);
			result = true;
		}
		else
		{
			outsideChenyx06 = !reframeLibObj.ComputeReframe(x, y, h, ReframeWrapper::LV03_Military, ReframeWrapper::LV95, ReframeWrapper::LHN95, ReframeWrapper::Ellipsoid);
			result = true;
		}
	}
    if(!result)
        return false;

    pv.setX(TLength(x));
    pv.setY(TLength(y));
    pv.setH(TLength(h));

    return true;
}
