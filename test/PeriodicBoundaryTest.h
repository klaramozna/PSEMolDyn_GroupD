#pragma once

#include <gtest/gtest.h>

#include "../src/Particles/BoundaryEnforcer.h"

class MockForceCalculation : public ForceCalculation {
public:
    // Override CalculateForces to return a known force vector for testing
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override {
        // You can customize this for your specific testing needs
        return p1.getXVector() - p2.getXVector();
    }
};


class PeriodicBoundaryTest : public ::testing::Test {
public:
    LinkedCellContainer container{Boundary(5, 5, 5, 1, {}), 1};
    BoundaryEnforcer boundaryEnforcer{1.0,container, {5.0, 5.0, 5.0}, {BoundaryType::PERIODIC, BoundaryType::PERIODIC,BoundaryType::PERIODIC,BoundaryType::PERIODIC, BoundaryType::PERIODIC,BoundaryType::PERIODIC},fc};
    MockForceCalculation fc{};

    void areParticlesContained(const std::vector<Particle>& toFind, const std::vector<Particle> &particles);
};