//
// Created by klara on 14.12.23.
//

#include "MixingRuleLennardJonesTest.h"

TEST_F(MixingRuleLennardJonesTest, calculation){
    VectorDouble3 result = lennardJones.CalculateForces(p1, p2);
    VectorDouble3 expected{std::array<double, 3>{120,0,0}};
    ASSERT_EQ(result, expected);
}
