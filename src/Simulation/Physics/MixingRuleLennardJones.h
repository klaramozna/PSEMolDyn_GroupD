

#ifndef PSEMOLDYN_GROUPD_MIXINGRULELENNARDJONES_H
#define PSEMOLDYN_GROUPD_MIXINGRULELENNARDJONES_H

#include "ForceCalculation.h"

class MixingRuleLennardJones : public ForceCalculation{
public:

    /**
     * @brief Calculates the Lennard Jones forces between the two particles. The parameters sigma and epsilon are determined based on the type of the particles using mixing rules.
     * @param p1 Particle which should be considered in the force calculation.
     * @param p2 Particle which should be considered in the force calculation.
     * @return The resulting force between the particles.
     */
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override;
};


#endif //PSEMOLDYN_GROUPD_MIXINGRULELENNARDJONES_H
