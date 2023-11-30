#pragma once

#include <string>

#include "../../Particles/ParticleContainer.h"
#include "SimParameters.h"

class ParticleReader {
public:
    virtual void readFile(ParticleContainer &container, std::string &filename){};
    virtual void readFile(ParticleContainer &container, std::string &filename, SimParameters& SimParameters){};

};

