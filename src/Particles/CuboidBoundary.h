//
// Created by klara on 27.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
#define PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H

#include "../Particles/Particle.h"

enum class BoundaryType {
    None = 0,
    Outflow = 1,
    ReflectiveGhostParticle = 2,
    ReflectiveForce = 3,
};

class CuboidBoundary {
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
    bool isInside(const Particle& p);

    /**
     * @brief Sets the boundary type for a specific face of the cuboid.
     * @param face The face index (0 for x-min, 1 for x-max, 2 for y-min, 3 for y-max, 4 for z-min, 5 for z-max).
     * @param boundaryType The boundary type for the specified face.
     */
    void setBoundaryType(int face, BoundaryType boundaryType);

    /**
     * @brief Gets the boundary type for a specific face of the cuboid.
     * @param face The face index (0 for x-min, 1 for x-max, 2 for y-min, 3 for y-max, 4 for z-min, 5 for z-max).
     * @return The boundary type for the specified face.
     */
    BoundaryType getBoundaryType(int face) const;

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

    /**
     * @brief Support different boundaries in 3D
     */
    std::array<BoundaryType, 6> boundaryTypes{BoundaryType::None, BoundaryType::None, BoundaryType::None,
                                             BoundaryType::None, BoundaryType::None, BoundaryType::None};
};


#endif //PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
