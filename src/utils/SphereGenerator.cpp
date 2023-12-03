//
// Created by RayenManai on 03.12.23.
//

#include "SphereGenerator.h"
#include <cmath>
#include <iostream>

SphereGenerator::SphereGenerator(std::array<double, 3> center, double particleDistance, int radius, double mass, std::array<double, 3> velocity): center(), velocity() {
    this->center = center;
    this->particleDistance = particleDistance;
    this->radius = radius;
    this->mass = mass;
    this->velocity = velocity;
}

DirectSumContainer SphereGenerator::generateParticles(int type) {

    //number of particles along the radius
    int numParticles = radius * 2 + 1;
    int toReserve = 0;


    // Generate particles on the surface of the sphere
   for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            for (int k = -radius; k <= radius; ++k) {
                // Calculate positions of particles within the sphere
                double x = center[0] + i * particleDistance;
                double y = center[1] + j * particleDistance;
                double z = center[2] + k * particleDistance;

                // Check if the point is inside the sphere
                // to Do: improve with vectorDouble and L2Norm
                double distance = sqrt((x - center[0]) * (x -  center[0]) +
                                       (y - center[1]) * (y -  center[1]) +
                                       (z - center[2] )* (z -  center[2]));
                if (distance <= radius * particleDistance) {
                    std::array<double, 3> particlePosition{x , y, z};
                    particles.emplace_back(particlePosition, velocity, mass, 0);
                }
            }
        }
    }
    return DirectSumContainer(particles);
}
