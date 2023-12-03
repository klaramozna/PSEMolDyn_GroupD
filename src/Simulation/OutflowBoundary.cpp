//
// Created by rodff on 22.11.23.
//

#include "OutflowBoundary.h"
#include "../Particles/LinkedCellContainer.h";

void OutflowBoundary::processBoundary(LinkedCellContainer &container) {
    container.deleteHaloParticles(*this);
};