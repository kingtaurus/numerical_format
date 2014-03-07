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
add_library( pdg_error_static             STATIC pdg_error.cpp)
add_library( type                         SHARED type.cpp )
add_library( type_static                  STATIC type.cpp )
add_library( symmetric_error              SHARED symmetric_error.cpp)
add_library( symmetric_error_static       STATIC symmetric_error.cpp)
add_library( stream_output_proxy          SHARED stream_output_proxy.cpp)
add_library( stream_output_proxy_static   STATIC stream_output_proxy.cpp)
add_library( error_helper_def             SHARED error_helper_def.cpp)
add_library( error_helper_def_static      SHARED error_helper_def.cpp)

# # The library target "foo" already has a default OUTPUT_NAME of "foo", so we don't need to change it.
# # The library target "foo-static" has a default OUTPUT_NAME of "foo-static", so change it.
# SET_TARGET_PROPERTIES(foo-static PROPERTIES OUTPUT_NAME "foo")
# # Now the library target "foo-static" will be named "foo.lib" with MS tools.
# # This conflicts with the "foo.lib" import library corresponding to "foo.dll",
# # so we add a "lib" prefix (which is default on other platforms anyway):
# SET_TARGET_PROPERTIES(foo-static PROPERTIES PREFIX "lib")

add_library( pdg SHARED pdg_error type stream_output_proxy error_helper_def)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Greg King") #required

install(
     TARGETS pdg
     LIBRARY DESTINATION lib/numeric_error_format
     COMPONENT pdg
)
install(
     TARGETS pdg_error
     LIBRARY DESTINATION lib/numeric_error_format
     COMPONENT pdg
)


INCLUDE(CPack)
#make package
#ls _CPack_Packages/Linux/DEB/libnumeric_error_format-0.1.1-Linux/usr/lib/numeric_error_format/



#add_library(HEADER_ONLY_TARGET STATIC test1.hpp test2.hpp)
#set_target_properties(HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)

