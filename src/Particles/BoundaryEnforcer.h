//
// Created by rodff on 14.12.23.
//

#ifndef PSEMOLDYN_GROUPD_BOUNDARYENFORCER_H
#define PSEMOLDYN_GROUPD_BOUNDARYENFORCER_H

#include "LinkedCellContainer.h"

#include "../Simulation/Physics/ForceCalculation.h"

#include "../utils/BoundaryTypes.h"
#include "../utils/BoundaryDirection.h"
#include "../utils/Constants.h"

class BoundaryEnforcer {
public:
    BoundaryEnforcer(double sigma, LinkedCellContainer &container, std::array<double,3> dimensions, std::array<BoundaryType, 6> boundaryTypes, ForceCalculation &fc);
    void applyBoundaryConditionsForParticle(Particle &particle);
private:
    LinkedCellContainer &container;
    std::array<double,3> dimensions;
    std::array<BoundaryType, 6> boundaryTypes;
    double sigma;
    ForceCalculation &fc;

    void applyReflectiveForce(Particle &p, BoundaryDirection boundaryofParticle);
    std::vector<BoundaryDirection> getBoundariesOfParticle(Particle &particle);
};


#endif //PSEMOLDYN_GROUPD_BOUNDARYENFORCER_H
