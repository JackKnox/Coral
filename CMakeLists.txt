cmake_minimum_required(VERSION 3.15)
project(Coral LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(
    $<$<PLATFORM_ID:Windows>:CORAL_WINDOWS>
    $<$<PLATFORM_ID:Linux>:CORAL_LINUX>
    $<$<PLATFORM_ID:Darwin>:CORAL_MACOSX>
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Managed/Coral.Managed.runtimeconfig.json" DESTINATION "${CMAKE_SOURCE_DIR}/Strype/master/DotNet")

# Actual static library
file(GLOB_RECURSE SOURCE_DIR
    "Coral.Native/Source/**.cpp"
)

add_library(Coral.Native STATIC ${SOURCE_DIR})

target_precompile_headers(Coral.Native PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Source/CoralPCH.hpp")

target_include_directories(Coral.Native PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Source" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Include/Coral"
    "${CMAKE_CURRENT_SOURCE_DIR}/Coral.Native/Include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/NetCore"
)
