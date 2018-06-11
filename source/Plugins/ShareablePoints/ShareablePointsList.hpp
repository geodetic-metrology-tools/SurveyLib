/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPOINTSLIST_HPP
#define SHAREABLEPOINTSLIST_HPP

#include <memory>
#include <string>

class ShareableFrame;
struct ShareableParams;

class ShareablePointsList
{
public:
	ShareablePointsList(const std::string& titre);

	void setTitre(const std::string& titre) { _titre = titre; }
	const std::string& getTitre() const noexcept { return _titre; }
	const ShareableParams& getParams() const noexcept { return *_params; }
	/**
	 * Return the parameters.
	 *
	 * @warning The parameters are shared between all the frames of the tree. Changing one of its value will change it for all the frames of the tree.
	 *
	 * @return the parameters
	 */
	ShareableParams& getParams() noexcept { return *_params; }
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
	const ShareableFrame& getRootFrame() const { return *_rootFrame; }
	ShareableFrame& getRootFrame() { return *_rootFrame; }


private:
	/** If the project has a title, the title of the project. */
	std::string _titre;
	/** The parameters of the points (shared with all the frames). */
	std::shared_ptr<ShareableParams> _params;
	/** The root frame. */
	std::unique_ptr<ShareableFrame> _rootFrame;
};

#endif // SHAREABLEPOINTSLIST_HPP
