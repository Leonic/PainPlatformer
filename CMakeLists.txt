# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Main project name
project ("PainNSuffering")

# GCC will default to C11 if we don't do this and everything will crash and burn
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Our custom find CMakeFiles for dependencies 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

# Default to debug
if (CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "Build type not defined, defaulting to debug...")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "Build configured as a ${CMAKE_BUILD_TYPE} build")

# Apply some debug options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(WARDEBUG)
    add_compile_definitions(USE_CONSOLE)
endif()

# For Linux and Windows specific code
if (WIN32)
    add_compile_definitions(_WIN32)
elseif(UNIX)
    add_compile_definitions(_UNIX)
endif()

# Mod name (for the Engine)
set (MOD_NAME "PainNSuffering")
set (GAME_NAME "PainPlatformer")

# Window sizes and stuff
add_compile_definitions(DEF_WIDTH=640)
add_compile_definitions(DEF_HEIGHT=480)
add_compile_definitions(DEF_FPS=62)

# Go away M$
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# Build path for debug
set(BIN_PATH_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(BIN_PATH_RELEASE ${CMAKE_BINARY_DIR}/Release)

# Store stuff when compiled here!
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH_DEBUG}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH_DEBUG}/bin") 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_PATH_DEBUG}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_PATH_RELEASE}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_PATH_RELEASE}/bin") 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_PATH_RELEASE}")

add_subdirectory("Game")