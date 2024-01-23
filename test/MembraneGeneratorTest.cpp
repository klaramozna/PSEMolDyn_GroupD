#include "MembraneGeneratorTest.h"
#include "../src/Particles/DirectSumContainer.h"
#include "../src/Particles/LinkedCellContainer.h"


TEST_F(MembraneGeneratorTest, Generating){

    LinkedCellContainer lc {Boundary(9, 9, 9, 1.0, {"Reflective", "Reflective","Reflective","Reflective","Reflective","Reflective"}), 2};
    lc.addParticlesPointer(generator.generateParticles());
    std::array<double, 3> velocity{};
    double mass = 1;
    std::vector<Particle> result = lc.getParticleVector();
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
     std::vector<std::shared_ptr<Particle>> parallel_neighbors_of_0 = {std::make_shared<Particle>(result.at(1)),
                                                                       std::make_shared<Particle>(result.at(3))};

    std::vector<std::shared_ptr<Particle>> diagonal_neighbors_of_0 = {std::make_shared<Particle>(result.at(4))};

    std::vector<std::shared_ptr<Particle>> expected_parallel_neighbors_of_0 = result[0].getParallelNeighbours();

    std::vector<std::shared_ptr<Particle>>expected_diagonal_neighbors_of_0 = result[0].getDiagonalNeighbours();


    ASSERT_EQ(parallel_neighbors_of_0.size(), expected_parallel_neighbors_of_0.size());
    ASSERT_EQ(diagonal_neighbors_of_0.size(), expected_diagonal_neighbors_of_0.size());
    

}
