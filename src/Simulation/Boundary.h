//
// Created by rodff on 22.11.23.
//

#pragma once

#include "Physics/ForceCalculation.h"
#include <array>
#include <cmath>

/**
 * @file Boundary.h
 *
 * @brief Stores boundary information, such as type of boundary, starting point (3D vector) and dimensions in each axis,
 * and executes the boundary control according to the boundary type of a given "wall"
 * */

class LinkedCellContainer;

class Boundary {
public:
    const double sixthRootOf2 = std::pow(2.0, 1.0 / 6.0);

    /**
     * @brief Goes through all boundary particles and enforces boundary conditions according to the given boundary type
     * @param container LinkedCellContainer that implements the LinkedCellLogic
     * @param calculation Type of potential used to calculate particle interactions. Is useful for a specific
     * type of reflective boundary implementation
     *
     * */
    virtual void processBoundary(LinkedCellContainer &container) = 0;

    /**
     * @brief Constructor for a Boundary class
     * @param dimensions Vector containing the lengths of each "edge" along the axis
     * @param llc Left-Lower-Corner defining a point of reference for the boundaries
     * */
    Boundary(std::array<double, 3> llc, std::array<double, 3> dimensions, ForceCalculation &forceCalculation) : dimensions{dimensions}, llc{llc}, forceCalculation{forceCalculation} {};

    /**
     * @brief Returns true, if the given particle is inside of or on the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is inside / on the boundary, else false.
     */
    bool isInside(const Particle &p) {
        auto isCoordinateInside = [this](double coordinate, int index) -> bool {
            return coordinate >= llc[index] && coordinate <= llc[index] + llc[index];
        };

        std::array<double, 3> pos = p.getX();
        return isCoordinateInside(pos[0], 0) && isCoordinateInside(pos[1], 1) && isCoordinateInside(pos[2], 2);
    }

    /**
     * @brief Destroys a boundary object
     */
    virtual ~Boundary() = default;

    std::array<double,3> getDimensions() {
        return dimensions;
    };

protected:
    std::array<double,3> dimensions;
    std::array<double, 3> llc;
    ForceCalculation &forceCalculation;
};

