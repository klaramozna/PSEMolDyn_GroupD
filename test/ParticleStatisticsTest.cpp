//
// Created by klara on 29.01.24.
//

#include "ParticleStatisticsTest.h"


TEST_F(ParticleStatisticsTest, calculateStatistics){
    std::vector<std::pair<VectorDouble3, double>> statsActual = statistics.calculateStatisticsTest({p1, p2, p3, p4, p5, p6});
    std::vector<std::pair<VectorDouble3, double>> statsExpected = {{VectorDouble3({7, 7, 7}), 0.0625}, {VectorDouble3({3, 3, 3}), 0.125}};
    ASSERT_EQ(statsActual, statsExpected);
}
