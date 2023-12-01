//
// Created by klara on 30.11.23.
//

#include "LinkedCellContainerTest.h"
#include <gtest/gtest.h>


TEST_F(LinkedCellContainerTest, Initialization){
    std::vector<Cell> grid = container.getCells();
    ASSERT_TRUE(grid[9].contains(p1));
    ASSERT_TRUE(grid[22].contains(p3));
    ASSERT_TRUE(grid[4].contains(p2));
    ASSERT_TRUE(grid[26].contains(p4));
}


void LinkedCellContainerTest::SetUp() {
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
}
