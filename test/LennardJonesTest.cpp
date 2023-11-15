#include "LennardJonesTest.h"


/**
 * @brief Ensures that initialization works fine
 * */
TEST_F(LennardJonesTest, Initialization) {
    ASSERT_EQ(lennardJones.getEpsilon(), 5);
    ASSERT_EQ(lennardJones.getSigma(), 1);
}

/**
 * @brief check implementation correctness against manually-calculated values
 **/

TEST_F(LennardJonesTest, Calculation) {
    Particle particle1({1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);  
    Particle particle2({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    VectorDouble3 *result = lennardJones.CalculateForces(particle1, particle2);
    VectorDouble3 expected{std::array<double,3>{120,0,0}};
    ASSERT_EQ(*result, expected);
}