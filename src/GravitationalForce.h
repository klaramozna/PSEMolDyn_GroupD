#ifndef PSEMOLDYN_GROUPD_GRAVITATIONALFORCE_H
#define PSEMOLDYN_GROUPD_GRAVITATIONALFORCE_H

#include "ForceCalculation.h"

class GravitationalForce : public ForceCalculation {
private:
    VectorDouble3 result;
public:
    VectorDouble3* CalculateForces(Particle& p1, Particle& p2) override;
    ~GravitationalForce() override = default; // Virtual destructor for polymorphism.
};


#endif //PSEMOLDYN_GROUPD_GRAVITATIONALFORCE_H
