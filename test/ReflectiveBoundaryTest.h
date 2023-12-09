//
// Created by rodff on 08.12.23.
//

#ifndef PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARYTEST_H
#define PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARYTEST_H

#include "../src/Particles/Particle.h"
#include "../src/utils/VectorDouble3.h"
#include "../src/Simulation/Physics/ForceCalculation.h"

#include "../src/Particles/ReflectiveBoundary.h"

#include <gtest/gtest.h>

// Define a mock ForceCalculation class for testing
class MockForceCalculation : public ForceCalculation {
public:
    // Override CalculateForces to return a known force vector for testing
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override {
        // You can customize this for your specific testing needs
        return p1.getXVector() - p2.getXVector();
    }
};


class ReflectiveBoundaryTest : public ::testing::Test {
public:
    ReflectiveBoundary boundary{3.0, 3.0, 1.0};
    MockForceCalculation fc{};
};


#endif //PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARYTEST_H
