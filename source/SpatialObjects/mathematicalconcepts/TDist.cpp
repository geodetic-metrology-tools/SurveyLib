#include "TDist.h"

/////////////////////////////////
// planimetric distance in meters
/////////////////////////////////
real	dist(TLength x1, TLength y1, TLength x2, TLength y2)
{
	
	return sqrtq(powq((x1.getMetresValue()-x2.getMetresValue()),2)
		+powq((y1.getMetresValue()-y2.getMetresValue()),2));
}


real	dist(real x1, real y1, real x2, real y2)
{
	
	return sqrtq(powq((x1-x2),2)+powq((y1-y2),2));
}


real	dist3D(TLength x1, TLength y1, TLength z1, TLength x2, TLength y2, TLength z2)
{
	
	return sqrtq(powq((x1.getMetresValue()-x2.getMetresValue()),2)
		+powq((y1.getMetresValue()-y2.getMetresValue()),2) +powq((z1.getMetresValue()-z2.getMetresValue()),2));


}


real	dist3D(real x1, real y1, real z1, real x2, real y2, real z2)
{
	
	return sqrtq(powq((x1-x2),2)
		+powq((y1-y2),2) +powq((z1-z2),2));


}
