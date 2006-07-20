#include "TDist.h"

/////////////////////////////////
// planimetric distance in meters
/////////////////////////////////
double	dist(TLength x1, TLength y1, TLength x2, TLength y2)
{
	
	return sqrt(pow((x1.getMetresValue()-x2.getMetresValue()),2)
		+pow((y1.getMetresValue()-y2.getMetresValue()),2));
}


double	dist(double x1, double y1, double x2, double y2)
{
	
	return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}


double	dist3D(TLength x1, TLength y1, TLength z1, TLength x2, TLength y2, TLength z2)
{
	
	return sqrt(pow((x1.getMetresValue()-x2.getMetresValue()),2)
		+pow((y1.getMetresValue()-y2.getMetresValue()),2) +pow((z1.getMetresValue()-z2.getMetresValue()),2));


}


double	dist3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
	
	return sqrt(pow((x1-x2),2)
		+pow((y1-y2),2) +pow((z1-z2),2));


}