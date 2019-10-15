/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef T_NOT_IN_LEP_GRID_EXCEPTION_493226D1_63D7_4e28_8900_47AF81CEADDB
#define T_NOT_IN_LEP_GRID_EXCEPTION_493226D1_63D7_4e28_8900_47AF81CEADDB

#include <stdexcept>

struct TNotInLepGridException : std::runtime_error
{
	explicit TNotInLepGridException(const std::string & error_message)
		: std::runtime_error(error_message) {}
};

#endif
