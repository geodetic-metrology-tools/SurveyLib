#include "TAdjustableLength.h"

#include <stdexcept>

#include "TConstants.h"

TAdjustableLength::TAdjustableLength(const TLength &angleValue, bool isFixed, const std::string &name) :
	fName(name), ifFixed(isFixed), fProvisionalValue(angleValue), fCorrection(0.0), fEstimatedValue(angleValue), fEstimatedPrecision(0.0), uidx(-1)
{
}

TAdjustableLength TAdjustableLength::createUninitialized(const std::string &name)
{
	return TAdjustableLength(TLength(NO_VALf), true, name);
}

void TAdjustableLength::setFirstUidx(int idx)
{
	if (isFixed())
		throw std::logic_error("Trying to assign unknown index to a fixed length. Length " + getName());
	uidx = idx;
}

void TAdjustableLength::setCorrection(int idx, TReal value)
{
	if (uidx == idx)
	{
		fCorrection.setMetresValue(value);
		fEstimatedValue.setMetresValue(fEstimatedValue.getMetresValue() + value);
	}
	else
		throw std::logic_error("Invalid unknown index in parameter access. Length " + getName());
}

void TAdjustableLength::setEstVal(int idx, TReal value) {
	if (uidx == idx){
      fEstimatedValue.setMetresValue(value);
	}
	else
		throw std::logic_error("Invalid unknown index in parameter access.");
}


void TAdjustableLength::setEstimatedPrecision(int idx, TReal ep) {
	if (uidx == idx)
		fEstimatedPrecision.setMetresValue(ep);
	else
		throw std::logic_error("Invalid unknown index in parameter access. Length " + getName());
}

void TAdjustableLength::reInitialise()
{
	fEstimatedPrecision.setMetresValue(0.0);
	fCorrection.setMetresValue(0.0);
	fEstimatedValue = fProvisionalValue;
}

bool TAdjustableLength::operator==(const TAdjustableLength &other) const
{
	return fProvisionalValue == other.fProvisionalValue && fCorrection == other.fCorrection && fEstimatedValue == other.fEstimatedValue
		&& fEstimatedPrecision == other.fEstimatedPrecision && ifFixed == other.ifFixed && uidx == other.uidx && fName == other.fName;
}

#if USE_SERIALIZER
void TAdjustableLength::serialize(ObjectSerializer &obj) const
{
	TVAdjustableObject::serialize(obj);
	obj.addProperty("fName", fName);
	obj.addProperty("fProvisionalValue", fProvisionalValue.getMetresValue());
	obj.addProperty("fEstimatedValue", fEstimatedValue.getMetresValue());
	obj.addProperty("fCorrection", fCorrection.getMetresValue());
	obj.addProperty("fEstimatedPrecision", fEstimatedPrecision.getMetresValue());

	obj.addProperty("ifFixed", ifFixed);
	obj.addProperty("uidx", uidx);
}
#endif // USE_SERIALIZER
