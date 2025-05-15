// SPDX-FileCopyrightText: 2025 CERN

// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

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
		throw std::logic_error("Trying to assign unknown index to a fixed angle. Angle " + getName());
	uidx = idx;
}

void TAdjustableAngle::setCorrection(int idx, TReal value) {
	if (uidx == idx){
		fCorrection.setRadiansValue(value);
		fEstimatedValue.setRadiansValue(fEstimatedValue.getRadiansValue() + value);
	}
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
