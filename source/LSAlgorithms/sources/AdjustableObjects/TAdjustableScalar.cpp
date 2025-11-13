// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "TAdjustableScalar.h"

#include "TConstants.h"

TAdjustableScalar::TAdjustableScalar(TReal scalValue, bool isFixed, const std::string &name) :
	fName(name), isScalarFixed(isFixed), fProvisionalValue(scalValue), fCorrection(0.0), fEstimatedValue(scalValue), fEstimatedPrecision(0.0), uidx(-1)
{
}

TAdjustableScalar TAdjustableScalar::createUninitialized(const std::string &name)
{
	return TAdjustableScalar(NO_VALf, true, name);
}

Eigen::VectorXd TAdjustableScalar::getEstVector() const
{
	Eigen::VectorXd estVect(1);
	estVect << fEstimatedValue;
	return estVect;
}

TReal TAdjustableScalar::getValue(int idx) const
{
	if (uidx != idx)
		throw std::logic_error("Invalid unknown index in parameter access. Scalar " + getName());
	return fEstimatedValue;
}

void TAdjustableScalar::setValue(int idx, TReal value)
{
	if (uidx == idx)
	{
		fEstimatedValue = value;
		return;
	}
	throw std::logic_error("Invalid unknown index in parameter access. Scalar " + getName());
}

void TAdjustableScalar::setFirstUidx(int idx)
{
	if (isScalarFixed)
		throw std::logic_error("Trying to assign unknown index to fixed scalar. Scalar " + getName());
	uidx = idx;
}

void TAdjustableScalar::setEstimatedPrecision(int idx, TReal ep)
{
	if (uidx == idx)
		fEstimatedPrecision = ep;
	else
		throw std::logic_error("Invalid unknown index in parameter access. Scalar " + getName());
}

void TAdjustableScalar::reInitialise()
{
	fCorrection = 0.0;
	fEstimatedPrecision = 0.0;
	fEstimatedValue = fProvisionalValue;
}

#if USE_SERIALIZER
void TAdjustableScalar::serialize(ObjectSerializer &obj) const
{
	TVAdjustableObject::serialize(obj);
	obj.addProperty("fName", fName);
	obj.addProperty("fProvisionalValue", fProvisionalValue);
	obj.addProperty("fEstimatedValue", fEstimatedValue);
	obj.addProperty("fCorrection", fCorrection);
	obj.addProperty("fEstimatedPrecision", fEstimatedPrecision);

	obj.addProperty("ifFixed", isScalarFixed);
	obj.addProperty("uidx", uidx);
}
#endif // USE_SERIALIZER
