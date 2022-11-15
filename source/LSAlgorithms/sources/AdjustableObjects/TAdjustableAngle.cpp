#include <stdexcept>
#include "TAdjustableAngle.h"

TAdjustableAngle::TAdjustableAngle(const TAngle& angleValue, bool isFixed, const std::string& name):
   fName(name),
   ifFixed(isFixed),
   fProvisionalValue(angleValue),
   fCorrection(0.0),
   fEstimatedValue(angleValue),
   fEstimatedPrecision(0.0),
   uidx(-1)
{}

TAdjustableAngle TAdjustableAngle::createUninitialized(const std::string& name){
	return TAdjustableAngle(TAngle(NO_VALf), true, name);
}

void TAdjustableAngle::setFirstUidx(int idx) {
	if (isFixed())
		throw std::logic_error("Trying to assign unknown index to a fixed angle.");
	uidx = idx;
}

void TAdjustableAngle::setCorrection(int idx, TReal value) {
	if (uidx == idx){
		fCorrection.setRadiansValue(value);
		fEstimatedValue.setRadiansValue(fEstimatedValue.getRadiansValue() + value);
	}
	else
		throw std::logic_error("Invalid unknown index in parameter access.");
}

void TAdjustableAngle::setEstimatedPrecision(int idx, TReal ep) {
	if (uidx == idx)
		fEstimatedPrecision.setRadiansValue(ep);
	else
		throw std::logic_error("Invalid unknown index in parameter access.");
}

void TAdjustableAngle::reInitialise(){
	fEstimatedPrecision.setRadiansValue(0.0);
	fCorrection.setRadiansValue(0.0);
}


#ifdef USE_SERIALIZER
void TAdjustableAngle::serialize(SerializerObject::SerializationHelper &obj) const
{
	obj.addProperty("fName", fName);
	obj.addProperty("fProvisionalValue", fProvisionalValue);
	obj.addProperty("fEstimatedValue", fEstimatedValue);
	obj.addProperty("fCorrection", fCorrection);
	obj.addProperty("fEstimatedPrecision", fEstimatedPrecision);

	obj.addProperty("ifFixed", ifFixed);
	obj.addProperty("uidx", uidx);
}
#endif // USE_SERIALIZER
