cmake_minimum_required(VERSION 3.5)
project(tip VERSION 0.0.1 DESCRIPTION "A tiny INI parser")

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds with the option CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#=== SETTING LIBRARY ===#
add_library(tip SHARED tip/tip.cpp)
set_target_properties(tip PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER tip/tip.h)
target_include_directories(tip PRIVATE .)
target_compile_features( tip PUBLIC cxx_std_17 )


#=== SETTING VARIABLES ===#
# Compiling flags
set( CXX_COMPILE_FLAGS "-Wall -pedantic" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS}" )


#=== SETTING TEST APP ===#
include_directories(tip)
add_executable(driver_tip examples/driver_tip.cpp)
# define C++17 as the standard.
target_compile_features( driver_tip PUBLIC cxx_std_17 )
# Define target and its dependency
target_link_libraries( driver_tip PRIVATE tip )


#=== SYSTEM WIDE INSTALLATION ===#
include(GNUInstallDirs)
configure_file(tip.pc.in tip.pc @ONLY)
install(TARGETS tip
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/tip.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
