#pragma once

#include <gtest/gtest.h>
#include "../src/utils/MembraneGenerator.h"
#include "../src/Simulation/Physics/TruncatedLennardJones.h"
#include "../src/Particles/Particle.h" 
#include "../src/utils/VectorDouble3.h" 
#include "../src/Particles/DirectSumContainer.h"
#include<cmath>

class MembraneForcesTest : public testing::Test {
protected:
    MembraneGenerator generator{std::array<double, 3>{0, 0, 0}, 3, 3, 1, 1, 1, std::array<double, 3>{0, 0, 0}, 1.0, 1.0, 300, 2, {}};

    DirectSumContainer container;

    TruncatedLennardJones truncatedLennard{};

    void SetUp() override;

    void applyHarmonicForces(Particle& p) {

        double stiffness = p.getStiffness();
        double averageBondLength = p.getBondLength();

        for (auto neighb : p.getParallelNeighbours())
        {
                double distance = (p.getXVector() - neighb.get()->getXVector()).getL2Norm();
                auto result = (stiffness * (distance - averageBondLength) / distance) * (neighb.get()->getXVector() - p.getXVector());
                p.setF(p.getFVector() + result);
        }

        double square_root_of_two = std::sqrt(2);

        for (auto neighb : p.getDiagonalNeighbours())
        {
                double distance = (p.getXVector() - neighb.get()->getXVector()).getL2Norm();
                auto result = (stiffness * (distance - square_root_of_two * averageBondLength) / distance) * (neighb.get()->getXVector() - p.getXVector());
                p.setF(p.getFVector() + result);
        }

    }

     std::vector<int> getParticleIds(const std::vector<std::shared_ptr<Particle>>& particles) {
        std::vector<int> ids;

        for (const auto& particlePtr : particles) {
            if (particlePtr) {
                ids.push_back(particlePtr->getId());
            }
        }
        
        return ids;
    }

    void calculateF(Particle& p1, Particle& p2) {
        VectorDouble3 result = truncatedLennard.CalculateForces(p1,p2);
        if (!std::isnan(result.at(0)) && !std::isnan(result.at(1)) && !std::isnan(result.at(2))) {
        p1.setF(p1.getFVector() + result);
        p2.setF(p2.getFVector() - result);
    }
}
};


