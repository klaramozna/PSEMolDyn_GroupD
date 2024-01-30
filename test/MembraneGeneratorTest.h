#pragma once

#include <gtest/gtest.h>
#include "../src/utils/MembraneGenerator.h"

class MembraneGeneratorTest : public testing::Test {
protected:
    MembraneGenerator generator{std::array<double, 3>{0, 0, 0}, 3, 3, 1, 1, 1, std::array<double, 3>{0, 0, 0}, 1.0, 1.0, 500, 2.2, {}};


    std::vector<int> getParticleIds(const std::vector<std::shared_ptr<Particle>>& particles) {
        std::vector<int> ids;

        for (const auto& particlePtr : particles) {
            if (particlePtr) {
                ids.push_back(particlePtr->getId());
            }
        }
        
        return ids;
    }
};


