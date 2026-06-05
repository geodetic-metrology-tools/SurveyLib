// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TAdjustablePoint.h"

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

#include "TXYH2CCS.h"

//////////////////////////////////////////////////////////////////////
// CONSTRUCTORS / DESTRUCTOR
//////////////////////////////////////////////////////////////////////

// Private constructor for creating uninitialized object
TAdjustablePoint::TAdjustablePoint(const std::string &name) :
	fName(name),
	fProvisionalValue(NO_VALf, NO_VALf, NO_VALf, TCoordSysFactory::k3DCartesian),
	fEstimatedValue(fProvisionalValue),
	fHfixed(false),
	fReferential(TRefSystemFactory::ERefFrame::kNotInGraph)
{
	setDefaults(true, true, true);
}

TAdjustablePoint::TAdjustablePoint() :
	fName(""),
	fProvisionalValue(NO_VALf, NO_VALf, NO_VALf, TCoordSysFactory::k3DCartesian),
	fEstimatedValue(fProvisionalValue),
	fHfixed(false),
	fReferential(TRefSystemFactory::ERefFrame::kNotInGraph)
{
	setDefaults(true, true, true);
}

TAdjustablePoint::TAdjustablePoint(const TPositionVector &pos, bool isXfixed, bool isYfixed, bool isZHfixed, const std::string &name, TRefSystemFactory::ERefFrame referential) :
	fName(name), fProvisionalValue(pos), fEstimatedValue(fProvisionalValue), fReferential(referential), fHfixed(false)
{
	if (pos.getCoordSys() == TCoordSysFactory::k2DPlusH)
	{ // If position is given in 2D + H system
		if (fReferential == TRefSystemFactory::ERefFrame::kCERNXYHsSphereSPS)
			TXYH2CCS::XYHs2CCS(fEstimatedValue);
		else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg00Machine)
			TXYH2CCS::XYHg2000Machine2CCS(fEstimatedValue);
		else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg85Machine)
			TXYH2CCS::XYHg1985Machine2CCS(fEstimatedValue);

		// If referential is a 2D+H system and H is fixed, than set fHfixed to TRUE, because we need to resetting original H when setting contributions
		if (isZHfixed == true)
			fHfixed = true;
	}

	setDefaults(isXfixed, isYfixed, isZHfixed);
}

/// Copy constructor
TAdjustablePoint::TAdjustablePoint(const TAdjustablePoint &pos) :
	fName(pos.fName),
	fProvisionalValue(pos.fProvisionalValue),
	fEstimatedValue(pos.fEstimatedValue),
	fReferential(pos.fReferential),
	fHfixed(pos.fHfixed),
	fCovarianceMatrix(pos.fCovarianceMatrix),
	fCovarianceMatrixIsSet(pos.fCovarianceMatrixIsSet),
	fXValueSet(pos.fXValueSet),
	fYValueSet(pos.fYValueSet),
	eolcomment(pos.eolcomment),
	hdrcomment(pos.hdrcomment),
	line(pos.line)
{
	for (int i = 0; i < 3; i++)
	{
		fCorrection[i] = pos.fCorrection[i];
		fixedState[i] = pos.fixedState[i];
		uidx[i] = pos.uidx[i];
	}
}

TAdjustablePoint TAdjustablePoint::createUninitialized(const std::string &name)
{
	TAdjustablePoint ap(name);
	return ap;
}

///////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESS METHODS
///////////////////////////////////////////////////////////////////////////

TLength TAdjustablePoint::getErrorEllMajorAxis() const
{
	TReal gdAxe(NO_VALf);

	switch (getSpatialStatus())
	{
	case TSpatialStatus::ESpatialStatus::kVxy: {
		TReal vxy = getXYCovar() * M2MM * M2MM; // because vxy is store in m^2
		TReal sx2 = powq(getXEstPrecision().getMMetresValue(), 2);
		TReal sy2 = powq(getYEstPrecision().getMMetresValue(), 2);
		gdAxe = (LITERAL(1.0) / sqrtq(LITERAL(2.0))) * sqrtq(sx2 + sy2 + sqrtq(powq((sy2 - sx2), 2) + (LITERAL(4.0) * vxy * vxy)));
		break;
	}
	case TSpatialStatus::ESpatialStatus::kVxz: {
		TReal vxz = getXYCovar() * M2MM * M2MM; // because vxz is store in m^2
		TReal sx2 = powq(getXEstPrecision().getMMetresValue(), 2);
		TReal sz2 = powq(getZEstPrecision().getMMetresValue(), 2);
		gdAxe = (LITERAL(1.0) / sqrtq(LITERAL(2.0))) * sqrtq(sx2 + sz2 + sqrtq(powq((sz2 - sx2), 2) + (LITERAL(4.0) * vxz * vxz)));
		break;
	}
	case TSpatialStatus::ESpatialStatus::kVyz: {
		TReal vyz = getXYCovar() * M2MM * M2MM; // because vyz is store in m^2
		TReal sz2 = powq(getZEstPrecision().getMMetresValue(), 2);
		TReal sy2 = powq(getYEstPrecision().getMMetresValue(), 2);
		gdAxe = (LITERAL(1.0) / sqrtq(LITERAL(2.0))) * sqrtq(sz2 + sy2 + sqrtq(powq((sy2 - sz2), 2) + (LITERAL(4.0) * vyz * vyz)));
	}
	}

	TLength res;
	res.setMMetresValue(gdAxe);
	return res;
}

TLength TAdjustablePoint::getErrorEllMinorAxis() const
{
	TReal ptAxe(NO_VALf);

	switch (getSpatialStatus())
	{
	case TSpatialStatus::ESpatialStatus::kVxy: {
		TReal vxy = getXYCovar() * M2MM * M2MM; // because vxy is store in m^2
		TReal sx2 = powq(getXEstPrecision().getMMetresValue(), 2);
		TReal sy2 = powq(getYEstPrecision().getMMetresValue(), 2);
		ptAxe = (LITERAL(1.0) / sqrtq(LITERAL(2.0))) * sqrtq(sx2 + sy2 - sqrtq(powq((sy2 - sx2), 2) + (LITERAL(4.0) * vxy * vxy)));
		break;
	}
	case TSpatialStatus::ESpatialStatus::kVxz: {
		TReal vxz = getXYCovar() * M2MM * M2MM; // because vxz is store in m^2
		TReal sx2 = powq(getXEstPrecision().getMMetresValue(), 2);
		TReal sz2 = powq(getZEstPrecision().getMMetresValue(), 2);
		ptAxe = (LITERAL(1.0) / sqrtq(LITERAL(2.0))) * sqrtq(sx2 + sz2 - sqrtq(powq((sz2 - sx2), 2) + (LITERAL(4.0) * vxz * vxz)));
		break;
	}
	case TSpatialStatus::ESpatialStatus::kVyz: {
		TReal vyz = getXYCovar() * M2MM * M2MM; // because vyz is store in m^2
		TReal sz2 = powq(getZEstPrecision().getMMetresValue(), 2);
		TReal sy2 = powq(getYEstPrecision().getMMetresValue(), 2);
		ptAxe = (LITERAL(1.0) / sqrtq(LITERAL(2.0))) * sqrtq(sz2 + sy2 - sqrtq(powq((sy2 - sz2), 2) + (LITERAL(4.0) * vyz * vyz)));
	}
	}

	TLength res;
	res.setMMetresValue(ptAxe);
	return res;
}

TAngle TAdjustablePoint::getErrorEllGis() const
{
	TAngle gis(0.0);

	switch (getSpatialStatus())
	{
	case TSpatialStatus::ESpatialStatus::kVxy: {
		TReal vxy = getXYCovar() * M2MM * M2MM; // because vxy is store in m^2
		TReal sx2 = powq(getXEstPrecision().getMMetresValue(), 2);
		TReal sy2 = powq(getYEstPrecision().getMMetresValue(), 2);
		gis = ((LITERAL(0.5)) * TAngle::aTan2(2 * vxy, (sy2 - sx2)));
		break;
	}
	case TSpatialStatus::ESpatialStatus::kVxz: {
		TReal vxz = getXYCovar() * M2MM * M2MM; // because vxz is store in m^2
		TReal sx2 = powq(getXEstPrecision().getMMetresValue(), 2);
		TReal sz2 = powq(getZEstPrecision().getMMetresValue(), 2);
		gis = ((LITERAL(0.5)) * TAngle::aTan2(2 * vxz, (sz2 - sx2)));
		break;
	}
	case TSpatialStatus::ESpatialStatus::kVyz: {
		TReal vyz = getXYCovar() * M2MM * M2MM; // because vyz is store in m^2
		TReal sz2 = powq(getZEstPrecision().getMMetresValue(), 2);
		TReal sy2 = powq(getYEstPrecision().getMMetresValue(), 2);
		gis = ((LITERAL(0.5)) * TAngle::aTan2(2 * vyz, (sz2 - sy2)));
	}
	}

	TReal testAffichage = gis.getGonsValue();
	TAngle deuxCentGrad;
	deuxCentGrad.setGonsValue(200);
	if (testAffichage > 200)
	{
		gis = gis - deuxCentGrad;
	}

	return gis;
}

TAdjustablePoint::ErrorEllipsoid TAdjustablePoint::getErrorEllipsoid() const
{
	ensureCovarIsSet();
	Eigen::EigenSolver<Eigen::Matrix3d> ev(fCovarianceMatrix);

	const auto &evals(ev.eigenvalues());
	const auto &evecs(ev.eigenvectors());

	/* The length of the semimajor axes of the 95% confidence ellipsoid are
	   Fv * [eigenvalue_0, eigenvalue_1, eigenvalue_2] with Fv being the 95%
	   percentile of the Fisher distribution for three degrees of freedom (approx. 7.80).
	   We are interested in the one-sigma-level, so our multiplier actualy is 1.0.

	   We need the eigenvectors as well since they are the direction sof the ellipsoid's axes.

	   Source:
	   Parameter Estimation and Inverse Problems
	   Richard C. Aster, Brian Borchers, Clifford H. Thurber
	   Academic Press, 2013 - 360 pages
	   (on page 36)
	*/

	// Indexing is (row, column): Each column corresponds to one eigenvector
	TReal vx[3] = {evecs(0, 0).real(), evecs(1, 0).real(), evecs(2, 0).real()};
	TReal vy[3] = {evecs(0, 1).real(), evecs(1, 1).real(), evecs(2, 1).real()};
	TReal vz[3] = {evecs(0, 2).real(), evecs(1, 2).real(), evecs(2, 2).real()};
	ErrorEllipsoid ell(vx, vy, vz, sqrtq(evals(0).real()), sqrtq(evals(1).real()), sqrtq(evals(2).real()));

	return ell;
}

/*!
	See \ref TVAdjustableObject::setFirstUidx

	\throws Throws a logic_error if no component of the point is variable, i.e. a fixed point.
*/
void TAdjustablePoint::setFirstUidx(int idx)
{
	if (isFixed())
		throw std::logic_error("Trying to assign unknown index to a fixed point. Point " + getName());

	for (int i = 0; i < 3; i++)
		if (!fixedState[i])
			uidx[i] = idx++;
}

/// Update the adjustment information of an uninitialized point
void TAdjustablePoint::updateFixedState(bool lx, bool ly, bool lz)
{
	fixedState[0] = (lx);
	fixedState[1] = (ly);
	fixedState[2] = (lz);
	// make sure also the h is updated
	if (fProvisionalValue.getCoordSys() == TCoordSysFactory::k2DPlusH)
		fHfixed = lz;

	fXValueSet = (lx);
	fYValueSet = (ly);
}

void TAdjustablePoint::reInitialise()
{
	TFreeVector zeroVec(LITERAL(0.0), LITERAL(0.0), LITERAL(0.0), TCoordSysFactory::k3DCartesian);
	fCorrection[0] = fCorrection[1] = fCorrection[2] = TLength(0.0);
	fEstimatedValue = fProvisionalValue;

	/*If the provisional value was in XYH, transform the estimated value into XYZ*/
	if (fProvisionalValue.getCoordSys() == TCoordSysFactory::k2DPlusH)
	{ // If position is given in 2D + H system
		if (fReferential == TRefSystemFactory::ERefFrame::kCERNXYHsSphereSPS)
			TXYH2CCS::XYHs2CCS(fEstimatedValue);
		else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg00Machine)
			TXYH2CCS::XYHg2000Machine2CCS(fEstimatedValue);
		else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg85Machine)
			TXYH2CCS::XYHg1985Machine2CCS(fEstimatedValue);
	}

	fCovarianceMatrix.setZero();
}

int TAdjustablePoint::getNumUnkn() const
{
	return !(int)fixedState[0] + !(int)fixedState[1] + !(int)fixedState[2];
}

bool TAdjustablePoint::hasVariable() const
{
	return !fixedState[0] || !fixedState[1] || !fixedState[2];
}

int TAdjustablePoint::getFirstUidx() const
{
	for (int i = 0; i < 3; i++)
		if (!fixedState[i])
			return uidx[i];
	throw std::logic_error("Trying to get unknown index from fixed coordinate. Point " + getName());
}

int TAdjustablePoint::getLastUidx() const
{
	for (int i = 2; i >= 0; i--)
		if (!fixedState[i])
			return uidx[i];
	throw std::logic_error("Trying to get unknown index from fixed coordinate. Point " + getName());
}

int TAdjustablePoint::getCoordinateUnknIndex(int d) const
{
	assert3D(d);
	if (!fixedState[d])
		return uidx[d];
	else
		throw std::logic_error("Trying to get unknown index from fixed coordinate. Point " + getName());
}

const std::vector<int> TAdjustablePoint::getRelativeUnknIndices() const
{
	std::vector<int> activeIndices;
	for (int i = 0; i < 3; i++)
	{
		if (!fixedState[i])
		{
			activeIndices.push_back(i);
		}
	}
	return activeIndices;
}
///////////////////////////////////////////////////////////////////////////
// PRIVATE METHODS
///////////////////////////////////////////////////////////////////////////

void TAdjustablePoint::setDefaults(bool lx, bool ly, bool lz)
{
	fixedState[0] = lx;
	fixedState[1] = ly;
	fixedState[2] = lz;

	uidx[0] = -1;
	uidx[1] = -1;
	uidx[2] = -1;

	fXValueSet = lx;
	fYValueSet = ly;

	fCorrection[0] = TLength(0.0);
	fCorrection[1] = TLength(0.0);
	fCorrection[2] = TLength(0.0);

	fCovarianceMatrix.setZero();
	fCovarianceMatrixIsSet = false;
}

void TAdjustablePoint::transformEstimatedValue()
{
	// Set original H value and calculate Z0star for next iteration.
	fEstimatedValue.setCoordSys(TCoordSysFactory::ECoordSys::k2DPlusH);
	fEstimatedValue.setH(fProvisionalValue.getH());
	if (fReferential == TRefSystemFactory::ERefFrame::kCERNXYHsSphereSPS)
		TXYH2CCS::XYHs2CCS(fEstimatedValue);
	else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg00Machine)
		TXYH2CCS::XYHg2000Machine2CCS(fEstimatedValue);
	else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg85Machine)
		TXYH2CCS::XYHg1985Machine2CCS(fEstimatedValue);
}

TReal TAdjustablePoint::getHEstValue() const
{
	if (fReferential == TRefSystemFactory::ERefFrame::kLocalRefFrame)
		throw std::runtime_error("Point is defined in local system, no geoid assigned. Point " + getName());

	TPositionVector pvEst = fEstimatedValue;
	if (fReferential == TRefSystemFactory::ERefFrame::kCERNXYHsSphereSPS)
		TXYH2CCS::CCS2XYHs(pvEst);
	else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg00Machine)
		TXYH2CCS::CCS2XYHg2000Machine(pvEst);
	else if (fReferential == TRefSystemFactory::ERefFrame::kCernXYHg85Machine)
		TXYH2CCS::CCS2XYHg1985Machine(pvEst);

	return pvEst.getH().getMetresValue();
}

Eigen::VectorXd TAdjustablePoint::getEstVector() const
{
	return fEstimatedValue.toRealVector();
}

TReal TAdjustablePoint::getValue(int idx) const
{
	TReal value = 0;
	for (int i = 0; i < 3; i++)
	{
		if (uidx[i] == idx)
		{
			if (i == 0)
				value = TReal(fEstimatedValue.getX());
			else if (i == 1)
				value = TReal(fEstimatedValue.getY());
			else
				value = TReal(fEstimatedValue.getZ());
		}
	}
	return value;
}

void TAdjustablePoint::setValue(int idx, TReal value)
{
	for (int i = 0; i < 3; i++)
	{
		if (uidx[i] == idx)
		{
			if (i == 0)
			{
				fEstimatedValue.setX(TLength(value));
			}
			else if (i == 1)
			{
				fEstimatedValue.setY(TLength(value));
			}
			else
			{
				fEstimatedValue.setZ(TLength(value));
			}
			return;
		}
	}

	throw std::logic_error("Invalid unknown index in parameter access. Point " + getName());
}

/*! Gets the euclidean estimated distance from this adjustable point to another one.
	\param[in] Second adjustable point
*/
TLength TAdjustablePoint::getEstimatedEuclideanDistance(const TAdjustablePoint *ptOther) const
{
	// NB: getEstValue method returns coordinates in Meters
	return TLength(sqrt(pow2(getEstValue(0) - ptOther->getEstValue(0)) + pow2(getEstValue(1) - ptOther->getEstValue(1)) + pow2(getEstValue(2) - ptOther->getEstValue(2))));
}

#if USE_SERIALIZER
void TAdjustablePoint::serialize(ObjectSerializer &obj) const
{
	TVAdjustableObject::serialize(obj);
	obj.addProperty("eolcomment", eolcomment);
	obj.addProperty("fCorrection", fCorrection);
	obj.addProperty("fCovarianceMatrix", fCovarianceMatrix);
	obj.addProperty("fCovarianceMatrixIsSet", fCovarianceMatrixIsSet);
	obj.addProperty("fEstimatedValue", fEstimatedValue);
	obj.addProperty("fHfixed", fHfixed);
	obj.addProperty("fixedState", fixedState);
	obj.addProperty("fName", fName);
	obj.addProperty("fProvisionalValue", fProvisionalValue);
	obj.addProperty("fReferential", fReferential);
	obj.addProperty("fSpatialStatus", getSpatialStatus());
	obj.addProperty("fXValueSet", fXValueSet);
	obj.addProperty("fYValueSet", fYValueSet);
	obj.addProperty("hdrcomment", hdrcomment);
	obj.addProperty("line", line);
	obj.addProperty("uidx", uidx);
}

void TAdjustablePoint::ErrorEllipsoid::serialize(ObjectSerializer &obj) const
{
	obj.addProperty("vx", vx);
	obj.addProperty("vy", vy);
	obj.addProperty("vz", vz);
	obj.addProperty("lx", lx);
	obj.addProperty("ly", ly);
	obj.addProperty("lz", lz);
}
#endif // USE_SERIALIZER
