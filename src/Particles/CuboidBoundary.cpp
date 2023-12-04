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

/**
 * @brief Gets the boundary type for a specific face of the cuboid.
 * @param face The face index (0 for x-min, 1 for x-max, 2 for y-min, 3 for y-max, 4 for z-min, 5 for z-max).
 * @return The boundary type for the specified face.
 */
BoundaryType CuboidBoundary::getBoundaryType(int face) const {
    if (face >= 0 && face < 6) {
        return boundaryTypes[face];
    }
    return BoundaryType::None;  // Default if face index is out of bounds
}

void CuboidBoundary::setBoundaryType(int face, BoundaryType boundaryType) {
    if (face >= 0 && face < 6) {
        boundaryTypes[face] = boundaryType;
    }
}
