// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#if !defined(__linux__) && defined(UIPlugins_EXPORT)
	# define SULIB_SHARED_EXPORT __declspec(dllexport)
#elif !defined(__linux__) &&  defined(UIPlugins_IMPORT)
	# define SULIB_SHARED_EXPORT __declspec(dllimport)
#endif

#ifndef SULIB_SHARED_EXPORT
	# define SULIB_SHARED_EXPORT
#endif
