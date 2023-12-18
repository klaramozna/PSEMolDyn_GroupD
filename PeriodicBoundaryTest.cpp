#include "PeriodicBoundaryTest.h"

TEST_F(PeriodicBoundaryTest, MirroringLeftX) {
    Particle p = Particle({0.4, 1.5 , 3}, {}, 0);
    Particle pOpposite = Particle({5.4, 1.5, 3}, {}, 0);

    container.addParticle(p);

    boundaryEnforcer.applyBoundaryCondition();

    ASSERT_TRUE(std::find(container.getParticleVector().begin(), container.getParticleVector().end(), pOpposite) != container.getParticleVector().end());
}

TEST_F(PeriodicBoundaryTest, MirroringRightX) {
    Particle p = Particle({4.7, 1.5 , 3}, {}, 0);
    Particle pOpposite = Particle({-0.3, 1.5, 3}, {}, 0);

    container.addParticle(p);

    boundaryEnforcer.applyBoundaryCondition();

    ASSERT_TRUE(std::find(container.getParticleVector().begin(), container.getParticleVector().end(), pOpposite) != container.getParticleVector().end());
}

TEST_F(PeriodicBoundaryTest, MirroringTopY) {
    Particle p = Particle({1.5, 4.7, 1}, {}, 0);
    Particle pOpposite = Particle({1.5, -0.3 , 1}, {}, 0);

    container.addParticle(p);

    boundaryEnforcer.applyBoundaryCondition();

    ASSERT_TRUE(std::find(container.getParticleVector().begin(), container.getParticleVector().end(), pOpposite) != container.getParticleVector().end());
}

TEST_F(PeriodicBoundaryTest, MirroringLowerY) {
    Particle p = Particle({3.5, 0.1, 1}, {}, 0);
    Particle pOpposite = Particle({3.5, 5.1 , 1}, {}, 0);

    container.addParticle(p);

    boundaryEnforcer.applyBoundaryCondition();

    ASSERT_TRUE(std::find(container.getParticleVector().begin(), container.getParticleVector().end(), pOpposite) != container.getParticleVector().end());
}

TEST_F(PeriodicBoundaryTest, MirroringTopLeftRow) {
    Particle p = Particle({0.2, 2.7, 3}, {}, 0);

    Particle pOpposite = Particle({-0.2, 2.7 , 3}, {}, 0);
    Particle pOppositeTwo = Particle({});

    container.addParticle(p);

    boundaryEnforcer.applyBoundaryCondition();

    ASSERT_TRUE(std::find(container.getParticleVector().begin(), container.getParticleVector().end(), pOpposite) != container.getParticleVector().end());
}

TEST_F(PeriodicBoundaryTest, MirroringTopRightRow) {
    Particle p = Particle({2.9, 2.6, 1}, {}, 0);
    Particle pOpposite = Particle({3.1, 3.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, MirroringLowerLeftRow) {
    Particle p = Particle({0.2, 0.2, 1}, {}, 0);
    Particle pOpposite = Particle({-0.2, -0.2, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, MirroringLowerRightRow) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, MirroringLowerRightCorner) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}


TEST_F(PeriodicBoundaryTest, MirroringLowerLeftCorner) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, MirroringTopLeftCorner) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, MirroringTopRightCorner) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, ExitingParticleWithMirroring) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}

TEST_F(PeriodicBoundaryTest, ExitingParticleWithoutMirroring) {
    Particle p = Particle({2.7, 0.4, 1}, {}, 0);
    Particle pOpposite = Particle({3.3, -0.4, 1}, {}, 0);

    boundaryEnforcer.applyBoundaryConditionsForParticle(p);

    MockForceCalculation fcTest{};
    VectorDouble3 resultingForce = fcTest.CalculateForces(p, pOpposite);

    ASSERT_TRUE(p.getF() == resultingForce.convertToArray());
}
