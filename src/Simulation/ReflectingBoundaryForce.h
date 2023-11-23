//
// Created by rodff on 23.11.23.
//

#pragma once

#include "ReflectingBoundary.h"

class ReflectingBoundaryForce : public ReflectingBoundary {
public:
    virtual void processBoundary(LinkedCellContainerStub &container, ForceCalculation &forceCalculation) override;
};
