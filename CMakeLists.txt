cmake_minimum_required(VERSION 3.14)

# define project name, version
project(PSEMolDyn_GroupD VERSION 0.0.1)

# Add CMake Modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# Includes
include(doxygen)
include(gtest)


# Set C++ requirements for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

enable_testing()

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Look for Xerces XML Parser, and raise an error if not found with instruction to install it
#comment this on the linux cluster
find_package(XercesC QUIET)

if(NOT XercesC_FOUND)
    message(FATAL_ERROR "Xerces XML Parser not found. You can install it with: sudo apt-get install libxerces-c-dev")
endif()

# Look for Boost program options
find_package(Boost QUIET COMPONENTS program_options)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost program options not found. You can install it with: sudo apt-get install libboost-program-options-dev")
endif()

# Extend current CMake to /src
add_subdirectory(src)


# Extend current CMake to /test if enabled
if (BUILD_GTESTS)
    add_subdirectory(test)
endif()




