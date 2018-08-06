/*
The main() function is where the program starts execution
*/

// Include Files
//==============

#include <cstdlib>
#include <iostream>
#include <External\Lua\Includes.h>
#include <cassert>
#include <filesystem>
#include <string>
#include <windows.h>
// Helper Function Declarations
//=============================

namespace
{
	// For a C/C++ function to be callable by Lua it must be a lua_CFunction:
	//	* typedef int (*lua_CFunction)( lua_State *L );
	// The input parameters will already be pushed on the stack in the provided lua_State*
	// and the function should push the return values on the stack
	// and then return how many there are.
	// There will be more explanation in the examples.

	int LuaGetEnvironmentVariable(lua_State* io_luaState);
	int LuaCopyFile(lua_State* io_luaState);
	int LuaCreateDirectoryIfItDoesntExist(lua_State* io_luaState);
	int LuaGetFilesInDirectory(lua_State* io_luaState);
	int LuaIsDirectory(lua_State* io_luaState);
	int LuaOutputMessage(lua_State* io_luaState);
}

// Entry Point
//============

int main(int i_argumentCount, char** i_arguments)
{
	int exitCode = EXIT_SUCCESS;

	// Create a new Lua state
	lua_State* luaState = nullptr;
	{
		luaState = luaL_newstate();
		if (!luaState)
		{
			exitCode = EXIT_FAILURE;
			goto OnExit;
		}
	}
	// Open the standard libraries
	luaL_openlibs(luaState);

	// Make the C/C++ functions available to the Lua state
	// (this sets the function as a global variable
	// using the name provided)
	{
		lua_register(luaState, "GetEnvironmentVariable", LuaGetEnvironmentVariable);
		lua_register(luaState, "CopyFile", LuaCopyFile);
		lua_register(luaState, "CreateDirectoryIfItDoesntExist", LuaCreateDirectoryIfItDoesntExist);
		lua_register(luaState, "GetFilesInDirectory", LuaGetFilesInDirectory);
		lua_register(luaState, "IsDirectory", LuaIsDirectory);
		lua_register(luaState, "OutputMessage", LuaOutputMessage);
	}

	// Load and run the Lua script that calls the functions
	{
		 //If you set breakpoints in the registered C/C++ functions
		 //before executing the Lua script you will be able to watch them get called

		constexpr DWORD maxCharacterCount = MAX_PATH;
		char buffer[MAX_PATH];
		const auto characterCount = ::GetEnvironmentVariable("OutputDir", buffer, maxCharacterCount);

		std::string path(buffer);
		path += "AssetBuildFunctions.lua";

		const auto result = luaL_dofile(luaState, path.c_str());
		if (result != LUA_OK)
		{
			const auto* const errorMessage = lua_tostring(luaState, -1);
			std::cerr << errorMessage << std::endl;
			lua_pop(luaState, 1);
			exitCode = EXIT_FAILURE;
			goto OnExit;
		}

	}

OnExit:

	if (luaState)
	{
		assert(lua_gettop(luaState) == 0);

		lua_close(luaState);
		luaState = NULL;
	}

	system("Pause");

	return exitCode;
}

// Helper Function Definitions
//============================

namespace
{
	int LuaGetEnvironmentVariable(lua_State* io_luaState)
	{
		// Argument #1: The key
		const char* i_key;
		if (lua_isstring(io_luaState, 1))
		{
			i_key = lua_tostring(io_luaState, 1);
		}
		else
		{
			return luaL_error(io_luaState, "Argument #1 must be a string (instead of a %s)", luaL_typename(io_luaState, 1));
		}


		constexpr DWORD maxCharacterCount = MAX_PATH;
		char buffer[MAX_PATH];

		if (::GetEnvironmentVariable(i_key, buffer, maxCharacterCount))
		{
			lua_pushstring(io_luaState, buffer);
			constexpr int returnValueCount = 1;
			return returnValueCount;
		}
		else
		{
			std::string error = "GetEnvironmentVariable Error: ";
			error += i_key;

			lua_pushnil(io_luaState);
			lua_pushstring(io_luaState, error.c_str());

			constexpr int returnValueCount = 2;
			return returnValueCount;
		}
	}

	int LuaCopyFile(lua_State* io_luaState)
	{
		// Argument #1: The source path
		const char* i_path_source;

		if (lua_isstring(io_luaState, 1))
		{
			i_path_source = lua_tostring(io_luaState, 1);
		}
		else
		{
			return luaL_error(io_luaState, "Argument #1 must be a string (instead of a %s)", luaL_typename(io_luaState, 1));
		}

		// Argument #2: The target path
		const char* i_path_target;

		if (lua_isstring(io_luaState, 2))
		{
			i_path_target = lua_tostring(io_luaState, 2);
		}
		else
		{
			return luaL_error(io_luaState, "Argument #2 must be a string (instead of a %s)", luaL_typename(io_luaState, 2));
		}

		// Copy the file
		{
			if (std::experimental::filesystem::exists(i_path_source))
			{
				std::experimental::filesystem::copy(i_path_source, i_path_target, std::experimental::filesystem::copy_options::overwrite_existing);
				lua_pushboolean(io_luaState, true);
				constexpr int returnValueCount = 1;
				return returnValueCount;
			}
			else
			{
				std::string errorMessage = "File Not exists: ";
				errorMessage += i_path_source;

				lua_pushboolean(io_luaState, false);
				lua_pushstring(io_luaState, errorMessage.c_str());
				constexpr int returnValueCount = 2;
				return returnValueCount;
			}
		}
	}

	int LuaCreateDirectoryIfItDoesntExist(lua_State* io_luaState)
	{
		// Argument #1: The path
		const char* i_path;

		if (lua_isstring(io_luaState, 1))
		{
			i_path = lua_tostring(io_luaState, 1);
		}
		else
		{
			return luaL_error(io_luaState, "Argument #1 must be a string (instead of a %s)", luaL_typename(io_luaState, 1));
		}

		if (std::experimental::filesystem::exists(i_path) && std::experimental::filesystem::is_directory(i_path))
		{
			constexpr int returnValueCount = 0;
			return returnValueCount;
		}
		else if (std::experimental::filesystem::create_directory(i_path))
		{
			constexpr int returnValueCount = 0;
			return returnValueCount;
		}
		else
		{
			std::string errorMessage = "can't create: ";
			errorMessage += i_path;

			return luaL_error(io_luaState, errorMessage.c_str());
		}
	}


	int LuaGetFilesInDirectory(lua_State* io_luaState)
	{
		// Argument #1: The path
		const char* i_path;
		if (lua_isstring(io_luaState, 1))
		{
			i_path = lua_tostring(io_luaState, 1);
		}
		else
		{
			return luaL_error(io_luaState, "Argument #1 must be a string (instead of a %s)", luaL_typename(io_luaState, 1));
		}
		// Argument #2: An optional indication of whether the directory's subdirectories should be searched recursively
		bool i_shouldSubdirectoriesBeSearchedRecursively = true;
		if (!lua_isnoneornil(io_luaState, 2))
		{
			if (lua_isboolean(io_luaState, 2))
			{
				i_shouldSubdirectoriesBeSearchedRecursively = lua_toboolean(io_luaState, 2) != 0;
			}
			else
			{
				return luaL_error(io_luaState, "Argument #2 must be a boolean (instead of a %s)", luaL_typename(io_luaState, 2));
			}
		}

		std::vector<std::string> paths;

		if (std::experimental::filesystem::exists(i_path))
		{
			if (i_shouldSubdirectoriesBeSearchedRecursively)
			{
				for (auto & p : std::experimental::filesystem::recursive_directory_iterator(i_path))
				{
					paths.push_back(p.path().string());
				}
			}
			else
			{
				for (auto & p : std::experimental::filesystem::directory_iterator(i_path))
				{
					paths.push_back(p.path().string());
				}
			}

			const auto arraySize = paths.size();
			constexpr int noDictionaryEntries = 0;
			lua_createtable(io_luaState, static_cast<int>(arraySize), noDictionaryEntries);

			for (size_t i = 0; i < arraySize; ++i)
			{
				lua_pushinteger(io_luaState, i + 1);
				lua_pushstring(io_luaState, paths[i].c_str());
				lua_settable(io_luaState, -3);
			}

			constexpr int returnValueCount = 1;
			return returnValueCount;
		}
		else
		{
			std::string errorMessage = "File Not exists: ";
			errorMessage += i_path;
			return luaL_error(io_luaState, "Error");
		}
	}

	int LuaIsDirectory(lua_State * io_luaState)
	{
		// Argument #1: The path
		const char* i_path = nullptr;

		if (lua_isstring(io_luaState, 1))
		{
			i_path = lua_tostring(io_luaState, 1);
		}
		else
		{
			return luaL_error(io_luaState, "Argument #1 must be a string (instead of a %s)", luaL_typename(io_luaState, 1));
		}

		int result = std::experimental::filesystem::is_directory(i_path);

		lua_pushboolean(io_luaState, result ? true : false);
		constexpr int returnValueCount = 1;
		return returnValueCount;
	}

	int LuaOutputMessage(lua_State* io_luaState)
	{
		const auto* const i_value = lua_tostring(io_luaState, 1);

		std::cout << "LOG: " << i_value << std::endl;

		constexpr int returnValueCount = 0;
		return returnValueCount;
	}
}
