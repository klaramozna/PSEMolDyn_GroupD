#pragma once

#include <string>

#include <memory>
#include "SimParameters.h"
#include "../../Particles/DirectSumContainer.h"

class ParticleReader {
public:
    virtual void readFile(const std::shared_ptr<ParticleContainer> &container, std::string &filename){};
    virtual void readFile(const std::shared_ptr<ParticleContainer> &container, std::string &filename, SimParameters& SimParameters){};
};

