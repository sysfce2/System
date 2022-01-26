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

#include <string>
#include <algorithm>

namespace System {
    static inline std::string ltrim(std::string str)
    {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](const char& c)
        {
            return !std::isspace((unsigned char)c);
        }));

        return str;
    }

    static inline std::string rtrim(std::string str)
    {
        str.erase(std::find_if(str.rbegin(), str.rend(), [](const char& c)
        {
            return !std::isspace((unsigned char)c);
        }).base(), str.end());

        return str;
    }

    static inline std::string trim(std::string str)
    {
        return rtrim(ltrim(str));
    }

    static inline std::string to_lower(std::string str)
    {
        for (auto& c : str)
        {
            c = std::tolower((unsigned char)c);
        }
        return str;
    }

    static inline std::string to_lower(const char* str)
    {
        return System::to_lower(std::string{ str });
    }

    static inline std::string to_upper(std::string str)
    {
        for (auto& c : str)
        {
            c = std::toupper((unsigned char)c);
        }
        return str;
    }

    static inline std::string to_upper(const char* str)
    {
        return System::to_upper(std::string{ str });
    }

    template<typename IteratorType>
    inline std::string string_join(IteratorType begin, IteratorType end, const std::string &sep)
    {
        std::string res;

        if (begin != end)
            res += *begin++;

        while(begin != end)
        {
            res += sep;
            res += *begin++;
        }

        return res;
    }

    template<typename T>
    inline std::string string_join(T const& container, const std::string &sep)
    {
        return string_join(std::begin(container), std::end(container), sep);
    }
}