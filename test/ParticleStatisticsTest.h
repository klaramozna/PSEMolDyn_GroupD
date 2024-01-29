//
// Created by klara on 29.01.24.
//

#ifndef PSEMOLDYN_GROUPD_PARTICLESTATISTICSTEST_H
#define PSEMOLDYN_GROUPD_PARTICLESTATISTICSTEST_H

#include <gtest/gtest.h>
#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Particles/ParticleStatistics.h"
#include "../src/Particles/Boundary.h"

class ParticleStatisticsTest : public testing::Test{
protected:
    ParticleStatistics statistics{Boundary(4, 4, 4, 1.0, {}), 2, 3};
    // Bin 1
    Particle p5{std::array<double, 3>{3.5, 2.5, 3}, std::array<double, 3>{8, 8, 8}, 1};
    Particle p6{std::array<double, 3>{0.5, 3, 2}, std::array<double, 3>{6, 6, 6}, 1};

    // Bin 2
    Particle p1{std::array<double, 3>{0.1, 0.1, 3}, std::array<double, 3>{2, 2, 2}, 1};
    Particle p2{std::array<double, 3>{0.5, 0.8, 2}, std::array<double, 3>{2, 2, 2}, 1};
    Particle p3{std::array<double, 3>{1, 1.5, 1}, std::array<double, 3>{4, 4, 4}, 1};
    Particle p4{std::array<double, 3>{2.5, 1.8, 2}, std::array<double, 3>{4, 4, 4}, 1};
};


#endif //PSEMOLDYN_GROUPD_PARTICLESTATISTICSTEST_H
