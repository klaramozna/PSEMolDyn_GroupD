
#ifndef PSEMOLDYN_GROUPD_SIMPLETHERMOSTATTEST_H
#define PSEMOLDYN_GROUPD_SIMPLETHERMOSTATTEST_H

#include <gtest/gtest.h>
#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Simulation/SimpleThermostat.h"
#include "../src/Particles/Boundary.h"

// Define a mock ForceCalculation class for testing
class MockForceCalculation : public ForceCalculation {
public:
    // Override CalculateForces to return a known force vector for testing
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override {
        // You can customize this for your specific testing needs
        return p1.getXVector() - p2.getXVector();
    }
};

class SimpleThermostatTest : public testing::Test{
protected:
    MockForceCalculation fc{};
    LinkedCellContainer container{Boundary(4, 4, 4, 1.0, {}), 1};
    SimpleThermostat thermostat{10, 4, 3, 3};
    Particle p1{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p2{std::array<double, 3>{1, 0.5, 2}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p3{std::array<double, 3>{3, 2, 0}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p4{std::array<double, 3>{1, 0.3, 2}, std::array<double, 3>{1, 1, 1}, 1};
    void SetUp() override;
};


#endif //PSEMOLDYN_GROUPD_SIMPLETHERMOSTATTEST_H
