//
// Created by klara on 27.11.23.
//

#include "CuboidBoundary.h"

bool CuboidBoundary::isInside(const Particle &p) {
    auto isCoordinateInside = [this](double coordinate, int index) {
        return coordinate >= corner[index] && coordinate <= corner[index] + dim[index];
    };

    std::array<double, 3> pos = p.getX();
    return isCoordinateInside(pos[0], 0) && isCoordinateInside(pos[1], 1) && isCoordinateInside(pos[2], 2);
}

std::array<int,3> CuboidBoundary::getDimensions() {
    return dim;
}