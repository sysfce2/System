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

#include "System_internals.h"

#include <System/String.hpp>

#include <string.h>
#include <algorithm>

namespace System {
namespace String {

namespace details {
    template<typename T>
    static inline void ToLower(T begin, T end)
    {
        std::transform(begin, end, begin, [](char c)
        {
            return std::tolower((unsigned char)c);
        });
    }

    template<typename T>
    static inline void ToUpper(T begin, T end)
    {
        std::transform(begin, end, begin, [](char c)
        {
            return std::toupper((unsigned char)c);
        });
    }
}

void LeftTrim(std::string& str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](const char& c)
    {
        return !std::isspace((unsigned char)c);
    }));
}

void RightTrim(std::string& str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [](const char& c)
    {
        return !std::isspace((unsigned char)c);
    }).base(), str.end());
}

void Trim(std::string& str)
{
    LeftTrim(str);
    RightTrim(str);
}

std::string CopyLeftTrim(std::string const& str)
{
    std::string r(str);
    LeftTrim(r);
    return r;
}

std::string CopyRightTrim(std::string const& str)
{
    std::string r(str);
    RightTrim(r);
    return r;
}

void ToLower(char* str, size_t len)
{
    while (len--)
    {
        unsigned char c = (unsigned char)*str;
        *str++ = std::tolower(c);
    }
}

char* CloneString(System::StringView src)
{
    size_t len = src.length() + 1;
    char* res = new char[len];
    memcpy(res, src.data(), len);
    return res;
}

size_t CopyString(System::StringView src, char* dst, size_t dst_size)
{
    size_t written = 0;
    if (dst != nullptr && dst_size > 0)
    {
        written = src.length() > dst_size ? dst_size - 1 : src.length();
        memcpy(dst, src.data(), written);
        dst[written] = '\0';
    }
    return written;
}

}// namespace details

}// namespace String
}// namespace System