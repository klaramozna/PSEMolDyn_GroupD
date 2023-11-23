//
// Created by rodff on 22.11.23.
//

#pragma once

#include "Boundary.h"
#include "./Physics/ForceCalculation.h"

class OutflowBoundary : public Boundary {
    virtual void processBoundary(LinkedCellContainerStub &container, ForceCalculation &forceCalculation) override;
};

