#ifndef PSEMOLDYN_GROUPD_FORCECALCULATION_H
#define PSEMOLDYN_GROUPD_FORCECALCULATION_H

#include "Particle.h"

class ForceCalculation {
public:
    virtual VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) = 0;
    virtual ~ForceCalculation() = default; // Virtual destructor for polymorphism.
};

#endif //PSEMOLDYN_GROUPD_FORCECALCULATION_H
