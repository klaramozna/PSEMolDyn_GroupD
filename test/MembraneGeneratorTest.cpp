#include "MembraneGeneratorTest.h"
#include "../src/Particles/DirectSumContainer.h"
#include "../src/Particles/LinkedCellContainer.h"


TEST_F(MembraneGeneratorTest, Generating){

    LinkedCellContainer lc {Boundary(9, 9, 9, 1.0, {"Reflective", "Reflective","Reflective","Reflective","Reflective","Reflective"}), 2};
    lc.addParticlesPointer(generator.generateParticles());
    std::array<double, 3> velocity{0, 0, 0};
    double mass = 1;
    std::vector<Particle> result = lc.getParticleVector();
    //sort the ids because getParticleVector does not iterate the same way as the membrane generator
    std::sort(result.begin(), result.end(), [](const Particle& a, const Particle& b) {
        return a.getId() < b.getId();
    });

    // 9 particles were generated
    ASSERT_EQ(result.size(), 9);
    // positions of the particles
    ASSERT_EQ(result[0], Particle(std::array<double, 3>{0, 0, 0}, velocity, mass));
    ASSERT_EQ(result[1], Particle(std::array<double, 3>{0, 1, 0}, velocity, mass));
    ASSERT_EQ(result[2], Particle(std::array<double, 3>{0, 2, 0}, velocity, mass));
    ASSERT_EQ(result[3], Particle(std::array<double, 3>{1, 0, 0}, velocity, mass));
    ASSERT_EQ(result[4], Particle(std::array<double, 3>{1, 1, 0}, velocity, mass));
    ASSERT_EQ(result[5], Particle(std::array<double, 3>{1, 2, 0}, velocity, mass));
    ASSERT_EQ(result[6], Particle(std::array<double, 3>{2, 0, 0}, velocity, mass));
    ASSERT_EQ(result[7], Particle(std::array<double, 3>{2, 1, 0}, velocity, mass));
    ASSERT_EQ(result[8], Particle(std::array<double, 3>{2, 2, 0}, velocity, mass));
    
    /*so it the rectangular grid of this membrane (in terms of particle ids)

    2 --- 5 --- 8
    |     |     |
    1 --- 4 --- 7
    |     |     |
    0 --- 3 --- 6

    */

    //The following are the tests for all particles: check the parallel and diagonal neighbous of all 9 particles (see the grid above for reference)

    //particle at index 0
    std::vector<int> parallel_neighbors_of_0 = {1, 3};
    std::vector<int> diagonal_neighbors_of_0 = {4};

    std::vector<int> expected_parallel_neighbors_of_0 = getParticleIds(result[0].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_0.begin(),expected_parallel_neighbors_of_0.end());

    std::vector<int> expected_diagonal_neighbors_of_0 = getParticleIds(result[0].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_0.begin(),expected_diagonal_neighbors_of_0.end());


    ASSERT_EQ(parallel_neighbors_of_0, expected_parallel_neighbors_of_0);
    ASSERT_EQ(diagonal_neighbors_of_0, expected_diagonal_neighbors_of_0);

    //particle at index 1

    std::vector<int> parallel_neighbors_of_1 = {0, 2, 4};
    std::vector<int> diagonal_neighbors_of_1 = {3, 5};

    std::vector<int> expected_parallel_neighbors_of_1 = getParticleIds(result[1].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_1.begin(),expected_parallel_neighbors_of_1.end());

    std::vector<int> expected_diagonal_neighbors_of_1 = getParticleIds(result[1].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_1.begin(),expected_diagonal_neighbors_of_1.end());


    ASSERT_EQ(parallel_neighbors_of_1, expected_parallel_neighbors_of_1);
    ASSERT_EQ(diagonal_neighbors_of_1, expected_diagonal_neighbors_of_1);


    //particle at index 2

    std::vector<int> parallel_neighbors_of_2 = {1,5};
    std::vector<int> diagonal_neighbors_of_2 = {4};

     std::vector<int> expected_parallel_neighbors_of_2 = getParticleIds(result[2].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_2.begin(),expected_parallel_neighbors_of_2.end());

    std::vector<int> expected_diagonal_neighbors_of_2 = getParticleIds(result[2].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_2.begin(),expected_diagonal_neighbors_of_2.end());


    ASSERT_EQ(parallel_neighbors_of_2, expected_parallel_neighbors_of_2);
    ASSERT_EQ(diagonal_neighbors_of_2, expected_diagonal_neighbors_of_2);

     //particle at index 3

    std::vector<int> parallel_neighbors_of_3 = {0, 4, 6};
    std::vector<int> diagonal_neighbors_of_3 = {1, 7};

     std::vector<int> expected_parallel_neighbors_of_3 = getParticleIds(result[3].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_3.begin(),expected_parallel_neighbors_of_3.end());

    std::vector<int> expected_diagonal_neighbors_of_3 = getParticleIds(result[3].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_3.begin(),expected_diagonal_neighbors_of_3.end());


    ASSERT_EQ(parallel_neighbors_of_3, expected_parallel_neighbors_of_3);
    ASSERT_EQ(diagonal_neighbors_of_3, expected_diagonal_neighbors_of_3);



    //particle at index 4
    std::vector<int> parallel_neighbors_of_4 = {1, 3, 5, 7};
    std::vector<int> diagonal_neighbors_of_4 = {0, 2 ,6 ,8};

    std::vector<int> expected_parallel_neighbors_of_4 = getParticleIds(result[4].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_4.begin(),expected_parallel_neighbors_of_4.end());

    std::vector<int> expected_diagonal_neighbors_of_4 = getParticleIds(result[4].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_4.begin(),expected_diagonal_neighbors_of_4.end());


    ASSERT_EQ(parallel_neighbors_of_4, expected_parallel_neighbors_of_4);
    ASSERT_EQ(diagonal_neighbors_of_4, expected_diagonal_neighbors_of_4);



    //particle at index 5
    std::vector<int> parallel_neighbors_of_5 = {2, 4, 8};
    std::vector<int> diagonal_neighbors_of_5 = {1, 7};

    std::vector<int> expected_parallel_neighbors_of_5 = getParticleIds(result[5].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_5.begin(),expected_parallel_neighbors_of_5.end());

    std::vector<int> expected_diagonal_neighbors_of_5 = getParticleIds(result[5].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_5.begin(),expected_diagonal_neighbors_of_5.end());


    ASSERT_EQ(parallel_neighbors_of_5, expected_parallel_neighbors_of_5);
    ASSERT_EQ(diagonal_neighbors_of_5, expected_diagonal_neighbors_of_5);


    //particle at index 6
    std::vector<int> parallel_neighbors_of_6 = {3, 7};
    std::vector<int> diagonal_neighbors_of_6 = {4};

    std::vector<int> expected_parallel_neighbors_of_6 = getParticleIds(result[6].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_6.begin(),expected_parallel_neighbors_of_6.end());

    std::vector<int> expected_diagonal_neighbors_of_6 = getParticleIds(result[6].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_6.begin(),expected_diagonal_neighbors_of_6.end());


    ASSERT_EQ(parallel_neighbors_of_6, expected_parallel_neighbors_of_6);
    ASSERT_EQ(diagonal_neighbors_of_6, expected_diagonal_neighbors_of_6);

    //particle at index 7
    std::vector<int> parallel_neighbors_of_7 = {4, 6, 8};
    std::vector<int> diagonal_neighbors_of_7 = {3, 5};

    std::vector<int> expected_parallel_neighbors_of_7 = getParticleIds(result[7].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_7.begin(),expected_parallel_neighbors_of_7.end());

    std::vector<int> expected_diagonal_neighbors_of_7 = getParticleIds(result[7].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_7.begin(),expected_diagonal_neighbors_of_7.end());


    ASSERT_EQ(parallel_neighbors_of_7, expected_parallel_neighbors_of_7);
    ASSERT_EQ(diagonal_neighbors_of_7, expected_diagonal_neighbors_of_7);

    //particle at index 8 
    std::vector<int> parallel_neighbors_of_8 = {5, 7};
    std::vector<int> diagonal_neighbors_of_8 = {4};

    std::vector<int> expected_parallel_neighbors_of_8 = getParticleIds(result[8].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_8.begin(),expected_parallel_neighbors_of_8.end());

    std::vector<int> expected_diagonal_neighbors_of_8 = getParticleIds(result[8].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_8.begin(),expected_diagonal_neighbors_of_8.end());


    ASSERT_EQ(parallel_neighbors_of_8, expected_parallel_neighbors_of_8);
    ASSERT_EQ(diagonal_neighbors_of_8, expected_diagonal_neighbors_of_8);

    

}
