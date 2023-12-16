#pragma once

#include "OneParticleForceCalculation.h"

class GravityForce: public OneParticleForceCalculation {
public:
    GravityForce(double gravity_factor);
    VectorDouble3 CalculateForce(const Particle& p) override;
    ~GravityForce() = default;

    double getGravityFactor() const {return gravity_factor;}
    void setGravityFactor(double val) {gravity_factor = val;}
private:
    double gravity_factor;
};


