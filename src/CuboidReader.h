#pragma once

#include "ParticleReader.h"

class CuboidReader : public ParticleReader {
public:
    ~CuboidReader() {};
    void readFile(ParticleContainer &container, std::string &filename) override;
};