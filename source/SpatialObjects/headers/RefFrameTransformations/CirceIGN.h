#ifndef __CIRCE_IGN__
#	define __CIRCE_IGN__ 

#include <string>

/**
*
* Management of Circe executable
* 
*
*/


namespace circeIGN
{
/// Execute Circe program with the given command
std::string execCirce(const char *cmd);

/// Extract Circe output
void readCirceResult(std::string result, double &z);

/// Convert RGF-IGN69 altitude into GRS80 ellipsoidal height using RAF20 altimetric conversion grid
void circeTransfoRafToH(bool lambert, const double &X, const double &Y, double &h);

/// Convert GRS80 ellipsoidal height into RGF-IGN69 altitude using RAF20 altimetric conversion grid
void circeTransfoHToRaf(bool lambert, const double &X, const double &Y, double &h);

}
#endif // __CIRCE_IGN__ 
