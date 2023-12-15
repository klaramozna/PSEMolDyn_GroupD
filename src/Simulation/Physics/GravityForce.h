#pragma once

#include "OneParticleForceCalculation.h"

class GravityForce: public OneParticleForceCalculation {
public:
    GravityForce(double gravity_factor);
    VectorDouble3 CalculateForces(const Particle& p) override;
    ~GravityForce() = default;

private:
    double gravity_factor;
};


