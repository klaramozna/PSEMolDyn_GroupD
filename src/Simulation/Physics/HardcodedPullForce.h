#pragma once

#include "OneParticleForceCalculation.h"

class HardcodedPullForce: public OneParticleForceCalculation {
public:
    HardcodedPullForce(std::array<double,3>  pull_factors);
    VectorDouble3 CalculateForce(const Particle& p) override;
    ~HardcodedPullForce() = default;

    std::array<double,3> getPullFactor() const {return pull_factors;}
    void setPullFactors(std::array<double,3>  val) {pull_factors = val;}
private:
    std::array<double,3> pull_factors;
};


