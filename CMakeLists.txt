cmake_minimum_required(VERSION 3.15)
project(Coral LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(
    $<$<PLATFORM_ID:Windows>:CORAL_WINDOWS>
    $<$<PLATFORM_ID:Linux>:CORAL_LINUX>
    $<$<PLATFORM_ID:Darwin>:CORAL_MACOSX>
)

# Locate MSBuild
find_program(MSBUILD_PATH
    NAMES MSBuild.exe
    PATHS
        "$ENV{ProgramFiles}/Microsoft Visual Studio"
        "$ENV{ProgramFiles}/MSBuild"
        "$ENV{ProgramFilesx86}/Microsoft Visual Studio"
    PATH_SUFFIXES
        "2022/Community/MSBuild/Current/Bin"
        "2019/Community/MSBuild/Current/Bin"
        "MSBuild/Current/Bin"
)

# Generate and build C# project with one target
add_custom_target(Coral.Managed
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/Premake/premake5.exe" vs2022
    COMMAND "C:/Program Files/Microsoft Visual Studio/2022/Community/Msbuild/Current/Bin/MSBuild.exe" Coral.Managed.csproj -property:Configuration=Debug -t:restore,build
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Managed"
    COMMENT "Generating and building Coral.Managed"
)

# Actual static library
file(GLOB_RECURSE SOURCE_DIR
    "Coral.Native/Source/**.cpp"
    "Coral.Native/Source/**.hpp"
    "Coral.Native/Include/Coral/**.h"
)

add_library(Coral.Native STATIC ${SOURCE_DIR})

target_precompile_headers(Coral.Native PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Source/CoralPCH.hpp")

target_include_directories(Coral.Native PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Source" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Include/Coral"
    "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/NetCore"
)

# Ensure Coral.Native builds after Coral.Managed
add_dependencies(Coral.Native Coral.Managed)
