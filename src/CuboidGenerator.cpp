//
// Created by klara on 13.11.23.
//

#include "CuboidGenerator.h"

CuboidGenerator::CuboidGenerator(std::array<double, 3> corner, int n1, int n2, int n3, double particleDistance,
                                 double mass, std::array<double, 3> velocity): corner(), velocity() {
    this->corner = corner;
    this->n1= n1;
    this->n2 = n2;
    this->n3 = n3;
    this->particleDistance = particleDistance;
    this->mass = mass;
    this->velocity = velocity;
    particles.reserve(n1 * n2 * n3);
}

ParticleContainer CuboidGenerator::generateParticles() {
    double xCorner = corner[0];
    double yCorner = corner[1];
    double zCorner = corner[2];
    for(int x = 0; x < n1; x++){
        for(int y = 0; y < n2; y++){
            for(int z = 0; z < n3; z++){
                std::array<double, 3> particlePosition{xCorner - particleDistance * x, yCorner + particleDistance * y, zCorner + particleDistance * z};
                particles.emplace_back(particlePosition, velocity, mass);
            }
        }
    }
    return ParticleContainer(particles);
}
