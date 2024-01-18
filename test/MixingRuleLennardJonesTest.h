//
// Created by klara on 14.12.23.
//

#ifndef PSEMOLDYN_GROUPD_MIXINGRULELENNARDJONESTEST_H
#define PSEMOLDYN_GROUPD_MIXINGRULELENNARDJONESTEST_H


#include <gtest/gtest.h>
#include "../src/Simulation/Physics/MixingRuleLennardJones.h"
#include "../src/utils/CuboidGenerator.h"

class MixingRuleLennardJonesTest : public testing::Test{
protected:
    MixingRuleLennardJones lennardJones{};
    Particle p1{std::array<double, 3>{1, 0, 0}, std::array<double, 3>{}, 0, 50, 0.5, false};
    Particle p2{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{}, 0, 0.5, 1.5, false};
    CuboidGenerator cuboidGenerator{{0, 0, 0}, 2, 2, 2, 0.5, 1, {1, 1, 1}, 3, 4};
};


#endif //PSEMOLDYN_GROUPD_MIXINGRULELENNARDJONESTEST_H
