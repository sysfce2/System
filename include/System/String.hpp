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
 * License along with the System; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <cstdint>
#include <iterator>

namespace System {
namespace String {

void LeftTrim(std::string& str);

void RightTrim(std::string& str);

void Trim(std::string& str);

std::string CopyLeftTrim(std::string const& str);

std::string CopyRightTrim(std::string const& str);

std::string CopyTrim(std::string const& str);

void ToLower(std::string& str);

void ToLower(char* str);

std::string CopyToLower(std::string const& str);

std::string CopyToLower(const char* str);

void ToUpper(std::string str);

void ToUpper(char* str);

std::string CopyUpper(std::string const& str);

std::string CopyUpper(const char* str);

template<typename IteratorType>
inline std::string Join(IteratorType begin, IteratorType end, const std::string& sep)
{
    std::string res;

    if (begin != end)
        res += *begin++;

    while (begin != end)
    {
        res += sep;
        res += *begin++;
    }

    return res;
}

template<typename T>
inline std::string Join(T const& container, const std::string& sep)
{
    return Join(std::begin(container), std::end(container), sep);
}

// Clone a string allocated with the "new" operator, if str is nullptr, an empty string ("") will be returned, NOT nullptr !
char* CloneString(const char* str);

char* CloneString(std::string const& str);

template<size_t N>
inline size_t CopyString(std::string const& src, char(&dst)[N])
{
    return CopyString(src, dst, N);
}

// Will always end the C-String with a null char.
size_t CopyString(std::string const& src, char* dst, size_t dst_size);

}
}

#include "StringView.hpp"
#include "StringSwitch.hpp"