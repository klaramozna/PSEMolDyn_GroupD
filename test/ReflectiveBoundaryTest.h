//
// Created by rodff on 08.12.23.
//

#ifndef PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARYTEST_H
#define PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARYTEST_H

#include "../src/Particles/Particle.h"
#include "../src/utils/VectorDouble3.h"
#include "../src/Simulation/Physics/ForceCalculation.h"

#include "../src/Particles/BoundaryEnforcer.h"

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
    LinkedCellContainer container{Boundary(3, 3, 3, 1, {}), 1};
    BoundaryEnforcer boundaryEnforcer{1.0,container, {3.0, 3.0, 3.0}, {BoundaryType::REFLECTIVE, BoundaryType::REFLECTIVE,BoundaryType::REFLECTIVE,BoundaryType::REFLECTIVE, BoundaryType::REFLECTIVE,BoundaryType::REFLECTIVE},fc};
    MockForceCalculation fc{};
};


#endif //PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARYTEST_H
