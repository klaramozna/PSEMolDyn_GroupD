//
// Created by klara on 27.11.23.
//

#include "CuboidBoundary.h"

bool CuboidBoundary::isInside(const Particle &p) {
    double x = p.getX()[0];
    double y = p.getX()[1];
    double z = p.getX()[2];
    bool xInside = x >= corner[0] && x <= corner[0] + dim[0];
    bool yInside = y >= corner[1] && y <= corner[1] + dim[1];
    bool zInside = z >= corner[2] && z <= corner[2] + dim[2];
    return xInside && yInside && zInside;
}

std::array<double,3> CuboidBoundary::getDimensions() {
    return dim;
}