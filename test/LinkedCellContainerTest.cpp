//
// Created by klara on 30.11.23.
//

#include "LinkedCellContainerTest.h"
#include <gtest/gtest.h>


TEST_F(LinkedCellContainerTest, Initialization){
    // Make sure particles are put into correct cells.
    std::vector<Cell> grid = container.getCells();
    ASSERT_TRUE(grid[44].contains(p1));
    ASSERT_TRUE(grid[57].contains(p3));
    ASSERT_TRUE(grid[40].contains(p2));
    ASSERT_TRUE(grid[61].contains(p4));
    ASSERT_EQ(container.getSize(), 4);
}

TEST_F(LinkedCellContainerTest, deleteHaloParticles){
    std::vector<Cell> grid = container.getCells();
    container.deleteHaloParticles();
    ASSERT_TRUE(grid[44].contains(p1));
    ASSERT_FALSE(grid[57].contains(p3));
    ASSERT_TRUE(grid[40].contains(p2));
    ASSERT_TRUE(grid[61].contains(p4));
    ASSERT_EQ(container.getSize(), 3);
}

TEST_F(LinkedCellContainerTest, applyToAll){
    // Shifting all particles down by 2
    container.applyToAll([this](Particle& p){p.setX(p.getXVector() - VectorDouble3(std::array<double, 3>{0, 2,  0}));});
    std::vector<Cell> grid = container.getCells();
    // Making sure the particles were removed from their old cells
    ASSERT_FALSE(grid[44].contains(p1));
    ASSERT_FALSE(grid[57].contains(p3));
    ASSERT_FALSE(grid[40].contains(p2));
    ASSERT_FALSE(grid[61].contains(p4));

    // Making sure the particles were added to their correct cells
    ASSERT_TRUE(grid[38].contains(p1Shifted));
    ASSERT_TRUE(grid[51].contains(p3Shifted));
    ASSERT_TRUE(grid[55].contains(p4Shifted));

    // Making sure that particle p2 that was shifted out of the grid is not contained in the grid
    for(auto & cell : grid){
        ASSERT_FALSE(cell.contains(p2Shifted));
    }
    ASSERT_EQ(container.getSize(), 3);
}

TEST_F(LinkedCellContainerTest, applyToPairs){
    // Particles that will affect p2
    Particle neighbourP2_1{std::array<double, 3>{6.5, 0.25, 0.5}, std::array<double, 3>{}, 0};
    Particle neighbourP2_2{std::array<double, 3>{8.4, -1.5, 0.5}, std::array<double, 3>{}, 0};

    // Particle that will affect p3
    Particle neighbourP3_1{std::array<double, 3>{5, 4.1, 0.5}, std::array<double, 3>{}, 0};

    // Adding neighbours
    container.addParticle(neighbourP2_1);
    container.addParticle(neighbourP2_2);
    container.addParticle(neighbourP3_1);

    // Apply function (the velocity vector will indicate how many neighbours were considered)
    container.applyToPairs([this](Particle& p1, Particle& p2){
        p1.setV(p1.getVVector() + VectorDouble3(std::array<double, 3>{1, 1, 1}));
        p2.setV(p2.getVVector() + VectorDouble3(std::array<double, 3>{1, 1, 1}));
    });

    // Check if each particle has the correct number of neighbours
    std::vector<Cell> grid = container.getCells();
    for(auto & cell : grid){
        for(auto & p : cell){
            if(p.getX() == p1.getX()){
                ASSERT_EQ(p.getV()[0], 0) << "p1";
            }
            if(p.getX() == p2.getX()){
                ASSERT_EQ(p.getV()[0], 2) << "p2";
            }
            if(p.getX() == p3.getX()){
                ASSERT_EQ(p.getV()[0], 1)  << "p3";
            }
            if(p.getX() == p4.getX()){
                ASSERT_EQ(p.getV()[0], 0) << "p4";
            }
            if(p.getX() == neighbourP2_1.getX()){
                ASSERT_EQ(p.getV()[0], 1) << "p2_1";
            }
            if(p.getX() == neighbourP2_2.getX()){
                ASSERT_EQ(p.getV()[0], 1) << "p2_2";
            }
            if(p.getX() == neighbourP3_1.getX()){
                ASSERT_EQ(p.getV()[0], 1) << "p3_1";
            }
        }
    }
}

TEST_F(LinkedCellContainerTest, applyToBoundary){
    container.applyToBoundary([this](Particle& p){p.setV(VectorDouble3(std::array<double, 3>{50, 50, 50}));});
    ASSERT_EQ(p4.getV(), (std::array<double, 3>{50, 50, 50}));
    ASSERT_EQ(p1.getV(), (std::array<double, 3>{50, 50, 50}));
    ASSERT_EQ(p2.getV(), (std::array<double, 3>{0, 0, 0}));
    ASSERT_EQ(p3.getV(), (std::array<double, 3>{0, 0, 0}));
}

void LinkedCellContainerTest::SetUp() {
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
}
