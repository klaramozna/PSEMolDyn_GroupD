//
// Created by klara on 29.01.24.
//

#ifndef PSEMOLDYN_GROUPD_TEMPDIFFRENCETHERMOSTATTEST_H
#define PSEMOLDYN_GROUPD_TEMPDIFFRENCETHERMOSTATTEST_H

#include <gtest/gtest.h>
#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Simulation/TempDifferenceThermostat.h"
#include "../src/Particles/Boundary.h"

class TempDiffrenceThermostatTest : public testing::Test {
protected:
    void SetUp() override;
    LinkedCellContainer container{Boundary(4, 4, 4, 1.0, {}), 1};
    TempDifferenceThermostat thermostat{10, 4, 3, 3};
    Particle p1{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{4, 4, 4}, 1};
    Particle p2{std::array<double, 3>{1, 0.5, 2}, std::array<double, 3>{2, 2, 2}, 1};
    Particle p3{std::array<double, 3>{3, 2, 0}, std::array<double, 3>{3, 3, 3}, 1};
    Particle p4{std::array<double, 3>{1, 0.3, 2}, std::array<double, 3>{1, 1, 1}, 1};

};


#endif //PSEMOLDYN_GROUPD_TEMPDIFFRENCETHERMOSTATTEST_H
