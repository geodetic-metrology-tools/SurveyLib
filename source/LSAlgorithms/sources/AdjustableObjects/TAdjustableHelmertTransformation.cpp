#include "TAdjustableHelmertTransformation.h"

#include <stdexcept>

TAdjustableHelmertTransformation::TAdjustableHelmertTransformation()
{
	fixedTranslations = std::bitset<3>();
	fixedRotations = std::bitset<3>();
	fixedScale = std::bitset<1>();
	name = "";

	setDefaults();
	setDefaultsParams();
}

TAdjustableHelmertTransformation::TAdjustableHelmertTransformation(const std::bitset<3> &fixedTranslations,
	const std::bitset<3> &fixedRotations,
	const std::bitset<1> &fixedScale,
	const std::string &name) :
	fixedTranslations(fixedTranslations), fixedRotations(fixedRotations), fixedScale(fixedScale), name(name)
{
	setDefaults();
	setDefaultsParams();
}

TAdjustableHelmertTransformation::TAdjustableHelmertTransformation(const TransformParameters &transfParam,
	const std::bitset<3> &fixedTranslations,
	const std::bitset<3> &fixedRotations,
	const std::bitset<1> &fixedScale,
	const std::string &name) :
	fixedTranslations(fixedTranslations), fixedRotations(fixedRotations), fixedScale(fixedScale), name(name), fProvParameter(transfParam), fEstParameter(transfParam)
{
	setDefaults();
}

int TAdjustableHelmertTransformation::getNumUnkn() const
{
	return (int)!fixedRotations[0] + (int)!fixedRotations[1] + (int)!fixedRotations[2] + (int)!fixedTranslations[0] + (int)!fixedTranslations[1]
		+ (int)!fixedTranslations[2] + (int)!fixedScale[0];
}

int TAdjustableHelmertTransformation::getTranslationUnknIndex(int d) const
{
	assert3D(d);
	if (!fixedTranslations[d])
		return uidx_trans[d];
	throw std::logic_error("Trying to get unknown index from fixed translation. Transformation " + getName());
}

int TAdjustableHelmertTransformation::getRotationUnknIndex(int d) const
{
	assert3D(d);
	if (!fixedRotations[d])
		return uidx_rot[d];
	throw std::logic_error("Trying to get unknown index from fixed rotation. Transformation " + getName());
}

int TAdjustableHelmertTransformation::getScaleUnknIndex() const
{
	if (!fixedScale[0])
		return uidx_scale;
	throw std::logic_error("Trying to get unknown index from fixed scale. Transformation " + getName());
}

const std::vector<int> TAdjustableHelmertTransformation::getRelativeUnknIndices() const
{
	std::vector<int> activeIndices;
	for (int i = 0; i < 3; i++)
		if (!fixedTranslations[i])
			activeIndices.push_back(i);

	for (int i = 0; i < 3; i++)
		if (!fixedRotations[i])
			activeIndices.push_back(i + 3);

	if (!fixedScale[0])
		activeIndices.push_back(6);

	return activeIndices;
}

int TAdjustableHelmertTransformation::getFirstUidx() const
{
	for (int i = 0; i < 3; i++)
		if (!fixedTranslations[i])
			return uidx_trans[i];

	for (int i = 0; i < 3; i++)
		if (!fixedRotations[i])
			return uidx_rot[i];

	if (!fixedScale[0])
		return uidx_scale;

	throw std::logic_error("Trying to get unknown index from fixed transformation. Transformation " + getName());
}

int TAdjustableHelmertTransformation::getLastUidx() const
{
	if (!fixedScale[0])
		return uidx_scale;

	for (int i = 2; i >= 0; i--)
		if (!fixedRotations[i])
			return uidx_rot[i];
	for (int i = 2; i >= 0; i--)
		if (!fixedTranslations[i])
			return uidx_trans[i];

	throw std::logic_error("Trying to get unknown index from fixed transformation. Transformation " + getName());
}

void TAdjustableHelmertTransformation::setCorrection(int idx, TReal value)
{
	for (int i = 0; i < 3; i++)
		if (uidx_trans[i] == idx)
		{
			setTranslationCorrection(i, TLength(value));
			return;
		}

	for (int i = 0; i < 3; i++)
		if (uidx_rot[i] == idx)
		{
			setRotationCorrection(i, TAngle(value, TAngle::kRadians));
			return;
		}

	if (uidx_scale == idx)
	{
		setScaleCorrection(value);
		return;
	}

	throw std::logic_error("Invalid unknown index in parameter access. Transformation " + getName());
}

void TAdjustableHelmertTransformation::setParam(const TAngle &rx, const TAngle &ry, const TAngle &rz)
{
	fEstParameter.omega = fProvParameter.omega = rx;
	fEstParameter.phi = fProvParameter.phi = ry;
	fEstParameter.kappa = fProvParameter.kappa = rz;
}

void TAdjustableHelmertTransformation::setParam(const TLength tx, const TLength ty, const TLength tz)
{
	fEstParameter.tX = fProvParameter.tX = tx;
	fEstParameter.tY = fProvParameter.tY = ty;
	fEstParameter.tZ = fProvParameter.tZ = tz;
}

void TAdjustableHelmertTransformation::setParam(const TReal scl)
{
	fEstParameter.scale = fProvParameter.scale = scl;
}

void TAdjustableHelmertTransformation::setParam(const TLength tx, const TLength ty, const TLength tz, const TAngle &rx, const TAngle &ry, const TAngle &rz, const TReal scl)
{
	setParam(rx, ry, rz);
	setParam(tx, ty, tz);
	setParam(scl);
}

void TAdjustableHelmertTransformation::setTranslationCorrection(int idx, TLength value)
{
	if (idx == 0)
		fEstParameter.tX = fEstParameter.tX + value;
	else if (idx == 1)
		fEstParameter.tY = fEstParameter.tY + value;
	else if (idx == 2)
		fEstParameter.tZ = fEstParameter.tZ + value;
	else
		throw std::logic_error("Invalid unknown index in parameter access. Transformation " + getName());
	return;
}

void TAdjustableHelmertTransformation::setRotationCorrection(int idx, const TAngle &value)
{
	if (idx == 0)
		fEstParameter.omega = fEstParameter.omega + value;
	else if (idx == 1)
		fEstParameter.phi = fEstParameter.phi + value;
	else if (idx == 2)
		fEstParameter.kappa = fEstParameter.kappa + value;
	else
		throw std::logic_error("Invalid unknown index in parameter access. Transformation " + getName());
	return;
}

void TAdjustableHelmertTransformation::setScaleCorrection(TReal value)
{
	fEstParameter.scale = fEstParameter.scale + value;
}

const TAngle TAdjustableHelmertTransformation::getEstimatedPrecisionRot(int d) const
{
	ensureCovarIsSet();
	return TAngle(sqrt(fCovarianceMatrix(3 + d, 3 + d)));
}

const TLength TAdjustableHelmertTransformation::getEstimatedPrecisionTransl(int d) const
{
	ensureCovarIsSet();
	return TLength(sqrt(fCovarianceMatrix(d, d)));
}

TReal TAdjustableHelmertTransformation::getEstimatedPrecisionScale() const
{
	ensureCovarIsSet();
	return sqrt(fCovarianceMatrix(6, 6));
}

Eigen::Matrix<double, 7, 7> TAdjustableHelmertTransformation::getCovar() const
{
	ensureCovarIsSet();
	return fCovarianceMatrix;
}

bool TAdjustableHelmertTransformation::isTranslationFixed(int d) const
{
	assert3D(d);
	return (fixedTranslations[d]);
}

bool TAdjustableHelmertTransformation::isRotationFixed(int d) const
{
	assert3D(d);
	return (fixedRotations[d]);
}

void TAdjustableHelmertTransformation::setFirstUidx(int idx)
{
	if (isFixed())
		throw std::logic_error("Trying to assign unknown index to fixed transformation. Transformation " + getName());

	for (int i = 0; i < 3; i++)
		if (!fixedTranslations[i])
			uidx_trans[i] = idx++;

	for (int i = 0; i < 3; i++)
		if (!fixedRotations[i])
			uidx_rot[i] = idx++;

	if (!fixedScale[0])
		uidx_scale = idx++;
}

void TAdjustableHelmertTransformation::setDefaults()
{
	fCovarianceMatrix.setZero();
	fCovarianceMatrixIsSet = false;

	uidx_rot[0] = -1;
	uidx_rot[1] = -1;
	uidx_rot[2] = -1;

	uidx_trans[0] = -1;
	uidx_trans[1] = -1;
	uidx_trans[2] = -1;

	uidx_scale = -1;
}

void TAdjustableHelmertTransformation::setDefaultsParams()
{
	fProvParameter.omega.setRadiansValue(0.0);
	fProvParameter.phi.setRadiansValue(0.0);
	fProvParameter.kappa.setRadiansValue(0.0);
	fProvParameter.tX = TLength(0.0);
	fProvParameter.tY = TLength(0.0);
	fProvParameter.tZ = TLength(0.0);
	fProvParameter.scale = 1;

	fEstParameter.omega.setRadiansValue(0.0);
	fEstParameter.phi.setRadiansValue(0.0);
	fEstParameter.kappa.setRadiansValue(0.0);
	fEstParameter.tX = TLength(0.0);
	fEstParameter.tY = TLength(0.0);
	fEstParameter.tZ = TLength(0.0);
	fEstParameter.scale = 1;
}

TLength TAdjustableHelmertTransformation::getEstTranslation(int axis) const
{
	assert3D(axis);
	if (axis == 0)
		return fEstParameter.tX;
	else if (axis == 1)
		return fEstParameter.tY;
	else
		return fEstParameter.tZ;
}

TLength TAdjustableHelmertTransformation::getProvTranslation(int axis) const
{
	assert3D(axis);
	if (axis == 0)
		return fProvParameter.tX;
	else if (axis == 1)
		return fProvParameter.tY;
	else
		return fProvParameter.tZ;
}

const TAngle &TAdjustableHelmertTransformation::getEstRotation(int axis) const
{
	TAngle ang(NO_VALf, TAngle::kRadians);
	assert3D(axis);

	if (axis == 0)
		return fEstParameter.omega;
	else if (axis == 1)
		return fEstParameter.phi;
	else
		return fEstParameter.kappa;
}

const TAngle &TAdjustableHelmertTransformation::getProvRotation(int axis) const
{
	TAngle ang(NO_VALf, TAngle::kRadians);
	assert3D(axis);

	if (axis == 0)
		return fProvParameter.omega;
	else if (axis == 1)
		return fProvParameter.phi;
	else
		return fProvParameter.kappa;
}

void TAdjustableHelmertTransformation::reInitialise()
{
	setParam(fProvParameter.tX, fProvParameter.tY, fProvParameter.tZ);
	setParam(fProvParameter.omega, fProvParameter.phi, fProvParameter.kappa);
	setParam(fProvParameter.scale);

	fCovarianceMatrix.setZero();
	fCovarianceMatrixIsSet = false;
}

#if USE_SERIALIZER
void TAdjustableHelmertTransformation::serialize(ObjectSerializer &obj) const
{
	TVAdjustableObject::serialize(obj);

	obj.addProperty("fCovarianceMatrix", fCovarianceMatrix);
	obj.addProperty("fCovarianceMatrixIsSet", fCovarianceMatrixIsSet);
	obj.addProperty("fEstParameter",
		std::vector<double>{
			fEstParameter.tX.getMetresValue(),
			fEstParameter.tY.getMetresValue(),
			fEstParameter.tZ.getMetresValue(),
			fEstParameter.omega.getRadiansValue(),
			fEstParameter.phi.getRadiansValue(),
			fEstParameter.kappa.getRadiansValue(),
			fEstParameter.scale,
		});

	obj.addProperty("fixedTranfParam",
		std::vector<bool>{
			(bool)fixedTranslations[0],
			(bool)fixedTranslations[1],
			(bool)fixedTranslations[2],
			(bool)fixedRotations[0],
			(bool)fixedRotations[1],
			(bool)fixedRotations[2],
			(bool)fixedScale[0],
		});

	obj.addProperty("fProvParameter",
		std::vector<double>{
			fProvParameter.tX.getMetresValue(),
			fProvParameter.tY.getMetresValue(),
			fProvParameter.tZ.getMetresValue(),
			fProvParameter.omega.getRadiansValue(),
			fProvParameter.phi.getRadiansValue(),
			fProvParameter.kappa.getRadiansValue(),
			fProvParameter.scale,
		});

	obj.addProperty("line", line);
	obj.addProperty("name", name);

	obj.addProperty("uidx",
		std::vector<int>{
			uidx_trans[0],
			uidx_trans[1],
			uidx_trans[2],
			uidx_rot[0],
			uidx_rot[1],
			uidx_rot[2],
			uidx_scale,
		});
}
#endif // USE_SERIALIZER
