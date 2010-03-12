#include "TDist.h"

/////////////////////////////////
// planimetric distance in meters
/////////////////////////////////
quad	dist(TLength x1, TLength y1, TLength x2, TLength y2)
{
	
	return __sqrtq(__powq((x1.getMetresValue()-x2.getMetresValue()),2)
		+__powq((y1.getMetresValue()-y2.getMetresValue()),2));
}


quad	dist(quad x1, quad y1, quad x2, quad y2)
{
	
	return __sqrtq(__powq((x1-x2),2)+__powq((y1-y2),2));
}


quad	dist3D(TLength x1, TLength y1, TLength z1, TLength x2, TLength y2, TLength z2)
{
	
	return __sqrtq(__powq((x1.getMetresValue()-x2.getMetresValue()),2)
		+__powq((y1.getMetresValue()-y2.getMetresValue()),2) +__powq((z1.getMetresValue()-z2.getMetresValue()),2));


}


quad	dist3D(quad x1, quad y1, quad z1, quad x2, quad y2, quad z2)
{
	
	return __sqrtq(__powq((x1-x2),2)
		+__powq((y1-y2),2) +__powq((z1-z2),2));


}
