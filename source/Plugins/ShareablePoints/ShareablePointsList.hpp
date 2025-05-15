// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿

#ifndef SHAREABLEPOINTSLIST_HPP
#define SHAREABLEPOINTSLIST_HPP

#include <memory>
#include <string>

#include <ShareablePoints/ShareableFrame.hpp>

/**
 * @defgroup shpoints ShareablePoints
 *
 * Module to share points between SU software.
 *
 * The goal of this module is to have a common interface for a list of points, so we can easily share points between all the SU applications.
 *
 * A point (ShareablePoint) is an object that has a name and coordinates (ShareablePosition). The coordinates are expressed in a coordinate system
 * held by the parameters of the list (ShareableParams).
 *
 * Points are grouped together in frames (ShareableFrame). A frame is just a list of points, where the points are expressed in relative coordinates
 * to the position of the frame. A frame can contain points, or other frames, which creates a tree where nodes are frames and leaves are points.
 * A frame has a relative position from its parent expressed by a translation and a rotation.
 *
 * All these objects are usually stored in a main object: the ShareablePointsList. This class has a root frame, the root of the points tree. And it
 * also defines the parameters (coordinate system and all) that are shared between all frames.
 */

class ShareableFrame;
struct ShareableParams;

/**
 * Main class for describing a list of points.
 *
 * ShareablePointsList is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * This class represent the root of the points tree described by ShareableFrame and ShareablePoint. It is composed of:
 * - an optional title
 * - the root frame of the point tree
 * - the parameters shared with all the frames
 *
 * Notice that the parameters are the same for all the frames. Changing the parameters here will also automatically change the values
 * in all the tree.
 *
 * @see shpoints, ShareableFrame, ShareablePoint, ShareableParams
 */
class ShareablePointsList
{
public:
	ShareablePointsList(std::string title = "");
	~ShareablePointsList();
	ShareablePointsList(const ShareablePointsList &) = delete; // can't copy (too heavy structure)
	ShareablePointsList(ShareablePointsList &&) = default;
	ShareablePointsList &operator=(const ShareablePointsList &) = delete;
	ShareablePointsList &operator=(ShareablePointsList &&) = default;

	/** Comparison operator. Comparison is done on values, not on pointers. */
	bool operator==(const ShareablePointsList &a) const noexcept;
	/** Comparison operator. Comparison is done on values, not on pointers. */
	bool operator!=(const ShareablePointsList &a) const noexcept { return !(*this == a); }

	void setTitle(std::string title) noexcept { _title = std::move(title); }
	const std::string &getTitle() const noexcept { return _title; }
	const ShareableParams &getParams() const noexcept { return *_params; }
	/**
	 * Return the parameters.
	 *
	 * @warning The parameters are shared between all the frames of the tree. Changing one of its value will change it for all the frames of the tree.
	 *
	 * @return the parameters
	 */
	ShareableParams &getParams() noexcept { return *_params; }
	/** @warning This method shouldn't be used!!! It is only here for rare cases of optimization. */
	[[deprecated("This method shouldn't be used, except for rare cases of optimization.")]] std::shared_ptr<ShareableParams> &getParamsPointer() noexcept
	{
		return _params;
	}
	/**
	 * Change the root frame.
	 *
	 * By default, the root frame is `nullptr`.
	 * Whenever you change the value of the root frame, the previous root frame is returned as a temporary `unique_ptr`.
	 * If you don't catch it, all the previous frame tree will be automatically deleted.
	 *
	 * @note It is safe to use an inner frame of the previous tree as a new root: only the frames above will be deleted.
	 * @note If the frame given is already the root frame, it does nothing and returns `nullptr`.
	 * @warning Ownership is taken over the frame pointer.
	 *
	 * @param frame the new root frame.
	 * @return the previous root frame.
	 */
	std::unique_ptr<ShareableFrame> setRootFrame(ShareableFrame *frame);
	const ShareableFrame &getRootFrame() const { return *_rootFrame; }
	ShareableFrame &getRootFrame() { return *_rootFrame; }

private:
	/** If the project has a title, the title of the project. */
	std::string _title;
	/** The parameters of the points (shared with all the frames). */
	std::shared_ptr<ShareableParams> _params;
	/** The root frame. */
	std::unique_ptr<ShareableFrame> _rootFrame;
};

#endif // SHAREABLEPOINTSLIST_HPP
