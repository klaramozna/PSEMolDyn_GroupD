//
// Created by klara on 30.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H

#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Particles/Boundary.h"
#include <gtest/gtest.h>


class LinkedCellContainerTest : public testing::Test{
protected:
    LinkedCellContainer container{Boundary(8, 8, 2), 2};
    Particle p1{std::array<double, 3>{2, 0, 0.5}, std::array<double, 3>{}, 0};
    Particle p2{std::array<double, 3>{6.5, -1.5, 0.5}, std::array<double, 3>{}, 0};
    Particle p3{std::array<double, 3>{5.25, 4.1, 0.5}, std::array<double, 3>{}, 0};
    Particle p4{std::array<double, 3>{0.5, 6.1, 0.5}, std::array<double, 3>{}, 0};

    Particle p1Shifted{std::array<double, 3>{2, 0-2, 0.5}, std::array<double, 3>{}, 0};
    Particle p2Shifted{std::array<double, 3>{6.5, -1.5-2, 0.5}, std::array<double, 3>{}, 0};
    Particle p3Shifted{std::array<double, 3>{5.25, 4.1-2, 0.5}, std::array<double, 3>{}, 0};
    Particle p4Shifted{std::array<double, 3>{0.5, 6.1-2, 0.5}, std::array<double, 3>{}, 0};
    void SetUp() override;
    LinkedCellContainer boundaryContainer{Boundary(3, 3, 3), 1};
    Particle boundary1{std::array<double, 3>{1.5, 1.5, 1.5}, std::array<double, 3>{}, 0};
    Particle boundary2{std::array<double, 3>{0.5, 1.5, 1.5}, std::array<double, 3>{}, 0};
    Particle boundaryChanged2{std::array<double, 3>{0.5, 1.5, 1.5}, std::array<double, 3>{50, 50, 50}, 0};
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
