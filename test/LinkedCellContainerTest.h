//
// Created by klara on 30.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H

#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Simulation/Boundary.h"
#include <gtest/gtest.h>


class LinkedCellContainerTest : public testing::Test{
protected:
    LinkedCellContainer container{CuboidBoundary(4, 4, 3), 2};
    Particle p1{std::array<double, 3>{2, 0, 1}, std::array<double, 3>{}, 0};
    Particle p2{std::array<double, 3>{6.5, -1.5, 1}, std::array<double, 3>{}, 0};
    Particle p3{std::array<double, 3>{5.25, 4.1, 1}, std::array<double, 3>{}, 0};
    Particle p4{std::array<double, 3>{0.5, 6.1, 1}, std::array<double, 3>{}, 0};
    void SetUp() override;
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
