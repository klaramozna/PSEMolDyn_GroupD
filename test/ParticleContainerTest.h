#ifndef PARTICLE_CONTAINER_TEST_H
#define PARTICLE_CONTAINER_TEST_H

#include <gtest/gtest.h>
#include "../src/Particles/ParticleContainer.h"

#include <vector>

class ParticleContainerTest : public testing::Test {
protected:
    ParticleContainer container;
    std::vector<Particle> particles;

    void SetUp() override;
};

#endif // PARTICLE_CONTAINER_TEST_H
