// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include "ShareablePointsList.hpp"

#include "ShareableFrame.hpp"
#include "ShareableParams.hpp"

ShareablePointsList::ShareablePointsList(std::string title) :
	_title(std::move(title)),
	_params(new ShareableParams()),
	_rootFrame(std::make_unique<ShareableFrame>(_params))
{
}

ShareablePointsList::~ShareablePointsList() = default;

bool ShareablePointsList::operator==(const ShareablePointsList &a) const noexcept
{
	return _title == a._title && *_params == *a._params && *_rootFrame == *a._rootFrame;
}

std::unique_ptr<ShareableFrame> ShareablePointsList::setRootFrame(ShareableFrame *frame)
{
	if (_rootFrame.get() == frame)
		return nullptr;
	if (frame && frame->getParentFrame()) // we need to change its parent
		frame = frame->getParentFrame()->removeFrame(*frame).release();
	auto tmp = std::unique_ptr<ShareableFrame>(frame);

	// Swaps just the frames
	std::swap(tmp, _rootFrame);
	// Set params for ShareablePointsList, slight overhead as new params have to be created
	_params = std::make_shared<ShareableParams>(_rootFrame->getParams());
	_rootFrame->setParams(_params); // Propagate the pointer

	return tmp;
}
