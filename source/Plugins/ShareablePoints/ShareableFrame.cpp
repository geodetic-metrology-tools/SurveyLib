// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include "ShareableFrame.hpp"

#include <algorithm>
#include <iterator>

#include "ShareablePoint.hpp"

template<class T>
inline std::unique_ptr<T> remove(std::vector<std::unique_ptr<T>> &vector, size_t position)
{
	if (position >= vector.size())
		return nullptr;
	std::unique_ptr<T> old(std::move(vector[position]));
	vector.erase(std::begin(vector) + position);
	return old;
}

template<class T>
inline std::unique_ptr<T> remove(std::vector<std::unique_ptr<T>> &vector, const T &elt)
{
	for (auto it = std::cbegin(vector); it != std::cend(vector); it++)
	{
		if (it->get() == &elt)
			return remove(vector, std::distance(std::cbegin(vector), it));
	}
	return nullptr;
}

ShareableFrame::ShareableFrame(ShareableFrame &&other) noexcept
{
	*this = std::move(other);
}

ShareableFrame &ShareableFrame::operator=(ShareableFrame &&other) noexcept
{
	_parentFrame = other._parentFrame;
	_name = std::move(other._name);
	_translation = std::move(other._translation);
	_rotation = std::move(other._rotation);
	_scale = other._scale;
	_isfreescale = other._isfreescale;
	_params = std::move(other._params);
	/** Point children. */
	_points = std::move(other._points);
	for (auto &p : _points)
		p->parent = this;
	/** Frame children. */
	_innerFrames = std::move(other._innerFrames);
	for (auto &f : _innerFrames)
		f->_parentFrame = this;

	return *this;
}

bool ShareableFrame::operator==(const ShareableFrame &a) const noexcept
{
	bool result = _name == a._name &&
		_translation == a._translation && _rotation == a._rotation &&
		_scale == a._scale && _isfreescale == a._isfreescale &&
		_points.size() == a._points.size() && _innerFrames.size() == a._innerFrames.size();
	for (size_t i = 0; i < _points.size() && result; i++)
	{
		if (*_points[i] != *a._points[i])
			result = false;
	}
	for (size_t i = 0; i < _innerFrames.size() && result; i++)
	{
		if (*_innerFrames[i] != *a._innerFrames[i])
			result = false;
	}
	return result;
}

void ShareableFrame::add(ShareableFrame *frame, size_t position)
{
	if (!frame)
		return;
	const auto &it = (position >= _innerFrames.size()) ? std::cend(_innerFrames) : std::cbegin(_innerFrames) + position;

	// if the frame was owned, we remove it from its parent
	if (frame->_parentFrame)
		frame->_parentFrame->removeFrame(*frame).release();
	_innerFrames.emplace(it, frame);
	frame->_parentFrame = this;
	frame->_params = _params;
}

std::unique_ptr<ShareableFrame> ShareableFrame::removeFrame(size_t position)
{
	auto tmp = remove(_innerFrames, position);
	tmp->_parentFrame = nullptr;
	return tmp;
}

std::unique_ptr<ShareableFrame> ShareableFrame::removeFrame(const ShareableFrame &frame)
{
	auto tmp = remove(_innerFrames, frame);
	tmp->_parentFrame = nullptr;
	return tmp;
}

void ShareableFrame::add(ShareablePoint *point, size_t position)
{
	if (!point)
		return;
	const auto &it = (position >= _points.size()) ? std::cend(_points) : std::cbegin(_points) + position;

	// if the frame was owned, we remove it from its parent
	if (point->parent)
		point->parent->removePoint(*point).release();
	_points.emplace(it, point);
	point->parent = this;
}

std::unique_ptr<ShareablePoint> ShareableFrame::removePoint(size_t position)
{
	auto tmp = remove(_points, position);
	tmp->parent = nullptr;
	return tmp;
}

std::unique_ptr<ShareablePoint> ShareableFrame::removePoint(const ShareablePoint &point)
{
	auto tmp = remove(_points, point);
	tmp->parent = nullptr;
	return tmp;
}

std::vector<const ShareablePoint *> ShareableFrame::getAllPoints() const
{
	std::vector<const ShareablePoint *> tmp;
	tmp.reserve(_points.size());
	std::transform(std::cbegin(_points), std::cend(_points), std::back_inserter(tmp), [](auto &ptr) -> ShareablePoint * { return ptr.get(); });

	for (const auto &f : _innerFrames)
	{
		auto vector = f->getAllPoints();
		tmp.insert(std::end(tmp), std::make_move_iterator(std::begin(vector)), std::make_move_iterator(std::end(vector)));
	}

	return tmp;
}

void ShareableFrame::setParams(std::shared_ptr<ShareableParams> params)
{
	if (_params == params)
		return;
	_params = params;
	// change in children
	for (auto &f : _innerFrames)
	{
		if (f->_params != params)
			f->setParams(params);
	}
	// parent
	if (_parentFrame && _parentFrame->_params != params)
		_parentFrame->setParams(params);
}
