file(GLOB_RECURSE TEST_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

set(source_needed_for_test
        ${PROJECT_SOURCE_DIR}/src/ParticleContainer.cpp
        ${PROJECT_SOURCE_DIR}/src/ParticleContainer.h
        ${PROJECT_SOURCE_DIR}/src/Particle.cpp
        ${PROJECT_SOURCE_DIR}/src/Particle.h
        ${PROJECT_SOURCE_DIR}/src/utils/ArrayUtils.h
        ${PROJECT_SOURCE_DIR}/src/VectorDouble3.cpp
        ${PROJECT_SOURCE_DIR}/src/VectorDouble3.h
)

add_executable(
        particleContainer_test
        ${TEST_SRC}
        ${source_needed_for_test}
)

target_link_libraries(
        particleContainer_test
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(particleContainer_test)
