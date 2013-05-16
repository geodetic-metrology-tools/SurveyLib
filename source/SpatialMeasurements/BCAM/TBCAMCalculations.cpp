#include <Eigen/Core>
#include <Eigen/Geometry>

#include "TBCAMCalculations.h"

using namespace Eigen;
typedef Matrix<TReal, 3, 1> Vec3;
typedef Matrix<TReal, 3, 3> Mat3;
static const TCoordSysFactory::ECoordSys k3D(TCoordSysFactory::k3DCartesian);

inline Vec3 VecFromTpos(const TPositionVector& p) {
	return Vector3d(p.getX().getMetresValue(),
		            p.getY().getMetresValue(),
					p.getZ().getMetresValue());
}

TBCAMCalculations::TBCAMCalculations(const TPositionVector& cone,
								     const TPositionVector& slot,
									 const TPositionVector& plane) :
mv(TFreeVector(k3D))
{
	Vec3 vcone(VecFromTpos(cone));
	Vec3 ex, ey, ez;
	// cone-slot vector
	Vec3 cs(VecFromTpos(slot)-vcone);
	// cone-plane vector
	Vec3 cp(VecFromTpos(plane)-vcone);
	// rotation around y-axis to have z close to the optical axis
    static const TReal rot_y(0.2798);

    // Y-axis perpendicular on ball plane
    ey = cs.cross(cp);
    // normalize Y-axis
    ey.normalize();

	// z-axis is inverted direction of cone-slot
    ez = -cs;
    ez.normalize();
    // X-axis perpendicular on y and z-axis
    ex = ey.cross(ez);
	
    // rotate X and Z around the calculated Y-axis
	ex = AngleAxis<TReal>(rot_y, ey)*ex;
    ez = AngleAxis<TReal>(rot_y, ey)*ez;
    ex.normalize();
    ez.normalize();

	// Set the cone to be the origin
	mv = TFreeVector(vcone(0), vcone(1), vcone(2), k3D);

	// set the colum vetors of the matrix from unit vectors
	for (int i = 0; i < 3; i++) mm.setC(i,0, ex(i));
	for (int i = 0; i < 3; i++) mm.setC(i,1, ey(i));
	for (int i = 0; i < 3; i++) mm.setC(i,2, ez(i));
}

TPositionVector& TBCAMCalculations::extToBCAM(TPositionVector& p) {
	p = mm*p;
	p += mv;
	return p;
}

TPositionVector& TBCAMCalculations::BCAMToExt(TPositionVector& p) {
	p -= mv;
	p = mm*p;
	return p;
}