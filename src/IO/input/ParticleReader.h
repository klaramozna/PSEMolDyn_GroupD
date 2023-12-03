#pragma once

#include <string>

#include "SimParameters.h"
#include "../../Particles/DirectSumContainer.h"

class ParticleReader {
public:
    virtual DirectSumContainer readFile(std::string &filename){};
    virtual DirectSumContainer readFile(std::string &filename, SimParameters& SimParameters){};
};

