/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEPOINT_HPP
#define SHAREABLEPOINT_HPP

#include <string>

#include "ShareableExtraInfo.hpp"
#include "ShareablePosition.hpp"

class ShareableFrame;

struct ShareablePoint
{
	/** default constructor */
	ShareablePoint() = default;
	/**
	 * Constructor
	 * @see name, position, inlineComment, headerComment
	 */
	ShareablePoint(const std::string& name, const ShareablePosition& position, const std::string& inlineComment = "", const std::string& headerComment = "") :
		name(name), position(position), inlineComment(inlineComment), headerComment(headerComment) {}

	/** The frame where the point is. */
	ShareableFrame * parent = nullptr;
	/** The name of the point. */
	std::string name;
	/** The position (coordinates) of the point. By default (0, 0, 0) */
	ShareablePosition position = { 0, 0, 0, 0, 0, 0 };
	/** The inline comment associated to the point if it exists. */
	std::string inlineComment;
	/** The header comment (comment right before in the file) associated to the point if it exists. */
	std::string headerComment;
	/** Extra infos if there are. */
	ShareableExtraInfos extraInfos;
	/** Tells it the point is activated (should be part of the computations). */
	bool active = true;
};

#endif // SHAREABLEPOINT_HPP
