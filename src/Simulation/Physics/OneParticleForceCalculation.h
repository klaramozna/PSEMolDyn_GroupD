#pragma once

#include "../../Particles/Particle.h"

class OneParticleForceCalculation {
public:
    virtual VectorDouble3 CalculateForce(const Particle& p) = 0;
    virtual ~OneParticleForceCalculation() = default; // Virtual destructor for polymorphism.
};

