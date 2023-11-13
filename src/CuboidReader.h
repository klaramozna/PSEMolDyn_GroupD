#pragma once

#include "ParticleReader.h"

class CuboidReader : public ParticleReader {
    void readFile(ParticleContainer &container, std::string &filename);
    void generateCuboid(int numberOfCuboids, double mass,
                        ParticleContainer &container,
                        std::array<double, 3> &coordinate,
                        std::array<double, 3> &numParticles,
                        std::array<double, 3> distance,
                        std::array<double, 3> initialVelocity)
};