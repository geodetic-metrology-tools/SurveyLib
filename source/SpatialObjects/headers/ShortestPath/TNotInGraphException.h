/*
© Copyright CERN 2000-2017. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef T_NOT_IN_GRAPH_EXCEPTION_89670E6B_13FA_4ec4_A91E_C7E925AAF765
#define T_NOT_IN_GRAPH_EXCEPTION_89670E6B_13FA_4ec4_A91E_C7E925AAF765

#include <stdexcept>

struct TNotInGraphException : std::runtime_error
{
	explicit TNotInGraphException(const std::string & error_message)
		: std::runtime_error(error_message) {}
};

#endif
