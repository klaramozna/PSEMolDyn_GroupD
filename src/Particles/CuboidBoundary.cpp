//
// Created by klara on 27.11.23.
//

#include "CuboidBoundary.h"

bool CuboidBoundary::isInside(const Particle &p) {
    double x = p.getX()[0];
    double y = p.getX()[1];
    double z = p.getX()[2];
    bool xInside = x >= corner[0] && x <= corner[0] + width;
    bool yInside = y >= corner[1] && x <= corner[1] + height;
    bool zInside = z >= corner[2] && x <= corner[2] + depth;
    return xInside && yInside && zInside;
}
