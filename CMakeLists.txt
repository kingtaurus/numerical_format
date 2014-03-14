cmake_minimum_required(VERSION 2.8)

project(libnumeric_error_format)

#set (CPACK_INSTALL_PREFIX "/usr")

#SET(CMAKE_VERBOSE_MAKEFILE)
set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#  # using Clang
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#  # using GCC
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
#  # using Intel C++
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#  # using Visual Studio C++
#endif()

ENABLE_TESTING()

include(CodeCoverage)
include(CMakeFindBinUtils)

#cmake -DCMAKE_BUILD_TYPE=Debug ../ -G "Unix Makefiles"
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54 COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

ENABLE_TESTING()

SET(BUILD_SHARED_LIBS ON)

SET (CMAKE_C_FLAGS                "-O0 -g3 -Wall -W --coverage -fPIC")
SET (CMAKE_C_FLAGS_DEBUG          "-O0 -g3 --coverage -fPIC")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG -fPIC")
SET (CMAKE_C_FLAGS_RELEASE        "-O3 -DNDEBUG -fPIC")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g2 -fPIC")

SET (CMAKE_CXX_FLAGS                "-O0 -g3 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings --coverage -fPIC")
SET (CMAKE_CXX_FLAGS_DEBUG          "-O0 -g3 --coverage -fPIC")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG -fPIC")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG -fPIC")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g2 -fPIC")

IF(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Debug
       CACHE STRING "Choose the type of build : None Debug Release RelWithDebInfo MinSizeRel Coverage."
       FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

message("* Current build type is  : * ${CMAKE_BUILD_TYPE} *")
message("** NONE                  : * ${CMAKE_CXX_FLAGS} *")
message("** DEBUG                 : * ${CMAKE_CXX_FLAGS_DEBUG} *")
message("** MINSIZEREL            : * ${CMAKE_CXX_FLAGS_MINSIZEREL} *")
message("** RELEASE               : * ${CMAKE_CXX_FLAGS_RELEASE} *")
message("** RELWITHDEBINFO        : * ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} *")
message("** COVERAGE              : * ${CMAKE_CXX_FLAGS_COVERAGE} *")

if(${CMAKE_BUILD_TYPE} MATCHES "None")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
  set(CMAKE_C_FLAGS   "-g0 ${CMAKE_C_FLAGS_RELEASE}")
  set(CMAKE_CXX_FLAGS "-g0 ${CMAKE_CXX_FLAGS_RELEASE}")
elseif (${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
elseif (${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS_MINSIZEREL}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_MINSIZEREL}")
elseif (${CMAKE_BUILD_TYPE} MATCHES "Coverage")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS_COVERAGE}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_COVERAGE}")
elseif ()
  message("Build type: ${CMAKE_BUILD_TYPE} is not known; defaulting to Debug")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --std=c++11")
message("** C   FLAGS             : * ${CMAKE_C_FLAGS} *")
message("** CXX FLAGS             : * ${CMAKE_CXX_FLAGS} *")

configure_file (
  "${PROJECT_SOURCE_DIR}/inc/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}"
)

include_directories( inc/ )

add_subdirectory ( src )
add_subdirectory ( tests )

include (CTest)




