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
#include <vector>
#include <fstream>
#include <ctime>

namespace System {
namespace Filesystem {
    #if defined(WIN64) || defined(_WIN64) || defined(__MINGW64__) || defined(WIN32) || defined(_WIN32) || defined(__MINGW32__)
        constexpr static char separator = '\\';
    #else
        constexpr static char separator = '/';
    #endif

    std::string clean_path(std::string const& path);
    std::string filename(std::string const& path);
    std::string dirname(std::string const& path);
    bool is_absolute(std::string const& path);

    inline std::string const& join(std::string const& path) { return path; }
    template<typename ...Args>
    std::string join(std::string const& path, Args&& ...args)
    {
        std::string res(join(args...));
        if (*path.rbegin() == separator)
        {
            if (!res.empty() && *res.begin() == separator)
                return path + res.substr(1);

            return path + res;
        }

        if (!res.empty() && *res.begin() == separator)
            return path + res;

        return path + separator + res;
    }

    std::string get_cwd();
    std::string canonical_path(std::string const& path);

    bool is_dir(std::string const& path);
    bool is_file(std::string const& path);
    bool exists(std::string const& path);
    size_t file_size(std::string const& path);
    time_t file_atime(std::string const& path);
    time_t file_mtime(std::string const& path);
    time_t file_ctime(std::string const& path);

    bool create_directory(std::string const& directory, bool recursive = true);
    bool delete_file(std::string const& path);
    std::vector<std::string> list_files(std::string const& path, bool recursive = false);

}
}