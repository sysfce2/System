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

#include <tuple>
#include <mutex>

namespace System {

template<typename... Args>
class ScopedLock
{
    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type unlock(std::tuple<Tp...>& t) { }

    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if < I < sizeof...(Tp), void>::type unlock(std::tuple<Tp...>& t)
    {
        std::get<I>(t).unlock();
        unlock<I + 1, Tp...>(t);
    }

    std::tuple<Args&...> _mutexes;

public:
    explicit ScopedLock(Args&... mutexes) : _mutexes(mutexes...)
    {
        std::lock(mutexes...);
    }

    explicit ScopedLock(std::adopt_lock_t, Args&... mutexes) : _mutexes(mutexes...)
    {}

    ~ScopedLock()
    {
        unlock(_mutexes);
    }

    ScopedLock(ScopedLock&&) noexcept = default;
    ScopedLock& operator=(ScopedLock&&) noexcept = default;

    ScopedLock(ScopedLock const&) = delete;
    ScopedLock& operator=(ScopedLock const&) = delete;
};

template<typename... Args>
ScopedLock<Args...> ScopeLock(Args&... mutexes)
{
    return ScopedLock<Args...>(mutexes...);
}

}