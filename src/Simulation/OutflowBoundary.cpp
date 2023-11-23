//
// Created by rodff on 22.11.23.
//

#include "OutflowBoundary.h"

void OutflowBoundary::processBoundary(LinkedCellContainerStub &container, ForceCalculation &forceCalculation) {
    container.deleteHaloParticles();
};