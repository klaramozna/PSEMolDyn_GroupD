//
// Created by rodff on 22.11.23.
//

#pragma once

#include <cmath>
#include <memory>

#include "../Particles/Particle.h"
#include "../Particles/CuboidBoundary.h"

/**
 * @file BoundaryActions.h
 *
 * @brief Stores boundary information, such as type of boundary, starting point (3D vector) and dimensions in each axis,
 * and executes the boundary control according to the boundary type of a given "wall"
 * */

class BoundaryActions {
public:
    BoundaryActions() = delete;

    constexpr static double sixthRootOf2 = 1.12246204831;

    /**
     * @brief Creates an opposing particle based on the position of the given particle and boundary.
     *
     * @param p The particle for which the opposing particle is created.
     * @param boundary The cuboid boundary used to determine the opposing particle's adjusted position.
     * @return The created opposing particle.
     */
    static std::unique_ptr<Particle> createOpposingParticle(const Particle &p, CuboidBoundary &boundary, double sigma);

    /**
     * @brief Finds the position of the opposing particle in relation to the given particle and boundary.
     *
     * This function determines the position of the opposing particle based on the position of the given particle
     * and the dimensions of the provided cuboid boundary. The opposing particle position is adjusted
     * to simulate reflection across the boundaries.
     *
     * @param p The particle for which the opposing particle position is calculated.
     * @param boundary The cuboid boundary used to determine the opposing particle's adjusted position.
     * @return The adjusted position of the opposing particle.
     */
    static std::array<double,3> findOpposingParticle(const Particle& p, CuboidBoundary& boundary);
};