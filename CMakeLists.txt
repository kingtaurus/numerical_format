cmake_minimum_required(VERSION 2.8)

project(libnumeric_error_format)
#SET(CMAKE_VERBOSE_MAKEFILE)
set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#cmake -DCMAKE_BUILD_TYPE=Debug ../ -G "Unix Makefiles"

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
ENABLE_TESTING()

SET(BUILD_SHARED_LIBS ON)

SET (CMAKE_C_FLAGS                "-g3 -O1 -Wall -W")
SET (CMAKE_C_FLAGS_DEBUG          "-O0 -g3 --coverage")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g2")

SET (CMAKE_CXX_FLAGS              "-g3 -O1 --std=c++11  -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")
SET (CMAKE_CXX_FLAGS_DEBUG          "-O0 -g3 --coverage")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g2")

SET (CMAKE_C_FLAGS_COVERAGE   "${GCC_DEBUG_FLAGS} --coverage -Wall -W")
SET (CMAKE_CXX_FLAGS_COVERAGE "${GCC_DEBUG_FLAGS} --std=c++11 --coverage -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")

IF(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Debug
       CACHE STRING "Choose the type of build : None Debug Release RelWithDebInfo MinSizeRel."
       FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)
message("* Current build type is : ${CMAKE_BUILD_TYPE} *")
message("** NONE                  : * ${CMAKE_CXX_FLAGS} *")
message("** DEBUG                 : * ${CMAKE_CXX_FLAGS_DEBUG} *")
message("** MINSIZEREL            : * ${CMAKE_CXX_FLAGS_MINSIZEREL} *")
message("** RELEASE               : * ${CMAKE_CXX_FLAGS_RELEASE} *")
message("** RELWITHDEBINFO        : * ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} *")

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
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



