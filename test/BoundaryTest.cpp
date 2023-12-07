//
// Created by rodff on 07.12.23.
//

#include "BoundaryTest.h"

/**
 * @brief Tests isInside function for particles inside, on, and outside a 2x2x2 Boundary.
 */
TEST_F(BoundaryTest, IsInside) {
    Boundary boundary(2.0, 2.0, 2.0);

    // Test particle inside the boundary
    Particle insideParticle({1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, 1.0);
    EXPECT_TRUE(boundary.isInside(insideParticle));

    // Test particle on the boundary
    Particle onBoundaryParticle({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    EXPECT_TRUE(boundary.isInside(onBoundaryParticle));

    // Test particle outside the boundary
    Particle outsideParticle({3.0, 3.0, 3.0}, {0.0, 0.0, 0.0}, 1.0);
    EXPECT_FALSE(boundary.isInside(outsideParticle));
}

/**
 * @brief Tests isOutside function for particles inside, on, and outside a 2x2x2 Boundary.
 */
TEST_F(BoundaryTest, IsOutside) {
    Boundary boundary(2.0, 2.0, 2.0);

    // Test particle inside the boundary
    Particle insideParticle({1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, 1.0);
    EXPECT_FALSE(boundary.isOutside(insideParticle));

    // Test particle on the boundary
    Particle onBoundaryParticle({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    EXPECT_FALSE(boundary.isOutside(onBoundaryParticle));

    // Test particle outside the boundary
    Particle outsideParticle({3.0, 3.0, 3.0}, {0.0, 0.0, 0.0}, 1.0);
    EXPECT_TRUE(boundary.isOutside(outsideParticle));
}

/**
 * @brief Tests getDimensions function for a 2x2x2 Boundary.
 */
TEST_F(BoundaryTest, GetDimensions) {
    // Create a Boundary with dimensions (width=2, height=2, depth=2)
    Boundary boundary(2.0, 2.0, 2.0);

    // Check if the dimensions match
    auto dimensions = boundary.getDimensions();
    EXPECT_EQ(dimensions[0], 2.0);
    EXPECT_EQ(dimensions[1], 2.0);
    EXPECT_EQ(dimensions[2], 2.0);
}