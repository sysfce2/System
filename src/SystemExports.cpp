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

#include <System/SystemExports.h>

#ifdef WANT_SYSTEM_SHARED_LIBRARY_EXPORTS
#if defined(SYSTEM_OS_WINDOWS)

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved )
{
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
            shared_library_load();
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            shared_library_unload();
            break;
    }
    return TRUE;
}

#elif defined(SYSTEM_OS_LINUX) || defined(SYSTEM_OS_APPLE)

__attribute__((constructor)) SYSTEM_HIDE_API(void, SYSTEM_CALL_DEFAULT) system_shared_library_constructor()
{
    shared_library_load();
}

__attribute__((destructor)) SYSTEM_HIDE_API(void, SYSTEM_CALL_DEFAULT) system_shared_library_destructor()
{
    shared_library_unload();
}

#endif

#endif
