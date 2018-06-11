#include "ShareablePosition.hpp"

#include <iomanip>
#include <sstream>

constexpr ShareablePosition ShareablePosition::operator+(const ShareablePosition & sp) const noexcept
{
	return ShareablePosition{
		x + sp.x,
		y + sp.y,
		z + sp.z,
		sigmax + sp.sigmax,
		sigmay + sp.sigmay,
		sigmaz + sp.sigmaz
	};
}

constexpr ShareablePosition & ShareablePosition::operator+=(const ShareablePosition & sp) noexcept
{
	x += sp.x;
	y += sp.y;
	z += sp.z;
	sigmax += sp.sigmax;
	sigmay += sp.sigmay;
	sigmaz += sp.sigmaz;
	return *this;
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
