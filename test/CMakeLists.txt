file(GLOB_RECURSE TEST_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

set(source_needed_for_test
        ${PROJECT_SOURCE_DIR}/src/Particles/DirectSumContainer.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/DirectSumContainer.h
        ${PROJECT_SOURCE_DIR}/src/Particles/ParticleContainer.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/ParticleContainer.h
        ${PROJECT_SOURCE_DIR}/src/Particles/Particle.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/Particle.h
        ${PROJECT_SOURCE_DIR}/src/utils/ArrayUtils.h
        ${PROJECT_SOURCE_DIR}/src/utils/VectorDouble3.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/VectorDouble3.h
        ${PROJECT_SOURCE_DIR}/src/IO/input/CuboidReader.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/input/CuboidReader.h
        ${PROJECT_SOURCE_DIR}/src/IO/Logger.h
        ${PROJECT_SOURCE_DIR}/src/IO/Logger.cpp
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/LennardJones.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/LennardJones.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/CuboidGenerator.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/CuboidGenerator.h
        ${PROJECT_SOURCE_DIR}/src/IO/input/XMLReader.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/input/SimParameters.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/input/simulationFormat.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/Cell.cpp 
        ${PROJECT_SOURCE_DIR}/src/Particles/LinkedCellContainer.cpp 
        ${PROJECT_SOURCE_DIR}/src/Particles/Boundary.cpp 
        ${PROJECT_SOURCE_DIR}/src/Particles/CuboidBoundary.cpp 
        CuboidGeneratorTest.cpp
        CuboidGeneratorTest.h
        LinkedCellContainerTest.cpp
        LinkedCellContainerTest.h
)

add_executable(
        particleContainer_test
        ${TEST_SRC}
        ${source_needed_for_test}
)

target_include_directories(particleContainer_test
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/
)

target_link_libraries(
        particleContainer_test
        GTest::gtest
        GTest::gtest_main
        xerces-c
)
include(GoogleTest)
gtest_discover_tests(particleContainer_test)
