//
// Created by RayenManai on 03.12.23.
//

#pragma once

#include "../Particles/ParticleGenerator.h"

class SphereGenerator : public ParticleGenerator{
public:
    /**
     * @brief Creates a SphereGenerator object initializing it with the given parameters.
     * @param center represents the x, y and z coordinate of the center of the sphere
     * @param particleDistance is the distance between particles.
     * @param radius the radius in terms of the number of molecules along the radius
     * @param mass is the mass of each particle.
     * @param velocity is the initial velocity of the whole sphere.
     */
    SphereGenerator(std::array<double, 3> center, double particleDistance, int radius, double mass, std::array<double, 3> velocity);

    /**
     * @brief Generates a sphere of particles.
     * @return A vector with the generated particles.
     */
    std::vector<Particle> generateParticles(int type = 0) override;

    /**
     * @brief Generates a disk (2D) of particles.
     * @return A vector with the generated particles.
     */
    std::vector<Particle> generateDisk(int type = 0);

private:

    /**
     * @brief Coordinates x, y and z coordinate of the center of the sphere
     */
    std::array<double, 3> center;

    /**
     * @brief Distance between particles.
     */
    double particleDistance;

    /**
     * @brief the radius in terms of the number of molecules along the radius
     */
    int radius;

    /**
     * @brief Mass of each particle.
     */
    double mass;

    /**
     * @brief Initial velocity of the whole sphere
     */
    std::array<double, 3> velocity;
};
