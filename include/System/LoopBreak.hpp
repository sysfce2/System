/*
 * Copyright (C) Nemirtingas
 * This file is part of System.
 *
 * System is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * System is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with System; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#pragma once

#define SYSTEM_LOOP_NAME_CAT_(x,y) x##y
#define SYSTEM_LOOP_NAME_CAT (x,y) SYSTEM_LOOP_NAME_CAT_(x,y)

#define SYSTEM_LOOP_NAME(name) \
	if (constexpr bool _namedloopInvalidBreakOrContinue = false) \
	{ \
		SYSTEM_LOOP_NAME_CAT(_namedloop_break_, name): break; \
		SYSTEM_LOOP_NAME_CAT(_namedloop_continue_, name): continue; \
	} \
	else

#define SYSTEM_LOOP_BREAK(name)    goto SYSTEM_LOOP_NAME_CAT(_namedloop_break_, name)
#define SYSTEM_LOOP_CONTINUE(name) goto SYSTEM_LOOP_NAME_CAT(_namedloop_continue_, name)