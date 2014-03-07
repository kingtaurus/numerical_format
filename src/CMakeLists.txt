# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#add_library( pdg_error                    SHARED pdg_error.cpp )
#add_library( pdg_error_static             STATIC pdg_error.cpp)

#add_custom_target( pdg DEPENDS pdg_error.cpp )

#add_library( pdg_error        SHARED pdg_error.cpp )
#add_library( pdg_error_static STATIC pdg_error.cpp)

#add_dependencies(  pdg_error        pdg)
#add_dependencies(  pdg_error_static pdg)

add_library( pdg_error                    SHARED pdg_error.cpp )
add_library( pdg_error-static             STATIC pdg_error.cpp )
SET_TARGET_PROPERTIES( pdg_error-static PROPERTIES OUTPUT_NAME "pdg_error")
SET_TARGET_PROPERTIES( pdg_error-static PROPERTIES PREFIX      "lib")

add_library( type                         SHARED type.cpp )
add_library( type-static                  STATIC type.cpp )
SET_TARGET_PROPERTIES( type-static PROPERTIES OUTPUT_NAME "type")
SET_TARGET_PROPERTIES( type-static PROPERTIES PREFIX      "lib")

add_library( symmetric_error              SHARED symmetric_error.cpp)
add_library( symmetric_error-static       STATIC symmetric_error.cpp)
SET_TARGET_PROPERTIES( symmetric_error-static PROPERTIES OUTPUT_NAME "symmetric_error")
SET_TARGET_PROPERTIES( symmetric_error-static PROPERTIES PREFIX      "lib")

add_library( stream_output_proxy          SHARED stream_output_proxy.cpp)
add_library( stream_output_proxy-static   STATIC stream_output_proxy.cpp)
SET_TARGET_PROPERTIES( stream_output_proxy-static PROPERTIES OUTPUT_NAME "stream_output_proxy")
SET_TARGET_PROPERTIES( stream_output_proxy-static PROPERTIES PREFIX      "lib")

add_library( error_helper_def             SHARED error_helper_def.cpp)
add_library( error_helper_def-static      STATIC error_helper_def.cpp)
SET_TARGET_PROPERTIES( error_helper_def-static PROPERTIES OUTPUT_NAME "error_helper_def")
SET_TARGET_PROPERTIES( error_helper_def-static PROPERTIES PREFIX      "lib")
# # The library target "foo" already has a default OUTPUT_NAME of "foo", so we don't need to change it.
# # The library target "foo-static" has a default OUTPUT_NAME of "foo-static", so change it.
# SET_TARGET_PROPERTIES(foo-static PROPERTIES OUTPUT_NAME "foo")
# # Now the library target "foo-static" will be named "foo.lib" with MS tools.
# # This conflicts with the "foo.lib" import library corresponding to "foo.dll",
# # so we add a "lib" prefix (which is default on other platforms anyway):
# SET_TARGET_PROPERTIES(foo-static PROPERTIES PREFIX "lib")

add_library( pdg       SHARED pdg_error       type stream_output_proxy error_helper_def)
add_library( symmetric SHARED symmetric_error type stream_output_proxy error_helper_def)

add_library( pdg-static       STATIC pdg_error.cpp       type.cpp stream_output_proxy.cpp error_helper_def.cpp)
SET_TARGET_PROPERTIES( pdg-static PROPERTIES OUTPUT_NAME "pdg")
SET_TARGET_PROPERTIES( pdg-static PROPERTIES PREFIX      "lib")

add_library( symmetric-static STATIC symmetric_error.cpp type.cpp stream_output_proxy.cpp error_helper_def.cpp)
SET_TARGET_PROPERTIES( symmetric-static PROPERTIES OUTPUT_NAME "symmetric")
SET_TARGET_PROPERTIES( symmetric-static PROPERTIES PREFIX      "lib")

SET(CPACK_STRIP_FILES "")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

SET(CPACK_GENERATOR "DEB")
#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")#this doesn't seem to add the LICENSE to debian
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Greg King <greg.james.king@gmail.com>") #required
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/kingtaurus/numerical_format")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY 
"Numerical Error Format.\n Provides pdg and symmetric formatting of a central value and its associated\n error. Further numerical output can be formatted using LaTeX or terminal\n decoration.")
SET(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
execute_process(COMMAND "dpkg --print-architecture" OUTPUT_VARIABLE DPKG_ARCH)
SET(CPACK_SYSTEM_NAME ${DPKG_ARCH})
SET(CPACK_PACKAGE_NAME "libnumeric-error-format")

#cpack --help-variable-list
#FROM dpkg --print-architecture

#SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
#SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_MAJOR_VERSION}.${CPACK_PACKAGE_MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")

SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
#SET(CPACK_COMPONENTS_ALL Libraries ApplicationData)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=  2.17), libstdc++-4.8-dev (>= 4.8.1), linux-libc-dev (>= 3.11.0), libgcc1 (>= 1:4.8.0), libboost1.54-all-dev(>= 1.54.0), libmpfr-dev (>= 3.0.0), libgmp-dev (>= 2:5.1.1)")


#lintian -i on the deb created:
#missing changelog
#missing LICENSE

FILE(GLOB Common_HPP "${PROJECT_SOURCE_DIR}/inc/*.hpp")
MESSAGE("Headers  : ${Common_HPP}")

# uncomment next two lines and add the 3rd to the install directive below,
#'if' you want to combine all install commands together
#set_target_properties(pdg PROPERTIES
#  PUBLIC_HEADER "${Common_HPP}")
#PUBLIC_HEADER DESTINATION include/numeric_error_format COMPONENT pdg

install(
     TARGETS pdg symmetric pdg-static symmetric-static
     LIBRARY DESTINATION lib/numeric_error_format COMPONENT pdg
     ARCHIVE DESTINATION lib/numeric_error_format COMPONENT pdg
)

install( 
     TARGETS pdg_error type symmetric_error stream_output_proxy error_helper_def
     LIBRARY DESTINATION lib/numeric_error_format COMPONENT pdg
)

install( 
     TARGETS pdg_error-static type-static symmetric_error-static stream_output_proxy-static error_helper_def-static
     ARCHIVE DESTINATION lib/numeric_error_format COMPONENT pdg
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/ DESTINATION include/
        FILES_MATCHING PATTERN "*.hpp")

INCLUDE(CPack)
#make package
#ls _CPack_Packages/Linux/DEB/libnumeric_error_format-0.1.1-Linux/usr/lib/numeric_error_format/



#add_library(HEADER_ONLY_TARGET STATIC test1.hpp test2.hpp)
#set_target_properties(HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)

