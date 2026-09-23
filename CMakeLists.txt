# Originally pulled and modified from https://github.com/Xanz/Quake4SDK

cmake_minimum_required(VERSION 3.13.0)
project(Quake4SDK VERSION 1.4.4)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c src/game/game.def)
file(GLOB_RECURSE HEADERS src/*.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -fpermissive -fno-strict-aliasing -Wno-conversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

add_compile_definitions(__linux__)
add_compile_definitions(__i386__)

add_compile_definitions(GAME_DLL)
add_compile_definitions(Q4SDK)
add_compile_definitions(_DEBUG) # change this if needed

# Needed so that VSCode can syntax check correctly.
include_directories(${CMAKE_SOURCE_DIR}/src PUBLIC)

add_library(gamex86 SHARED ${HEADERS} ${SOURCES})

# Force 32 bit compilation in GCC
set_target_properties(gamex86 PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32")

# GCC seems to add a "lib" prefix to the output.
set_target_properties(gamex86 PROPERTIES PREFIX "")
set_property(TARGET gamex86 PROPERTY CXX_STANDARD 11)

target_precompile_headers(gamex86 PRIVATE src/idlib/precompiled.h)

set_target_properties(gamex86 PROPERTIES VS_DEBUGGER_COMMAND ${Q4InstallPath}//Quake4.exe)
set_target_properties(gamex86 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${Q4InstallPath}")
set_target_properties(gamex86 PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "+set fs_game ${Q4ModName} +set com_allowConsole 1  +set win_allowmultipleInstances 1")
