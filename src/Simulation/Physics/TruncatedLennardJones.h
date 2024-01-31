

#pragma once

#include "ForceCalculation.h"

class TruncatedLennardJones : public ForceCalculation{
public:

    /**
     * @brief Calculates the Lennard Jones forces between the two particles, runcated at a distance of (2^(1/6)) * sigma), so that only the repulsive part is active
     * @param p1 Particle which should be considered in the force calculation.
     * @param p2 Particle which should be considered in the force calculation.
     * @return The resulting force between the particles.
     */
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override;
};

