#include "MembraneGeneratorTest.h"
#include "../src/Particles/DirectSumContainer.h"

TEST_F(MembraneGeneratorTest, Generating){
    DirectSumContainer container = DirectSumContainer(generator.generateParticles());
    std::array<double, 3> velocity{};
    double mass = 1;
    std::vector<Particle> result = container.getParticleVector();
    ASSERT_EQ(result.size(), 9);
    ASSERT_EQ(result[0], Particle(std::array<double, 3>{0, 0, 0}, velocity, mass));
    ASSERT_EQ(result[1], Particle(std::array<double, 3>{0, 1, 0}, velocity, mass));
    ASSERT_EQ(result[2], Particle(std::array<double, 3>{0, 2, 0}, velocity, mass));
    ASSERT_EQ(result[3], Particle(std::array<double, 3>{1, 0, 0}, velocity, mass));
    ASSERT_EQ(result[4], Particle(std::array<double, 3>{1, 1, 0}, velocity, mass));
    ASSERT_EQ(result[5], Particle(std::array<double, 3>{1, 2, 0}, velocity, mass));
    ASSERT_EQ(result[6], Particle(std::array<double, 3>{2, 0, 0}, velocity, mass));
    ASSERT_EQ(result[7], Particle(std::array<double, 3>{2, 1, 0}, velocity, mass));
    ASSERT_EQ(result[8], Particle(std::array<double, 3>{2, 2, 0}, velocity, mass));

    /*so it the rectangular grid of this membrane:
    2 --- 5 --- 8
    |     |     |
    1 --- 4 --- 7
    |     |     |
    0 --- 3 --- 6
    */

    //particle at index 0

    std::vector<int> parallel_neighbors_of_0 = {1, 3};
    std::vector<int> diagonal_neighbors_of_0 = {4};

    std::vector<int> expected_parallel_neighbors_of_0 = result[0].getParallelNeighbours();
    std::sort(expected_parallel_neighbors_of_0.begin(),expected_parallel_neighbors_of_0.end());

    std::vector<int> expected_diagonal_neighbors_of_0 = result[0].getDiagonalNeighbours();
    std::sort(expected_diagonal_neighbors_of_0.begin(),expected_diagonal_neighbors_of_0.end());


    ASSERT_EQ(parallel_neighbors_of_0, expected_parallel_neighbors_of_0);
    ASSERT_EQ(diagonal_neighbors_of_0, expected_diagonal_neighbors_of_0);
    
    //particle at index 1

    std::vector<int> parallel_neighbors_of_1 = {0, 2, 4};
    std::vector<int> diagonal_neighbors_of_1 = {3, 5};

     std::vector<int> expected_parallel_neighbors_of_1 = result[1].getParallelNeighbours();
    std::sort(expected_parallel_neighbors_of_1.begin(),expected_parallel_neighbors_of_1.end());

    std::vector<int> expected_diagonal_neighbors_of_1 = result[1].getDiagonalNeighbours();
    std::sort(expected_diagonal_neighbors_of_1.begin(),expected_diagonal_neighbors_of_1.end());


    ASSERT_EQ(parallel_neighbors_of_1, expected_parallel_neighbors_of_1);
    ASSERT_EQ(diagonal_neighbors_of_1, expected_diagonal_neighbors_of_1);

     //particle at index 2

    std::vector<int> parallel_neighbors_of_2 = {1,5};
    std::vector<int> diagonal_neighbors_of_2 = {4};

     std::vector<int> expected_parallel_neighbors_of_2 = result[2].getParallelNeighbours();
    std::sort(expected_parallel_neighbors_of_2.begin(),expected_parallel_neighbors_of_2.end());

    std::vector<int> expected_diagonal_neighbors_of_2 = result[2].getDiagonalNeighbours();
    std::sort(expected_diagonal_neighbors_of_2.begin(),expected_diagonal_neighbors_of_2.end());


    ASSERT_EQ(parallel_neighbors_of_2, expected_parallel_neighbors_of_2);
    ASSERT_EQ(diagonal_neighbors_of_2, expected_diagonal_neighbors_of_2);



    //particle at index 4
    std::vector<int> parallel_neighbors_of_4 = {1, 3, 5, 7};
    std::vector<int> diagonal_neighbors_of_4 = {0, 2 ,6 ,8};

    std::vector<int> expected_parallel_neighbors_of_4 = result[4].getParallelNeighbours();
    std::sort(expected_parallel_neighbors_of_4.begin(),expected_parallel_neighbors_of_4.end());

    std::vector<int> expected_diagonal_neighbors_of_4 = result[4].getDiagonalNeighbours();
    std::sort(expected_diagonal_neighbors_of_4.begin(),expected_diagonal_neighbors_of_4.end());


    ASSERT_EQ(parallel_neighbors_of_4, expected_parallel_neighbors_of_4);
    ASSERT_EQ(diagonal_neighbors_of_4, expected_diagonal_neighbors_of_4);


    //particle at index 8 
    std::vector<int> parallel_neighbors_of_8 = {5, 7};
    std::vector<int> diagonal_neighbors_of_8 = {4};

    std::vector<int> expected_parallel_neighbors_of_8 = result[8].getParallelNeighbours();
    std::sort(expected_parallel_neighbors_of_8.begin(),expected_parallel_neighbors_of_8.end());

    std::vector<int> expected_diagonal_neighbors_of_8 = result[8].getDiagonalNeighbours();
    std::sort(expected_diagonal_neighbors_of_8.begin(),expected_diagonal_neighbors_of_8.end());


    ASSERT_EQ(parallel_neighbors_of_8, expected_parallel_neighbors_of_8);
    ASSERT_EQ(diagonal_neighbors_of_8, expected_diagonal_neighbors_of_8);

}
