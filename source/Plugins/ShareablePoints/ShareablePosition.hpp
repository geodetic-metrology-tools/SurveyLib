/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPOSITION_HPP
#define SHAREABLEPOSITION_HPP

#include <string>

#include "Quad.h"

/**
 * Holds the basic information about the position of a point.
 *
 * Thi class is a POD ([Plain Old Data](https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/7189821#7189821)). It holds the
 * 3D coordinates of a point, along with their accuracy (sigma).
 *
 * You can create a ShareablePoint with an initializer list, as explained here: https://en.cppreference.com/w/cpp/language/aggregate_initialization (notice the benefits
 * of C++20, not available yet in MSVC 2017).
 * @code{cpp}
 * ShareablePoint sp1{0, 1, 2}, sp2 = {0, 1, 2, 3, 4, 5}, sp3;
 * // sp1: { x = 0, y = 1, z = 2, sigmax = sigmay = sigmaz = 0 }
 * // sp2: { x = 0, y = 1, z = 2, sigmax = 3, sigmay = 4, sigmaz = 5 }
 * // sp3: { x = y = z = sigmax = sigmay = sigmaz = ??? }
 * @endcode
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
	constexpr ShareablePosition operator-() const noexcept { return ShareablePosition{ -x, -y, -z, sigmax, sigmay, sigmaz }; }
	/**
	 * Return the substraction between this point and sp.
	 *
	 * The new point has its sigmas added.
	 *
	 * @param sp the other point to substract
	 * @return the substraction between 2 points (sigmas are added)
	 */
	constexpr ShareablePosition operator-(const ShareablePosition& sp) const noexcept { return operator+(-sp); }
	/**
	 * Return the addition between this point and sp.
	 *
	 * The new point has its sigmas added.
	 *
	 * @param sp the other point to add
	 * @return the addition between 2 points (sigmas are added)
	 */
	constexpr ShareablePosition operator+(const ShareablePosition& sp) const noexcept;
	/**
	 * Adds sp to the current point.
	 *
	 * The sigmas of sp are added to the current point.
	 *
	 * @param sp the point to add
	 * @return the current point (this)
	 */
	constexpr ShareablePosition& operator+=(const ShareablePosition& sp) noexcept;
	/**
	 * Substract sp to the current point.
	 *
	 * The sigmas of sp are added to the current point.
	 *
	 * @param sp the point to substract
	 * @return the current point (this)
	 */
	constexpr ShareablePosition& operator-=(const ShareablePosition& sp) noexcept { return operator+=(-sp); }

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

#endif // SHAREABLEPOSITION_HPP
