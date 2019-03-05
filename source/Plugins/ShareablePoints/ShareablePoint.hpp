/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPOINT_HPP
#define SHAREABLEPOINT_HPP

#include <string>

#include "ShareableExtraInfos.hpp"
#include "ShareablePosition.hpp"

class ShareableFrame;

/**
 * A point with all the attributes needed by SU applications.
 *
 * ShareablePoint is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * A point has:
 * - a name
 * - a position (ShareablePosition)
 * - optional comments (inline or header)
 * - an active status
 * - optional extra infos (ShareableExtraInfos)
 * - a parent frame (ShareableFrame)
 *
 * Note that like the ShareablePosition, you can initialize this class with initializer lists as explained here: https://en.cppreference.com/w/cpp/language/aggregate_initialization
 * (notice the benefits of C++20, not available yet in MSVC 2017).
 * @code{cpp}
 * ShareablePoint sp1{ "name" }, sp2 = { "name", { 1, 2, 3 }, "inline", "header", false }, sp3;
 * // sp1: { name = "name", position = { 0, 0, 0, 0, 0, 0 }, active = true } // everything else is emmpty / null
 * // sp2: { name = "name", position = { 1, 2, 3, 0, 0, 0 }, inlinecomment = "inline", headerComment = "header", active = false }
 * // sp3: all default values
 * @endcode
 *
 * A point is generally part of a frame (ShareableFrame). This information is stored in the `parent` attribute.
 *
 * If the point has some specific configuration that comes from the application and that is not storeable in the provided attributes,
 * you can store them in the `extraInfos` ShareableExtraInfos.
 *
 * @see shpoints, ShareableExtraInfos, ShareablePosition, ShareableFrame
 */
struct ShareablePoint
{
	/** The name of the point. */
	std::string name = "";
	/** The position (coordinates) of the point. By default (0, 0, 0) */
	ShareablePosition position = { 0, 0, 0, 0, 0, 0, false, false, false };
	/** The inline comment associated to the point if it exists. */
	std::string inlineComment = "";
	/** The header comment (comment right before in the file) associated to the point if it exists. */
	std::string headerComment = "";
	/** Tells it the point is activated (should be part of the computations). */
	bool active = true;
	/** Extra infos if there are. */
	ShareableExtraInfos extraInfos;
	/** The frame where the point is. */
	ShareableFrame * parent = nullptr;

	/**
	 * Comparison operator.
	 * The parent is not checked. If all the values are the same but the parent, it returns true.
	 */
	bool operator==(const ShareablePoint& a) const noexcept
	{
		return name == a.name &&
			position == a.position &&
			inlineComment == a.inlineComment && headerComment == a.headerComment &&
			active == a.active &&
			extraInfos == a.extraInfos;
	}
	/**
	* Comparison operator.
	* The parent is not checked. If only the parent differs, return false.
	*/
	bool operator!=(const ShareablePoint& a) const noexcept { return !(*this == a); }
};

#endif // SHAREABLEPOINT_HPP
