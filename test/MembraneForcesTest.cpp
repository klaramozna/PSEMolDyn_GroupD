#include "MembraneForcesTest.h"

void MembraneForcesTest::SetUp() {
    container.addParticlesPointer(generator.generateParticles());
}

TEST_F(MembraneForcesTest, TestNeighbours){
    
    std::vector<Particle> result = container.getParticleVector();
     std::sort(result.begin(), result.end(), [](const Particle& a, const Particle& b) {
        return a.getId() < b.getId();
    });

    std::vector<int> parallel_neighbors_of_0 = {1, 3};
    std::vector<int> diagonal_neighbors_of_0 = {4};

    std::vector<int> expected_parallel_neighbors_of_0 = getParticleIds(result[0].getParallelNeighbours());
    std::sort(expected_parallel_neighbors_of_0.begin(),expected_parallel_neighbors_of_0.end());

    std::vector<int> expected_diagonal_neighbors_of_0 = getParticleIds(result[0].getDiagonalNeighbours());
    std::sort(expected_diagonal_neighbors_of_0.begin(),expected_diagonal_neighbors_of_0.end());


    ASSERT_EQ(parallel_neighbors_of_0, expected_parallel_neighbors_of_0);
    ASSERT_EQ(diagonal_neighbors_of_0, expected_diagonal_neighbors_of_0);


}
//check harmonic forces with hand calculated values
TEST_F(MembraneForcesTest, HarmonicForces){
    ASSERT_EQ(container.getSize(), 9);
    container.applyToAll([this](Particle& p) { applyHarmonicForces(p); });
    ASSERT_EQ(container.getSize(), 9);


    std::array<double,3> r1 {-600,-600, 0};
    ASSERT_EQ(container.getParticleVector().at(0).getId(), 0); 
    ASSERT_EQ(container.getParticleVector().at(0).getFVector().convertToArray(), r1);


    std::array<double,3> r4 {0, 0, 0};
    ASSERT_EQ(container.getParticleVector().at(4).getId(), 4); 
    ASSERT_EQ(container.getParticleVector().at(4).getFVector().convertToArray(), r4);


    std::array<double,3> r8 {600, 600, 0};
    ASSERT_EQ(container.getParticleVector().at(8).getId(), 8); 
    ASSERT_EQ(container.getParticleVector().at(8).getFVector().convertToArray(), r8);

}

TEST_F(MembraneForcesTest, TruncatedLennardJones){
    ASSERT_EQ(container.getSize(), 9);
    std::array<double,3> r8 {600, 600, 0};
    container.applyToAll([this](Particle& p) { applyHarmonicForces(p); });
    ASSERT_EQ(container.getParticleVector().at(8).getFVector().convertToArray(), r8);

    // only particles with id 7 and 5 interact with particle with id 8
    std::array<double,3> r8_2 {624, 624, 0};
    container.applyToPairs([this](Particle& p1, Particle& p2) { calculateF(p1, p2); });
    ASSERT_EQ(container.getParticleVector().at(8).getId(), 8); 
    ASSERT_EQ(container.getParticleVector().at(8).getFVector().convertToArray(), r8_2);

}