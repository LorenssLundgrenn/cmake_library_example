cmake_minimum_required(VERSION 3.28)
project(my-library LANGUAGES CXX)

# cmake module that provides definitions for standard installation 
# directories
include(GNUInstallDirs)
# module that adds functions and definitions to generate cmake config 
# files to make it easier to find the library with find_package()
include(CMakePackageConfigHelpers)

# define global build variables

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SRC "${SRC_DIR}/*.cpp") # all .cpp files in source directory

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB INCLUDE_FILES 
"${INCLUDE_DIR}/*.h"
"${INCLUDE_DIR}/*.hpp"
) # all header files in include directory

# define global library configuration variables

set(LIB_TARGET mytarget)
set(LIB_EXPORT_SET ${LIB_TARGET}-targets)
set(LIB_PCKG_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_TARGET})

if(BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE SHARED)
else()
    set(LIBRARY_TYPE STATIC)
endif()

# configure library

# set the name of our library target, specify library type
# and associated source files
add_library(${LIB_TARGET} ${LIBRARY_TYPE} ${SRC})
set_target_properties(${LIB_TARGET}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

# define a preprocessor macro for the target. defines 
# USE_BUILD_SYMBOLS macro used in shared.hpp
target_compile_definitions(${LIB_TARGET}
    PRIVATE USE_BUILD_SYMBOLS # PRIVATE: applies only to the target itself.
                              # the program importing the library will not
                              # have this macro defined
)

# define a macro for if we are building a shared library
if(BUILD_SHARED_LIBS)
    target_compile_definitions(${LIB_TARGET}
        PRIVATE IS_SHARED
    )
endif()

# tell the linker which directory to link from when building
# and installing the library
target_include_directories(${LIB_TARGET}
    PUBLIC 
        "$<BUILD_INTERFACE:${INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# specify directory where to install header files to
install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# configure installation of the library target.
# using standard installation directories
install(TARGETS ${LIB_TARGET}                           # specify target to configure
    EXPORT ${LIB_EXPORT_SET}                            # link target to an export set
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}         # shared library directory
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}         # static library directory
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}         # binary directory
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}    # include directory
)

# configure the export set.
install(EXPORT ${LIB_EXPORT_SET}        # specify export set to configure
    FILE ${LIB_EXPORT_SET}.cmake        # set the name of the export set file, ends with .cmake
    NAMESPACE ${LIB_TARGET}::           # specify prefix to specify targets from this export set
    DESTINATION ${LIB_PCKG_CONFIG_DIR}  # destination for the .cmake file
)

# generate helper configuration files

# this function accepts a template file to generate a Cmake.config file.
# the Cmake.config file tells a cmake project how to use your library
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in                 # input template file
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Config.cmake"     # output config file (temp)
    INSTALL_DESTINATION ${LIB_PCKG_CONFIG_DIR}                  # specify install directory for config file
)

# installs the Config.make file in the requested destination
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Config.cmake"     
    DESTINATION ${LIB_PCKG_CONFIG_DIR}                              
)

# still, cmake won't be able to find the library on windows.
# one easy fix is to rename the installation directory to match the library target.
# However it's better to help cmake find the library by specifying the install
# directory through CMakePresets.json