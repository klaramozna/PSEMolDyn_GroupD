#ifndef PSEMOLDYN_GROUPD_FORCECALCULATION_H
#define PSEMOLDYN_GROUPD_FORCECALCULATION_H

#include "Particle.h"

class ForceCalculation {
private:
    VectorDouble result;
public:
    virtual VectorDouble* CalculateForces(Particle& p1, Particle& p2) = 0;
    virtual ~ForceCalculation() = default; // Virtual destructor for polymorphism.
};

#endif //PSEMOLDYN_GROUPD_FORCECALCULATION_H
