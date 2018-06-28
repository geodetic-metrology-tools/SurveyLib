#include "ShareablePointsList.hpp"

#include "ShareableFrame.hpp"
#include "ShareableParams.hpp"

ShareablePointsList::ShareablePointsList(const std::string & title) :
	_title(title),
	_params(new ShareableParams()),
	_rootFrame(std::make_unique<ShareableFrame>(_params))
{
}

std::unique_ptr<ShareableFrame> ShareablePointsList::setRootFrame(ShareableFrame * frame)
{
	if (_rootFrame.get() == frame)
		return nullptr;
	if (frame && frame->getParentFrame()) // we need to change its parent
		frame = frame->getParentFrame()->removeFrame(*frame).release();
	if (frame)
		frame->setParams(_params);

	auto tmp = std::unique_ptr<ShareableFrame>(frame);
	std::swap(tmp, _rootFrame);
	return tmp;
}
