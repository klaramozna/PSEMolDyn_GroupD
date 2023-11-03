cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PSEMolDyn_GroupD_Tests VERSION 1.0)

# Include Boost.Test
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Gather the test source files
file(GLOB TEST_SOURCE_FILES "*.cpp")

set(SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/Simulation.cpp
)

# Create a test target for each test suite or case
foreach(TEST_SOURCE_FILE ${TEST_SOURCE_FILES})
    get_filename_component(TEST_NAME ${TEST_SOURCE_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE_FILE})
    target_link_libraries(${TEST_NAME} Boost::unit_test_framework MolSimLib)
    # Register each test target with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

