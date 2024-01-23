#pragma once

#include "OneParticleForceCalculation.h"

class GravityForce: public OneParticleForceCalculation {
public:
    GravityForce(std::array<double,3>  gravity_factor);
    VectorDouble3 CalculateForce(const Particle& p) override;
    ~GravityForce() = default;

    std::array<double,3> getGravityFactor() const {return gravity_factor;}
    void setGravityFactor(std::array<double,3>  val) {gravity_factor = val;}
private:
    std::array<double,3> gravity_factor;
};


