/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
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

class ShareableFrame
{
public:
	ShareableFrame(std::shared_ptr<ShareableParams> params, const std::string& name="") : _params(params), _name(name) {}
	ShareableFrame(const ShareableFrame&) = delete; // can't copy (too heavy structure)
	ShareableFrame(const ShareableFrame&&) = delete;
	ShareableFrame& operator=(const ShareableFrame&) = delete;
	ShareableFrame& operator=(const ShareableFrame&&) = delete;

	/** @return the parent frame */
	const ShareableFrame* getParentFrame() const noexcept { return _parentFrame; }
	/** @return the parent frame */
	ShareableFrame* getParentFrame() noexcept { return _parentFrame; }
	void setName(const std::string& name) { _name = name; }
	const std::string& getName() const noexcept { return _name; }

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
	void add(ShareableFrame* frame, size_t position = -1);
	/**
	 * Add a new empty frame.
	 *
	 * If position is out of bound, it adds the frame at the end.
	 *
	 * @param position the insertion position
	 * @return the created frame
	 */
	ShareableFrame& addFrame(size_t position = -1) { auto f = new ShareableFrame(_params); add(f, position); return *f; }
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
	std::unique_ptr<ShareableFrame> removeFrame(const ShareableFrame& frame);
	/** @return the frame */
	const ShareableFrame& getFrame(size_t position) const { return *_innerFrames[position]; }
	/** @return the frame */
	ShareableFrame& getFrame(size_t position) { return *_innerFrames[position]; }
	/** @return the vector of subframes */
	const std::vector<std::unique_ptr<ShareableFrame>>& getFrames() const noexcept { return _innerFrames; }
	/** Removes all subframes. */
	void clearFrames() noexcept { _innerFrames.clear(); }

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
	void add(ShareablePoint* point, size_t position = -1);
	/**
	 * Add a new empty frame.
	 *
	 * If position is out of bound, it adds the frame at the end.
	 *
	 * @param position the insertion position
	 * @return the created frame
	 */
	ShareablePoint& addPoint(size_t position = -1) { auto p = new ShareablePoint(); add(p, position); return *p; }
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
	std::unique_ptr<ShareablePoint> removePoint(const ShareablePoint& point);
	/** @return the point */
	const ShareablePoint& getPoint(size_t position) const { return *_points[position]; }
	/** @return the point */
	ShareablePoint& getPoint(size_t position) { return *_points[position]; }
	/** @return the vector of points */
	const std::vector<std::unique_ptr<ShareablePoint>>& getPoints() const noexcept { return _points; }
	/** Removes all points in this frame. */
	void clearPoints() noexcept { _points.clear(); }

	void setTranslation(const ShareablePosition& translation) noexcept { _translation = translation; }
	const ShareablePosition& getTranslation() const noexcept { return _translation; }
	ShareablePosition& getTranslation() noexcept { return _translation; }
	void setRotation(const ShareablePosition& rotation) noexcept { _rotation = rotation; }
	const ShareablePosition& getRotation() const noexcept { return _rotation; }
	ShareablePosition& getRotation() noexcept { return _rotation; }

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
	const ShareableParams& getParams() const noexcept { return *_params; }
	/**
	 * Return the parameters.
	 *
	 * @warning The parameters are shared between all the frames of the tree. Changing one of its value will change it for all the frames of the tree.
	 *
	 * @return the parameters
	 */
	ShareableParams& getParams() noexcept { return *_params; }

private:
	ShareableFrame * _parentFrame = nullptr;
	std::string _name;
	ShareablePosition _translation = { 0, 0, 0, 0, 0, 0 };
	ShareablePosition _rotation = { 0, 0, 0, 0, 0, 0 };
	std::vector<std::unique_ptr<ShareableFrame>> _innerFrames;
	std::vector<std::unique_ptr<ShareablePoint>> _points;
	std::shared_ptr<ShareableParams> _params;
};

#endif // SHAREABLEFRAME_HPP
