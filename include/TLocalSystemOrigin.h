#ifndef SPATIAL_OBJECTS_e62c6be5-6903-4e36-b58e-5dd8c858f5d2
#define SPATIAL_OBJECTS_e62c6be5-6903-4e36-b58e-5dd8c858f5d2

#include <TAngle.h>
#include <TSpatialPosition.h>

class TLocalSystemOrigin
{
public:
    TLocalSystemOrigin(const TSpatialPosition & origin, const TAngle & gisement, const TAngle & slope);
    bool operator==(const TLocalSystemOrigin & rhs) const;
    
    TSpatialPosition origin() const {return fOrigin;}
    TAngle gisement() const {return fGisement;}
    TAngle slope() const {return fSlope;}
private:
    const TSpatialPosition fOrigin; 
    const TAngle fGisement; 
    const TAngle fSlope;
};

#endif