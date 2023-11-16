#ifndef PSEMOLDYN_GROUPD_GRAVITATIONALFORCE_H
#define PSEMOLDYN_GROUPD_GRAVITATIONALFORCE_H

#include "ForceCalculation.h"

class GravitationalForce : public ForceCalculation {
public:
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override;
    ~GravitationalForce() override = default;
};


#endif //PSEMOLDYN_GROUPD_GRAVITATIONALFORCE_H
