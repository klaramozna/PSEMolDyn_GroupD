#pragma once

#include <string>

#include "../../Particles/DirectSumContainer.h"

class ParticleReader {
public:
    virtual void readFile(DirectSumContainer &container, std::string &filename) = 0;
};

