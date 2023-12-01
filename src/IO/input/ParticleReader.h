#pragma once

#include <string>

#include "SimParameters.h"
#include "../../Particles/DirectSumContainer.h"

class ParticleReader {
public:
    virtual void readFile(DirectSumContainer &container, std::string &filename){};
    virtual void readFile(DirectSumContainer &container, std::string &filename, SimParameters& SimParameters){};
};

