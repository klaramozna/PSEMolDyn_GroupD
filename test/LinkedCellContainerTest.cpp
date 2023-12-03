//
// Created by klara on 30.11.23.
//

#include "LinkedCellContainerTest.h"
#include <gtest/gtest.h>


TEST_F(LinkedCellContainerTest, Initialization){
    LennardJones force{1, 1};
    OutflowBoundary boundary{std::array<double, 3>{0, 0, 0}, std::array<double, 3>{4, 4, 3}, force};
    LinkedCellContainer container{boundary, 2};
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
    std::vector<Cell> grid = container.getCells();
    ASSERT_TRUE(grid[9].contains(p1));
    ASSERT_TRUE(grid[22].contains(p3));
    ASSERT_TRUE(grid[4].contains(p2));
    ASSERT_TRUE(grid[26].contains(p4));
}



