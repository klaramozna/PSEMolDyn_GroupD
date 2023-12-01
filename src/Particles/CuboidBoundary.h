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
     */
    CuboidBoundary(double width, double height, double depth) {
        dim[0] = width;
        dim[1] = height;
        dim[2] = depth;

        corner = {0.0, 0.0, 0.0};
    };

     /**
     * @brief Returns true, if the given particle is inside of or on the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is inside / on the boundary, else false.
     */
    bool isInside(const Particle& p) override;

    std::array<double,3> getDimensions();

private:

    /**
     * @brief Dimensions of the boundaries
     * dim[0] = Width
     * dim[1] = Height
     * dim[2] = Length
     */
    std::array<double,3> dim{};

    /**
     * @brief Lower Left Corner
     */
    std::array<double,3> corner{};
};


#endif //PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
