// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include "NumericUtils.h"

#include <stdexcept>
#include <limits>
#include <climits>

int svlTools::size_tToInt(size_t value)
{
	// Since size_t is, at least while writing this comment, in any relevant environment unsigned I only check upper boundary
	if (value <= static_cast<size_t>(INT_MAX))
		return static_cast<size_t>(value);
	else
		throw std::overflow_error("Integer overflow!");
}
