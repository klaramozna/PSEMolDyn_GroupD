#include "PeriodicBoundaryTest.h"

TEST_F(PeriodicBoundaryTest, MirroringLeftX) {
    Particle p = Particle({0.4, 1.5 , 3}, {}, 0);
    Particle pOpposite = Particle({5.4, 1.5, 3}, {}, 0);

    container.addParticle(p);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    ASSERT_TRUE(std::find(container.getParticleVector().begin(), container.getParticleVector().end(), pOpposite) != container.getParticleVector().end());
}

TEST_F(PeriodicBoundaryTest, MirroringRightX) {
    Particle particle = Particle({4.7, 1.5 , 3}, {}, 0);
    Particle pOpposite = Particle({-0.3, 1.5, 3}, {}, 0);
    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    auto particleInVector = std::find_if(particles.begin(), particles.end(), [&](const Particle& p) {
        return p.getX() == particle.getX();  // Adjust the comparison based on your Particle equality criteria
    });

    ASSERT_TRUE(particleInVector != particles.end());
}

TEST_F(PeriodicBoundaryTest, MirroringTopY) {
    Particle particle = Particle({1.5, 4.7, 3}, {}, 0);
    Particle pOpposite = Particle({1.5, -0.3 , 3}, {}, 0);
    container.addParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    auto particleInVector = std::find_if(particles.begin(), particles.end(), [&](const Particle& p) {
        return p.getX() == particle.getX();  // Adjust the comparison based on your Particle equality criteria
    });

    ASSERT_TRUE(particleInVector != particles.end());
}

TEST_F(PeriodicBoundaryTest, MirroringLowerY) {
    Particle particle = Particle({3.5, 0.1, 3}, {}, 0);
    Particle pOpposite = Particle({3.5, 5.1, 3}, {}, 0);
    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    auto particleInVector = std::find_if(particles.begin(), particles.end(), [&](const Particle& p) {
        return p.getX() == particle.getX();  // Adjust the comparison based on your Particle equality criteria
    });

    ASSERT_TRUE(particleInVector != particles.end());
}

TEST_F(PeriodicBoundaryTest, MirroringTopLeftRow) {
    Particle particle = Particle({0.2, 4.4, 3}, {}, 0);

    Particle p1 = Particle({5.2, 4.4 , 3}, {}, 0);
    Particle p2 = Particle({0.2, -0.6, 3}, {}, 0);
    Particle p3 = Particle({5.2, -0.6, 3}, {}, 0);

    std::vector<Particle> toFind = {p1, p2, p3};

    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    areParticlesContained(toFind, particles);
}

TEST_F(PeriodicBoundaryTest, MirroringTopRightRow) {
    Particle particle = Particle({4.9, 4.6, 3}, {}, 0);;

    Particle p1 = Particle({-0.1, 4.6 , 3}, {}, 0);
    Particle p2 = Particle({4.9, -0.4, 3}, {}, 0);
    Particle p3 = Particle({-0.1, -0.4 , 3}, {}, 0);

    std::vector<Particle> toFind = {p1, p2, p3};

    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    areParticlesContained(toFind, particles);
}

TEST_F(PeriodicBoundaryTest, MirroringLowerLeftRow) {
    Particle particle = Particle({0.2, 0.3, 3}, {}, 0);

    Particle p1 = Particle({5.2, 0.3 , 3}, {}, 0);
    Particle p2 = Particle({0.2, 5.3, 3}, {}, 0);
    Particle p3 = Particle({5.2, 5.3, 3}, {}, 0);

    std::vector<Particle> toFind = {p1, p2, p3};

    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    areParticlesContained(toFind, particles);
}

TEST_F(PeriodicBoundaryTest, MirroringLowerRightRow) {
    Particle particle = Particle({4.8, 0.3, 3}, {}, 0);

    Particle p1 = Particle({4.8, 5.3 , 3}, {}, 0);
    Particle p2 = Particle({-0.2, 0.3 , 3}, {}, 0);
    Particle p3 = Particle({-0.2, 5.3, 3}, {}, 0);

    std::vector<Particle> toFind = {p1, p2, p3};

    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    areParticlesContained(toFind, particles);
}

TEST_F(PeriodicBoundaryTest, MirroringLowerLeftCorner) {
    Particle particle = Particle({0.2, 0.3, 0.9}, {}, 0);

    Particle p1 = Particle({5.2, 0.3 , 0.9}, {}, 0);
    Particle p2 = Particle({5.2, 5.3, 0.9}, {}, 0);
    Particle p3 = Particle({0.2, 5.3, 0.9}, {}, 0);
    Particle p4 = Particle({5.2, 0.3 , 5.9}, {}, 0);
    Particle p5 = Particle({5.2, 5.3, 5.9}, {}, 0);
    Particle p6 = Particle({0.2, 5.3, 5.9}, {}, 0);
    Particle p7 = Particle({0.2, 0.3 , 0.9}, {}, 0);

    std::vector<Particle> toFind = {p1, p2, p3,p4, p5, p6, p7};

    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    areParticlesContained(toFind, particles);
}


TEST_F(PeriodicBoundaryTest, MirroringLowerRightCorner) {
    Particle particle = Particle({4.6, 0.3, 0.9}, {}, 0);

    Particle p1 = Particle({-0.4, 0.3 , 0.9}, {}, 0);
    Particle p2 = Particle({4.6, 5.3, 0.9}, {}, 0);
    Particle p3 = Particle({-0.4, 0.3, 0.9}, {}, 0);
    Particle p4 = Particle({-0.4, 0.3 , 5.1}, {}, 0);
    Particle p5 = Particle({4.6, 5.3, 5.1}, {}, 0);
    Particle p6 = Particle({-0.4, 0.3, 5.1}, {}, 0);
    Particle p7 = Particle({4.6, 0.3 , 5.1}, {}, 0);

    std::vector<Particle> toFind = {p1, p2, p3,p4, p5, p6, p7};

    container.addParticle(particle);

    boundaryEnforcer.applyBoundaryConditionsForParticle(particle);

    std::vector<Particle> particles = container.getParticleVector();

    areParticlesContained(toFind, particles);
}

void PeriodicBoundaryTest::areParticlesContained(const std::vector<Particle> &toFind,
                                                 const std::vector<Particle> &particles) {
    for (const Particle& particle : toFind) {
        auto particleInVector = std::find_if(
                particles.begin(),
                particles.end(),
                [&](const Particle& p) {
                    return p.getX() == particle.getX();
                }
        );
        ASSERT_NE(particleInVector, container.getParticleVector().end()) << "Particle not found in the container";
    }
};

