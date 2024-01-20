//
// Created by RayenManai on 03.12.23.
//

#include "SphereGenerator.h"
#include <cmath>
#include <iostream>
#include "VectorDouble3.h"

SphereGenerator::SphereGenerator(std::array<double, 3> center, double particleDistance, int radius, double mass, std::array<double, 3> velocity, double epsilon, double sigma): center(), velocity() {
    this->center = center;
    this->particleDistance = particleDistance;
    this->radius = radius;
    this->mass = mass;
    this->velocity = velocity;
    this->epsilon = epsilon;
    this->sigma = sigma;
}

std::vector<std::shared_ptr<Particle>> SphereGenerator::generateParticles(int type) {

    // Generate particles on the surface of the sphere
   for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            for (int k = -radius; k <= radius; ++k) {
                // Calculate positions of particles within the sphere
                double x = center[0] + i * particleDistance;
                double y = center[1] + j * particleDistance;
                double z = center[2] + k * particleDistance;

                // Check if the point is inside the sphere
                VectorDouble3 cord (std::array<double,3>{x - center[0], y - center[1], z - center[2]});
                double distance = cord.getL2Norm();
                if (distance <= radius * particleDistance) {
                    std::array<double, 3> particlePosition{x , y, z};
                    std::shared_ptr<Particle> particlePtr = std::make_shared<Particle>(particlePosition, velocity, mass, epsilon, sigma, type);
                    particles.emplace_back(particlePtr);
                }
            }
        }
    }
    return particles;
}

std::vector<std::shared_ptr<Particle>> SphereGenerator::generateDisk(int type) {

    double z = center[2];
 // Generate particles within the circular area
    for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            // Calculate positions of particles within the circular area
            double x = center[0] + i * particleDistance;
            double y = center[1] + j * particleDistance;

            // Check if the point is inside the disk (circle)
            double distance = sqrt((x - center[0]) * (x - center[0]) + (y - center[1]) * (y - center[1]));
                if (distance <= radius * particleDistance) {
                    std::array<double, 3> particlePosition{x , y, z};
                    std::shared_ptr<Particle> particlePtr = std::make_shared<Particle>(particlePosition, velocity, mass, epsilon, sigma, type);
                    particles.emplace_back(particlePtr);
                }
            }
        }
    return particles;
}