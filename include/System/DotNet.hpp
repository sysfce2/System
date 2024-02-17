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
#include <functional>

namespace System {
namespace DotNet {

class DotNetCoreHost
{
	class DotNetCoreHostImpl* _Impl;

public:
	DotNetCoreHost();
	~DotNetCoreHost();

	/// <summary>
	/// Loads the dotnet host
	/// </summary>
	/// <param name="dotnet_root">Set to an empty string to let the class deduce the host</param>
	/// <param name="dotnet_version">Set to an empty string to load the latest available host</param>
	/// <returns>Loaded or not</returns>
	bool LoadDotNetCoreHost(std::string const& dotnet_root = std::string(), std::string const& dotnet_version = std::string());

	/// <summary>
	/// Loads the assembly and return the entry point delegate
	/// </summary>
	/// <param name="assembly_entry_point_class">The assembly's entry point full qualified class name</param>
	/// <param name="assembly_entry_point_function">The assembly's entry point static public function name </param>
	/// <param name="assembly_path">The assembly .dll</param>
	/// <param name="assembly_runtimeconfig">The assembly runtime configuration (set to an empty string if you want to load the runtime configuration next to the .dll)</param>
	/// <returns>entry point delegate</returns>
	std::function<int(void*, int32_t)> LoadAssemblyAndEntryPoint(std::string const& assembly_entry_point_class, std::string const& assembly_entry_point_function, std::string const& assembly_path, std::string const& assembly_runtimeconfig = std::string());

	/// <summary>
	/// Gets an already loaded assembly function delegate
	/// </summary>
	/// <param name="assembly_entry_point_class">The assembly's entry point full qualified class name</param>
	/// <param name="assembly_entry_point_function">The assembly's entry point static public function name </param>
	/// <returns>entry point delegate</returns>
	std::function<int(void*, int32_t)> GetFunctionDelegate(std::string const& full_qualified_class_name, std::string const& static_public_function_name);
};

}
}