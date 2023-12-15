//
// Created by rodff on 08.12.23.
//

#ifndef PSEMOLDYN_GROUPD_OUTFLOWBOUNDARY_H
#define PSEMOLDYN_GROUPD_OUTFLOWBOUNDARY_H

#include "Boundary.h"

class OutflowBoundary : public Boundary {
public:
    OutflowBoundary(double width, double height, double depth, ForceCalculation &fc, double cellSize, double sigma) : Boundary(width, height, depth, fc, cellSize, sigma) {};

};
#endif //PSEMOLDYN_GROUPD_OUTFLOWBOUNDARY_H
