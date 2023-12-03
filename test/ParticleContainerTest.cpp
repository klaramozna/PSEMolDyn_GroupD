#include "ParticleContainerTest.h"


void ParticleContainerTest::SetUp() {
// Initialize a container with a single particle
    Particle particle({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    particles.
    push_back(particle);
    container = DirectSumContainer(particles);
}

/**
 * @brief Ensures consistency of the size() method of DirectSumContainer
 * */
TEST_F(ParticleContainerTest, Size) {
    ASSERT_EQ(container.getSize(), particles.size());
}

/**
 * @brief Tests whether the size() has increased by one and
 * whether it is the same object as passed before
 */
TEST_F(ParticleContainerTest, AddParticle) {
    // Test adding a single particle.
    Particle newParticle({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    container.addParticle(newParticle);
    ASSERT_EQ(container.getSize(), particles.size() + 1)
        << "Expected" << particles.size() + 1 << "but got " << container.getSize();

    auto yieldedParticle = container.end();

    // Container not empty
    if (yieldedParticle != container.begin()) {
        --yieldedParticle; // Decrement the iterator to get the last particle
        Particle yieldedParticleObject = *yieldedParticle; // Access the last particle
        EXPECT_EQ(yieldedParticleObject,newParticle) << "Object inside DirectSumContainer doesn't match the object inside the particle vector " ;

    } else {
        FAIL() << "No object found in DirectSumContainer";
    }
}

/**
 * @brief Tests whether the size() has increased by particlesToAdd.size()
 * and whether all included objects match with the ones in the particles vector
 */
TEST_F(ParticleContainerTest, AddParticles) {
    // Test adding a vector of particles.
    std::vector<Particle> particlesToAdd = {
            Particle({0,0,0}, {0,0,0}, 0.0),
            Particle({0,0,0}, {0,0,0}, 0.0),
            Particle({0,0,0}, {0,0,0}, 0.0),
            Particle({0,0,0}, {0,0,0}, 0.0)
    };
    DirectSumContainer toAdd{particlesToAdd};
    container.addParticles(toAdd);
    ASSERT_EQ(container.getSize(), particles.size() + particlesToAdd.size());
}


/**
 * @brief Tests whether the iterator gives the objects in the correct order
 * and gives the current number of elements
 * */
TEST_F(ParticleContainerTest, Iterator) {
    // Test the basic iterator functionality.
    auto it = container.begin();
    int count = 0;
    while (it != container.end()) {
        ASSERT_EQ(*it, particles[count]);
        ++it;
        ++count;
    }
    ASSERT_EQ(count, particles.size());
}

/**
 * @brief Tests whether the pair iterators only gives pairs of pairwise differente molecules
 * */
TEST_F(ParticleContainerTest, PairIterator) {
    Particle particle1({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    Particle particle2({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, 1.0);
    particles.push_back(particle1);
    particles.push_back(particle2);
    container = DirectSumContainer(particles);
    int pairCount = 0;
    for (auto pairIt = container.beginPair(); pairIt != container.endPair(); ++pairIt) {
        auto pair = *pairIt;

        // Ensure that the pairs do not contain the same particle
        EXPECT_NE(pair.first, pair.second) << "Found a pair that contains the same particles";
        ++pairCount;
    }
    // Pairs of distinct objects are given by (n * (m-1)) / 2
    ASSERT_EQ(pairCount, (particles.size() * (particles.size() - 1)) / 2);
}

/**
 * @brief Test whether applyToAll() works by summing up all of the functions masses
 * */
TEST_F(ParticleContainerTest, ApplyToAll) {
    // Test applying a function to all particles.
    int sum = 0;
    auto addFunction = [&sum](Particle& particle) {
        sum += particle.getM();
    };
    container.applyToAll(addFunction);

    // All masses are 1 => Total mass = m * 1 = m
    ASSERT_EQ(sum, container.getSize());
}
