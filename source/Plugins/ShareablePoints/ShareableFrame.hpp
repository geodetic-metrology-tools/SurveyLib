/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEFRAME_HPP
#define SHAREABLEFRAME_HPP

#include <memory>
#include <string>
#include <vector>

#include "ShareablePoint.hpp"
#include "ShareablePosition.hpp"

struct ShareableParams;

/**
 * Group of points organized in a tree.
 *
 * ShareableFrame is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * A frame gather together a group of point, which coordinates are relative to the frame. This may be useful, for instance, for points that can only
 * move together.
 *
 * Frames are organized in a tree: you can have frames inside a frame. The leaves of the tree are the points. Thus, a frame, if it is not the root of
 * the tree, has a parent frame, and a relative position to it. This position is set thanks to a rotation and a translation from the parent frame.
 * A frame is a coordinate system that can either be fixed (i.e. known) with respect to its parent frame, or considered as free, meaning in this
 * last case that parts (or all) of its position parameters are flexible (the translation or rotation can have some ShareablePosition::isfreex
 * (or other) true).
 *
 * Finally, a frame is composed of:
 * - a parent frame
 * - a name
 * - a translation (ShareablePosition) from its parent frame
 * - a rotation (ShareablePosition) from its parent frame
 * - a scale from its parent frame
 * - a flexibility on the scale attribute
 * - a list of children frames
 * - a list of childen points
 * - the parameters for the list of points (shared by all the frames and the ShareablePointsList).
 *
 * Note that it is possible to get all the points from a frame and its children into a single vector thanks to the function getAllPoints().
 * The points from all the subframes are concatenated into one vector.
 *
 * @see shpoints, ShareablePoint, ShareablePointsList, ShareableParams, ShareablePosition
 */
class ShareableFrame
{
public:
	/** Constructor. */
	ShareableFrame(std::shared_ptr<ShareableParams> params, std::string name = "") noexcept : _name(std::move(name)), _params(std::move(params)) {}
	ShareableFrame(const ShareableFrame &) = delete; // can't copy (too heavy structure)
	ShareableFrame(ShareableFrame &&other) noexcept;
	ShareableFrame &operator=(const ShareableFrame &) = delete;
	ShareableFrame &operator=(ShareableFrame &&other) noexcept;

	/**
	 * Comparison operator.
	 * The parent and the params are not checked. If all the values are the same but the parent and/or the params, it returns true.
	 * Comparison is done on values, not on pointers.
	 */
	bool operator==(const ShareableFrame &a) const noexcept;
	/**
	 * Comparison operator.
	 * The parent and the params are not checked. If only the parent and/or the params differ, return false.
	 */
	bool operator!=(const ShareableFrame &a) const noexcept { return !(*this == a); }

	/** @return the parent frame */
	const ShareableFrame *getParentFrame() const noexcept { return _parentFrame; }
	/** @return the parent frame */
	ShareableFrame *getParentFrame() noexcept { return _parentFrame; }
	void setName(std::string name) noexcept { _name = std::move(name); }
	const std::string &getName() const noexcept { return _name; }

	/**
	 * Add the given frame as a child frame.
	 *
	 * If position is out of bound, it adds the frame at the end. If the frame was owned by another one before, it is removed from its previous parent.
	 *
	 * @warning The ownership over the frame is taken.
	 *
	 * @warning The parameters of the added frame is reset to have the same as the current one.
	 *
	 * @param frame the new frame
	 * @param position the insertion position
	 */
	void add(ShareableFrame *frame, size_t position = -1);
	/**
	 * Add a new empty frame.
	 *
	 * If position is out of bound, it adds the frame at the end.
	 *
	 * @param position the insertion position
	 * @return the created frame
	 */
	ShareableFrame &addFrame(size_t position = -1)
	{
		auto f = new ShareableFrame(_params);
		add(f, position);
		return *f;
	}
	/**
	 * Removes the frame.
	 *
	 * If position is out of bound, nothing happens (`nullptr` is returned).
	 *
	 * @warning The removed frame is returned as a temporary object. If you don't take it, it will be automatically destroyed.
	 *
	 * @param position the position of the frame to remove
	 * @return the removed frame, or nullptr
	 */
	std::unique_ptr<ShareableFrame> removeFrame(size_t position);
	/**
	 * Removes the frame.
	 *
	 * If the given frame is not a subframe, nothing happens (`nullptr` is returned).
	 *
	 * @warning The removed frame is returned as a temporary object. If you don't take it, it will be automatically destroyed.
	 *
	 * @param frame the frame to remove
	 * @return the removed frame, or nullptr
	 */
	std::unique_ptr<ShareableFrame> removeFrame(const ShareableFrame &frame);
	/** @return the frame */
	const ShareableFrame &getFrame(size_t position) const { return *_innerFrames[position]; }
	/** @return the frame */
	ShareableFrame &getFrame(size_t position) { return *_innerFrames[position]; }
	/** @return the vector of subframes */
	const std::vector<std::unique_ptr<ShareableFrame>> &getFrames() const noexcept { return _innerFrames; }
	/**
	 * Removes all subframes.
	 * @warning All frames are deleted.
	 */
	void clearFrames() noexcept { _innerFrames.clear(); }
	/** @return the number of children frames */
	size_t sizeFrames() const noexcept { return _innerFrames.size(); }

	/**
	 * Adds the given point.
	 *
	 * If position is out of bound, it adds the point at the end. If the point was owned by another frame before, it is removed from its previous parent.
	 *
	 * @warning The ownership over the point is taken.
	 *
	 * @param point the new frame
	 * @param position the insertion position
	 */
	void add(ShareablePoint *point, size_t position = -1);
	/**
	 * Add a new empty point.
	 *
	 * If position is out of bound, it adds the frame at the end.
	 *
	 * @param position the insertion position
	 * @return the created frame
	 */
	ShareablePoint &addPoint(size_t position = -1)
	{
		auto p = new ShareablePoint();
		add(p, position);
		return *p;
	}
	/**
	 * Removes the point.
	 *
	 * If position is out of bound, nothing happens (`nullptr` is returned).
	 *
	 * @warning The removed point is returned as a temporary object. If you don't take it, it will be automatically destroyed.
	 *
	 * @param position the position of the point to remove
	 * @return the removed point, or nullptr
	 */
	std::unique_ptr<ShareablePoint> removePoint(size_t position);
	/**
	 * Removes the point.
	 *
	 * If the given point is not in this frame, nothing happens (`nullptr` is returned).
	 *
	 * @warning The removed point is returned as a temporary object. If you don't take it, it will be automatically destroyed.
	 *
	 * @param point the frame to remove
	 * @return the removed frame, or nullptr
	 */
	std::unique_ptr<ShareablePoint> removePoint(const ShareablePoint &point);
	/** @return the point */
	const ShareablePoint &getPoint(size_t position) const { return *_points[position]; }
	/** @return the point */
	ShareablePoint &getPoint(size_t position) { return *_points[position]; }
	/** @return the vector of points */
	const std::vector<std::unique_ptr<ShareablePoint>> &getPoints() const noexcept { return _points; }
	/** @return a vector with all the points in this frame and its children. */
	std::vector<const ShareablePoint *> getAllPoints() const;
	/**
	 * Removes all points in this frame.
	 * @warning All points are deleted.
	 */
	void clearPoints() noexcept { _points.clear(); }
	/** @return the number of children points */
	size_t sizePoints() const noexcept { return _points.size(); }

	void setTranslation(ShareablePosition translation) noexcept { _translation = std::move(translation); }
	const ShareablePosition &getTranslation() const noexcept { return _translation; }
	ShareablePosition &getTranslation() noexcept { return _translation; }
	void setRotation(ShareablePosition rotation) noexcept { _rotation = std::move(rotation); }
	const ShareablePosition &getRotation() const noexcept { return _rotation; }
	ShareablePosition &getRotation() noexcept { return _rotation; }
	void setScale(double scale) noexcept { _scale = scale; }
	double getScale() const noexcept { return _scale; }
	void isFreeScale(bool free) noexcept { _isfreescale = free; }
	bool isFreeScale() const noexcept { return _isfreescale; }

	/**
	 * Change the parameters for this frame and all its children.
	 *
	 * @warning As it is a recursive method that will change the parameters for all the tree, it is a heavy function (o(n) with "n" the number of nodes in the tree).
	 * Wherever it is called in the tree, it will change all the nodes.
	 * Thus, it is better to change the values of the current parameters than change its instance. As the parameter is shared between all frames, the change will be
	 * done at no cost.
	 *
	 * @params the new parameters
	 */
	void setParams(std::shared_ptr<ShareableParams> params);
	const ShareableParams &getParams() const noexcept { return *_params; }
	/**
	 * Return the parameters.
	 *
	 * @warning The parameters are shared between all the frames of the tree. Changing one of its value will change it for all the frames of the tree.
	 *
	 * @return the parameters
	 */
	ShareableParams &getParams() noexcept { return *_params; }

private:
	/** The parent frame (null if the frame is the root). */
	ShareableFrame *_parentFrame = nullptr;
	/** The name of the frame. */
	std::string _name;
	/** The translation from the parent frame. */
	ShareablePosition _translation = {0, 0, 0, 0, 0, 0, false, false, false};
	/** The rotation from the parent frame. */
	ShareablePosition _rotation = {0, 0, 0, 0, 0, 0, false, false, false};
	/** Scale factor from the parent frame. */
	double _scale = 1;
	/** Tells if the scale is flexible (free, known). */
	bool _isfreescale = false;
	/** Frame children. */
	std::vector<std::unique_ptr<ShareableFrame>> _innerFrames;
	/** Point children. */
	std::vector<std::unique_ptr<ShareablePoint>> _points;
	/** Parameters of the points. */
	std::shared_ptr<ShareableParams> _params;
};

#endif // SHAREABLEFRAME_HPP
