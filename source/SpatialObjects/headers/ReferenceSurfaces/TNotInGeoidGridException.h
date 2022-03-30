/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
#ifndef T_NOT_IN_GEOID_GRID_EXCEPTION
#define T_NOT_IN_GEOID_GRID_EXCEPTION

#include <stdexcept>

struct TNotInGeoidGridException : std::runtime_error
{
	explicit TNotInGeoidGridException(const std::string &error_message) : std::runtime_error(error_message) {}
};

#endif
