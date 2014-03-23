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

#SET( legacy_link   ${CMAKE_INSTALL_PREFIX}/libIex.so)
#SET( legacy_target ${CMAKE_INSTALL_PREFIX}/libIex-2_0.so.10.0.1)
#ADD_CUSTOM_COMMAND( OUTPUT ${legacy_link}
#                    COMMAND ln -s ${legacy_target} ${legacy_link}
#                    DEPENDS install ${legacy_target}#                    COMMENT "Generating legacy symbolic link")
#ADD_CUSTOM_TARGET( install_legacy DEPENDS ${legacy_link} )

add_library( type                         SHARED type.cpp )
add_library( type-static                  STATIC type.cpp )
SET_TARGET_PROPERTIES( type-static PROPERTIES OUTPUT_NAME "type")
SET_TARGET_PROPERTIES( type-static PROPERTIES PREFIX      "lib")

add_library( symmetric_error              SHARED symmetric_error.cpp)
add_library( symmetric_error-static       STATIC symmetric_error.cpp)
SET_TARGET_PROPERTIES( symmetric_error-static PROPERTIES OUTPUT_NAME "symmetric_error")
SET_TARGET_PROPERTIES( symmetric_error-static PROPERTIES PREFIX      "lib")

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

add_library( pdg       SHARED pdg_error       type error_helper_def)
add_library( symmetric SHARED symmetric_error type error_helper_def)

add_library( pdg-static       STATIC pdg_error.cpp       type.cpp error_helper_def.cpp)
SET_TARGET_PROPERTIES( pdg-static PROPERTIES OUTPUT_NAME "pdg")
SET_TARGET_PROPERTIES( pdg-static PROPERTIES PREFIX      "lib")

add_library( symmetric-static STATIC symmetric_error.cpp type.cpp error_helper_def.cpp)
SET_TARGET_PROPERTIES( symmetric-static PROPERTIES OUTPUT_NAME "symmetric")
SET_TARGET_PROPERTIES( symmetric-static PROPERTIES PREFIX      "lib")

message("${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.0")
message("${${PROJECT_NAME}_VERSION_MAJOR}")

SET_TARGET_PROPERTIES (pdg
  PROPERTIES VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
)

SET_TARGET_PROPERTIES (symmetric
  PROPERTIES VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
)



#stream_output_proxy symmetric_error
# type pdg_error


#SET(CPACK_SET_DESTDIR "on")
#SET(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
SET(CPACK_GENERATOR "DEB")

#https://www.debian.org/doc/debian-policy/ch-source.html#s-dpkgchangelog
#http://faceted.wordpress.com/2011/05/18/howto-build-a-trivial-debian-package-with-dh_make/

SET(CPACK_STRIP_FILES "")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/copyright")

#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")#this doesn't seem to add the LICENSE to debian
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Greg King <greg.james.king@gmail.com>") #required
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/kingtaurus/numerical_format")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY"Numerical Error Format.\n Provides pdg and symmetric formatting of a central value and its associated\n error. Further numerical output can be formatted using LaTeX or terminal\n decoration.")
SET(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
#execute_process(COMMAND "dpkg --print-architecture" OUTPUT_VARIABLE DPKG_ARCH)
#SET(CPACK_SYSTEM_NAME ${DPKG_ARCH})
SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
SET(CPACK_PACKAGE_NAME "libnumeric-error-format-dev")
#cpack --help-variable-list
#FROM dpkg --print-architecture

SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=  2.17), libstdc++-4.8-dev (>= 4.8.1), linux-libc-dev (>= 3.11.0), libgcc1 (>= 1:4.8.0), libboost1.54-all-dev(>= 1.54.0), libgmp10(>= 2:5.1.2 ), libmpfr-dev (>= 3.0.0), libgmp-dev (>= 2:5.1.1)")#\${shlibs:Depends},
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)


# Using the following
# for x in *.cpp
# do
#   gcc -M ${x} -I../inc --std=c++11 | cut -f1 -d'\' | tr ' ' '\n' | grep -v ^$ | grep -v ${x} | grep -v ${x/cpp/o} | xargs -n1 apt-file search | cut -f1 -d: >> tmp
#done
#
#
#BUILD_DEPS
# libboost1.54-dev
# libc6-dev
# libgcc-4.8-dev
# libstdc++-4.8-dev
# linux-libc-dev
#LINK DEPS
#ldd macro_checks | grep -v vdso | cut -f2 -d'>' | cut -f1 -d'(' | xargs -n1 apt-file search | cut -f1 -d':' | sort | uniq

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


#this is bad form according to debian; (these libraries have different names)
#this could be made proper by only doing one file for each library
install(
     TARGETS pdg symmetric pdg-static symmetric-static
     LIBRARY DESTINATION lib COMPONENT pdg
     ARCHIVE DESTINATION lib COMPONENT pdg
)

install(     TARGETS pdg_error type symmetric_error error_helper_def
     LIBRARY DESTINATION lib COMPONENT pdg
)

install(     TARGETS pdg_error-static type-static symmetric_error-static error_helper_def-static
     ARCHIVE DESTINATION lib COMPONENT pdg
)

set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/debian/postinst;${CMAKE_SOURCE_DIR}/debian/prerm;${CMAKE_SOURCE_DIR}/debian/postrm")
#can use the above to do the following
#add a file to /etc/ld.so.conf.d/
#add symbolic links
#I THINK these files can be generated by cmake

install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/ DESTINATION include/numeric_error_format
        COMPONENT headers
        FILES_MATCHING PATTERN "*.hpp" )

install(FILES ${PROJECT_SOURCE_DIR}/copyright DESTINATION share/doc/${CPACK_PACKAGE_NAME}
        COMPONENT copyright)

#this will add the copyright to the appropriate location in the debian
#/usr/share/doc/${PROJECT_NAME}/
#technically this can also be use to setup commands to strip the libraries


#execute_process(COMMAND ls $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib
#OUTPUT_VARIABLE lsresults)
#message("${lsresults}")

set(CPACK_WARN_ON_ABSOLUTE_INSTALL_DESTINATION TRUE)
#set(CPACK_COMPONENTS_ALL_GROUPS_IN_ONE_PACKAGE 1)


INCLUDE(CPack)

#gking@bender:~/Programming/C++/stream_errors/build/Release$ lintian -I libnumeric-error-format-dev-0.1.0-Linux.deb#W: libnumeric-error-format-dev: package-name-doesnt-match-sonames liberror-helper-def libpdg libpdg-error libstream-output-proxy libsymmetric libsymmetric-error libtype
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/liberror_helper_def.so .comment
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/libpdg.so .comment
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/libpdg_error.so .comment
#W: libnumeric-error-format-dev: shared-lib-without-dependency-information usr/lib/libpdg_error.so
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/libstream_output_proxy.so .comment
#W: libnumeric-error-format-dev: shared-lib-without-dependency-information usr/lib/libstream_output_proxy.so
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/libsymmetric.so .comment
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/libsymmetric_error.so .comment
#I: libnumeric-error-format-dev: binary-has-unneeded-section usr/lib/libtype.so .comment
#E: libnumeric-error-format-dev: changelog-file-missing-in-native-package
#E: libnumeric-error-format-dev: copyright-file-contains-full-gpl-license
#E: libnumeric-error-format-dev: copyright-should-refer-to-common-license-file-for-lgpl
#I: libnumeric-error-format-dev: description-synopsis-might-not-be-phrased-properly
#W: libnumeric-error-format-dev: wrong-section-according-to-package-name libnumeric-error-format-dev => libdevel
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/liberror_helper_def.so liberror_helper_def.so
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/libpdg.so libpdg.so
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/libstream_output_proxy.so libstream_output_proxy.so
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/libpdg_error.so libpdg_error.so
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/libsymmetric_error.so libsymmetric_error.so
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/libtype.so libtype.so
#W: libnumeric-error-format-dev: shlib-without-versioned-soname usr/lib/libsymmetric.so libsymmetric.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/liberror_helper_def.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/libpdg.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/libpdg_error.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/libstream_output_proxy.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/libsymmetric_error.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/libsymmetric.so
#I: libnumeric-error-format-dev: no-symbols-control-file usr/lib/libtype.so



#The listed shared library in a public library directory has an SONAME that does not contain any versioning information, either after the .so or before it and set off by a hyphen. It cannot therefore be represented in the shlibs system, and if linked by binaries its interface cannot safely change. There is no backward-compatible way to migrate programs linked against it to a new ABI.
#Normally, this means the shared library is a private library for a particular application and is not meant for general use. Policy recommends that such libraries be installed in a subdirectory of /usr/lib rather than in a public shared library directory.
#To view the SONAME of a shared library, run readelf -d on the shared library and look for the tag of type SONAME.
#There are some special stub libraries or special-purpose shared objects for which an ABI version is not meaningful. If this is one of those cases, please add an override.



#make package
#ls _CPack_Packages/Linux/DEB/libnumeric_error_format-0.1.1-Linux/usr/lib/numeric_error_format/


#add_library(HEADER_ONLY_TARGET STATIC test1.hpp test2.hpp)
#set_target_properties(HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)




#I think I need to use CPack to make the deb properly
# CPACK_INCLUDE_TOPLEVEL_DIRECTORY
# CPACK_MONOLITHIC_INSTALL
# CPACK_DEB_COMPONENT_INSTALL
# CPACK_DEBIAN_PACKAGE_RECOMMENDS
# CPACK_DEBIAN_PACKAGE_SUGGESTS
# CPACK_DEBIAN_PACKAGE_PREDEPENDS
# CPACK_DEBIAN_PACKAGE_ENHANCES
# CPACK_DEBIAN_PACKAGE_BREAKS
# CPACK_DEBIAN_PACKAGE_CONFLICTS
# CPACK_DEBIAN_PACKAGE_PROVIDES
# CPACK_DEBIAN_PACKAGE_REPLACES



#CPACK_OUTPUT_FILE_PREFIX
#CPACK_TOPLEVEL_DIRECTORY
#CPACK_TEMPORARY_DIRECTORY
#CPACK_OUTPUT_FILE_NAME
#CPACK_OUTPUT_FILE_PATH
#CPACK_TEMPORARY_PACKAGE_FILE_NAME
#CPACK_INSTALL_DIRECTORY
#CPACK_NATIVE_INSTALL_DIRECTORY
#CPACK_TEMPORARY_INSTALL_DIRECTORY






