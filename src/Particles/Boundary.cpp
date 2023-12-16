//
// Created by klara on 27.11.23.
//

#include "Boundary.h"

bool Boundary::isOutside(const Particle &p) {
    return !isInside(p);
}

bool Boundary::isInside(const Particle &p) {
    double x = p.getX()[0];
    double y = p.getX()[1];
    double z = p.getX()[2];
    bool xInside = x >= corner[0] && x <= corner[0] + dim[0];
    bool yInside = y >= corner[1] && y <= corner[1] + dim[1];
    bool zInside = z >= corner[2] && z <= corner[2] + dim[2];
    return xInside && yInside && zInside;
}

std::array<double,3> Boundary::getDimensions() {
    return dim;
}

Boundary::Boundary(double width, double height, double depth, double sigma, const std::array<std::string, 6>& boundaryType_str) : sigma{sigma} {
    dim[0] = width;
    dim[1] = height;
    dim[2] = depth;

    corner = {0.0, 0.0, 0.0};

    for (int i = 0; i < 6; i++) {
        if (boundaryType_str[i] == "Reflective") {
            boundaryTypes[i] = REFLECTIVE;
        } else if (boundaryType_str[i] == "Outflow") {
            boundaryTypes[i] = OUTFLOW;
        } else if (boundaryType_str[i] == "Periodic") {
            boundaryTypes[i] = PERIODIC;
        }
    }
}

std::array<BoundaryType, 6> Boundary::getBoundaryTypes() {
    return boundaryTypes;
}
