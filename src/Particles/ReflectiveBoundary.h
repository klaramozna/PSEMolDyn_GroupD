//
// Created by rodff on 08.12.23.
//

#ifndef PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARY_H
#define PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARY_H

#include "Boundary.h"

class ReflectiveBoundary : public Boundary {
public:
    void applyBoundaryToParticle(Particle& p, ForceCalculation &fc, double cellSize) override;
    ReflectiveBoundary(double width, double height, double depth);
private:
    static constexpr double sixthRootOfTwo = 1.12246204831;
};


#endif //PSEMOLDYN_GROUPD_REFLECTIVEBOUNDARY_H
