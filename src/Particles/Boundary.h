//
// Created by klara on 27.11.23.
//

#ifndef PSEMOLDYN_GROUPD_BOUNDARY_H
#define PSEMOLDYN_GROUPD_BOUNDARY_H


#include <array>
#include "Particle.h"
#include "../Simulation/Physics/ForceCalculation.h"
#include "../utils/BoundaryTypes.h"

class Boundary {
public:
    /**
     * @brief Creates a CuboidBoundary object with the given parameters.
     * @param width Width of the cuboid boundary
     * @param height Height of the cuboid boundary.
     * @param depth Depth of the cuboid boundary.
    */
    Boundary(double width, double height, double depth, double sigma, const std::array<std::string, 6>& boundaryType_str);

    /**
     * @brief Returns true, if the given particle is inside of or on the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is inside / on the boundary, else false.
     */
     virtual bool isInside(const Particle& p);

    /**
     * @brief Returns true, if the given particle is outside of the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is outside of boundary, else false.
     */
    virtual bool isOutside(const Particle& p) final;

    /**
     * @brief Returns the dimensions of the boundary
     * @return Array containing the length measures for each dimension of a 3D space
     */
    virtual std::array<double,3> getDimensions();

    /**
     * @brief Returns array containing boundary types for each wall
     */
    virtual std::array<BoundaryType, 6> getBoundaryTypes();

    /**
     * @brief Destroys a boundary object
     */
    virtual ~Boundary() = default;

protected:
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
     * @brief Type of the boundary for each wall
    */
    std::array<BoundaryType, 6> boundaryTypes{};

    /**
     * @brief Sigma as defined by the parameters
     */
    double sigma;
};


#endif //PSEMOLDYN_GROUPD_BOUNDARY_H
