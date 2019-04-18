/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPOSITION_HPP
#define SHAREABLEPOSITION_HPP

#include <string>

/**
 * Holds the basic information about the position of a point.
 *
 * ShareablePosition is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * This class is a POD ([Plain Old Data](https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/7189821#7189821)). It holds
 * the 3D coordinates of a point, along with their accuracy (sigma).
 *
 * A position is composed of:
 * - 3D coordinates (`x`, `y`, `z`). Note that `z` may be interprated as `h`
 * - a confidence interval for all the coordinates (`sigmax`, `sigmay`, `sigmaz`)
 * - a freedom (flexibility) for all the coordinates (`isfreex`, `isfreey`, `isfreez`). This freedom is mainly used by LGC and tells if the coordinate can be changed
 * during the calculation
 *
 * You can create a ShareablePoint with an initializer list, as explained here: https://en.cppreference.com/w/cpp/language/aggregate_initialization (notice the benefits
 * of C++20, not available yet in MSVC 2017).
 * @code{cpp}
 * ShareablePosition sp1{ 0, 1, 2 }, sp2 = { 0, 1, 2, 3, 4, 5, true, false, true }, sp3{}, sp4;
 * // sp1: { x = 0, y = 1, z = 2, sigmax = sigmay = sigmaz = 0 , isfreex = isfreey = isfreez = false }
 * // sp2: { x = 0, y = 1, z = 2, sigmax = 3, sigmay = 4, sigmaz = 5, isfreex = true, isfreey = false, isfreez = true }
 * // sp3: { x = y = z = sigmax = sigmay = sigmaz = 0, isfreex = isfreey = isfreez = false }
 * // sp4: { x = y = z = sigmax = sigmay = sigmaz = isfreex = isfreey = isfreez = ??? }
 * @endcode
 *
 * It is possible to add or substract ShareablePositions. Note that in such a case, the freedom (flexibility) of the corrdinates is not changed, but the sigmas
 * are computed this way (no matter if it is an addition or a substraction):
 * @f[\sigma_{xresult} = \sqrt{\sigma_{x1}^2 + \sigma_{x2}^2}@f]
 *
 * @see shpoints, ShareablePoint
 */
struct ShareablePosition
{
	/** X coordinate */
	double x;
	/** Y coordinate */
	double y;
	/** Z or H coordinate */
	double z;
	/** Accuracy on X */
	double sigmax;
	/** Accuracy on Y */
	double sigmay;
	/** Accuracy on Z or H */
	double sigmaz;
	/** Tells if X coordinate is free or fixed. */
	bool isfreex;
	/** Tells if Y coordinate is free or fixed. */
	bool isfreey;
	/** Tells if Z coordinate is free or fixed. */
	bool isfreez;

	/** @return the opposit point (-x, -y, -z), with the same accuracy (same sigmas) */
	friend constexpr const ShareablePosition operator-(const ShareablePosition &sp) noexcept { return -1 * sp; }
	/**
	 * Return the substraction between this point and sp.
	 *
	 * @param sp1, sp2 the points to substract
	 * @return the substraction between 2 points (sigmas are changed too accroding to the formula in the class description)
	 */
	friend const ShareablePosition operator-(ShareablePosition sp1, const ShareablePosition &sp2) noexcept { return sp1 -= sp2; }
	/**
	 * Return the addition between this point and sp.
	 *
	 * @param sp1, sp2 the points to add
	 * @return the addition between 2 points (sigmas are changed too accroding to the formula in the class description)
	 */
	friend const ShareablePosition operator+(ShareablePosition sp1, const ShareablePosition &sp2) noexcept { return sp1 += sp2; }
	/**
	 * Return the multiplication between this point and a scalar.
	 *
	 * @param sp1 the points that will be multiplied
	 * @param f the scalar
	 * @return the multiplication between this point and a scalar.
	 */
	friend constexpr const ShareablePosition operator*(ShareablePosition sp1, double f) noexcept { return sp1 *= f; }
	/**
	 * Return the multiplication between this point and a scalar.
	 *
	 * @param f the scalar
	 * @param sp1 the points that will be multiplied
	 * @return the multiplication between this point and a scalar.
	 */
	friend constexpr const ShareablePosition operator*(double f, ShareablePosition sp1) noexcept { return sp1 *= f; }
	/**
	 * Return the division between this point and a scalar.
	 *
	 * @param f the scalar
	 * @return the division between this point and a scalar.
	 */
	friend constexpr const ShareablePosition operator/(ShareablePosition sp1, double f) noexcept { return sp1 /= f; }
	/**
	 * Adds sp to the current point.
	 *
	 * The sigmas of sp are added to the current point.
	 *
	 * @param sp the point to add
	 * @return the current point (this)
	 * @see operator+()
	 */
	const ShareablePosition &operator+=(const ShareablePosition &sp) noexcept;
	/**
	 * Substract sp to the current point.
	 *
	 * The sigmas of sp are added to the current point.
	 *
	 * @param sp the point to substract
	 * @return the current point (this)
	 * @see operator-()
	 */
	const ShareablePosition &operator-=(const ShareablePosition &sp) noexcept { return *this += (-sp); }
	/**
	 * Multiply this point with a scalar.
	 *
	 * @param f the scalar
	 * @return the current point (this)
	 * @see operator*()
	 */
	constexpr const ShareablePosition &operator*=(double f) noexcept
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	/**
	 * Divide this point with a scalar.
	 *
	 * @param f the scalar
	 * @return the current point (this)
	 * @see operator/()
	 */
	constexpr const ShareablePosition &operator/=(double f) noexcept { return *this *= (1 / f); }

	/**
	 * Compare the points.
	 *
	 * All values must be identical to be considered as equal (coordinates, sigmas and flexibility).
	 *
	 * @return true if equals, false otherwise
	 */
	constexpr bool operator==(const ShareablePosition &sp) const noexcept
	{
		return x == sp.x && y == sp.y && z == sp.z
			&& sigmax == sp.sigmax && sigmay == sp.sigmay && sigmaz == sp.sigmaz
			&& isfreex == sp.isfreex && isfreey == sp.isfreey && isfreez == sp.isfreez;
	}
	/**
	 * Compares the points.
	 *
	 * @see operator==()
	 */
	constexpr bool operator!=(const ShareablePosition &sp) const noexcept { return !(*this == sp); }

	/**
	 * Return a string representation of the point.
	 *
	 * The point is written on one line with this format:
	 * @code
	 * x: x.xxxxxx (+- sx.xxxxxx),	y: y.yyyyyy (+- sy.yyyyyy),	z: z.zzzzzz (+- sz.zzzzzz)
	 * @endcode
	 * If the coordinate is fixed, it is prefixed with a `*`.
	 *
	 * @param precision the precision needed for the floating coordinates (default is 6)
	 * @return a string representation of the current point
	 */
	std::string to_string(const int precision = 6) const;
};

#endif // SHAREABLEPOSITION_HPP
