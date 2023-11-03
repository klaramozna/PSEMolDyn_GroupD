cmake_minimum_required(VERSION 3.10)

# define project name, version
project(PSEMolDyn_GroupD VERSION 0.0.1)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Look for Xerces XML Parser, and raise an error if not found with instruction to install it
find_package(XercesC QUIET)

if(NOT XercesC_FOUND)
    message(FATAL_ERROR "Xerces XML Parser not found. You can install it with: sudo apt-get install libxerces-c-dev")
endif()

# Look for Boost program options
find_package(Boost QUIET COMPONENTS program_options unit_test_framework)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost program options and/or test-dev not found. You can install it with: sudo apt-get install libboost-program-options-dev or sudo apt-get install libboost-test-dev")
endif()


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

include(doxygen)
include(CTest)

add_subdirectory(src)
#add_subdirectory(test)

enable_testing()





