file(GLOB_RECURSE TEST_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
# Define the path to test resources relative to the project directory
set(TEST_RESOURCES_DIR ${CMAKE_SOURCE_DIR}/test/resources/)
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
        ${PROJECT_SOURCE_DIR}/src/utils/MembraneGenerator.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/MembraneGenerator.h
        ${PROJECT_SOURCE_DIR}/src/utils/SphereGenerator.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/SphereGenerator.h
        ${PROJECT_SOURCE_DIR}/src/Particles/LinkedCellContainer.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/LinkedCellContainer.h
        ${PROJECT_SOURCE_DIR}/src/Particles/Boundary.h
        ${PROJECT_SOURCE_DIR}/src/Particles/Boundary.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/ParticleContainer.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/ParticleContainer.h
        ${PROJECT_SOURCE_DIR}/src/Particles/Cell.h
        ${PROJECT_SOURCE_DIR}/src/Particles/Cell.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/input/XMLReader.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/input/CheckpointReader.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/input/SimParameters.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/output/outputWriter/CheckpointWriter.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/xsdCode/simulationFormat.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/xsdCode/checkpointFormat.cpp
        ${PROJECT_SOURCE_DIR}/src/IO/xsdCode/commonSchema.cpp   
        ${PROJECT_SOURCE_DIR}/src/IO/xsdCode/simulationFormat.cpp
        ${PROJECT_SOURCE_DIR}/src/Simulation/Thermostat.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/Thermostat.cpp
        ${PROJECT_SOURCE_DIR}/src/Simulation/SimpleThermostat.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/SimpleThermostat.cpp
        ${PROJECT_SOURCE_DIR}/src/Simulation/GradualThermostat.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/GradualThermostat.cpp
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/GravitationalForce.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/GravitationalForce.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/BoundaryEnforcer.cpp
        ${PROJECT_SOURCE_DIR}/src/Particles/BoundaryEnforcer.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/MixingRuleLennardJones.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/MixingRuleLennardJones.cpp
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/TruncatedLennardJones.h
        ${PROJECT_SOURCE_DIR}/src/Simulation/Physics/TruncatedLennardJones.cpp
        CuboidGeneratorTest.cpp
        CuboidGeneratorTest.h
        LinkedCellContainerTest.cpp
        LinkedCellContainerTest.h
        SimpleThermostatTest.cpp
        SimpleThermostatTest.h
        GradualThermostatTest.cpp
        GradualThermostatTest.h
        BoundaryTest.cpp
        BoundaryTest.h
        CheckpointTest.cpp
        MixingRuleLennardJonesTest.cpp
        MixingRuleLennardJonesTest.h
        PeriodicBoundaryTest.cpp
        PeriodicBoundaryTest.h
)

add_executable(
        particleContainer_test
        ${TEST_SRC}
        ${source_needed_for_test}
)

target_include_directories(particleContainer_test
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/libxsd
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

target_compile_definitions(particleContainer_test PRIVATE TEST_RESOURCES_DIR="${TEST_RESOURCES_DIR}")