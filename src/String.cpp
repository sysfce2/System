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

std::string CopyTrim(std::string const& str)
{
    std::string r(str);
    LeftTrim(r);
    RightTrim(r);
    return r;
}

void ToLower(std::string& str)
{
    details::ToLower(str.begin(), str.end());
}

void ToLower(char* str)
{
    details::ToLower(str, str + strlen(str));
}

std::string CopyToLower(std::string const& str)
{
    std::string r(str);
    details::ToLower(r.begin(), r.end());
    return r;
}

std::string CopyToLower(const char* str)
{
    return CopyToLower(std::string{ str });
}

void ToUpper(std::string str)
{
    details::ToUpper(str.begin(), str.end());
}

void ToUpper(char* str)
{
    details::ToUpper(str, str + strlen(str));
}

std::string CopyUpper(std::string const& str)
{
    std::string r(str);
    details::ToUpper(r.begin(), r.end());
    return r;
}

std::string CopyUpper(const char* str)
{
    return CopyUpper(std::string{ str });
}

// Clone a string allocated with the "new" operator, if str is nullptr, an empty string ("") will be returned, NOT nullptr !
char* CloneString(const char* str)
{
    if (str == nullptr)
    {
        char* res = new char[1];
        res[0] = '\0';
        return res;
    }

    size_t len = strlen(str) + 1;
    char* res = new char[len];
    memcpy(res, str, len);
    return res;
}

char* CloneString(std::string const& str)
{
    size_t len = str.length() + 1;
    char* res = new char[len];
    memcpy(res, str.c_str(), len);
    return res;
}

size_t CopyString(std::string const& src, char* dst, size_t dst_size)
{
    size_t written = 0;
    if (dst != nullptr && dst_size > 0)
    {
        written = src.copy(dst, dst_size - 1);
        dst[written] = '\0';
    }
    return written;
}

}// namespace String
}// namespace System