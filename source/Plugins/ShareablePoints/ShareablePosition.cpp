#include "ShareablePosition.hpp"

#include <iomanip>
#include <sstream>

const ShareablePosition ShareablePosition::operator+(const ShareablePosition & sp) const noexcept
{
	return ShareablePosition{
		x + sp.x,
		y + sp.y,
		z + sp.z,
		std::sqrt(std::pow(sigmax, 2) + std::pow(sp.sigmax, 2)),
		std::sqrt(std::pow(sigmay, 2) + std::pow(sp.sigmay, 2)),
		std::sqrt(std::pow(sigmaz, 2) + std::pow(sp.sigmaz, 2))
	};
}

std::string ShareablePosition::to_string(const int precision) const
{
	std::ostringstream str;
	str << std::setprecision(precision) << std::fixed;
	str << "x: " << x << " (+- " << sigmax << "),\t"
		<< "y: " << y << " (+- " << sigmay << "),\t"
		<< "z: " << z << " (+- " << sigmaz << ")";
	return str.str();
}
