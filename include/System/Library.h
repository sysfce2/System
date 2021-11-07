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

namespace System {

class Library
{
    void* _Handle;

public:
    inline Library():
        _Handle(nullptr)
    {}

    inline Library(Library const& other)
    {
        _Handle = other._Handle;
    }

    inline Library(Library&& other) noexcept
    {
        _Handle = other._Handle;
        other._Handle = nullptr;
    }

    inline Library& operator=(Library const& other)
    {
        _Handle = other._Handle;
        return *this;
    }

    inline Library& operator=(Library&& other) noexcept
    {
        void* tmp = other._Handle;
        other._Handle = _Handle;
        _Handle = tmp;

        return *this;
    }

    inline ~Library()
    {
        CloseLibrary(_Handle);
        _Handle = nullptr;
    }

    bool OpenLibrary(std::string const& library_name, bool append_extension);

    inline void CloseLibrary()
    {
        CloseLibrary(_Handle);
        _Handle = nullptr;
    }

	template<typename T>
    inline T* GetSymbol(std::string const& symbol_name)
    {
        return reinterpret_cast<T*>(GetSymbol(_Handle, symbol_name));
    }

    inline std::string GetModulePath()
    {
        return GetModulePath(_Handle);
    }

    inline bool IsLoaded() const
    {
        return _Handle != nullptr;
    }

    // Triies to load the library, I suggest that you use a Library instance instead
    static void* OpenLibrary(std::string const& library_name);
    // Will decrease the OS' ref counter on the library, use it to close a handle opened by open_library.
    // A Library instance will automatically call this in the destructor
    static void  CloseLibrary(void* handle);
    // Will try to retrieve a symbol address from the library handle
    static void* GetSymbol(void* handle, std::string const& symbol_name);
    // Get a pointer to the library, if it is not loaded, will return nullptr. This doesn't increment the OS' internal ref counter
    static void* GetModuleHandle(std::string const& library_name);
    // Get the library path of a module handle
    static std::string GetModulePath(void* handle);
};

}
