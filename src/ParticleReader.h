#pragma once

#include <string>

#include "ParticleContainer.h"

class ParticleReader {
    virtual void readFile(ParticleContainer &container, std::string &filename) = 0;
};

