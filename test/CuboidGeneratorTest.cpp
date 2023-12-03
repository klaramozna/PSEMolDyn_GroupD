//
// Created by klara on 15.11.23.
//

#include "CuboidGeneratorTest.h"
#include "../src/Particles/DirectSumContainer.h"

TEST_F(CuboidGeneratorTest, Generating){
    DirectSumContainer container = DirectSumContainer(generator.generateParticles());
    std::array<double, 3> velocity{};
    double mass = 1;
    std::vector<Particle> result = container.getParticleVector();
    ASSERT_EQ(result.size(), 12);
    ASSERT_EQ(result[0], Particle(std::array<double, 3>{0, 0, 0}, velocity, mass));
    ASSERT_EQ(result[1], Particle(std::array<double, 3>{0, 0, 1}, velocity, mass));
    ASSERT_EQ(result[2], Particle(std::array<double, 3>{0, 0, 2}, velocity, mass));
    ASSERT_EQ(result[3], Particle(std::array<double, 3>{0, 1, 0}, velocity, mass));
    ASSERT_EQ(result[4], Particle(std::array<double, 3>{0, 1, 1}, velocity, mass));
    ASSERT_EQ(result[5], Particle(std::array<double, 3>{0, 1, 2}, velocity, mass));
    ASSERT_EQ(result[6], Particle(std::array<double, 3>{1, 0, 0}, velocity, mass));
    ASSERT_EQ(result[7], Particle(std::array<double, 3>{1, 0, 1}, velocity, mass));
    ASSERT_EQ(result[8], Particle(std::array<double, 3>{1, 0, 2}, velocity, mass));
    ASSERT_EQ(result[9], Particle(std::array<double, 3>{1, 1, 0}, velocity, mass));
    ASSERT_EQ(result[10], Particle(std::array<double, 3>{1, 1, 1}, velocity, mass));
    ASSERT_EQ(result[11], Particle(std::array<double, 3>{1, 1, 2}, velocity, mass));
}
