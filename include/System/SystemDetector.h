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

#if defined(WIN64) || defined(_WIN64) || defined(__MINGW64__)
    #define SYSTEM_OS_WINDOWS
    #define SYSTEM_ARCH_X64

#elif defined(WIN32) || defined(_WIN32) || defined(__MINGW32__)
    #define SYSTEM_OS_WINDOWS
    #define SYSTEM_ARCH_X86
#elif defined(__linux__) || defined(linux)
    #if defined(__x86_64__)
        #define SYSTEM_OS_LINUX
        #define SYSTEM_ARCH_X64
    #else
        #define SYSTEM_OS_LINUX
        #define SYSTEM_ARCH_X86
    #endif
#elif defined(__APPLE__)
    #if defined(__x86_64__)
        #define SYSTEM_OS_APPLE
        #define SYSTEM_ARCH_X64
    #else
        #define SYSTEM_OS_APPLE
        #define SYSTEM_ARCH_X86
    #endif
#else
    //#error "Unknown OS"
#endif

#ifdef __cplusplus
// Some constexpr for C++17 constexpr if.
namespace System {
    enum class OperatingSystem {
        Windows = 0,
        Linux   = 1,
        Apple   = 2,
    };

    enum class Arch {
        x86 = 0,
        x64 = 1,
    };

    static constexpr OperatingSystem os =
#if defined(SYSTEM_OS_WINDOWS)
    OperatingSystem::Windows;
#elif defined(SYSTEM_OS_LINUX)
    OperatingSystem::Linux;
#elif defined(SYSTEM_OS_APPLE)
    OperatingSystem::Apple;
#endif

    static constexpr Arch arch =
#if defined(SYSTEM_ARCH_X86)
    Arch::x86;
#elif defined(SYSTEM_ARCH_X64)
    Arch::x64;
#endif

}
#endif
