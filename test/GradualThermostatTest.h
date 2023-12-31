//
// Created by klara on 10.12.23.
//

#ifndef PSEMOLDYN_GROUPD_GRADUALTHERMOSTATTEST_H
#define PSEMOLDYN_GROUPD_GRADUALTHERMOSTATTEST_H

#include <gtest/gtest.h>
#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Simulation/GradualThermostat.h"

class GradualThermostatTest : public testing::Test{
protected:
    LinkedCellContainer containerWarming{Boundary(4, 4, 4, 1, {}), 1};
    LinkedCellContainer containerCooling{Boundary(4, 4, 4, 1, {}), 1};
    GradualThermostat thermostatWarming{10, 4, 3, 3, 1};
    GradualThermostat thermostatCooling{10, 1, 3, 3, 1};
    Particle p1{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p2{std::array<double, 3>{1, 0.5, 2}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p3{std::array<double, 3>{3, 2, 0}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p4{std::array<double, 3>{1, 0.3, 2}, std::array<double, 3>{1, 1, 1}, 1};
    Particle p5{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{2, 2, 2}, 1};
    Particle p6{std::array<double, 3>{1, 0.5, 2}, std::array<double, 3>{2, 2, 2}, 1};
    Particle p7{std::array<double, 3>{3, 2, 0}, std::array<double, 3>{2, 2, 2}, 1};
    Particle p8{std::array<double, 3>{1, 0.3, 2}, std::array<double, 3>{2, 2, 2}, 1};
    void SetUp() override;
};


#endif //PSEMOLDYN_GROUPD_GRADUALTHERMOSTATTEST_H
