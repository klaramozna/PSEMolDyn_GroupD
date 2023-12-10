
#ifndef PSEMOLDYN_GROUPD_SIMPLETHERMOSTATTEST_H
#define PSEMOLDYN_GROUPD_SIMPLETHERMOSTATTEST_H

#include <gtest/gtest.h>
#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Simulation/SimpleThermostat.h"

class SimpleThermostatTest : public testing::Test{
protected:
    LinkedCellContainer container{CuboidBoundary(4, 4, 4), 1};
    SimpleThermostat thermostat{10, 4, 3, 3};
    Particle p1{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p2{std::array<double, 3>{1, 0.5, 2}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p3{std::array<double, 3>{3, 2, 0}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p4{std::array<double, 3>{1, 0.3, 2}, std::array<double, 3>{1, 1, 1}, 1};
    void SetUp() override;
};


#endif //PSEMOLDYN_GROUPD_SIMPLETHERMOSTATTEST_H
