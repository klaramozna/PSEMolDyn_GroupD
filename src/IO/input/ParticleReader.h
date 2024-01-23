#pragma once

#include <string>

#include "SimParameters.h"
#include "../../Particles/DirectSumContainer.h"

class ParticleReader {
public:
    virtual void readFile (std::string &filename, SimParameters& simParameters){};

    std::vector<std::shared_ptr<Particle>> getParticles () {
        return particles;
    }
    
    std::vector<std::shared_ptr<Particle>> particles;
};

