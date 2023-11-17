#pragma once

#include <string>

#include "../../Particles/ParticleContainer.h"

class ParticleReader {
public:
    virtual void readFile(ParticleContainer &container, std::string &filename) = 0;
};

