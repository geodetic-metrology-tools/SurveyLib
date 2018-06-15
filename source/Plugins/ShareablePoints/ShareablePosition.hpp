/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPOSITION_HPP
#define SHAREABLEPOSITION_HPP

#include <cmath>
#include <string>

#include "Quad.h"

/**
 * Holds the basic information about the position of a point.
 *
 * ShareablePosition is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * This class is a POD ([Plain Old Data](https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/7189821#7189821)). It holds the
 * 3D coordinates of a point, along with their accuracy (sigma).
 *
 * You can create a ShareablePoint with an initializer list, as explained here: https://en.cppreference.com/w/cpp/language/aggregate_initialization (notice the benefits
 * of C++20, not available yet in MSVC 2017).
 * @code{cpp}
 * ShareablePosition sp1{ 0, 1, 2 }, sp2 = { 0, 1, 2, 3, 4, 5 }, sp3{}, sp4;
 * // sp1: { x = 0, y = 1, z = 2, sigmax = sigmay = sigmaz = 0 }
 * // sp2: { x = 0, y = 1, z = 2, sigmax = 3, sigmay = 4, sigmaz = 5 }
 * // sp3: { x = y = z = sigmax = sigmay = sigmaz = 0 }
 * // sp4: { x = y = z = sigmax = sigmay = sigmaz = ??? }
 * @endcode
 *
 * It is possible to add or substract ShareablePositions. Note that in such a case, the sigmas are computed this way (no matter if it is an addition
 * or a substraction):
 * @f[\sigma_{xresult} = \sqrt{\sigma_{x1}^2 + \sigma_{x2}^2}@f]
 *
 * @see shpoints, ShareablePoint
 */
struct ShareablePosition
{
	/** X coordinate */
	TReal x;
	/** Y coordinate */
	TReal y;
	/** Z or H coordinate */
	TReal z;
	/** Accuracy on X */
	TReal sigmax;
	/** Accuracy on Y */
	TReal sigmay;
	/** Accuracy on Z or H */
	TReal sigmaz;

	/** @return the opposit point (-x, -y, -z), with the same accuracy (same sigmas) */
	constexpr const ShareablePosition operator-() const noexcept { return ShareablePosition{ -x, -y, -z, sigmax, sigmay, sigmaz }; }
	/**
	 * Return the substraction between this point and sp.
	 *
	 * @param sp the other point to substract
	 * @return the substraction between 2 points (sigmas are changed too accroding to the formula in the class description)
	 */
	const ShareablePosition operator-(const ShareablePosition& sp) const noexcept { return operator+(-sp); }
	/**
	 * Return the addition between this point and sp.
	 *
	 * @param sp the other point to add
	 * @return the addition between 2 points (sigmas are changed too accroding to the formula in the class description)
	 */
	const ShareablePosition operator+(const ShareablePosition& sp) const noexcept;
	/**
	 * Return the multiplication between this point and a scalar.
	 *
	 * @param f the scalar
	 * @return the multiplication between this point and a scalar.
	 */
	constexpr const ShareablePosition operator*(TReal f) const noexcept { return ShareablePosition{ x * f, y * f, z * f, sigmax, sigmay, sigmaz }; }
	/**
	 * Return the division between this point and a scalar.
	 *
	 * @param f the scalar
	 * @return the division between this point and a scalar.
	 */
	constexpr const ShareablePosition operator/(TReal f) const noexcept { return operator*(1 / f); }
	/**
	 * Adds sp to the current point.
	 *
	 * The sigmas of sp are added to the current point.
	 *
	 * @param sp the point to add
	 * @return the current point (this)
	 * @see operator+()
	 */
	const ShareablePosition& operator+=(const ShareablePosition& sp) noexcept { *this = operator+(sp); return *this; }
	/**
	 * Substract sp to the current point.
	 *
	 * The sigmas of sp are added to the current point.
	 *
	 * @param sp the point to substract
	 * @return the current point (this)
	 * @see operator-()
	 */
	const ShareablePosition& operator-=(const ShareablePosition& sp) noexcept { return operator+=(-sp); }
	/**
	 * Multiply this point with a scalar.
	 *
	 * @param f the scalar
	 * @return the current point (this)
	 * @see operator*()
	 */
	constexpr const ShareablePosition& operator*=(TReal f) noexcept { *this = operator*(f); return *this; }
	/**
	 * Divide this point with a scalar.
	 *
	 * @param f the scalar
	 * @return the current point (this)
	 * @see operator/()
	 */
	constexpr const ShareablePosition& operator/=(TReal f) noexcept { return operator*=(1 / f); }

	/**
	 * Compare the points.
	 *
	 * All values must be identical to be considered as equal (coordinates and sigmas).
	 *
	 * @return true if equals, false otherwise
	 */
	constexpr bool operator==(const ShareablePosition& sp) const noexcept { return x == sp.x && y == sp.y && z == sp.z && sigmax == sp.sigmax && sigmay == sp.sigmay && sigmaz == sp.sigmaz; }
	/**
	 * Compares the points.
	 *
	 * @see operator==()
	 */
	constexpr bool operator!=(const ShareablePosition& sp) const noexcept { return !operator==(sp); }

	/**
	 * Return a string representation of the point.
	 *
	 * The point is written on one line with this format:
	 * @code
	 * x: x.xxxxxx (+- sx.xxxxxx),	y: y.yyyyyy (+- sy.yyyyyy),	z: z.zzzzzz (+- sz.zzzzzz)
	 * @endcode
	 *
	 * @param precision the precision needed for the floating coordinates (default is 6)
	 * @return a string representation of the current point
	 */
	std::string to_string(const int precision = 6) const;
};

/** @see ShareablePosition::operator*() */
constexpr const ShareablePosition operator*(TReal f, const ShareablePosition& sp) noexcept { return sp * f; }

#endif // SHAREABLEPOSITION_HPP
