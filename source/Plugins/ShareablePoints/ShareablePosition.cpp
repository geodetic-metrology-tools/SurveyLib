#include "ShareablePosition.hpp"

#include <iomanip>
#include <sstream>

const ShareablePosition& ShareablePosition::operator+=(const ShareablePosition & sp) noexcept
{
	x += sp.x;
	y += sp.y;
	z += sp.z;
	sigmax = std::sqrt(std::pow(sigmax, 2) + std::pow(sp.sigmax, 2));
	sigmay = std::sqrt(std::pow(sigmay, 2) + std::pow(sp.sigmay, 2));
	sigmaz = std::sqrt(std::pow(sigmaz, 2) + std::pow(sp.sigmaz, 2));
	return *this;
}

std::string ShareablePosition::to_string(const int precision) const
{
	std::ostringstream str;
	str << std::setprecision(precision) << std::fixed;
	str << (isfreex ? "" : "*") << "x: " << x << " (+- " << sigmax << "),\t"
		<< (isfreey ? "" : "*") << "y: " << y << " (+- " << sigmay << "),\t"
		<< (isfreez ? "" : "*") << "z: " << z << " (+- " << sigmaz << ")";
	return str.str();
}
