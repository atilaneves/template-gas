cmake_minimum_required(VERSION 2.8)

project(templatega)

#set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug Release"
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#set(PROJ_FLAGS_DEBUG "-Wall -g -pg -fno-inline --std=c++0x")
#set(PROJ_FLAGS_RELEASE "-Wall -O1 --std=c++0x")
set(PROJ_FLAGS_DEBUG "-Wall -g -pg -fno-inline")
set(PROJ_FLAGS_RELEASE "-Wall -O1")
set(CMAKE_C_FLAGS_DEBUG ${PROJ_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_DEBUG ${PROJ_FLAGS_DEBUG})
set(CMAKE_C_FLAGS_RELEASE ${PROJ_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELEASE ${PROJ_FLAGS_RELEASE})

message("Build type is ${CMAKE_BUILD_TYPE}")

file(GLOB SRCS *.cpp)

include_directories(.)

#if(WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
#  set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
#endif()

add_executable(ga ${SRCS})
