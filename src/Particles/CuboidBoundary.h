//
// Created by klara on 27.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
#define PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H

#include "Boundary.h"

class CuboidBoundary : public Boundary {
public:
    /**
     * @brief Creates a CuboidBoundary object with the given parameters.
     * @param width Width of the cuboid boundary
     * @param height Height of the cuboid boundary.
     * @param depth Depth of the cuboid boundary.
     * @param corner Lower left corner of the boundary (lowest x, y and z).
     */
    CuboidBoundary(double width, double height, double depth, std::array<double, 3> corner = {0, 0, 0}): width(width), height(height), depth(depth), corner(corner){};

     /**
     * @brief Returns true, if the given particle is inside of or on the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is inside / on the boundary, else false.
     */
    bool isInside(const Particle& p) override;

private:

    /**
     * @brief Width of the cuboid boundary.
     */
    double width;

    /**
     * @brief Height of the cuboid boundary.
     */
    double height;

    /**
     * @brief Depth of the cuboid boundary.
     */
    double depth;

    /**
     * @brief Lower left corner of the boundary (lowest x, y and z).
     */
    std::array<double, 3> corner;

};


#endif //PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
