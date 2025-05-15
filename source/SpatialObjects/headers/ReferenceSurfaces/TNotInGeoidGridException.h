/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿
#ifndef T_NOT_IN_GEOID_GRID_EXCEPTION
#define T_NOT_IN_GEOID_GRID_EXCEPTION

#include <stdexcept>

struct TNotInGeoidGridException : std::runtime_error
{
	explicit TNotInGeoidGridException(const std::string &error_message) : std::runtime_error(error_message) {}
};

#endif
