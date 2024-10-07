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

void TAdjustableScalar::setFirstUidx(int idx)
{
	if (isScalarFixed)
		throw std::logic_error("Trying to assign unknown index to fixed scalar. Scalar " + getName());
	uidx = idx;
}

void TAdjustableScalar::setCorrection(int idx, TReal value)
{
	if (uidx == idx)
	{
		fCorrection = value;
		fEstimatedValue += value;
		return;
	}
	throw std::logic_error("Invalid unknown index in parameter access. Scalar " + getName());
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
