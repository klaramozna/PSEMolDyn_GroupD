//
// Created by klara on 30.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H

#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Simulation/OutflowBoundary.h"
#include "../src/Simulation/Physics/LennardJones.h"
#include <gtest/gtest.h>


class LinkedCellContainerTest : public testing::Test{
protected:
    LinkedCellContainer container = LinkedCellContainer(
                                        Boundary({0.0, 0.0, 0.0}, {4.0, 4.0, 3.0}, LennardJones(1.0, 1.0)),
                                        2.0
                                        );
    Particle p1{std::array<double, 3>{2, 0, 1}, std::array<double, 3>{}, 0};
    Particle p2{std::array<double, 3>{6.5, -1.5, 1}, std::array<double, 3>{}, 0};
    Particle p3{std::array<double, 3>{5.25, 4.1, 1}, std::array<double, 3>{}, 0};
    Particle p4{std::array<double, 3>{0.5, 6.1, 1}, std::array<double, 3>{}, 0};
public:

protected:
    void SetUp() override;
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
