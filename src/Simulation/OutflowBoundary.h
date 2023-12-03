//
// Created by rodff on 22.11.23.
//

#pragma once

#include "Boundary.h"

class OutflowBoundary : public Boundary {
public:
    OutflowBoundary(std::array<double, 3> llc, std::array<double, 3> dimensions, ForceCalculation &forceCalculation) : Boundary(llc, dimensions, forceCalculation) {};
    void processBoundary(LinkedCellContainer &container) override;
};

