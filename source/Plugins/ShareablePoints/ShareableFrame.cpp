#include "ShareableFrame.hpp"

#include "ShareablePoint.hpp"

template<class T>
inline std::unique_ptr<T> remove(std::vector<std::unique_ptr<T>>& vector, size_t position)
{
	if (position >= vector.size())
		return nullptr;
	std::unique_ptr<T> old(std::move(vector[position]));
	vector.erase(std::begin(vector) + position);
	return old;
}

template<class T>
inline std::unique_ptr<T> remove(std::vector<std::unique_ptr<T>>& vector, const T & elt)
{
	for (auto it = std::cbegin(vector); it != std::cend(vector); it++)
	{
		if (it->get() == &elt)
			return remove(vector, std::distance(std::cbegin(vector), it));
	}
	return nullptr;
}

void ShareableFrame::add(ShareableFrame* frame, size_t position)
{
	if (!frame)
		return;
	const auto& it = (position >= _innerFrames.size()) ? std::cend(_innerFrames) : std::cbegin(_innerFrames) + position;

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

std::unique_ptr<ShareableFrame> ShareableFrame::removeFrame(const ShareableFrame & frame)
{
	auto tmp = remove(_innerFrames, frame);
	tmp->_parentFrame = nullptr;
	return tmp;
}

void ShareableFrame::add(ShareablePoint* point, size_t position)
{
	if (!point)
		return;
	const auto& it = (position >= _points.size()) ? std::cend(_points) : std::cbegin(_points) + position;

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

std::unique_ptr<ShareablePoint> ShareableFrame::removePoint(const ShareablePoint & point)
{
	auto tmp = remove(_points, point);
	tmp->parent = nullptr;
	return tmp;
}

void ShareableFrame::setParams(std::shared_ptr<ShareableParams> params)
{
	if (_params == params)
		return;
	_params = params;
	// change in children
	for (auto& f : _innerFrames)
	{
		if (f->_params != params)
			f->setParams(params);
	}
	// parent
	if (_parentFrame->_params != params)
		_parentFrame->setParams(params);
}
