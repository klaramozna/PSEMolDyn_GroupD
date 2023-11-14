#pragma once

#include "ParticleReader.h"
#include "CuboidMock.h"

class CuboidReader : public ParticleReader {
private:
    std::vector<CuboidMock> cuboids;
public:
    ~CuboidReader() {};
    void readFile(ParticleContainer &container, std::string &filename) override;
};