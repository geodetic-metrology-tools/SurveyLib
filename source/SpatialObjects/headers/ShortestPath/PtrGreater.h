/*
 * SPDX-FileCopyrightText: 2025 CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

﻿#ifndef PTR_GREATER
#define PTR_GREATER

#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable:4786)
#endif


template<class T>
/*!\ingroup ShortestPath
	@{*/
struct PtrGreater
{
	bool operator()(T x, T y) const { return *y < *x; }
};
/*@}*/

#endif
