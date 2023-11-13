//
// Created by klara on 13.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDGENERATOR_H
#define PSEMOLDYN_GROUPD_CUBOIDGENERATOR_H

#include "ParticleGenerator.h"

class CuboidGenerator : public ParticleGenerator{
public:
    CuboidGenerator(std::array<double, 3> corner, int numParticlesPerDim, double particleDistance, double mass, std::array<double, 3> velocity);
    ParticleContainer generateParticles() override;
private:
    const double MEAN_VELOCITY_BROWNIAN = 0;
    std::array<double, 3> corner;
    int numParticlesPerDim;
    double particleDistance;
    double mass;
    std::array<double, 3> velocity;
};


#endif //PSEMOLDYN_GROUPD_CUBOIDGENERATOR_H
