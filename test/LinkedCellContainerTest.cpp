//
// Created by klara on 30.11.23.
//

#include "LinkedCellContainerTest.h"
#include "../src/utils/ArrayUtils.h"
#include <memory>


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
    container.deleteHaloParticles();
    std::vector<Cell> grid = container.getCells();
    ASSERT_TRUE(grid[44].contains(p1));
    ASSERT_TRUE(grid[57].contains(p3));
    ASSERT_FALSE(grid[40].contains(p2));
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
            if(p->getX() == p1.getX()){
                ASSERT_EQ(p->getV()[0], 0) << "p1";
            }
            if(p->getX() == p2.getX()){
                ASSERT_EQ(p->getV()[0], 2) << "p2";
            }
            if(p->getX() == p3.getX()){
                ASSERT_EQ(p->getV()[0], 1)  << "p3";
            }
            if(p->getX() == p4.getX()){
                ASSERT_EQ(p->getV()[0], 0) << "p4";
            }
            if(p->getX() == neighbourP2_1.getX()){
                ASSERT_EQ(p->getV()[0], 1) << "p2_1";
            }
            if(p->getX() == neighbourP2_2.getX()){
                ASSERT_EQ(p->getV()[0], 1) << "p2_2";
            }
            if(p->getX() == neighbourP3_1.getX()){
                ASSERT_EQ(p->getV()[0], 1) << "p3_1";
            }
        }
    }
}

TEST_F(LinkedCellContainerTest, applyToBoundary){
    boundaryContainer.applyToBoundary([](Particle &p) {
        p.setV(VectorDouble3(std::array<double, 3>{50, 50, 50}));
    });

    std::vector<Cell> grid = boundaryContainer.getCells();

    // Making sure boundary particles were changed and no longer have their old values
    ASSERT_FALSE(grid[61].contains(boundary2));

    // Making sure boundary cells contain the changed boundary particles
    ASSERT_TRUE(grid[61].contains(boundaryChanged2));

    // Making sure other particles remained unchanged
    ASSERT_TRUE(grid[62].contains(boundary1));
    ASSERT_EQ(boundaryContainer.getSize(), 2);
}

TEST_F(LinkedCellContainerTest, wrongAligment){
    // Make sure particles are put into correct cells.
    std::vector<Cell> grid = wrongAlignmentContainer.getCells();
    // Check the cellsize in each dimension
    EXPECT_DOUBLE_EQ(wrongAlignmentContainer.getCellSize()[0], 1.5);
    EXPECT_DOUBLE_EQ(wrongAlignmentContainer.getCellSize()[1], 1.66666666666666666666666666666666666666666666666666666666666666666666666);
    EXPECT_DOUBLE_EQ(wrongAlignmentContainer.getCellSize()[2], 1.5);
    ASSERT_TRUE(grid[61].contains(p1WrongAlignment));
    ASSERT_TRUE(grid[68].contains(p2WrongAlignment));
    ASSERT_TRUE(grid[73].contains(p3WrongAlignment));
    ASSERT_EQ(wrongAlignmentContainer.getSize(), 3);
}

TEST_F(LinkedCellContainerTest, wrongAlignmentBoundary){
    wrongAlignmentContainer.applyToBoundary([](Particle &p) {
        p.setV(VectorDouble3(std::array<double, 3>{50, 50, 50}));
    });

    std::vector<Cell> grid = wrongAlignmentContainer.getCells();

    // Making sure boundary particles were changed and no longer have their old values
    ASSERT_FALSE(grid[68].contains(p2WrongAlignment));
    ASSERT_FALSE(grid[73].contains(p3WrongAlignment));

    // Making sure boundary cells contain the changed boundary particles
    ASSERT_TRUE(grid[68].contains(p2BoundaryWrongAlignment));
    ASSERT_TRUE(grid[73].contains(p3BoundaryWrongAlignment));

    // Making sure other particles remained unchanged
    ASSERT_TRUE(grid[61].contains(p1WrongAlignment));
    ASSERT_EQ(wrongAlignmentContainer.getSize(), 3);
}

TEST_F(LinkedCellContainerTest, pointerTest){
    Particle p{{-0.5, -0.5, -0.5}, {}, 1};
    pointerContainer.addParticle(p);
    auto pointerIterator = pointerContainer.getCells()[0].begin();
    std::shared_ptr<Particle> pointer = *pointerIterator;
    Particle *pAddress = &(*pointer);

    pointerContainer.applyToAll([](Particle& p){p.setX(p.getXVector() + VectorDouble3({1, 0, 0}));});

    ASSERT_EQ(pAddress, &(*(*(pointerContainer.getCells()[1].begin()))));

}

TEST_F(LinkedCellContainerTest, pointerInMain){
    std::shared_ptr<Particle> pointer = std::make_shared<Particle>(Particle{{-0.5, -0.5, -0.5}, {}, 1});
    pointerContainer.addParticlePointer(pointer);
    pointerContainer.applyToAll([](Particle& p){p.setX(p.getXVector() + VectorDouble3({1, 0, 0}));});
    ASSERT_EQ(&(*pointer), &(*(*(pointerContainer.getCells()[1].begin()))));
}



void LinkedCellContainerTest::SetUp() {
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
    std::vector<Particle> boundary{boundary1, boundary2};
    boundaryContainer.addParticles(boundary);
    std::vector<Particle> wrongAlignmentParticles{p1WrongAlignment, p2WrongAlignment, p3WrongAlignment};
    wrongAlignmentContainer.addParticles(wrongAlignmentParticles);
}
