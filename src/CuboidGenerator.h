//
// Created by klara on 13.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDGENERATOR_H
#define PSEMOLDYN_GROUPD_CUBOIDGENERATOR_H

#include "ParticleGenerator.h"

class CuboidGenerator : public ParticleGenerator{
public:
    /**
     * @brief Creates a CuboidGenerator object initializing it with the given parameters.
     * @param corner represents the x, y and z coordinate of the left-lower corner of the front side of the cuboid.
     * @param n1 is the number of particles in x direction.
     * @param n2 is the number of particles in y direction.
     * @param n3 is the number of particles in z direction.
     * @param particleDistance is the distance between particles.
     * @param mass is the mass of each particle.
     * @param velocity is the initial velocity of each particle.
     */
    CuboidGenerator(std::array<double, 3> corner, int n1, int n2, int n3, double particleDistance, double mass, std::array<double, 3> velocity);

    /**
     * @brief Generates a cuboid of particles.
     * @return A particle container with the generated particles.
     */
    ParticleContainer generateParticles() override;

private:
    /**
     * @brief The mean-value of the velocity of the Brownian Motion.
     */
    const double MEAN_VELOCITY_BROWNIAN = 0;

    /**
     * @brief Coordinates of the left-lower corner of the front side of the cuboid.
     */
    std::array<double, 3> corner;

    /**
     * @brief Number of particles in the x direction.
     */
    int n1;

    /**
    * @brief Number of particles in the y direction.
    */
    int n2;

    /**
    * @brief Number of particles in the z direction.
    */
    int n3;

    /**
     * @brief Distance between particles.
     */
    double particleDistance;

    /**
     * @brief Mass of each particle.
     */
    double mass;

    /**
     * @brief Initial velocity of each particle.
     */
    std::array<double, 3> velocity;
};


#endif //PSEMOLDYN_GROUPD_CUBOIDGENERATOR_H
