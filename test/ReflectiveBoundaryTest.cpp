//
// Created by rodff on 08.12.23.
//

#include "ReflectiveBoundaryTest.h"
#include "../src/utils/ArrayUtils.h"

/* Tests for the 2D Case */

TEST_F(ReflectiveBoundaryTest, TwoD_LeftX) {
    Particle p = Particle({0.3, 1.5 , 1}, {}, 0);
    Particle pOpposite = Particle({-0.3, 1.5, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_RightX) {
    Particle p = Particle({2.8, 1.5, 1}, {}, 0);
    Particle pOpposite = Particle({3.2, 1.5, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_TopY) {
    Particle p = Particle({1.5, 2.5, 1}, {}, 0);
    Particle pOpposite = Particle({1.5, 3.5, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_LowerY) {
    Particle p = Particle({1.5, 0.1, 1}, {}, 0);
    Particle pOpposite = Particle({1.5, -0.1, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_TopLeftCorner) {
    Particle p = Particle({0.2, 2.7, 1}, {}, 0);
    Particle pOpposite = Particle({-0.2, 3.3, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_TopRightCorner) {
    Particle p = Particle({2.9, 2.6, 1}, {}, 0);
    Particle pOpposite = Particle({3.1, 3.4, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_LowerLeftCorner) {
    Particle p = Particle({0.2, 0.2, 1}, {}, 0);
    Particle pOpposite = Particle({-0.2, -0.2, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(ReflectiveBoundaryTest, TwoD_LowerRightCorner) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundary.applyBoundaryToParticle(p, fc, 1);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

