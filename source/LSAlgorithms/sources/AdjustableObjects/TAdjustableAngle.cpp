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

const std::vector<int> TAdjustableAngle::getRelativeUnknIndices() const
{
	std::vector<int> activeIndices;
	if (!ifFixed)
		activeIndices.push_back(0);
	return activeIndices;
}

void TAdjustableAngle::setFirstUidx(int idx)
{
	if (isFixed())
		throw std::logic_error("Trying to assign unknown index to a fixed angle. Angle " + getName());
	uidx = idx;
}

Eigen::VectorXd TAdjustableAngle::getEstVector() const
{
	Eigen::VectorXd estVect(1);
	estVect << fEstimatedValue.getRadiansValue();
	return estVect;
}

TReal TAdjustableAngle::getValue(int idx) const
{
	if (uidx != idx)
		throw std::logic_error("Invalid unknown index in parameter access. Angle " + getName());
	return TReal(fEstimatedValue.getRadiansValue());
}

void TAdjustableAngle::setValue(int idx, TReal value)
{
	if (uidx == idx)
		fEstimatedValue.setRadiansValue(value);
	else
		throw std::logic_error("Invalid unknown index in parameter access. Angle " + getName());
}

void TAdjustableAngle::setEstimatedPrecision(int idx, TReal ep) {
	if (uidx == idx)
		fEstimatedPrecision.setRadiansValue(ep);
	else
		throw std::logic_error("Invalid unknown index in parameter access. Angle " + getName());
}

void TAdjustableAngle::reInitialise(){
	fEstimatedPrecision.setRadiansValue(0.0);
	fCorrection.setRadiansValue(0.0);
}


#if USE_SERIALIZER
void TAdjustableAngle::serialize(ObjectSerializer &obj) const
{
	TVAdjustableObject::serialize(obj);
	obj.addProperty("fName", fName);
	obj.addProperty("fProvisionalValue", fProvisionalValue.getRadiansValue());
	obj.addProperty("fEstimatedValue", fEstimatedValue.getRadiansValue());
	obj.addProperty("fCorrection", fCorrection.getRadiansValue());
	obj.addProperty("fEstimatedPrecision", fEstimatedPrecision.getRadiansValue());

	obj.addProperty("ifFixed", ifFixed);
	obj.addProperty("uidx", uidx);
}
#endif // USE_SERIALIZER
